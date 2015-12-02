#ifndef RECOCANDIDATE_H
#define RECOCANDIDATE_H

#include "TLorentzVector.h"

class RecoCandidate {

public:
   RecoCandidate( TLorentzVector tlv );
   ~RecoCandidate( void );
   
   TLorentzVector  p4;
   
private:

};

#endif // RECOCANDIDATE_H
