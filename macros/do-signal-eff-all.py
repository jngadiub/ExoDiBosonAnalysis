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
parser.add_option('-c', '--channel',action="store",type="string",dest="channel",default="el")
parser.add_option('--batch', '-b',action="store_true",dest="batch",default=False)
parser.add_option('-s', '--sample',action="store",type="string",dest="sample",default="Wprime")
(opts, args) = parser.parse_args(argv)

tdrstyle.setTDRStyle()
if opts.batch: gROOT.SetBatch(kTRUE)

dir = '../../AnalysisOutput/eff/'
masses = array('i',[800,2000,4000])
lcolors = [ kWhite, kWhite, kAzure-6]
fstyle = [ 1001, 3002, 0]
fcolors = [ 38, kAzure+5, 0]
binlabels = ['trigger','lepton','MET','W_{lept}','one AK8 jet','b-tag veto','Angular cuts',
             'M_{WV} > 700 GeV','m_{j}^{pruned}','tau_{21} < 0.6']	    
legname = {'Wprime':"M_{W'}",'Zprime':"M_{Z'}",'BulkGraviton':"M_{G}"}
 
#************************#
eff_ = []

for m in masses:
 tmp = ROOT.TH1F("eff_M%i"%m,"eff_M%i"%m,10,0,10)
 eff_.append(tmp)
 
i = 0
for m in masses:
     
   fname = dir+'ExoDiBosonAnalysis.%s.M-%i.%s.root' %(opts.sample,m,opts.channel)   	 
   indata = ROOT.TFile.Open(fname,"READ")
   intree = indata.Get("tree")
   nevents = indata.Get("nEvents").GetBinContent(1)

   eff_[i].SetBinContent(1,indata.Get("nPassedTrigger").GetBinContent(1)/nevents)
   eff_[i].SetBinContent(2,indata.Get("nPassedVetoExtraLeptons").GetBinContent(1)/nevents)
   eff_[i].SetBinContent(3,indata.Get("nPassedFoundMET").GetBinContent(1)/nevents)
   eff_[i].SetBinContent(4,indata.Get("nPassedFoundW").GetBinContent(1)/nevents)
   eff_[i].SetBinContent(5,indata.Get("nPassedJetPtTight").GetBinContent(1)/nevents)
   eff_[i].SetBinContent(6,indata.Get("nPassedAJetCut").GetBinContent(1)/nevents)
   eff_[i].SetBinContent(7,indata.Get("nPassedJetWDPhi").GetBinContent(1)/nevents)
   eff_[i].SetBinContent(8,intree.GetEntries("MWW>700")/nevents)
   eff_[i].SetBinContent(9,intree.GetEntries("MWW>700 && Mjpruned>65 && Mjpruned<105")/nevents)
   eff_[i].SetBinContent(10,intree.GetEntries("MWW>700 && Mjpruned>65 && Mjpruned<105 && tau21<0.6")/nevents)
   i+=1
   #print m,ROOT.Double(intree.GetEntries("MWW>700 && Mjpruned>65 && Mjpruned<105 && tau21<0.6"))/intree.GetEntries("MWW>700")

l = ROOT.TLegend(0.6633166,0.6625874,0.8731156,0.8531469,"","NDC")
l.SetLineWidth(2)
l.SetBorderSize(0)
l.SetFillColor(0)
l.SetTextFont(42)
l.SetTextSize(0.04)
l.SetTextAlign(12)

i = 0
for h in eff_:
 for b in range(1,len(binlabels)+1):
  h.GetXaxis().SetBinLabel(b,binlabels[b-1])
 h.LabelsOption("u","x") 
 h.SetLineWidth(2)
 h.SetLineColor(lcolors[i])
 h.SetFillColor(fcolors[i])
 h.SetFillStyle(fstyle[i])
 i+=1

l.AddEntry(eff_[0],"%s = 0.8 TeV"%legname[opts.sample],"F")
l.AddEntry(eff_[1],"%s = 2 TeV"%legname[opts.sample],"F")
l.AddEntry(eff_[2],"%s = 4 TeV"%legname[opts.sample],"L")
canv = get_canvas("eff_%s_%s"%(opts.sample,opts.channel),1,opts.channel)
canv.cd()

eff_[0].Draw()
eff_[0].SetMinimum(0.2)
eff_[0].SetMaximum(1.2)
eff_[0].GetYaxis().SetTitle("Signal efficiency")
eff_[0].GetYaxis().SetTitleOffset(1)
eff_[0].GetXaxis().SetLabelOffset(0.017)
eff_[0].GetYaxis().SetNdivisions(505)
for h in range(1,len(eff_)):
 eff_[h].Draw("same")
l.Draw() 

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
canv.SaveAs("eff/"+canv.GetName()+".root")
canv.SaveAs("eff/"+canv.GetName()+".pdf")

#time.sleep(1000)
'''
####### BulkG #######
print "#######################################3"
print "BulkG"
eff_g = []

for m in masses:
 tmp = ROOT.TH1F("eff_g_M%i"%m,"eff_g_M%i"%m,10,0,10)
 eff_g.append(tmp)
 
i = 0
for m in masses:
      
   if m == 1000: continue
        
   fname = dir+'ExoDiBosonAnalysis.BulkGraviton.M-%i.%s.root' %(m,opts.channel)   	 
   indata = ROOT.TFile.Open(fname,"READ")
   intree = indata.Get("tree")
   nevents = indata.Get("nEvents").GetBinContent(1)
   
   eff_g[i].SetBinContent(1,indata.Get("nPassedTrigger").GetBinContent(1)/nevents)
   eff_g[i].SetBinContent(2,indata.Get("nPassedVetoExtraLeptons").GetBinContent(1)/nevents)
   eff_g[i].SetBinContent(3,indata.Get("nPassedFoundMET").GetBinContent(1)/nevents)
   eff_g[i].SetBinContent(4,indata.Get("nPassedFoundW").GetBinContent(1)/nevents)
   eff_g[i].SetBinContent(5,indata.Get("nPassedJetPtTight").GetBinContent(1)/nevents)
   eff_g[i].SetBinContent(6,indata.Get("nPassedAJetCut").GetBinContent(1)/nevents)
   eff_g[i].SetBinContent(7,indata.Get("nPassedJetWDPhi").GetBinContent(1)/nevents)
   eff_g[i].SetBinContent(8,intree.GetEntries("MWW>700")/nevents)
   eff_g[i].SetBinContent(9,intree.GetEntries("MWW>700 && Mjpruned>65 && Mjpruned<105")/nevents)
   eff_g[i].SetBinContent(10,intree.GetEntries("MWW>700 && Mjpruned>65 && Mjpruned<105 && tau21<0.6")/nevents)
   i+=1
   print m,ROOT.Double(intree.GetEntries("MWW>700 && Mjpruned>65 && Mjpruned<105 && tau21<0.6"))/intree.GetEntries("MWW>700")

l = ROOT.TLegend(0.6633166,0.6625874,0.8731156,0.8531469,"","NDC")
l.SetLineWidth(2)
l.SetBorderSize(0)
l.SetFillColor(0)
l.SetTextFont(42)
l.SetTextSize(0.04)
l.SetTextAlign(12)

i = 0
for h in eff_g:
 for b in range(1,len(binlabels)+1):
  h.GetXaxis().SetBinLabel(b,binlabels[b-1])
 h.LabelsOption("u","x") 
 h.SetLineWidth(2)
 h.SetLineColor(lcolors[i])
 h.SetFillColor(fcolors[i])
 h.SetFillStyle(fstyle[i])
 i+=1

l.AddEntry(eff_g[0],"M_{G} = 0.8 TeV","F")
l.AddEntry(eff_g[1],"M_{G} = 2 TeV","F")
l.AddEntry(eff_g[2],"M_{G} = 4 TeV","L")
canv = get_canvas("eff_g",1)
canv.cd()

eff_g[0].Draw()
eff_g[0].SetMinimum(0.2)
eff_g[0].SetMaximum(1.2)
eff_g[0].GetYaxis().SetTitle("Signal efficiency")
eff_g[0].GetYaxis().SetTitleOffset(1)
eff_g[0].GetXaxis().SetLabelOffset(0.017)
eff_g[0].GetYaxis().SetNdivisions(505)
for h in range(1,len(eff_g)):
 eff_g[h].Draw("same")
l.Draw() 

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
canv.SaveAs("eff/"+canv.GetName()+"all_g_%s.root"%opts.channel)
canv.SaveAs("eff/"+canv.GetName()+"all_g_%s.pdf"%opts.channel)

#time.sleep(1000)
'''
