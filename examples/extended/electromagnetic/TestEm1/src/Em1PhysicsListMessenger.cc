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
// $Id: Em1PhysicsListMessenger.cc,v 1.6 2002/03/08 13:43:30 maire Exp $
// GEANT4 tag $Name: geant4-04-01-patch-01 $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "Em1PhysicsListMessenger.hh"

#include "Em1PhysicsList.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

Em1PhysicsListMessenger::Em1PhysicsListMessenger(Em1PhysicsList* EvAct)
:physList(EvAct)
{ 
  cutGCmd = new G4UIcmdWithADoubleAndUnit("/run/particle/setGCut",this);
  cutGCmd->SetGuidance("Set gamma cut.");
  cutGCmd->SetParameterName("Gcut",false);
  cutGCmd->SetRange("Gcut>0.");
  cutGCmd->SetUnitCategory("Length");
  cutGCmd->AvailableForStates(PreInit,Idle);
  
  cutECmd = new G4UIcmdWithADoubleAndUnit("/run/particle/setECut",this);
  cutECmd->SetGuidance("Set electron cut");
  cutECmd->SetParameterName("Ecut",false);
  cutECmd->SetRange("Ecut>0.");
  cutECmd->SetUnitCategory("Length");   
  cutECmd->AvailableForStates(PreInit,Idle);
  
  cutPCmd = new G4UIcmdWithADoubleAndUnit("/run/particle/setPCut",this);
  cutPCmd->SetGuidance("Set proton cut.");
  cutPCmd->SetParameterName("Pcut",false);
  cutPCmd->SetRange("Pcut>0.");
  cutPCmd->SetUnitCategory("Length");      
  cutPCmd->AvailableForStates(PreInit,Idle);
     
  rCmd = new G4UIcmdWithADoubleAndUnit("/run/particle/getRange",this);
  rCmd->SetGuidance("get the electron cut for the current material.");
  rCmd->SetParameterName("energy",false);
  rCmd->SetRange("energy>0.");
  rCmd->SetUnitCategory("Energy");  
  rCmd->AvailableForStates(Idle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

Em1PhysicsListMessenger::~Em1PhysicsListMessenger()
{
  delete cutGCmd;
  delete cutECmd;
  delete cutPCmd;
  delete rCmd;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void Em1PhysicsListMessenger::SetNewValue(G4UIcommand* command,
                                          G4String newValue)
{ 
  if(command == cutGCmd)
    {physList->SetGammaCut(cutGCmd->GetNewDoubleValue(newValue));}
  if(command == cutECmd)
    {physList->SetElectronCut(cutECmd->GetNewDoubleValue(newValue));}
  if(command == cutPCmd)
    {physList->SetProtonCut(cutPCmd->GetNewDoubleValue(newValue));}        
  if(command == rCmd)
    {physList->GetRange(rCmd->GetNewDoubleValue(newValue));}
   
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
