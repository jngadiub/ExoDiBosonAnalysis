#ifndef MUONCANDIDATE_H
#define MUONCANDIDATE_H

#include "include/RecoCandidate.h"

class MuonCandidate : public RecoCandidate {

public:
   MuonCandidate( TLorentzVector tlv );
   ~MuonCandidate( void );
     
   double iso;
      
private:

};

#endif // MUONCANDIDATE_H


