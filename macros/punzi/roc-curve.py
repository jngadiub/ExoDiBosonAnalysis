import ROOT
import sys
import time
import math
import CMS_lumi, tdrstyle
from array import *

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
   
fbkg = ROOT.TFile.Open('../../AnalysisOutput/topmassroc_csvwp/M1000/mu/ExoDiBosonAnalysis.TTbar.root')
fsig = ROOT.TFile.Open('../../AnalysisOutput/topmassroc_csvwp/M1000/mu/ExoDiBosonAnalysis.Graviton.M-1000.mu.root')

bkg = ROOT.TTree()
fbkg.GetObject('tree',bkg)
sig = ROOT.TTree()
fsig.GetObject('tree',sig)

ngenbkg = bkg.GetEntries()
ngensig = sig.GetEntries()
print "tree signal entries: %i" %ngensig
print "tree bkg entries: %i" %ngenbkg

canv = get_canvas()
canv.cd()

num = ROOT.TH1F('roc','roc curve',100,0.,1.)
den = ROOT.TH1F('den','den',100,0.,1.)

l = ROOT.TLegend(0.17,0.80,0.38,0.86,"","NDC")
l.SetLineWidth(2)
l.SetBorderSize(0)
l.SetFillColor(0)
l.SetTextFont(42)
l.SetTextSize(0.04)
l.SetTextAlign(12)

l2 = ROOT.TLegend(0.1821608,0.6923077,0.3919598,0.7517483,"","NDC")
l2.SetLineWidth(2)
l2.SetBorderSize(0)
l2.SetFillColor(0)
l2.SetTextFont(42)
l2.SetTextSize(0.04)
l2.SetTextAlign(12)
   
ltopmin = [x*10 for x in range(8,15)]
htopmin = [x*10 for x in range(10,17)]
ltopmax = [x*10 for x in range(18,31)]
htopmax = [x*10 for x in range(22,31)]

lweight = 831.76/25446993.
lumi = 10000.

print "top mass steps:"
print ltopmin
print ltopmax

mass = 1000.
wwmin = mass-15*mass/100. 
wwmax = mass+15*mass/100.

print "WW mass limits:"
print wwmin,wwmax

hnums = fsig.Get("nPassedExoCandidateMass")
hdens = fsig.Get("nEvents")
hnumbkg = fbkg.Get("nPassedExoCandidateMass")
hdenbkg = fbkg.Get("nEvents")

es_start = hnums.GetBinContent(1)/hdens.GetBinContent(1)
eb_start = hnumbkg.GetBinContent(1)/hdenbkg.GetBinContent(1)

print "Starting signal efficiency: %f" %(es_start)
print "Starting bkg efficiency: %f" %(eb_start)

cut = 'MWH > %f && MWH < %f' %(wwmin,wwmax)
nbkg = float(bkg.GetEntries(cut))
nsig = float(sig.GetEntries(cut))
B = nbkg*lweight*lumi
es = nsig/ngensig
eb = nbkg/ngenbkg
a = math.sqrt(nsig)/nsig
b = math.sqrt(ngensig)/ngensig

print "Default punzi: %f" %(es_start/(1+math.sqrt(B)))
print "B = %f" %B
print "es = %f" %es

punzi = []
cuts = []
signaleffs = []
bkgeffs = []
errsignaleffs = []
bkgyields = []

for lmin in ltopmin:
 for lmax in ltopmax:
  for hmin in htopmin:
   for hmax in htopmax:
    if hmax > hmin and lmax > lmin:
    
       cut = '((ltopmass > %f && ltopmass < %f) || (htopmass > %f && htopmass < %f))' %(lmin,lmax,hmin,hmax)
       cuts.append(cut)
       #cut+= ' && (MWH > %f && MWH < %f)' %(wwmin,wwmax)
       
       #nbkg1 = float(bkg.GetEntries(cut))
       #nsig1 = float(sig.GetEntries(cut))
       
       cut2 = '!( (ltopmass > %f && ltopmass < %f) || (htopmass > %f && htopmass < %f) )' %(lmin,lmax,hmin,hmax)
       #cut2+= ' && (MWH > %f && MWH < %f)' %(wwmin,wwmax)
       nbkg = float(bkg.GetEntries(cut2))
       nsig = float(sig.GetEntries(cut2))
       
       B = nbkg*lweight*lumi
       es = nsig/ngensig
       eb = nbkg/ngenbkg
       a = math.sqrt(nsig)/nsig
       b = math.sqrt(ngensig)/ngensig
       err = es*math.sqrt( a*a + b*b )
       
       punzi.append(es/(1+math.sqrt(B)))       
       signaleffs.append(es)
       errsignaleffs.append(err)
       bkgeffs.append(eb)
       bkgyields.append(B)
       
       #if lmin==80 and lmax==200 and hmin==100 and hmax==220:
       #print cut
       #print "   * sigeff %.6f - bkg eff %.6f - bkg yields %.6f - punzi %.6f" %(es,eb,B,es/(1+math.sqrt(B)))
       num.Fill(es,es/(1+math.sqrt(B)))
       den.Fill(es)
      
tmp = punzi[0]
index = 0
for p in range(0,len(punzi)):
   if punzi[p] > tmp:
      index = p
      tmp = punzi[p]

print "Max significance"
print index,punzi[index],cuts[index],bkgeffs[index],signaleffs[index],bkgyields[index]
a =  errsignaleffs[index]/signaleffs[index]
b = 1./(1+math.sqrt(bkgyields[index]))
err = punzi[index]*math.sqrt(a*a+b*b)
print " ---> error +/- %f" %(err)

tmp = punzi[0]
index = 0
for p in range(0,len(punzi)):
   if punzi[p] < tmp:
      index = p
      tmp = punzi[p]

print "Min significance"
print index,punzi[index],cuts[index],bkgeffs[index],signaleffs[index],bkgyields[index]
a =  errsignaleffs[index]/signaleffs[index]
b = 1./(1+math.sqrt(bkgyields[index]))
err = punzi[index]*math.sqrt(a*a+b*b)
print " ---> error +/- %f" %(err)

tmp = signaleffs[0]
index = 0
for p in range(0,len(signaleffs)):
   if signaleffs[p] > tmp:
      index = p
      tmp = signaleffs[p]

print "Max signal efficiency"
print index,punzi[index],cuts[index],bkgeffs[index],signaleffs[index],bkgyields[index]
 
tmp = bkgeffs[0]
index = 0
for p in range(0,len(bkgeffs)):
   if bkgeffs[p] < tmp:
      index = p
      tmp = bkgeffs[p]

print "Max bkg rejection"
print index,punzi[index],cuts[index],bkgeffs[index],signaleffs[index],bkgyields[index]
 
print "********************************"
#for p in range(0,len(punzi)):
#   if punzi[p] > 0.355 and punzi[p]<0.356: print cuts[p],punzi[p],bkgeffs[p],signaleffs[p]
            
#for e in range(0,len(signaleffs)):
#   if signaleffs[e] > 0.94: #and signaleffs[e] < 0.74:
#      print punzi[e],cuts[e],bkgeffs[e],signaleffs[e]  
                
num.Divide(den)
l.AddEntry(num,"M_{G} = 1 TeV , muon category","P")
num.SetMarkerStyle(20)
num.SetMarkerColor(ROOT.kPink-1)
num.Draw("P")
num.GetXaxis().SetTitle("Signal efficiency")
num.GetXaxis().SetLabelSize(0.04)
num.GetYaxis().SetTitle("Punzi's significance")
num.GetYaxis().SetTitleOffset(1.)
num.GetYaxis().SetLabelSize(0.04)
l.Draw()

x = array('d',[])
y = array('d',[])

bin = num.GetXaxis().FindBin(0.86176)

x.append(num.GetBinCenter(bin))
y.append(num.GetBinContent(bin))
gr = ROOT.TGraph(1,x,y)
gr.SetMarkerStyle(29)
gr.SetMarkerSize(2.4)
l2.AddEntry(gr,'','P')
gr.Draw("P")
l2.Draw()

pt = ROOT.TPaveText(0.2324121,0.6328671,0.4422111,0.7395105,"NDC")
pt.SetTextFont(42)
pt.SetTextSize(0.03)
pt.SetTextAlign(12)
pt.SetFillColor(0)
pt.SetBorderSize(0)
pt.SetFillStyle(0)  

text = pt.AddText('Optimal cut:')
text.SetTextFont(62)
pt.AddText('')
pt.AddText('m_{top}^{lept} #in [80,210] or m_{top}^{hadr} #in [100,230]')
pt.Draw()

canv.Update()

time.sleep(1000)	 

fbkg.Close()
fbkg.Delete()
fsig.Close()
fsig.Delete()
