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
// $Id: Em10PrimaryGeneratorAction.hh,v 1.2 2001/07/11 09:57:20 gunter Exp $
// GEANT4 tag $Name: geant4-04-01-patch-01 $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#ifndef Em10PrimaryGeneratorAction_h
#define Em10PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;
class Em10DetectorConstruction;
class Em10PrimaryGeneratorMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class Em10PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    Em10PrimaryGeneratorAction(Em10DetectorConstruction*);    
   ~Em10PrimaryGeneratorAction();

  public:
    void GeneratePrimaries(G4Event*);
    void SetRndmFlag(G4String val) { rndmFlag = val;}
    void Setxvertex(G4double x) ;
    void Setyvertex(G4double y) ;
    void Setzvertex(G4double z) ;

    static G4String GetPrimaryName() ;                

  private:
    G4ParticleGun*                particleGun;	//pointer a to G4 service class
    Em10DetectorConstruction*      Em10Detector; //pointer to the geometry
    
    Em10PrimaryGeneratorMessenger* gunMessenger; //messenger of this class
    G4String                      rndmFlag;	//flag for a random impact point       

    static G4String thePrimaryParticleName ;
    G4double xvertex,yvertex,zvertex;
    G4bool vertexdefined ;

};

#endif


