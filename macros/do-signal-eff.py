#python do-btag-syst.py -T W -C HP0 -c mu -S -s Wprime
#python do-btag-syst.py -T W -C HP0 -c mu -S -s BulkGraviton
import xml.etree.ElementTree as ET
import os,commands
import sys
from optparse import OptionParser
import ConfigParser
import ROOT
from ROOT import *
import CMS_lumi, tdrstyle
from array import array
import time

def get_canvas(cname,lumi,ch):

   lep = "e"
   if ch == 'mu': lep = '#mu'
   CMS_lumi.lumi_13TeV = "WV #rightarrow %s#nuqq, #sqrt{s} = "%lep
   CMS_lumi.writeExtraText = 1
   CMS_lumi.extraText = "Simulation"

   iPos = 11
   if( iPos==0 ): CMS_lumi.relPosX = 0.15

   H_ref = 600; 
   W_ref = 800; 
   W = W_ref
   H  = H_ref

   T = 0.08*H_ref
   B = 0.12*H_ref 
   L = 0.12*W_ref
   R = 0.06*W_ref

   canvas = ROOT.TCanvas(cname,cname,W,H)
   canvas.SetFillColor(0)
   canvas.SetBorderMode(0)
   canvas.SetFrameFillStyle(0)
   canvas.SetFrameBorderMode(0)
   canvas.SetLeftMargin( L/W )
   canvas.SetRightMargin( R/W )
   canvas.SetTopMargin( T/H )
   canvas.SetBottomMargin( B/H+0.03 )
   canvas.SetTickx()
   canvas.SetTicky()
   
   return canvas

argv = sys.argv
parser = OptionParser()
parser.add_option('--channel', '-c',action="store",type="string",dest="channel",default="el")
parser.add_option('--batch', '-b',action="store_true",dest="batch",default=False)
parser.add_option('--printinfo', '-p',action="store_true",dest="printinfo",default=False)
(opts, args) = parser.parse_args(argv)

tdrstyle.setTDRStyle()
if opts.batch: gROOT.SetBatch(kTRUE)

dir = '../../AnalysisOutput/eff/'

masses = array('d',[800,1200,1400,1600,1800,2000,2500,3000,3500,4000,4500])

####### Wprime #######
eff_HPW_Wp = array('d',[])
eff_HPZ_Wp = array('d',[])
eff_LPW_Wp = array('d',[])
eff_LPZ_Wp = array('d',[])
eff_HPV_Wp = array('d',[])
eff_LPV_Wp = array('d',[])
x = array('d',[])

for m in masses:
        
   x.append(m/1000.)	 
   fname = dir+'ExoDiBosonAnalysis.Wprime.M-%i.%s.root' %(m,opts.channel)   	 
   indata = ROOT.TFile.Open(fname,"READ")
   intree = indata.Get("tree")
   nevents = indata.Get("nEvents").GetBinContent(1)

   #print m,intree.GetEntries("issignal && MWW>700 && Mjpruned>65 && Mjpruned<85 && tau21<0.6")/indata.Get("nPassedFoundW").GetBinContent(1)
   #print m,intree.GetEntries("issignal && MWW>700 && Mjpruned>85 && Mjpruned<105 && tau21<0.6")/indata.Get("nPassedFoundW").GetBinContent(1)
   #print m,intree.GetEntries("issignal && MWW>700 && Mjpruned>65 && Mjpruned<85 && tau21>0.6 && tau21<0.75")/nevents
   #print m,indata.Get("nPassedFoundW").GetBinContent(1)/nevents
               
   eff_HPW_Wp.append(intree.GetEntries("issignal && MWW>700 && Mjpruned>65 && Mjpruned<85 && tau21<0.6")/nevents) 
   eff_LPW_Wp.append(intree.GetEntries("issignal && MWW>700 && Mjpruned>65 && Mjpruned<85 && tau21>0.6 && tau21<0.75")/nevents)   

   eff_HPZ_Wp.append(intree.GetEntries("issignal && MWW>700 && Mjpruned>85 && Mjpruned<105 && tau21<0.6")/nevents) 
   eff_LPZ_Wp.append(intree.GetEntries("issignal && MWW>700 && Mjpruned>85 && Mjpruned<105 && tau21>0.6 && tau21<0.75")/nevents) 

   eff_HPV_Wp.append(intree.GetEntries("issignal && MWW>700 && Mjpruned>65 && Mjpruned<105 && tau21<0.6")/nevents) 
   eff_LPV_Wp.append(intree.GetEntries("issignal && MWW>700 && Mjpruned>65 && Mjpruned<105 && tau21>0.6 && tau21<0.75")/nevents)
   
grHPW_Wp = TGraph(len(x),x,eff_HPW_Wp)
grLPZ_Wp = TGraph(len(x),x,eff_LPZ_Wp)
grHPZ_Wp = TGraph(len(x),x,eff_HPZ_Wp)
grLPW_Wp = TGraph(len(x),x,eff_LPW_Wp)
grHPV_Wp = TGraph(len(x),x,eff_HPV_Wp)
grLPV_Wp = TGraph(len(x),x,eff_LPV_Wp)

####### Zprime #######
eff_HPW_Zp = array('d',[])
eff_HPZ_Zp = array('d',[])
eff_LPW_Zp = array('d',[])
eff_LPZ_Zp = array('d',[])
eff_HPV_Zp = array('d',[])
eff_LPV_Zp = array('d',[])
x = array('d',[])

masses = array('d',[800,1200,1400,1800,2000,2500,3000,3500,4000,4500])
for m in masses:
        
   x.append(m/1000.)	 
   fname = dir+'ExoDiBosonAnalysis.Zprime.M-%i.%s.root' %(m,opts.channel)   	 
   indata = ROOT.TFile.Open(fname,"READ")
   intree = indata.Get("tree")
   nevents = indata.Get("nEvents").GetBinContent(1)

   #print m,intree.GetEntries("issignal && MWW>700 && Mjpruned>65 && Mjpruned<85 && tau21<0.6")/indata.Get("nPassedFoundW").GetBinContent(1)
   #print m,intree.GetEntries("issignal && MWW>700 && Mjpruned>85 && Mjpruned<105 && tau21<0.6")/indata.Get("nPassedFoundW").GetBinContent(1)
   #print m,intree.GetEntries("issignal && MWW>700 && Mjpruned>65 && Mjpruned<85 && tau21>0.6 && tau21<0.75")/nevents
   #print m,indata.Get("nPassedFoundW").GetBinContent(1)/nevents
               
   eff_HPW_Zp.append(intree.GetEntries("issignal && MWW>700 && Mjpruned>65 && Mjpruned<85 && tau21<0.6")/nevents) 
   eff_LPW_Zp.append(intree.GetEntries("issignal && MWW>700 && Mjpruned>65 && Mjpruned<85 && tau21>0.6 && tau21<0.75")/nevents)   

   eff_HPZ_Zp.append(intree.GetEntries("issignal && MWW>700 && Mjpruned>85 && Mjpruned<105 && tau21<0.6")/nevents) 
   eff_LPZ_Zp.append(intree.GetEntries("issignal && MWW>700 && Mjpruned>85 && Mjpruned<105 && tau21>0.6 && tau21<0.75")/nevents) 

   eff_HPV_Zp.append(intree.GetEntries("issignal && MWW>700 && Mjpruned>65 && Mjpruned<105 && tau21<0.6")/nevents) 
   eff_LPV_Zp.append(intree.GetEntries("issignal && MWW>700 && Mjpruned>65 && Mjpruned<105 && tau21>0.6 && tau21<0.75")/nevents)
   
grHPW_Zp = TGraph(len(x),x,eff_HPW_Zp)
grLPZ_Zp = TGraph(len(x),x,eff_LPZ_Zp)
grHPZ_Zp = TGraph(len(x),x,eff_HPZ_Zp)
grLPW_Zp = TGraph(len(x),x,eff_LPW_Zp)
grHPV_Zp = TGraph(len(x),x,eff_HPV_Zp)
grLPV_Zp = TGraph(len(x),x,eff_LPV_Zp)

####### BulkG #######
eff_HPW_G = array('d',[])
eff_HPZ_G = array('d',[])
eff_LPW_G = array('d',[])
eff_LPZ_G = array('d',[])
eff_HPV_G = array('d',[])
eff_LPV_G = array('d',[])

x = array('d',[])
for m in masses:
      
   if m == 1000: continue
   x.append(m/1000.)
        
   fname = dir+'ExoDiBosonAnalysis.BulkGraviton.M-%i.%s.root' %(m,opts.channel)   	 
   indata = ROOT.TFile.Open(fname,"READ")
   intree = indata.Get("tree")
   nevents = indata.Get("nEvents").GetBinContent(1)
   
   #print m,intree.GetEntries("issignal && MWW>700 && Mjpruned>65 && Mjpruned<85 && tau21<0.6")/indata.Get("nPassedFoundW").GetBinContent(1)
   #print m,intree.GetEntries("issignal && MWW>700 && Mjpruned>85 && Mjpruned<105 && tau21<0.6")/indata.Get("nPassedFoundW").GetBinContent(1)
   #print m,intree.GetEntries("issignal && MWW>700 && Mjpruned>65 && Mjpruned<105 && tau21<0.6")/nevents
   #print m,indata.Get("nPassedFoundW").GetBinContent(1)/nevents
   
   eff_HPW_G.append(intree.GetEntries("issignal && MWW>700 && Mjpruned>65 && Mjpruned<85 && tau21<0.6")/nevents) 
   eff_LPW_G.append(intree.GetEntries("issignal && MWW>700 && Mjpruned>65 && Mjpruned<85 && tau21>0.6 && tau21<0.75")/nevents)   

   eff_HPZ_G.append(intree.GetEntries("issignal && MWW>700 && Mjpruned>85 && Mjpruned<105 && tau21<0.6")/nevents) 
   eff_LPZ_G.append(intree.GetEntries("issignal && MWW>700 && Mjpruned>85 && Mjpruned<105 && tau21>0.6 && tau21<0.75")/nevents) 

   eff_HPV_G.append(intree.GetEntries("issignal && MWW>700 && Mjpruned>65 && Mjpruned<105 && tau21<0.6")/nevents) 
   eff_LPV_G.append(intree.GetEntries("issignal && MWW>700 && Mjpruned>65 && Mjpruned<105 && tau21>0.6 && tau21<0.75")/nevents)
      
grHPW_G = TGraph(len(x),x,eff_HPW_G)
grLPW_G = TGraph(len(x),x,eff_LPW_G)
grHPZ_G = TGraph(len(x),x,eff_HPZ_G)
grLPZ_G = TGraph(len(x),x,eff_LPZ_G)
grHPV_G = TGraph(len(x),x,eff_HPV_G)
grLPV_G = TGraph(len(x),x,eff_LPV_G)

#### HPV ###
canv = get_canvas("eff_HPV",1,opts.channel)
canv.cd()

l = ROOT.TLegend(0.57,0.75,0.78,0.88,"","NDC")
l.SetLineWidth(2)
l.SetBorderSize(0)
l.SetFillColor(0)
l.SetTextFont(42)
l.SetTextSize(0.031)
l.SetTextAlign(12)

pt = ROOT.TPaveText(0.61,0.66,0.96,0.77,"NDC")
pt.SetTextFont(42)
pt.SetTextSize(0.031)
pt.SetTextAlign(12)
pt.SetFillColor(0)
pt.SetBorderSize(0)
pt.SetFillStyle(0)
text = pt.AddText("High Purity: #tau_{21} < 0.6")
text.SetTextFont(62)
#text = pt.AddText("#tau_{21} < 0.6")
#text.SetTextFont(42)
#text = pt.AddText("65 < m_{jet}^{pruned} < 85 GeV")
#text.SetTextFont(42)

grW = TH1F("grW","grW",1,0.,1.)
grW.SetLineColor(kBlack)
grW.SetLineWidth(2)
grZ = TH1F("grZ","grZ",1,0.,1.)
grZ.SetLineColor(kBlack)
grZ.SetLineWidth(2)
grZ.SetLineStyle(7)
grV = TH1F("grV","grV",1,0.,1.)
grV.SetLineColor(kBlack)
grV.SetLineWidth(2)
grV.SetLineStyle(3)

l2 = ROOT.TLegend(0.16,0.62,0.37,0.75,"","NDC")
l2.SetLineWidth(2)
l2.SetBorderSize(0)
l2.SetFillColor(0)
l2.SetTextFont(42)
l2.SetTextSize(0.031)
l2.SetTextAlign(12)

l2.AddEntry(grW,"WW-enriched cat.","L")
l2.AddEntry(grZ,"WZ-enriched cat.","L")
l2.AddEntry(grV,"WW+WZ cat. combined","L")

mg = ROOT.TMultiGraph("mg_HPV","mg_HPV")

grHPW_Zp.SetLineColor(kMagenta)
grHPW_Zp.SetLineWidth(2)
l.AddEntry(grHPW_Zp,"Z' #rightarrow WW (PYTHIA8)","L")
mg.Add(grHPW_Zp)

grHPW_Wp.SetLineColor(kTeal+2)
grHPW_Wp.SetLineWidth(2)
l.AddEntry(grHPW_Wp,"W' #rightarrow WZ (PYTHIA8)","L")
mg.Add(grHPW_Wp)

grHPW_G.SetLineColor(kAzure+5)
grHPW_G.SetLineWidth(2)
l.AddEntry(grHPW_G,"G_{bulk} #rightarrow WW (MADGRAPH)","L")
mg.Add(grHPW_G)

grHPZ_Wp.SetLineColor(kTeal+2)
grHPZ_Wp.SetLineWidth(2)
grHPZ_Wp.SetLineStyle(7)
#l.AddEntry(gr3_Wp,"W' #rightarrow WZ (PYTHIA8)","L")
mg.Add(grHPZ_Wp)

grHPZ_Zp.SetLineColor(kMagenta)
grHPZ_Zp.SetLineWidth(2)
grHPZ_Zp.SetLineStyle(7)
#l.AddEntry(gr3_Wp,"W' #rightarrow WZ (PYTHIA8)","L")
mg.Add(grHPZ_Zp)

grHPZ_G.SetLineColor(kAzure+5)
grHPZ_G.SetLineWidth(2)
grHPZ_G.SetLineStyle(7)
mg.Add(grHPZ_G)
#l.AddEntry(gr3_G,"G_{bulk} #rightarrow WW (MADGRAPH)","L")

grHPV_Wp.SetLineColor(kTeal+2)
grHPV_Wp.SetLineWidth(2)
grHPV_Wp.SetLineStyle(3)
#l.AddEntry(gr3_Wp,"W' #rightarrow WZ (PYTHIA8)","L")
mg.Add(grHPV_Wp)

grHPV_Zp.SetLineColor(kMagenta)
grHPV_Zp.SetLineWidth(2)
grHPV_Zp.SetLineStyle(3)
#l.AddEntry(gr3_Wp,"W' #rightarrow WZ (PYTHIA8)","L")
mg.Add(grHPV_Zp)

grHPV_G.SetLineColor(kAzure+5)
grHPV_G.SetLineWidth(2)
grHPV_G.SetLineStyle(3)
mg.Add(grHPV_G)
#l.AddEntry(gr3_G,"G_{bulk} #rightarrow WW (MADGRAPH)","L")

mg.SetMinimum(0)
mg.SetMaximum(1.1)
mg.Draw("AL")
mg.GetYaxis().SetNdivisions(505)
mg.GetYaxis().SetTitle("Signal efficiency")
mg.GetYaxis().SetTitleOffset(1)
mg.GetXaxis().SetTitle("M_{X} [GeV]")
pt.Draw()
l.Draw()
l2.Draw()

canv.Update()
canv.cd()            
CMS_lumi.CMS_lumi(canv, 4, 11)	   
canv.cd()
canv.Update()
canv.RedrawAxis()
frame = canv.GetFrame()
frame.Draw()   
canv.cd()
canv.Update()
canv.SaveAs("eff/"+canv.GetName()+"_%s.root"%opts.channel)
canv.SaveAs("eff/"+canv.GetName()+"_%s.pdf"%opts.channel)

#### LPV ###
canv = get_canvas("eff_LPV",1,opts.channel)
canv.cd()

l = ROOT.TLegend(0.57,0.75,0.78,0.88,"","NDC")
l.SetLineWidth(2)
l.SetBorderSize(0)
l.SetFillColor(0)
l.SetTextFont(42)
l.SetTextSize(0.031)
l.SetTextAlign(12)

pt = ROOT.TPaveText(0.61,0.63,0.96,0.74,"NDC")
pt.SetTextFont(42)
pt.SetTextSize(0.031)
pt.SetTextAlign(12)
pt.SetFillColor(0)
pt.SetBorderSize(0)
pt.SetFillStyle(0)
text = pt.AddText("Low Purity: 0.6 < #tau_{21} < 0.75")
text.SetTextFont(62)
#text = pt.AddText("#tau_{21} < 0.6")
#text.SetTextFont(42)
#text = pt.AddText("65 < m_{jet}^{pruned} < 85 GeV")
#text.SetTextFont(42)

mg = ROOT.TMultiGraph("mg_LPV","mg_LPV")

grLPW_Wp.SetLineColor(kTeal+2)
grLPW_Wp.SetLineWidth(2)
l.AddEntry(grLPW_Wp,"W' #rightarrow WZ (PYTHIA8)","L")
mg.Add(grLPW_Wp)

grLPW_Zp.SetLineColor(kMagenta)
grLPW_Zp.SetLineWidth(2)
l.AddEntry(grLPW_Zp,"Z' #rightarrow WW (PYTHIA8)","L")
mg.Add(grLPW_Zp)

grLPW_G.SetLineColor(kAzure+5)
grLPW_G.SetLineWidth(2)
l.AddEntry(grLPW_G,"G_{bulk} #rightarrow WW (MADGRAPH)","L")
mg.Add(grLPW_G)

grLPZ_Wp.SetLineColor(kTeal+2)
grLPZ_Wp.SetLineWidth(2)
grLPZ_Wp.SetLineStyle(7)
#l.AddEntry(gr3_Wp,"W' #rightarrow WZ (PYTHIA8)","L")
mg.Add(grLPZ_Wp)

grLPZ_Zp.SetLineColor(kMagenta)
grLPZ_Zp.SetLineWidth(2)
grLPZ_Zp.SetLineStyle(7)
#l.AddEntry(gr3_Wp,"W' #rightarrow WZ (PYTHIA8)","L")
mg.Add(grLPZ_Zp)

grLPZ_G.SetLineColor(kAzure+5)
grLPZ_G.SetLineWidth(2)
grLPZ_G.SetLineStyle(7)
mg.Add(grLPZ_G)
#l.AddEntry(gr3_G,"G_{bulk} #rightarrow WW (MADGRAPH)","L")

grLPV_Wp.SetLineColor(kTeal+2)
grLPV_Wp.SetLineWidth(2)
grLPV_Wp.SetLineStyle(3)
#l.AddEntry(gr3_Wp,"W' #rightarrow WZ (PYTHIA8)","L")
mg.Add(grLPV_Wp)

grLPV_Zp.SetLineColor(kMagenta)
grLPV_Zp.SetLineWidth(2)
grLPV_Zp.SetLineStyle(3)
#l.AddEntry(gr3_Wp,"W' #rightarrow WZ (PYTHIA8)","L")
mg.Add(grLPV_Zp)

grLPV_G.SetLineColor(kAzure+5)
grLPV_G.SetLineWidth(2)
grLPV_G.SetLineStyle(3)
mg.Add(grLPV_G)
#l.AddEntry(gr3_G,"G_{bulk} #rightarrow WW (MADGRAPH)","L")

mg.SetMinimum(0.)
mg.SetMaximum(0.12)
mg.Draw("AL")
mg.GetYaxis().SetNdivisions(505)
mg.GetYaxis().SetTitle("Signal efficiency")
mg.GetYaxis().SetTitleOffset(1)
mg.GetXaxis().SetTitle("M_{X} [GeV]")
pt.Draw()
l.Draw()
l2.Draw()

canv.Update()
canv.cd()            
CMS_lumi.CMS_lumi(canv, 4, 11)	   
canv.cd()
canv.Update()
canv.RedrawAxis()
frame = canv.GetFrame()
frame.Draw()   
canv.cd()
canv.Update() 
canv.SaveAs("eff/"+canv.GetName()+"_%s.root"%opts.channel)
canv.SaveAs("eff/"+canv.GetName()+"_%s.pdf"%opts.channel)

#time.sleep(1000)

if opts.printinfo:

 print "**** Wprime ****"
 print "HPW"
 grHPW_Wp.Print()
 print "LPZ"
 grLPZ_Wp.Print()
 print "HPZ"
 grHPZ_Wp.Print()
 print "LPW"
 grLPW_Wp.Print()
 print "HPV"
 grHPV_Wp.Print()
 print "LPV"
 grLPV_Wp.Print()
 
 print ""
 print "**** Zprime ****"
 print "HPW"
 grHPW_Zp.Print()
 print "LPZ"
 grLPZ_Zp.Print()
 print "HPZ"
 grHPZ_Zp.Print()
 print "LPW"
 grLPW_Zp.Print()
 print "HPV"
 grHPV_Zp.Print()
 print "LPV"
 grLPV_Zp.Print() 
 
 print "**** BulkG ****"
 print "HPW"
 grHPW_G.Print()
 print "LPZ"
 grLPZ_G.Print()
 print "HPZ"
 grHPZ_G.Print()
 print "LPW"
 grLPW_G.Print()
 print "HPV"
 grHPV_G.Print()
 print "LPV"
 grLPV_G.Print() 
