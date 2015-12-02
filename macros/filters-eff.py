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
from ROOT import *

def get_canvas(cname,lumi):

   CMS_lumi.lumi_13TeV = "%.1f pb^{-1},#sqrt{s} = " %(lumi)
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

def get_line(xmin,xmax,y,style):

   line = ROOT.TLine(xmin,y,xmax,y)
   line.SetLineColor(kRed)
   line.SetLineStyle(style)
   line.SetLineWidth(2)
   return line

def OverflowToLast(hist):

  binContent = hist.GetBinContent(hist.GetNbinsX()) + hist.GetBinContent(hist.GetNbinsX()+1);
  binError = TMath.Sqrt(hist.GetBinError(hist.GetNbinsX())*hist.GetBinError(hist.GetNbinsX()) + hist.GetBinError(hist.GetNbinsX()+1)*hist.GetBinError(hist.GetNbinsX()+1));
  hist.SetBinContent(hist.GetNbinsX(),binContent);
  hist.SetBinContent(hist.GetNbinsX()+1,0.);

  binContent = hist.GetBinContent(0) + hist.GetBinContent(1);
  binError = TMath.Sqrt(hist.GetBinError(0)*hist.GetBinError(0) + hist.GetBinError(1)*hist.GetBinError(1));
  hist.SetBinContent(1,binContent);
  hist.SetBinContent(0,0.);
  
  return hist

def get_pull(sfdict_):
   
   pull = ROOT.TGraphAsymmErrors( len(sfdict_['x']),
                                   sfdict_['x'], sfdict_['y'],
                                   sfdict_['errxlo'], sfdict_['errxhi'],
                                   sfdict_['errylo'], sfdict_['erryhi'] ) 

   pull.SetLineColor(1)      
   pull.SetLineColor(1)
   pull.SetMarkerColor(1)
   pull.SetMarkerStyle(20)
   pull.SetMarkerSize(1.)
         
   return pull
				   
def get_sf(gr_num,gr_den):

   sfdict = {}
   x_ = array('d',[])
   y_ = array('d',[])
   errxhi_ = array('d',[])
   erryhi_ = array('d',[])
   errxlo_ = array('d',[])
   errylo_ = array('d',[])
   
   x_num = ROOT.Double(0.)
   y_num = ROOT.Double(0.)
   x_den = ROOT.Double(0.)
   y_den = ROOT.Double(0.)
   for p in range(gr_num.GetN()):
   
      gr_num.GetPoint(p,x_num,y_num)
      gr_den.GetPoint(p,x_den,y_den)

      if y_den == 0 or y_num == 0: continue

      x_.append(x_num)            
      y_.append(y_num/y_den)

      #print x_num,y_num/y_den
      
      errxhi_.append(gr_num.GetErrorXhigh(p))
      errxlo_.append(gr_num.GetErrorXlow(p))

      errnum_2 = gr_num.GetErrorYhigh(p)*gr_num.GetErrorYhigh(p)
      num_2 = y_num*y_num
      errden_2 = gr_den.GetErrorYhigh(p)*gr_den.GetErrorYhigh(p)
      den_2 = y_den*y_den
      err = (y_num/y_den)*TMath.Sqrt( errnum_2/num_2 + errden_2/den_2 )
      erryhi_.append(err)

      #print 'errhi %f' %err
      errnum_2 = gr_num.GetErrorYlow(p)*gr_num.GetErrorYlow(p)
      num_2 = y_num*y_num
      errden_2 = gr_den.GetErrorYlow(p)*gr_den.GetErrorYlow(p)
      den_2 = y_den*y_den
      err = (y_num/y_den)*TMath.Sqrt( errnum_2/num_2 + errden_2/den_2 )
      errylo_.append(err)
 
      #print 'errlo %f' %err
     
   sfdict['x'] = x_
   sfdict['y'] = y_
   sfdict['errxhi'] = errxhi_
   sfdict['erryhi'] = erryhi_
   sfdict['errxlo'] = errxlo_
   sfdict['errylo'] = errylo_   
   
   return sfdict           

def get_histo(nbins,xmin,xmax,xtitle):

   gt = TH1F("gt","gt",nbins,xmin,xmax);
   gt.SetMinimum(0.0001);
   gt.SetMaximum(1.9999);
   gt.SetDirectory(0);
   gt.SetStats(0);
   gt.SetLineStyle(0);
   gt.SetMarkerStyle(20);
   gt.GetXaxis().SetTitle(xtitle);
   gt.GetXaxis().SetLabelFont(42);
   gt.GetXaxis().SetLabelOffset(0.02);
   gt.GetXaxis().SetLabelSize(0.15);
   gt.GetXaxis().SetTitleSize(0.15);
   gt.GetXaxis().SetTitleOffset(1.2);
   gt.GetXaxis().SetTitleFont(42);
   gt.GetYaxis().SetTitle("#frac{Data}{MC}");
   gt.GetYaxis().CenterTitle(True);
   gt.GetYaxis().SetNdivisions(205);
   gt.GetYaxis().SetLabelFont(42);
   gt.GetYaxis().SetLabelOffset(0.007);
   gt.GetYaxis().SetLabelSize(0.15);
   gt.GetYaxis().SetTitleSize(0.15);
   gt.GetYaxis().SetTitleOffset(0.4);
   gt.GetYaxis().SetTitleFont(42);
   gt.GetXaxis().SetNdivisions(505)
   
   return gt

def get_hgraph(nbins,xmin,xmax,xtitle):

   hgraph = TH1F("hgraph","hgraph",nbins,xmin,xmax);
   hgraph.SetMinimum(0.8)
   hgraph.SetMaximum(1.2)
   hgraph.SetDirectory(0);
   hgraph.SetStats(0);
   hgraph.SetLineStyle(0);
   hgraph.SetMarkerStyle(20);
   hgraph.GetYaxis().SetTitle('Trigger Efficiency');
   hgraph.GetXaxis().SetTitle(xtitle);
   hgraph.GetYaxis().SetNdivisions(505);
   hgraph.GetYaxis().SetLabelFont(42);
   hgraph.GetYaxis().SetLabelOffset(0.007);
   hgraph.GetYaxis().SetLabelSize(0.045);
   hgraph.GetYaxis().SetTitleSize(0.045);
   hgraph.GetYaxis().SetTitleOffset(1.2);
   hgraph.GetYaxis().SetTitleFont(42);
   hgraph.GetXaxis().SetLabelSize(0.045);
   hgraph.GetXaxis().SetTitleSize(0.045);
   hgraph.GetXaxis().SetTitleOffset(1.5);
      
   return hgraph
  
#--------------------------------------------------------#
tdrstyle.setTDRStyle()
#suffix = "Eta"
suffix = "PT"
hdenname = 'FiltersEff%s_den'%suffix
#rebin = 1
rebin = 40

#--------------------------------------------------------#
pt = ROOT.TPaveText(0.1557789,0.215035,0.4949749,0.3846154,"NDC")
pt.SetBorderSize(0)
pt.SetFillStyle(0)
pt.SetTextFont(62)
pt.SetTextSize(0.038)
pt.SetTextAlign(12)
pt.SetFillColor(0)
text = pt.AddText("AK8 Jets")
text.SetTextFont(62)
text = pt.AddText("p_{T} > 200 GeV,|#eta| < 2.4")
text.SetTextFont(42)
text = pt.AddText("Jet ID Loose ")
text.SetTextFont(42)

pt2 = ROOT.TPaveText(0.1557789,0.7604895,0.4949749,0.8811189,"NDC")
pt2.SetBorderSize(0)
pt2.SetFillStyle(0)
pt2.SetTextFont(62)
pt2.SetTextSize(0.038)
pt2.SetTextAlign(12)
pt2.SetFillColor(0)
text = pt2.AddText("All filters:")
#text = pt2.AddText("EEBadSc Filter")
#text = pt2.AddText("HBHE Noise Filter Loose")
#text = pt2.AddText("CSC Beam Halo Filter")
#text = pt2.AddText("GoodVtx Filter")
#text = pt2.AddText("EEBadSc Filter")
text.SetTextFont(62)
text = pt2.AddText('HBHE,CSCHalo,GoodVtx,EEBadSc')
text.SetTextFont(42)

l = ROOT.TLegend(0.6193467,0.6748252,0.8291457,0.8444056,"","NDC")
l.SetLineWidth(2)
l.SetBorderSize(0)
l.SetFillColor(0)
l.SetFillStyle(0)
l.SetTextFont(42)
l.SetTextSize(0.04495504)
l.SetTextAlign(12)

#--------------------------------------------------------#

fname1 = '../../AnalysisOutput/QCD.root' 
tfile = ROOT.TFile.Open(fname1)

hnumname = 'HBHEFilterEff%s' %suffix
hnum1 = ROOT.TH1F(tfile.Get(hnumname))
hden1 = ROOT.TH1F(tfile.Get(hdenname))
nu = hnum1.Integral(hnum1.GetXaxis().FindBin(200.),hnum1.GetNbinsX())
de = hden1.Integral(hden1.GetXaxis().FindBin(200.),hden1.GetNbinsX())
if suffix == "PT": print "RunC hbhe eff = %f" %(nu/de)
hnum1.Rebin(rebin)
hden1.Rebin(rebin) 

hnumname = 'CSCHaloFilterEff%s' %suffix
hnum2 = ROOT.TH1F(tfile.Get(hnumname))
hden2 = ROOT.TH1F(tfile.Get(hdenname))
nu = hnum2.Integral(hnum2.GetXaxis().FindBin(200.),hnum2.GetNbinsX())
de = hden2.Integral(hden2.GetXaxis().FindBin(200.),hden2.GetNbinsX())
if suffix == "PT": print "RunC cschalo eff = %f" %(nu/de)
hnum2.Rebin(rebin)
hden2.Rebin(rebin) 

hnumname = 'GoodVtxFilterEff%s' %suffix
hnum3 = ROOT.TH1F(tfile.Get(hnumname))
hden3 = ROOT.TH1F(tfile.Get(hdenname))
nu = hnum3.Integral(hnum3.GetXaxis().FindBin(200.),hnum3.GetNbinsX())
de = hden3.Integral(hden3.GetXaxis().FindBin(200.),hden3.GetNbinsX())
if suffix == "PT": print "RunC goodvtx eff = %f" %(nu/de)
hnum3.Rebin(rebin)
hden3.Rebin(rebin)

hnumname = 'EEBadScFilterEff%s' %suffix
hnum4 = ROOT.TH1F(tfile.Get(hnumname))
hden4 = ROOT.TH1F(tfile.Get(hdenname))
nu = hnum4.Integral(hnum4.GetXaxis().FindBin(200.),hnum4.GetNbinsX())
de = hden4.Integral(hden4.GetXaxis().FindBin(200.),hden4.GetNbinsX())
if suffix == "PT": print "RunC eebadsc eff = %f" %(nu/de)
hnum4.Rebin(rebin)
hden4.Rebin(rebin)

hnumname = 'METFiltersEff%s' %suffix
hnum5 = ROOT.TH1F(tfile.Get(hnumname))
hden5 = ROOT.TH1F(tfile.Get(hdenname))
nu = hnum5.Integral(hnum5.GetXaxis().FindBin(200.),hnum5.GetNbinsX())
de = hden5.Integral(hden5.GetXaxis().FindBin(200.),hden5.GetNbinsX())
if suffix == "PT": print "RunC all filters eff = %f" %(nu/de)
hnum5.Rebin(rebin)
hden5.Rebin(rebin)

hmet = ROOT.TH1F(tfile.Get('HBHEFilterMET'))
hsumet = ROOT.TH1F(tfile.Get('HBHEFilterSumET'))

#--------------------------------------------------------#
print "==========================================="

fname2 = '../../AnalysisOutput/JetHT.Run2015D.root'
tfile2 = ROOT.TFile.Open(fname2)

hnumname = 'HBHEFilterEff%s' %suffix
hnum6 = ROOT.TH1F(tfile2.Get(hnumname))
hden6 = ROOT.TH1F(tfile2.Get(hdenname))
nu = hnum6.Integral(hnum6.GetXaxis().FindBin(200.),hnum6.GetNbinsX())
de = hden6.Integral(hden6.GetXaxis().FindBin(200.),hden6.GetNbinsX())
if suffix == "PT": print "RunD hbhe eff = %f" %(nu/de)
hnum6.Rebin(rebin)
hden6.Rebin(rebin) 

hnumname = 'CSCHaloFilterEff%s' %suffix
hnum7 = ROOT.TH1F(tfile2.Get(hnumname))
hden7 = ROOT.TH1F(tfile2.Get(hdenname))
nu = hnum7.Integral(hnum7.GetXaxis().FindBin(200.),hnum7.GetNbinsX())
de = hden7.Integral(hden7.GetXaxis().FindBin(200.),hden7.GetNbinsX())
if suffix == "PT": print "RunD cschalo eff = %f" %(nu/de)
hnum7.Rebin(rebin)
hden7.Rebin(rebin) 

hnumname = 'GoodVtxFilterEff%s' %suffix
hnum8 = ROOT.TH1F(tfile2.Get(hnumname))
hden8 = ROOT.TH1F(tfile2.Get(hdenname))
nu = hnum8.Integral(hnum8.GetXaxis().FindBin(200.),hnum8.GetNbinsX())
de = hden8.Integral(hden8.GetXaxis().FindBin(200.),hden8.GetNbinsX())
if suffix == "PT": print "RunD goodvtx eff = %f" %(nu/de)
hnum8.Rebin(rebin)
hden8.Rebin(rebin)

hnumname = 'EEBadScFilterEff%s' %suffix
hnum9 = ROOT.TH1F(tfile2.Get(hnumname))
hden9 = ROOT.TH1F(tfile2.Get(hdenname))
nu = hnum9.Integral(hnum9.GetXaxis().FindBin(200.),hnum9.GetNbinsX())
de = hden9.Integral(hden9.GetXaxis().FindBin(200.),hden9.GetNbinsX())
if suffix == "PT": print "RunD eebadsc eff = %f" %(nu/de)
hnum9.Rebin(rebin)
hden9.Rebin(rebin)

hnumname = 'METFiltersEff%s' %suffix
hnum10 = ROOT.TH1F(tfile2.Get(hnumname))
hden10 = ROOT.TH1F(tfile2.Get(hdenname))
nu = hnum10.Integral(hnum10.GetXaxis().FindBin(200.),hnum10.GetNbinsX())
de = hden10.Integral(hden10.GetXaxis().FindBin(200.),hden10.GetNbinsX())
if suffix == "PT": print "RunD all filters eff = %f" %(nu/de)
hnum10.Rebin(rebin)
hden10.Rebin(rebin)

hmet2 = ROOT.TH1F(tfile2.Get('HBHEFilterMET'))
hsumet2 = ROOT.TH1F(tfile2.Get('HBHEFilterSumET'))

#--------------------------------------------------------#

'''
hsumet.GetXaxis().SetTitleSize(0.045)
hsumet.GetYaxis().SetTitleSize(0.045)
hsumet.GetXaxis().SetLabelSize(0.04)
hsumet.GetYaxis().SetLabelSize(0.04)
hsumet.GetYaxis().SetTitle("Normalized")
#hsumet.GetXaxis().SetTitle("E_{T}^{miss} [GeV]")
hsumet.GetXaxis().SetTitle("met/sumET")
hsumet.GetXaxis().SetTitleOffset(1.2)
hsumet.GetYaxis().SetTitleOffset(1.1)

hsumet = OverflowToLast(hsumet)
hsumet.Rebin(10)
hsumet.Scale(1./hsumet.GetEntries())
hsumet.SetLineColor(kRed)
hsumet.SetLineWidth(2)
l.AddEntry(hsumet,'Run 2015 C','LP')

hsumet2 = OverflowToLast(hsumet2)
hsumet2.Rebin(10)
hsumet2.Scale(1./hsumet2.GetEntries())
hsumet2.SetLineColor(kBlue)
hsumet2.SetLineWidth(2)
l.AddEntry(hsumet2,'Run 2015 D','LP')

hsumet.Draw("HIST")
hsumet2.Draw("HISTsame")
l.Draw()

hmet.GetXaxis().SetTitleSize(0.045)
hmet.GetYaxis().SetTitleSize(0.045)
hmet.GetXaxis().SetLabelSize(0.04)
hmet.GetYaxis().SetLabelSize(0.04)
hmet.GetYaxis().SetTitle("Normalized")
hmet.GetXaxis().SetTitle("E_{T}^{miss} [GeV]")
hmet.GetXaxis().SetTitleOffset(1.2)
hmet.GetYaxis().SetTitleOffset(1.1)

hmet = OverflowToLast(hmet)
hmet.Scale(1./hmet.Integral())
hmet.SetLineColor(kRed)
hmet.SetLineWidth(2)
l.AddEntry(hmet,'Run 2015 C','LP')

hmet2 = OverflowToLast(hmet2)
hmet2.Scale(1./hmet2.Integral())
hmet2.SetLineColor(kBlue)
hmet2.SetLineWidth(2)
l.AddEntry(hmet2,'Run 2015 D','LP')

hmet.Draw("HIST")
hmet2.Draw("HISTsame")
l.Draw()
'''

eff1 = ROOT.TGraphAsymmErrors()
eff1.Divide(hnum5,hden5)
eff1.SetMarkerStyle(4)
eff1.SetMarkerColor(ROOT.kBlue)
eff1.SetLineColor(ROOT.kBlack)
#mg.Add(eff1)
l.AddEntry(eff1,'Simulation','LP')

eff2 = ROOT.TGraphAsymmErrors()
eff2.Divide(hnum10,hden10)
eff2.SetMarkerStyle(23)
eff2.SetMarkerColor(ROOT.kRed)
eff2.SetLineColor(ROOT.kBlack)
#mg.Add(eff2)
l.AddEntry(eff2,'Data Run2015D','LP')

canv = get_canvas("c1",578.31)
canv.SetGrid()
canv.cd()

'''
pad0 = ROOT.TPad("pad0","pad0",0,0.3,1,1)
pad0.SetRightMargin(0.1);
pad0.SetTopMargin(0.1);
pad0.SetBottomMargin(0);
pad0.Draw()
pad0.cd()  
'''
if suffix == "PT":
 hmg = get_hgraph(eff1.GetN(),200,1500,'AK8 Jet p_{T} [GeV]')
else:
 hmg = get_hgraph(eff1.GetN(),-2.4,2.4,'AK8 Jet Eta')
 
eff1.SetHistogram(hmg)

eff1.Draw('AP')
eff2.Draw('Psame')
pt.Draw()
pt2.Draw()
l.Draw()

'''
canv.Update()	
canv.cd()

pad1 = ROOT.TPad("pad1","pad1",0,0,1,0.30) 
pad1.SetRightMargin(0.1)
pad1.SetTopMargin(0)
pad1.SetBottomMargin(0.4)
pad1.Draw("same")
pad1.cd()

ph = get_pull(get_sf(eff2,eff1))
if suffix == "PT":
 gt = get_histo(ph.GetN(),200,1500,'AK8 Jet p_{T} [GeV]')
else:
 gt = get_histo(ph.GetN(),-2.4,2.4,'AK8 Jet Eta')

ph.SetHistogram(gt);
ph.Draw("AP")
if suffix == "PT":
 li = get_line(200,1500,1,1)
else:
 li = get_line(-2.4,2.4,1,1)
 
li.Draw()
ph.Draw("Psame")
'''    
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
