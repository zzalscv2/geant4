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
// * authors in the GEANT4 collaboration.                             *
// * By copying,  distributing  or modifying the Program (or any work *
// * based  on  the Program)  you indicate  your  acceptance of  this *
// * statement, and all its terms.                                    *
// ********************************************************************
//
//
// $Id: G4DistributionGenerator.cc,v 1.8 2001/10/05 16:09:44 hpw Exp $
// GEANT4 tag $Name: geant4-04-01-patch-01 $
//
// -------------------------------------------------------------------
//      GEANT 4 class file --- Copyright CERN 1998
//      CERN Geneva Switzerland
//
//
//      File name:     G4DistributionGenerator
//
//      Author:        Maria Grazia Pia (pia@genova.infn.it)
// 
//      Creation date: 8 May 1998
//
//      Modifications: 
// -------------------------------------------------------------------

#include "globals.hh"
#include "G4DistributionGenerator.hh"
#include "G4ios.hh"
#include <assert.h>

// Constructor

G4DistributionGenerator::G4DistributionGenerator(G4std::vector<G4double>& x,
						 G4std::vector<G4double>& values)
  
{
  _x = x;

  // Check boundaries: must be size(x) = size(values) + 1
  if (x.size() != (values.size() + 1))
    { G4cout << " Inconsistent parameters in G4DistributionGenerator "
	   << G4endl;
    }
  assert (x.size() == (values.size() + 1));

  G4double tot = 0.;
  unsigned int i;
  for (i=0; i<values.size(); i++) { tot += values[i]; }
  assert (tot > 0.);
  
  _cumProb.push_back(0.);    
  //  _cumProb.push_back(values[0] / tot);
  G4double sum = 0.;
  for (i=0; i<values.size(); i++) 
    { 
      sum += values[i];
      _cumProb.push_back(sum / tot); }

  // Debugging
  /*
  for (i=0; i<values.size(); i++)
    { G4cout << values[i] << "  " ; }
  G4cout << "  Integral = " << tot << G4endl;
  for (i=0; i<_cumProb.size(); i++)
    { 
      G4cout << "Variable " << _x[i]  
	   << " --- cumProb = " << _cumProb[i] << G4endl;
    }
  */
  // End of debugging

}

// Destructor

G4DistributionGenerator::~G4DistributionGenerator()
{
}


G4double G4DistributionGenerator::Generate(G4double ranflat)
{
  G4double xRandom = _x[0];

  G4int bin = _cumProb.size() - 1;
  unsigned int i;
  for (i=1; i<_cumProb.size(); i++)
    {
      if (ranflat >= _cumProb[i-1] && ranflat < _cumProb[i])
	{
	  bin = i - 1;
	}
    }

  if (bin >= 0 && bin < static_cast<G4int>(_cumProb.size()-1) && bin < static_cast<G4int>(_x.size()-1)) 
    {
      G4double coeff = (ranflat - _cumProb[bin]) *  (_x[bin+1] - _x[bin]) / 
                   (_cumProb[bin+1] - _cumProb[bin]);
      xRandom = _x[bin] + coeff;

      // Deugging
      /*
      G4cout << "Random = " << ranflat << " Generated " << xRandom << G4endl;
      */
      // Endo of Debugging

    }
  else
    { 	
      // Debugging
      /*
      G4cout << "Bin " << bin << " "
	   << _cumProb.size() << " " 
	   << _x.size()
	   << G4endl;
      */
      // End of debugging
    }

  return xRandom;

}


