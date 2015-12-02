#include "include/NtupleManager.h"
#include "core/include/SCycleBase.h"

////////////////////////////////////////////////////////////////////
NtupleManager::NtupleManager( SCycleBase* theAnalysis ):theAnalysis_( theAnalysis )
{

}

////////////////////////////////////////////////////////////////////
NtupleManager::~NtupleManager( void ){

}

////////////////////////////////////////////////////////////////////
void NtupleManager::ConnectVariables( std::string treeName, bool runOnMC ){
   
   if( runOnMC ){
   
      theAnalysis_->ConnectVariable( treeName.c_str(), "genParticle_pdgId" , theData_.genParticle_pdgId  );
      theAnalysis_->ConnectVariable( treeName.c_str(), "genParticle_status", theData_.genParticle_status );
      theAnalysis_->ConnectVariable( treeName.c_str(), "genParticle_pt"    , theData_.genParticle_pt	 );
      theAnalysis_->ConnectVariable( treeName.c_str(), "genParticle_mass"  , theData_.genParticle_mass   );
      theAnalysis_->ConnectVariable( treeName.c_str(), "genParticle_e"     , theData_.genParticle_e	 );
      theAnalysis_->ConnectVariable( treeName.c_str(), "genParticle_eta"   , theData_.genParticle_eta	 );
      theAnalysis_->ConnectVariable( treeName.c_str(), "genParticle_phi"   , theData_.genParticle_phi	 );
      theAnalysis_->ConnectVariable( treeName.c_str(), "genParticle_dau"   , theData_.genParticle_dau	 );
      theAnalysis_->ConnectVariable( treeName.c_str(), "genParticle_mother", theData_.genParticle_mother );
      theAnalysis_->ConnectVariable( treeName.c_str(), "lheV_pt"	   , theData_.lheV_pt		 );

      theAnalysis_->ConnectVariable( treeName.c_str(), "nPuVtxTrue"	   , theData_.nPUTrue	         );
      theAnalysis_->ConnectVariable( treeName.c_str(), "bX"		   , theData_.bX		 );
         
   }
   
   theAnalysis_->ConnectVariable( treeName.c_str(), "el_N"		       , theData_.el_N      	    );
   theAnalysis_->ConnectVariable( treeName.c_str(), "el_e"		       , theData_.el_e      	    );
   theAnalysis_->ConnectVariable( treeName.c_str(), "el_eta"		       , theData_.el_eta    	    );
   theAnalysis_->ConnectVariable( treeName.c_str(), "el_pt"		       , theData_.el_pt     	    );
   theAnalysis_->ConnectVariable( treeName.c_str(), "el_phi"		       , theData_.el_phi    	    );
   theAnalysis_->ConnectVariable( treeName.c_str(), "el_isHeepElectron"        , theData_.el_isHEEP         );

   theAnalysis_->ConnectVariable( treeName.c_str(), "mu_N"		       , theData_.mu_N      	    );
   theAnalysis_->ConnectVariable( treeName.c_str(), "mu_e"		       , theData_.mu_e      	    );
   theAnalysis_->ConnectVariable( treeName.c_str(), "mu_eta"		       , theData_.mu_eta    	    );
   theAnalysis_->ConnectVariable( treeName.c_str(), "mu_pt"		       , theData_.mu_pt     	    );
   theAnalysis_->ConnectVariable( treeName.c_str(), "mu_phi"		       , theData_.mu_phi    	    );
   theAnalysis_->ConnectVariable( treeName.c_str(), "mu_trackIso"              , theData_.mu_trackIso       );	
   theAnalysis_->ConnectVariable( treeName.c_str(), "mu_isHighPtMuon"          , theData_.mu_isHighPtMuon   );
   theAnalysis_->ConnectVariable( treeName.c_str(), "mu_isPFMuon"              , theData_.mu_isPFMuon       );
   theAnalysis_->ConnectVariable( treeName.c_str(), "mu_isGlobalMuon"          , theData_.mu_isGlobalMuon   );
   theAnalysis_->ConnectVariable( treeName.c_str(), "mu_globalHits"            , theData_.mu_globalHits      );
   theAnalysis_->ConnectVariable( treeName.c_str(), "mu_matchedStations"       , theData_.mu_matchedStations );
   theAnalysis_->ConnectVariable( treeName.c_str(), "mu_bestTrack_ptErr"       , theData_.mu_bestTrack_ptErr );
   theAnalysis_->ConnectVariable( treeName.c_str(), "mu_bestTrack_pt"          , theData_.mu_bestTrack_pt    );
   theAnalysis_->ConnectVariable( treeName.c_str(), "mu_d0"                    , theData_.mu_d0              );
   theAnalysis_->ConnectVariable( treeName.c_str(), "mu_dz"                    , theData_.mu_dz              );
   theAnalysis_->ConnectVariable( treeName.c_str(), "mu_pixelHits"             , theData_.mu_pixelHits       );
   theAnalysis_->ConnectVariable( treeName.c_str(), "mu_trackerHits"           , theData_.mu_trackerHits     );
         
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK4_N"                 , theData_.njetsAK4	      	);
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK4_e"		       , theData_.jetAK4_e	      	);
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK4_eta"	       , theData_.jetAK4_eta	      	);
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK4_pt"		       , theData_.jetAK4_pt	      	);
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK4_phi"	       , theData_.jetAK4_phi	      	);
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK4_cisv"	       , theData_.jetAK4_csv	      	);
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK4_partonFlavour"     , theData_.jetAK4_flavor       	);
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK4_IDLoose"	       , theData_.jetAK4_IDLoose      	);
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK4_jecUp"	       , theData_.jetAK4_jecUp		);
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK4_jecDown"	       , theData_.jetAK4_jecDown	);
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK4_jec"	       , theData_.jetAK4_jec	        );
     
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_N"                 , theData_.njetsAK8	      	);
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_e"		       , theData_.jetAK8_e	      	);
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_mass"	       , theData_.jetAK8_mass	      	);
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_eta"	       , theData_.jetAK8_eta		);
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_pt"		       , theData_.jetAK8_pt		);
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_phi"	       , theData_.jetAK8_phi		);
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_csv"	       , theData_.jetAK8_csv		);
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_cm"	               , theData_.jetAK8_cm		);
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_nm"	               , theData_.jetAK8_nm		);
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_tau1"	       , theData_.jetAK8_tau1		);
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_tau2"	       , theData_.jetAK8_tau2		);
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_tau3"	       , theData_.jetAK8_tau3		);
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_IDLoose"	       , theData_.jetAK8_IDLoose	);
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_partonFlavour"     , theData_.jetAK8_flavor 	);
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_che"	       , theData_.jetAK8_che		);
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_ne"	               , theData_.jetAK8_ne		);
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_jecUp"	       , theData_.jetAK8_jecUp		);
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_jecDown"	       , theData_.jetAK8_jecDown	);
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_jec"	       , theData_.jetAK8_jec	        );

   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_pruned_massCorr"   , theData_.jetAK8_prunedmass     );
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_pruned_jec"        , theData_.jetAK8_pruned_jec   	);
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_pruned_jecUp"      , theData_.jetAK8_pruned_jecUp   );
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_pruned_jecDown"    , theData_.jetAK8_pruned_jecDown );
   //theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_pruned_mass"       , theData_.jetAK8_prunedmass   	);
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_softdrop_mass"     , theData_.jetAK8_softdropmass 	);


   theAnalysis_->ConnectVariable( treeName.c_str(), "subjetAK8_softdrop_N"	, theData_.subjetAK8_softdrop_N       );
   theAnalysis_->ConnectVariable( treeName.c_str(), "subjetAK8_softdrop_pt"	, theData_.subjetAK8_softdrop_pt      );
   theAnalysis_->ConnectVariable( treeName.c_str(), "subjetAK8_softdrop_eta"	, theData_.subjetAK8_softdrop_eta     );
   theAnalysis_->ConnectVariable( treeName.c_str(), "subjetAK8_softdrop_phi"	, theData_.subjetAK8_softdrop_phi     );
   theAnalysis_->ConnectVariable( treeName.c_str(), "subjetAK8_softdrop_e"	, theData_.subjetAK8_softdrop_e       );   
   theAnalysis_->ConnectVariable( treeName.c_str(), "subjetAK8_softdrop_csv"	, theData_.subjetAK8_softdrop_csv     );
   theAnalysis_->ConnectVariable( treeName.c_str(), "subjetAK8_softdrop_partonFlavour", theData_.subjetAK8_softdrop_flavour );   

   theAnalysis_->ConnectVariable( treeName.c_str(), "subjetAK8_pruned_N"	, theData_.subjetAK8_pruned_N       );
   theAnalysis_->ConnectVariable( treeName.c_str(), "subjetAK8_pruned_pt"	, theData_.subjetAK8_pruned_pt      );
   theAnalysis_->ConnectVariable( treeName.c_str(), "subjetAK8_pruned_eta"	, theData_.subjetAK8_pruned_eta     );
   theAnalysis_->ConnectVariable( treeName.c_str(), "subjetAK8_pruned_phi"	, theData_.subjetAK8_pruned_phi     );
   theAnalysis_->ConnectVariable( treeName.c_str(), "subjetAK8_pruned_e"	, theData_.subjetAK8_pruned_e       );   
   theAnalysis_->ConnectVariable( treeName.c_str(), "subjetAK8_pruned_csv"	, theData_.subjetAK8_pruned_csv     );
   theAnalysis_->ConnectVariable( treeName.c_str(), "subjetAK8_pruned_partonFlavour", theData_.subjetAK8_pruned_flavour );;
            
   theAnalysis_->ConnectVariable( treeName.c_str(), "MET_et"	   	   , theData_.MET_et	  );
   theAnalysis_->ConnectVariable( treeName.c_str(), "MET_phi"	   	   , theData_.MET_phi	  );
   theAnalysis_->ConnectVariable( treeName.c_str(), "MET_sumEt"	   	   , theData_.MET_sumEt	  );
   theAnalysis_->ConnectVariable( treeName.c_str(), "METraw_et"	           , theData_.METraw_et   );
   theAnalysis_->ConnectVariable( treeName.c_str(), "METraw_phi"	   , theData_.METraw_phi  );
   
   theAnalysis_->ConnectVariable( treeName.c_str(), "PV_N"                 , theData_.nPVs        );
   theAnalysis_->ConnectVariable( treeName.c_str(), "PV_filter"            , theData_.PV_filter   );
   
   theAnalysis_->ConnectVariable( treeName.c_str(), "EVENT_event"          , theData_.EVENT_event );
   theAnalysis_->ConnectVariable( treeName.c_str(), "EVENT_run"            , theData_.EVENT_run   );
   theAnalysis_->ConnectVariable( treeName.c_str(), "EVENT_lumiBlock"      , theData_.EVENT_lumi  );

   theAnalysis_->ConnectVariable( treeName.c_str(), "genWeight"            , theData_.genWeight   );

   theAnalysis_->ConnectVariable( treeName.c_str(), "HLT_isFired" 	   , theData_.HLT_isFired );

   theAnalysis_->ConnectVariable( treeName.c_str(), "passFilter_HBHE"		      , theData_.passFilter_HBHE_		 );
   theAnalysis_->ConnectVariable( treeName.c_str(), "passFilter_HBHELoose"	      , theData_.passFilter_HBHELoose_		 );
   theAnalysis_->ConnectVariable( treeName.c_str(), "passFilter_HBHEIso"	      , theData_.passFilter_HBHEIso_		 );
   theAnalysis_->ConnectVariable( treeName.c_str(), "passFilter_CSCHalo"	      , theData_.passFilter_CSCHalo_		 );
   theAnalysis_->ConnectVariable( treeName.c_str(), "passFilter_HCALlaser"	      , theData_.passFilter_HCALlaser_  	 );
   theAnalysis_->ConnectVariable( treeName.c_str(), "passFilter_ECALDeadCell"	      , theData_.passFilter_ECALDeadCell_	 );
   theAnalysis_->ConnectVariable( treeName.c_str(), "passFilter_GoodVtx"	      , theData_.passFilter_GoodVtx_		 );
   theAnalysis_->ConnectVariable( treeName.c_str(), "passFilter_TrkFailure"	      , theData_.passFilter_TrkFailure_ 	 );
   theAnalysis_->ConnectVariable( treeName.c_str(), "passFilter_EEBadSc"	      , theData_.passFilter_EEBadSc_		 );
   theAnalysis_->ConnectVariable( treeName.c_str(), "passFilter_ECALlaser"	      , theData_.passFilter_ECALlaser_  	 );
   theAnalysis_->ConnectVariable( treeName.c_str(), "passFilter_TrkPOG" 	      , theData_.passFilter_TrkPOG_		 );
   theAnalysis_->ConnectVariable( treeName.c_str(), "passFilter_TrkPOG_manystrip"     , theData_.passFilter_TrkPOG_manystrip_	 );
   theAnalysis_->ConnectVariable( treeName.c_str(), "passFilter_TrkPOG_toomanystrip"  , theData_.passFilter_TrkPOG_toomanystrip_ );
   theAnalysis_->ConnectVariable( treeName.c_str(), "passFilter_TrkPOG_logError"      , theData_.passFilter_TrkPOG_logError_	 );
   theAnalysis_->ConnectVariable( treeName.c_str(), "passFilter_METFilters"	      , theData_.passFilter_METFilters_ 	 );
    
}
