import ROOT
import CMS_lumi, tdrstyle
import time

def get_canvas():

   tdrstyle.setTDRStyle()
   CMS_lumi.lumi_13TeV = "13 TeV"
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

   #canvas = ROOT.TCanvas("c2","c2",50,50,W,H)
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


canv = get_canvas()
canv.SetLogy()
canv.cd()

pt = ROOT.TPaveText(0.16,0.18,0.37,0.35,"NDC")
pt.SetTextFont(42)
pt.SetTextSize(0.03)
pt.SetTextAlign(12)
pt.SetFillColor(0)
pt.SetBorderSize(0)
pt.SetFillStyle(0)  

text = pt.AddText('HVT model B parameters:')
text.SetTextFont(62)
pt.AddText('')
pt.AddText('g_{V} = 3')
pt.AddText('C_{H} = -0.976')
pt.AddText('C_{f} = 1.024')

mg = ROOT.TMultiGraph()

l = ROOT.TLegend(0.64,0.64,0.85,0.83,"","NDC")
l.SetLineWidth(2)
l.SetBorderSize(0)
l.SetFillColor(0)
l.SetTextFont(42)
l.SetTextSize(0.035)
l.SetTextAlign(12)

wpg8 = ROOT.TGraph("hvt-xsec-wp-8tev.txt")
wpg8.SetLineColor(ROOT.kRed)
wpg8.SetLineStyle(7)
wpg8.SetLineWidth(2)
mg.Add(wpg8)
l.AddEntry(wpg8,"W' 8 TeV",'L')

wpg13 = ROOT.TGraph("hvt-xsec-wp-13tev.txt")
wpg13.SetLineColor(ROOT.kRed)
wpg13.SetLineWidth(2)
mg.Add(wpg13)
l.AddEntry(wpg13,"W' 13 TeV",'L')

zpg8 = ROOT.TGraph("hvt-xsec-zp-8tev.txt")
zpg8.SetLineColor(ROOT.kBlue)
zpg8.SetLineStyle(7)
zpg8.SetLineWidth(2)
mg.Add(zpg8)
l.AddEntry(zpg8,"Z' 8 TeV",'L')

zpg13 = ROOT.TGraph("hvt-xsec-zp-13tev.txt")
zpg13.SetLineColor(ROOT.kBlue)
zpg13.SetLineWidth(2)
mg.Add(zpg13)
l.AddEntry(zpg13,"Z' 13 TeV",'L')

mg.Draw("AL")
l.Draw()
pt.Draw()

canv.Update()
#canv.cd()
#CMS_lumi.CMS_lumi(canv, 4, 0)
#canv.cd()
#canv.Update()
#canv.RedrawAxis()
#frame = canv.GetFrame()
#frame.Draw()
#canv.cd()
#canv.Update()

time.sleep(1000)
