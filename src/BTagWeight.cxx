#include "include/BTagWeight.h"
#include "include/JetCandidate.h"

#include "TFile.h"
#include "TH2D.h"

#include <iostream>
#include <cmath>
#include <stdlib.h> 

//==============================================================================================
BTagWeight::BTagWeight( void )
   : scale_b_(0)
   , scale_light_(0)
{

}

//==============================================================================================
BTagWeight::~BTagWeight( void ){

}

//==============================================================================================
void BTagWeight::initBTagWeights(const std::string& eff4vetoFile, const std::string& eff4fatjetFile, const std::string& eff4subjetFile ){

   eff4vetoFilename_   = eff4vetoFile  ;
   eff4fatjetFilename_ = eff4fatjetFile;
   eff4subjetFilename_ = eff4subjetFile;
   
}

//==============================================================================================
void BTagWeight::getEff( float pt, float eta, int flavor , std::string which ){

   double eff   = 1.0;
   double eff_e = 0.0;

   std::string HistNameN;
   std::string HistNameD;

   flavor = abs(flavor);
   eta = fabs(eta);

   if( flavor == 1 || flavor == 2 || flavor == 3 || flavor == 21 ){ 
      HistNameN="h2_BTaggingEff_Num_udsg_L";
      HistNameD="h2_BTaggingEff_Denom_udsg_L";
   }
   else if( flavor == 4 ){
       HistNameN = "h2_BTaggingEff_Num_c_L";
       HistNameD = "h2_BTaggingEff_Denom_c_L";
   }
   else if( flavor == 5 ){
      HistNameN = "h2_BTaggingEff_Num_b_L";
      HistNameD = "h2_BTaggingEff_Denom_b_L";
   }
   else{
      HistNameN = "h2_BTaggingEff_Num_udsg_L";
      HistNameD = "h2_BTaggingEff_Denom_udsg_L";
   }
    
   std::string EffmapFilename_;       
   
   if( which == "veto" ){
      EffmapFilename_ = eff4vetoFilename_;
      if( flavor == 1 || flavor == 2 || flavor == 3 || flavor == 21 ){ 
         HistNameN="numerator_udsg";
         HistNameD="denominator_udsg";
      }
      else if( flavor == 4 ){
          HistNameN = "numerator_c";
          HistNameD = "denominator_c";
      }
      else if( flavor == 5 ){
         HistNameN = "numerator_b";
         HistNameD = "denominator_b";
      }
      else{
         HistNameN = "numerator_udsg";
         HistNameD = "denominator_udsg";
      }                
   }
   else if( which == "fatjet" ) { 
      EffmapFilename_ = eff4fatjetFilename_;    
   }
   else if( which == "subjet" )  {
      EffmapFilename_ = eff4subjetFilename_;          
   }
                 
   TFile file(EffmapFilename_.c_str());
   TH2D* hN = (TH2D*)file.Get(HistNameN.c_str());
   TH2D* hD = (TH2D*)file.Get(HistNameD.c_str());
   
   int nbinspt = hN->GetNbinsX();
   int nbinseta = hN->GetNbinsY();
   
   double* ptmin = new double [nbinspt+1];
   double* etamin = new double [nbinseta+1];
   
   for( int b = 0; b < nbinspt; ++b ){
       ptmin[b] = hN->GetXaxis()->GetBinLowEdge(b+1);
   }
   ptmin[nbinspt] = hN->GetXaxis()->GetBinUpEdge(nbinspt);
   
   for( int b = 0; b < nbinseta; ++b ){
     etamin[b] = hN->GetYaxis()->GetBinLowEdge(b+1);
   }
   etamin[nbinseta] = hN->GetYaxis()->GetBinUpEdge(nbinseta);
   
   TH2D* hE = new TH2D("tmp","tmp",nbinspt, ptmin, nbinseta, etamin);
				   
   hE->Divide(hN,hD,1,1,"B");	
   //hE->Sumw2();			   

   double binx = hE->GetXaxis()->FindBin(pt);
   double biny = hE->GetYaxis()->FindBin(eta);

   eff   = hE->GetBinContent(binx,biny);
   eff_e = hE->GetBinError(binx,biny);
 
   //std::cout << which  << " --> eff "<< eff << " err " << eff_e << std::endl;
   
   jetEff.push_back(eff);
   jetEff_e.push_back(eff_e);

   delete hE;
   delete hN;
   delete hD;
   delete [] ptmin;
   delete [] etamin;
                       
}

//==============================================================================================
void BTagWeight::getSFL( float pt, float eta, int flavor ){

   double    SF           = 1.0;
   const int nbins        = 16;
   double    ptmin[nbins] = {20, 30, 40, 50, 60, 70, 80, 100, 120, 160, 210, 260, 320, 400, 500, 600};
   double    ptmax[nbins] = {30, 40, 50, 60, 70, 80,100, 120, 160, 210, 260, 320, 400, 500, 600, 800};
   double    SF_e_up   = 0.;
   double    SF_e_down = 0.;

   flavor = abs(flavor);
   if( flavor == 4 || flavor == 5){
      if( fabs(eta) > 2.4 ){
         jetSF.push_back(SF);
         jetSF_e_up.push_back(SF_e_up);
         jetSF_e_down.push_back(SF_e_down);
         return; 
      }
      if( pt < 20 ){
         SF = 0.997942*((1.+(0.00923753*20))/(1.+(0.0096119*20)));
         SF_e_up = SF_e_down = 0.033299*2;
      }
      else if( pt > 800 ){
         SF = 0.997942*((1.+(0.00923753*800))/(1.+(0.0096119*800)));
         SF_e_up = SF_e_down = 0.0350099*2;
      }
      else{//20 < pt < 800
 	SF = 0.997942*((1.+(0.00923753*pt))/(1.+(0.0096119*pt)));
 	double SFb_error[nbins] = {
 	   0.033299,
 	   0.0146768,
 	   0.013803,
 	   0.0170145,
 	   0.0166976,
 	   0.0137879,
 	   0.0149072,
 	   0.0153068,
 	   0.0133077,
 	   0.0123737,
 	   0.0157152,
 	   0.0175161,
 	   0.0209241,
 	   0.0278605,
 	   0.0346928,
 	   0.0350099 };
        for( int i = 0; i < nbins; i++ ){
           if( pt >= ptmin[i] && pt <= ptmax[i] ) SF_e_up=SF_e_down=SFb_error[i];
        }
      }//end of 20 < pt < 800 GeV
      if( flavor == 4 ){//SFc = SFb with twice the quoted uncertainty
         SF_e_up = 2*SF_e_up;
         SF_e_down = 2*SF_e_down;
      }
   }//end of b,c
   else{ // light flavor
      double SF_low     ;
      double SF_high    ;
      double ptmax      ;
      bool   overmax = 0;
      if( fabs(eta) < 0.5 ){
         ptmax = 1000;
         if( pt > ptmax ){ pt = ptmax; overmax = 1; }
         SF      = ((1.01177 +(0.0023066*pt)) +(-4.56052e-06*(pt*pt)))+(2.57917e-09*(pt*(pt*pt)));
         SF_low  = ((0.977761+(0.00170704*pt))+(-3.2197e-06*(pt*pt))) +(1.78139e-09*(pt*(pt*pt)));
         SF_high = ((1.04582 +(0.00290226*pt))+(-5.89124e-06*(pt*pt)))+(3.37128e-09*(pt*(pt*pt)));
      }
      else if( fabs(eta) > 0.5 && fabs(eta) < 1.0 ){
         ptmax = 1000;
         if( pt > ptmax ){ pt = ptmax; overmax = 1;}
         SF      = ((0.975966+(0.00196354*pt))+(-3.83768e-06*(pt*pt)))+(2.17466e-09*(pt*(pt*pt)));
         SF_low  = ((0.945135+(0.00146006*pt))+(-2.70048e-06*(pt*pt)))+( 1.4883e-09*(pt*(pt*pt)));
         SF_high = ((1.00683 +(0.00246404*pt))+(-4.96729e-06*(pt*pt)))+(2.85697e-09*(pt*(pt*pt)));
      }
      else if( fabs(eta) > 1.0 && fabs(eta) < 1.5 ){
         ptmax = 850;
         if( pt > ptmax ){ pt = ptmax; overmax = 1;}
         SF      = ((0.93821 +(0.00180935*pt))+(-3.86937e-06*(pt*pt)))+(2.43222e-09*(pt*(pt*pt)));
         SF_low  = ((0.911657+(0.00142008*pt))+(-2.87569e-06*(pt*pt)))+(1.76619e-09*(pt*(pt*pt)));
         SF_high = ((0.964787+(0.00219574*pt))+(-4.85552e-06*(pt*pt)))+(3.09457e-09*(pt*(pt*pt)));
      }
      else if( fabs(eta) > 1.5 && fabs(eta) < 2.4 ){
         SF      = ((1.00022+(0.0010998*pt))+(-3.10672e-06*(pt*pt)))+(2.35006e-09*(pt*(pt*pt)));
         SF_low  = ((0.970045+(0.000862284*pt))+(-2.31714e-06*(pt*pt)))+(1.68866e-09*(pt*(pt*pt)));
         SF_high = ((1.03039+(0.0013358*pt))+(-3.89284e-06*(pt*pt)))+(3.01155e-09*(pt*(pt*pt)));      
      }
      else{
         jetSF.push_back(SF);
         jetSF_e_up.push_back(SF_e_up);
         jetSF_e_down.push_back(SF_e_down);
         return;
      }
      
      SF_e_up = SF_high - SF;
      SF_e_down = SF - SF_low;

      if( overmax == 1 ){ SF_e_up = 2*SF_e_up; SF_e_down = 2*SF_e_down;}

   }//endl of light flavor

   jetSF.push_back(SF);
   jetSF_e_up.push_back(SF_e_up);
   jetSF_e_down.push_back(SF_e_down);

   return;
}

//==============================================================================================
void BTagWeight::getSFM( float pt, float eta, int flavor ){

   double    SF           = 1.0;
   const int nbins        = 16;
   double    ptmin[nbins] = {20, 30, 40, 50, 60, 70, 80, 100, 120, 160, 210, 260, 320, 400, 500, 600};
   double    ptmax[nbins] = {30, 40, 50, 60, 70, 80,100, 120, 160, 210, 260, 320, 400, 500, 600, 800};
   double    SF_e_up   = 0.;
   double    SF_e_down = 0.;

   flavor = abs(flavor);
   if( flavor == 4 || flavor == 5){
      if( fabs(eta) > 2.4 ){
         jetSF.push_back(SF);
         jetSF_e_up.push_back(SF_e_up);
         jetSF_e_down.push_back(SF_e_down);
         return; 
      }
      if( pt < 20 ){
         SF = (0.938887+(0.00017124*20.))+(-2.76366e-07*(20.*20.));
         SF_e_up = SF_e_down = 0.0415707*2;
      }
      else if( pt > 800 ){
         SF = (0.938887+(0.00017124*800.))+(-2.76366e-07*(800.*800.));
         SF_e_up = SF_e_down = 0.0596716*2;
      }
      else{//20 < pt < 800
 	SF = (0.938887+(0.00017124*pt))+(-2.76366e-07*(pt*pt));
 	double SFb_error[nbins] = {
 	  0.0415707,
 	  0.0204209,
 	  0.0223227,
 	  0.0206655,
 	  0.0199325,
 	  0.0174121,
 	  0.0202332,
 	  0.0182446,
 	  0.0159777,
 	  0.0218531,
 	  0.0204688,
 	  0.0265191,
 	  0.0313175,
 	  0.0415417,
 	  0.0740446,
 	  0.0596716 };
        for( int i = 0; i < nbins; i++ ){
           if( pt >= ptmin[i] && pt <= ptmax[i] ) SF_e_up=SF_e_down=SFb_error[i];
        }
      }//end of 20 < pt < 800 GeV
      if( flavor == 4 ){//SFc = SFb with twice the quoted uncertainty
         SF_e_up = 2*SF_e_up;
         SF_e_down = 2*SF_e_down;
      }
   }//end of b,c
   else{ // light flavor
      double SF_low     ;
      double SF_high    ;
      double ptmax      ;
      bool   overmax = 0;
      if( fabs(eta) < 0.8 ){
         ptmax = 1000;
         if( pt > ptmax ){ pt = ptmax; overmax = 1; }
         SF      = ((1.07541+(0.00231827*pt))+(-4.74249e-06*(pt*pt)))+(2.70862e-09*(pt*(pt*pt)));
         SF_low  = ((0.964527+(0.00149055*pt))+(-2.78338e-06*(pt*pt)))+(1.51771e-09*(pt*(pt*pt)));
         SF_high = ((1.18638+(0.00314148*pt))+(-6.68993e-06*(pt*pt)))+(3.89288e-09*(pt*(pt*pt)));
      }
      else if( fabs(eta) > 0.8 && fabs(eta) < 1.6 ){
         ptmax = 1000;
         if( pt > ptmax ){ pt = ptmax; overmax = 1;}
         SF      = ((1.05613+(0.00114031*pt))+(-2.56066e-06*(pt*pt)))+(1.67792e-09*(pt*(pt*pt)));
         SF_low  = ((0.946051+(0.000759584*pt))+(-1.52491e-06*(pt*pt)))+(9.65822e-10*(pt*(pt*pt)));
         SF_high = ((1.16624+(0.00151884*pt))+(-3.59041e-06*(pt*pt)))+(2.38681e-09*(pt*(pt*pt)));
      }
      else if( fabs(eta) > 1.6 && fabs(eta) < 2.4 ){
         ptmax = 850;
         if( pt > ptmax ){ pt = ptmax; overmax = 1;}
         SF      = ((1.05625+(0.000487231*pt))+(-2.22792e-06*(pt*pt)))+(1.70262e-09*(pt*(pt*pt)));
         SF_low  = ((0.956736+(0.000280197*pt))+(-1.42739e-06*(pt*pt)))+(1.0085e-09*(pt*(pt*pt)));
         SF_high = ((1.15575+(0.000693344*pt))+(-3.02661e-06*(pt*pt)))+(2.39752e-09*(pt*(pt*pt)));
      }
      else{
         jetSF.push_back(SF);
         jetSF_e_up.push_back(SF_e_up);
         jetSF_e_down.push_back(SF_e_down);
         return;
      }
      
      SF_e_up = SF_high - SF;
      SF_e_down = SF - SF_low;

      if( overmax == 1 ){ SF_e_up = 2*SF_e_up; SF_e_down = 2*SF_e_down;}

   }//endl of light flavor

   jetSF.push_back(SF);
   jetSF_e_up.push_back(SF_e_up);
   jetSF_e_down.push_back(SF_e_down);

   return;
}

//==============================================================================================
double BTagWeight::getBTagWeight( std::vector<JetCandidate> jets, std::string which ){

   jetEff.clear();
   jetEff_e.clear();
   jetSF.clear();
   jetSF_e_up.clear();
   jetSF_e_down.clear(); 
   
   double weight    = 1.0;
   double mcTag     = 1.0;
   double dataTag   = 1.0;
   double mcNoTag   = 1.0;
   double dataNoTag = 1.0;

   double CSVwp;
   if( which == "veto" ) CSVwp = 0.890;
   else CSVwp = 0.605;
   
   //std::cout << which << " wp " << jets.size() << std::endl;

   for( unsigned int j = 0; j < jets.size(); ++j ){
   
      //reading eff and SF for each jet and save into vector
      getEff(jets[j].p4.Pt(),jets[j].p4.Eta(),jets[j].flavor, which);
      if( which == "veto" ) getSFM(jets[j].p4.Pt(),jets[j].p4.Eta(),jets[j].flavor);
      else getSFL(jets[j].p4.Pt(),jets[j].p4.Eta(),jets[j].flavor); 
           
   }     
     
   
   for( unsigned int j = 0; j < jets.size(); ++j ){

      //std::cout << "jet " << j << " - pt " << jets[j].p4.Pt() << " - eta " << jets[j].p4.Eta() << " - flavor " << jets[j].flavor << " - eff " << jetEff[j];
      //std::cout << " sf " << jetSF[j] << " - err eff " << jetEff_e[j] << std::endl;            
      	    
      if( jets[j].csv > CSVwp ){
      
         if( jetEff[j] == 0 ) jetEff[j] = 1.;
	 
         mcTag *= jetEff[j];
	 dataTag *= jetEff[j]*jetSF[j];
	 
      }
      else{
         
	 if( jetEff[j] == 1 ) jetEff[j] = 0.;
	 
	 mcNoTag *= (1-jetEff[j]);
	 dataNoTag *= (1-jetEff[j]*jetSF[j]);
	       
      }
            
   }

   weight = (dataNoTag*dataTag)/(mcNoTag*mcTag);
   //std::cout << "   --------> " << weight << std::endl;
   
   return weight;  
                
}



//==============================================================================================
double BTagWeight::getBTagWeight( JetCandidate jet, std::string which ){

   std::vector<JetCandidate> jets; jets.push_back(jet);
   
   jetEff.clear();
   jetEff_e.clear();
   jetSF.clear();
   jetSF_e_up.clear();
   jetSF_e_down.clear(); 
   
   double weight    = 1.0;
   double mcTag     = 1.0;
   double dataTag   = 1.0;
   double mcNoTag   = 1.0;
   double dataNoTag = 1.0;

   double CSVwp;
   if( which == "veto" ) CSVwp = 0.890;
   else CSVwp = 0.605;

   //std::cout << which << " wp " << CSVwp << std::endl;
   
   for( unsigned int j = 0; j < jets.size(); ++j ){
   
      //reading eff and SF for each jet and save into vector
      getEff(jets[j].p4.Pt(),jets[j].p4.Eta(),jets[j].flavor, which);
      if( which == "veto" ) getSFM(jets[j].p4.Pt(),jets[j].p4.Eta(),jets[j].flavor);
      else getSFL(jets[j].p4.Pt(),jets[j].p4.Eta(),jets[j].flavor); 
           
   }    
         
   for( unsigned int j = 0; j < jets.size(); ++j ){
      
      //std::cout << "jet " << j << " - pt " << jets[j].p4.Pt() << " - eta " << jets[j].p4.Eta() << " - flavor " << jets[j].flavor << " - eff " << jetEff[j];
      //std::cout << " sf " << jetSF[j] << " - err eff " << jetEff_e[j] << std::endl;
            
      if( jets[j].csv > CSVwp ){
      
         if( jetEff[j] == 0 ) jetEff[j] = 1.;
	 
         mcTag *= jetEff[j];
	 dataTag *= jetEff[j]*jetSF[j];
	 
      }
      else{
         
	 if( jetEff[j] == 1 ) jetEff[j] = 0.;
	 
	 mcNoTag *= (1-jetEff[j]);
	 dataNoTag *= (1-jetEff[j]*jetSF[j]);
      
      }
            
   }

   weight = (dataNoTag*dataTag)/(mcNoTag*mcTag);
   
   return weight;  
                
}

//==============================================================================================
double BTagWeight::getBTagSFWeightUp( std::vector<JetCandidate> jets, std::string which ){

   jetEff.clear();
   jetEff_e.clear();
   jetSF.clear();
   jetSF_e_up.clear();
   jetSF_e_down.clear(); 
   
   double weight    = 1.0;
   double weightup  = 1.0;
   double mcTag     = 1.0;
   double dataTag   = 1.0;
   double mcNoTag   = 1.0;
   double dataNoTag = 1.0;
   double errTag    = 0;
   double errNoTag  = 0;
   double SFerr     = 0;
   double werr      = 0;

   double CSVwp;
   if( which == "veto" ) CSVwp = 0.890;
   else CSVwp = 0.605;
   
   for( unsigned int j = 0; j < jets.size(); ++j ){
   
      //reading eff and SF for each jet and save into vector
      getEff(jets[j].p4.Pt(),jets[j].p4.Eta(),jets[j].flavor, which);
      if( which == "veto" ) getSFM(jets[j].p4.Pt(),jets[j].p4.Eta(),jets[j].flavor);
      else getSFL(jets[j].p4.Pt(),jets[j].p4.Eta(),jets[j].flavor); 
           
   }     
      
   for( unsigned int j = 0; j < jets.size(); ++j ){      
      
      SFerr = jetSF_e_up[j];

      //std::cout << "jet " << j << " - pt " << jets[j].p4.Pt() << " - eta " << jets[j].p4.Eta() << " - flavor " << jets[j].flavor << " - eff " << jetEff[j];
      //std::cout << " sf up " << jetSF[j] + SFerr << std::endl;
            
      if( jets[j].csv > CSVwp ){
      
         mcTag *= jetEff[j];
	 //dataTag *= jetEff[j]*jetSF[j];
	 dataTag *= jetEff[j]*(jetSF[j]+SFerr);
	 
	 errTag += (SFerr/jetSF[j])*(SFerr/jetSF[j]);
	 
      }
      else{
         
	 mcNoTag *= (1-jetEff[j]);
	 //dataNoTag *= (1-jetEff[j]*jetSF[j]);
	 dataNoTag *= (1-jetEff[j]*(jetSF[j]+SFerr));
	 
	 errNoTag += ((-jetEff[j]*SFerr)/(1-jetEff[j]*jetSF[j]))*((-jetEff[j]*SFerr)/(1-jetEff[j]*jetSF[j]));
      
      }      

   }

   weight = (dataNoTag*dataTag)/(mcNoTag*mcTag);
   //std::cout << "   --------> " << weight << std::endl;
   //werr = TMath::Sqrt(errTag+errNoTag)*weight;
   //weightup = weight+werr;
   
   //std::cout << "########### which " << which << " weight " << weightup << " err " << werr << std::endl;
  
   //return weightup;
   return weight;
      
}

//==============================================================================================
double BTagWeight::getBTagSFWeightDown( std::vector<JetCandidate> jets, std::string which ){

   jetEff.clear();
   jetEff_e.clear();
   jetSF.clear();
   jetSF_e_up.clear();
   jetSF_e_down.clear(); 
   
   double weight     = 1.0;
   double weightdown = 1.0;
   double mcTag      = 1.0;
   double dataTag    = 1.0;
   double mcNoTag    = 1.0;
   double dataNoTag  = 1.0;
   double errTag     = 0;
   double errNoTag   = 0;
   double SFerr      = 0;
   double werr       = 0;

   double CSVwp;
   if( which == "veto" ) CSVwp = 0.890;
   else CSVwp = 0.605;
   
   for( unsigned int j = 0; j < jets.size(); ++j ){
   
      //reading eff and SF for each jet and save into vector
      getEff(jets[j].p4.Pt(),jets[j].p4.Eta(),jets[j].flavor, which);
      if( which == "veto" ) getSFM(jets[j].p4.Pt(),jets[j].p4.Eta(),jets[j].flavor);
      else getSFL(jets[j].p4.Pt(),jets[j].p4.Eta(),jets[j].flavor); 
           
   }     
      
   for( unsigned int j = 0; j < jets.size(); ++j ){      
      
      SFerr = jetSF_e_down[j];

      //std::cout << "jet " << j << " - pt " << jets[j].p4.Pt() << " - eta " << jets[j].p4.Eta() << " - flavor " << jets[j].flavor << " - eff " << jetEff[j];
      //std::cout << " sf down " << jetSF[j] - SFerr << std::endl;
            
      if( jets[j].csv > CSVwp ){
      
         mcTag *= jetEff[j];
	 //dataTag *= jetEff[j]*jetSF[j];
	 dataTag *= jetEff[j]*(jetSF[j]-SFerr);
	 
	 errTag += (SFerr/jetSF[j])*(SFerr/jetSF[j]);
	 
      }
      else{
         
	 mcNoTag *= (1-jetEff[j]);
	 //dataNoTag *= (1-jetEff[j]*jetSF[j]);
	 dataNoTag *= (1-jetEff[j]*(jetSF[j]-SFerr));
	 
	 errNoTag += ((-jetEff[j]*SFerr)/(1-jetEff[j]*jetSF[j]))*((-jetEff[j]*SFerr)/(1-jetEff[j]*jetSF[j]));
      
      }      

   }

   weight = (dataNoTag*dataTag)/(mcNoTag*mcTag);
   //std::cout << "   --------> " << weight << std::endl;
   //werr = TMath::Sqrt(errTag+errNoTag)*weight;
   //weightdown = (weight-werr) > 0 ? weight-werr:0;
   
   //std::cout << "########### which " << which << " weight " << weight << " err " << werr << std::endl;
  
   //return weightdown;
   return weight;
   
}

//==============================================================================================
double BTagWeight::getBTagEffWeightUp( std::vector<JetCandidate> jets, std::string which ){

   jetEff.clear();
   jetEff_e.clear();
   jetSF.clear();
   jetSF_e_up.clear();
   jetSF_e_down.clear(); 
   
   double weight    = 1.0;
   double weightup  = 1.0;
   double mcTag     = 1.0;
   double dataTag   = 1.0;
   double mcNoTag   = 1.0;
   double dataNoTag = 1.0;
   double errNoTag  = 0;
   double werr      = 0;

   double CSVwp;
   if( which == "veto" ) CSVwp = 0.890;
   else CSVwp = 0.605; 
   
   for( unsigned int j = 0; j < jets.size(); ++j ){
   
      //reading eff and SF for each jet and save into vector
      getEff(jets[j].p4.Pt(),jets[j].p4.Eta(),jets[j].flavor, which);
      if( which == "veto" ) getSFM(jets[j].p4.Pt(),jets[j].p4.Eta(),jets[j].flavor);
      else getSFL(jets[j].p4.Pt(),jets[j].p4.Eta(),jets[j].flavor); 
           
   }     
  
   for( unsigned int j = 0; j < jets.size(); ++j ){      
            
      if( jets[j].csv > CSVwp ){
      
         mcTag *= jetEff[j];
	 dataTag *= jetEff[j]*jetSF[j];
	 	 
      }
      else{
         
	 mcNoTag *= (1-jetEff[j]);
	 dataNoTag *= (1-jetEff[j]*jetSF[j]);
	 
	 errNoTag += ((1-jetSF[j])*jetEff_e[j])/((1-jetEff[j])*(1-jetEff[j]*jetSF[j]))*((1-jetSF[j])*jetEff_e[j])/((1-jetEff[j])*(1-jetEff[j]*jetSF[j]));
      
      }      

   }

   weight = (dataNoTag*dataTag)/(mcNoTag*mcTag);
   werr = errNoTag*weight;
   weightup = weight+werr;
   
   //std::cout << "########### which " << which << " weight " << weight << " err " << werr << std::endl;
  
   return weightup;
         
}

//==============================================================================================
double BTagWeight::getBTagEffWeightDown( std::vector<JetCandidate> jets, std::string which ){

   jetEff.clear();
   jetEff_e.clear();
   jetSF.clear();
   jetSF_e_up.clear();
   jetSF_e_down.clear(); 
   
   double weight     = 1.0;
   double weightdown = 1.0;
   double mcTag      = 1.0;
   double dataTag    = 1.0;
   double mcNoTag    = 1.0;
   double dataNoTag  = 1.0;
   double errNoTag     = 0;
   double werr       = 0;

   double CSVwp;
   if( which == "veto" ) CSVwp = 0.890;
   else CSVwp = 0.605;  
   
   for( unsigned int j = 0; j < jets.size(); ++j ){
   
      //reading eff and SF for each jet and save into vector
      getEff(jets[j].p4.Pt(),jets[j].p4.Eta(),jets[j].flavor, which);
      if( which == "veto" ) getSFM(jets[j].p4.Pt(),jets[j].p4.Eta(),jets[j].flavor);
      else getSFL(jets[j].p4.Pt(),jets[j].p4.Eta(),jets[j].flavor); 
           
   }   
   
   for( unsigned int j = 0; j < jets.size(); ++j ){      
            
      if( jets[j].csv > CSVwp ){
      
         mcTag *= jetEff[j];
	 dataTag *= jetEff[j]*jetSF[j];
	 	 
      }
      else{
         
	 mcNoTag *= (1-jetEff[j]);
	 dataNoTag *= (1-jetEff[j]*jetSF[j]);
	 
	 errNoTag += ((1-jetSF[j])*jetEff_e[j])/((1-jetEff[j])*(1-jetEff[j]*jetSF[j]))*((1-jetSF[j])*jetEff_e[j])/((1-jetEff[j])*(1-jetEff[j]*jetSF[j]));
      
      }      

   }

   weight = (dataNoTag*dataTag)/(mcNoTag*mcTag);
   werr = errNoTag*weight;
   weightdown = (weight-werr) > 0 ? weight-werr:0;
   
   //std::cout << "########### which " << which << " weight " << weight << " err " << werr << std::endl;
  
   return weightdown;
      
}

