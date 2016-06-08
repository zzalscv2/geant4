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
// $Id: CadVisManager.cc,v 1.1 2002/06/20 10:00:56 gcosmo Exp $
// GEANT4 tag $Name: geant4-04-01-patch-01 $
// --------------------------------------------------------------------

#ifdef G4VIS_USE

#include "CadVisManager.hh"

// Visualization drivers...

#include "G4ASCIITree.hh"
#include "G4DAWNFILE.hh"
#include "G4GAGTree.hh"
#include "G4HepRepFile.hh"
#include "G4RayTracer.hh"

CadVisManager::CadVisManager () {}

void CadVisManager::RegisterGraphicsSystems ()
{
  RegisterGraphicsSystem (new G4ASCIITree);
  RegisterGraphicsSystem (new G4DAWNFILE);
  RegisterGraphicsSystem (new G4GAGTree);
  RegisterGraphicsSystem (new G4HepRepFile);
  RegisterGraphicsSystem (new G4RayTracer);

  if (fVerbose > 0)
  {
    G4cout << G4endl
           << "You have successfully chosen to use"
	   << " the following graphics systems:"
	   << G4endl;
    PrintAvailableGraphicsSystems ();
  }
}

#endif
