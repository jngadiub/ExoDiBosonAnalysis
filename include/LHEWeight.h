#ifndef LHEWeight_H
#define LHEWeight_H

#include <string>
#include <vector>

class LHEWeight{

public:
   LHEWeight( void );
   ~LHEWeight( void );
   
   enum Sample { WJets, DYJets, None };
   
   void initLHEWeights(const LHEWeight::Sample sample);
   
   LHEWeight::Sample toSample(const std::string& str);
   std::string toString(const LHEWeight::Sample sample);
   
   double getLHEWeight( float pt );

private:
   /*double binEntriesIncl_         ;
   double countsIncl_             ;
   double xSecIncl_               ;
   std::vector<double> binEntries_;
   std::vector<double> counts_    ;
   std::vector<double> xSec_      ;*/
   
   std::vector<double> weights_map;
    
};

#endif //LHEWeight_H
