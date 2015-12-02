#python do-btag-syst.py -T W -C HP0 -c mu -S -s Wprime
#python do-btag-syst.py -T W -C HP0 -c mu -S -s BulkGraviton
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
parser.add_option('-C', '--category',action="store",type="string",dest="category",default="HP0")
parser.add_option('-T', '--tagging',action="store",type="string",dest="tagging",default="W")
parser.add_option("-S", "--syst", dest="syst", default=False, action="store_true",help="do systematics")
parser.add_option('-s', '--signal',action="store",type="string",dest="signal",default="Wprime")
(opts, args) = parser.parse_args(argv)

status,ls_la = commands.getstatusoutput( 'ls -l centralValueBTag' ) 													      
if status:																				      
   os.system('mkdir centralValueBTag')   

status,ls_la = commands.getstatusoutput( 'ls -l BTagSFup' )													      
if status:																				      
   os.system('mkdir BTagSFup')

status,ls_la = commands.getstatusoutput( 'ls -l BTagSFdown' )													      
if status:																				      
   os.system('mkdir BTagSFdown')

mlo = 60
mhi = 80
if opts.tagging == 'Z':
  mlo = 80
  mhi = 95
      
#masses = [800,1000,1200,1400,1600,1800,2000,2500,3000,4000,4500]
masses = [2000]
if opts.syst:														 

 # get muon channel xml config file and parse																       
 xmlfile = 'config/%s_%s_BTagSys.xml' %(opts.signal,opts.channel)
														       
 tree = ET.parse(xmlfile)																		       
 root = tree.getroot()  																		       

 ############### do central value ####################																		                   
 status,ls_la = commands.getstatusoutput( 'ls -l centralValueBTag/%s'%(opts.category+opts.tagging) )													       
 if status:																				       
    os.system('mkdir centralValueBTag/%s'%(opts.category+opts.tagging)) 																	       

 r = root.find('Cycle').find('UserConfig')																    
 for i in r.findall('Item'):																		    
    if i.get('Name') == 'NsubjBTag':																	    
       i.set('Value',list(opts.category)[2]) 																	    
    if i.get('Name') == 'Tau21Cut':		    
       i.set('Value',list(opts.category)[0]+list(opts.category)[1])																	    
    if i.get('Name') == 'BtagSFSysUp':		    
       i.set('Value','false')
    if i.get('Name') == 'BtagSFSysDown':		    
       i.set('Value','false')
    if i.get('Name') == 'mLow':		    
       i.set('Value',str(mlo))
    if i.get('Name') == 'mHigh':		    
       i.set('Value',str(mhi))
                             																					    
 with open('config/syst/docentralValueBTag_%s_%s.xml'%(opts.channel,opts.category+opts.tagging), 'w') as f:													    
  f.write('<?xml version="1.0" encoding="UTF-8"?>\n<!DOCTYPE JobConfiguration PUBLIC "" "/shome/jngadiub/EXOVVAnalysisRunII/SFrame-04-00-01/user/config/JobConfig.dtd">\n')      
  tree.write(f, 'utf-8')																		    
 																					    
 cmd = 'make && sframe_main config/syst/docentralValueBTag_%s_%s.xml' %(opts.channel,opts.category+opts.tagging)												    
 print cmd																				    
 os.system(cmd) 
 
 for mass in masses:																			    
  cmd = 'mv ../AnalysisOutput/BTagSys/ExoDiBosonAnalysis.%s.M-%i.%s.root centralValueBTag/%s/ExoDiBosonAnalysis.%s.M-%i.%s.root' %(opts.signal,mass,opts.channel,opts.category+opts.tagging,opts.signal,mass,opts.channel) 			    
  print cmd																				    
  os.system(cmd) 																			    

 ############### do btag sf up ####################																		       
 status,ls_la = commands.getstatusoutput( 'ls -l BTagSFup/%s'%(opts.category+opts.tagging) )													       
 if status:																				       
    os.system('mkdir BTagSFup/%s'%(opts.category+opts.tagging)) 																	       

 r = root.find('Cycle').find('UserConfig')																    
 for i in r.findall('Item'):																		    
    if i.get('Name') == 'NsubjBTag':																	    
       i.set('Value',list(opts.category)[2]) 																	    
    if i.get('Name') == 'Tau21Cut':		    
       i.set('Value',list(opts.category)[0]+list(opts.category)[1])																	    
    if i.get('Name') == 'BtagSFSysUp':		    
       i.set('Value','true')
    if i.get('Name') == 'BtagSFSysDown':		    
       i.set('Value','false')
    if i.get('Name') == 'mLow':		    
       i.set('Value',str(mlo))
    if i.get('Name') == 'mHigh':		    
       i.set('Value',str(mhi))
               																					    
 with open('config/syst/doBTagSFup_%s_%s.xml'%(opts.channel,opts.category+opts.tagging), 'w') as f:													    
  f.write('<?xml version="1.0" encoding="UTF-8"?>\n<!DOCTYPE JobConfiguration PUBLIC "" "/shome/jngadiub/EXOVVAnalysisRunII/SFrame-04-00-01/user/config/JobConfig.dtd">\n')      
  tree.write(f, 'utf-8')																		    
 																					    
 cmd = 'make && sframe_main config/syst/doBTagSFup_%s_%s.xml' %(opts.channel,opts.category+opts.tagging)												    
 print cmd																				    
 os.system(cmd) 
 
 for mass in masses:																			    
  cmd = 'mv ../AnalysisOutput/BTagSys/ExoDiBosonAnalysis.%s.M-%i.%s.root BTagSFup/%s/ExoDiBosonAnalysis.%s.M-%i.%s.root' %(opts.signal,mass,opts.channel,opts.category+opts.tagging,opts.signal,mass,opts.channel) 			    
  print cmd																				    
  os.system(cmd) 

 ############### do btag sf down ####################																		       
 status,ls_la = commands.getstatusoutput( 'ls -l BTagSFdown/%s'%(opts.category+opts.tagging) )													       
 if status:																				       
    os.system('mkdir BTagSFdown/%s'%(opts.category+opts.tagging)) 																	       

 r = root.find('Cycle').find('UserConfig')																    
 for i in r.findall('Item'):																		    
    if i.get('Name') == 'NsubjBTag':																	    
       i.set('Value',list(opts.category)[2]) 																	    
    if i.get('Name') == 'Tau21Cut':		    
       i.set('Value',list(opts.category)[0]+list(opts.category)[1])																	    
    if i.get('Name') == 'BtagSFSysUp':		    
       i.set('Value','false')
    if i.get('Name') == 'BtagSFSysDown':		    
       i.set('Value','true')
    if i.get('Name') == 'mLow':		    
       i.set('Value',str(mlo))
    if i.get('Name') == 'mHigh':		    
       i.set('Value',str(mhi))
               																					    
 with open('config/syst/doBTagSFdown_%s_%s.xml'%(opts.channel,opts.category+opts.tagging), 'w') as f:													    
  f.write('<?xml version="1.0" encoding="UTF-8"?>\n<!DOCTYPE JobConfiguration PUBLIC "" "/shome/jngadiub/EXOVVAnalysisRunII/SFrame-04-00-01/user/config/JobConfig.dtd">\n')      
  tree.write(f, 'utf-8')																		    
 																					    
 cmd = 'make && sframe_main config/syst/doBTagSFdown_%s_%s.xml' %(opts.channel,opts.category+opts.tagging)												    
 print cmd																				    
 os.system(cmd) 
 
 for mass in masses:																			    
  cmd = 'mv ../AnalysisOutput/BTagSys/ExoDiBosonAnalysis.%s.M-%i.%s.root BTagSFdown/%s/ExoDiBosonAnalysis.%s.M-%i.%s.root' %(opts.signal,mass,opts.channel,opts.category+opts.tagging,opts.signal,mass,opts.channel) 			    
  print cmd																				    
  os.system(cmd) 
         
##############################################################
#####calculate yields#####
##############################################################

outfile = open('BTagSys_%s_%s.txt'%(opts.channel,opts.category+opts.tagging),'w')
outfile.write('mass BTagSFup BTagSFdown\n')
outfile.write('\n')
      
for mass in masses:

   print "######## Mass = %i #########" %mass
     
   fname = 'centralValueBTag/%s/ExoDiBosonAnalysis.%s.M-%i.%s.root' %(opts.category+opts.tagging,opts.signal,mass,opts.channel)
   tfile = ROOT.TFile.Open(fname,'READ')
   #cv = ROOT.TH1F(tfile.Get('nPassedExoCandidateMass')).GetBinContent(1)
   cv = ROOT.TH1F(tfile.Get('AK8jetPrunedMass')).Integral()
   print "Central Value = %.3f" %(cv)
   tfile.Close()
   tfile.Delete() 

   fname = 'BTagSFup/%s/ExoDiBosonAnalysis.%s.M-%i.%s.root' %(opts.category+opts.tagging,opts.signal,mass,opts.channel)
   tfile = ROOT.TFile.Open(fname,'READ')
   btagup = ROOT.TH1F(tfile.Get('AK8jetPrunedMass')).Integral()#ROOT.TH1F(tfile.Get('nPassedExoCandidateMass')).GetBinContent(1)   
   print "BTag sf sys up = %.3f" %(btagup)
   tfile.Close()
   tfile.Delete()

   fname = 'BTagSFdown/%s/ExoDiBosonAnalysis.%s.M-%i.%s.root' %(opts.category+opts.tagging,opts.signal,mass,opts.channel)
   tfile = ROOT.TFile.Open(fname,'READ')
   btagdown = ROOT.TH1F(tfile.Get('AK8jetPrunedMass')).Integral()#ROOT.TH1F(tfile.Get('nPassedExoCandidateMass')).GetBinContent(1)
   print "BTag sf sys down = %.3f" %(btagdown)
   tfile.Close()
   tfile.Delete()
   
   outfile.write('BulkG_WW_lvjj_M%i %.3f %.3f\n' %(mass,(btagup-cv)*100/cv,(btagdown-cv)*100/cv))            
   #outfile.write('%i %.3f %.3f\n' %(mass,(btagup-cv)*100/cv,(cv-btagdown)*100/cv))


outfile.close()


