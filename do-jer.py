#python do-JER.py -T W -c mu -S -s BulkGraviton -C HP
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
parser.add_option("-S", "--syst", dest="syst", default=False, action="store_true",help="do systematics")
parser.add_option('-s', '--signal',action="store",type="string",dest="signal",default="Wprime")
(opts, args) = parser.parse_args(argv)

status,ls_la = commands.getstatusoutput( 'ls -l centralValueJER' ) 													      
if status:																				      
   os.system('mkdir centralValueJER')   

status,ls_la = commands.getstatusoutput( 'ls -l JERUp' )													      
if status:																				      
   os.system('mkdir JERUp')

status,ls_la = commands.getstatusoutput( 'ls -l JERDown' )													      
if status:																				      
   os.system('mkdir JERDown')

if opts.signal == "BulkGraviton":       
 masses = [800,1200,1400,1600,1800,2000,2500,3000,3500,4000,4500]
else: masses = [800,1000,1200,1400,1600,1800,2000,2500,3000,3500,4000,4500] 
#masses = [800]

if opts.syst:														 

 # get muon channel xml config file and parse																       
 xmlfile = 'config/%s_%s_JERsys.xml' %(opts.signal,opts.channel)															       

 tree = ET.parse(xmlfile)																		       
 root = tree.getroot()  																		       

 ############### do central value ####################																		                   
 status,ls_la = commands.getstatusoutput( 'ls -l centralValueJER/')													       
 if status:																				       
    os.system('mkdir centralValueJER/') 																	       

 r = root.find('Cycle').find('UserConfig')																    
 for i in r.findall('Item'):																		    																    																	    
    if i.get('Name') == 'ScalePrunedMassUp':		    
       i.set('Value','false')
    if i.get('Name') == 'ScalePrunedMassDown':		    
       i.set('Value','false')
    if i.get('Name') == 'ScalePrunedMassResidual':		    
       i.set('Value','0')
    if i.get('Name') == 'JetMassResolutionUpDown':		    
       i.set('Value','0')
    if i.get('Name') == 'JetEnergyResolutionUpDown':		    
       i.set('Value','-2')
    if i.get('Name') == 'ScaleJERUp':		    
       i.set('Value','false')
    if i.get('Name') == 'ScaleJERDown':		    
       i.set('Value','false')                              
                             																					    
 with open('config/syst/docentralValueJER_%s_%s.xml'%(opts.channel,opts.signal), 'w') as f:													    
  f.write('<?xml version="1.0" encoding="UTF-8"?>\n<!DOCTYPE JobConfiguration PUBLIC "" "/shome/jngadiub/EXOVVAnalysisRunII/SFrame-04-00-01/user/config/JobConfig.dtd">\n')      
  tree.write(f, 'utf-8')																		    
 																					    
 cmd = 'sframe_main config/syst/docentralValueJER_%s_%s.xml' %(opts.channel,opts.signal)												    
 print cmd																				    
 os.system(cmd) 
 
 for mass in masses:																			    
  cmd = 'mv ../AnalysisOutput/JERsys/ExoDiBosonAnalysis.%s.M-%i.%s.root centralValueJER/ExoDiBosonAnalysis.%s.M-%i.%s.root' %(opts.signal,mass,opts.channel,opts.signal,mass,opts.channel) 			    
  print cmd																				    
  os.system(cmd) 																			    

 ############### do btag sf up ####################																		       
 status,ls_la = commands.getstatusoutput( 'ls -l JERUp/')													       
 if status:																				       
    os.system('mkdir JERUp/') 																	       

 r = root.find('Cycle').find('UserConfig')																    
 for i in r.findall('Item'):																		    																	    																    
    if i.get('Name') == 'ScalePrunedMassUp':		    
       i.set('Value','false')
    if i.get('Name') == 'ScalePrunedMassDown':		    
       i.set('Value','false')
    if i.get('Name') == 'ScalePrunedMassResidual':		    
       i.set('Value','0')
    if i.get('Name') == 'JetMassResolutionUpDown':		    
       i.set('Value','0')
    if i.get('Name') == 'JetEnergyResolutionUpDown':		    
       i.set('Value','1')
    if i.get('Name') == 'ScaleJERUp':		    
       i.set('Value','false')
    if i.get('Name') == 'ScaleJERDown':		    
       i.set('Value','false')    
               																					    
 with open('config/syst/doJERUp_%s_%s.xml'%(opts.channel,opts.signal), 'w') as f:													    
  f.write('<?xml version="1.0" encoding="UTF-8"?>\n<!DOCTYPE JobConfiguration PUBLIC "" "/shome/jngadiub/EXOVVAnalysisRunII/SFrame-04-00-01/user/config/JobConfig.dtd">\n')      
  tree.write(f, 'utf-8')																		    
 																					    
 cmd = 'sframe_main config/syst/doJERUp_%s_%s.xml' %(opts.channel,opts.signal)												    
 print cmd																				    
 os.system(cmd) 
 
 for mass in masses:																			    
  cmd = 'mv ../AnalysisOutput/JERsys/ExoDiBosonAnalysis.%s.M-%i.%s.root JERUp/ExoDiBosonAnalysis.%s.M-%i.%s.root' %(opts.signal,mass,opts.channel,opts.signal,mass,opts.channel) 			    
  print cmd																				    
  os.system(cmd) 

 ############### do btag sf down ####################																		       
 status,ls_la = commands.getstatusoutput( 'ls -l JERDown/')													       
 if status:																				       
    os.system('mkdir JERDown/') 																	       

 r = root.find('Cycle').find('UserConfig')																    
 for i in r.findall('Item'):																		    																	    																	    
    if i.get('Name') == 'ScalePrunedMassUp':		    
       i.set('Value','false')
    if i.get('Name') == 'ScalePrunedMassDown':		    
       i.set('Value','false')
    if i.get('Name') == 'ScalePrunedMassResidual':		    
       i.set('Value','0')
    if i.get('Name') == 'JetMassResolutionUpDown':		    
       i.set('Value','0')
    if i.get('Name') == 'JetEnergyResolutionUpDown':		    
       i.set('Value','-1')
    if i.get('Name') == 'ScaleJERUp':		    
       i.set('Value','false')
    if i.get('Name') == 'ScaleJERDown':		    
       i.set('Value','false')           
               																					    
 with open('config/syst/doJERDown_%s_%s.xml'%(opts.channel,opts.signal), 'w') as f:													    
  f.write('<?xml version="1.0" encoding="UTF-8"?>\n<!DOCTYPE JobConfiguration PUBLIC "" "/shome/jngadiub/EXOVVAnalysisRunII/SFrame-04-00-01/user/config/JobConfig.dtd">\n')      
  tree.write(f, 'utf-8')																		    
 																					    
 cmd = 'sframe_main config/syst/doJERDown_%s_%s.xml' %(opts.channel,opts.signal)												    
 print cmd																				    
 os.system(cmd) 
 
 for mass in masses:																			    
  cmd = 'mv ../AnalysisOutput/JERsys/ExoDiBosonAnalysis.%s.M-%i.%s.root JERDown/ExoDiBosonAnalysis.%s.M-%i.%s.root' %(opts.signal,mass,opts.channel,opts.signal,mass,opts.channel) 			    
  print cmd																				    
  os.system(cmd) 
          
##############################################################
#####calculate yields#####
##############################################################

fout = ['JERsys_%s_HPV_%s.txt'%(opts.channel,opts.signal),'JERsys_%s_LPV_%s.txt'%(opts.channel,opts.signal),
        'JERsys_%s_HPW_%s.txt'%(opts.channel,opts.signal),'JERsys_%s_LPW_%s.txt'%(opts.channel,opts.signal),          
        'JERsys_%s_HPZ_%s.txt'%(opts.channel,opts.signal),'JERsys_%s_LPZ_%s.txt'%(opts.channel,opts.signal)]          

cuts = []
debugs = []

debugs.append("VV HP category")
cut =  "Mjpruned > 65 && Mjpruned < 105 && tau21 < 0.6"
cuts.append(cut)

debugs.append("VV LP category")
cut =  "Mjpruned > 65 && Mjpruned < 105 && tau21 > 0.6 && tau21 < 0.75"
cuts.append(cut)

debugs.append("WW HP category")
cut =  "Mjpruned > 65 && Mjpruned < 85 && tau21 < 0.6"
cuts.append(cut)

debugs.append("WW LP category")
cut =  "Mjpruned > 65 && Mjpruned < 85 && tau21 > 0.6 && tau21 < 0.75"
cuts.append(cut)

debugs.append("WZ HP category")
cut =  "Mjpruned > 85 && Mjpruned < 105 && tau21 < 0.6"
cuts.append(cut)

debugs.append("WZ LP category")
cut =  "Mjpruned > 85 && Mjpruned < 105 && tau21 > 0.6 && tau21 < 0.75"
cuts.append(cut)

for f in range(len(fout)):

 outfile = open(fout[f],'w')
 outfile.write('mass JERUp JERDown\n')
 outfile.write('\n')

 print ""
 print debugs[f]
 print cuts[f]
 print "" 
 for mass in masses:

   print "######## Mass = %i #########" %mass
     
   fname = 'centralValueJER/ExoDiBosonAnalysis.%s.M-%i.%s.root' %(opts.signal,mass,opts.channel)
   tfile = ROOT.TFile.Open(fname,'READ')
   tree = tfile.Get("tree")
   cv = tree.GetEntries(cuts[f])
   print "Central Value = %.3f" %(cv)
   tfile.Close()
   tfile.Delete() 

   fname = 'JERUp/ExoDiBosonAnalysis.%s.M-%i.%s.root' %(opts.signal,mass,opts.channel)
   tfile = ROOT.TFile.Open(fname,'READ')
   tree = tfile.Get("tree")
   btagup = tree.GetEntries(cuts[f])  
   print "JER sys up = %.3f" %(btagup)
   tfile.Close()
   tfile.Delete()

   fname = 'JERDown/ExoDiBosonAnalysis.%s.M-%i.%s.root' %(opts.signal,mass,opts.channel)
   tfile = ROOT.TFile.Open(fname,'READ')
   tree = tfile.Get("tree")
   btagdown = tree.GetEntries(cuts[f])
   print "JER sys down = %.3f" %(btagdown)
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

