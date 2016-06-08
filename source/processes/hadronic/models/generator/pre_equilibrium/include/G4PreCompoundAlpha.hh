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
// $Id: G4PreCompoundAlpha.hh,v 1.10 2002/06/06 16:59:32 larazb Exp $
// GEANT4 tag $Name: geant4-04-01-patch-01 $
//
// by V. Lara

#ifndef G4PreCompoundAlpha_h
#define G4PreCompoundAlpha_h 1

#include "G4VPreCompoundIon.hh"
#include "G4ReactionProduct.hh"
#include "G4Alpha.hh"

#include "G4AlphaCoulombBarrier.hh"


class G4PreCompoundAlpha : public G4VPreCompoundIon
{
public:
  // default constructor
  G4PreCompoundAlpha():G4VPreCompoundIon(4,2,&theAlphaCoulombBarrier,"Alpha") {}

  // copy constructor
  G4PreCompoundAlpha(const G4PreCompoundAlpha &right): G4VPreCompoundIon(right) {}

  // destructor
  ~G4PreCompoundAlpha() {}

  // operators  
  const G4PreCompoundAlpha & operator=(const G4PreCompoundAlpha &right) {
    if (&right != this) this->G4VPreCompoundIon::operator=(right);
    return *this;
  };

  G4bool operator==(const G4PreCompoundAlpha &right) const
  { return G4VPreCompoundIon::operator==(right);}

  
  G4bool operator!=(const G4PreCompoundAlpha &right) const
  { return G4VPreCompoundIon::operator!=(right);}


    G4ReactionProduct * GetReactionProduct() const
	{
	    G4ReactionProduct * theReactionProduct =
                new G4ReactionProduct(G4Alpha::AlphaDefinition());
            theReactionProduct->SetMomentum(GetMomentum().vect());
            theReactionProduct->SetTotalEnergy(GetMomentum().e());
#ifdef pctest
            theReactionProduct->SetCreatorModel("G4PrecompoundModel");
#endif
            return theReactionProduct;
        }   
    
private:
    virtual G4double GetAlpha()
	{
	    G4double C = 0.0;
	    G4double aZ = GetZ() + GetRestZ();
	    if (aZ <= 30) {
		C = 0.10;
	    } else if (aZ <= 50) {
		C = 0.1 + -((aZ-50.)/20.)*0.02;
	    } else if (aZ < 70) {
		C = 0.08 + -((aZ-70.)/20.)*0.02;
	    } else {
		C = 0.06;
	    }
	    return 1.0+C;
	}

    virtual G4double GetBeta()
	{
	    return -GetCoulombBarrier();
	}

    virtual G4double FactorialFactor(const G4double N, const G4double P)
	{
	    return 
		(N-4.0)*(P-3.0)*(
		    (((N-3.0)*(P-2.0))/2.0) *(
			(((N-2.0)*(P-1.0))/3.0) *(
			    (((N-1.0)*P)/2.0)
			    )
			)
		    );
	}

    virtual G4double CoalescenceFactor(const G4double A)
	{
	    return 4096.0/(A*A*A);
	}    
private:

    G4AlphaCoulombBarrier theAlphaCoulombBarrier;

};

#endif
 

