# ExoDiBosonAnalysis
exo-vv analyzer

1) set ROOT environment (you can take it from from CMSSW > 74X )

2) check out and compile SFrame analysis framework

  mkdir YOURANALYSISDIR
  cd YOURANALYSISDIR
  svn co https://svn.code.sf.net/p/sframe/code/SFrame/tags/SFrame-04-00-01 SFrame-04-00-01
  cd SFrame-04-00-01
  source setup.sh
  make
  cd ../
  
3) create the ExoDiBosonAnalysis analysis package in SFrame otherwise SFrame does not know that it exists

  sframe_new_package.sh ExoDiBosonAnalysis
  cd ExoDiBosonAnalysis
  sframe_create_cycle.py -n ExoDiBosonAnalysis

4) fork the ExoDiBosonAnalysis repository into your git account
  
5) check out and compile ExoDiBosonAnalysis code
  
  export GITUSER=`git config user.github`
  echo "Your github username has been set to \"$GITUSER\""
  git clone git@github.com:${GITUSER}/ExoDiBosonAnalysis.git ExoDiBosonAnalysis_tmp
  cd ../
  rm -rf ExoDiBosonAnalysis
  mv ExoDiBosonAnalysis_tmp ExoDiBosonAnalysis
    
  git clone git@github.com:UZHCMS/GoodRunsLists.git
  cd GoodRunsLists
  make clean && make
  
  cd ../ExoDiBosonAnalysis
  make clean && make
  
6) run the ExoDiBosonAnalysis code

  sframe_main config/BulkGraviton_mu.xml  
