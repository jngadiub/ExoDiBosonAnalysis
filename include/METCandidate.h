#ifndef METCANDIDATE_H
#define METCANDIDATE_H

#include "../ExoDiBosonAnalysis/include/RecoCandidate.h"

class METCandidate : public RecoCandidate {

public:
   METCandidate( TLorentzVector tlv );
   ~METCandidate( void );
    
   double sumEt;
      
private:

};

#endif // METCANDIDATE_H
