//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  File:   G4BetaPlusDecay.cc                                                //
//  Author: D.H. Wright (SLAC)                                                //
//  Date:   14 November 2014                                                  //
//  Modifications:                                                            //
//    23.08.2023 V.Ivanchenko                                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "G4BetaPlusDecay.hh"
#include "G4BetaDecayCorrections.hh"
#include "G4IonTable.hh"
#include "G4ThreeVector.hh"
#include "G4LorentzVector.hh"
#include "G4DynamicParticle.hh"
#include "G4DecayProducts.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4Positron.hh"
#include "G4NeutrinoE.hh"
#include "G4RandomDirection.hh"
#include "G4BetaSpectrumSampler.hh"
#include <iostream>
#include <iomanip>

namespace {
  const G4double eMass = CLHEP::electron_mass_c2;
}

G4BetaPlusDecay::G4BetaPlusDecay(const G4ParticleDefinition* theParentNucleus,
                                 const G4double& branch, const G4double& e0,
                                 const G4double& excitationE,
                                 const G4Ions::G4FloatLevelBase& flb,
                                 const G4BetaDecayType& betaType)
 : G4NuclearDecay("beta+ decay", BetaPlus, excitationE, flb),
   maxEnergy(e0/eMass - 2.0),
   estep(maxEnergy/(G4double)(npti - 1))
{
  SetParent(theParentNucleus);  // Store name of parent nucleus, delete G4MT_parent 
  SetBR(branch);
  SetNumberOfDaughters(3);

  fPrimaryIon = theParentNucleus;
  fLepton = G4Positron::Positron();
  fNeutrino = G4NeutrinoE::NeutrinoE();

  G4IonTable* theIonTable = G4ParticleTable::GetParticleTable()->GetIonTable();
  G4int daughterZ = theParentNucleus->GetAtomicNumber() - 1;
  G4int daughterA = theParentNucleus->GetAtomicMass();
  fResIon = const_cast<const G4ParticleDefinition*>(theIonTable->GetIon(daughterZ, daughterA,
                                                                        excitationE, flb));

  parentMass = theParentNucleus->GetPDGMass();
  resMass = fResIon->GetPDGMass();

  SetUpBetaSpectrumSampler(daughterZ, daughterA, betaType);

  SetDaughter(0, fResIon);
  SetDaughter(1, fLepton);
  SetDaughter(2, fNeutrino);

  // Fill G4MT_parent with theParentNucleus (stored by SetParent in ctor)  
  CheckAndFillParent();

  // Fill G4MT_daughters with e+, nu and residual nucleus (stored by SetDaughter)  
  CheckAndFillDaughters();
}

G4DecayProducts* G4BetaPlusDecay::DecayIt(G4double)
{
  // Set up final state
  // parentParticle is set at rest here because boost with correct momentum 
  // is done later
  G4DynamicParticle prim(fPrimaryIon, G4ThreeVector(0,0,1), 0.0);
  G4DecayProducts* products = new G4DecayProducts(prim);

  // Generate positron isotropic in angle, with energy from stored spectrum
  const G4double eKE = eMass*G4BetaSpectrumSampler::shoot(npti, cdf, estep);

  G4double eMomentum = std::sqrt(eKE*(eKE + 2.*eMass));
  G4ThreeVector dir = G4RandomDirection();
  G4DynamicParticle* dp = new G4DynamicParticle(fLepton, dir, eKE);
  products->PushProducts(dp);
  /*
  G4cout << "G4BetaPlusDecay::DecayIt: " << fPrimaryIon->GetParticleName() 
	 << " -> " << fResIon->GetParticleName() << " + " << fLepton->GetParticleName()
	 << " + " << fNeutrino->GetParticleName() << " Ee(MeV)=" << eKE
         << G4endl;
  */
  // 4-momentum of residual ion and neutrino
  G4LorentzVector lv(-eMomentum*dir.x(), -eMomentum*dir.y(), -eMomentum*dir.z(),
                     parentMass - eKE - eMass);

  const G4double elim = CLHEP::eV;
  // centrum of mass system
  G4double M = lv.mag();
  G4double edel = M - resMass;
  // Free energy should be above limit
  if (edel >= elim) {
    // neutrino
    G4double eNu = 0.5*(M - resMass*resMass/M);
    G4LorentzVector lvnu(eNu*G4RandomDirection(), eNu);
    lvnu.boost(lv.boostVector());
    dir = lvnu.vect().unit();
    dp = new G4DynamicParticle(fNeutrino, dir, lvnu.e());
    products->PushProducts(dp);

    // residual
    lv -= lvnu;
    dir = lv.vect().unit();
    G4double ekin = std::max(lv.e() - resMass, 0.0);
    dp = new G4DynamicParticle(fResIon, dir, ekin);
    products->PushProducts(dp);

  } else {
    // neglecting relativistic kinematic and giving all energy to neutrino
    dp = new G4DynamicParticle(fNeutrino, G4RandomDirection(), elim);
    products->PushProducts(dp);
    dp = new G4DynamicParticle(fResIon, G4ThreeVector(0.0,0.0,1.0), 0.0);
    products->PushProducts(dp);
  }

  return products;
}


void
G4BetaPlusDecay::SetUpBetaSpectrumSampler(const G4int& daughterZ,
                                          const G4int& daughterA,
                                          const G4BetaDecayType& betaType)
{
  cdf[0] = 0.0;

  // Check for cases in which Q < 2Me (e.g. z67.a162) 
  if (maxEnergy > 0.) {
    G4BetaDecayCorrections corrections(-daughterZ, daughterA);

    // Fill array to store cumulative spectrum
    G4double ex;  // Positron kinetic energy
    G4double p;   // Positron momentum in units of electron mass
    G4double f;   // Spectral shape function
    G4double f0 = 0.0;
    G4double sum = 0.0;
    for (G4int i = 1; i < npti-1; ++i) {
      ex = estep*i;
      p = std::sqrt(ex*(ex + 2.));
      f = p*(1. + ex)*(maxEnergy - ex)*(maxEnergy - ex);

      // Apply Fermi factor to get allowed shape
      f *= corrections.FermiFunction(1. + ex);

      // Apply shape factor for forbidden transitions
      f *= corrections.ShapeFactor(betaType, p, maxEnergy - ex);
      sum += f + f0;
      cdf[i] = sum;
      f0 = f;
    }
    cdf[npti-1] = sum + f0;
  } else {
    for (G4int i = 0; i < npti; ++i) { cdf[i] = 0.0; }
  }
}

void G4BetaPlusDecay::DumpNuclearInfo()
{
  G4cout << " G4BetaPlusDecay  " << fPrimaryIon->GetParticleName()
	 << " -> " << fResIon->GetParticleName() << " + " << fLepton->GetParticleName()
	 << " + " << fNeutrino->GetParticleName() << " Eemax(MeV)="
	 << maxEnergy*eMass << " BR=" << GetBR() << "%" << G4endl;
}
