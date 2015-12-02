#include <iostream>
#include "TMath.h"

double data[4], dataerr[4], MC[4], TTbar[4], Wjets[4], MCerr[4];

void InitData( double* mydata, double* mydataerr, double* myMC, double* myTTbar, double* myWjets, double* myMCerr ){

   for( int i = 0; i < 4; ++i ){
      data[i] = mydata[i];
      dataerr[i] = mydataerr[i];
      MC[i] = myMC[i];
      TTbar[i] = myTTbar[i];
      Wjets[i] = myWjets[i];
      MCerr[i] = myMCerr[i];
   }

}

void PrintData( void ){

   for( int i = 0; i < 4; ++i ){
       std::cout << data[i] << " +/- " << dataerr[i] << std::endl;
       std::cout << MC[i] << std::endl;
   }
   
}

Double_t func(	double ttbar, double wjets, double bkg, double *par )
{
	double SF_TTbar = par[0];
	double SF_Wjets = par[1];

	double value = ttbar*SF_TTbar + wjets*SF_Wjets + bkg;
	
 	return value;
}

void fcn(int &npar, double *gin, double &f, double *par, int iflag)
{
	// energy range for the fit, in bins
	//const int fit_min = 35;
	//const int fit_max = 55;

	const int fit_min = 0; // good fit
	const int fit_max = 4;
	
	int i;
	
	double chisq = 0;
	double delta;
	for (i=fit_min; i<fit_max; i++) {
   
		delta=(data[i]-func(TTbar[i],Wjets[i],MC[i],par));
		
		if(data[i]!=0){ 
			chisq += delta*delta/TMath::Sqrt(dataerr[i]*dataerr[i]+MCerr[i]*MCerr[i]);
		}
	}
	f = chisq;
	
}


