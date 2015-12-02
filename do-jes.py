#python do-jes.py -T W -c mu -S -s BulkGraviton -C HP
import xml.etree.ElementTree as ET
import os,commands
import sys
from optparse import OptionParser
import ConfigParser
import ROOT
from ROOT import *

argv = sys.argv
parser = OptionParser()
parser.add_option('-c', '--channel',action="store",type="string",dest="channel",default="el")
parser.add_option('-C', '--category',action="store",type="string",dest="category",default="HP")
parser.add_option('-T', '--tagging',action="store",type="string",dest="tagging",default="")
parser.add_option("-S", "--syst", dest="syst", default=False, action="store_true",help="do systematics")
parser.add_option('-s', '--signal',action="store",type="string",dest="signal",default="Wprime")
(opts, args) = parser.parse_args(argv)

status,ls_la = commands.getstatusoutput( 'ls -l centralValueJES' ) 													      
if status:																				      
   os.system('mkdir centralValueJES')   

status,ls_la = commands.getstatusoutput( 'ls -l JESUp' )													      
if status:																				      
   os.system('mkdir JESUp')

status,ls_la = commands.getstatusoutput( 'ls -l JESDown' )													      
if status:																				      
   os.system('mkdir JESDown')

if opts.tagging == 'W':
 mlo = 65
 mhi = 85
elif opts.tagging == 'Z':
  mlo = 85
  mhi = 105
else:
  mlo = 65
  mhi = 105

print mlo,mhi
if opts.signal == "BulkGraviton":       
 masses = [800,1200,1400,1600,1800,2000,2500,3000,3500,4000,4500]
else: masses = [800,1000,1200,1400,1600,1800,2000,2500,3000,3500,4000,4500] 
#masses = [800]

if opts.syst:														 

 # get muon channel xml config file and parse																       
 xmlfile = 'config/%s_%s_JESsys.xml' %(opts.signal,opts.channel)															       

 tree = ET.parse(xmlfile)																		       
 root = tree.getroot()  																		       

 ############### do central value ####################																		                   
 status,ls_la = commands.getstatusoutput( 'ls -l centralValueJES/%s'%(opts.category+opts.tagging) )													       
 if status:																				       
    os.system('mkdir centralValueJES/%s'%(opts.category+opts.tagging)) 																	       

 r = root.find('Cycle').find('UserConfig')																    
 for i in r.findall('Item'):																		    																    																	    
    if i.get('Name') == 'Tau21Cut':		    
       i.set('Value',opts.category)
    if i.get('Name') == 'ScalePrunedMassUp':		    
       i.set('Value','false')
    if i.get('Name') == 'ScalePrunedMassDown':		    
       i.set('Value','false')
    if i.get('Name') == 'ScalePrunedMassResidual':		    
       i.set('Value','0')
    if i.get('Name') == 'JetMassResolutionUpDown':		    
       i.set('Value','0')
    if i.get('Name') == 'JetEnergyResolutionUpDown':		    
       i.set('Value','0')
    if i.get('Name') == 'ScaleJESUp':		    
       i.set('Value','false')
    if i.get('Name') == 'ScaleJESDown':		    
       i.set('Value','false')                            
    if i.get('Name') == 'mLow':		    
       i.set('Value',str(mlo))
    if i.get('Name') == 'mHigh':		    
       i.set('Value',str(mhi))
                             																					    
 with open('config/syst/docentralValueJES_%s_%s_%s.xml'%(opts.channel,opts.category+opts.tagging,opts.signal), 'w') as f:													    
  f.write('<?xml version="1.0" encoding="UTF-8"?>\n<!DOCTYPE JobConfiguration PUBLIC "" "/shome/jngadiub/EXOVVAnalysisRunII/SFrame-04-00-01/user/config/JobConfig.dtd">\n')      
  tree.write(f, 'utf-8')																		    
 																					    
 cmd = 'sframe_main config/syst/docentralValueJES_%s_%s_%s.xml' %(opts.channel,opts.category+opts.tagging,opts.signal)												    
 print cmd																				    
 os.system(cmd) 
 
 for mass in masses:																			    
  cmd = 'mv ../AnalysisOutput/JESsys/ExoDiBosonAnalysis.%s.M-%i.%s.root centralValueJES/%s/ExoDiBosonAnalysis.%s.M-%i.%s.root' %(opts.signal,mass,opts.channel,opts.category+opts.tagging,opts.signal,mass,opts.channel) 			    
  print cmd																				    
  os.system(cmd) 																			    

 ############### do btag sf up ####################																		       
 status,ls_la = commands.getstatusoutput( 'ls -l JESUp/%s'%(opts.category+opts.tagging) )													       
 if status:																				       
    os.system('mkdir JESUp/%s'%(opts.category+opts.tagging)) 																	       

 r = root.find('Cycle').find('UserConfig')																    
 for i in r.findall('Item'):																		    																	    																    
    if i.get('Name') == 'Tau21Cut':		    
       i.set('Value',opts.category)
    if i.get('Name') == 'ScalePrunedMassUp':		    
       i.set('Value','true')
    if i.get('Name') == 'ScalePrunedMassDown':		    
       i.set('Value','false')
    if i.get('Name') == 'ScalePrunedMassResidual':		    
       i.set('Value','0')
    if i.get('Name') == 'JetMassResolutionUpDown':		    
       i.set('Value','0')
    if i.get('Name') == 'JetEnergyResolutionUpDown':		    
       i.set('Value','0')
    if i.get('Name') == 'ScaleJESUp':		    
       i.set('Value','true')
    if i.get('Name') == 'ScaleJESDown':		    
       i.set('Value','false')  
    if i.get('Name') == 'mLow':		    
       i.set('Value',str(mlo))
    if i.get('Name') == 'mHigh':		    
       i.set('Value',str(mhi))
               																					    
 with open('config/syst/doJESUp_%s_%s_%s.xml'%(opts.channel,opts.category+opts.tagging,opts.signal), 'w') as f:													    
  f.write('<?xml version="1.0" encoding="UTF-8"?>\n<!DOCTYPE JobConfiguration PUBLIC "" "/shome/jngadiub/EXOVVAnalysisRunII/SFrame-04-00-01/user/config/JobConfig.dtd">\n')      
  tree.write(f, 'utf-8')																		    
 																					    
 cmd = 'sframe_main config/syst/doJESUp_%s_%s_%s.xml' %(opts.channel,opts.category+opts.tagging,opts.signal)												    
 print cmd																				    
 os.system(cmd) 
 
 for mass in masses:																			    
  cmd = 'mv ../AnalysisOutput/JESsys/ExoDiBosonAnalysis.%s.M-%i.%s.root JESUp/%s/ExoDiBosonAnalysis.%s.M-%i.%s.root' %(opts.signal,mass,opts.channel,opts.category+opts.tagging,opts.signal,mass,opts.channel) 			    
  print cmd																				    
  os.system(cmd) 

 ############### do btag sf down ####################																		       
 status,ls_la = commands.getstatusoutput( 'ls -l JESDown/%s'%(opts.category+opts.tagging) )													       
 if status:																				       
    os.system('mkdir JESDown/%s'%(opts.category+opts.tagging)) 																	       

 r = root.find('Cycle').find('UserConfig')																    
 for i in r.findall('Item'):																		    																	    																	    
    if i.get('Name') == 'Tau21Cut':		    
       i.set('Value',opts.category)
    if i.get('Name') == 'ScalePrunedMassUp':		    
       i.set('Value','false')
    if i.get('Name') == 'ScalePrunedMassDown':		    
       i.set('Value','true')
    if i.get('Name') == 'ScalePrunedMassResidual':		    
       i.set('Value','0')
    if i.get('Name') == 'JetMassResolutionUpDown':		    
       i.set('Value','0')
    if i.get('Name') == 'JetEnergyResolutionUpDown':		    
       i.set('Value','0')
    if i.get('Name') == 'ScaleJESUp':		    
       i.set('Value','false')
    if i.get('Name') == 'ScaleJESDown':		    
       i.set('Value','true') 
    if i.get('Name') == 'mLow':		    
       i.set('Value',str(mlo))
    if i.get('Name') == 'mHigh':		    
       i.set('Value',str(mhi))
               																					    
 with open('config/syst/doJESDown_%s_%s_%s.xml'%(opts.channel,opts.category+opts.tagging,opts.signal), 'w') as f:													    
  f.write('<?xml version="1.0" encoding="UTF-8"?>\n<!DOCTYPE JobConfiguration PUBLIC "" "/shome/jngadiub/EXOVVAnalysisRunII/SFrame-04-00-01/user/config/JobConfig.dtd">\n')      
  tree.write(f, 'utf-8')																		    
 																					    
 cmd = 'sframe_main config/syst/doJESDown_%s_%s_%s.xml' %(opts.channel,opts.category+opts.tagging,opts.signal)												    
 print cmd																				    
 os.system(cmd) 
 
 for mass in masses:																			    
  cmd = 'mv ../AnalysisOutput/JESsys/ExoDiBosonAnalysis.%s.M-%i.%s.root JESDown/%s/ExoDiBosonAnalysis.%s.M-%i.%s.root' %(opts.signal,mass,opts.channel,opts.category+opts.tagging,opts.signal,mass,opts.channel) 			    
  print cmd																				    
  os.system(cmd) 
          
##############################################################
#####calculate yields#####
##############################################################

outfile = open('JESsys_%s_%s_%s.txt'%(opts.channel,opts.category+opts.tagging,opts.signal),'w')
outfile.write('mass JESUp JESDown\n')
outfile.write('\n')
      
for mass in masses:

   print "######## Mass = %i #########" %mass
     
   fname = 'centralValueJES/%s/ExoDiBosonAnalysis.%s.M-%i.%s.root' %(opts.category+opts.tagging,opts.signal,mass,opts.channel)
   tfile = ROOT.TFile.Open(fname,'READ')
   cv = ROOT.TH1F(tfile.Get('nPassedExoCandidateMass')).GetBinContent(1)
   #cv = ROOT.TH1F(tfile.Get('AK8jetPrunedMass')).Integral()
   print "Central Value = %.3f" %(cv)
   tfile.Close()
   tfile.Delete() 

   fname = 'JESUp/%s/ExoDiBosonAnalysis.%s.M-%i.%s.root' %(opts.category+opts.tagging,opts.signal,mass,opts.channel)
   tfile = ROOT.TFile.Open(fname,'READ')
   #btagup = ROOT.TH1F(tfile.Get('AK8jetPrunedMass')).Integral()
   btagup = ROOT.TH1F(tfile.Get('nPassedExoCandidateMass')).GetBinContent(1)   
   print "JES sys up = %.3f" %(btagup)
   tfile.Close()
   tfile.Delete()

   fname = 'JESDown/%s/ExoDiBosonAnalysis.%s.M-%i.%s.root' %(opts.category+opts.tagging,opts.signal,mass,opts.channel)
   tfile = ROOT.TFile.Open(fname,'READ')
   #btagdown = ROOT.TH1F(tfile.Get('AK8jetPrunedMass')).Integral()
   btagdown = ROOT.TH1F(tfile.Get('nPassedExoCandidateMass')).GetBinContent(1)
   print "JES sys down = %.3f" %(btagdown)
   tfile.Close()
   tfile.Delete()
    
   sup = btagup-cv
   sdown = btagdown-cv
   #if sup < 0 and sdown < 0: sdown = -sdown      
     
   if opts.signal == 'BulkGraviton':  
    outfile.write('BulkG_WW_lvjj_M%i %.3f %.3f\n' %(mass,sup*100/cv,sdown*100/cv))
   elif opts.signal == 'Wprime':
    outfile.write('Wprime_WZ_lvjj_M%i %.3f %.3f\n' %(mass,sup*100/cv,sdown*100/cv))

outfile.close()


