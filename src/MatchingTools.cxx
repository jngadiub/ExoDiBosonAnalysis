#include "include/MatchingTools.h"
#include "include/InputData.h"
#include "include/LeptonCandidate.h"
#include "include/JetCandidate.h"

#include <iostream>
#include <map>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<LeptonCandidate> MatchingTools::findMuonsMatch( TLorentzVector genMu, InputData& data ){

   std::vector<LeptonCandidate> vec;
   std::map<int,double> map;
   TLorentzVector p4Mu;
   LeptonCandidate matchedMu( p4Mu );
   double deltaR;
   for( int l = 0; l < data.nlep; ++l ){
     if( abs((*data.lep_type)[l]) == 13 ){    
     	p4Mu.SetPtEtaPhiE( (*data.lep_pt)[l], (*data.lep_eta)[l], (*data.lep_phi)[l], (*data.lep_e)[l] );
     	if( (deltaR = genMu.DeltaR(p4Mu)) < 0.5 ) map[l] = deltaR;
     }
   }
   
   std::map<int,double>::iterator it = map.begin();
   int index = -1;
   double tmp = 999999;
   while( it != map.end() ){
      if( it->second < tmp ){ 
         index = it->first;
	 tmp = it->second;
      }
      ++it;
   }
   
   if( map.size() != 0 ){
      p4Mu.SetPtEtaPhiE( (*data.lep_pt)[index], (*data.lep_eta)[index], (*data.lep_phi)[index], (*data.lep_e)[index] );
      matchedMu.p4 = p4Mu;
      vec.push_back(matchedMu);
   }
   
   return vec;
   
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<LeptonCandidate> MatchingTools::findElectronsMatch( TLorentzVector genEle, InputData& data ){

   std::vector<LeptonCandidate> vec;
   std::map<int,double> map;
   TLorentzVector p4Ele;   
   LeptonCandidate matchedEle( p4Ele );
   double deltaR;
   for( int l = 0; l < data.nlep; ++l ){
     if( abs((*data.lep_type)[l]) == 11 ){
        p4Ele.SetPtEtaPhiE( (*data.lep_pt)[l], (*data.lep_eta)[l], (*data.lep_phi)[l], (*data.lep_e)[l] ); 
     	if( (deltaR = genEle.DeltaR(p4Ele)) < 0.5 ) map[l] = deltaR;
     }
   }
   
   std::map<int,double>::iterator it = map.begin();
   int index = -1;
   double tmp = 999999;
   while( it != map.end() ){
      if( it->second < tmp ){
         index = it->first;
	 tmp = it->second;
      }
      ++it;
   }
   
   if( map.size() != 0 ){
      p4Ele.SetPtEtaPhiE( (*data.lep_pt)[index], (*data.lep_eta)[index], (*data.lep_phi)[index], (*data.lep_e)[index] );
      matchedEle.p4 = p4Ele;
      vec.push_back(matchedEle);
   }
      
   return vec;
   
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<JetCandidate> MatchingTools::findAK4JetsMatch( TLorentzVector genQ, InputData& data ){
   
   std::vector<JetCandidate> vec;
   std::map<int,double> map;
   TLorentzVector p4Jet;
   JetCandidate matchedJet( p4Jet );
   double deltaR;
   for( int j = 0; j < data.njetsAK4; ++j ){
      p4Jet.SetPtEtaPhiE( (*data.jetAK4_pt)[j], (*data.jetAK4_eta)[j], (*data.jetAK4_phi)[j], (*data.jetAK4_e)[j] );
      if( (deltaR = genQ.DeltaR(p4Jet)) < 0.5 ) map[j] = deltaR;
   }
   
   std::map<int,double>::iterator it = map.begin();
   int index = -1;
   double tmp = 999999;
   while( it != map.end() ){
      if( it->second < tmp ){ 
         index = it->first;
	 tmp = it->second;
      }
      ++it;
   }
   
   if( map.size() != 0 ){
      p4Jet.SetPtEtaPhiE( (*data.jetAK4_pt)[index], (*data.jetAK4_eta)[index], (*data.jetAK4_phi)[index], (*data.jetAK4_e)[index] );
      matchedJet.p4 = p4Jet;
      matchedJet.csv = (*data.jetAK4_csv)[index];
      vec.push_back(matchedJet);
   }
   
   return vec;
   
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<JetCandidate> MatchingTools::findAK8JetsMatch( TLorentzVector genQ, InputData& data ){

   std::vector<JetCandidate> vec;
   std::map<int,double> map;
   TLorentzVector p4Jet;
   JetCandidate matchedJet( p4Jet );
   double deltaR;
   for( int j = 0; j < data.njetsAK8; ++j ){
      p4Jet.SetPtEtaPhiE( (*data.jetAK8_pt)[j], (*data.jetAK8_eta)[j], (*data.jetAK8_phi)[j], (*data.jetAK8_e)[j] );
      if( (deltaR = genQ.DeltaR(p4Jet)) < 0.8 ) map[j] = deltaR;
   }
   
   std::map<int,double>::iterator it = map.begin();
   int index = -1;
   double tmp = 999999;
   while( it != map.end() ){
      if( it->second < tmp ){ 
         index = it->first;
	 tmp = it->second;
      }
      ++it;
   }
   
   if( map.size() != 0 ){
      p4Jet.SetPtEtaPhiE( (*data.jetAK8_pt)[index], (*data.jetAK8_eta)[index], (*data.jetAK8_phi)[index], (*data.jetAK8_e)[index] );
      matchedJet.p4 = p4Jet;
      matchedJet.csv = (*data.jetAK8_csv)[index];
      vec.push_back(matchedJet);
   }
   
   return vec;
   
}
