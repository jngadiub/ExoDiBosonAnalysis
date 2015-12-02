#ifndef JETCANDIDATE_H
#define JETCANDIDATE_H

#include "../ExoDiBosonAnalysis/include/RecoCandidate.h"

class JetCandidate : public RecoCandidate {

public:
   JetCandidate( TLorentzVector tlv );
   ~JetCandidate( void );
   
   float csv ;
   float mass;
   float prunedMass;
   float softdropMass;
   float tau1;
   float tau2;
   float tau3;
   int   flavor; 
   float rcn;
   float scale;
      
private:

};

#endif // JETCANDIDATE_H



