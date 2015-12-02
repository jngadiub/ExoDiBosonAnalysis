#ifndef MATCHINGTOOLS_H
#define MATCHINGTOOLS_H

#include <vector>
#include <TLorentzVector.h>

class InputData;
class LeptonCandidate;
class JetCandidate;

namespace MatchingTools {
 
   std::vector<LeptonCandidate> findMuonsMatch    ( TLorentzVector genMu , InputData& data );
   std::vector<LeptonCandidate> findElectronsMatch( TLorentzVector genEle, InputData& data );
   std::vector<JetCandidate>    findAK4JetsMatch  ( TLorentzVector genQ  , InputData& data );
   std::vector<JetCandidate>    findAK8JetsMatch  ( TLorentzVector genQ  , InputData& data );
   
};

#endif // MATCHINGTOOLS_H
