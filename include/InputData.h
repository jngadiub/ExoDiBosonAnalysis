#ifndef INPUTDATA_H
#define INPUTDATA_H

#include <vector>
#include <TLorentzVector.h>
#include <map>

class InputData {

public:
   InputData( void );
   ~InputData( void );

   std::vector<int  >*		   genParticle_pdgId 	 ;
   std::vector<int  >*		   genParticle_status 	 ;
   std::vector<float>*		   genParticle_pt    	 ;
   std::vector<float>*  	   genParticle_mass  	 ;
   std::vector<float>*		   genParticle_e     	 ;
   std::vector<float>*		   genParticle_eta   	 ;
   std::vector<float>*		   genParticle_phi   	 ;
   std::vector<std::vector<int> >* genParticle_mother 	 ;
   std::vector<std::vector<int> >* genParticle_dau   	 ;
   float                           lheV_pt               ;
   
   int                             nlep              	 ;
   std::vector<float>*    	   lep_e             	 ;
   std::vector<float>*  	   lep_eta           	 ;
   std::vector<float>*  	   lep_pt            	 ;
   std::vector<float>*  	   lep_phi           	 ;
   std::vector<int  >*  	   lep_type	     	 ;
   std::vector<float>*  	   lep_trackIso          ;   
   std::vector<int  >*  	   lep_tightId           ;
   std::vector<int  >*  	   lep_isHEEP            ;   
   std::vector<int  >*             lep_isHighPtMuon      ;
   std::vector<int  >*  	   lep_isPFMuon	         ;

   int                             el_N              	 ;
   std::vector<float>*    	   el_e 	    	 ;
   std::vector<float>*  	   el_eta	    	 ;
   std::vector<float>*  	   el_pt	    	 ;
   std::vector<float>*  	   el_phi	    	 ;
   std::vector<int  >*  	   el_isHEEP	         ;

   int                             mu_N              	 ;
   std::vector<float>*    	   mu_e 	    	 ;
   std::vector<float>*  	   mu_eta	    	 ;
   std::vector<float>*  	   mu_pt	    	 ;
   std::vector<float>*  	   mu_phi	    	 ;
   std::vector<float>*  	   mu_trackIso           ;   
   std::vector<int  >*             mu_isHighPtMuon       ;
   std::vector<int  >*  	   mu_isPFMuon	         ;
   std::vector<int  >*             mu_isGlobalMuon       ; 
   std::vector<int  >*             mu_globalHits     	 ;
   std::vector<int  >*             mu_pixelHits		 ;
   std::vector<int  >*             mu_trackerHits   	 ;
   std::vector<int  >*             mu_matchedStations	 ;
   std::vector<float>*             mu_bestTrack_ptErr	 ;
   std::vector<float>*             mu_bestTrack_pt   	 ;
   std::vector<float>*             mu_d0	         ;
   std::vector<float>*             mu_dz	         ;
   
   std::vector<float>* 	           MET_et                ;
   std::vector<float>* 	           MET_phi               ;
   std::vector<float>* 	           MET_sumEt             ;
   std::vector<float>* 	           METraw_et             ;
   std::vector<float>* 	           METraw_phi            ;
   
   int                             njetsAK4          	 ;
   std::vector<float>*		   jetAK4_pt	     	 ;
   std::vector<float>*		   jetAK4_eta	     	 ;
   std::vector<float>*		   jetAK4_phi	     	 ;
   std::vector<float>*		   jetAK4_e	     	 ;
   std::vector<float>*		   jetAK4_csv	     	 ;
   std::vector<int  >*		   jetAK4_flavor	 ;
   std::vector<bool  >*  	   jetAK4_IDLoose        ;  
   std::vector<float>*		   jetAK4_jecUp	     	 ;
   std::vector<float>*		   jetAK4_jecDown	 ;
   std::vector<float>*		   jetAK4_jec	         ;
      
   int                             njetsAK8          	 ;
   std::vector<float>*		   jetAK8_pt	     	 ;
   std::vector<float>*		   jetAK8_eta	     	 ;
   std::vector<float>*		   jetAK8_phi	     	 ;
   std::vector<float>*		   jetAK8_e	     	 ;
   std::vector<float>*		   jetAK8_mass	     	 ;
   std::vector<float>*		   jetAK8_csv	     	 ;
   std::vector<int  >*             jetAK8_nm             ;
   std::vector<int  >*             jetAK8_cm             ;
   std::vector<float>*             jetAK8_che            ;
   std::vector<float>*             jetAK8_ne             ;
   std::vector<float>*		   jetAK8_tau1	     	 ;
   std::vector<float>*		   jetAK8_tau2	     	 ;
   std::vector<float>*		   jetAK8_tau3	     	 ;
   std::vector<bool  >*  	   jetAK8_IDLoose        ;  
   std::vector<bool  >*  	   jetAK8_IDTight        ;  
   std::vector<int   >*  	   jetAK8_flavor         ;
   std::vector<int   >*  	   jetAK8_nconstituents  ;
   std::vector<float>*		   jetAK8_jecUp	     	 ;
   std::vector<float>*		   jetAK8_jecDown	 ;
   std::vector<float>*		   jetAK8_jec	         ;

   std::vector<float>*  	   jetAK8_pruned_jec     ;
   std::vector<float>*  	   jetAK8_pruned_jecUp   ;
   std::vector<float>*  	   jetAK8_pruned_jecDown ;
   std::vector<float>*  	   jetAK8_prunedmass     ;
   std::vector<float>*  	   jetAK8_softdropmass   ;
   
   std::vector<int>*                  subjetAK8_softdrop_N      ;
   std::vector< std::vector<float> >* subjetAK8_softdrop_pt     ;
   std::vector< std::vector<float> >* subjetAK8_softdrop_eta    ;
   std::vector< std::vector<float> >* subjetAK8_softdrop_phi    ;
   std::vector< std::vector<float> >* subjetAK8_softdrop_e      ;
   std::vector< std::vector<float> >* subjetAK8_softdrop_csv    ;      
   std::vector< std::vector<int> >*   subjetAK8_softdrop_flavour;      

   std::vector<int>*                  subjetAK8_pruned_N      ;
   std::vector< std::vector<float> >* subjetAK8_pruned_pt     ;
   std::vector< std::vector<float> >* subjetAK8_pruned_eta    ;
   std::vector< std::vector<float> >* subjetAK8_pruned_phi    ;
   std::vector< std::vector<float> >* subjetAK8_pruned_e      ;
   std::vector< std::vector<float> >* subjetAK8_pruned_csv    ;      
   std::vector< std::vector<int> >*   subjetAK8_pruned_flavour;   
             
   std::vector<int  >*             nPUTrue               ;
   std::vector<int  >*             bX                    ;
   int                             nPVs                  ; 
   int                             EVENT_event           ;
   int                             EVENT_run             ;
   int                             EVENT_lumi            ;
   bool                            PV_filter             ;
   float                           genWeight             ;

   /*bool 			       isFired_HLT_IsoMu24_eta2p1_v1              ;
   bool 			       isFired_HLT_IsoMu24_eta2p1_v2              ;
   bool 			       isFired_HLT_Mu45_eta2p1_v1                 ;
   bool 			       isFired_HLT_Mu50_eta2p1_v1                 ;
   bool 			       isFired_HLT_Ele23_CaloIdL_TrackIdL_IsoVL_v1;
   bool 			       isFired_HLT_Ele32_eta2p1_WP75_Gsf_v1       ;
   bool 			       isFired_HLT_Ele105_CaloIdVT_GsfTrkIdT_v1   ;
   bool 			       isFired_HLT_Ele105_CaloIdVT_GsfTrkIdT_v2   ;
   bool 			       isFired_HLT_Ele115_CaloIdVT_GsfTrkIdT_v1   ;*/
   std::map<std::string,bool>*         HLT_isFired;

   /*std::vector<float>*		       triggerObject_pt 	 ;
   std::vector<float>*		       triggerObject_eta	 ;
   std::vector<float>*		       triggerObject_phi	 ;
   std::vector<float>*		       triggerObject_mass	 ;
   std::vector< std::vector<float> >*  triggerObject_filterIDs   ;
   std::vector< std::vector<int> >*    triggerObject_firedTrigger;*/

   bool passFilter_HBHE_;
   bool passFilter_HBHEIso_;
   bool passFilter_HBHELoose_;
   bool passFilter_CSCHalo_;
   bool passFilter_HCALlaser_;
   bool passFilter_ECALDeadCell_;
   bool passFilter_GoodVtx_;
   bool passFilter_TrkFailure_;
   bool passFilter_EEBadSc_;
   bool passFilter_ECALlaser_;
   bool passFilter_TrkPOG_;
   bool passFilter_TrkPOG_manystrip_;
   bool passFilter_TrkPOG_toomanystrip_;
   bool passFilter_TrkPOG_logError_;
   bool passFilter_METFilters_;
                
private:
   
};

#endif // INPUTDATA_H
