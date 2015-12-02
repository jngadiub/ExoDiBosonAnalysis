#include "include/LumiWeight.h"

#include <iostream>

//==============================================================================================
LumiWeight::LumiWeight( void ){

}

//==============================================================================================
LumiWeight::~LumiWeight( void ){

}

//==============================================================================================
double LumiWeight::getLumiWeight( TString sample ){

   xSec_ = 1.;
   genEvents_ = 1.;
   
   //lumi weights for 50ns samples 
   if( sample.Contains("50ns") ){
   
      //single top samples
      if( sample.Contains( "ST_t-channel_top" ) ){
         xSec_ = 136.02*0.3272;
	 genEvents_ = 1273800.;      
      }
      else if( sample.Contains( "ST_t-channel_antitop" ) ){
         xSec_ = 80.95*0.3272;
	 genEvents_ = 681900.;                
      }
      else if( sample.Contains( "ST_tW_top" ) ){
         xSec_ = 35.6;
	 genEvents_ = 998400.;                
      }   
      else if( sample.Contains( "ST_tW_antitop" ) ){
         xSec_ = 35.6;
	 genEvents_ = 1000000.;                
      }      
      //VV samples
      else if( sample.Contains( "_WW_" ) ){
         xSec_ = 118.7;
         genEvents_ = 989608.;
      }
      else if( sample.Contains( "_WZ_" ) ){
         xSec_ = 66.1;
         genEvents_ = 996920.;
      }
      else if( sample.Contains( "_ZZ_" ) ){
         xSec_ = 15.4;
         genEvents_ = 998848.;
      } 	
      //W+Jets samples
      else if( sample.Contains( "WJetsToLNu" ) && !sample.Contains("_HT-") ){
         xSec_ = 61526.7;
         genEvents_ = 24089991.;
      }
      //TTbar samples 
      else if( sample.Contains( "TTJets" ) && sample.Contains( "amcatnlo" ) ){
         xSec_ = 831.76;
         genEvents_ = 4994250.;
      } 
      else if( sample.Contains( "TT_" ) && sample.Contains( "powheg" ) ){
         xSec_ = 831.76;
	 genEvents_ = 19665194.;
      }  
                
   }           
   //25 ns samples old version
   else if( !sample.Contains("50ns") && !sample.Contains("reMiniAOD") ){
      //single top samples
      if( sample.Contains( "ST_t-channel_top" ) ){
         xSec_ = 136.02*0.3272;
         genEvents_ = 3299800.;
      }  
      if( sample.Contains( "ST_t-channel_antitop" ) ){
         xSec_ = 80.95*0.3272;
         genEvents_ = 1695400.;
      }         
      else if( sample.Contains( "ST_s-channel" ) ){
         xSec_ = 11.36*0.3272;
         //genEvents_ = 984400.; //das
         genEvents_ = 613384.; //genweights
      }	  
      else if( sample.Contains( "ST_t-channel" ) && !(sample.Contains("top") || sample.Contains("antitop")) ){
         xSec_ = 216.99*0.3272;
         genEvents_ = 2966200.;
      }	
      else if( sample.Contains( "ST_tW_top" ) ){
         xSec_ = 35.6;
         genEvents_ = 995600.;
      } 
      else if( sample.Contains( "ST_tW_antitop" ) ){
         xSec_ = 35.6;
         genEvents_ = 1000000.;
      }   
      else if( sample.Contains( "TTJets" ) ){
         xSec_ = 831.76;
         //genEvents_ = 42730273.; //das
         genEvents_ = 14170480.; //genweights
      }
      else if( sample.Contains( "TT" ) && sample.Contains("powheg") ){
         xSec_ = 831.76;
         genEvents_ = 19899500.;
      }
      else if( sample.Contains( "_WW_" ) ){
         xSec_ = 118.7;
         genEvents_ = 994416.;
      }
      else if( sample.Contains( "_WZ_" ) ){
         xSec_ = 47.13;//66.1;
         genEvents_ = 991232.;
      }
      else if( sample.Contains( "_ZZ_" ) ){
         xSec_ = 16.5;//15.4;
         genEvents_ = 996168.;
      }      
      else if( sample.Contains( "WJetsToLNu_HT-100To200" ) ){
         xSec_ = 1.21*1347.;//1292.;
         genEvents_ = 10142187.;
      } 
      else if( sample.Contains( "WJetsToLNu_HT-200To400" ) ){
         xSec_ = 1.21*360.;//385.9;
         genEvents_ = 5231856.;
      } 
      else if( sample.Contains( "WJetsToLNu_HT-400To600" ) ){
         xSec_ = 1.21*48.9;//47.9;
         genEvents_ = 1901705.;
      } 
      else if( sample.Contains( "WJetsToLNu_HT-600ToInf" ) ){
         xSec_ = 1.21*18.77;//19.9;
         genEvents_ = 1036108.;
      } 	 
      else if( sample.Contains( "WJetsToLNu" ) && !sample.Contains("_HT-") ){
         xSec_ = 61526.7;
         genEvents_ = 24151270.;
      }
   
   }//25 ns reMiniAOD
   else{
      //single top samples
      if( sample.Contains( "ST_t-channel_top" ) ){
         xSec_ = 136.02*0.3272;
         genEvents_ = 3299800.;
      }  
      if( sample.Contains( "ST_t-channel_antitop" ) ){
         xSec_ = 80.95*0.3272;
         genEvents_ = 1680200.;
      }         
      if( sample.Contains( "ST_t-channel" ) && sample.Contains( "ext" ) ){
         xSec_ = 216.99*0.322;
         //genEvents_ = 29954054.; //das
	 genEvents_ =  6456052.; //gen weights
      }  
      else if( sample.Contains( "ST_s-channel" ) ){
         xSec_ = 11.36*0.3272;
         //genEvents_ = 984400.; //das
         genEvents_ = 613384.; //genweights
      }	  
      /*else if( sample.Contains( "ST_t-channel" ) && !(sample.Contains("top") || sample.Contains("antitop")) ){//wrong for reMiniAOD
         xSec_ = 216.99*0.3272;
         genEvents_ = 2966200.;
      }*/	
      else if( sample.Contains( "ST_tW_top" ) ){
         xSec_ = 35.6;
         genEvents_ = 995600.;
      } 
      else if( sample.Contains( "ST_tW_antitop" ) ){
         xSec_ = 35.6;
         genEvents_ = 988500.;
      }   
      /*else if( sample.Contains( "TTJets" ) ){ //wrong for reMiniAOD
         xSec_ = 831.76;
         //genEvents_ = 42730273.; //das
         genEvents_ = 14170480.; //genweights
      }*/
      else if( sample.Contains( "TT" ) && sample.Contains("powheg") ){
         xSec_ = 831.76;
         genEvents_ = 19757190.;
      }
      else if( sample.Contains( "_WW_" ) && !sample.Contains( "powheg" ) ){
         xSec_ = 118.7;
         genEvents_ = 993640.;
      }
      else if( sample.Contains( "_WW_" ) && sample.Contains( "powheg" ) ){
         xSec_ = 49.997;
         genEvents_ = 1951600.;
      }
      else if( sample.Contains( "_WZ_" ) && !sample.Contains( "amcatnlo" ) ){
         xSec_ = 47.13;
         genEvents_ = 978512.;
      }
       else if( sample.Contains( "_WZ_" ) && sample.Contains( "amcatnlo" ) ){
         xSec_ = 10.71;
         //genEvents_ = 978512.;//das
	 genEvents_ = 14346866; //gen weights
      }
      else if( sample.Contains( "_ZZ_" ) && !sample.Contains( "amcatnlo" ) ){
         xSec_ = 16.5;
         genEvents_ = 996944.;
      }      
      else if( sample.Contains( "_ZZ_" ) && sample.Contains( "amcatnlo" ) ){
         xSec_ = 3.22;
         //genEvents_ = 18790122.;//das
	 genEvents_ = 11863244.;//gen weights
      }  
      else if( sample.Contains( "WJetsToLNu_HT-100To200" ) ){
         xSec_ = 1.21*1345.;//1292.;
         genEvents_ = 10152718.;
      } 
      else if( sample.Contains( "WJetsToLNu_HT-200To400" ) ){
         xSec_ = 1.21*359.7;//385.9;
         genEvents_ = 5221599.;
      } 
      else if( sample.Contains( "WJetsToLNu_HT-400To600" ) ){
         xSec_ = 1.21*48.91;//47.9;
         genEvents_ = 1745914.;
      } 
      else if( sample.Contains( "WJetsToLNu_HT-600To800" ) ){
         xSec_ = 1.21*12.05;//47.9;
         genEvents_ = 4041997.;
      } 
       else if( sample.Contains( "WJetsToLNu_HT-800To1200" ) ){
         xSec_ = 1.21*5.501;//47.9;
         genEvents_ = 1574633.;
      } 
       else if( sample.Contains( "WJetsToLNu_HT-1200To2500" ) ){
         xSec_ = 1.21*1.329;//47.9;
         genEvents_ = 255637.;
      } 
       else if( sample.Contains( "WJetsToLNu_HT-2500ToInf" ) ){
         xSec_ = 1.21*0.03216;//47.9;
         genEvents_ = 253036.;
      } 
      else if( sample.Contains( "WJetsToLNu_HT-600ToInf" ) ){
         xSec_ = 1.21*18.77;//19.9;
         genEvents_ = 1039152.;
      } 	 
      /*else if( sample.Contains( "WJetsToLNu" ) && !sample.Contains("_HT-") ){ //wrong for reMiniAOD
         xSec_ = 61526.7;
         genEvents_ = 24151270.;
      }*/
   
   }
   
   //signal samples
   if( sample.Contains( "RSGravitonToWWToLNQQ" ) && sample.Contains( "M_600" ) ){ //ok
      xSec_ = 1.;
      genEvents_ = 32354.;   
   } 
   else if( sample.Contains( "RSGravitonToWWToLNQQ" ) && sample.Contains( "M_800" ) ){ //ok
      xSec_ = 1.;
      genEvents_ = 31906.;   
   } 
   else if( sample.Contains( "RSGravitonToWWToLNQQ" ) && sample.Contains( "M_1000" ) ){ //ok
      xSec_ = 1.;
      genEvents_ = 32448.;   
   } 
   else if( sample.Contains( "RSGravitonToWWToLNQQ" ) && sample.Contains( "M_1200" ) ){ //ok
      xSec_ = 1.;
      genEvents_ = 32252.;   
   } 
   else if( sample.Contains( "RSGravitonToWWToLNQQ" ) && sample.Contains( "M_1400" ) ){ //ok
      xSec_ = 1.;
      genEvents_ = 32275.;   
   } 
   else if( sample.Contains( "RSGravitonToWWToLNQQ" ) && sample.Contains( "M_1600" ) ){ //ok
      xSec_ = 1.;
      genEvents_ = 31971.;   
   }  
   else if( sample.Contains( "RSGravitonToWWToLNQQ" ) && sample.Contains( "M_1800" ) ){ //ok
      xSec_ = 1.;
      genEvents_ = 32021.;   
   } 
   else if( sample.Contains( "RSGravitonToWWToLNQQ" ) && sample.Contains( "M_2000" ) ){ //ok
      xSec_ = 1.;
      genEvents_ = 31295.;   
   } 
   else if( sample.Contains( "RSGravitonToWWToLNQQ" ) && sample.Contains( "M_2500" ) ){ //ok
      xSec_ = 1.;
      genEvents_ = 32032.;   
   } 
   else if( sample.Contains( "RSGravitonToWWToLNQQ" ) && sample.Contains( "M_3000" ) ){ //ok
      xSec_ = 1.;
      genEvents_ = 31374.;   
   } 
   else if( sample.Contains( "RSGravitonToWWToLNQQ" ) && sample.Contains( "M_3500" ) ){ //ok
      xSec_ = 1.;
      genEvents_ = 32194.;   
   } 
   else if( sample.Contains( "RSGravitonToWWToLNQQ" ) && sample.Contains( "M_4000" ) ){ //ok
      xSec_ = 1.;
      genEvents_ = 32207.;   
   } 
   else if( sample.Contains( "RSGravitonToWWToLNQQ" ) && sample.Contains( "M_4500" ) ){ //ok
      xSec_ = 1.;
      genEvents_ = 31551.;   
   }                                    
   else if( sample.Contains( "BulkGravToWWToWlepWhad" ) && sample.Contains( "M_800" ) ){ //ok
      xSec_ = 1.;
      genEvents_ = 50000.;   
   } 
   else if( sample.Contains( "BulkGravToWWToWlepWhad" ) && sample.Contains( "M_1000" ) ){ //ok
      xSec_ = 1.;
      genEvents_ = 50000.;   
   } 
   else if( sample.Contains( "BulkGravToWWToWlepWhad" ) && sample.Contains( "M_1200" ) ){ //ok
      xSec_ = 1.;
      genEvents_ = 50000.;   
   } 
   else if( sample.Contains( "BulkGravToWWToWlepWhad" ) && sample.Contains( "M_1400" ) ){ //ok
      xSec_ = 1.;
      genEvents_ = 50000.;   
   } 
   else if( sample.Contains( "BulkGravToWWToWlepWhad" ) && sample.Contains( "M_1600" ) ){ //ok
      xSec_ = 1.;
      genEvents_ = 49200.;   
   } 
   else if( sample.Contains( "BulkGravToWWToWlepWhad" ) && sample.Contains( "M_1800" ) ){ //ok
      xSec_ = 1.;
      genEvents_ = 48400.;   
   } 
   else if( sample.Contains( "BulkGravToWWToWlepWhad" ) && sample.Contains( "M_2000" ) ){ //ok
      xSec_ = 1.;
      genEvents_ = 50000.;   
   } 
   else if( sample.Contains( "BulkGravToWWToWlepWhad" ) && sample.Contains( "M_2500" ) ){ //ok
      xSec_ = 1.;
      genEvents_ = 48400.;   
   } 
   else if( sample.Contains( "BulkGravToWWToWlepWhad" ) && sample.Contains( "M_3000" ) ){ //ok
      xSec_ = 1.;
      genEvents_ = 49800.;   
   } 
   else if( sample.Contains( "BulkGravToWWToWlepWhad" ) && sample.Contains( "M_3500" ) ){ //ok
      xSec_ = 1.;
      genEvents_ = 49700.;   
   } 
   else if( sample.Contains( "BulkGravToWWToWlepWhad" ) && sample.Contains( "M_4000" ) ){ //ok
      xSec_ = 1.;
      genEvents_ = 50000.;   
   } 
   else if( sample.Contains( "BulkGravToWWToWlepWhad" ) && sample.Contains( "M_4500" ) ){ //ok
      xSec_ = 1.;
      genEvents_ = 47600.; //50000.  
   } 
   else if( sample.Contains( "WprimeToWZToWlepZhad" ) && sample.Contains( "M-800" ) ){ //ok
      xSec_ = 1.;
      genEvents_ = 50000.;   
   }                              
   else if( sample.Contains( "WprimeToWZToWlepZhad" ) && sample.Contains( "M-1000" ) ){ //ok
      xSec_ = 1.;
      genEvents_ = 50000.;   
   }  
   else if( sample.Contains( "WprimeToWZToWlepZhad" ) && sample.Contains( "M-1200" ) ){ //ok
      xSec_ = 1.;
      genEvents_ = 50000.;   
   }  
   else if( sample.Contains( "WprimeToWZToWlepZhad" ) && sample.Contains( "M-1400" ) ){ //ok
      xSec_ = 1.;
      genEvents_ = 50000.;   
   }  
   else if( sample.Contains( "WprimeToWZToWlepZhad" ) && sample.Contains( "M-1600" ) ){ //ok
      xSec_ = 1.;
      genEvents_ = 49200.;   
   }  
   else if( sample.Contains( "WprimeToWZToWlepZhad" ) && sample.Contains( "M-1800" ) ){ //ok
      xSec_ = 1.;
      genEvents_ = 49800.;   
   }                              
   else if( sample.Contains( "WprimeToWZToWlepZhad" ) && sample.Contains( "M-2000" ) ){ //ok
      xSec_ = 1.;
      genEvents_ = 50000.;   
   }  
   else if( sample.Contains( "WprimeToWZToWlepZhad" ) && sample.Contains( "M-2500" ) ){ //ok
      xSec_ = 1.;
      genEvents_ = 50000.;   
   }  
   else if( sample.Contains( "WprimeToWZToWlepZhad" ) && sample.Contains( "M-3000" ) ){ //ok
      xSec_ = 1.;
      genEvents_ = 49600.;   
   }  
   else if( sample.Contains( "WprimeToWZToWlepZhad" ) && sample.Contains( "M-3500" ) ){ //ok
      xSec_ = 1.;
      genEvents_ = 50000.;   
   } 
   else if( sample.Contains( "WprimeToWZToWlepZhad" ) && sample.Contains( "M-4000" ) ){ //ok
      xSec_ = 1.;
      genEvents_ = 50000.;   
   }  
   else if( sample.Contains( "WprimeToWZToWlepZhad" ) && sample.Contains( "M-4500" ) ){ //ok
      xSec_ = 1.;
      genEvents_ = 50000.;   
   } 
   return xSec_/genEvents_;
      
}
