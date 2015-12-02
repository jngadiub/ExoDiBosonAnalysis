#include "include/LeptonCandidate.h"

///////////////////////////////////////////////////////////////////////////////////////////////
LeptonCandidate::LeptonCandidate( TLorentzVector tlv )
   : RecoCandidate( tlv )
   , iso(-99)
   , scale(-99)
   , isGlobalMuon(-99)  
   , globalHits(-99)      
   , pixelHits(-99)
   , trackerHits(-99)   
   , matchedStations(-99)
   , bestTrack_ptErrRel(-99)
   , d0(-99)	      
   , dz(-99)	      
{

}

///////////////////////////////////////////////////////////////////////////////////////////////
LeptonCandidate::~LeptonCandidate( void )
{

} 



