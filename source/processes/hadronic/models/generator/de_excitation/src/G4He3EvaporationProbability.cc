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
// $Id: G4He3EvaporationProbability.cc,v 1.5 2002/12/12 19:17:21 gunter Exp $
// GEANT4 tag $Name: geant4-05-00 $
//
// Hadronic Process: Nuclear De-excitations
// by V. Lara (Nov 1999)
//


#include "G4He3EvaporationProbability.hh"

G4He3EvaporationProbability::G4He3EvaporationProbability() :
    G4EvaporationProbability(3,2,6) // A,Z,Gamma
{
    G4std::vector<G4double>::size_type NumExcitedStatesEnergy = 31+1;
    G4std::vector<G4int>::size_type NumExcitedStatesSpin = 31+1;
    ExcitEnergies.reserve(NumExcitedStatesEnergy);
    ExcitSpins.reserve(NumExcitedStatesSpin);
    ExcitEnergies.insert(ExcitEnergies.begin(),NumExcitedStatesEnergy,0.0);
    ExcitSpins.insert(ExcitSpins.begin(),NumExcitedStatesSpin,0.0);


	
    ExcitEnergies[18] = 7.29*MeV;
    ExcitEnergies[20] = 6.48*MeV;
    ExcitEnergies[25] = 5.69*MeV;
    ExcitEnergies[26] = 8.31*MeV;
    ExcitEnergies[31] = 5.10*MeV;

    ExcitSpins[18] = 6;
    ExcitSpins[20] = 8;
    ExcitSpins[25] = 3;
    ExcitSpins[26] = 2;
    ExcitSpins[31] = 7;	
	
    SetExcitationEnergiesPtr(&ExcitEnergies);
    SetExcitationSpinsPtr(&ExcitSpins);	
}

G4He3EvaporationProbability::G4He3EvaporationProbability(const G4He3EvaporationProbability &right)
{
    G4Exception("G4He3EvaporationProbability::copy_constructor meant to not be accessable");
}




const G4He3EvaporationProbability & G4He3EvaporationProbability::
operator=(const G4He3EvaporationProbability &right)
{
    G4Exception("G4He3EvaporationProbability::operator= meant to not be accessable");
    return *this;
}


G4bool G4He3EvaporationProbability::operator==(const G4He3EvaporationProbability &right) const
{
    return false;
}

G4bool G4He3EvaporationProbability::operator!=(const G4He3EvaporationProbability &right) const
{
    return true;
}

G4double G4He3EvaporationProbability::CCoeficient(const G4double aZ) const
{
    // Data comes from 
    // Dostrovsky, Fraenkel and Friedlander
    // Physical Review, vol 116, num. 3 1959
    // 
    // const G4int size = 5;
    // G4double Zlist[5] = { 10.0, 20.0, 30.0, 50.0, 70.0};
    //	G4double Calpha[5] = { 0.10, 0.10, 0.10, 0.08, 0.06};
    // C for He3 is equal to C for alpha times 4/3
    G4double C = 0.0;
	
	
    if (aZ <= 30) {
	C = 0.10;
    } else if (aZ <= 50) {
	C = 0.1 + -((aZ-50.)/20.)*0.02;
    } else if (aZ < 70) {
	C = 0.08 + -((aZ-70.)/20.)*0.02;
    } else {
	C = 0.06;
    }
    return C*(4.0/3.0);
}