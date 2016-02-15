#include "../ExoDiBosonAnalysis/include/ExoDiBosonAnalysis.h"
#include "../ExoDiBosonAnalysis/include/Utilities.h"
#include "../ExoDiBosonAnalysis/include/HistosManager.h"
#include "../ExoDiBosonAnalysis/include/NtupleManager.h"
#include "../ExoDiBosonAnalysis/include/MatchingTools.h"

#include <iostream>

//==============================================================================================
ClassImp( ExoDiBosonAnalysis );

//==============================================================================================
ExoDiBosonAnalysis::ExoDiBosonAnalysis()
   : SCycleBase()
   , weight_(1.)
   , genweight_(1.)
   , puweight_(1.)
   , hltweight_(1.)
   , btagweight_(1.)
   , lumiweight_(1.){

   SetLogName( GetName() );
   
   /* general settings */   
   DeclareProperty( "InputTreeName"     , InputTreeName_      );
   DeclareProperty( "OutputTreeName"    , OutputTreeName_     );
   DeclareProperty( "isSignal"          , isSignal_	      );
   DeclareProperty( "runOnMC"           , runOnMC_	      );
   DeclareProperty( "GenFilter"         , genFilter_	      );
   DeclareProperty( "Flavour"           , Flavour_	      );
   DeclareProperty( "Channel"           , Channel_	      );
   DeclareProperty( "Trigger"           , Trigger_	      );
   DeclareProperty( "applyFilters"      , applyFilters_	      );
   DeclareProperty( "Synch"             , Synch_  	      );
   DeclareProperty( "JSONfile"          , JSONfile_  	      );

   /* leptonic selections */
   DeclareProperty( "LeptPtCut"         , leptPtCut_	      );
   DeclareProperty( "LeptEtaCut"        , leptEtaCut_	      );
   DeclareProperty( "AleptPtCut"        , AleptPtCut_	      );
   DeclareProperty( "AleptEtaCut"       , AleptEtaCut_	      );
   DeclareProperty( "METCut"            , METCut_	      );
   DeclareProperty( "WptCut"            , WptCut_	      );

   /* jet selections */
   DeclareProperty( "JetPtCutLoose"     , JetPtCutLoose_      );
   DeclareProperty( "JetPtCutTight"     , JetPtCutTight_      );
   DeclareProperty( "JetEtaCut"         , JetEtaCut_	      );
   DeclareProperty( "Tau21Cut"          , Tau21Cut_	      );
   DeclareProperty( "SubjetsBtagWP"     , SubjetsBtagWP_      );
   DeclareProperty( "NsubjBTag"         , NsubjBTag_          );

   /* btag veto */
   DeclareProperty( "nAJetCut"          , nAJetCut_	      );
   DeclareProperty( "BtagVetoWP"        , BtagVetoWP_	      );

   /* back-to-back topology */
   DeclareProperty( "AngularCuts"       , AngularCuts_	      );
      
   /* top mass veto */
   DeclareProperty( "TopMassCut"        , TopMassCut_	      );
   DeclareProperty( "leptTopMassLow"    , leptTopMassLow_     );
   DeclareProperty( "leptTopMassHigh"   , leptTopMassHigh_    );
   DeclareProperty( "hadrTopMassLow"    , hadrTopMassLow_     );
   DeclareProperty( "hadrTopMassHigh"   , hadrTopMassHigh_    );
   
   /* pruned mass */   
   DeclareProperty( "JetMassAlgo"       , JetMassAlgo_	      );
   DeclareProperty( "VetoSR"            , VetoSR_	      );
   DeclareProperty( "mLow"              , mLow_  	      );
   DeclareProperty( "mHigh"             , mHigh_ 	      );

   /* WW mass window */
   DeclareProperty( "WWMass"            , WWMass_	      );

   /* weights settings */
   DeclareProperty( "xSec"              , xSec_  	      );
   DeclareProperty( "genEvents"         , genEvents_	      );
   DeclareProperty( "Lumi"              , Lumi_  	      );
   DeclareProperty( "PUdata"            , PUProfileData_      );
   DeclareProperty( "BTagEff4vetoData"  , BTagEff4vetoData_   );
   DeclareProperty( "BTagEff4fatjetData", BTagEff4fatjetData_ );
   DeclareProperty( "BTagEff4subjetData", BTagEff4subjetData_ );
      
   /* systematics */
   DeclareProperty( "BtagSFSysUpVeto"          , BtagSFSysUpVeto_	    );
   DeclareProperty( "BtagSFSysDownVeto"        , BtagSFSysDownVeto_	    );
   DeclareProperty( "BtagSFSysUp"              , BtagSFSysUp_		    );
   DeclareProperty( "BtagSFSysDown"            , BtagSFSysDown_ 	    );
   DeclareProperty( "ScaleMuonUpDown"          , ScaleMuonUpDown_	    );
   DeclareProperty( "ScalePrunedMassResidual"  , ScalePrunedMassResidual_   );
   DeclareProperty( "ScalePrunedMassUp"        , ScalePrunedMassUp_	    );
   DeclareProperty( "ScalePrunedMassDown"      , ScalePrunedMassDown_	    );
   DeclareProperty( "JetMassResolutionUpDown"  , JetMassResolutionUpDown_   );
   DeclareProperty( "JetEnergyResolutionUpDown", JetEnergyResolutionUpDown_ );
   DeclareProperty( "ScaleJESUp"               , ScaleJESUp_		    );
   DeclareProperty( "ScaleJESDown"             , ScaleJESDown_  	    );
   DeclareProperty( "JMRSigmaMCPTData"         , JMRSigmaMCPTData_	    );
   DeclareProperty( "JERSigmaMCPTData"         , JERSigmaMCPTData_	    );
                      
   theHistosManager_ = new HistosManager( this );
   theNtupleManager_ = new NtupleManager( this );
   
   /* old b-tag working point */
   //bTagWPmap_["CSVL"] = 0.244;
   //bTagWPmap_["CSVM"] = 0.814;
   //bTagWPmap_["CSVT"] = 0.898;  

   bTagWPmap_["CSVL"] = 0.605;
   bTagWPmap_["CSVM"] = 0.890;
   bTagWPmap_["CSVT"] = 0.970;
   
   jetIndex_ = -1;  
   tr_ = new TRandom3(0);      
     
}

//==============================================================================================
ExoDiBosonAnalysis::~ExoDiBosonAnalysis() {
   
   if( theHistosManager_ ){
      delete theHistosManager_;
      theHistosManager_ = 0;
   }
   
   if( theNtupleManager_ ){
      delete theNtupleManager_;
      theNtupleManager_ = 0;
   }
      
}

//==============================================================================================
void ExoDiBosonAnalysis::BeginCycle() throw( SError ) {

   initWeight();    

   if( Tau21Cut_ == "HP" ){ Tau21Low_ = 0.; Tau21High_ = 0.6; }
   else if( Tau21Cut_ == "LP" ){ Tau21Low_ = 0.6; Tau21High_ = 0.75; }
   else{ Tau21Low_ = 0.; Tau21High_ = 1.; }

   if( !runOnMC_ && JSONfile_ != "" ){;
    m_logger << INFO << "Loading GoodRunsList from file: " << JSONfile_ << SLogger::endmsg;
    Root::TGoodRunsListReader reader( TString( JSONfile_.c_str() ) );
    if( ! reader.Interpret() ) {
      m_logger << FATAL << "Couldn't read in the GRL!" << SLogger::endmsg;
      throw SError( ( "Couldn't read in file: " + JSONfile_ ).c_str(), SError::SkipCycle );
    }
    m_grl = reader.GetMergedGoodRunsList();
    m_grl.Summary();
    m_grl.SetName( "MyGoodRunsList" );

    //
    // Add it as a configuration object, so that the worker nodes will receive it:
    //
    AddConfigObject( &m_grl );
   }
                          
   return;

}
//==============================================================================================
void ExoDiBosonAnalysis::initWeight( void ){

   PUWeight::Scenario sc = PUWeight_.toScenario("PU2015_25ns");
   PUWeight_.initPUWeights(PUProfileData_,sc); 

   HLTWeight::Channel ch = HLTWeight_.toChannel(Channel_);
   HLTWeight_.initHLTWeights(ch);
   
   BTagWeight_.initBTagWeights(BTagEff4vetoData_,BTagEff4fatjetData_,BTagEff4subjetData_);
   
   //TFile* fPUweights = TFile::Open(PUProfileData_.c_str(),"READ");
   //hPUweights_ = (TH1F*)fPUweights->Get("puweights");
   
   TFile* fJMRSigmaMCPTData = TFile::Open(JMRSigmaMCPTData_.c_str(),"READ");
   hJMRSigmaMCPT_ = (TH1F*)fJMRSigmaMCPTData->Get("sigmaMC");

   TFile* fJERSigmaMCPTData = TFile::Open(JERSigmaMCPTData_.c_str(),"READ");
   hJERSigmaMCPT_ = (TH1F*)fJERSigmaMCPTData->Get("sigmaMC");
      
}

//==============================================================================================
void ExoDiBosonAnalysis::BeginInputFile( const SInputData& ) throw( SError ) {

   theNtupleManager_->ConnectVariables( InputTreeName_, runOnMC_ );
         
   return;
}

//==============================================================================================
void ExoDiBosonAnalysis::BeginInputData( const SInputData& ) throw( SError ) {

   if( !runOnMC_ ) {
    TObject* grl;
    if( ! ( grl = GetConfigObject( "MyGoodRunsList" ) ) ) {
      m_logger << FATAL << "Can't access the GRL!" << SLogger::endmsg;
      throw SError( "Can't access the GRL!", SError::SkipCycle );
    }
    m_grl = *( dynamic_cast< Root::TGoodRunsList* >( grl ) );
   }
  
   nEvents_                 = 0;
   nPassedFilters_          = 0;
   nPassedTrigger_          = 0;	   
   nPassedFoundLept_        = 0;
   nPassedVetoExtraLeptons_ = 0;	   
   nPassedFoundMET_         = 0;	   
   nPassedFoundW_           = 0;	   
   nPassedFoundJet_         = 0;	   
   nPassedLepJetDR_         = 0;	   
   nPassedJetPtTight_       = 0;	   
   nPassedAJetCut_          = 0;	   
   nPassedLepJetDR2_        = 0;	   
   nPassedMETJetDPhi_       = 0;	   
   nPassedJetWDPhi_         = 0;	   
   nPassedTopMass_          = 0;	   
   nPassedJetMass_          = 0;
   nPassedTau21Cut_   	    = 0;  
   nPassedNsubjBTagCut_     = 0;  
   nPassedExoCandidateMass_ = 0;
   nPassedJetsDEta_         = 0;
   nPassedFoundJets_        = 0;
   nPassedMjj_              = 0;  
   
   nPassedFilter_HBHE_                = 0;
   nPassedFilter_HBHEIso_             = 0;
   nPassedFilter_CSCHalo_             = 0;
   nPassedFilter_HCALlaser_           = 0;
   nPassedFilter_ECALDeadCell_        = 0;
   nPassedFilter_GoodVtx_             = 0;
   nPassedFilter_TrkFailure_          = 0;
   nPassedFilter_EEBadSc_             = 0;
   nPassedFilter_ECALlaser_           = 0;
   nPassedFilter_TrkPOG_              = 0;
   nPassedFilter_TrkPOG_manystrip_    = 0;
   nPassedFilter_TrkPOG_toomanystrip_ = 0;
   nPassedFilter_TrkPOG_logError_     = 0;
   nPassedFilter_METFilters_          = 0;
   nPassedMETFiltersAll_              = 0;
   nPassedTrkFiltersAll_              = 0;
   nPassedGoodPVFilter_               = 0;

   sumGenWeights_ = 0;
              
   if( Synch_ ){  

      Book( TH1F( "Event", "event", 30000, 0, 30000));

      theHistosManager_->bookHistos();    
   
      /* for synch */
      DeclareVariable( run		, "run" 	     , OutputTreeName_.c_str() );
      DeclareVariable( event		, "event"	     , OutputTreeName_.c_str() );
      DeclareVariable( lumi		, "lumi"	     , OutputTreeName_.c_str() );
      DeclareVariable( nPV		, "nPV" 	     , OutputTreeName_.c_str() );
      DeclareVariable( pfMET		, "pfMET"	     , OutputTreeName_.c_str() );
      DeclareVariable( pfMETPhi 	, "pfMETPhi"	     , OutputTreeName_.c_str() );
      DeclareVariable( nLooseEle	, "nLooseEle"	     , OutputTreeName_.c_str() );
      DeclareVariable( nLooseMu 	, "nLooseMu"	     , OutputTreeName_.c_str() );
      DeclareVariable( l_pt		, "l_pt"	     , OutputTreeName_.c_str() );
      DeclareVariable( l_eta		, "l_eta"	     , OutputTreeName_.c_str() );
      DeclareVariable( l_phi		, "l_phi"	     , OutputTreeName_.c_str() );
      DeclareVariable( jet_pt		, "jet_pt"	     , OutputTreeName_.c_str() );
      DeclareVariable( jet_eta  	, "jet_eta"	     , OutputTreeName_.c_str() );
      DeclareVariable( jet_phi  	, "jet_phi"	     , OutputTreeName_.c_str() );
      DeclareVariable( jet_mass_pruned  , "jet_mass_pruned"  , OutputTreeName_.c_str() );
      DeclareVariable( jet_mass_softdrop, "jet_mass_softdrop", OutputTreeName_.c_str() );
      DeclareVariable( jet_tau2tau1	, "jet_tau2tau1"     , OutputTreeName_.c_str() );
      DeclareVariable( W_pt		, "W_pt"	     , OutputTreeName_.c_str() );
      DeclareVariable( W_eta		, "W_eta"	     , OutputTreeName_.c_str() );
      DeclareVariable( W_phi		, "W_phi"	     , OutputTreeName_.c_str() );
      DeclareVariable( m_lvj		, "m_lvj"	     , OutputTreeName_.c_str() );
      DeclareVariable( njets		, "njets"	     , OutputTreeName_.c_str() );
      DeclareVariable( nbtag		, "nbtag"	     , OutputTreeName_.c_str() );
      DeclareVariable( jet2_pt  	, "jet2_pt"	     , OutputTreeName_.c_str() );
      DeclareVariable( jet2_btag	, "jet2_btag"	     , OutputTreeName_.c_str() );
      DeclareVariable( jet3_pt  	, "jet3_pt"	     , OutputTreeName_.c_str() );
      DeclareVariable( jet3_btag	, "jet3_btag"	     , OutputTreeName_.c_str() );
      DeclareVariable( weight_	   	, "weight"           , OutputTreeName_.c_str() );
   }
   else{

      theHistosManager_->bookHistos();    

      DeclareVariable( run		 , "run"	      , OutputTreeName_.c_str() );
      DeclareVariable( event		 , "event"	      , OutputTreeName_.c_str() );
      DeclareVariable( lumi		 , "lumi"	      , OutputTreeName_.c_str() );	
      DeclareVariable( weight_	   	 , "weight"	       , OutputTreeName_.c_str() );
      DeclareVariable( puweight_   	 , "puweight"	       , OutputTreeName_.c_str() );
      DeclareVariable( hltweight_  	 , "hltweight"         , OutputTreeName_.c_str() );
      DeclareVariable( lumiweight_ 	 , "lumiweight"        , OutputTreeName_.c_str() );
      DeclareVariable( btagweight_ 	 , "btagweight"        , OutputTreeName_.c_str() );
      DeclareVariable( genweight_ 	 , "genweight"         , OutputTreeName_.c_str() );
      DeclareVariable( channel     	 , "channel"	       , OutputTreeName_.c_str() );
      DeclareVariable( MWWmethod2        , "MWW"	       , OutputTreeName_.c_str() );
      DeclareVariable( jet_mass          , "jet_mass"	       , OutputTreeName_.c_str() );
      DeclareVariable( jet_mass_pruned   , "Mjpruned"	       , OutputTreeName_.c_str() );
      DeclareVariable( jet1_mass_pruned  , "Mjpruned_1"	       , OutputTreeName_.c_str() );
      DeclareVariable( jet2_mass_pruned  , "Mjpruned_2"	       , OutputTreeName_.c_str() );
      DeclareVariable( jet_mass_softdrop , "Mjsoftdrop"        , OutputTreeName_.c_str() );
      DeclareVariable( jet_pt            , "Whadr_pt"	       , OutputTreeName_.c_str() );
      DeclareVariable( jet_eta           , "Whadr_eta"         , OutputTreeName_.c_str() );
      DeclareVariable( jet_phi           , "Whadr_phi"         , OutputTreeName_.c_str() );
      DeclareVariable( jet_tau2tau1      , "tau21"	       , OutputTreeName_.c_str() );
      DeclareVariable( jet1_tau2tau1      , "tau21_1"	       , OutputTreeName_.c_str() );
      DeclareVariable( jet2_tau2tau1      , "tau21_2"	       , OutputTreeName_.c_str() );
      DeclareVariable( l_pt         	 , "lept_pt"	       , OutputTreeName_.c_str() );
      DeclareVariable( l_eta     	 , "lept_eta"	       , OutputTreeName_.c_str() );
      DeclareVariable( l_phi          	 , "lept_phi"	       , OutputTreeName_.c_str() );
      DeclareVariable( l_iso         	 , "lept_iso"	       , OutputTreeName_.c_str() );
      DeclareVariable( isGlobalMuon      , "isGlobalMuon"      , OutputTreeName_.c_str() ); 
      DeclareVariable( globalHits        , "globalHits"        , OutputTreeName_.c_str() );
      DeclareVariable( pixelHits         , "pixelHits"	       , OutputTreeName_.c_str() );
      DeclareVariable( trackerHits       , "trackerHits"       , OutputTreeName_.c_str() );
      DeclareVariable( matchedStations   , "matchedStations"   , OutputTreeName_.c_str() );
      DeclareVariable( bestTrack_ptErrRel, "bestTrack_ptErrRel", OutputTreeName_.c_str() );
      DeclareVariable( d0	         , "d0" 	       , OutputTreeName_.c_str() );
      DeclareVariable( dz	         , "dz" 	       , OutputTreeName_.c_str() );
      DeclareVariable( Wlept_pt          , "Wlept_pt"	       , OutputTreeName_.c_str() ); 
      DeclareVariable( Wlept_mt          , "Wlept_mt"	       , OutputTreeName_.c_str() );
      DeclareVariable( pfMET             , "met"	       , OutputTreeName_.c_str() );
      DeclareVariable( pfMETPhi          , "met_phi"	       , OutputTreeName_.c_str() );
      DeclareVariable( ltopmass          , "ltopmass"	       , OutputTreeName_.c_str() );
      DeclareVariable( htopmass          , "htopmass"	       , OutputTreeName_.c_str() );
      DeclareVariable( issignal          , "issignal"	       , OutputTreeName_.c_str() );
      DeclareVariable( dr_lepjet  	 , "dr_lepjet"         , OutputTreeName_.c_str() );
      DeclareVariable( dphi_metjet	 , "dphi_metjet"       , OutputTreeName_.c_str() );
      DeclareVariable( dphi_jetw  	 , "dphi_jetw"         , OutputTreeName_.c_str() );
      DeclareVariable( nPVs     	 , "nPVs"	       , OutputTreeName_.c_str() );
      DeclareVariable( nsubj     	 , "nsubj"	       , OutputTreeName_.c_str() );
      DeclareVariable( nsubjbtag     	 , "nsubjbtag"         , OutputTreeName_.c_str() );
      DeclareVariable( nsubjbtagM     	 , "nsubjbtagM"        , OutputTreeName_.c_str() );
      DeclareVariable( subj1csv     	 , "subj1csv"	       , OutputTreeName_.c_str() );  		    
      DeclareVariable( subj2csv     	 , "subj2csv"	       , OutputTreeName_.c_str() );
      DeclareVariable( subj1flavor     	 , "subj1flavor"       , OutputTreeName_.c_str() );
      DeclareVariable( subj2flavor    	 , "subj2flavor"       , OutputTreeName_.c_str() );
      DeclareVariable( subj1eta     	 , "subj1eta"	       , OutputTreeName_.c_str() );
      DeclareVariable( subj2eta    	 , "subj2eta"	       , OutputTreeName_.c_str() );
      DeclareVariable( subj1pt     	 , "subj1pt"	       , OutputTreeName_.c_str() );
      DeclareVariable( subj2pt    	 , "subj2pt"	       , OutputTreeName_.c_str() );
      DeclareVariable( nak4jets    	 , "nak4jets"	       , OutputTreeName_.c_str() );
      DeclareVariable( ak4jet1_csv    	 , "ak4jet1_csv"       , OutputTreeName_.c_str() );
      DeclareVariable( ak4jet1_pt    	 , "ak4jet1_pt"        , OutputTreeName_.c_str() );
      DeclareVariable( ak4jet2_csv    	 , "ak4jet2_csv"       , OutputTreeName_.c_str() );
      DeclareVariable( ak4jet2_pt    	 , "ak4jet2_pt"        , OutputTreeName_.c_str() );
      DeclareVariable( ak4jet3_csv    	 , "ak4jet3_csv"       , OutputTreeName_.c_str() );
      DeclareVariable( ak4jet3_pt    	 , "ak4jet3_pt"        , OutputTreeName_.c_str() );
   }
   
   return;

}

//==============================================================================================
void ExoDiBosonAnalysis::initData( void ){

   data_ = theNtupleManager_->getData();
      
}

//==============================================================================================
void ExoDiBosonAnalysis::reset( void ){

   genCandidates_.clear();
   leptonCand_   .clear();
   AK4jetCand_   .clear();
   fatJetCand_   .clear();
   METCand_      .clear();
   WCand_        .clear();
   SubjetCand_   .clear();
   
}

//==============================================================================================
void ExoDiBosonAnalysis::setGenCandidates( void ) {

   if( !runOnMC_ ) return;
   if( !isSignal_ && !genFilter_ ) return;

   TLorentzVector genP;   
   double genptV = -99;
   for( unsigned int p = 0; p < (data_.genParticle_pdgId)->size(); ++p ){
      if( (*data_.genParticle_status)[p] != 4 && (*data_.genParticle_status)[p] != 22 && (*data_.genParticle_status)[p] != 23 && (*data_.genParticle_status)[p] != 1) continue;
      //if( (*data_.genParticle_status)[p] != 3 ) continue;
      genP.SetPtEtaPhiM( (*data_.genParticle_pt)[p], (*data_.genParticle_eta)[p], (*data_.genParticle_phi)[p], (*data_.genParticle_e)[p] );
      genCandidates_[(*data_.genParticle_pdgId)[p]] = genP;  
   }
                    
   return;
}

//==============================================================================================
bool ExoDiBosonAnalysis::selectChannel( void ){

    if( !runOnMC_ ) return true;
    if( !genFilter_ ) return true;  
	     
    bool foundMu  = false;
    bool foundEle = false;
    bool foundTau = false;
    int  nMus = 0;
    int  nEles = 0;
    int  nTaus = 0;
    for( unsigned int p = 0; p < (data_.genParticle_pdgId)->size(); ++p ){
    
       if( (*data_.genParticle_status)[p] != 4 && (*data_.genParticle_status)[p] != 22 && (*data_.genParticle_status)[p] != 23 ) continue;
       
       if( abs((*data_.genParticle_pdgId)[p]) == 13 ){
          for( unsigned int m = 0; m < (*data_.genParticle_mother)[p].size(); ++m ){
             if( abs((*data_.genParticle_mother)[p][m]) == 24 || abs((*data_.genParticle_mother)[p][m]) == 23 ){
        	foundMu = true;
		nMus++;
        	break;
             }  				     
          }
       }
       if( abs((*data_.genParticle_pdgId)[p]) == 11 ){
          for( unsigned int m = 0; m < (*data_.genParticle_mother)[p].size(); ++m ){
             if( abs((*data_.genParticle_mother)[p][m]) == 24 || abs((*data_.genParticle_mother)[p][m]) == 23 ){
        	foundEle = true;
		nEles++;
        	break;
             }  				     
          }
       }
       if( abs((*data_.genParticle_pdgId)[p]) == 15 ){
          for( unsigned int m = 0; m < (*data_.genParticle_mother)[p].size(); ++m ){
             if( abs((*data_.genParticle_mother)[p][m]) == 24 || abs((*data_.genParticle_mother)[p][m]) == 23 ){
	        foundTau = true;
		nTaus++;
        	break;
             }  				     
          }
       }       																														  
   } 
   
   if( Channel_ == "muon" && (!foundMu || nMus > 1) ) return false;     

   if( Channel_ == "electron" && (!foundEle || nEles > 1) ) return false;

   if( Channel_ == "tau" && (!foundTau || nTaus > 1) ) return false;
            
   return true;   
   
}

//==============================================================================================
void ExoDiBosonAnalysis::setWeight( TString infile ){

   if( !runOnMC_ ) return;

   for( unsigned int v = 0; v < (data_.nPUTrue)->size(); ++v ){
      if( (*data_.bX)[v] == 0 ) puweight_ = PUWeight_.getPUWeight( (*data_.nPUTrue)[v] );
   }
  
   //if( data_.nPVs <= 50 ){
   //   int bin = hPUweights_->GetXaxis()->FindBin(data_.nPVs);
   //   puweight_ = hPUweights_->GetBinContent(bin); 
   //} 
   
   if( Channel_.find("mu") != std::string::npos )
    hltweight_ = HLTWeight_.getHLTWeight( leptonCand_[0].p4.Pt(), leptonCand_[0].p4.Eta() );
             
   double lumiw = xSec_/genEvents_;
      
   lumiweight_ = lumiw*LumiWeight_.getLumiWeight( infile )*Lumi_;
         
   btagvetow = 1.; 
   htagw = 1.;
   
   //if( BtagSFSysUpVeto_ ) btagvetow = BTagWeight_.getBTagSFWeightUp( AK4jetCand_, "veto" ); 
   //else if( BtagSFSysDownVeto_ ) btagvetow = BTagWeight_.getBTagSFWeightDown( AK4jetCand_, "veto" ); 
   //else btagvetow = BTagWeight_.getBTagWeight( AK4jetCand_, "veto" );
   if( NsubjBTag_ != -1 ){ 
   if( BtagSFSysUp_ ){

      //btagvetow = BTagWeight_.getBTagWeight( AK5jetCand_, "veto" );
      htagw = BTagWeight_.getBTagSFWeightUp( SubjetCand_[0], "subjet" );

   }
   else if( BtagSFSysDown_ ){

      //btagvetow = BTagWeight_.getBTagWeight( AK5jetCand_, "veto" );
      htagw = BTagWeight_.getBTagSFWeightDown( SubjetCand_[0], "subjet" );

   }
   else{

      //btagvetow = BTagWeight_.getBTagWeight( AK5jetCand_, "veto" );
      //htagw = BTagWeight_.getBTagWeight( SubjetCand_[0], "subjet" );
      htagw = 1.;

   }
   }

      
   if( nAJetCut_ == -1 ) btagvetow = 1.;

   btagweight_ =  btagvetow*htagw;
   
   genweight_ = data_.genWeight < 0 ? -1 : 1;
         
   weight_ = genweight_*puweight_*lumiweight_*hltweight_*btagweight_;

   //std::cout << "pu w " << puweight_ << " hlt w " << hltweight_ << " btag w " << btagweight_ << " lumi w " << lumiweight_;
   //std::cout << " tot w " << weight_ << std::endl; 
   
}

//==============================================================================================
void ExoDiBosonAnalysis::ExecuteEvent( const SInputData&, Double_t ) throw( SError ) {
      
   initData();      
   reset();         
   setGenCandidates(); 
     
   int gW = data_.genWeight < 0 ? -1 : 1;
   sumGenWeights_+=gW;
            	
   if( !selectChannel() ) throw SError( SError::SkipEvent );
   nEvents_++;
   
   Hist( "runNumber" )->Fill(data_.EVENT_run);
   
   //if( data_.EVENT_event != 1278 ) return;
   //std::cout << "************ FOUND EVENT " << data_.EVENT_event << std::endl;
   //TriggerEfficiency();
   //FiltersEfficiency();
   //doPileUp();
   //METnoHF();
   //return;
   
   if( !applyJSON() ) throw SError( SError::SkipEvent ); 
   
   if( !passedFilters() ) throw SError( SError::SkipEvent );  
   nPassedFilters_++;
   
   if( !passedTrigger() ) throw SError( SError::SkipEvent );  
   nPassedTrigger_++;   
   
   bool DEBUGgen = false;
   
   if( DEBUGgen ){
      std::cout << "====================================" << std::endl;
      for( unsigned int p = 0; p < (data_.genParticle_pdgId)->size(); ++p ){
            //if( (*data_.genParticle_status)[p] != 4 && (*data_.genParticle_status)[p] != 22 && (*data_.genParticle_status)[p] != 23 ) continue;
            //if( (*data_.genParticle_status)[p] != 3 ) continue;
            std::cout << " gen particle: " << (*data_.genParticle_pdgId)[p] << " status " << (*data_.genParticle_status)[p] << std::endl;
            std::cout << "    - mothers: ";
            for( unsigned int m = 0; m < (*data_.genParticle_mother)[p].size(); ++m ) std::cout << (*data_.genParticle_mother)[p][m] << ",";
            std::cout << std::endl;
            std::cout << "    - daughters: ";
            for( unsigned int d = 0; d < (*data_.genParticle_dau)[p].size(); ++d ) std::cout << (*data_.genParticle_dau)[p][d] << ",";     
            std::cout << std::endl;
      }
   }

   TString infile = TString(this->GetHistInputFile()->GetName());	           
   if(  Channel_ != "dijet" && passedSelections() ){

       if( Synch_ ){ run4Synch(); TString infile = TString(this->GetHistInputFile()->GetName()); setWeight(infile);}
       else{
       	  
	  /*std::cout << "************ FOUND EVENT " << data_.EVENT_event << " LUMI " << data_.EVENT_lumi << " RUN " << data_.EVENT_run;
          std::cout << " MWW " << MWWmethod2 << " lepton pt " << leptonCand_[0].p4.Pt() << " eta " << leptonCand_[0].p4.Eta() << " phi " << leptonCand_[0].p4.Phi();
	  std::cout << " jet pt " << fatJetCand_[0].p4.Pt() << " eta " << fatJetCand_[0].p4.Eta() << " phi " << fatJetCand_[0].p4.Phi();
	  std::cout << " pruned jet mass " << fatJetCand_[0].prunedMass << " jet mass " << fatJetCand_[0].p4.M();
	  std::cout << " MET " << METCand_[0].p4.Pt() << " met phi " << METCand_[0].p4.Phi() << " Wlept pt " << WCand_[0].p4.Pt();
	  std::cout << " lepJetDR " << leptonCand_[0].p4.DeltaR(fatJetCand_[0].p4);
	  std::cout << " METJetDPhi " << fabs(METCand_[0].p4.DeltaPhi(fatJetCand_[0].p4));
	  std::cout << " JetWDPhi " << fabs(fatJetCand_[0].p4.DeltaPhi(WCand_[0].p4)) << std::endl;*/ 
	  setWeight(infile);       
          fillHistos();          
          fillTree();	
              	       
        }
   }      
   else if( Channel_ == "dijet" && passedDijetSelections() ){
     setWeight(infile);
     fillDijetTree();   
   }
   else 
      throw SError( SError::SkipEvent );
         
   return;

}

//==============================================================================================
bool ExoDiBosonAnalysis::applyJSON( void ){

   if( runOnMC_ || JSONfile_ == "" ) return true;
   return m_grl.HasRunLumiBlock( data_.EVENT_run, data_.EVENT_lumi );

   //bool isGood = m_grl.HasRunLumiBlock( data_.EVENT_run, data_.EVENT_lumi );
   //if( !isGood ) m_logger << DEBUG << "Bad event! Run: " << data_.EVENT_run <<  " - Lumi Section: " << data_.EVENT_lumi << SLogger::endmsg;
   //else m_logger << DEBUG << "Good event! Run: " << data_.EVENT_run <<  " - Lumi Section: " << data_.EVENT_lumi << SLogger::endmsg;

}

//==============================================================================================
bool ExoDiBosonAnalysis::passedFilters( void ){
     
   if( data_.PV_filter ) nPassedGoodPVFilter_++;
   else return false;
   
   if( !applyFilters_ ) return true;

   //if( data_.PV_filter                       ) nPassedGoodPVFilter_++;       
   if( data_.passFilter_HBHELoose_           ) nPassedFilter_HBHE_++;
   if( data_.passFilter_HBHEIso_             ) nPassedFilter_HBHEIso_++;
   if( data_.passFilter_CSCHalo_             ) nPassedFilter_CSCHalo_++;
   if( data_.passFilter_HCALlaser_	     ) nPassedFilter_HCALlaser_++;
   if( data_.passFilter_ECALDeadCell_        ) nPassedFilter_ECALDeadCell_++;
   if( data_.passFilter_GoodVtx_	     ) nPassedFilter_GoodVtx_++;
   if( data_.passFilter_TrkFailure_	     ) nPassedFilter_TrkFailure_++;
   if( data_.passFilter_EEBadSc_	     ) nPassedFilter_EEBadSc_++;
   if( data_.passFilter_ECALlaser_           ) nPassedFilter_ECALlaser_++;
   if( data_.passFilter_TrkPOG_              ) nPassedFilter_TrkPOG_++;
   if( data_.passFilter_TrkPOG_manystrip_    ) nPassedFilter_TrkPOG_manystrip_++;
   if( data_.passFilter_TrkPOG_toomanystrip_ ) nPassedFilter_TrkPOG_toomanystrip_++;
   if( data_.passFilter_TrkPOG_logError_     ) nPassedFilter_TrkPOG_logError_++;
   if( data_.passFilter_METFilters_	     ) nPassedFilter_METFilters_++;
   //if( isGood ) nPassedFilter_EventList_++;          
   
   //bool passMETFiltersAll = data_.passFilter_HBHE_ && data_.passFilter_CSCHalo_ && data_.passFilter_HCALlaser_;
   bool passMETFiltersAll = data_.passFilter_CSCHalo_ && data_.passFilter_HCALlaser_;
   passMETFiltersAll = passMETFiltersAll && data_.passFilter_ECALDeadCell_ && data_.passFilter_GoodVtx_ && data_.passFilter_TrkFailure_;
   passMETFiltersAll = passMETFiltersAll && data_.passFilter_EEBadSc_ && data_.passFilter_ECALlaser_ && data_.passFilter_TrkPOG_;
   
   bool passTrkFiltersAll = data_.passFilter_TrkPOG_manystrip_ && data_.passFilter_TrkPOG_toomanystrip_ && data_.passFilter_TrkPOG_logError_;
      
   if( passMETFiltersAll ) nPassedMETFiltersAll_++;
   if( passTrkFiltersAll ) nPassedTrkFiltersAll_++;
   
   bool passAllfilters = data_.passFilter_HBHELoose_ && data_.passFilter_HBHEIso_ && data_.passFilter_CSCHalo_ && data_.PV_filter && data_.passFilter_EEBadSc_;
   if( passAllfilters ) return true;
   
   return false;    

}

//==============================================================================================
bool ExoDiBosonAnalysis::passedTrigger( void ){

   if( runOnMC_ && !Trigger_ ) return true;

   std::vector<std::string> trignames;
   if( Channel_.find("mu") != std::string::npos ){
      trignames.push_back("HLT_Mu45_eta2p1");
      trignames.push_back("HLT_Mu50");
   }
   else if( Channel_.find("el") != std::string::npos ){
      trignames.push_back("HLT_Ele105_CaloIdVT_GsfTrkIdT");
      trignames.push_back("HLT_Ele115_CaloIdVT_GsfTrkIdT");
   }
   else if( Channel_ == "dijet" ){
      //Dijet triggers
      trignames.push_back("AK8PFJet360_TrimMass30") ;
      trignames.push_back("AK8PFHT700_TrimR0p1PT0p03Mass50") ;
      // trignames.push_back("AK8DiPFJet280_200_TrimMass30_BTagCSV0p45") ;
      trignames.push_back("PFHT650_WideJetMJJ950DEtaJJ1p5") ;
      trignames.push_back("PFHT650_WideJetMJJ900DEtaJJ1p5") ;
      trignames.push_back("PFHT800_v") ;
   }
   
   bool isfired = false;
   for( std::map<std::string,bool>::iterator it = (data_.HLT_isFired)->begin(); it != (data_.HLT_isFired)->end(); ++it){
      for( unsigned int t = 0; t < trignames.size(); ++t ){
         if( (it->first).find(trignames[t]) != std::string::npos && it->second ) isfired = true;
      }
   }

   return isfired;
    
}

//==============================================================================================
bool ExoDiBosonAnalysis::passedDijetSelections( void ){
   
  bool foundTwoJets	= false;
  bool passedDeltaEtaCut = false;
  bool passedMjjCut	= false;
  bool passedGroomedMassCut	= false;
  bool passedWTag = false;
	
  //Make sure events contains two AK8 jets passing loose requirements
  if( findJetCandidates() ) foundTwoJets = true;
  if( !foundTwoJets) return false;
  nPassedFoundJets_++;
  
  //Only select jets separated by |DeltaEta| < cut
  float jetsDeltaEta = fabs( fatJetCand_.at(0).p4.Eta()  - fatJetCand_.at(1).p4.Eta() ) ; 
  if (jetsDeltaEta <= 1.3) passedDeltaEtaCut = true;	
  if( !passedDeltaEtaCut ) return false;  
  nPassedJetsDEta_++;
    
  if ( ( fatJetCand_.at(0).p4 + fatJetCand_.at(1).p4 ).M() >= 1000. ) passedMjjCut = true;    
  if( !passedMjjCut ) return false;   
  nPassedMjj_++;     

  //std::cout << "FINALLY IS -->  Jet1 pt " << fatJetCand_.at(0).p4.Pt() << " pruned mass " << fatJetCand_.at(0).prunedMass;
  //std::cout << " Jet2 pt " <<  fatJetCand_.at(1).p4.Pt() << " pruned mass " << fatJetCand_.at(1).prunedMass;
  if( fatJetCand_.at(0).prunedMass > mLow_ && fatJetCand_.at(0).prunedMass <= mHigh_ &&
      fatJetCand_.at(1).prunedMass > mLow_ && fatJetCand_.at(1).prunedMass <= mHigh_ ) passedGroomedMassCut = true;

  if( !passedGroomedMassCut ) return false;
  nPassedJetMass_++;
  
  // //Apply selection
  if ( foundTwoJets && passedDeltaEtaCut && passedMjjCut && passedGroomedMassCut) return true;
  else
    return false;   

}

//==============================================================================================
bool ExoDiBosonAnalysis::passedSelections( void ){
   
   issignal = false;
   /*************************************************************/
   bool foundLept = false;
  
   if( findLeptonCandidate() ) foundLept = true; 

   if( !foundLept ) return false;
   nPassedFoundLept_++;

   if( ( foundAMu_+foundAEle_ ) > 0 ) return false; 
   nPassedVetoExtraLeptons_++;

   /*************************************************************/
   bool foundMET = false;
   
   if( findMETCandidate() ){ 
      if( METCand_[0].p4.Pt() > METCut_ )foundMET = true;
   } 

   if( !foundMET ) return false;   
   nPassedFoundMET_++;
 
   /*************************************************************/  
   bool foundW = false;
   
   if( foundLept && foundMET && findWCandidate() ){ 
      if( WCand_[0].p4.Pt() > WptCut_ ) foundW = true;
   } 

   if( !foundW ) return false;   
   nPassedFoundW_++;
    
   /*************************************************************/
   bool foundJet1 = false;
   bool foundJet2 = false;
   bool foundJet3 = false;

   if( foundLept /*&& findJetCandidateNoJEC()*/ && findJetCandidate() ){
      foundJet1 = true;
      if( leptonCand_[0].p4.DeltaR(fatJetCand_[0].p4) > 1.0 ) foundJet2 = true;
      if( fatJetCand_[0].p4.Pt() > JetPtCutTight_ ) foundJet3 = true;
   }
 
   if( !foundJet1 ) return false;
   nPassedFoundJet_++;
   
   if( !foundJet2 ) return false;   
   nPassedLepJetDR_++;

   if( !foundJet3 ) return false;      
   nPassedJetPtTight_++;
        
   /*************************************************************/
   findExtraJets();
            
   bool najetCut = false; 
   int najet = 0;
   for( unsigned int j = 0; j < AK4jetCand_.size(); j++ ){
      if( AK4jetCand_[j].csv > bTagWPmap_[BtagVetoWP_] ) najet++;
   }
   
   if( (Channel_.find("ttbar") == std::string::npos && najet <= nAJetCut_) ||
       (Channel_.find("ttbar") != std::string::npos && najet  > nAJetCut_) ) najetCut = true;
   
   if( nAJetCut_ != -1 && !najetCut ) return false;
   nPassedAJetCut_++;    
    
   /*************************************************************/            
   bool lepJetDR = false;
   if( foundLept && foundJet1 && leptonCand_[0].p4.DeltaR(fatJetCand_[0].p4) > TMath::Pi()/2. ) lepJetDR = true;
        
   if( AngularCuts_ && !lepJetDR ) return false;
   if( lepJetDR )
      nPassedLepJetDR2_++;
          
   /*************************************************************/      
   bool METJetDPhi = false;
   if( foundMET && foundJet1 && fabs(METCand_[0].p4.DeltaPhi(fatJetCand_[0].p4)) > 2. ) METJetDPhi = true;
    
   if( AngularCuts_ && !METJetDPhi ) return false;
     if( METJetDPhi )
      nPassedMETJetDPhi_++;
         
   /*************************************************************/         
   bool JetWDPhi = false;
   if( foundW && foundJet1 && fabs(fatJetCand_[0].p4.DeltaPhi(WCand_[0].p4)) > 2. ) JetWDPhi = true;

   if( AngularCuts_ && !JetWDPhi ) return false;
   if( JetWDPhi ) 
      nPassedJetWDPhi_++; 
      
   if( lepJetDR && METJetDPhi && JetWDPhi ) issignal = true;
   
   if( foundLept && foundJet1 ) dr_lepjet = leptonCand_[0].p4.DeltaR(fatJetCand_[0].p4);
   if( foundMET && foundJet1 ) dphi_metjet = fabs(METCand_[0].p4.DeltaPhi(fatJetCand_[0].p4));
   if( foundW && foundJet1 ) dphi_jetw = fabs(fatJetCand_[0].p4.DeltaPhi(WCand_[0].p4));
   
   if( AngularCuts_ && !issignal ) return false;
      
   /*************************************************************/         
   findTopCandidate();
   if( TopMassCut_ && ((ltopmass > leptTopMassLow_ && ltopmass < leptTopMassHigh_) || (htopmass > hadrTopMassLow_ && htopmass < hadrTopMassHigh_)) ) return false;   
   nPassedTopMass_++;
             
   /*************************************************************/       
   float jetMass = 0.;
   
   if( foundJet1 ){
      jetMass = fatJetCand_[0].softdropMass;
      if( JetMassAlgo_ == "pruning" ) jetMass = fatJetCand_[0].prunedMass; 
   }
        
   bool foundJet = false;   
   if( foundJet1 && fatJetCand_[0].tau2/fatJetCand_[0].tau1 > Tau21Low_ && fatJetCand_[0].tau2/fatJetCand_[0].tau1 < Tau21High_ ) foundJet = true;

   if( !foundJet ) return false; 
   nPassedTau21Cut_++;

   foundJet = false;
   if( foundJet1 && jetMass > mLow_ && jetMass < mHigh_ ) foundJet = true;

   if( JetMassAlgo_ != "None" && !foundJet ) return false; 
   nPassedJetMass_++;
   
   /*************************************************************/   
   nsubjbtag = 0;
   nsubjbtagM = 0;
   if( SubjetCand_.size() != 0 ){
   for( unsigned int sj = 0; sj < SubjetCand_[0].size(); ++sj ){
      if( SubjetCand_[0][sj].csv > bTagWPmap_[SubjetsBtagWP_] ){
            nsubjbtag++;
      }
   }
   for( unsigned int sj = 0; sj < SubjetCand_[0].size(); ++sj ){
      if( SubjetCand_[0][sj].csv > bTagWPmap_["CSVM"] ){
            nsubjbtagM++;
      }
   } 
   }
   
   if( NsubjBTag_ != -1 && nsubjbtag != NsubjBTag_ ) return false;
   nPassedNsubjBTagCut_++;

   /*************************************************************/

   if( VetoSR_ && jetMass > 65. && jetMass < 135. ) return false;    
   if( !runOnMC_ && !TString(Channel_).Contains("ttbar") && jetMass > 105. && jetMass < 135. ) return false;     

   /*************************************************************/    

   findExoCandidate();
   if( WWMass_ == -1 ){
       nPassedExoCandidateMass_++;       
       return true;
   }
   
   double low;
   double up;
   
   if( WWMass_ == 0 ){
      low = 700;
      up = 5000;
   }
   else{	        
      low = WWMass_ - WWMass_*15./100.;
      up = WWMass_ + WWMass_*15./100.; 
   }

   if( MWWmethod2 > low && MWWmethod2 < up ){
       nPassedExoCandidateMass_++;
       return true;
   }
   else return false;

}

//==============================================================================================
double ExoDiBosonAnalysis::getMuonScale( double oldpt ){

   double scale = 0.;
   
   if( oldpt < 200. ) scale = (ScaleMuonUpDown_)*0.2*oldpt/100.;
   else if( oldpt >= 200. ) scale = (ScaleMuonUpDown_)*5.*oldpt/100.;	
   
   return scale;
      
}

//==============================================================================================
double ExoDiBosonAnalysis::getPrunedMassScale( double prunedmass, double corrUp, double corrDown, double corr, double pt ){
   
   double newmass = prunedmass/corr;
   //std::cout << "***** mass " << prunedmass << " corr " << corr << " corrUp " << corrUp << " corrDown " << corrDown << std::endl;
   if( ScalePrunedMassUp_ ){
    newmass = newmass*corrUp;
    //std::cout << "I AM HERE" << std::endl;
    //std::cout << "old mass " << prunedmass << " mass raw " << prunedmass/corr << " new mass " << newmass << std::endl;
   }
   else if( ScalePrunedMassDown_ ){
    newmass = newmass*corrDown;
    //std::cout << "I AM HERE" << std::endl;
    //std::cout << "old mass " << prunedmass << " mass raw " << prunedmass/corr << " new mass " << newmass << std::endl;
   }
   else if( ScalePrunedMassResidual_ == -2 ){
    //std::cout << "CV: old pruned mass " << prunedmass << " new mass " << prunedmass - prunedmass*0.7/100. << std::endl;
    return prunedmass - prunedmass*0.7/100.; //0.9
   }
   else if( ScalePrunedMassResidual_ == 1 ){
    //std::cout << "UP: old pruned mass " << prunedmass << " new mass " << prunedmass - prunedmass*0.04/100. << std::endl;
    return prunedmass - prunedmass*0.04/100.; //2
   }
   else if( ScalePrunedMassResidual_ == -1 ){
    //std::cout << "DOWN: old pruned mass " << prunedmass << " new mass " << prunedmass - prunedmass*1.4/100. << std::endl;
    return prunedmass - prunedmass*1.4/100.; //0.3
   }
   else if( JetMassResolutionUpDown_ == -2 ){

     double c = 1.12;   
     double sigmaMC = 7.3;
     if( pt > 300 ){
     
        int bin = hJMRSigmaMCPT_->GetXaxis()->FindBin(pt);
        sigmaMC = sigmaMC*hJMRSigmaMCPT_->GetBinContent(bin)/hJMRSigmaMCPT_->GetBinContent(1);
	
     }
     newmass = tr_->Gaus( prunedmass,TMath::Sqrt(c*c-1)*sigmaMC );
     //std::cout << "  * sigma = " << TMath::Sqrt(c*c-1)*sigmaMC << " pt " << pt << " sigmaMC " << sigmaMC << " old pruned mass " << prunedmass;
     //std::cout << " new pruned mass = " << newmass;
     //std::cout << " c " << c << "  ::CentralValue::" << std::endl;
   
   }
   else if( TMath::Abs(JetMassResolutionUpDown_) > 0  ){

     double c = 1.12;   
     double sigmaMC = 7.3;
     if( pt > 300 ){
     
        int bin = hJMRSigmaMCPT_->GetXaxis()->FindBin(pt);
        sigmaMC = sigmaMC*hJMRSigmaMCPT_->GetBinContent(bin)/hJMRSigmaMCPT_->GetBinContent(1);
	
     }
     c = c + JetMassResolutionUpDown_*0.07;
     newmass = tr_->Gaus( prunedmass,TMath::Sqrt(c*c-1)*sigmaMC  );
     //std::cout << "  * sigma = " << TMath::Sqrt(c*c-1)*sigmaMC << " pt " << pt << " sigmaMC " << sigmaMC << " old pruned mass " << prunedmass;
     //std::cout << " new pruned mass = " << newmass;
     //std::cout << " c " << c << "  ::SmearUpDown::" << std::endl;
        
   }
   else{
   
    newmass = prunedmass;
    //std::cout << "  ::NOSMEARINGandNOSCALE::" << std::endl;    
    
   }
   
   return newmass;
         
}

//==============================================================================================
double ExoDiBosonAnalysis::getJetEnergyScale( double oldpt, double corrUp, double corrDown, double corr, double eta ){

   double pt = oldpt/corr;
   //std::cout << "corr " << corr << " corrUp " << corrUp << " corrDown " << corrDown << std::endl;
   if( ScaleJESUp_ ) pt = pt*corrUp;
   else if( ScaleJESDown_ ) pt = pt*corrDown;
   else if( JetEnergyResolutionUpDown_ == -2 ){

     double c = 1;
     if( fabs(eta) > 0 && fabs(eta) < 0.5 ) c = 1.079;
     else if( fabs(eta) > 0.5 && fabs(eta) < 1.1 ) c = 1.099;
     else if( fabs(eta) > 1.1 && fabs(eta) < 1.7 ) c = 1.121;
     else if( fabs(eta) > 1.7 && fabs(eta) < 2.3 ) c = 1.208;
     else if( fabs(eta) > 2.3 && fabs(eta) < 2.8 ) c = 1.254;
        
     double sigmaMC = 1.;     
     int binpt = hJERSigmaMCPT_->GetXaxis()->FindBin(pt);
     int bineta = hJERSigmaMCPT_->GetYaxis()->FindBin(fabs(eta));
     if( pt < 200. ) binpt = 1;
     sigmaMC = hJERSigmaMCPT_->GetBinContent(binpt,bineta);
	
     pt = tr_->Gaus( oldpt, TMath::Sqrt(c*c-1)*sigmaMC );
     //std::cout << "  * sigma = " << TMath::Sqrt(c*c-1)*sigmaMC << " pt " << pt << " sigmaMC " << sigmaMC << " old pt " << oldpt;
     //std::cout << " eta " << eta ;
     //std::cout << " new pt = " << pt;
     //std::cout << " c " << c << "  ::CentralValue::" << std::endl;
   
   }
   else if( JetEnergyResolutionUpDown_ == 1  ){

     double c = 1;
     if( fabs(eta) > 0 && fabs(eta) < 0.5 ) c = 1.105;
     else if( fabs(eta) > 0.5 && fabs(eta) < 1.1 ) c = 1.127;
     else if( fabs(eta) > 1.1 && fabs(eta) < 1.7 ) c = 1.150;
     else if( fabs(eta) > 1.7 && fabs(eta) < 2.3 ) c = 1.254;
     else if( fabs(eta) > 2.3 && fabs(eta) < 2.8 ) c = 1.316;
        
     double sigmaMC = 1.;     
     int binpt = hJERSigmaMCPT_->GetXaxis()->FindBin(pt);
     int bineta = hJERSigmaMCPT_->GetYaxis()->FindBin(fabs(eta));
     if( pt < 200. ) binpt = 1;
     sigmaMC = hJERSigmaMCPT_->GetBinContent(binpt,bineta);
	
     pt = tr_->Gaus( oldpt, TMath::Sqrt(c*c-1)*sigmaMC );
     //std::cout << "  * sigma = " << TMath::Sqrt(c*c-1)*sigmaMC << " pt " << pt << " sigmaMC " << sigmaMC << " old pt " << oldpt;
     //std::cout << " eta " << eta ;
     //std::cout << " new pt = " << pt;
     //std::cout << " c " << c << "  ::ScaleUP::" << std::endl;
        
   }
   else if( JetEnergyResolutionUpDown_ == -1  ){

     double c = 1;
     if( fabs(eta) > 0 && fabs(eta) < 0.5 ) c = 1.053;
     else if( fabs(eta) > 0.5 && fabs(eta) < 1.1 ) c = 1.071;
     else if( fabs(eta) > 1.1 && fabs(eta) < 1.7 ) c = 1.092;
     else if( fabs(eta) > 1.7 && fabs(eta) < 2.3 ) c = 1.162;
     else if( fabs(eta) > 2.3 && fabs(eta) < 2.8 ) c = 1.192;
        
     double sigmaMC = 1.;     
     int binpt = hJERSigmaMCPT_->GetXaxis()->FindBin(pt);
     int bineta = hJERSigmaMCPT_->GetYaxis()->FindBin(fabs(eta));
     if( pt < 200. ) binpt = 1;
     sigmaMC = hJERSigmaMCPT_->GetBinContent(binpt,bineta);
	
     pt = tr_->Gaus( oldpt, TMath::Sqrt(c*c-1)*sigmaMC );
     //std::cout << "  * sigma = " << TMath::Sqrt(c*c-1)*sigmaMC << " pt " << pt << " sigmaMC " << sigmaMC << " old pt " << oldpt;
     //std::cout << " eta " << eta ;
     //std::cout << " new pt = " << pt;
     //std::cout << " c " << c << "  ::ScaleDown::" << std::endl;
        
   }
   else{
   
    pt = oldpt;
    //std::cout << "  ::NOSMEARINGandNOSCALE::" << std::endl;    
    
   } 
   
   return pt;
 
}

//==============================================================================================
bool ExoDiBosonAnalysis::findLeptonCandidate( void ){

   if( Channel_.find("el") != std::string::npos ) return findElectronCandidate();
   else if( Channel_.find("mu") != std::string::npos ) return findMuonCandidate();
   else return false;
   
}

//==============================================================================================
bool ExoDiBosonAnalysis::findMuonCandidate( void ){

   foundAEle_ = 0;
   foundAMu_ = 0;
   
   TLorentzVector TLV;
   bool foundLept = false;
   double ptMu = -999;
   int muIndex = 999;
   double scale = 0.;
   double newpt = 0.;
   double scale_ = 0.;
   for( int l = 0; l < data_.mu_N; ++l ){
      if( (*data_.mu_isHighPtMuon)[l] != 1 ) continue;
      //if( (*data_.mu_isPFMuon)[l] != 1 ) continue;
      scale = getMuonScale((*data_.mu_pt)[l]);
      newpt = (*data_.mu_pt)[l]+scale;
      if( (*data_.mu_trackIso)[l]/newpt >= 0.1 ) continue;
      if( newpt <= leptPtCut_ ) continue;
      if( fabs((*data_.mu_eta)[l]) >= leptEtaCut_ ) continue;
      foundLept = true;
      if( newpt > ptMu ){   
         ptMu = newpt;
         TLV.SetPtEtaPhiE( newpt, (*data_.mu_eta)[l], (*data_.mu_phi)[l], (*data_.mu_e)[l]+scale );  
	 muIndex = l;
	 scale_ = scale;
      }      
   }
   
   if( foundLept ){
     LeptonCandidate muCand(TLV);
     muCand.iso = (*data_.mu_trackIso)[muIndex]/ptMu;
     muCand.scale = scale_;
     muCand.isGlobalMuon = (*data_.mu_isGlobalMuon)[muIndex];
     muCand.globalHits = (*data_.mu_globalHits)[muIndex];
     muCand.matchedStations = (*data_.mu_matchedStations)[muIndex];
     muCand.bestTrack_ptErrRel = (*data_.mu_bestTrack_ptErr)[muIndex]/(*data_.mu_bestTrack_pt)[muIndex];
     muCand.d0 = (*data_.mu_d0)[muIndex];
     //muCand.dz = (*data_.mu_dz)[muIndex];
     muCand.pixelHits = (*data_.mu_pixelHits)[muIndex];
     muCand.trackerHits = (*data_.mu_trackerHits)[muIndex];
     leptonCand_.push_back( muCand );
   }
   
   scale = 0.;
   for( int l = 0; l < data_.mu_N; ++l ){
      if( muIndex == 999 || l == muIndex ) continue;
      if( (*data_.mu_isHighPtMuon)[l] != 1 ) continue;
      scale = getMuonScale((*data_.mu_pt)[l]);
      newpt = (*data_.mu_pt)[l]+scale;
      if( (*data_.mu_trackIso)[l]/newpt >= 0.1 ) continue;
      if( newpt <= AleptPtCut_ ) continue;
      if( fabs((*data_.mu_eta)[l]) >= AleptEtaCut_ ) continue;
      foundAMu_++;
   }
   
   for( int l = 0; l < data_.el_N; ++l ){
      if( (*data_.el_isHEEP)[l] != 1 ) continue;
      if( (*data_.el_pt)[l] <= 35. ) continue;
      //if( fabs((*data_.el_eta)[l]) >= 1.4442 && fabs((*data_.el_eta)[l]) <= 1.566 ) continue;
      //if( fabs((*data_.el_eta)[l]) >= 2.5 ) continue;
      foundAEle_++;
   }
   
   return foundLept;

   //if( (foundAMu_+foundAEle_)<1 && foundLept ) return true;
   //else return false;
   
}

//==============================================================================================
bool ExoDiBosonAnalysis::findElectronCandidate( void ){

   foundAMu_ = 0;
   foundAEle_ = 0;

   TLorentzVector TLV;
   bool foundEle = false;
   double ptEle = -999;
   int eleIndex = 999;
   for( int l = 0; l < data_.el_N; ++l ){
      if( (*data_.el_pt)[l] <= 35. ) continue;     
      //if( fabs((*data_.el_eta)[l]) >= 1.4442 && fabs((*data_.el_eta)[l]) <= 1.566 ) continue; 
      //if( fabs((*data_.el_eta)[l]) >= leptEtaCut_ ) continue; 
      if( (*data_.el_isHEEP)[l] != 1 ) continue;
      if( (*data_.el_pt)[l] <= leptPtCut_ ) continue;
      foundEle = true;
      if( (*data_.el_pt)[l] > ptEle ){   
         ptEle = (*data_.el_pt)[l];
         TLV.SetPtEtaPhiE( (*data_.el_pt)[l], (*data_.el_eta)[l], (*data_.el_phi)[l], (*data_.el_e)[l] );         
	 eleIndex = l;
      }
   }

   if( foundEle )
    leptonCand_.push_back( LeptonCandidate( TLV ) );
   
   for( int l = 0; l < data_.el_N; ++l ){
      if( eleIndex == 999 || l == eleIndex ) continue;
      if( (*data_.el_isHEEP)[l] != 1 ) continue;
      if( (*data_.el_pt)[l] <= AleptPtCut_ ) continue;
      //if( fabs((*data_.el_eta)[l]) >= 1.4442 && fabs((*data_.el_eta)[l]) <= 1.566 ) continue;
      //if( fabs((*data_.el_eta)[l]) >= AleptEtaCut_ ) continue;
      foundAEle_++;
   }   
   for( int l = 0; l < data_.mu_N; ++l ){
      if( (*data_.mu_isHighPtMuon)[l] != 1 ) continue;
      if( (*data_.mu_trackIso)[l]/(*data_.mu_pt)[l] >= 0.1 ) continue;
      if( (*data_.mu_pt)[l] <= 20. ) continue;
      if( fabs((*data_.mu_eta)[l]) >= 2.4 ) continue;
      foundAMu_++;
   }
   
   return foundEle;
   
   //if( (foundAMu+foundAEle)<1 && foundEle ) return true;
   //else return false;   
      
}

//==============================================================================================
bool ExoDiBosonAnalysis::findJetCandidate( void ){

   TLorentzVector jet_tlv;
   TLorentzVector bestjet_tlv;
   
   bool   foundJet = false;
   float  ptJet    = -9999; 
   int    jetIndex = 999;
   float  jetmass  = -9999;
   double newpt    = 0.;
   double jec      = 1;
   double jecup    = 1;
   double jecdown  = 1;
   double scale    = 0.;
   for( int j = 0; j < data_.njetsAK8; ++j ){
   
      //std::cout << "jet ak8 " << j << " pt " << (*data_.jetAK8_pt)[j] << " e " << (*data_.jetAK8_e)[j];
      //std::cout << " mass " << (*data_.jetAK8_prunedmass)[j] << std::endl;
      //if( j == jetIndex_ ) continue;
      jec = (*data_.jetAK8_jec)[j];
      jecup = (*data_.jetAK8_jecUp)[j];
      jecdown = (*data_.jetAK8_jecDown)[j];
      newpt = getJetEnergyScale( (*data_.jetAK8_pt)[j], jecup, jecdown, jec, (*data_.jetAK8_eta)[j] );
      jet_tlv.SetPtEtaPhiE( newpt, (*data_.jetAK8_eta)[j], (*data_.jetAK8_phi)[j], (newpt/(*data_.jetAK8_pt)[j])*(*data_.jetAK8_e)[j] );
      //std::cout << "   ---> scale " << (newpt/(*data_.jetAK8_pt)[j]) << " new en " << (newpt/(*data_.jetAK8_pt)[j])*(*data_.jetAK8_e)[j] << std::endl;
            
      if( (*data_.jetAK8_IDLoose)[j] != 1 ) continue;
      //std::cout << " * passed id loose" << std::endl;
      if( newpt <= JetPtCutLoose_ ) continue;
      //std::cout << " * passed pt cut" << std::endl;
      if( fabs((*data_.jetAK8_eta)[j]) >= JetEtaCut_ ) continue;
      //std::cout << " * passed eta cut " << std::endl;
      if( /*leptonCand_.size() != 0 &&*/ leptonCand_[0].p4.DeltaR(jet_tlv) <= 1.0 ) continue;
      //std::cout << " * cleaned by lepton" << std::endl;
      
      njets++;
      
      if( (Channel_.find("ttbar") == std::string::npos && (*data_.jetAK8_pt)[j] > ptJet) || 
          (Channel_.find("ttbar") != std::string::npos && (*data_.jetAK8_prunedmass)[j] > jetmass) ){
	  
         ptJet = newpt;
	 jetmass = (*data_.jetAK8_prunedmass)[j]; 
         bestjet_tlv.SetPtEtaPhiE( newpt, (*data_.jetAK8_eta)[j], (*data_.jetAK8_phi)[j], (newpt/(*data_.jetAK8_pt)[j])*(*data_.jetAK8_e)[j] ); 
	 foundJet = true;
	 jetIndex = j;
         scale = newpt-(*data_.jetAK8_pt)[j];
	 
      }
   }
   
   if( foundJet ){
   
     //std::cout << "   * FOUND JET " << jetIndex << " pt " << bestjet_tlv.Pt() << " e " << bestjet_tlv.Energy() << std::endl;
     jetIndex_ = jetIndex;
     JetCandidate jetC(bestjet_tlv); 
     jetC.csv  = (*data_.jetAK8_csv)[jetIndex];
     jetC.tau1 = (*data_.jetAK8_tau1)[jetIndex];
     jetC.tau2 = (*data_.jetAK8_tau2)[jetIndex];
     jetC.tau3 = (*data_.jetAK8_tau3)[jetIndex];
     jetC.softdropMass = (*data_.jetAK8_softdropmass)[jetIndex];
     jetC.mass = (*data_.jetAK8_mass)[jetIndex];
     jetC.scale = scale;

     jec = (*data_.jetAK8_pruned_jec)[jetIndex];     
     jecup = (*data_.jetAK8_pruned_jecUp)[jetIndex];
     jecdown = (*data_.jetAK8_pruned_jecDown)[jetIndex];
     jetC.prunedMass = getPrunedMassScale( (*data_.jetAK8_prunedmass)[jetIndex], jecup, jecdown, jec, bestjet_tlv.Pt() ); 
     //std::cout << "jec " << jec << " jec up " << jecup << " jec down " << jecdown << std::endl;
     
     fatJetCand_.push_back( jetC );
     
     /*std::vector<JetCandidate> tmp;   
     for( int sj = 0; sj < (*data_.subjetAK8_pruned_N)[jetIndex]; ++sj ){
      jet_tlv.SetPtEtaPhiE((*data_.subjetAK8_pruned_pt)[jetIndex][sj],(*data_.subjetAK8_pruned_eta)[jetIndex][sj],(*data_.subjetAK8_pruned_phi)[jetIndex][sj],(*data_.subjetAK8_pruned_e)[jetIndex][sj]);
      csv = (*data_.subjetAK8_pruned_csv)[jetIndex][sj];
      JetCandidate jetC(jet_tlv);
      jetC.csv = csv;
      jetC.flavor = 0;
      if( runOnMC_ ) jetC.flavor = (*data_.subjetAK8_pruned_flavour)[jetIndex][sj];
      tmp.push_back(jetC);
     }
     SubjetCand_.push_back(tmp);*/
   
   }
                        
   return foundJet;

}

//==============================================================================================
void ExoDiBosonAnalysis::findExtraJets( void ){

   //std::cout << "AK8 JET CAND pt " << fatJetCand_[0].p4.Pt() << " eta " << fatJetCand_[0].p4.Eta() << std::endl;
   //std::cout << "LEPTON CAND pt " << leptonCand_[0].p4.Pt() << " eta " << leptonCand_[0].p4.Eta() << std::endl;

   TLorentzVector jet;
   double newpt    = 0.;
   double jec      = 1;
   double jecup    = 1;
   double jecdown  = 1;
   double scale    = 0.;
   for( int j = 0; j < data_.njetsAK4; ++j ){ 
   
      //std::cout << "jet " << j+1 << " pt " << (*data_.jetAK4_pt)[j] << " eta " << (*data_.jetAK4_eta)[j];
      //std::cout << " csv " << (*data_.jetAK4_csv)[j] << std::endl;
      jec = (*data_.jetAK4_jec)[j];
      jecup = (*data_.jetAK4_jecUp)[j];
      jecdown = (*data_.jetAK4_jecDown)[j];
      newpt = getJetEnergyScale( (*data_.jetAK4_pt)[j], jecup, jecdown, jec, (*data_.jetAK4_eta)[j] );          
      jet.SetPtEtaPhiE( newpt, (*data_.jetAK4_eta)[j], (*data_.jetAK4_phi)[j], (newpt/(*data_.jetAK4_pt)[j])*(*data_.jetAK4_e)[j] );
           
      if( jet.DeltaR(fatJetCand_[0].p4) < 0.8 ) continue;
      //std::cout << "* cleaned by AK8 jet : dR = " << jet.DeltaR(fatJetCand_[0].p4) << std::endl;
      if( (*data_.jetAK4_IDLoose)[j] != 1 ) continue;
      //std::cout << " * passed ID loose" << std::endl;
      if( newpt <= 30. ) continue;
      //std::cout << " * passed pt cut" << std::endl;
      if( fabs((*data_.jetAK4_eta)[j]) >= JetEtaCut_ ) continue;
      //std::cout << " * passed eta cut" << std::endl;
      if( jet.DeltaR(leptonCand_[0].p4) < 0.3 ) continue;
      //std::cout << " * cleaned by lepton: dR = " << jet.DeltaR(leptonCand_[0].p4) << std::endl;
      JetCandidate Ajet(jet);
      Ajet.csv = (*data_.jetAK4_csv)[j];
      Ajet.flavor = 0;
      if( runOnMC_ ) Ajet.flavor = abs((*data_.jetAK4_flavor)[j]);
      AK4jetCand_.push_back(Ajet);
      
   }
   
}

//==============================================================================================
bool ExoDiBosonAnalysis::findMETCandidate( void ){
 
   if( ScaleMuonUpDown_!= 0 || ScaleJESUp_ != 0 || ScaleJESDown_ != 0 || JetEnergyResolutionUpDown_ != 0 ){
    return findMETCandidateForSys();   
   }
   
   TLorentzVector TLV;
   bool foundMET = false;
   if( (*data_.MET_et)[0] > 0. ){
   
      TLV.SetPtEtaPhiE( (*data_.MET_et)[0], 0., (*data_.MET_phi)[0], 0. );
                 
      METCandidate metC(TLV);
      metC.sumEt = (*data_.MET_sumEt)[0];
      METCand_.push_back( METCandidate( TLV ) );
      foundMET = true;
      
   }
   
   return foundMET; 
   
}

//==============================================================================================
bool ExoDiBosonAnalysis::findMETCandidateForSys( void ){
 
   TLorentzVector TLV;
   bool foundMET = false;
   if( (*data_.MET_et)[0] > 0. ){
   
      if( ScaleMuonUpDown_ != 0 ) {

         TVector2 lepnew; lepnew.SetMagPhi( leptonCand_[0].p4.Pt(), leptonCand_[0].p4.Phi() );
         TVector2 lep; lep.SetMagPhi( leptonCand_[0].p4.Pt() - leptonCand_[0].scale, leptonCand_[0].p4.Phi() );
         TVector2 diff = lepnew - lep;
	     TVector2 met; met.SetMagPhi( (*data_.MET_et)[0], (*data_.MET_phi)[0] );
	     TVector2 METcorr = met - diff;
	     TLV.SetPtEtaPhiE( METcorr.Mod(), 0., METcorr.Phi(), 0. );
	 
      }
      else if( ScaleJESUp_ != 0 || ScaleJESDown_ != 0 || JetEnergyResolutionUpDown_ != 0 ) {

         TLorentzVector jetnew;
         TLorentzVector jet;
         TLorentzVector diff;
   
         double newpt    = 0.;
         double jec      = 1;
         double jecup    = 1;
         double jecdown  = 1;
         for( int j = 0; j < data_.njetsAK4; ++j ){ 
   
          jec = (*data_.jetAK4_jec)[j];
          jecup = (*data_.jetAK4_jecUp)[j];
          jecdown = (*data_.jetAK4_jecDown)[j];
          newpt = getJetEnergyScale( (*data_.jetAK4_pt)[j], jecup, jecdown, jec, (*data_.jetAK4_eta)[j] );          
          jetnew.SetPtEtaPhiE( newpt, (*data_.jetAK4_eta)[j], (*data_.jetAK4_phi)[j], (newpt/(*data_.jetAK4_pt)[j])*(*data_.jetAK4_e)[j] );           
          jet.SetPtEtaPhiE( (*data_.jetAK4_pt)[j], (*data_.jetAK4_eta)[j], (*data_.jetAK4_phi)[j], (*data_.jetAK4_e)[j] );     
          diff+=(jet-jetnew);      
      
        }
        
        TLorentzVector met; met.SetPtEtaPhiE( (*data_.MET_et)[0], 0., (*data_.MET_phi)[0], 0. );
        TLorentzVector METcorr = met - diff;
        TLV.SetPtEtaPhiE( METcorr.Pt(), 0., METcorr.Phi(), 0. );
   	  
      }
                 
      METCandidate metC(TLV);
      metC.sumEt = (*data_.MET_sumEt)[0];
      METCand_.push_back( METCandidate( TLV ) );
      foundMET = true;
      
   }
    
   return foundMET; 
   
}

//==============================================================================================
bool ExoDiBosonAnalysis::findWCandidate( void ){

   TLorentzVector TLV;
   bool foundW = false;
   if( (METCand_[0].p4+leptonCand_[0].p4).Pt() > 0. ){
      foundW = true;
      TLV = METCand_[0].p4+leptonCand_[0].p4;
      WCand_.push_back( TLV );
   }
   
   return foundW;
}

//==============================================================================================
bool ExoDiBosonAnalysis::findJetCandidates( void ){
  
  TLorentzVector TLV;
  std::vector<float> jetPt;
  std::vector<float> jetPtNew;
  std::vector<float> jecupV;
  std::vector<float> jecdownV;
  std::vector<float> jecV;
  bool foundJets = false;
  float csv = -9999;
  double newpt    = 0.;
  double jec      = 1;
  double jecup    = 1;
  double jecdown  = 1;
   		
  jetPt.clear();
  //Make sure jets passes loose ID, pT and eta cuts
  for( int j = 0; j < data_.njetsAK8 ; ++j ){
  
    //std::cout << "Jet " << j << " pt " << (*data_.jetAK8_pt)[j] << " pruned mass " << (*data_.jetAK8_prunedmass).at(j) << std::endl;
    if( j < 2 && (*data_.jetAK8_IDTight).at(j) != 1 )break;
    if( (*data_.jetAK8_IDTight).at(j) != 1 )continue;
    //std::cout << "   * passed ID Tight" << std::endl;
    jec = (*data_.jetAK8_jec)[j];
    jecup = (*data_.jetAK8_jecUp)[j];
    jecdown = (*data_.jetAK8_jecDown)[j];
    newpt = getJetEnergyScale( (*data_.jetAK8_pt)[j], jecup, jecdown, jec, (*data_.jetAK8_eta)[j] );
    //std::cout << "   * new pt " << newpt << std::endl;      
    if( newpt <= JetPtCutTight_ )continue;
    //std::cout << "   * passed pt cut" << std::endl;
    if( fabs((*data_.jetAK8_eta).at(j)) >= JetEtaCut_ )continue;
    //std::cout << "   * passed eta cut" << std::endl;		
    jetPt.push_back((*data_.jetAK8_pt)[j]);
    jetPtNew.push_back(newpt);
    jecupV.push_back(jecup);
    jecdownV.push_back(jecdown);
    jecV.push_back(jec);
    
  }
	
  if( jetPtNew.size() > 1 ) foundJets = true;
  if( !foundJets) return false;
	
  //std::cout << "************ FOUND AT LEAST 2 JETS *************" << std::endl;	
  //for( unsigned int n = 0; n < jetPtNew.size(); ++n ) std::cout << n+1 << ") pt " << jetPtNew.at(n) << "/" << jetPt.at(n) << std::endl;
   	
  //Find two highest pT jets in event
  if( foundJets ){
  
    std::sort  (jetPt.begin(),jetPt.end());
    std::reverse(jetPt.begin(),jetPt.end());
    for( int jj = 0; jj < 2; ++jj ){
      bool foundOverlap = false;
      if( (*data_.jetAK8_pt)[jj] == jetPt.at(0) ){
        newpt = jetPtNew.at(0);
        //std::cout << "DEBUG --> 1) " << newpt << std::endl;
        TLV.SetPtEtaPhiE( newpt, (*data_.jetAK8_eta).at(jj), (*data_.jetAK8_phi).at(jj), (newpt/(*data_.jetAK8_pt).at(jj))*(*data_.jetAK8_e).at(jj) );
        if ( findMuonCandidate() || findElectronCandidate() ){
          for(int i = 0; i < abs(leptonCand_.size()); i++){
            if( TLV.DeltaR(leptonCand_.at(i).p4) < 0.8 ){
              foundOverlap = true;
          }
        }
      }
       
      if( foundOverlap ) break;
	
      JetCandidate jet(TLV);
      jet.csv = -99;
      jet.tau1 = (*data_.jetAK8_tau1).at(jj);
      jet.tau2 = (*data_.jetAK8_tau2).at(jj);
      jet.tau3 = (*data_.jetAK8_tau3).at(jj);
      jet.prunedMass = getPrunedMassScale( (*data_.jetAK8_prunedmass).at(jj), jecupV.at(0), jecdownV.at(0), jecV.at(0), TLV.Pt() ); 
      //std::cout << "---------- old pruned mass " << (*data_.jetAK8_prunedmass).at(jj);
      //std::cout << " - new pruned mass " << jet.prunedMass << std::endl;
      jet.softdropMass = (*data_.jetAK8_softdropmass).at(jj)*(*data_.jetAK8_pruned_jec).at(jj);
      jet.mass = (*data_.jetAK8_mass).at(jj);
      jet.flavor = -99;        
      fatJetCand_.push_back( jet );
        
      }
      else if( (*data_.jetAK8_pt).at(jj) == jetPt.at(1) ){
        newpt = jetPtNew.at(1);
        //std::cout << "DEBUG --> 2) " << newpt << std::endl;
        TLV.SetPtEtaPhiE( newpt, (*data_.jetAK8_eta).at(jj), (*data_.jetAK8_phi).at(jj), (newpt/(*data_.jetAK8_pt).at(jj))*(*data_.jetAK8_e).at(jj) );
        if ( findMuonCandidate() || findElectronCandidate() ){
          for(int i = 0; i < abs(leptonCand_.size()); i++){
            if( TLV.DeltaR(leptonCand_.at(i).p4) < 0.8 ){
              foundOverlap = true;
            }
          }
        }
        if( foundOverlap ) break;
        JetCandidate secondJet(TLV);
        secondJet.csv           = -99;
        secondJet.tau1          = (*data_.jetAK8_tau1).at(jj);
        secondJet.tau2          = (*data_.jetAK8_tau2).at(jj);
        secondJet.tau3          = (*data_.jetAK8_tau3).at(jj);
        secondJet.prunedMass = getPrunedMassScale( (*data_.jetAK8_prunedmass).at(jj), jecupV.at(1), jecdownV.at(1), jecV.at(1), TLV.Pt() ); 
        //std::cout << "---------- old pruned mass " << (*data_.jetAK8_prunedmass).at(jj);
        //std::cout << " - new pruned mass " << secondJet.prunedMass << std::endl;
        secondJet.softdropMass  = (*data_.jetAK8_softdropmass).at(jj);
        secondJet.mass          = (*data_.jetAK8_mass).at(jj);
        secondJet.flavor        = -99;
        fatJetCand_.push_back( secondJet );
      }
      else
        continue;
    }
  }
  
  if (fatJetCand_.size() < 2) return false;
  
  return foundJets;
}

//==============================================================================================
TLorentzVector ExoDiBosonAnalysis::getp4Nu( void ){

   return Utilities::NuMomentum( leptonCand_[0].p4.Px(), leptonCand_[0].p4.Py(), leptonCand_[0].p4.Pz(), leptonCand_[0].p4.Pt(), leptonCand_[0].p4.E(), METCand_[0].p4.Px(), METCand_[0].p4.Py() );   
   
}

//==============================================================================================
TLorentzVector ExoDiBosonAnalysis::getp4NuMethod2( void ){

   double E_l  = leptonCand_[0].p4.E();
   double m_l  = leptonCand_[0].p4.M();
   double px_l = leptonCand_[0].p4.Px();
   double py_l = leptonCand_[0].p4.Py();
   double pz_l = leptonCand_[0].p4.Pz();
      
   double px_v = METCand_[0].p4.Px();
   double py_v = METCand_[0].p4.Py();
      
   double m_W = 80.4;
   
   double a = m_W*m_W - m_l*m_l + 2*px_l*px_v + 2*py_l*py_v;
   double A = 4*(E_l*E_l - pz_l*pz_l);
   double B = (-4)*a*pz_l;
   double C = 4*E_l*E_l*(px_v*px_v + py_v*py_v) - a*a;
   double Delta = B*B - 4*A*C;
      
   double pz_v_1 = -9999;
   double pz_v_2 = -9999;
   double pz_v   = -9999;
      
   if( Delta > 0 ){
      pz_v_1 = ( -B + TMath::Sqrt(Delta) )/( 2*A );
      pz_v_2 = ( -B - TMath::Sqrt(Delta) )/( 2*A ); 
      if( fabs(pz_v_1) <= fabs(pz_v_2) ) pz_v = pz_v_1;
      else pz_v = pz_v_2;     
   }
   else if ( Delta <= 0 )
      pz_v = -B/(2*A);

   TLorentzVector v; v.SetPxPyPzE(px_v,py_v,pz_v,fabs(TMath::Sqrt(pz_v*pz_v + py_v*py_v + px_v*px_v)));
   v.SetPz(pz_v);
   v.SetPx(px_v);
   v.SetPy(py_v);
   v.SetE(fabs(TMath::Sqrt(pz_v*pz_v + py_v*py_v + px_v*px_v)));  
   
   return v;
      
}

//==============================================================================================
void ExoDiBosonAnalysis::findExoCandidate( void ){

   TLorentzVector p4nu = getp4Nu();      
   MWW = (p4nu + leptonCand_[0].p4 + fatJetCand_[0].p4).M();
   WMass = (p4nu + leptonCand_[0].p4).M();
   
   TLorentzVector p4nu2 = getp4NuMethod2();
   //Hist( "pzNu" )->Fill(p4nu2.Pz());

   //Hist( "NuLeptInvMass"  )->Fill( (p4nu2 + leptonCand_[0].p4).M() );
   MWWmethod2 = (p4nu2 + leptonCand_[0].p4 + fatJetCand_[0].p4).M();  
   WMassMethod2 = (p4nu2 + leptonCand_[0].p4).M();  

   return;
            
}

//==============================================================================================
void ExoDiBosonAnalysis::fillHistos( void ){
         
   /* lepton histos */
   Hist( "leptonPT"         	 )->Fill( leptonCand_[0].p4.Pt(), weight_ );
   Hist( "leptonPhi"         	 )->Fill( leptonCand_[0].p4.Phi(), weight_ );
   Hist( "leptonEta"        	 )->Fill( leptonCand_[0].p4.Eta(), weight_ );
   
   /* MET histos */
   Hist( "MET"              	 )->Fill( METCand_[0].p4.Pt(), weight_ );
   Hist( "METphi"              	 )->Fill( METCand_[0].p4.Phi(), weight_ );

   /* leptonic W histos */
   Hist( "recoWPT"          	 )->Fill( WCand_[0].p4.Pt(), weight_ );
   Hist( "recoWMT"          	 )->Fill( TMath::Sqrt( 2*METCand_[0].p4.Pt()*leptonCand_[0].p4.Pt()*(1-cos(leptonCand_[0].p4.DeltaPhi(METCand_[0].p4))) ), weight_ );

   /*if( runOnMC== true ){
   std::map<int,TLorentzVector>::iterator it = genCandidates_.find(24)!=genCandidates_.end() ? genCandidates_.find(24) : genCandidates_.find(-24);
   Hist( "genWMass" )->Fill( (it->second).M() );
   Hist( "WMassResolution" )->Fill( ((it->second).M()-WMass)/(it->second).M() );
   Hist( "WMassResolutionV2" )->Fill( ((it->second).M()-WMassMethod2)/(it->second).M() );
   for( unsigned int p = 0; p < (data_.genParticle_pdgId)->size(); ++p ){
      if( (*data_.genParticle_status)[p] != 4 && (*data_.genParticle_status)[p] != 22 && (*data_.genParticle_status)[p] != 23 ) continue;
      if( (*data_.genParticle_pdgId)[p] == 5100039 ){
         Hist( "WWMassResolution" )->Fill( ( (*data_.genParticle_mass)[p]-MWW )/(it->second).M() );
         Hist( "WWMassResolutionV2" )->Fill( ( (*data_.genParticle_mass)[p]-MWWmethod2)/(it->second).M() );
         break;
      } 
   }
   }*/

   /* topology histos */
   Hist( "lepJetDR"         	 )->Fill( leptonCand_[0].p4.DeltaR(fatJetCand_[0].p4), weight_ );
   Hist( "METJetDphi"       	 )->Fill( fabs(METCand_[0].p4.DeltaPhi(fatJetCand_[0].p4)), weight_ );
   Hist( "WJetDphi"         	 )->Fill( fabs(fatJetCand_[0].p4.DeltaPhi(WCand_[0].p4)), weight_ );

   /* top histos */
   Hist( "leptonictopmass"       )->Fill( ltopmass,weight_ );
   Hist( "hadronictopmass"       )->Fill( htopmass,weight_ );
   Hist( "leptonictopmassV2"       )->Fill( ltopmassMethod2,weight_ );

   /* MWW */
   Hist( "DiBosonInvMass"        )->Fill( MWW, weight_ );
   Hist( "DiBosonInvMassMethod2" )->Fill( MWWmethod2, weight_ );

   /* other histos */
   Hist( "PUWeights"        	 )->Fill( puweight_ );
   Hist( "nVertices"        	 )->Fill( data_.nPVs, weight_ );
   Hist( "htagweight"            )->Fill(htagw);
   Hist( "btagvweight"           )->Fill(btagvetow);

   /* AK8 b-jet histos */
   Hist( "AK8jetPT"       	 )->Fill( fatJetCand_[0].p4.Pt(), weight_ );
   Hist( "AK8jetEta"      	 )->Fill( fatJetCand_[0].p4.Eta(), weight_ );
   Hist( "AK8jetPhi"      	 )->Fill( fatJetCand_[0].p4.Phi(), weight_ );
   Hist( "AK8jetCSV"      	 )->Fill( fatJetCand_[0].csv, weight_ );
   Hist( "AK8jetPrunedMass" 	 )->Fill( fatJetCand_[0].prunedMass, weight_ );
   Hist( "AK8jetSoftDropMass" 	 )->Fill( fatJetCand_[0].softdropMass, weight_ );
   Hist( "AK8jetMass"       	 )->Fill( fatJetCand_[0].mass, weight_ );
   Hist( "tau21"	         )->Fill( fatJetCand_[0].tau2/fatJetCand_[0].tau1,weight_ );
   Hist( "tau31"	         )->Fill( fatJetCand_[0].tau3/fatJetCand_[0].tau1,weight_ );
   Hist( "tau32"	         )->Fill( fatJetCand_[0].tau3/fatJetCand_[0].tau2,weight_ );
          
   /* AK4 jets histos */    
   int najets=0; 
   for( unsigned int j = 0; j < AK4jetCand_.size(); ++j ){
      if( AK4jetCand_[j].csv > bTagWPmap_[BtagVetoWP_] ) najets++;
   }    
   Hist( "nAJetsBTag" )->Fill(najets, weight_ );
   Hist( "nAJets" )->Fill(AK4jetCand_.size(), weight_ );
   
   if( AK4jetCand_.size() != 0 ){ 
      Hist( "AK4jetPt"       )->Fill( AK4jetCand_[0].p4.Pt(), weight_ );
      Hist( "AK4jetCSV"      )->Fill( AK4jetCand_[0].csv , weight_ );
      Hist( "AK4jetMass"     )->Fill( AK4jetCand_[0].p4.M(), weight_ );
   }
         
}


//==============================================================================================
void ExoDiBosonAnalysis::findTopCandidate( void ){

   unsigned int size = AK4jetCand_.size();
   htopmass = 1.;
   ltopmass = 1.;
   
   if( size == 0 )
      return;
     
   double dRtmp = 9999.;
   double dR = 0.;
   unsigned int jetIndex = 99;
   for( unsigned int j = 0; j < size; ++j ){
      dR = AK4jetCand_[j].p4.DeltaR(fatJetCand_[0].p4);
      if( dR < 0.8 ) continue;
      if( dR < dRtmp ){
          jetIndex = j;
	  dRtmp = dR;  
      } 
   }
   
   if( jetIndex != 99 ) htopmass = (AK4jetCand_[jetIndex].p4+fatJetCand_[0].p4).M();
   
   dRtmp = 9999.;
   dR = 0.;
   jetIndex = 99;
   for( unsigned int j = 0; j < size; ++j ){
      dR = AK4jetCand_[j].p4.DeltaR(leptonCand_[0].p4);
      if( dR < dRtmp ){
          jetIndex = j;
	  dRtmp = dR;  
      } 
   }
   
   if( jetIndex != 99 ) {
   
      TLorentzVector p4nu = getp4Nu();
      ltopmass = (p4nu + leptonCand_[0].p4 + AK4jetCand_[jetIndex].p4).M();

      TLorentzVector p4nu2 = getp4NuMethod2();
      ltopmassMethod2 = (p4nu2 + leptonCand_[0].p4 + AK4jetCand_[jetIndex].p4).M();
      
   }
      
}

//==============================================================================================
void ExoDiBosonAnalysis::TriggerEfficiency( void ){

   bool foundLept = false;  
   if( findLeptonCandidate() ) foundLept = true; 
   if( !foundLept ) return;
   nPassedFoundLept_++;
   
   float pt = leptonCand_[0].p4.Pt();
   float eta = leptonCand_[0].p4.Eta();
   
   Hist( "leptonTriggerEffPTden" )->Fill(pt);
   Hist( "leptonTriggerEffEtaden" )->Fill(eta);
   if( passedTrigger() ){
      Hist( "leptonTriggerEffPT" )->Fill(pt);
      Hist( "leptonTriggerEffEta" )->Fill(eta);   
   }
   
}

//==============================================================================================
void ExoDiBosonAnalysis::FiltersEfficiency( void ){
   
   bool isfired = false;
   for( std::map<std::string,bool>::iterator it = (data_.HLT_isFired)->begin(); it != (data_.HLT_isFired)->end(); ++it){
         if( (it->first).find("HLT_PFHT800") != std::string::npos && it->second ) isfired = true;
   }

   if( !runOnMC_ && !isfired ) return;
   
   TLorentzVector bestjet_tlv;   
   bool  foundJet1   = false;
   float ptJet       = -9999; 
   int   jetIndex    = 999;
   
   for( int j = 0; j < data_.njetsAK8; ++j ){
               
      if( (*data_.jetAK8_IDLoose)[j] != 1 ) continue;
      if( (*data_.jetAK8_pt)[j] <= JetPtCutLoose_ ) continue;
      if( fabs((*data_.jetAK8_eta)[j]) >= JetEtaCut_ ) continue;
            
      if( (*data_.jetAK8_pt)[j] > ptJet ){
         ptJet = (*data_.jetAK8_pt)[j];
         bestjet_tlv.SetPtEtaPhiE( (*data_.jetAK8_pt)[j], (*data_.jetAK8_eta)[j], (*data_.jetAK8_phi)[j], (*data_.jetAK8_e)[j] ); 
	     foundJet1 = true;
	     jetIndex = j;
      }
      
   }

   if( !foundJet1 ) return;
   JetCandidate jetC1(bestjet_tlv); 
   fatJetCand_.push_back( jetC1 );   
   if( fatJetCand_[0].p4.Pt() <= JetPtCutTight_ ) return;
      
   bool foundJet2 = false;   
   ptJet = -9999; 
   for( int j = 0; j < data_.njetsAK8; ++j ){
               
      if( j == jetIndex ) continue;
               
      if( (*data_.jetAK8_IDLoose)[j] != 1 ) continue;
      if( (*data_.jetAK8_pt)[j] <= JetPtCutLoose_ ) continue;
      if( fabs((*data_.jetAK8_eta)[j]) >= JetEtaCut_ ) continue;
            
      if( (*data_.jetAK8_pt)[j] > ptJet ){
         ptJet = (*data_.jetAK8_pt)[j];
         bestjet_tlv.SetPtEtaPhiE( (*data_.jetAK8_pt)[j], (*data_.jetAK8_eta)[j], (*data_.jetAK8_phi)[j], (*data_.jetAK8_e)[j] ); 
	     foundJet2 = true;
      }
      
   }
   
   if( !foundJet2 ) return;
   JetCandidate jetC2(bestjet_tlv); 
   fatJetCand_.push_back( jetC2 );   
            
   if( fatJetCand_[0].p4.DeltaPhi(fatJetCand_[1].p4) < 2. ) return;
       
   Hist( "FiltersEffPT_den" )->Fill(fatJetCand_[0].p4.Pt());
   Hist( "FiltersEffEta_den" )->Fill(fatJetCand_[0].p4.Eta());
   	
   if( data_.passFilter_HBHE_ ){
      Hist( "HBHEFilterEffPT" )->Fill(fatJetCand_[0].p4.Pt());
      Hist( "HBHEFilterEffEta" )->Fill(fatJetCand_[0].p4.Eta());
   }
   else{
      Hist( "HBHEFilterMET" )->Fill( (*data_.MET_et)[0] );
      Hist( "HBHEFilterSumET" )->Fill( (*data_.MET_et)[0]/(*data_.MET_sumEt)[0] );
      if( (*data_.MET_et)[0] > 2000. ) std::cout << "**** FOUND BAD MET " << (*data_.MET_et)[0] << std::endl; 
   }

   if( data_.passFilter_HBHEIso_ ){
      Hist( "HBHEIsoFilterEffPT" )->Fill(fatJetCand_[0].p4.Pt());
      Hist( "HBHEIsoFilterEffEta" )->Fill(fatJetCand_[0].p4.Eta());
   }

   
   if( data_.passFilter_CSCHalo_ ){
     Hist( "CSCHaloFilterEffPT" )->Fill(fatJetCand_[0].p4.Pt());
     Hist( "CSCHaloFilterEffEta" )->Fill(fatJetCand_[0].p4.Eta());
   }
   
    if( data_.passFilter_GoodVtx_ ){
     Hist( "GoodVtxFilterEffPT" )->Fill(fatJetCand_[0].p4.Pt());
     Hist( "GoodVtxFilterEffEta" )->Fill(fatJetCand_[0].p4.Eta());
   }	  

   if( data_.passFilter_EEBadSc_ ){
     Hist( "EEBadScFilterEffPT" )->Fill(fatJetCand_[0].p4.Pt());
     Hist( "EEBadScFilterEffEta" )->Fill(fatJetCand_[0].p4.Eta());
   }
   
    if( data_.passFilter_GoodVtx_ && data_.passFilter_CSCHalo_ && data_.passFilter_HBHE_ && data_.passFilter_EEBadSc_ ){
     Hist( "METFiltersEffPT" )->Fill(fatJetCand_[0].p4.Pt());
     Hist( "METFiltersEffEta" )->Fill(fatJetCand_[0].p4.Eta());
   }
           
}


//==============================================================================================
void ExoDiBosonAnalysis::doPileUp( void ){

   if( !runOnMC_ && !passedTrigger() ) return;
   
   Hist( "nVertices" )->Fill( data_.nPVs );
   
   if( runOnMC_ ){
   for( unsigned int v = 0; v < (data_.nPUTrue)->size(); ++v ){
      if( (*data_.bX)[v] == 0 ){
       Hist( "nPUTrue" )->Fill((*data_.nPUTrue)[v] );
       puweight_ = PUWeight_.getPUWeight( (*data_.nPUTrue)[v] );
       Hist( "PUWeights" )->Fill( (*data_.nPUTrue)[v],puweight_ );
      }
   }

   
   }

}

//==============================================================================================
void ExoDiBosonAnalysis::METnoHF( void ){


 //TLorentzVector nu; 
 for( std::map<int,TLorentzVector>::iterator it = genCandidates_.begin(); it!=genCandidates_.end(); ++it ){
 
  //std::cout << it->first << std::endl;
  if( abs(it->first) == 12 || abs(it->first) == 14 || abs(it->first) == 16 ){
    findMETCandidate();
    Hist( "METresolution" )->Fill( ((it->second).Pt()-METCand_[0].p4.Pt())/(it->second).Pt() );
    //std::cout << (it->second).Pt()-METCand_[0].p4.Pt() << std::endl;
  
  }
  
 }
   
 return;
   
}
       			        
//==============================================================================================
void ExoDiBosonAnalysis::EndInputData( const SInputData& ) throw( SError ) {
   
   if( Channel_ == "dijet" ){
    printDijetCutFlow();
    return;
   }
   printCutFlow();                  
   theHistosManager_->formatHistos();

   Hist( "genEvents"               	     )->SetBinContent(1,genEvents_			   );
   Hist( "nEvents"	    	   	     )->SetBinContent(1,nEvents_			   );
   Hist( "nPassedFilters"   	   	     )->SetBinContent(1,nPassedFilters_ 		   );
   Hist( "nPassedTrigger"   	   	     )->SetBinContent(1,nPassedTrigger_ 		   );
   Hist( "nPassedFoundLepton" 	   	     )->SetBinContent(1,nPassedFoundLept_		   );
   Hist( "nPassedVetoExtraLeptons" 	     )->SetBinContent(1,nPassedVetoExtraLeptons_	   );
   Hist( "nPassedFoundMET"  	   	     )->SetBinContent(1,nPassedFoundMET_		   );
   Hist( "nPassedFoundW"    	      	     )->SetBinContent(1,nPassedFoundW_  		   );
   Hist( "nPassedFoundJet"  	   	     )->SetBinContent(1,nPassedFoundJet_		   );
   Hist( "nPassedLepJetDR"  	   	     )->SetBinContent(1,nPassedLepJetDR_		   );
   Hist( "nPassedJetPtTight"	   	     )->SetBinContent(1,nPassedJetPtTight_		   );
   Hist( "nPassedAJetCut"   	      	     )->SetBinContent(1,nPassedAJetCut_ 		   );
   Hist( "nPassedLepJetDR2" 	   	     )->SetBinContent(1,nPassedLepJetDR2_		   );
   Hist( "nPassedMETJetDPhi"	   	     )->SetBinContent(1,nPassedMETJetDPhi_		   );
   Hist( "nPassedJetWDPhi"  	   	     )->SetBinContent(1,nPassedJetWDPhi_		   );
   Hist( "nPassedTopMass"  	      	     )->SetBinContent(1,nPassedTopMass_ 		   );
   Hist( "nPassedJetMass"   	   	     )->SetBinContent(1,nPassedJetMass_ 		   );
   Hist( "nPassedNsubjBTagCut"     	     )->SetBinContent(1,nPassedNsubjBTagCut_		   );
   Hist( "nPassedExoCandidateMass" 	     )->SetBinContent(1,nPassedExoCandidateMass_	   );
   Hist( "nPassedGoodPVFilter"       	     )->SetBinContent(1,nPassedGoodPVFilter_               );	    
   Hist( "nPassedFilter_HBHE"        	     )->SetBinContent(1,nPassedFilter_HBHE_                );	    
   Hist( "nPassedFilter_HBHEIso"             )->SetBinContent(1,nPassedFilter_HBHEIso_             );	    
   Hist( "nPassedFilter_CSCHalo"     	     )->SetBinContent(1,nPassedFilter_CSCHalo_             );  
   Hist( "nPassedFilter_HCALlaser"   	     )->SetBinContent(1,nPassedFilter_HCALlaser_           );  
   Hist( "nPassedFilter_ECALDeadCell"	     )->SetBinContent(1,nPassedFilter_ECALDeadCell_        );  
   Hist( "nPassedFilter_GoodVtx"     	     )->SetBinContent(1,nPassedFilter_GoodVtx_             );  
   Hist( "nPassedFilter_TrkFailure"  	     )->SetBinContent(1,nPassedFilter_TrkFailure_          );  
   Hist( "nPassedFilter_EEBadSc"     	     )->SetBinContent(1,nPassedFilter_EEBadSc_             );  
   Hist( "nPassedFilter_ECALlaser"   	     )->SetBinContent(1,nPassedFilter_ECALlaser_           );  
   Hist( "nPassedFilter_TrkPOG"              )->SetBinContent(1,nPassedFilter_TrkPOG_              );	    
   Hist( "nPassedFilter_TrkPOG_manystrip"    )->SetBinContent(1,nPassedFilter_TrkPOG_manystrip_    );	
   Hist( "nPassedFilter_TrkPOG_toomanystrip" )->SetBinContent(1,nPassedFilter_TrkPOG_toomanystrip_ );
   Hist( "nPassedFilter_TrkPOG_logError"     )->SetBinContent(1,nPassedFilter_TrkPOG_logError_     );	 
   Hist( "nPassedFilter_METFilters"          )->SetBinContent(1,nPassedFilter_METFilters_          );		 
   Hist( "nPassedFilter_EventList"           )->SetBinContent(1,nPassedFilter_EventList_           );		 
   Hist( "nPassedMETFiltersAll"              )->SetBinContent(1,nPassedMETFiltersAll_              );	    
   Hist( "nPassedTrkFiltersAll"              )->SetBinContent(1,nPassedTrkFiltersAll_              );		    
   Hist( "nPassedFilters"                    )->SetBinContent(1,nPassedFilters_                    );
   Hist( "sumGenWeight"                      )->SetBinContent(1,sumGenWeights_                     );
   
   m_logger << INFO << std::endl; 
   m_logger << INFO << "############ Cut flow: ############" << std::endl;     
   m_logger << INFO << "number of events		                         " << nEvents_ << std::endl;
   m_logger << INFO << "passed filters		                                 " << nPassedFilters_ << " --- eff = " << (double)nPassedFilters_/nEvents_ << std::endl; 
   m_logger << INFO << "passed trigger		                                 " << nPassedTrigger_ << " --- eff = " << (double)nPassedTrigger_/nEvents_ << std::endl; 
   m_logger << INFO << "found lepton		                                 " << nPassedFoundLept_ << " --- eff = " << (double)nPassedFoundLept_/nEvents_ << std::endl;
   m_logger << INFO << "veto extra leptons		                         " << nPassedVetoExtraLeptons_ << " --- eff = " << (double)nPassedVetoExtraLeptons_/nEvents_ << std::endl;
   m_logger << INFO << "found jet candidate with pt cut loose (80 GeV)		 " << nPassedFoundJet_ << " --- eff = " << (double)nPassedFoundJet_/nEvents_ << std::endl;
   m_logger << INFO << "DR(j,l) > 1		                                 " << nPassedLepJetDR_ << " --- eff = " << (double)nPassedLepJetDR_/nEvents_ << std::endl;
   m_logger << INFO << "jet pt cut tight (200 GeV)		                 " << nPassedJetPtTight_ << " --- eff = " << (double)nPassedJetPtTight_/nEvents_ << std::endl;
   m_logger << INFO << "found MET 		                                 " << nPassedFoundMET_ << " --- eff = " << (double)nPassedFoundMET_/nEvents_ << std::endl;
   m_logger << INFO << "found W 		                                 " << nPassedFoundW_ << " --- eff = " << (double)nPassedFoundW_/nEvents_ << std::endl;
   m_logger << INFO << "additional jets cut		                         " << nPassedAJetCut_ << " --- eff = " << (double)nPassedAJetCut_/nEvents_ << std::endl;
   m_logger << INFO << "DR(j,l) > pi/2		                                 " << nPassedLepJetDR2_ << " --- eff = " << (double)nPassedLepJetDR2_/nEvents_ << std::endl;
   m_logger << INFO << "Dphi(MET,j) > 2		                                 " << nPassedMETJetDPhi_ << " --- eff = " << (double)nPassedMETJetDPhi_/nEvents_ << std::endl;
   m_logger << INFO << "Dphi(j,W) > 2		                                 " << nPassedJetWDPhi_ << " --- eff = " << (double)nPassedJetWDPhi_/nEvents_ << std::endl;
   m_logger << INFO << "top mass cut		                                 " << nPassedTopMass_ << " --- eff = " << (double)nPassedTopMass_/nEvents_ << std::endl;
   m_logger << INFO << "tau 21 cut		                                 " << nPassedTau21Cut_ << " --- eff = " << (double)nPassedTau21Cut_/nEvents_ << std::endl;
   m_logger << INFO << "jet mass cut		                                 " << nPassedJetMass_ << " --- eff = " << (double)nPassedJetMass_/nEvents_ << std::endl;
   m_logger << INFO << "subjet b-tagging		                         " << nPassedNsubjBTagCut_ << " --- eff = " << (double)nPassedNsubjBTagCut_/nEvents_ << std::endl;
   m_logger << INFO << "WW mass window		                                 " << nPassedExoCandidateMass_ << " --- eff = " << (double)nPassedExoCandidateMass_/nEvents_ << std::endl;

   m_logger << INFO << std::endl; 
   
   return;

}

//==============================================================================================
void ExoDiBosonAnalysis::EndCycle() throw( SError ) {

   return;

}

//==============================================================================================
void ExoDiBosonAnalysis::printCutFlow( void ) {

   std::cout << std::endl; 
   std::cout << "############ Cut flow: ############" << std::endl;	
   std::cout << "number of events		                         " << nEvents_ << std::endl;
   std::cout << "passed filters		                                 " << nPassedFilters_ << " --- eff = " << (double)nPassedFilters_/nEvents_ << std::endl; 
   std::cout << "passed trigger		                                 " << nPassedTrigger_ << " --- eff = " << (double)nPassedTrigger_/nEvents_ << std::endl; 
   std::cout << "found lepton		                                 " << nPassedFoundLept_ << " --- eff = " << (double)nPassedFoundLept_/nEvents_ << std::endl;
   std::cout << "veto extra leptons		                         " << nPassedVetoExtraLeptons_ << " --- eff = " << (double)nPassedVetoExtraLeptons_/nEvents_ << std::endl;
   std::cout << "found jet candidate with pt cut loose (80 GeV)		 " << nPassedFoundJet_ << " --- eff = " << (double)nPassedFoundJet_/nEvents_ << std::endl;
   std::cout << "DR(j,l) > 1		                                 " << nPassedLepJetDR_ << " --- eff = " << (double)nPassedLepJetDR_/nEvents_ << std::endl;
   std::cout << "jet pt cut tight (200 GeV)		                 " << nPassedJetPtTight_ << " --- eff = " << (double)nPassedJetPtTight_/nEvents_ << std::endl;
   std::cout << "found MET 		                                 " << nPassedFoundMET_ << " --- eff = " << (double)nPassedFoundMET_/nEvents_ << std::endl;
   std::cout << "found W 		                                 " << nPassedFoundW_ << " --- eff = " << (double)nPassedFoundW_/nEvents_ << std::endl;
   std::cout << "additional jets cut		                         " << nPassedAJetCut_ << " --- eff = " << (double)nPassedAJetCut_/nEvents_ << std::endl;
   std::cout << "DR(j,l) > pi/2		                                 " << nPassedLepJetDR2_ << " --- eff = " << (double)nPassedLepJetDR2_/nEvents_ << std::endl;
   std::cout << "Dphi(MET,j) > 2		                         " << nPassedMETJetDPhi_ << " --- eff = " << (double)nPassedMETJetDPhi_/nEvents_ << std::endl;
   std::cout << "Dphi(j,W) > 2		                                 " << nPassedJetWDPhi_ << " --- eff = " << (double)nPassedJetWDPhi_/nEvents_ << std::endl;
   std::cout << "top mass cut		                                 " << nPassedTopMass_ << " --- eff = " << (double)nPassedTopMass_/nEvents_ << std::endl;
   std::cout << "tau 21 cut		                                 " << nPassedTau21Cut_ << " --- eff = " << (double)nPassedTau21Cut_/nEvents_ << std::endl;
   std::cout << "jet mass cut		                                 " << nPassedJetMass_ << " --- eff = " << (double)nPassedJetMass_/nEvents_ << std::endl;
   std::cout << "subjet b-tagging		                         " << nPassedNsubjBTagCut_ << " --- eff = " << (double)nPassedNsubjBTagCut_/nEvents_ << std::endl;
   std::cout << "WW mass window		                                 " << nPassedExoCandidateMass_ << " --- eff = " << (double)nPassedExoCandidateMass_/nEvents_ << std::endl;

   std::cout << std::endl; 
   
}

//==============================================================================================
void ExoDiBosonAnalysis::printDijetCutFlow( void ) {

   std::cout << std::endl; 
   std::cout << "############ Cut flow: ############" << std::endl;	
   std::cout << "number of events		                             " << nEvents_ << std::endl;
   std::cout << "passed filters		                                 " << nPassedFilters_ << " --- eff = " << (double)nPassedFilters_/nEvents_ << std::endl; 
   std::cout << "passed trigger		                                 " << nPassedTrigger_ << " --- eff = " << (double)nPassedTrigger_/nEvents_ << std::endl; 
   std::cout << "found jets		                                     " << nPassedFoundJets_ << " --- eff = " << (double)nPassedFoundJets_/nEvents_ << std::endl; 
   std::cout << "dEta cut	                                         " << nPassedJetsDEta_ << " --- eff = " << (double)nPassedJetsDEta_/nEvents_ << std::endl; 
   std::cout << "Mjj cut	                                         " << nPassedMjj_ << " --- eff = " << (double)nPassedMjj_/nEvents_ << std::endl; 
   std::cout << "jet mass cut		                                 " << nPassedJetMass_ << " --- eff = " << (double)nPassedJetMass_/nEvents_ << std::endl;

   std::cout << std::endl; 
   
}

//==============================================================================================
void ExoDiBosonAnalysis::fillDijetTree( void ){

  jet1_mass_pruned = fatJetCand_[0].prunedMass; 
  jet2_mass_pruned = fatJetCand_[1].prunedMass; 
  jet1_tau2tau1 = fatJetCand_[0].tau2/fatJetCand_[0].tau1;
  jet2_tau2tau1 = fatJetCand_[1].tau2/fatJetCand_[1].tau1;
  
  channel == -1;
  if( fatJetCand_[0].prunedMass > 65 && fatJetCand_[0].prunedMass < 105 &&
      fatJetCand_[1].prunedMass > 65 && fatJetCand_[1].prunedMass < 105 ) channel = 0; //VV
  if( fatJetCand_[0].prunedMass > 65 && fatJetCand_[0].prunedMass < 85 &&
      fatJetCand_[1].prunedMass > 65 && fatJetCand_[1].prunedMass < 85 ) channel = 1; //WW
  if( fatJetCand_[0].prunedMass > 85 && fatJetCand_[0].prunedMass < 105 &&
      fatJetCand_[1].prunedMass > 85 && fatJetCand_[1].prunedMass < 105 ) channel = 2; //ZZ
  if( (fatJetCand_[0].prunedMass > 65 && fatJetCand_[0].prunedMass < 85 &&
      fatJetCand_[1].prunedMass > 85 && fatJetCand_[1].prunedMass < 105) || 
      (fatJetCand_[0].prunedMass > 85 && fatJetCand_[0].prunedMass < 105 &&
      fatJetCand_[1].prunedMass > 65 && fatJetCand_[1].prunedMass < 85) ) channel = 3; //WZ
                   
}

//==============================================================================================
void ExoDiBosonAnalysis::fillTree( void ){

   	  run = data_.EVENT_run;
   	  event = data_.EVENT_event;
   	  lumi = data_.EVENT_lumi;
          jet_mass = fatJetCand_[0].p4.M();
          jet_mass_softdrop = fatJetCand_[0].softdropMass;
	  jet_mass_pruned = fatJetCand_[0].prunedMass;
	  jet_pt = fatJetCand_[0].p4.Pt();
	  jet_eta = fatJetCand_[0].p4.Eta();
	  jet_phi = fatJetCand_[0].p4.Phi();
	  jet_tau2tau1 = fatJetCand_[0].tau2/fatJetCand_[0].tau1;
	  l_pt  = leptonCand_[0].p4.Pt();
	  l_eta = leptonCand_[0].p4.Eta();
	  l_phi = leptonCand_[0].p4.Phi();
	  l_iso = leptonCand_[0].iso;
	  isGlobalMuon           = leptonCand_[0].isGlobalMuon;      
	  globalHits	   	 = leptonCand_[0].globalHits;	    
	  pixelHits	   	 = leptonCand_[0].pixelHits;	    
	  trackerHits	   	 = leptonCand_[0].trackerHits;      
	  matchedStations        = leptonCand_[0].matchedStations;   
	  bestTrack_ptErrRel	 = leptonCand_[0].bestTrack_ptErrRel;
	  d0		   	 = leptonCand_[0].d0;		    
	  dz		   	 = leptonCand_[0].dz;		    
	  Wlept_pt = WCand_[0].p4.Pt();
	  Wlept_mt = TMath::Sqrt( 2*METCand_[0].p4.Pt()*leptonCand_[0].p4.Pt()*(1-cos(leptonCand_[0].p4.DeltaPhi(METCand_[0].p4))) );
	  pfMET = METCand_[0].p4.Pt();
	  pfMETPhi = METCand_[0].p4.Phi();	
	  nPVs = data_.nPVs;
      
          nak4jets = AK4jetCand_.size();
	  ak4jet1_pt = -9999;
	  ak4jet2_pt = -9999;
	  ak4jet3_pt = -9999;
	  ak4jet1_csv = -9999;
	  ak4jet2_csv = -9999;
	  ak4jet3_csv = -9999;
	  if( nak4jets > 0){
	   ak4jet1_pt = AK4jetCand_[0].p4.Pt();
	   ak4jet1_csv = AK4jetCand_[0].csv;	   
	   if( nak4jets > 1){
	    ak4jet2_pt = AK4jetCand_[1].p4.Pt();
	    ak4jet2_csv = AK4jetCand_[1].csv;	   
	    if( nak4jets > 2){
	     ak4jet3_pt = AK4jetCand_[2].p4.Pt();
	     ak4jet3_csv = AK4jetCand_[2].csv;	   
	    }
	   }
	  }
	  
	  nsubj = 0;//SubjetCand_[0].size();
	  subj1csv = 0.;
	  subj2csv = 0.;
	  subj1flavor = 0.;
	  subj2flavor = 0.;
	  if( nsubj > 0 ){
	     subj1csv = SubjetCand_[0][0].csv;
	     subj1flavor = SubjetCand_[0][0].flavor;
	     subj1pt = SubjetCand_[0][0].p4.Pt();
	     subj1eta = SubjetCand_[0][0].p4.Eta();
	     if( nsubj > 1 ){
	        subj2csv = SubjetCand_[0][1].csv;
		subj2flavor = SubjetCand_[0][1].flavor;
		subj2pt = SubjetCand_[0][1].p4.Pt(); 
		subj2eta = SubjetCand_[0][1].p4.Eta(); 
	     }
	  }
	  
          channel = -1;
	  lep = -1;
          if( fatJetCand_[0].tau2/fatJetCand_[0].tau1 > 0. && fatJetCand_[0].tau2/fatJetCand_[0].tau1 < 0.6 ){
	     if( Channel_.find("mu") != std::string::npos ){
	         channel = 1;
		 lep = 1;
		 //if( nsubjbtag == 0 ) channel = 7;
		 //if( nsubjbtag == 1 ) channel = 9;
		 //if( nsubjbtag == 2 ) channel = 11;
	     }
	     else if( Channel_.find("el") != std::string::npos ){
	         channel = 0;
		 lep = 0;
		 //if( nsubjbtag == 0 ) channel = 6;
		 //if( nsubjbtag == 1 ) channel = 8;
		 //if( nsubjbtag == 2 ) channel = 10;
             }
	  }
	  else if( fatJetCand_[0].tau2/fatJetCand_[0].tau1 > 0.6 && fatJetCand_[0].tau2/fatJetCand_[0].tau1 < 0.75 ){
	     if( Channel_.find("mu") != std::string::npos ){
	         channel = 3;
		 lep = 1;
		 //if( nsubjbtag == 0 ) channel = 13;
		 //if( nsubjbtag == 1 ) channel = 15;
		 //if( nsubjbtag == 2 ) channel = 17;		 
	     }
	     else if( Channel_.find("el") != std::string::npos ){
	         channel = 2;
		 lep = 0;
		 //if( nsubjbtag == 0 ) channel = 12;
		 //if( nsubjbtag == 1 ) channel = 14;
		 //if( nsubjbtag == 2 ) channel = 16;
	     }	  
	  }
	  else{
	     if( Channel_.find("mu") != std::string::npos ){
	         channel = 5;
		 lep = 1;
		 //if( nsubjbtag == 0 ) channel = 19;
		 //if( nsubjbtag == 1 ) channel = 21;
		 //if( nsubjbtag == 2 ) channel = 23;
	     } 
	     else if( Channel_.find("el") != std::string::npos ){
	         channel = 4;
		 lep = 0;
		 //if( nsubjbtag == 0 ) channel = 18;
		 //if( nsubjbtag == 1 ) channel = 20;
		 //if( nsubjbtag == 2 ) channel = 22;		 
	     } 
	  }
	     	  	  	            
}

//==============================================================================================
bool ExoDiBosonAnalysis::run4Synch( void ){

   bool DEBUG = false;
      
   /************ reset variables *************/   
   run = data_.EVENT_run;
   event = data_.EVENT_event;
   lumi = data_.EVENT_lumi;
   nPV = data_.nPVs;
   l_eta = -99;
   l_phi = -99;
   l_pt = -99;
   jet_pt = -99;
   jet_eta = -99;
   jet_phi = -99;
   jet_mass_pruned = -99;
   jet_mass_softdrop = -99;
   jet_tau2tau1 = -99;
   W_pt = -99;
   W_eta = -99;
   W_phi = -99;
   m_lvj = -99;
   njets = 0;
   jet2_pt = -99;
   jet2_btag = -99;
   jet3_pt = -99;
   jet3_btag = -99;
   nbtag = 0;     
   nLooseEle = 0;
   nLooseMu = 0;

   /************ fill variables *************/         
   pfMET = METCand_[0].p4.Pt();
   pfMETPhi = METCand_[0].p4.Phi();
   
   l_pt = leptonCand_[0].p4.Pt();
   l_eta = leptonCand_[0].p4.Eta();
   l_phi = leptonCand_[0].p4.Phi();

   jet_pt = fatJetCand_[0].p4.Pt();
   jet_eta = fatJetCand_[0].p4.Eta();
   jet_phi = fatJetCand_[0].p4.Phi();
   jet_mass_pruned = fatJetCand_[0].prunedMass;
   jet_mass_softdrop = fatJetCand_[0].softdropMass;
   jet_tau2tau1 = fatJetCand_[0].tau2/fatJetCand_[0].tau1;

   njets = AK4jetCand_.size();
   if( njets != 0 ){
      jet2_pt = AK4jetCand_[0].p4.Pt();
      jet2_btag = AK4jetCand_[0].csv;
      if( njets > 1 ){
         jet3_pt = AK4jetCand_[1].p4.Pt();
         jet3_btag = AK4jetCand_[1].csv;
      }
   }

   for( unsigned int j = 0; j < AK4jetCand_.size(); ++j ){
      if( AK4jetCand_[j].csv > bTagWPmap_[BtagVetoWP_] ) nbtag++;
   }    

   W_pt = (leptonCand_[0].p4+METCand_[0].p4).Pt();
   //W_eta = WCand_[0].p4.Eta();
   W_phi = WCand_[0].p4.Phi();
         
   TLorentzVector p4nu2 = getp4NuMethod2();
   m_lvj = (p4nu2 + leptonCand_[0].p4 + fatJetCand_[0].p4).M();  
   W_eta = (p4nu2 + leptonCand_[0].p4).Eta(); 
         
   return true;
         
}
