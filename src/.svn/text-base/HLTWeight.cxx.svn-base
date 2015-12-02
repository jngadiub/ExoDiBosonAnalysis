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
      //sf_weights_map.push_back( 0.99321 );// eta 0.0 - 0.9
      //sf_weights_map.push_back( 0.9911  ); // eta 0.9 - 1.2
      //sf_weights_map.push_back( 0.9975  ); // eta 1.2 - 2.1
      //hlt_weights_map.push_back( 0.94010 );// eta 0.0 - 0.9
      //hlt_weights_map.push_back( 0.84368  ); // eta 0.9 - 1.2
      //hlt_weights_map.push_back( 0.82423  ); // eta 1.2 - 2.1
      sf_weights_map.push_back( 0.9899644*0.9996494 );// eta 0.0 - 0.9
      sf_weights_map.push_back( 0.9923011*0.9993869 ); // eta 0.9 - 1.2
      sf_weights_map.push_back( 0.994906*0.9996816 ); // eta 1.2 - 2.1
      hlt_weights_map.push_back( 0.9289772 );// eta 0.0 - 0.9
      hlt_weights_map.push_back( 0.8313686  ); // eta 0.9 - 1.2
      hlt_weights_map.push_back( 0.8026888  ); // eta 1.2 - 2.1
      eta_map_min.push_back(0.);
      eta_map_max.push_back(0.9);
      eta_map_min.push_back(0.9);
      eta_map_max.push_back(1.2);
      eta_map_min.push_back(1.2);
      eta_map_max.push_back(2.1);
   }
   else if( channel == Ele ){
      sf_weights_map.push_back( 0.98 );
      sf_weights_map.push_back( 0.98 );
      hlt_weights_map.push_back( 0.991 );
      hlt_weights_map.push_back( 0.976 );
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
   }
      
   return;  
                  
}

//==============================================================================================
double HLTWeight::getHLTWeight( double pt, double eta ){

   double sflep     = 0. ;
   double sfhlt     = 0. ;
   
   eta = fabs(eta);      
   if( pt > 0. && pt < 99999. ){
      for( unsigned int i = 0; i < sf_weights_map.size(); ++i ){
         if( isInBin(i,fabs(eta)) ){
	    sflep = sf_weights_map[i];
	    sfhlt = hlt_weights_map[i];
	 }
      } 
   }

   return sflep*sfhlt;      
             
}

//==============================================================================================
bool HLTWeight::isInBin( int bin, double eta ){

   bool found = false;
   for( int b = 0; b < eta_map_min.size(); ++b ){
      if( b == bin && eta > eta_map_min[b] && eta < eta_map_max[b] ){
         found = true;
	 break;  
      }
   }

   return found;

}
