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

def get_canvas(cname,lumi):

   CMS_lumi.lumi_13TeV = "WV #rightarrow #mu#nuqq, #sqrt{s} = "
   CMS_lumi.writeExtraText = 1
   CMS_lumi.extraText = "Preliminary"

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

tdrstyle.setTDRStyle()
Red = array('d',[ 1.00, 0.00, 0.00])
Green= array('d',[ 0.00, 1.00, 0.00])
Blue= array('d',[ 1.00, 0.00, 1.00])
Length= array('d',[ 0.00, 0.50, 1.00 ])
Number = 3
nb = 50
TColor.CreateGradientColorTable(Number,Length,Red,Green,Blue,nb)
   
#fwp = ROOT.TFile.Open("Wprime.root","READ")
fwp = ROOT.TFile.Open("Wprime.1200.root","READ")
twp = fwp.Get("tree")

c1 = get_canvas("c1",1)
hwp = TH2F("hwp","hwp",50,0,1,100,0,200)
twp.Draw("Mjpruned:tau21>>hwp","","COLZ")

fg = ROOT.TFile.Open("BulkG.1200.root","READ")
tg = fwp.Get("tree")

c2 = get_canvas("c2",1)
hg = TH2F("hg","hg",50,0,1,100,0,200)
tg.Draw("Mjpruned:tau21>>hg","","COLZ")


time.sleep(1000)
