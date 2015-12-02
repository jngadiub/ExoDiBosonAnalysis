#ifndef ExoDiBosonAnalysis_H
#define ExoDiBosonAnalysis_H

#include "core/include/SCycleBase.h"

#include "TLorentzVector.h"
#include "TRandom3.h"

#include "../ExoDiBosonAnalysis/include/InputData.h"
#include "../ExoDiBosonAnalysis/include/PUWeight.h"
#include "../ExoDiBosonAnalysis/include/HLTWeight.h"
#include "../ExoDiBosonAnalysis/include/BTagWeight.h"
#include "../ExoDiBosonAnalysis/include/LumiWeight.h"
#include "../ExoDiBosonAnalysis/include/JetCandidate.h"
#include "../ExoDiBosonAnalysis/include/LeptonCandidate.h"
#include "../ExoDiBosonAnalysis/include/METCandidate.h"
#include "../ExoDiBosonAnalysis/include/HiggsCandidate.h"
#include "../../GoodRunsLists/include/TGoodRunsListReader.h"

class HistosManager;
class NtupleManager;

class ExoDiBosonAnalysis : public SCycleBase {

public:
   ExoDiBosonAnalysis();
   ~ExoDiBosonAnalysis();

   virtual void BeginCycle() throw( SError );
   virtual void EndCycle() throw( SError );

   virtual void BeginInputData( const SInputData& ) throw( SError );
   virtual void EndInputData  ( const SInputData& ) throw( SError );

   virtual void BeginInputFile( const SInputData& ) throw( SError );

   virtual void ExecuteEvent( const SInputData&, Double_t ) throw( SError );
   
   void setGenCandidates          ( void );
   bool selectChannel             ( void );
   
   void setWeight                 ( TString infile );
   void initWeight                ( void );
   
   void initData                  ( void );
   void reset                     ( void );
   InputData& getData             ( void ){ return data_; }
   void setNtupleManager          ( NtupleManager* ntupleManager ){ theNtupleManager_ = ntupleManager; }
   void printCutFlow              ( void );
   bool runOnMC                   ( void ){return runOnMC_;}

   void fillHistos                ( void );
   
   double getMuonScale            ( double oldpt );
   double getPrunedMassScale      ( double prunedmass, double corrUp, double corrDown, double corr, double pt );
   double getJetEnergyScale       ( double oldpt, double corrUp, double corrDown, double corr, double eta );

   bool passedSelections          ( void );
   bool passedDijetSelections     ( void );
   bool passedTrigger             ( void );
   bool passedFilters             ( void );
   bool applyJSON                 ( void );

   bool findLeptonCandidate       ( void );     
   bool findMuonCandidate         ( void ); 
   bool findElectronCandidate     ( void ); 
   bool findMETCandidate          ( void );
   bool findMETCandidateForSys    ( void );
   bool findWCandidate            ( void );
   bool findJetCandidate          ( void );
   void findExtraJets             ( void );
   void findTopCandidate          ( void );
   void findExoCandidate          ( void );   
   TLorentzVector getp4Nu         ( void );
   TLorentzVector getp4NuMethod2  ( void );
   
   bool run4Synch                 ( void );
   void TriggerEfficiency         ( void );
   void FiltersEfficiency         ( void );
   void doPileUp                  ( void );
   void METnoHF                   ( void );
        
private:
   ClassDef( ExoDiBosonAnalysis, 0 );  
       
   HistosManager* theHistosManager_;
   NtupleManager* theNtupleManager_;
   InputData      data_            ;
   PUWeight       PUWeight_        ;
   HLTWeight      HLTWeight_       ;
   BTagWeight     BTagWeight_      ;
   LumiWeight     LumiWeight_      ;
   TH1F*          hPUweights_      ;
   std::map<std::string,double> bTagWPmap_;
   int            jetIndex_        ;
   TRandom3*      tr_              ;   
   TH1F*          hJMRSigmaMCPT_   ;
   TH1F*          hJERSigmaMCPT_   ;
   Root::TGoodRunsList m_grl;
   std::string    JSONfile_;

   std::map<int,TLorentzVector> genCandidates_  ;
   std::vector<LeptonCandidate> leptonCand_     ;
   std::vector<JetCandidate>    AK4jetCand_     ;
   std::vector<JetCandidate>    fatJetCand_     ;
   std::vector<METCandidate>    METCand_        ;
   std::vector<HiggsCandidate>  WCand_          ;
   std::vector<std::vector<JetCandidate> > SubjetCand_;

   // XML configuration //
   
   /* general settings */         
   std::string    InputTreeName_   ;
   std::string    OutputTreeName_  ;   
   bool           isSignal_        ;
   bool           runOnMC_         ;
   bool           genFilter_       ;
   std::string    Flavour_         ; 
   std::string    Channel_         ; 
   bool           Trigger_         ;
   bool           applyFilters_    ;
   bool           Synch_           ;
   bool           Pseudodata_      ;

   /* leptonic selections */
   double         leptPtCut_	   ;
   double         leptEtaCut_	   ;
   double         AleptPtCut_	   ;
   double         AleptEtaCut_     ;
   double         METCut_  	   ;
   double         WptCut_  	   ;
   
   /* jet selections */
   double         JetPtCutLoose_   ;
   double         JetPtCutTight_   ;
   double         JetEtaCut_	   ; 
   std::string    Tau21Cut_	   ;
   double         Tau21Low_        ;
   double         Tau21High_       ;  
   std::string    SubjetsBtagWP_   ;
   int            NsubjBTag_       ;
         
   /* btag veto */
   int            nAJetCut_	   ; // if it's -1 the cut is not applied
   std::string    BtagVetoWP_      ;

   /* back-to-back topology */
   bool           AngularCuts_     ;

   /* top mass veto */
   bool           TopMassCut_      ;
   double         leptTopMassLow_  ;
   double         leptTopMassHigh_ ;
   double         hadrTopMassLow_  ;
   double         hadrTopMassHigh_ ;
   
   /* pruned mass */
   std::string    JetMassAlgo_     ;
   bool           VetoSR_          ;
   double         mLow_		   ;
   double         mHigh_	   ;
    
   /* WW mass window */
   double         WWMass_          ; // if it's -1 no window is applied otherwise put the mass of the resonance and the 15% window is automatically taken into account
      
   /* weights settings */            
   double         xSec_            ;
   double         genEvents_       ;
   double         Lumi_            ;
   std::string    PUProfileData_   ;
   std::string    BTagEff4vetoData_  ;
   std::string    BTagEff4fatjetData_;
   std::string    BTagEff4subjetData_;
   
   /* systematics */
   bool           BtagSFSysUpVeto_  ;
   bool           BtagSFSysDownVeto_;
   bool           BtagSFSysUp_      ;
   bool           BtagSFSysDown_    ;
   int            ScaleMuonUpDown_  ;
   int            ScalePrunedMassResidual_;
   bool           ScalePrunedMassUp_  ;
   bool           ScalePrunedMassDown_;
   int            JetMassResolutionUpDown_;
   int            JetEnergyResolutionUpDown_;
   bool           ScaleJESUp_;
   bool           ScaleJESDown_;
   std::string    JMRSigmaMCPTData_;
   std::string    JERSigmaMCPTData_;

   // END OF XML CONFIGURATION //
      
   //tree variables//      
   float  weight_      ;
   float  genweight_   ;
   float  puweight_    ;
   float  hltweight_   ;
   float  btagweight_  ;
   float  lumiweight_  ;
   float  btagvetow    ;
   float  htagw        ;  
   int    channel      ;

   float  MWW              ;
   float  MWWmethod2       ;
   float  jet_mass         ;
   float  jet_mass_pruned  ;
   float  jet_mass_softdrop; 
   float  jet_pt           ; 
   float  jet_eta          ; 
   float  jet_phi          ; 
   float  jet_tau2tau1     ;
   float  l_pt             ; 
   float  l_eta            ; 
   float  l_phi            ; 
   float  l_iso            ; 
   int    isGlobalMuon     ;   
   int    globalHits       ;	  
   int    pixelHits        ; 
   int    trackerHits      ;   
   int    matchedStations  ;
   float  bestTrack_ptErrRel;
   float  d0               ;		  
   float  dz               ;	   
   float  Wlept_pt         ;
   float  Wlept_mt         ;
   float  pfMET            ;
   float  pfMETPhi         ;	           
   float  htopmass         ;
   float  ltopmass         ;
   bool   issignal         ;
   float  dr_lepjet        ; 
   float  dphi_metjet      ;
   float  dphi_jetw        ;
   int    nPVs             ;
   int    nsubj            ;
   int    nsubjbtag        ;
   int    nsubjbtagM       ;
   float  subj1csv         ;    
   float  subj2csv         ; 
   int    subj1flavor      ;
   int    subj2flavor      ;   
   float  subj1pt          ;    
   float  subj2pt          ; 
   float  subj1eta         ;    
   float  subj2eta         ; 
   float  ak4jet1_pt       ;	
   float  ak4jet2_pt       ; 
   float  ak4jet3_pt       ; 
   float  ak4jet1_csv      ;	
   float  ak4jet2_csv      ; 
   float  ak4jet3_csv      ; 
   int    nak4jets         ; 
            
   //other variables//      
   float  ltopmassMethod2;
   float  WMass        ;
   float  WMassMethod2 ;
   
   int    foundAEle_              ;
   int    foundAMu_               ;

   int    sumGenWeights_          ;

   int    nEvents_                ;
   int    nPassedTrigger_         ;  
   int    nPassedFilters_         ;  
   int    nPassedFoundLept_       ;
   int    nPassedVetoExtraLeptons_;
   int    nPassedFoundMET_        ;
   int    nPassedFoundW_          ;
   int    nPassedFoundJet_        ;
   int    nPassedLepJetDR_        ;
   int    nPassedJetPtTight_      ;
   int    nPassedAJetCut_         ;
   int    nPassedLepJetDR2_       ;
   int    nPassedMETJetDPhi_      ;
   int    nPassedJetWDPhi_        ;
   int    nPassedTopMass_         ;         
   int    nPassedJetMass_         ;
   int    nPassedTau21Cut_        ;
   int    nPassedNsubjBTagCut_    ;
   int    nPassedExoCandidateMass_;
   int    nPassedFilter_HBHE_;
   int    nPassedFilter_HBHEIso_;
   int    nPassedFilter_CSCHalo_;
   int    nPassedFilter_HCALlaser_;
   int    nPassedFilter_ECALDeadCell_;
   int    nPassedFilter_GoodVtx_;
   int    nPassedFilter_TrkFailure_;
   int    nPassedFilter_EEBadSc_;
   int    nPassedFilter_ECALlaser_;
   int    nPassedFilter_TrkPOG_;
   int    nPassedFilter_TrkPOG_manystrip_;
   int    nPassedFilter_TrkPOG_toomanystrip_;
   int    nPassedFilter_TrkPOG_logError_;
   int    nPassedFilter_METFilters_;
   int    nPassedFilter_EventList_;
   int    nPassedMETFiltersAll_;
   int    nPassedTrkFiltersAll_;
   int    nPassedGoodPVFilter_;
      
   /* for synch */
   int run;
   int event;
   int lumi;
   int nPV;

   //float pfMET;
   //float pfMETPhi;

   int nLooseEle; //number of electrons with looseID
   int nLooseMu; //number of electrons with looseID	

   //SELECTED LEPTON - the most energetic one satisfying HEEP_ID/HighPtMuon_ID :
   //float l_pt; 
   //float l_eta; 
   //float l_phi; 

   //FAT JET: the most energetic AK8 jet satisfying loosejetID && cleaned from the all HEEP/highPtMuon leptons in a cone dR=1.0:
   //float jet_pt; 
   //float jet_eta; 
   //float jet_phi; 
   //float jet_mass_pruned;
   //float jet_mass_softdrop; 
   //float jet_tau2tau1; 

   //W boson:
   float W_pt;
   float W_eta;
   float W_phi;

   //lvj MASS:
   float m_lvj;

   //AK4 JETS collection: - cleaned from the all HEEP/highPtMuon leptons && dR>=1.0 from the fat jet && isLooseJetId
   int njets;  //AK4 jets
   int nbtag;  //number of AK4 jets b-tagged with iCSVM
   float jet2_pt;  //1st most energetic AK4 
   float jet2_btag;  //1st most energetic AK4 
   float jet3_pt;  //2nd most energetic AK4 
   float jet3_btag;  //2nd most energetic AK4 
   

}; // class ExoDiBosonAnalysis

#endif // ExoDiBosonAnalysis_H

