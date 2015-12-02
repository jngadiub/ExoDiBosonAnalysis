#include "include/LHEWeight.h"

#include <iostream>

//==============================================================================================
LHEWeight::LHEWeight( void ){

}

//==============================================================================================
LHEWeight::~LHEWeight( void ){

}

//==============================================================================================
LHEWeight::Sample LHEWeight::toSample( const std::string& str ) {

  LHEWeight::Sample sample = None;
  
  if( str == "WJets"  ) sample = WJets;
  else if( str == "DYJets" ) sample = DYJets;
  
  return sample;

}

//==============================================================================================
std::string LHEWeight::toString(const LHEWeight::Sample sample) {

  std::string str = "WJets";
  
  if( sample == DYJets ) str = "DYJets";
  else if( sample == None ) str = "None";

  return str;
}

//==============================================================================================
void LHEWeight::initLHEWeights(const LHEWeight::Sample sample){

   weights_map.clear();
   
   if( sample == WJets ){
      weights_map.push_back( 1.0 ); // pt < 180
      weights_map.push_back( 0.1167716963922136 ); // pt > 180
   }
   else if( sample == DYJets ){
      weights_map.push_back(1.);
      weights_map.push_back(1.);
   }
   else if( sample == None ){
      weights_map.push_back(1.);
      weights_map.push_back(1.);
   }
      
   return;                
     
}

//==============================================================================================
double LHEWeight::getLHEWeight( float pt ){
        
   if( pt < 180. ) return weights_map[0];
   else if ( pt >= 180. ) return weights_map[1];
   else return 1.;     
   
}
