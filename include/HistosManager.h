#ifndef HISTOSMANAGER_H
#define HISTOSMANAGER_H

class ExoDiBosonAnalysis;

class HistosManager {

public:
   HistosManager( ExoDiBosonAnalysis * theAnalysis );
   ~HistosManager( void );

   void bookHistos       ( void );
   void formatHistos     ( void );
   
private:
   ExoDiBosonAnalysis* theAnalysis_;
   
};

#endif // HISTOSMANAGER_H
