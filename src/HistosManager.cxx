#include "include/HistosManager.h"
#include "include/ExoDiBosonAnalysis.h"
#include "include/Utilities.h"

#include <TH1F.h>
#include <TH2F.h>

////////////////////////////////////////////////////////////////////
HistosManager::HistosManager( ExoDiBosonAnalysis* theAnalysis ):theAnalysis_( theAnalysis )
{

}

////////////////////////////////////////////////////////////////////
HistosManager::~HistosManager( void ){

}

////////////////////////////////////////////////////////////////////
void HistosManager::bookHistos( void ){

   /* lepton efficiency histos */
   theAnalysis_->Book( TH1F( "leptonRecoEffPT"       , "lepton pt"	      ,    50,  0. , 5000.  ) );
   theAnalysis_->Book( TH1F( "leptonRecoEffPTden"    , "lepton pt"	      ,    50,  0. , 5000.  ) );
   theAnalysis_->Book( TH1F( "leptonRecoEffEta"      , "lepton eta"	      ,    50, -2.5,	2.5 ) );
   theAnalysis_->Book( TH1F( "leptonRecoEffEtaden"   , "lepton eta"	      ,    50, -2.5,	2.5 ) );
   theAnalysis_->Book( TH1F( "leptonRecoGenDR"       , "#DeltaR(gen,reco)"    ,  1000,  0. ,   10.  ) );
   theAnalysis_->Book( TH1F( "leptonRecoGenDPT"      , "#Deltap_{T}(gen,reco)",  1000,-10. ,   10.  ) );
   theAnalysis_->Book( TH1F( "leptonIDEffPT"         , "lepton pt"	      ,   500,  0. , 5000.  ) );
   theAnalysis_->Book( TH1F( "leptonIDEffPTden"      , "lepton pt"	      ,   500,  0. , 5000.  ) );
   theAnalysis_->Book( TH1F( "leptonIDEffEta"        , "lepton eta"	      ,    50, -2.5,	2.5 ) );
   theAnalysis_->Book( TH1F( "leptonIDEffEtaden"     , "lepton eta"	      ,    50, -2.5,	2.5 ) );
   theAnalysis_->Book( TH1F( "leptonTriggerEffPT"    , "lepton pt"	      ,  5000,  0. , 5000.  ) );
   theAnalysis_->Book( TH1F( "leptonTriggerEffPTden" , "lepton pt"	      ,  5000,  0. , 5000.  ) );
   theAnalysis_->Book( TH1F( "leptonTriggerEffEta"   , "lepton eta"	      ,    50, -2.5,	2.5 ) );
   theAnalysis_->Book( TH1F( "leptonTriggerEffEtaden", "lepton eta"	      ,    50, -2.5,	2.5 ) );
   theAnalysis_->Book( TH1F( "leptonTriggerEffWPT"   , "W pt"	              ,  5000,  0. , 5000.  ) );
   theAnalysis_->Book( TH1F( "leptonTriggerEffWPTden", "W pt"	              ,  5000,  0. , 5000.  ) );
   theAnalysis_->Book( TH1F( "leptonTriggerEffMET"   , "MET"	              ,  5000,  0. , 5000.  ) );
   theAnalysis_->Book( TH1F( "leptonTriggerEffMETden", "MET"	              ,  5000,  0. , 5000.  ) );
         
   /* AK8 b-jet histos */
   theAnalysis_->Book( TH1F( "AK8jetPT" 	    , "AK8 b-jet pt"	     ,   2000,  0. , 2000.  ) );
   theAnalysis_->Book( TH1F( "AK8jetEta"	    , "AK8 b-jet eta"	     ,    50, -2.5,    2.5 ) );
   theAnalysis_->Book( TH1F( "AK8jetPhi"	    , "AK8 b-jet phi"	     ,    64, -3.2,    3.2 ) );
   theAnalysis_->Book( TH1F( "AK8jetCSV"	    , "AK8 b-jet csv"	     ,    50,  0. ,    1.  ) );
   theAnalysis_->Book( TH1F( "AK8jetMass" 	    , "AK8 b-jet mass"	     ,    80,  0. ,  200.  ) );
   theAnalysis_->Book( TH1F( "AK8jetPrunedMass"     , "AK8 b-jet pruned mass",    80,  0. ,  200.  ) );
   theAnalysis_->Book( TH1F( "AK8jetSoftDropMass"   , "AK8 b-jet soft drop mass",    80,  0. ,  200.  ) );
   theAnalysis_->Book( TH1F( "tau21"     	    , "#tau_{21}"            ,   100,  0. ,    1.  ) );
   theAnalysis_->Book( TH1F( "tau31"     	    , "#tau_{31}"            ,   100,  0. ,    1.  ) );
   theAnalysis_->Book( TH1F( "tau32"     	    , "#tau_{32}"            ,   100,  0. ,    1.  ) );

   /* lepton histos */
   theAnalysis_->Book( TH1F( "leptonPT"   	    , "lepton pt"	     ,   2000,  0. , 2000.  ) );		   
   theAnalysis_->Book( TH1F( "leptonPhi"   	    , "lepton #phi"	     ,    32, -3.2,    3.2 ) );		   
   theAnalysis_->Book( TH1F( "leptonEta"  	    , "lepton eta"	     ,    50, -2.5,    2.5 ) );		   
   theAnalysis_->Book( TH1F( "leptonIso"            , "lepton iso"           ,  1000,  0. ,    1.  ) );
   
   /* MET histos */
   theAnalysis_->Book( TH1F( "MET"	  	    , "#slash{E}_T"	     ,   2000,  0. , 2000.  ) );
   theAnalysis_->Book( TH1F( "METphi"	  	    , "MET $phi"	     ,    64, -3.2,    3.2  ) );
   theAnalysis_->Book( TH1F( "METresolution"	    , "#slash{E}_T"	     ,   2000,-100. ,   100. ) );
 
   /* leptonic W histos */
   theAnalysis_->Book( TH1F( "recoWPT"    	    , "W p_{T}" 	     ,   200,  0. , 2000.  ) );
   theAnalysis_->Book( TH1F( "recoWMT"    	    , "W M_{T}" 	     ,   400,  0. , 2000.  ) );
 
   /* AK4 jets histos */
   theAnalysis_->Book( TH1F( "nAJets"    	    , "# additional jets"    ,    21, -0.5,   20.5 ) );
   theAnalysis_->Book( TH1F( "nAJetsBTag"    	    , "# additional jets"    ,    21, -0.5,   20.5 ) );
   theAnalysis_->Book( TH1F( "AK4jetPt"    	    , "AK4 leading jet p_{T}",   100,  0. , 1000.  ) );
   theAnalysis_->Book( TH1F( "AK4jetCSV"    	    , "AK4 jet CSV"          ,    50,  0. ,    1.  ) );
   theAnalysis_->Book( TH1F( "AK4jetMass"    	    , "AK4 jet mass"         ,   150,  0. ,  300.  ) );

    /* topology histos */
   theAnalysis_->Book( TH1F( "lepJetDR"   	      , "#DeltaR(l,j)"	         , 100, 0. ,   10.  ) );
   theAnalysis_->Book( TH1F( "METJetDphi" 	      , "#Delta#phi(MET,j)"      , 128, 0. ,    3.2 ) );
   theAnalysis_->Book( TH1F( "WJetDphi"     	      , "#Delta#phi(j,W)"        , 128, 0. ,    3.2 ) );      

   /* top histos */
   theAnalysis_->Book( TH1F( "leptonictopmass"        , "leptonic top mass"      , 100, 0. , 1000.  ) );
   theAnalysis_->Book( TH1F( "hadronictopmass"        , "hadronic top mass"      , 100, 0. , 1000.  ) );
   theAnalysis_->Book( TH1F( "leptonictopmassV2"      , "leptonic top mass"      , 100, 0. , 1000.  ) );
 
   /* MWW */
   theAnalysis_->Book( TH1F( "DiBosonInvMass"	      , "di-bosons inv mass"     , 500, 0. , 5000.  ) );

   /* cut flow */
   theAnalysis_->Book( TH1F( "genEvents"              , "genEvents"              ,   1, 0.5,    1.5 ) );    
   theAnalysis_->Book( TH1F( "nEvents"                , "nEvents"	    	 ,   1, 0.5,    1.5 ) );
   theAnalysis_->Book( TH1F( "nPassedTrigger"         , "nPassedTrigger"    	 ,   1, 0.5,    1.5 ) );
   theAnalysis_->Book( TH1F( "nPassedFoundLepton"     , "nPassedFoundLepton" 	 ,   1, 0.5,    1.5 ) );
   theAnalysis_->Book( TH1F( "nPassedVetoExtraLeptons", "nPassedVetoExtraLeptons",   1, 0.5,    1.5 ) );
   theAnalysis_->Book( TH1F( "nPassedFoundMET"        , "nPassedFoundMET"  	 ,   1, 0.5,    1.5 ) );
   theAnalysis_->Book( TH1F( "nPassedFoundW"          , "nnPassedFoundW"    	 ,   1, 0.5,    1.5 ) );
   theAnalysis_->Book( TH1F( "nPassedFoundJet"        , "nPassedFoundJet"  	 ,   1, 0.5,    1.5 ) );
   theAnalysis_->Book( TH1F( "nPassedJetPtTight"      , "nPassedJetPtTight"	 ,   1, 0.5,    1.5 ) );
   theAnalysis_->Book( TH1F( "nPassedLepJetDR"        , "nPassedLepJetDR"  	 ,   1, 0.5,    1.5 ) );
   theAnalysis_->Book( TH1F( "nPassedTOBTECFilter"    , "nPassedTOBTECFilter"  	 ,   1, 0.5,    1.5 ) );
   theAnalysis_->Book( TH1F( "nPassedNsubj"           , "nPassedNsubj"  	 ,   1, 0.5,    1.5 ) );
   theAnalysis_->Book( TH1F( "nPassedDRsubj"          , "nPassedDRsubj"  	 ,   1, 0.5,    1.5 ) );
   theAnalysis_->Book( TH1F( "nPassedJetCSV"          , "nPassedJetCSV"    	 ,   1, 0.5,    1.5 ) );   
   theAnalysis_->Book( TH1F( "nPassedAJetCut"         , "nPassedAJetCut"    	 ,   1, 0.5,    1.5 ) );
   theAnalysis_->Book( TH1F( "nPassedLepJetDR2"       , "nPassedLepJetDR2" 	 ,   1, 0.5,    1.5 ) );
   theAnalysis_->Book( TH1F( "nPassedMETJetDPhi"      , "nPassedMETJetDPhi"	 ,   1, 0.5,    1.5 ) );
   theAnalysis_->Book( TH1F( "nPassedJetWDPhi"        , "nPassedJetWDPhi"  	 ,   1, 0.5,    1.5 ) );
   theAnalysis_->Book( TH1F( "nPassedTopMass"         , "nPassedTopMass"  	 ,   1, 0.5,    1.5 ) );   
   theAnalysis_->Book( TH1F( "nPassedJetMass"         , "nPassedJetMass"    	 ,   1, 0.5,    1.5 ) );
   theAnalysis_->Book( TH1F( "nPassedNsubjBTagCut"    , "nPassedNsubjBTagCut"    ,   1, 0.5,    1.5 ) );
   theAnalysis_->Book( TH1F( "nPassedExoCandidateMass", "nPassedExoCandidateMass",   1, 0.5,    1.5 ) );

   // filters cut flow //
   theAnalysis_->Book( TH1F( "nPassedGoodPVFilter"        	, "nPassedGoodPVFilter"              , 	1, 0.5, 1.5 ) );
   theAnalysis_->Book( TH1F( "nPassedFilter_HBHE"        	, "nPassedFilter_HBHE"               , 	1, 0.5, 1.5 ) );
   theAnalysis_->Book( TH1F( "nPassedFilter_HBHEIso"        	, "nPassedFilter_HBHEIso"            , 	1, 0.5, 1.5 ) );
   theAnalysis_->Book( TH1F( "nPassedFilter_CSCHalo"     	, "nPassedFilter_CSCHalo"            ,	1, 0.5, 1.5 ) );
   theAnalysis_->Book( TH1F( "nPassedFilter_HCALlaser"   	, "nPassedFilter_HCALlaser"          ,	1, 0.5,	1.5 ) );
   theAnalysis_->Book( TH1F( "nPassedFilter_ECALDeadCell"	, "nPassedFilter_ECALDeadCell"       , 	1, 0.5,	1.5 ) );
   theAnalysis_->Book( TH1F( "nPassedFilter_GoodVtx"     	, "nPassedFilter_GoodVtx"            ,	1, 0.5, 1.5 ) );
   theAnalysis_->Book( TH1F( "nPassedFilter_TrkFailure"  	, "nPassedFilter_TrkFailure"         ,	1, 0.5,	1.5 ) );
   theAnalysis_->Book( TH1F( "nPassedFilter_EEBadSc"     	, "nPassedFilter_EEBadSc"            ,	1, 0.5, 1.5 ) );
   theAnalysis_->Book( TH1F( "nPassedFilter_ECALlaser"   	, "nPassedFilter_ECALlaser"          ,	1, 0.5,	1.5 ) );
   theAnalysis_->Book( TH1F( "nPassedFilter_TrkPOG"             , "nPassedFilter_TrkPOG"             ,	1, 0.5, 1.5 ) );
   theAnalysis_->Book( TH1F( "nPassedFilter_TrkPOG_manystrip"   , "nPassedFilter_TrkPOG_manystrip"   ,	1, 0.5, 1.5 ) );
   theAnalysis_->Book( TH1F( "nPassedFilter_TrkPOG_toomanystrip", "nPassedFilter_TrkPOG_toomanystrip",  1, 0.5, 1.5 ) );
   theAnalysis_->Book( TH1F( "nPassedFilter_TrkPOG_logError"    , "nPassedFilter_TrkPOG_logError"    ,	1, 0.5, 1.5 ) );
   theAnalysis_->Book( TH1F( "nPassedFilter_METFilters"         , "nPassedFilter_METFilters"         ,	1, 0.5, 1.5 ) );
    theAnalysis_->Book( TH1F( "nPassedFilter_EventList"         , "nPassedFilter_EventList"         ,	1, 0.5, 1.5 ) );
   theAnalysis_->Book( TH1F( "nPassedMETFiltersAll"             , "nPassedMETFiltersAll"             ,	1, 0.5, 1.5 ) );
   theAnalysis_->Book( TH1F( "nPassedTrkFiltersAll"             , "nPassedTrkFiltersAll"             ,	1, 0.5, 1.5 ) );
   theAnalysis_->Book( TH1F( "nPassedFilters"        	        , "nPassedFilters"                   , 	1, 0.5, 1.5 ) );

   // filters efficiency //
   theAnalysis_->Book( TH1F( "FiltersEffPT_den" , "jet pt" , 5000,  0. , 5000.  ) );
   theAnalysis_->Book( TH1F( "FiltersEffEta_den", "jet eta",   50, -2.5,    2.5 ) );

   theAnalysis_->Book( TH1F( "HBHEFilterEffPT"    , "jet pt" , 5000,  0. , 5000.  ) );
   theAnalysis_->Book( TH1F( "HBHEFilterEffEta"   , "jet eta",   50, -2.5,    2.5 ) );
   theAnalysis_->Book( TH1F( "HBHEFilterMET"      , "MET"    ,  500,  0. ,  500.  ) );
   theAnalysis_->Book( TH1F( "HBHEFilterSumET"    , "sumET"  , 2000,  0. ,    2.  ) );

   theAnalysis_->Book( TH1F( "HBHEIsoFilterEffPT"    , "jet pt" , 5000,  0. , 5000.  ) );
   theAnalysis_->Book( TH1F( "HBHEIsoFilterEffEta"   , "jet eta",   50, -2.5,    2.5 ) );
   
   theAnalysis_->Book( TH1F( "METFiltersEffPT"    , "jet pt" , 5000,  0. , 5000.  ) );
   theAnalysis_->Book( TH1F( "METFiltersEffEta"   , "jet eta",   50, -2.5,    2.5 ) );

   theAnalysis_->Book( TH1F( "TrkPOGFiltersEffPT"    , "jet pt" , 5000,  0. , 5000.  ) );
   theAnalysis_->Book( TH1F( "TrkPOGFiltersEffEta"   , "jet eta",   50, -2.5,    2.5 ) );

   theAnalysis_->Book( TH1F( "CSCHaloFilterEffPT"    , "jet pt" , 5000,  0. , 5000.  ) );
   theAnalysis_->Book( TH1F( "CSCHaloFilterEffEta"   , "jet eta",   50, -2.5,    2.5 ) );

   theAnalysis_->Book( TH1F( "GoodVtxFilterEffPT"    , "jet pt" , 5000,  0. , 5000.  ) );
   theAnalysis_->Book( TH1F( "GoodVtxFilterEffEta"   , "jet eta",   50, -2.5,    2.5 ) );

   theAnalysis_->Book( TH1F( "EEBadScFilterEffPT"    , "jet pt" , 5000,  0. , 5000.  ) );
   theAnalysis_->Book( TH1F( "EEBadScFilterEffEta"   , "jet eta",   50, -2.5,    2.5 ) );
               
   /* other histos */
   theAnalysis_->Book( TH1F( "sumGenWeight"         , "sum gen weights"      ,     1,  0.5,    1.5 ) );
   theAnalysis_->Book( TH1F( "PUWeights"            , "pu weights"           ,   60,  0. ,   60.  ) );
   theAnalysis_->Book( TH1F( "htagweight"           , "h tag weights"        ,   100,  0. ,    5.  ) );
   theAnalysis_->Book( TH1F( "btagvweight"          , "b tag veto weights"   ,   100,  0. ,    5.  ) );
   theAnalysis_->Book( TH1F( "nVertices"            , "number of PVs"        ,    60,  0. ,   60.  ) );
   theAnalysis_->Book( TH1F( "runNumber"            , "run number"           ,  1000,  251000, 252000 ) );
   theAnalysis_->Book( TH1F( "nPUTrue"              , "number of true PU"    ,    60,  0. ,   60.  ) );

   /* debugging di-boson inv mass reconstruction*/
   theAnalysis_->Book( TH1F( "Discriminant"         , "#Delta"            ,   80,   -20. ,   20. ) );
   theAnalysis_->Book( TH1F( "A"                    , "A"                 ,   80,     0. ,   20. ) );
   theAnalysis_->Book( TH1F( "B"                    , "B"                 ,  100,   -50. ,   50. ) );
   theAnalysis_->Book( TH1F( "C"                    , "C"                 ,  120,   -10. ,   50. ) );
   theAnalysis_->Book( TH1F( "a"                    , "a"                 ,  100,     0. ,   50. ) );
   theAnalysis_->Book( TH1F( "pzNu"                 , "pzNu"              ,  100, -1000. , 1000. ) );
   theAnalysis_->Book( TH1F( "DiBosonInvMassMethod2", "mass"              ,  500,     0. , 5000. ) );
   theAnalysis_->Book( TH1F( "DiBosonInvMassDeltam" , "mass"              ,  500,     0. , 5000. ) );
   theAnalysis_->Book( TH1F( "DiBosonInvMassDeltap" , "mass"              ,  500,     0. , 5000. ) );
   theAnalysis_->Book( TH1F( "NuLeptInvMass"        , "mass"              ,  200,     0. ,  200. ) );
   theAnalysis_->Book( TH1F( "NuLeptInvMassDeltam"  , "mass"              ,  200,     0. ,  200. ) );
   theAnalysis_->Book( TH1F( "NuLeptInvMassDeltap"  , "mass"              ,  200,     0. ,  200. ) );
   theAnalysis_->Book( TH1F( "genWMass"             , "mass"              ,  200,     0. ,  200. ) );
   theAnalysis_->Book( TH1F( "WMassResolution"      , "resolution"        , 1000,   -10. ,   10. ) );
   theAnalysis_->Book( TH1F( "WMassResolutionV2"    , "resolution"        , 1000,   -10. ,   10. ) );
   theAnalysis_->Book( TH1F( "WWMassResolution"     , "resolution"        , 1000,   -10. ,   10. ) );
   theAnalysis_->Book( TH1F( "WWMassResolutionV2"   , "resolution"        , 1000,   -10. ,   10. ) );
           
}

////////////////////////////////////////////////////////////////////
void HistosManager::formatHistos( void ){

   /* lepton efficiency histos */
   //theAnalysis_->Hist( "leptonRecoEffPT" )->Divide(theAnalysis_->Hist( "leptonRecoEffPTden" ));
   //theAnalysis_->Hist( "leptonRecoEffEta" )->Divide(theAnalysis_->Hist( "leptonRecoEffEtaden" ));
   //theAnalysis_->Hist( "leptonIDEffPT" )->Divide( theAnalysis_->Hist( "leptonIDEffPTden") );    
   //theAnalysis_->Hist( "leptonIDEffEta" )->Divide( theAnalysis_->Hist( "leptonIDEffEtaden") );    
   //theAnalysis_->Hist( "leptonTriggerEffPT" )->Divide( theAnalysis_->Hist( "leptonTriggerEffPTden") );    
   //theAnalysis_->Hist( "leptonTriggerEffEta" )->Divide( theAnalysis_->Hist( "leptonTriggerEffEtaden") ); 
   
   /* AK8 b-jet histos */
   theAnalysis_->Hist( "AK8jetPT"  	       )->GetXaxis()->SetTitle( "W_{hadr} p_{T} [GeV]"		    );
   theAnalysis_->Hist( "AK8jetEta" 	       )->GetXaxis()->SetTitle( "W_{hadr} #eta"		            );
   theAnalysis_->Hist( "AK8jetPhi"  	       )->GetXaxis()->SetTitle( "W_{hadr} #phi [rad]"		    );
   theAnalysis_->Hist( "AK8jetCSV" 	       )->GetXaxis()->SetTitle( "CSV^{AK8}"			    );
   theAnalysis_->Hist( "AK8jetMass"           )->GetXaxis()->SetTitle( "W_{hadr} mass [GeV]"		    );
   theAnalysis_->Hist( "AK8jetPrunedMass"     )->GetXaxis()->SetTitle( "m_{jet}^{pruned} [GeV]"	    );
   theAnalysis_->Hist( "tau21"  	       )->GetXaxis()->SetTitle( "#tau_{21}"			    );
   theAnalysis_->Hist( "tau31"  	       )->GetXaxis()->SetTitle( "#tau_{31}"			    );
   theAnalysis_->Hist( "tau32"  	       )->GetXaxis()->SetTitle( "#tau_{32}"			    );

   /* lepton histos */            
   theAnalysis_->Hist( "leptonPT"   	       )->GetXaxis()->SetTitle( "lepton p_{T} [GeV]"		    );
   theAnalysis_->Hist( "leptonPhi"   	       )->GetXaxis()->SetTitle( "lepton #phi [rad]"		    );
   theAnalysis_->Hist( "leptonEta"  	       )->GetXaxis()->SetTitle( "lepton #eta"			    );

   /* MET histos */   
   theAnalysis_->Hist( "MET"	    	       )->GetXaxis()->SetTitle( "E_{T}^{miss} [GeV]"		    );
   theAnalysis_->Hist( "METphi"                )->GetXaxis()->SetTitle( "E_{T}^{miss} #phi [rad]"	    );

   /* leptonic W histos */
   theAnalysis_->Hist( "recoWPT"    	       )->GetXaxis()->SetTitle( "W_{lept} p_{T} [GeV]"		    );
   theAnalysis_->Hist( "recoWMT"    	       )->GetXaxis()->SetTitle( "M_{T} [GeV]"		            ); 

   /* AK4 jets histos */ 
   theAnalysis_->Hist( "nAJets"    	       )->GetXaxis()->SetTitle( "number of extra jets"	    );
   theAnalysis_->Hist( "nAJetsBTag"    	       )->GetXaxis()->SetTitle( "number of b-tagged extra jets"	    );
   theAnalysis_->Hist( "AK4jetPt"    	       )->GetXaxis()->SetTitle( "p_{T}^{AK4} [GeV]"		    );
   theAnalysis_->Hist( "AK4jetCSV"    	       )->GetXaxis()->SetTitle( "CSV^{AK4} [GeV]"		    );
   theAnalysis_->Hist( "AK4jetMass"    	       )->GetXaxis()->SetTitle( "mass^{AK4} [GeV]"		    );

    /* topology histos */   
   theAnalysis_->Hist( "lepJetDR"   	       )->GetXaxis()->SetTitle( "#DeltaR(lept,W_{hadr})"  		    );
   theAnalysis_->Hist( "METJetDphi" 	       )->GetXaxis()->SetTitle( "#Delta#phi(W_{hadr},#slash{E}_{T}) [rad]"  );
   theAnalysis_->Hist( "WJetDphi"   	       )->GetXaxis()->SetTitle( "#Delta#phi(W_{hadr},W_{lept}) [rad]" 	    );

   /* top histos */
   theAnalysis_->Hist( "leptonictopmass"     )->GetXaxis()->SetTitle( "leptonic top mass [GeV]"	    	    );
   theAnalysis_->Hist( "hadronictopmass"     )->GetXaxis()->SetTitle( "hadronic top mass [GeV]"	    	    );
         
   /* MWH */         
   theAnalysis_->Hist( "DiBosonInvMass"        )->GetXaxis()->SetTitle( "M_{G} [GeV]"           	    );

   /* other histos */
   theAnalysis_->Hist( "PUWeights"            )->GetXaxis()->SetTitle( "PU weights"			    );
   theAnalysis_->Hist( "htagweight"           )->GetXaxis()->SetTitle( "h-tag weights"			    );
   theAnalysis_->Hist( "btagvweight"          )->GetXaxis()->SetTitle( "b-tag veto weights"		    );
   theAnalysis_->Hist( "nVertices"            )->GetXaxis()->SetTitle( "# primary vertices"                 );

   
   Utilities::OverflowToLast( theAnalysis_->Hist( "AK8jetPT"  	      ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "AK8jetEta" 	      ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "AK8jetPhi" 	      ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "AK8jetCSV" 	      ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "AK8jetMass"       ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "AK8jetPrunedMass" ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "tau21"	      ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "tau31"	      ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "tau32"	      ) );

   Utilities::OverflowToLast( theAnalysis_->Hist( "leptonPT"          ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "leptonPhi"         ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "leptonEta"         ) );
   
   Utilities::OverflowToLast( theAnalysis_->Hist( "MET" 	      ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "METphi"            ) );

   Utilities::OverflowToLast( theAnalysis_->Hist( "recoWPT"	      ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "recoWMT"	      ) );

   Utilities::OverflowToLast( theAnalysis_->Hist( "nAJets"    	      ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "nAJetsBTag"        ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "AK4jetPt"          ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "AK4jetCSV"         ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "AK4jetMass"        ) );

   Utilities::OverflowToLast( theAnalysis_->Hist( "lepJetDR"	      ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "METJetDphi"        ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "WJetDphi"	      ) );

   Utilities::OverflowToLast( theAnalysis_->Hist( "leptonictopmass"   ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "hadronictopmass"   ) );
   
   //Utilities::OverflowToLast( theAnalysis_->Hist( "DiBosonInvMass"    ) );
   
   Utilities::OverflowToLast( theAnalysis_->Hist( "PUWeights"         ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "nVertices"         ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "htagweight"        ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "btagvweight"       ) );

   /*Utilities::OverflowToLast( theAnalysis_->Hist( "Discriminant"          ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "A"                     ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "B"                     ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "C"                     ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "a"                     ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "pzNu"                  ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "DiBosonInvMassMethod2" ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "DiBosonInvMassDeltam"  ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "DiBosonInvMassDeltap"  ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "NuLeptInvMass"         ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "NuLeptInvMassDeltam"   ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "NuLeptInvMassDeltap"   ) );*/
         
}
