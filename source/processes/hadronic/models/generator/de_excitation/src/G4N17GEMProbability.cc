//
// ********************************************************************
// * DISCLAIMER                                                       *
// *                                                                  *
// * The following disclaimer summarizes all the specific disclaimers *
// * of contributors to this software. The specific disclaimers,which *
// * govern, are listed with their locations in:                      *
// *   http://cern.ch/geant4/license                                  *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.                                                             *
// *                                                                  *
// * This  code  implementation is the  intellectual property  of the *
// * GEANT4 collaboration.                                            *
// * By copying,  distributing  or modifying the Program (or any work *
// * based  on  the Program)  you indicate  your  acceptance of  this *
// * statement, and all its terms.                                    *
// ********************************************************************
//
//
// $Id: G4N17GEMProbability.cc,v 1.1 2002/06/06 18:02:21 larazb Exp $
// GEANT4 tag $Name: geant4-04-01-patch-01 $
//
// Hadronic Process: Nuclear De-excitations
// by V. Lara (Nov 1999)
//


#include "G4N17GEMProbability.hh"

G4N17GEMProbability::G4N17GEMProbability() :
  G4GEMProbability(17,7,1.0/2.0) // A,Z,Spin
{
  ExcitEnergies.push_back(1373.9*keV);
  ExcitSpins.push_back(3.0/2.0);
  ExcitLifetimes.push_back(64e-15*s);

  ExcitEnergies.push_back(1849.6*keV);
  ExcitSpins.push_back(1.0/2.0);
  ExcitLifetimes.push_back(28e-12*s);

  ExcitEnergies.push_back(1906.8*keV);
  ExcitSpins.push_back(5.0/2.0);
  ExcitLifetimes.push_back(7.60e-12*s);

  ExcitEnergies.push_back(2526.0*keV);
  ExcitSpins.push_back(5.0/2.0);
  ExcitLifetimes.push_back(23e-12*s);

  ExcitEnergies.push_back(3128.9*keV);
  ExcitSpins.push_back(7.0/2.0);
  ExcitLifetimes.push_back(191e-15*s);

  ExcitEnergies.push_back(3204.2*keV);
  ExcitSpins.push_back(3.0/2.0);
  ExcitLifetimes.push_back(21e-15*s);

  ExcitEnergies.push_back(3628.7*keV);
  ExcitSpins.push_back(9.0/2.0);
  ExcitLifetimes.push_back(8.30e-12*s);

  ExcitEnergies.push_back(3663.0*keV);
  ExcitSpins.push_back(3.0/2.0);
  ExcitLifetimes.push_back(243e-15*s);

  ExcitEnergies.push_back(3906.0*keV);
  ExcitSpins.push_back(7.0/2.0);
  ExcitLifetimes.push_back(36e-15*s);

  ExcitEnergies.push_back(4006.4*keV);
  ExcitSpins.push_back(3.0/2.0);
  ExcitLifetimes.push_back(10e-15*s);

  ExcitEnergies.push_back(4208.0*keV);
  ExcitSpins.push_back(5.0/2.0);
  ExcitLifetimes.push_back(49e-15*s);

  ExcitEnergies.push_back(4415.0*keV);
  ExcitSpins.push_back(7.0/2.0);
  ExcitLifetimes.push_back(42e-15*s);

  ExcitEnergies.push_back(5170.0*keV);
  ExcitSpins.push_back(9.0/2.0);
  ExcitLifetimes.push_back(42e-15*s);

  ExcitEnergies.push_back(5195.0*keV);
  ExcitSpins.push_back(5.0/2.0);
  ExcitLifetimes.push_back(66e-15*s);

  ExcitEnergies.push_back(5514.0*keV);
  ExcitSpins.push_back(3.0/2.0);
  ExcitLifetimes.push_back(69e-15*s);

  ExcitEnergies.push_back(5770.0*keV);
  ExcitSpins.push_back(7.0/2.0);
  ExcitLifetimes.push_back(83e-15*s);

  SetExcitationEnergiesPtr(&ExcitEnergies);
  SetExcitationSpinsPtr(&ExcitSpins);
  SetExcitationLifetimesPtr(&ExcitLifetimes);
}


G4N17GEMProbability::G4N17GEMProbability(const G4N17GEMProbability &right)
{
  G4Exception("G4N17GEMProbability::copy_constructor meant to not be accessable");
}




const G4N17GEMProbability & G4N17GEMProbability::
operator=(const G4N17GEMProbability &right)
{
  G4Exception("G4N17GEMProbability::operator= meant to not be accessable");
  return *this;
}


G4bool G4N17GEMProbability::operator==(const G4N17GEMProbability &right) const
{
  return false;
}

G4bool G4N17GEMProbability::operator!=(const G4N17GEMProbability &right) const
{
  return true;
}



