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
// $Id: G4ExcitedBaryons.hh,v 1.5 2001/07/11 10:02:05 gunter Exp $
// GEANT4 tag $Name: geant4-04-01-patch-01 $
//
// 
// ------------------------------------------------------------
//      GEANT 4 class header file
//
//      History: first implementation, based on object model of
//      Hisaya Kurashige, 27 June 1998
// ----------------------------------------------------------------


#ifndef G4ExcitedBaryons_h
#define G4ExcitedBaryons_h 1

#include "globals.hh"
#include "G4ios.hh"
#include "G4VShortLivedParticle.hh"

// ######################################################################
// ###                          ExcitedBaryons                        ###
// ######################################################################

class G4ExcitedBaryons : public G4VShortLivedParticle
{
 public:
   G4ExcitedBaryons(
       const G4String&     aName,        G4double            mass,
       G4double            width,        G4double            charge,   
       G4int               iSpin,        G4int               iParity,    
       G4int               iConjugation, G4int               iIsospin,   
       G4int               iIsospin3,    G4int               gParity,
       const G4String&     pType,        G4int               lepton,      
       G4int               baryon,       G4int               encoding,
       G4bool              stable,       G4double            lifetime,
       G4DecayTable        *decaytable
   );
   G4ExcitedBaryons*    ExcitedBaryonsDefinition(){return this;};
   G4ExcitedBaryons*    ExcitedBaryons(){return this;};
   void                 SetMultipletName(const G4String& name);
};

inline
 void G4ExcitedBaryons::SetMultipletName(const G4String& name)
{
   SetParticleSubType(name);
}

#endif






