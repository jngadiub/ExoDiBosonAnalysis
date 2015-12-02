#include "include/Utilities.h"
//#include "include/MessageTools.h"

#include "core/include/SCycleBaseBase.h"
#include "core/include/SLogger.h"

#include "TAxis.h"
#include "TF1.h"
#include "TH1.h"
#include "TMath.h"

#include <iostream>

#include "include/EquationSolver.h"

//==========================================================================================================
void Utilities::gaussFit( TH1* hist){
 
  if (hist->GetEntries()<20)
     return;
     
  TAxis* xa = hist->GetXaxis();   
  TF1* myF = new TF1("myF","[0]*exp(-(x-[1])*(x-[1])/(2*[2]*[2]))", xa->GetXmin(), xa->GetXmax());    
      
  myF->SetParameter(0,0.75*hist->GetMaximum());
  myF->SetParameter(1,hist->GetMean());
  myF->SetParameter(2,0.5*hist->GetRMS());

  hist->Fit("myF","QR");
  
  float sigma = fabs(myF->GetParameter(2));
  float norm = myF->GetParameter(0);
  float mean = myF->GetParameter(1);
    
  for(int i = 0; i < 4; i++)
  {
     myF = new TF1("myF","[0]*exp(-(x-[1])*(x-[1])/(2*[2]*[2]))",(mean - 2*sigma),(mean + 2*sigma)); 
      
     myF->SetParameter(0,norm);
     myF->SetParameter(1,mean);
     myF->SetParameter(2,sigma);		
     myF->SetParName(0,"Norm");
     myF->SetParName(1,"Mean");
     myF->SetParName(2,"Sigma");

     hist->Fit("myF","QR");
	  
     sigma = fabs(myF->GetParameter(2));
     norm = myF->GetParameter(0);
     mean = myF->GetParameter(1);
  }
   
  double MeanError = myF->GetParError(1);
  double SigmaError = myF->GetParError(2);
   
  double ResolutionError = TMath::Sqrt( (SigmaError/mean)*(SigmaError/mean) + ((sigma*MeanError)/(mean*mean))*((sigma*MeanError)/(mean*mean)));
   
  //std::stringstream ss; 
  //ss.str(""); ss << "Sig " << sigma << " Mean " << mean << " Sig/Mean " << (sigma/mean) << " Error on Sig/Mean " << ResolutionError; 
  //STDLINE(ss.str(),ACPurple);
  
  return;
} 

//==========================================================================================================
void Utilities::OverflowToLast(TH1* hist)
{
  double binContent = hist->GetBinContent(hist->GetNbinsX()) + hist->GetBinContent(hist->GetNbinsX()+1);
  double binError = TMath::Sqrt(hist->GetBinError(hist->GetNbinsX())*hist->GetBinError(hist->GetNbinsX()) + hist->GetBinError(hist->GetNbinsX()+1)*hist->GetBinError(hist->GetNbinsX()+1));
  hist->SetBinContent(hist->GetNbinsX(),binContent);
  hist->SetBinContent(hist->GetNbinsX()+1,0.);

  binContent = hist->GetBinContent(0) + hist->GetBinContent(1);
  binError = TMath::Sqrt(hist->GetBinError(0)*hist->GetBinError(0) + hist->GetBinError(1)*hist->GetBinError(1));
  hist->SetBinContent(1,binContent);
  hist->SetBinContent(0,0.);
}

//==========================================================================================================
void Utilities:: CalculateAngles(TLorentzVector p4X  , 					    
		     		 TLorentzVector p4Z1 , TLorentzVector p4Z2 ,		     
		     		 TLorentzVector p4L11, TLorentzVector p4L12,		     
		     		 TLorentzVector p4L21, TLorentzVector p4L22,		     
		     	  	 double& costheta1, double& costheta2, double& costhetastar, 
		     		 double& phi	  , double& phi1     , double& phi2	   ,
		     		 double& phistar1 , double& phistar2 , double& phistar12   )
{
   double norm;

   TVector3 boostX = -(p4X.BoostVector());
   TLorentzVector p4Z1inXFrame( p4Z1 );
   TLorentzVector p4Z2inXFrame( p4Z2 );	   
   p4Z1inXFrame.Boost( boostX );
   p4Z2inXFrame.Boost( boostX );
   TVector3 theZ1X_p3 = TVector3( p4Z1inXFrame.X(), p4Z1inXFrame.Y(), p4Z1inXFrame.Z() );
   TVector3 theZ2X_p3 = TVector3( p4Z2inXFrame.X(), p4Z2inXFrame.Y(), p4Z2inXFrame.Z() );
   
   // calculate phi1, phi2, costhetastar...............
   phi1 = theZ1X_p3.Phi();
   phi2 = theZ2X_p3.Phi();   
   costhetastar  = theZ1X_p3.CosTheta();
   //TLorentzVector p4MothinXFrame( p4Moth );
   //p4MothinXFrame.Boost( boostX );
   //TVector3 p3MothinXFrame( p4MothinXFrame.X(), p4MothinXFrame.Y(),  p4MothinXFrame.Z() );
   //costhetastar = p3MothinXFrame.Dot(theZ1X_p3)/(p3MothinXFrame.Mag()*theZ1X_p3.Mag());

   //helicity angles................................
   TVector3 boostZ1 = -(p4Z1.BoostVector());
   TLorentzVector p4Z2Z1(p4Z2);
   p4Z2Z1.Boost(boostZ1);
   //find the decay axis
   /////TVector3 unitx_1 = -Hep3Vector(p4Z2Z1);
   TVector3 unitx_1( -p4Z2Z1.X(), -p4Z2Z1.Y(), -p4Z2Z1.Z() );
   norm = 1/(unitx_1.Mag());
   unitx_1*=norm;
   //boost daughters of z2
   TLorentzVector p4L21Z1(p4L21);
   TLorentzVector p4L22Z1(p4L22);
   p4L21Z1.Boost(boostZ1);
   p4L22Z1.Boost(boostZ1);
   //create z and y axes
   /////TVector3 unitz_1 = Hep3Vector(p4L21Z1).cross(Hep3Vector(p4L22Z1));
   TVector3 p4L21Z1_p3( p4L21Z1.X(), p4L21Z1.Y(), p4L21Z1.Z() );
   TVector3 p4L22Z1_p3( p4L22Z1.X(), p4L22Z1.Y(), p4L22Z1.Z() );
   TVector3 unitz_1 = p4L21Z1_p3.Cross( p4L22Z1_p3 );
   norm = 1/(unitz_1.Mag());
   unitz_1 *= norm;
   TVector3 unity_1 = unitz_1.Cross(unitx_1);

   //caculate theta1
   TLorentzVector p4L11Z1(p4L11);
   p4L11Z1.Boost(boostZ1);
   TVector3 p3L11( p4L11Z1.X(), p4L11Z1.Y(), p4L11Z1.Z() );
      
   TVector3 unitL11 = p3L11.Unit();
   double x_L11 = unitL11.Dot(unitx_1); double y_L11 = unitL11.Dot(unity_1); double z_L11 = unitL11.Dot(unitz_1);
   TVector3 L11_Z1frame(y_L11, z_L11, x_L11);
   costheta1 = L11_Z1frame.CosTheta();
   //std::cout << "theta1: " << L11_Z1frame.Theta() << std::endl;
   //////-----------------------old way of calculating phi---------------/////////
   phi = L11_Z1frame.Phi();

   //set axes for other system
   TVector3 boostZ2 = -(p4Z2.BoostVector());
   TLorentzVector p4Z1Z2(p4Z1);
   p4Z1Z2.Boost(boostZ2);
   TVector3 unitx_2( -p4Z1Z2.X(), -p4Z1Z2.Y(), -p4Z1Z2.Z() );
   norm = 1/(unitx_2.Mag());
   unitx_2*=norm;
   //boost daughters of z2
   TLorentzVector p4L11Z2(p4L11);
   TLorentzVector p4L12Z2(p4L12);
   p4L11Z2.Boost(boostZ2);
   p4L12Z2.Boost(boostZ2);
   TVector3 p4L11Z2_p3( p4L11Z2.X(), p4L11Z2.Y(), p4L11Z2.Z() );
   TVector3 p4L12Z2_p3( p4L12Z2.X(), p4L12Z2.Y(), p4L12Z2.Z() );
   TVector3 unitz_2 = p4L11Z2_p3.Cross( p4L12Z2_p3 );
   norm = 1/(unitz_2.Mag());
   unitz_2*=norm;
   TVector3 unity_2 = unitz_2.Cross(unitx_2);
   //calcuate theta2
   TLorentzVector p4L21Z2(p4L21);
   p4L21Z2.Boost(boostZ2);
   TVector3 p3L21( p4L21Z2.X(), p4L21Z2.Y(), p4L21Z2.Z() );
      
   TVector3 unitL21 = p3L21.Unit();
   double x_L21 = unitL21.Dot(unitx_2); double y_L21 = unitL21.Dot(unity_2); double z_L21 = unitL21.Dot(unitz_2);
   TVector3 L21_Z2frame(y_L21, z_L21, x_L21);
   costheta2 = L21_Z2frame.CosTheta();

   // calculate phi
   //calculating phi_n
   TLorentzVector n_p4Z1inXFrame( p4Z1 );
   TLorentzVector n_p4L11inXFrame( p4L11 );
   n_p4Z1inXFrame.Boost( boostX );
   n_p4L11inXFrame.Boost( boostX );	   
   TVector3 n_p4Z1inXFrame_unit = n_p4Z1inXFrame.Vect().Unit();
   TVector3 n_p4L11inXFrame_unit = n_p4L11inXFrame.Vect().Unit();  
   TVector3 n_unitz_1( n_p4Z1inXFrame_unit );
   //// y-axis is defined by neg lepton cross z-axis
   //// the subtle part is here...
   //////////TVector3 n_unity_1 = n_p4L11inXFrame_unit.Cross( n_unitz_1 );
   TVector3 n_unity_1 = n_unitz_1.Cross( n_p4L11inXFrame_unit );
   TVector3 n_unitx_1 = n_unity_1.Cross( n_unitz_1 );

   TLorentzVector n_p4L21inXFrame( p4L21 );
   n_p4L21inXFrame.Boost( boostX );
   TVector3 n_p4L21inXFrame_unit = n_p4L21inXFrame.Vect().Unit();
   //rotate into other plane
   TVector3 n_p4L21inXFrame_unitprime( n_p4L21inXFrame_unit.Dot(n_unitx_1), n_p4L21inXFrame_unit.Dot(n_unity_1), n_p4L21inXFrame_unit.Dot(n_unitz_1) );

   ///////-----------------new way of calculating phi-----------------///////
   //double phi_n =  n_p4L21inXFrame_unitprime.Phi();
   /// and then calculate phistar1
   TVector3 n_p4PartoninXFrame_unit( 0.0, 0.0, 1.0 );
   TVector3 n_p4PartoninXFrame_unitprime( n_p4PartoninXFrame_unit.Dot(n_unitx_1), n_p4PartoninXFrame_unit.Dot(n_unity_1), n_p4PartoninXFrame_unit.Dot(n_unitz_1) );
   // negative sign is for arrow convention in paper
   phistar1 = (n_p4PartoninXFrame_unitprime.Phi());

   // and the calculate phistar2
   TLorentzVector n_p4Z2inXFrame( p4Z2 );
   n_p4Z2inXFrame.Boost( boostX );
   TVector3 n_p4Z2inXFrame_unit = n_p4Z2inXFrame.Vect().Unit();
   ///////TLorentzVector n_p4L21inXFrame( p4L21 );
   //////n_p4L21inXFrame.Boost( boostX );	 
   ////TVector3 n_p4L21inXFrame_unit = n_p4L21inXFrame.Vect().Unit();  
   TVector3 n_unitz_2( n_p4Z2inXFrame_unit );
   //// y-axis is defined by neg lepton cross z-axis
   //// the subtle part is here...
   //////TVector3 n_unity_2 = n_p4L21inXFrame_unit.Cross( n_unitz_2 );
   TVector3 n_unity_2 = n_unitz_2.Cross( n_p4L21inXFrame_unit );
   TVector3 n_unitx_2 = n_unity_2.Cross( n_unitz_2 );
   TVector3 n_p4PartoninZ2PlaneFrame_unitprime( n_p4PartoninXFrame_unit.Dot(n_unitx_2), n_p4PartoninXFrame_unit.Dot(n_unity_2), n_p4PartoninXFrame_unit.Dot(n_unitz_2) );
   phistar2 = (n_p4PartoninZ2PlaneFrame_unitprime.Phi());

   double phistar12_0 = phistar1 + phistar2;
   if (phistar12_0 > TMath::Pi()) phistar12 = phistar12_0 - 2*TMath::Pi();
   else if (phistar12_0 < (-1.)*TMath::Pi()) phistar12 = phistar12_0 + 2*TMath::Pi();
   else phistar12 = phistar12_0;
}


//==========================================================================================================
bool Utilities::areTLVequals( TLorentzVector v1, TLorentzVector v2 ){

   //std::cout << "Utilities!" << std::endl;
   if( v1.Pt() == v2.Pt() && v1.Eta() == v2.Eta() && v1.Phi() == v2.Phi() && v1.E() == v2.E() ) return true;
   else return false;
}

//==========================================================================================================
TLorentzVector Utilities::NuMomentum( float leptonPx, float leptonPy, float leptonPz, float leptonPt, float leptonE, float metPx, float metPy ){

  double  mW = 80.399;

  TLorentzVector result;

  //  double Wmt = sqrt(pow(Lepton.et()+MET.pt(),2) - pow(Lepton.px()+metPx,2) - pow(leptonPy+metPy,2) );

  double MisET2 = (metPx * metPx + metPy * metPy);
  double mu = (mW * mW) / 2 + metPx * leptonPx + metPy * leptonPy;
  double a  = (mu * leptonPz) / (leptonE * leptonE - leptonPz * leptonPz);
  double a2 = TMath::Power(a, 2);
  double b  = (TMath::Power(leptonE, 2.) * (MisET2) - TMath::Power(mu, 2.)) / (TMath::Power(leptonE, 2) - TMath::Power(leptonPz, 2));
  double pz1(0), pz2(0), pznu(0);
  int nNuSol(0);

  TLorentzVector p4nu_rec;
  TLorentzVector p4W_rec;
  TLorentzVector p4b_rec;
  TLorentzVector p4Top_rec;
  TLorentzVector p4lep_rec;

  p4lep_rec.SetPxPyPzE(leptonPx, leptonPy, leptonPz, leptonE);

  TLorentzVector p40_rec(0, 0, 0, 0);

  if (a2 - b > 0 )
    {
      //if(!usePositiveDeltaSolutions_)
      //  {
      //  result.push_back(p40_rec);
      //  return result;
      //  }
      double root = sqrt(a2 - b);
      pz1 = a + root;
      pz2 = a - root;
      nNuSol = 2;

      //    if(usePzPlusSolutions_)pznu = pz1;
      //    if(usePzMinusSolutions_)pznu = pz2;
      //if(usePzAbsValMinimumSolutions_){
      pznu = pz1;
      if (fabs(pz1) > fabs(pz2)) pznu = pz2;
      //}


      double Enu = sqrt(MisET2 + pznu * pznu);

      p4nu_rec.SetPxPyPzE(metPx, metPy, pznu, Enu);

      //    result =.push_back(p4nu_rec);
      result = p4nu_rec;

    }
  else
    {

      // if(!useNegativeDeltaSolutions_){
      //result.push_back(p40_rec);
      //  return result;
      //    }
      //    double xprime = sqrt(mW;


      double ptlep = leptonPt, pxlep = leptonPx, pylep = leptonPy, metpx = metPx, metpy = metPy;

      double EquationA = 1;
      double EquationB = -3 * pylep * mW / (ptlep);
      double EquationC = mW * mW * (2 * pylep * pylep) / (ptlep * ptlep) + mW * mW - 4 * pxlep * pxlep * pxlep * metpx / (ptlep * ptlep) - 4 * pxlep * pxlep * pylep * metpy / (ptlep * ptlep);
      double EquationD = 4 * pxlep * pxlep * mW * metpy / (ptlep) - pylep * mW * mW * mW / ptlep;

      std::vector<long double> solutions = EquationSolve<long double>((long double)EquationA, (long double)EquationB, (long double)EquationC, (long double)EquationD);

      std::vector<long double> solutions2 = EquationSolve<long double>((long double)EquationA, -(long double)EquationB, (long double)EquationC, -(long double)EquationD);


      double deltaMin = 14000 * 14000;
      double zeroValue = -mW * mW / (4 * pxlep);
      double minPx = 0;
      double minPy = 0;

      //    std::cout<<"a "<<EquationA << " b " << EquationB  <<" c "<< EquationC <<" d "<< EquationD << std::endl;

      //  if(usePxMinusSolutions_){
      for ( int i = 0; i < (int)solutions.size(); ++i)
        {
	  if (solutions[i] < 0 ) continue;
	  double p_x = (solutions[i] * solutions[i] - mW * mW) / (4 * pxlep);
	  double p_y = ( mW * mW * pylep + 2 * pxlep * pylep * p_x - mW * ptlep * solutions[i]) / (2 * pxlep * pxlep);
	  double Delta2 = (p_x - metpx) * (p_x - metpx) + (p_y - metpy) * (p_y - metpy);

	  //      std:://cout<<"intermediate solution1 met x "<<metpx << " min px " << p_x  <<" met y "<<metpy <<" min py "<< p_y << std::endl;

	  if (Delta2 < deltaMin && Delta2 > 0)
            {
	      deltaMin = Delta2;
	      minPx = p_x;
	      minPy = p_y;
            }
	  //     std:://cout<<"solution1 met x "<<metpx << " min px " << minPx  <<" met y "<<metpy <<" min py "<< minPy << std::endl;
        }

      //    }

      //if(usePxPlusSolutions_){
      for ( int i = 0; i < (int)solutions2.size(); ++i)
        {
	  if (solutions2[i] < 0 ) continue;
	  double p_x = (solutions2[i] * solutions2[i] - mW * mW) / (4 * pxlep);
	  double p_y = ( mW * mW * pylep + 2 * pxlep * pylep * p_x + mW * ptlep * solutions2[i]) / (2 * pxlep * pxlep);
	  double Delta2 = (p_x - metpx) * (p_x - metpx) + (p_y - metpy) * (p_y - metpy);
	  //  std:://cout<<"intermediate solution2 met x "<<metpx << " min px " << minPx  <<" met y "<<metpy <<" min py "<< minPy << std::endl;
	  if (Delta2 < deltaMin && Delta2 > 0)
            {
	      deltaMin = Delta2;
	      minPx = p_x;
	      minPy = p_y;
            }
	  //  std:://cout<<"solution2 met x "<<metpx << " min px " << minPx  <<" mult;
	}
      //}

      double pyZeroValue = ( mW * mW * pxlep + 2 * pxlep * pylep * zeroValue);
      double delta2ZeroValue = (zeroValue - metpx) * (zeroValue - metpx) + (pyZeroValue - metpy) * (pyZeroValue - metpy);

      if (deltaMin == 14000 * 14000)return result;
      //    else std:://cout << " test " << std::endl;

      if (delta2ZeroValue < deltaMin)
        {
	  deltaMin = delta2ZeroValue;
	  minPx = zeroValue;
	  minPy = pyZeroValue;
        }

      //    std:://cout<<" MtW2 from min py and min px "<< sqrt((minPy*minPy+minPx*minPx))*ptlep*2 -2*(pxlep*minPx + pylep*minPy)  <<std::endl;
      ///    ////Y part

      double mu_Minimum = (mW * mW) / 2 + minPx * pxlep + minPy * pylep;
      double a_Minimum  = (mu_Minimum * leptonPz) / (leptonE * leptonE - leptonPz * leptonPz);
      pznu = a_Minimum;

      //if(!useMetForNegativeSolutions_){
      double Enu = sqrt(minPx * minPx + minPy * minPy + pznu * pznu);
      p4nu_rec.SetPxPyPzE(minPx, minPy, pznu , Enu);

      //    }
      //    else{
      //      pznu = a;
      //      double Enu = sqrt(metpx*metpx+metpy*metpy + pznu*pznu);
      //      p4nu_rec.SetPxPyPzE(metpx, metpy, pznu , Enu);
      //    }

      //      result.push_back(p4nu_rec);
      result = p4nu_rec;
    }
  return result;
}

