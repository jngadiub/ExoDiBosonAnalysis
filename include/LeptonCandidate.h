#ifndef LEPTONCANDIDATE_H
#define LEPTONCANDIDATE_H

#include "../ExoDiBosonAnalysis/include/RecoCandidate.h"

class LeptonCandidate : public RecoCandidate {

public:
   LeptonCandidate( TLorentzVector tlv );
   ~LeptonCandidate( void );
     
   double iso;
   double scale;
   int isGlobalMuon;   
   int globalHits;	  
   int pixelHits; 
   int trackerHits;   
   int matchedStations;
   double bestTrack_ptErrRel;
   double d0;		  
   double dz;		  
      
private:

};

#endif // LEPTONCANDIDATE_H


