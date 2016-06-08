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
// $Id: BrachyDetectorMessenger.cc,v 1.2 2002/06/18 22:30:31 guatelli Exp $
// GEANT4 tag $Name: geant4-04-01-patch-01 $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "BrachyDetectorMessenger.hh"

#include "BrachyDetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

BrachyDetectorMessenger::BrachyDetectorMessenger( BrachyDetectorConstruction* Det)
  :Detector(Det)
{ 
  detDir = new G4UIdirectory("/detector/");
  detDir->SetGuidance(" detector control.");
      
  AbsMaterCmd = new G4UIcmdWithAString("/detector/setMaterial",this);
  AbsMaterCmd->SetGuidance("Select Material of the detector.");
  AbsMaterCmd->SetParameterName("choice",false);
  AbsMaterCmd->AvailableForStates(Idle);
   
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

BrachyDetectorMessenger::~BrachyDetectorMessenger()
{
 
  delete AbsMaterCmd; 
  delete UpdateCmd;
  delete detDir;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void BrachyDetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  if( command == AbsMaterCmd )
    { Detector->SetAbsorberMaterial(newValue);}
   
 

  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
