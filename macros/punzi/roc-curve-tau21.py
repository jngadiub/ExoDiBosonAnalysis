import ROOT
import sys
import time
import math
import CMS_lumi, tdrstyle

def get_canvas():

   tdrstyle.setTDRStyle()
   CMS_lumi.lumi_13TeV = ""
   CMS_lumi.writeExtraText = 0
   CMS_lumi.extraText = "Preliminary"

   iPos = 0
   if( iPos==0 ): CMS_lumi.relPosX = 0.07

   H_ref = 600; 
   W_ref = 800; 
   W = W_ref
   H  = H_ref

   T = 0.08*H_ref
   B = 0.12*H_ref 
   L = 0.12*W_ref
   R = 0.04*W_ref

   canvas = ROOT.TCanvas("c2","c2",W,H)
   canvas.SetFillColor(0)
   canvas.SetBorderMode(0)
   canvas.SetFrameFillStyle(0)
   canvas.SetFrameBorderMode(0)
   canvas.SetLeftMargin( L/W )
   canvas.SetRightMargin( R/W )
   canvas.SetTopMargin( T/H )
   canvas.SetBottomMargin( B/H )
   canvas.SetTickx()
   canvas.SetTicky()
   
   return canvas
   
fbkg1 = ROOT.TFile.Open('../../AnalysisOutput/noCorr_tau21_0p5_ak4nocleaned_mj20_mwhcut/el/ExoDiBosonAnalysis.TTbar.root')
fbkg2 = ROOT.TFile.Open('../../AnalysisOutput/noCorr_tau21_0p5_ak4nocleaned_mj20_mwhcut/el/ExoDiBosonAnalysis.WJets.root')
fbkg3 = ROOT.TFile.Open('../../AnalysisOutput/noCorr_tau21_0p5_ak4nocleaned_mj20_mwhcut/el/ExoDiBosonAnalysis.SingleTop.root')
fsig = ROOT.TFile.Open('../../AnalysisOutput/noCorr_tau21_0p5_ak4nocleaned_mj20_mwhcut/el/ExoDiBosonAnalysis.Graviton.M-1000.el.root')

bkg1 = ROOT.TTree()
fbkg1.GetObject('tree',bkg1)
bkg2 = ROOT.TTree()
fbkg2.GetObject('tree',bkg2)
bkg3 = ROOT.TTree()
fbkg3.GetObject('tree',bkg3)
sig = ROOT.TTree()
fsig.GetObject('tree',sig)

ngenbkg1 = bkg1.GetEntries()
ngenbkg2 = bkg2.GetEntries()
ngenbkg3 = bkg3.GetEntries()
ngensig = sig.GetEntries()
print "tree signal entries: %i" %ngensig
print "1 - tree ttbar entries: %i" %ngenbkg1
print "2 -tree wjets entries: %i" %ngenbkg2
print "3 - tree stop entries: %i" %ngenbkg3

canv = get_canvas()
canv.cd()

#num = ROOT.TH1F('roc','roc curve',100,0.,1.)
#den = ROOT.TH1F('den','den',100,0.,1.)

#l = ROOT.TLegend(0.17,0.80,0.38,0.86,"","NDC")
#l.SetLineWidth(2)
#l.SetBorderSize(0)
#l.SetFillColor(0)
#l.SetTextFont(42)
#l.SetTextSize(0.04)
#l.SetTextAlign(12)
   
tau21cut = [0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9]

lumi = 10./3.

print "tau21 steps:"
print tau21cut

mass = 1000.
wwmin = mass-15*mass/100. 
wwmax = mass+15*mass/100.

print "WW mass limits:"
print wwmin,wwmax

hnums = fsig.Get("nPassedExoCandidateMass")
hdens = fsig.Get("nEvents")

es_start = hnums.GetBinContent(1)/hdens.GetBinContent(1)
print "Starting signal efficiency: %f" %(es_start)

hnumbkg = fbkg1.Get("nPassedExoCandidateMass")
hdenbkg = fbkg1.Get("nEvents")
eb_start = hnumbkg.GetBinContent(1)/hdenbkg.GetBinContent(1)
print "Starting ttbar bkg efficiency: %f" %(eb_start)

hnumbkg = fbkg2.Get("nPassedExoCandidateMass")
hdenbkg = fbkg2.Get("nEvents")
eb_start = hnumbkg.GetBinContent(1)/hdenbkg.GetBinContent(1)
print "Starting wjets bkg efficiency: %f" %(eb_start)

hnumbkg = fbkg3.Get("nPassedExoCandidateMass")
hdenbkg = fbkg3.Get("nEvents")
eb_start = hnumbkg.GetBinContent(1)/hdenbkg.GetBinContent(1)
print "Starting stop bkg efficiency: %f" %(eb_start)

cut = 'MWH > %f && MWH < %f' %(wwmin,wwmax)
nsig = float(sig.GetEntries(cut))
es = nsig/ngensig

histo = ROOT.TH1F("h","h", 80,  0. ,  200.)
cut = 'lumiweight*%f*(MWH > %f && MWH < %f)' %(lumi,wwmin,wwmax)
B = 0

bkg1.Draw("Mj>>h",cut)
B+=histo.Integral()
print "Starting ttbar yield: %f" %(histo.Integral())

bkg2.Draw("Mj>>h",cut)
B+=histo.Integral()
print "Starting wjets yield: %f" %(histo.Integral())

bkg3.Draw("Mj>>h",cut)
B+=histo.Integral()
print "Starting stop yield: %f" %(histo.Integral())

print "Default punzi: %f" %(es_start/(1+math.sqrt(B)))
print "B = %f" %B
print "es = %f" %es

punzi = []
cuts = []
signaleffs = []
bkgyields = []

for t in tau21cut:

 cut = 'tau21 < %f' %(t)
 cuts.append(cut)
 
 cut2 = 'tau21 > %f' %(t)
 nsig = float(sig.GetEntries(cut2))
 es = nsig/ngensig
 
 cut3 = 'lumiweight*%f*(tau21 > %f)' %(lumi,t)
 B = 0
 bkg1.Draw("Mj>>h",cut)
 B+=histo.Integral()

 bkg2.Draw("Mj>>h",cut)
 B+=histo.Integral()

 bkg3.Draw("Mj>>h",cut)
 B+=histo.Integral()
 
 punzi.append(es/(1+math.sqrt(B)))	 
 signaleffs.append(es)
 bkgyields.append(B)
 
 print cut
 print "   * sigeff %.6f - bkg yields %.6f - punzi %.6f" %(es,B,es/(1+math.sqrt(B)))
 #num.Fill(es,es/(1+math.sqrt(B)))
 #den.Fill(es)
      
