#ifndef BTagWeight_H
#define BTagWeight_H

#include "TLorentzVector.h"

#include <string>
#include <vector>

class JetCandidate;

class BTagWeight{

public:
   BTagWeight( void );
   ~BTagWeight( void );  
   
   void initBTagWeights(const std::string& eff4vetoFile, const std::string& eff4fatjetFile, const std::string& eff4subjetFile );    

   double getBTagWeight       ( JetCandidate jet, std::string which );   
   double getBTagWeight       ( std::vector<JetCandidate> jets, std::string which );
   double getBTagSFWeightUp   ( std::vector<JetCandidate> jets, std::string which );
   double getBTagSFWeightDown ( std::vector<JetCandidate> jets, std::string which );
   double getBTagEffWeightUp  ( std::vector<JetCandidate> jets, std::string which );
   double getBTagEffWeightDown( std::vector<JetCandidate> jets, std::string which );
   void   getEff              ( float pt, float eta, int flavor, std::string which );
   void   getSFM              ( float pt, float eta, int flavor );
   void   getSFL              ( float pt, float eta, int flavor );

private:   

   std::string eff4vetoFilename_  ;
   std::string eff4fatjetFilename_;
   std::string eff4subjetFilename_;
   
   std::vector<double> jetEff;
   std::vector<double> jetEff_e;
   std::vector<double> jetSF;
   std::vector<double> jetSF_e_up;
   std::vector<double> jetSF_e_down;
   
   int scale_b_    ;
   int scale_light_;
    
};

#endif //BTagWeight_H
