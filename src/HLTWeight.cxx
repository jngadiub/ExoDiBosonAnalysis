#include "include/HLTWeight.h"

#include <iostream>
#include <cmath>

//==============================================================================================
HLTWeight::HLTWeight( void ){

}

//==============================================================================================
HLTWeight::~HLTWeight( void ){

}

//==============================================================================================
HLTWeight::Channel HLTWeight::toChannel( const std::string& str ) {

  HLTWeight::Channel ch = None;

  if( str == "muon" || (str.find("ttbarmu") != std::string::npos) ) ch = Mu;  
  else if( str == "electron"  || (str.find("ttbarel") != std::string::npos) ) ch = Ele;

  return ch;
}

//==============================================================================================
std::string HLTWeight::toString(const HLTWeight::Channel channel) {

  std::string str = "none";
  
  if( channel == Mu ) str = "muon";
  else if( channel == Ele ) str = "electron";

  return str;
  
}

//==============================================================================================
void HLTWeight::initHLTWeights(const HLTWeight::Channel channel){

   sf_weights_map.clear();
   hlt_weights_map.clear();
   
   if( channel == Mu ){
   
      //for each eta bin I need a vector of pt bins
      
      //eta 0-0.9
      std::vector<double> ptW_1;
      ptW_1.push_back(0.9717); //pt 47-50
      ptW_1.push_back(0.9764); //pt 50-60
      ptW_1.push_back(0.9693); //pt 60-inf
      sf_weights_map.push_back(ptW_1);

      //eta 0.9-1.2
      std::vector<double> ptW_2;
      ptW_2.push_back(0.9534); //pt 47-50
      ptW_2.push_back(0.9722); //pt 50-60
      ptW_2.push_back(0.9607); //pt 60-inf
      sf_weights_map.push_back(ptW_2);
 
       //eta 1.2-2.1
      std::vector<double> ptW_3;
      ptW_3.push_back(0.9610); //pt 47-50
      ptW_3.push_back(0.9631); //pt 50-60
      ptW_3.push_back(0.9677); //pt 60-inf
      sf_weights_map.push_back(ptW_3);

      eta_map_min.push_back(0.);
      eta_map_max.push_back(0.9);
      eta_map_min.push_back(0.9);
      eta_map_max.push_back(1.2);
      eta_map_min.push_back(1.2);
      eta_map_max.push_back(2.1);
      
      pt_map_min.push_back(47.);
      pt_map_max.push_back(50.);
      pt_map_min.push_back(50.);
      pt_map_max.push_back(60.);
      pt_map_min.push_back(60.);
      pt_map_max.push_back(10000.);
      
   }
   /*else if( channel == Ele ){
      sf_weights_map.push_back( 1 );
      sf_weights_map.push_back( 1 );
      hlt_weights_map.push_back( 1 );
      hlt_weights_map.push_back( 1 );
      eta_map_min.push_back(0.);
      eta_map_max.push_back(1.442);
      eta_map_min.push_back(1.56);
      eta_map_max.push_back(2.5);
   }
   else if( channel == None ){
      sf_weights_map.push_back( 1.  );
      sf_weights_map.push_back( 1.  );
      sf_weights_map.push_back( 1.  );
      hlt_weights_map.push_back( 1. );
      hlt_weights_map.push_back( 1. );
      hlt_weights_map.push_back( 1. );
   }*/
      
   return;  
                  
}

//==============================================================================================
double HLTWeight::getHLTWeight( double pt, double eta ){

   double sflep     = 0. ;
   double sfhlt     = 0. ;
   
   eta = fabs(eta);      
   for( unsigned int i = 0; i < sf_weights_map.size(); ++i ){
    if( isInEtaBin(i,fabs(eta)) ){
     for( unsigned int j = 0; j < sf_weights_map[i].size(); ++j ){
      if( isInPtBin(j,pt) ) sflep = sf_weights_map[i][j];
     }
    }
   } 

   return sflep;      
             
}

//==============================================================================================
bool HLTWeight::isInEtaBin( int bin, double eta ){

   bool found = false;
   for( unsigned int b = 0; b < eta_map_min.size(); ++b ){
      if( b == bin && eta > eta_map_min[b] && eta < eta_map_max[b] ){
         found = true;
	 break;  
      }
   }

   return found;

}

//==============================================================================================
bool HLTWeight::isInPtBin( int bin, double pt ){

   bool found = false;
   for( unsigned int b = 0; b < pt_map_min.size(); ++b ){
      if( b == bin && pt > pt_map_min[b] && pt < pt_map_max[b] ){
         found = true;
	 break;  
      }
   }

   return found;

}
