from optparse import OptionParser
import ROOT
import sys
import ConfigParser
import time
import gc
import math
from array import array

def count_events(fname,k):

   #print fname
   f = ROOT.TFile.Open(fname,"READ")
   h = ROOT.TH1F(f.Get("CA8bjetPrunedMass"))
   nevents = (ROOT.TH1F(f.Get("nPassedExoCandidateMass"))).GetBinContent(1)
      
   error1 = math.sqrt(nevents)/nevents

   err = h.Integral()*k*error1
   y = h.Integral()*k

   f.Close()
   f.Delete()
      
   return [y,err]

def fitEXO(stepSize):

   fit_par = 2
   gMinuit = ROOT.TMinuit(fit_par)
   gMinuit.SetFCN(ROOT.fcn)	

   gMinuit.SetErrorDef(1)

   ierflg = ROOT.Long(0)

   # Set starting values and step sizes for parameters
   vstart = []
   vstart.append(1.)	# TTbar
   vstart.append(1.)	# Wjets

   step = [stepSize,stepSize]

   gMinuit.mnparm(0,	"TTbar", 	vstart[0], step[0],	1.,	1.2,	ierflg)
   gMinuit.mnparm(1,	"Wjets",	vstart[1], step[1], 	1.,	2.,	ierflg)

   # Now ready for minimization step
   gMinuit.mnexcm("SET STR",array('d',[2]),1,ierflg); 
   gMinuit.mnexcm("MIGRAD", array('d',[500]) ,1,ierflg);

   # Print results
   amin = ROOT.Double(0.)
   edm = ROOT.Double(0.) 
   errdef = ROOT.Double(0.)
   nvpar = ROOT.Long(1)
   nparx = ROOT.Long(1)
   icstat = ROOT.Long(1)
   gMinuit.mnstat(amin,edm,errdef,nvpar,nparx,icstat);
   gMinuit.mnprin(3,amin);

   SF = []
   SFerr = []
   for i in xrange(0,fit_par):
      par = ROOT.Double(0.)
      err = ROOT.Double(0.)
      gMinuit.GetParameter(i, par, err)
      SF.append(par)
      SFerr.append(err)

   return [SF,SFerr]
                       
argv = sys.argv
parser = OptionParser()
parser.add_option("-C", "--config", dest="config", default=[], action="append",
                              help="configuration")
(opts, args) = parser.parse_args(argv)
print opts.config

config = ConfigParser.ConfigParser()
config.read(opts.config)

prefix = eval(config.get('FITEXO','prefix'))
bkgfiles = eval(config.get('FITEXO','filelist'))
lumi = eval(config.get('FITEXO','lumi'))
datafiles = eval(config.get('FITEXO','data'))

print "------------------------ Lumi -----------------------------"
for k, v in lumi.iteritems():
   print "Lumi %s = %.0f" %(k,v)
print "------------------ Input files directory ------------------"
for k, v in prefix.iteritems():
   print "%s : %s" %(k,v)
print "----------------------- data files ------------------------"
for k, v in datafiles.iteritems():
   print "%s : %s" %(k,v)
print "---------------------- backgrounds ------------------------"
for k, v in bkgfiles.iteritems():   
   print "%s : %s" %(k,v)
print "-----------------------------------------------------------"

data = array('d',[])
dataerr = array('d',[])
TTbar = array('d',[])
TTbarerr = array('d',[])
Wjets = array('d',[])
Wjetserr = array('d',[])
STop = []
SToperr = []
VV = []
VVerr = []
Zjets = []
Zjetserr = []

print ""
print "################### Final Yields #######################"
print ""
print "==== Data: "

for k,v in prefix.iteritems():
   yields = count_events(v+datafiles[k],1.)
   data.append(yields[0])
   dataerr.append(yields[1])
   print "    * %s : %.2f +/- %.2f" %(k,yields[0],yields[1])

print "==== TTbar: "
for k,v in prefix.iteritems():
   yields = count_events(v+bkgfiles['TTbar'],lumi[k])
   TTbar.append(yields[0])
   TTbarerr.append(yields[1])
   print "    * %s : %.2f +/- %.2f" %(k,yields[0],yields[1])

print "==== Wjets: "
for k,v in prefix.iteritems():
   yields = count_events(v+bkgfiles['Wjets'],lumi[k]*29./23.5)
   Wjets.append(yields[0])
   Wjetserr.append(yields[1])
   print "    * %s : %.2f +/- %.2f" %(k,yields[0],yields[1])

print "==== STop: "
for k,v in prefix.iteritems():
   yields = count_events(v+bkgfiles['STop'],lumi[k])
   STop.append(yields[0])
   SToperr.append(yields[1])
   print "    * %s : %.2f +/- %.2f" %(k,yields[0],yields[1])

print "==== VV: "
for k,v in prefix.iteritems():
   yields = count_events(v+bkgfiles['VV'],lumi[k])
   VV.append(yields[0])
   VVerr.append(yields[1])
   print "    * %s : %.2f +/- %.2f" %(k,yields[0],yields[1])
   
#print "==== Zjets: "
#for k,v in prefix.iteritems():
#   yields = count_events(v+bkgfiles['Zjets'],lumi[k]*1.19)
#   Zjets.append(yields[0])
#   Zjetserr.append(yields[1])
#   print "    * %s : %.2f +/- %.2f" %(k,yields[0],yields[1])   

MC = array('d',[])
for i in xrange(0,4):
   MC.append(STop[i]+VV[i])
   #MC.append(STop[i]+VV[i]+Zjets[i])

MCerr = array('d',[])
for i in xrange(0,4):
   #errB = math.sqrt( math.pow(TTbarerr[i],2) + math.pow(Wjetserr[i],2) + math.pow(VVerr[i],2) + math.pow(SToperr[i],2) + math.pow(Zjetserr[i],2) )
   errB = math.sqrt( math.pow(TTbarerr[i],2) + math.pow(Wjetserr[i],2) + math.pow(VVerr[i],2) + math.pow(SToperr[i],2) )
   MCerr.append(errB)
   
#===============================================================================================%
ROOT.gROOT.ProcessLine(".L fitEXO.cxx+")

ROOT.InitData(data,dataerr,MC,TTbar,Wjets,MCerr)
ROOT.PrintData()

SF = fitEXO(0.001)

print ""
print ""
print ""
print "###################### Fit results #########################"
print ""
print "  * SF_ttbar = %f +/- %f" %(SF[0][0],SF[1][0])
print "  * SF_wjets = %f +/- %f" %(SF[0][1],SF[1][1])
print ""

