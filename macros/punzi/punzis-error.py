import math
import sys

args = sys.argv
print args
sig_num = float(args[1])
sig_den = float(args[2])
bkg = float(args[3])

print "sig_num %1.f sig_den %1.f bkg %2.f" %(sig_num,sig_den,bkg)

es = sig_num/sig_den
a = math.sqrt(sig_num)/sig_num
b = math.sqrt(sig_den)/sig_den
es_err = es*math.sqrt( a*a + b*b )

print "signal efficiency = %.4f +/- %.4f" %(es,es_err)    
       
punzi = es/(1+math.sqrt(bkg))            
a =  es_err/es
b = 1./(1+math.sqrt(bkg))
punzi_err = punzi*math.sqrt(a*a+b*b) 

print "punzi (x1000) = %f +/- %f" %(punzi*1000.,punzi_err*1000.)    

