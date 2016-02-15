import xml.etree.ElementTree as ET
import os,commands
import sys
from optparse import OptionParser
import ConfigParser
import ROOT
from ROOT import *
import math
from array import array
import time
import CMS_lumi, tdrstyle

def get_canvas(cname,lumi,sig):

   sname = "Z' #rightarrow WW"
   if sig == 'Wprime': sname = "W' #rightarrow WZ"
   if sig == 'BulkGraviton': sname = "G_{bulk} #rightarrow WW"
   CMS_lumi.lumi_13TeV = "%s, #sqrt{s} = "%sname
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


tdrstyle.setTDRStyle()
indir = '../../EXOVVSystematics/'
channel = 'el'
cats = ['HPW','HPZ']
signal = 'Zprime'
syst = ['JES','JMS','JMR']
sysup = {}
sysdown = {}
mg_HPW = TMultiGraph('mg_HPW','mg_HPW')
mg_HPZ = TMultiGraph('mg_HPZ','mg_HPZ')

l = ROOT.TLegend(0.5175879,0.6678322,0.7273869,0.8671329,"","NDC")
l.SetLineWidth(2)
l.SetBorderSize(0)
l.SetFillColor(0)
l.SetTextFont(42)
l.SetTextSize(0.035)
l.SetTextAlign(12)

##################### HPW ###########################  
for s in syst:
 
  fname = indir+s+'sys_'+channel+'_'+cats[0]+'_'+signal+'.txt'
  fin = open(fname,'r')

  sysup[s] = []
  sysdown[s] = []
  
  for line in fin:

   if signal!='BulkGraviton' and (line.find(signal) == -1 or line.find('800') != -1): continue
   if signal=='BulkGraviton' and (line.find('BulkG') == -1 or line.find('800') != -1): continue
   sysup[s].append(float(line.split(' ')[1].strip('\n')))
   sysdown[s].append(float(line.split(' ')[2].strip('\n')))

  fin.close() 

print "******** HPW ********"  
for s in syst:
 print s
 print sysup[s]
 print sysdown[s]

maxup_ = {}
minup_ = {}
maxdown_ = {}
mindown_ = {}

for s in syst:
 maxup_[s] = 0
 minup_[s] = 1000
 maxdown_[s] = 0
 mindown_[s] = 1000

for sn in syst:
 for s in sysup[sn]:
  if math.fabs(s) > math.fabs(maxup_[sn]): maxup_[sn] = s

for sn in syst:
 for s in sysup[sn]:
  if math.fabs(s) < math.fabs(minup_[sn]): minup_[sn] = s

for sn in syst:
 for s in sysdown[sn]:
  if math.fabs(s) > math.fabs(maxdown_[sn]): maxdown_[sn] = s

for sn in syst:
 for s in sysdown[sn]:
  if math.fabs(s) < math.fabs(mindown_[sn]): mindown_[sn] = s

print "max up: ",maxup_
print "min up: ",minup_
print "max down: ",maxdown_
print "min down: ",mindown_

gup_HPW = {}
point = -1
for sn in syst:
 point+=1
 x = array('d',[])
 x.append(point)
 x.append(point+1)
 x.append(point+1)
 x.append(point)
 y = array('d',[minup_[sn],minup_[sn],maxup_[sn],maxup_[sn]])
 gup_HPW[sn] = TGraphAsymmErrors(4,x,y)
 gup_HPW[sn].SetFillColor(ROOT.kRed)
 gup_HPW[sn].SetFillStyle(3001)
 gup_HPW[sn].SetLineStyle(1)
 gup_HPW[sn].SetLineWidth(3) 
 mg_HPW.Add(gup_HPW[sn])

point = -1
gdown_HPW = {}
for sn in syst:
 point+=1
 x = array('d',[])
 x.append(point)
 x.append(point+1)
 x.append(point+1)
 x.append(point)
 y = array('d',[mindown_[sn],mindown_[sn],maxdown_[sn],maxdown_[sn]])
 gdown_HPW[sn] = TGraphAsymmErrors(4,x,y)
 gdown_HPW[sn].SetFillColor(ROOT.kRed)
 gdown_HPW[sn].SetFillStyle(0)
 gdown_HPW[sn].SetLineStyle(1)
 gdown_HPW[sn].SetLineWidth(3) 
 mg_HPW.Add(gdown_HPW[sn])

##################### HPZ ###########################  
for s in syst:
 
  fname = indir+s+'sys_'+channel+'_'+cats[1]+'_'+signal+'.txt'
  fin = open(fname,'r')

  sysup[s] = []
  sysdown[s] = []
  
  for line in fin:

   if signal!='BulkGraviton' and (line.find(signal) == -1 or line.find('800') != -1): continue
   if signal=='BulkGraviton' and (line.find('BulkG') == -1 or line.find('800') != -1): continue
   sysup[s].append(float(line.split(' ')[1].strip('\n')))
   sysdown[s].append(float(line.split(' ')[2].strip('\n')))

  fin.close() 

print "******** HPZ ********"
for s in syst:
 print s
 print sysup[s]
 print sysdown[s]

maxup_ = {}
minup_ = {}
maxdown_ = {}
mindown_ = {}

for s in syst:
 maxup_[s] = 0
 minup_[s] = 1000
 maxdown_[s] = 0
 mindown_[s] = 1000

for sn in syst:
 for s in sysup[sn]:
  if math.fabs(s) > math.fabs(maxup_[sn]): maxup_[sn] = s

for sn in syst:
 for s in sysup[sn]:
  if math.fabs(s) < math.fabs(minup_[sn]): minup_[sn] = s

for sn in syst:
 for s in sysdown[sn]:
  if math.fabs(s) > math.fabs(maxdown_[sn]): maxdown_[sn] = s

for sn in syst:
 for s in sysdown[sn]:
  if math.fabs(s) < math.fabs(mindown_[sn]): mindown_[sn] = s

print "max up: ",maxup_
print "min up: ",minup_
print "max down: ",maxdown_
print "min down: ",mindown_

gup_HPZ = {}
point = -1
for sn in syst:
 point+=1
 x = array('d',[])
 x.append(point)
 x.append(point+1)
 x.append(point+1)
 x.append(point)
 y = array('d',[minup_[sn],minup_[sn],maxup_[sn],maxup_[sn]])
 gup_HPZ[sn] = TGraphAsymmErrors(4,x,y)
 gup_HPZ[sn].SetFillColor(ROOT.kBlack)
 gup_HPZ[sn].SetFillStyle(3001)
 gup_HPZ[sn].SetLineStyle(1)
 gup_HPZ[sn].SetLineWidth(3) 
 mg_HPZ.Add(gup_HPZ[sn])

point = -1
gdown_HPZ = {}
for sn in syst:
 point+=1
 x = array('d',[])
 x.append(point)
 x.append(point+1)
 x.append(point+1)
 x.append(point)
 y = array('d',[mindown_[sn],mindown_[sn],maxdown_[sn],maxdown_[sn]])
 gdown_HPZ[sn] = TGraphAsymmErrors(4,x,y)
 gdown_HPZ[sn].SetFillColor(ROOT.kBlack)
 gdown_HPZ[sn].SetFillStyle(0)
 gdown_HPZ[sn].SetLineStyle(1)
 gdown_HPZ[sn].SetLineWidth(3) 
 mg_HPZ.Add(gdown_HPZ[sn])


#################################################### 

hup_HPW = TH1F("hup_HPW","hup_HPW",1,0,1)
hup_HPW.SetFillColor(ROOT.kRed)
hup_HPW.SetLineColor(0)
hup_HPW.SetFillStyle(3001)
hup_HPW.SetLineStyle(2)
hup_HPW.SetLineWidth(0) 
l.AddEntry(hup_HPW,"WW-enriched cat. sys. up","F")
hdown_HPW = TH1F("hdown_HPW","hdown_HPW",1,0,1)
hdown_HPW.SetFillColor(ROOT.kRed)
hdown_HPW.SetLineColor(ROOT.kRed)
hdown_HPW.SetFillStyle(0)
hdown_HPW.SetLineStyle(3)
hdown_HPW.SetLineWidth(1) 
l.AddEntry(hdown_HPW,"WW-enriched cat. sys. down","F")
hup_HPZ = TH1F("hup_HPZ","hup_HPZ",1,0,1)
hup_HPZ.SetFillColor(ROOT.kBlack)
hup_HPZ.SetLineColor(0)
hup_HPZ.SetFillStyle(3001)
hup_HPZ.SetLineStyle(2)
hup_HPZ.SetLineWidth(0) 
l.AddEntry(hup_HPZ,"WZ-enriched cat. sys. up","F")
hdown_HPZ = TH1F("hdown_HPZ","hdown_HPZ",1,0,1)
hdown_HPZ.SetFillColor(ROOT.kBlack)
hdown_HPZ.SetLineColor(ROOT.kBlack)
hdown_HPZ.SetFillStyle(0)
hdown_HPZ.SetLineStyle(3)
hdown_HPZ.SetLineWidth(1) 
l.AddEntry(hdown_HPZ,"WZ-enriched cat. sys. down","F")

canv = get_canvas("c",1,signal)
canv.cd()
h = TH1F('h','h',3,0,3)
b = 0
for sn in syst:
 h.GetXaxis().SetBinLabel(b+1,sn) 
 b+=1

h.SetLineColor(kWhite)
h.Draw()
h.GetYaxis().SetTitle("Uncertainty [%]")
h.GetYaxis().SetTitleOffset(1)
h.GetXaxis().SetLabelSize(0.07)
h.SetMinimum(-50)
h.SetMaximum(50)
mg_HPW.Draw("F")
mg_HPZ.Draw("F")
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

time.sleep(1000)
