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
// $Id: G4PPara.cc,v 1.3 2001/07/11 10:02:24 gunter Exp $
// GEANT4 tag $Name: geant4-04-01-patch-01 $
//
// class G4PPara
//
// Implementation for G4PPara class
//
// History:
// 19.06.98 A.Kimura Converted G4Para.cc

#include <math.h>

#include "G4VSolid.hh"
#include "G4PPara.hh"
#include "G4Para.hh"

// Constructor - check and set half-widths

G4PPara::G4PPara(const G4Para* thePara)
 : G4PCSGSolid(thePara->GetName())
{
    G4double pDx = thePara->GetXHalfLength();
    G4double pDy = thePara->GetYHalfLength();
    G4double pDz = thePara->GetZHalfLength();

    if(pDx>0&&pDy>0&&pDz>0) {
	fDx = pDx;
	fDy = pDy;
	fDz = pDz;
	fTalpha = thePara->GetTanAlpha();
	G4ThreeVector symAxis = thePara->GetSymAxis();
	fTthetaCphi = symAxis.x()/symAxis.z();
	fTthetaSphi = symAxis.y()/symAxis.z();
    } else {
	G4Exception("Error in G4PPara::G4PPara - Invalid Length Parameters");
    }
}
// ----------------------------------------------------------------------------

G4PPara::~G4PPara()
{;}

// ----------------------------------------------------------------------------

// make a transient object
G4VSolid* G4PPara::MakeTransientObject() const {
    G4ThreeVector symaxis = GetSymAxis();
    G4double alpha = atan(fTalpha);
    G4double theta = acos(symaxis.z());
    G4double phi   = acos(fTthetaCphi/tan(theta));

    G4VSolid* transientObject = new G4Para(GetName(),
					 fDx, fDy, fDz,
					 alpha, theta, phi);
    return transientObject;
}

// ********************************  End of G4PPara.cc   ********************************
