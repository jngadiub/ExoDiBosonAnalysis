#python do-jes-dijet.py -S -s Wprime
import xml.etree.ElementTree as ET
import os,commands
import sys
from optparse import OptionParser
import ConfigParser
import ROOT
from ROOT import *

argv = sys.argv
parser = OptionParser()
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

masses = [1000,1200,1400,1600,1800,2000,2500,3000,3500,4000,4500]

if opts.syst:														 

 # get muon channel xml config file and parse																       
 xmlfile = 'config/Dijet_%s_JESsys.xml' %(opts.signal)														       

 tree = ET.parse(xmlfile)																		       
 root = tree.getroot()  																		       

 ############### do central value ####################																		                   
 status,ls_la = commands.getstatusoutput( 'ls -l centralValueJES/' )													       
 if status:																				       
    os.system('mkdir centralValueJES/') 																	       

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
       i.set('Value','0')
    if i.get('Name') == 'ScaleJESUp':		    
       i.set('Value','false')
    if i.get('Name') == 'ScaleJESDown':		    
       i.set('Value','false')                            
                             																					    
 with open('config/syst/Dijet_docentralValueJES_%s.xml'%(opts.signal), 'w') as f:													    
  f.write('<?xml version="1.0" encoding="UTF-8"?>\n<!DOCTYPE JobConfiguration PUBLIC "" "/shome/jngadiub/EXOVVAnalysisRunII/SFrame-04-00-01/user/config/JobConfig.dtd">\n')      
  tree.write(f, 'utf-8')																		    
 																					    
 cmd = 'sframe_main config/syst/Dijet_docentralValueJES_%s.xml' %(opts.signal)												    
 print cmd																				    
 os.system(cmd) 
 
 for mass in masses:																			    
  cmd = 'mv ../AnalysisOutput/JESsys/ExoDiBosonAnalysis.%s.M-%i.dijet.root centralValueJES/ExoDiBosonAnalysis.%s.M-%i.dijet.root' %(opts.signal,mass,opts.signal,mass) 			    
  print cmd																				    
  os.system(cmd) 																			    

 ############### do btag sf up ####################																		       
 status,ls_la = commands.getstatusoutput( 'ls -l JESUp/' )													       
 if status:																				       
    os.system('mkdir JESUp/') 																	       

 r = root.find('Cycle').find('UserConfig')																    
 for i in r.findall('Item'):																		    																	    																    
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
               																					    
 with open('config/syst/Dijet_doJESUp_%s.xml'%(opts.signal), 'w') as f:													    
  f.write('<?xml version="1.0" encoding="UTF-8"?>\n<!DOCTYPE JobConfiguration PUBLIC "" "/shome/jngadiub/EXOVVAnalysisRunII/SFrame-04-00-01/user/config/JobConfig.dtd">\n')      
  tree.write(f, 'utf-8')																		    
 																					    
 cmd = 'sframe_main config/syst/Dijet_doJESUp_%s.xml' %(opts.signal)												    
 print cmd																				    
 os.system(cmd) 
 
 for mass in masses:																			    
  cmd = 'mv ../AnalysisOutput/JESsys/ExoDiBosonAnalysis.%s.M-%i.dijet.root JESUp/ExoDiBosonAnalysis.%s.M-%i.dijet.root' %(opts.signal,mass,opts.signal,mass) 			    
  print cmd																				    
  os.system(cmd) 

 ############### do btag sf down ####################																		       
 status,ls_la = commands.getstatusoutput( 'ls -l JESDown/' )													       
 if status:																				       
    os.system('mkdir JESDown/') 																	       

 r = root.find('Cycle').find('UserConfig')																    
 for i in r.findall('Item'):																		    																	    																	    
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
               																					    
 with open('config/syst/Dijet_doJESDown_%s.xml'%(opts.signal), 'w') as f:													    
  f.write('<?xml version="1.0" encoding="UTF-8"?>\n<!DOCTYPE JobConfiguration PUBLIC "" "/shome/jngadiub/EXOVVAnalysisRunII/SFrame-04-00-01/user/config/JobConfig.dtd">\n')      
  tree.write(f, 'utf-8')																		    
 																					    
 cmd = 'sframe_main config/syst/Dijet_doJESDown_%s.xml' %(opts.signal)												    
 print cmd																				    
 os.system(cmd) 
 
 for mass in masses:																			    
  cmd = 'mv ../AnalysisOutput/JESsys/ExoDiBosonAnalysis.%s.M-%i.dijet.root JESDown/ExoDiBosonAnalysis.%s.M-%i.dijet.root' %(opts.signal,mass,opts.signal,mass) 			    
  print cmd																				    
  os.system(cmd) 

fout = ['JESsys_HP_VV_%s.txt'%(opts.signal),'JESsys_LP_VV_%s.txt'%(opts.signal),
        'JESsys_HP_WW_%s.txt'%(opts.signal),'JESsys_LP_WW_%s.txt'%(opts.signal),          
        'JESsys_HP_WZ_%s.txt'%(opts.signal),'JESsys_LP_WZ_%s.txt'%(opts.signal),          
        'JESsys_HP_ZZ_%s.txt'%(opts.signal),'JESsys_LP_ZZ_%s.txt'%(opts.signal)]          

cuts = []
debugs = []

debugs.append("VV HP category")
cut =  "Mjpruned_1 > 65 && Mjpruned_1 < 105 && tau21_1 < 0.45"
cut += " && Mjpruned_2 > 65 && Mjpruned_2 < 105 && tau21_2 < 0.45"  
cuts.append(cut)

debugs.append("VV LP category")
cut =  "Mjpruned_1 > 65 && Mjpruned_1 < 105 && Mjpruned_2 > 65 && Mjpruned_2 < 105"
cut += " && ( (tau21_1 < 0.45 && tau21_2 > 0.45 && tau21_2 < 0.75) || (tau21_2 < 0.45 && tau21_1 > 0.45 && tau21_1 < 0.75) )" 
cuts.append(cut)

debugs.append("WW HP category")
cut =  "Mjpruned_1 > 65 && Mjpruned_1 < 85 && tau21_1 < 0.45"
cut += " && Mjpruned_2 > 65 && Mjpruned_2 < 85 && tau21_2 < 0.45"  
cuts.append(cut)

debugs.append("WW LP category")
cut =  "Mjpruned_1 > 65 && Mjpruned_1 < 85 && Mjpruned_2 > 65 && Mjpruned_2 < 85"
cut += " && ( (tau21_1 < 0.45 && tau21_2 > 0.45 && tau21_2 < 0.75) || (tau21_2 < 0.45 && tau21_1 > 0.45 && tau21_1 < 0.75) )" 
cuts.append(cut)

debugs.append("WZ HP category")
cut =  " ((Mjpruned_1 > 65 && Mjpruned_1 < 85 && Mjpruned_2 > 85 && Mjpruned_1 < 105)"
cut += " || (Mjpruned_2 > 65 && Mjpruned_2 < 85 && Mjpruned_1 > 85 && Mjpruned_1 < 105)) "
cut += " && tau21_1 < 0.45 && tau21_2 < 0.45"  
cuts.append(cut)

debugs.append("WZ LP category")
cut =  " ((Mjpruned_1 > 65 && Mjpruned_1 < 85 && Mjpruned_2 > 85 && Mjpruned_1 < 105)"
cut += " || (Mjpruned_2 > 65 && Mjpruned_2 < 85 && Mjpruned_1 > 85 && Mjpruned_1 < 105)) "
cut += " && ( (tau21_1 < 0.45 && tau21_2 > 0.45 && tau21_2 < 0.75) || (tau21_2 < 0.45 && tau21_1 > 0.45 && tau21_1 < 0.75) ) "  
cuts.append(cut)

debugs.append("ZZ HP category")
cut =  "Mjpruned_1 > 85 && Mjpruned_1 < 105 && tau21_1 < 0.45"
cut += " && Mjpruned_2 > 85 && Mjpruned_2 < 105 && tau21_2 < 0.45"  
cuts.append(cut)

debugs.append("ZZ LP category")
cut =  "Mjpruned_1 > 85 && Mjpruned_1 < 105 && Mjpruned_2 > 85 && Mjpruned_2 < 105"
cut += " && ( (tau21_1 < 0.45 && tau21_2 > 0.45 && tau21_2 < 0.75) || (tau21_2 < 0.45 && tau21_1 > 0.45 && tau21_1 < 0.75) )" 
cuts.append(cut)

##############################################################
#####calculate yields for VV HP#####
##############################################################

for f in range(len(fout)):

 outfile = open(fout[f],'w')
 outfile.write('mass JESUp JESDown\n')
 outfile.write('\n')

 print ""
 print debugs[f]
 print cuts[f]
 print "" 
 for mass in masses:

   print "######## Mass = %i #########" %mass
     
   fname = 'centralValueJES/ExoDiBosonAnalysis.%s.M-%i.dijet.root' %(opts.signal,mass)
   tfile = ROOT.TFile.Open(fname,'READ')
   tree = tfile.Get("tree")
   cv = float(tree.GetEntries(cuts[f]))
   print "Central Value = %.3f" %(cv)
   tfile.Close()
   tfile.Delete() 

   fname = 'JESUp/ExoDiBosonAnalysis.%s.M-%i.dijet.root' %(opts.signal,mass)
   tfile = ROOT.TFile.Open(fname,'READ')
   tree = tfile.Get("tree")
   btagup = float(tree.GetEntries(cuts[f])) 
   print "JES sys up = %.3f" %(btagup)
   tfile.Close()
   tfile.Delete()

   fname = 'JESDown/ExoDiBosonAnalysis.%s.M-%i.dijet.root' %(opts.signal,mass)
   tfile = ROOT.TFile.Open(fname,'READ')
   tree = tfile.Get("tree")
   btagdown = float(tree.GetEntries(cuts[f]))
   print "JES sys down = %.3f" %(btagdown)
   tfile.Close()
   tfile.Delete()
    
   sup = btagup-cv
   sdown = btagdown-cv
   #if sup < 0 and sdown < 0: sdown = -sdown      
     
   if opts.signal == 'BulkGraviton_WW':  
    outfile.write('BulkG_WW_M%i %.3f %.3f\n' %(mass,sup*100/cv,sdown*100/cv))
   elif opts.signal == 'BulkGraviton_ZZ':  
    outfile.write('BulkG_ZZ_M%i %.3f %.3f\n' %(mass,sup*100/cv,sdown*100/cv))
   elif opts.signal == 'Wprime':
    outfile.write('Wprime_WZ_M%i %.3f %.3f\n' %(mass,sup*100/cv,sdown*100/cv))

 outfile.close()


