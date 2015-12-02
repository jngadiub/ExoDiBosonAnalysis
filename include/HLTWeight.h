#ifndef HLTWeight_H
#define HLTWeight_H

#include <string>
#include <vector>

class HLTWeight{

public:
   HLTWeight( void );
   ~HLTWeight( void );
   
   enum Channel { Mu, Ele, None };
   
   void initHLTWeights(const HLTWeight::Channel channel);
   
   HLTWeight::Channel toChannel(const std::string& str);
   std::string toString(const HLTWeight::Channel channel);
   
   double getHLTWeight( double pt, double eta );
   bool   isInEtaBin( int bin, double eta );
   bool   isInPtBin( int bin, double pt );

private:   
   std::vector<std::vector<double> > sf_weights_map;
   std::vector<double> hlt_weights_map;
   std::vector<double> eta_map_min;
   std::vector<double> eta_map_max;
   std::vector<double> pt_map_min;
   std::vector<double> pt_map_max;
       
};

#endif //HLTWeight_H
