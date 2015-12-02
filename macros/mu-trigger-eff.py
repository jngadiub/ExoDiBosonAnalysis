from optparse import OptionParser
import ROOT
import sys
import ConfigParser
import time
import gc
import math
import CMS_lumi, tdrstyle
from array import array
import math

def get_canvas(cname,lumi):

   CMS_lumi.lumi_13TeV = "#sqrt{s} = "
   CMS_lumi.writeExtraText = 0
   CMS_lumi.extraText = "Preliminary"

   iPos = 0
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

tdrstyle.setTDRStyle()

suffix = "PT"
#suffix = "Eta"

if suffix == "PT": fsuf = 'pt'
elif suffix == "Eta": fsuf = 'eta'

fname1 = '../../AnalysisOutput/triggers25ns/SingleMuon.Run2015D.%s.root'%fsuf      
fname2 = '../../AnalysisOutput/triggers25ns/SingleMuon.Run2015C.%s.root'%fsuf
#fname3 = '../../AnalysisOutput/SingleElectron.pt.root'


hnumname = 'leptonTriggerEff%s' %suffix
hdenname = 'leptonTriggerEff%sden' %suffix

#rebin = 1
rebin = 5

#--------------------------------------------------------#

file = ROOT.TFile.Open(fname1)
hnum1 = ROOT.TH1F(file.Get(hnumname))
hden1 = ROOT.TH1F(file.Get(hdenname))
nu = hnum1.Integral(hnum1.GetXaxis().FindBin(50.),hnum1.GetNbinsX())
de = hden1.Integral(hden1.GetXaxis().FindBin(50.),hden1.GetNbinsX())
if suffix == "PT": print "Run 2015D eff = %f" %(nu/de)
hnum1.Rebin(rebin)
hden1.Rebin(rebin) 

file2 = ROOT.TFile.Open(fname2)
hnum2 = ROOT.TH1F(file2.Get(hnumname))
hden2 = ROOT.TH1F(file2.Get(hdenname))
nu = hnum2.Integral(hnum2.GetXaxis().FindBin(50.),hnum2.GetNbinsX())
de = hden2.Integral(hden2.GetXaxis().FindBin(50.),hden2.GetNbinsX())
if suffix == "PT": print "Run 2015C eff = %f" %(nu/de)
hnum2.Rebin(rebin)
hden2.Rebin(rebin)

#--------------------------------------------------------#
canv = get_canvas('c1',1.)
canv.SetGrid()
canv.cd()

pt = ROOT.TPaveText(0.1796482,0.701049,0.5188442,0.8409091,"NDC")
pt.SetTextFont(42)
pt.SetTextSize(0.035)
pt.SetTextAlign(12)
pt.SetFillColor(0)
pt.SetBorderSize(0)
pt.SetFillStyle(0)
text = pt.AddText("HLT_Mu45_eta2p1")
text.SetTextFont(62)
text = pt.AddText("HighPT ID + IsoTrk03Rel < 0.1")
text.SetTextFont(42)
if suffix == "PT": text = pt.AddText("0 < |#eta| < 2.1")
if suffix == "Eta": text = pt.AddText("p_{T} > 50 GeV")
text.SetTextFont(42)
   
mg = ROOT.TMultiGraph()

l = ROOT.TLegend(0.71,0.70,0.92,0.87,"","NDC")
l.SetLineWidth(2)
l.SetBorderSize(0)
l.SetFillColor(0)
l.SetTextFont(42)
l.SetTextSize(0.04)
l.SetTextAlign(12)

eff1 = ROOT.TGraphAsymmErrors()
eff1.Divide(hnum1,hden1)
eff1.SetMarkerStyle(20)
eff1.SetMarkerColor(ROOT.kBlue)
eff1.SetLineColor(ROOT.kBlack)
mg.Add(eff1)
l.AddEntry(eff1,'Run 2015 D','LP')

eff2 = ROOT.TGraphAsymmErrors()
eff2.Divide(hnum2,hden2)
eff2.SetMarkerStyle(4)
eff2.SetMarkerColor(ROOT.kRed)
eff2.SetLineColor(ROOT.kBlack)
mg.Add(eff2)
l.AddEntry(eff2,'Run 2015 C','LP')

mg.SetMinimum(0.)
mg.SetMaximum(1.5)
mg.Draw('AP')
mg.GetXaxis().SetTitleSize(0.045)
mg.GetYaxis().SetTitleSize(0.045)
mg.GetXaxis().SetLabelSize(0.04)
mg.GetYaxis().SetLabelSize(0.04)
if suffix == "PT":
   mg.GetXaxis().SetTitle("Muon p_{T} [GeV]")
   mg.GetXaxis().SetRangeUser(0,500)
elif suffix == "Eta":   
   mg.GetXaxis().SetTitle("Muon #eta")
   mg.GetXaxis().SetRangeUser(-2.4,2.4)
mg.GetYaxis().SetTitle("Efficiency")
mg.GetXaxis().SetTitleOffset(1.2)
mg.GetYaxis().SetTitleOffset(1.1)

mg.Draw("AP")
l.Draw()
pt.Draw()

canv.Update()
canv.cd()            
CMS_lumi.CMS_lumi(canv, 4, 0)	   
canv.cd()
canv.Update()
canv.RedrawAxis()
frame = canv.GetFrame()
frame.Draw()   
canv.cd()
canv.Update() 
   
time.sleep(1000)
