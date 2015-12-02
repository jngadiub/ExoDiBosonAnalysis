#ifndef UTILITIES_H
#define UTILITIES_H

#include <map>
#include <vector>
#include "TLorentzVector.h"
#include <TFile.h>

class TH1;

namespace Utilities
{
   void gaussFit       ( TH1* hist );   
   void OverflowToLast ( TH1* hist );
   void CalculateAngles(TLorentzVector p4X  , 
                        TLorentzVector p4Z1 , TLorentzVector p4Z2 ,
                        TLorentzVector p4L11, TLorentzVector p4L12, 
			TLorentzVector p4L21, TLorentzVector p4L22,		    
		        double& costheta1, double& costheta2, double& costhetastar,   
		        double& phi	 , double& phi1     , double& phi2	  ,
		        double& phistar1 , double& phistar2 , double& phistar12   );
			
   bool areTLVequals( TLorentzVector v1, TLorentzVector v2 );
   TLorentzVector NuMomentum( float leptonPx, float leptonPy, float leptonPz, float leptonPt, float leptonE, float metPx, float metPy );
}

#endif // UTILITIES_H
