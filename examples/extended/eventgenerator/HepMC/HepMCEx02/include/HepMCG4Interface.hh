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

// ====================================================================
//
//   HepMCG4Interface.hh
//   $Id: HepMCG4Interface.hh,v 1.2 2002/11/19 10:25:08 murakami Exp $
//
//   A base class for primary generation via HepMC object.
//   This class is derived from G4VPrimaryGenerator.
//
// ====================================================================
#ifndef HEPMC_G4_INTERFACE_H
#define HEPMC_G4_INTERFACE_H

#include "G4VPrimaryGenerator.hh"
#include "HepMC/GenEvent.h"

class HepMCG4Interface : public G4VPrimaryGenerator {
protected:
  // Note that the life of HepMC event object must be handled by users.
  // In the default implementation, a current HepMC event will be
  // deleted at GeneratePrimaryVertex() in the next event.
  HepMC::GenEvent* hepmcEvent; // (care for single event case only)

  // We  have to take care for the position of primaries because
  // primary vertices outside the world voulme give rise to G4Execption.
  // If the default implementation is not adequate, an alternative 
  // can be implemented in your own class.
  virtual G4bool CheckVertexInsideWorld(const G4ThreeVector& pos) const;

  // service method for conversion from HepMC::GenEvent to G4Event
  void HepMC2G4(const HepMC::GenEvent* hepmcevt, G4Event* g4event);

  // Implement this method in his/her own concrete class.
  // An empty event will be created in default.
  virtual HepMC::GenEvent* GenerateHepMCEvent();

public: 
  HepMCG4Interface();
  virtual ~HepMCG4Interface();

  // set/get methods
  HepMC::GenEvent* GetHepMCGenEvent() const;

  // The default behavior is that a single HepMC event generated by
  // GenerateHepMCEvent() will be converted to G4Event through HepMC2G4().
  virtual void GeneratePrimaryVertex(G4Event* anEvent);
};

// ====================================================================
// inline functions
// ====================================================================

inline HepMC::GenEvent* HepMCG4Interface::GetHepMCGenEvent() const 
{ 
  return hepmcEvent; 
}

#endif