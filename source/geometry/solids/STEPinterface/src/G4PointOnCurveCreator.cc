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
// $Id: G4PointOnCurveCreator.cc,v 1.4 2001/07/11 10:00:11 gunter Exp $
// GEANT4 tag $Name: geant4-04-01-patch-01 $
//
// 
// ----------------------------------------------------------------------
// Class G4PointOnCurveCreator
//
// Authors: J.Sulkimo, P.Urban.
// Revisions by: L.Broglia, G.Cosmo.
//
// History:
//   18-Nov-1999: First step of re-engineering - G.Cosmo
// ----------------------------------------------------------------------

#include "G4PointOnCurveCreator.hh"
#include "G4GeometryTable.hh"

G4PointOnCurveCreator G4PointOnCurveCreator::csc;

G4PointOnCurveCreator::G4PointOnCurveCreator()
{
  G4GeometryTable::RegisterObject(this);
}

G4PointOnCurveCreator::~G4PointOnCurveCreator() {}

void G4PointOnCurveCreator::CreateG4Geometry(STEPentity& Ent)
{
  G4Curve* crv=0;
  G4double pval = 0;
  
  Ent.ResetAttributes();
  STEPattribute* Attr = Ent.NextAttribute();
  while(Attr->NonRefType() == STRING_TYPE ||
	Attr->NonRefType() == sdaiSTRING )
    Attr = Ent.NextAttribute();	

  // Get basis curve
  STEPentity* TmpEnt= *Attr->ptr.c;
  void* tmp =G4GeometryTable::CreateObject(*TmpEnt);
  crv = (G4Curve*)tmp;
  if (!tmp)
    G4cerr << "WARNING - G4PointOnCurveCreator::CreateG4Geometry" << G4endl
           << "\tUnexpected NULL pointer to G4Curve !" << G4endl;
  
  // Get parameter value
  Attr = Ent.NextAttribute();	
  pval = *Attr->ptr.r;
  
  createdObject = new G4double(pval);
}

void G4PointOnCurveCreator::CreateSTEPGeometry(void* G4obj) {}
