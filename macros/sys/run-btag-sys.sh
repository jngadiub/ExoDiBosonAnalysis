#python do-btag-syst.py -T W -C HP0 -c mu -S -s Wprime
#python do-btag-syst.py -T W -C HP1 -c mu -S -s Wprime
#python do-btag-syst.py -T W -C HP2 -c mu -S -s Wprime
#python do-btag-syst.py -T W -C LP0 -c mu -S -s Wprime
#python do-btag-syst.py -T W -C LP1 -c mu -S -s Wprime
#python do-btag-syst.py -T W -C LP2 -c mu -S -s Wprime

#python do-btag-syst.py -T Z -C HP0 -c mu -S -s Wprime
#python do-btag-syst.py -T Z -C HP1 -c mu -S -s Wprime
#python do-btag-syst.py -T Z -C HP2 -c mu -S -s Wprime
#python do-btag-syst.py -T Z -C LP0 -c mu -S -s Wprime
#python do-btag-syst.py -T Z -C LP1 -c mu -S -s Wprime
#python do-btag-syst.py -T Z -C LP2 -c mu -S -s Wprime

#mkdir WprimeSys
#mv *BTag* WprimeSys/.

python do-btag-syst.py -T W -C HP0 -c mu -S -s BulkGraviton
python do-btag-syst.py -T W -C HP1 -c mu -S -s BulkGraviton
python do-btag-syst.py -T W -C HP2 -c mu -S -s BulkGraviton
python do-btag-syst.py -T W -C LP0 -c mu -S -s BulkGraviton
python do-btag-syst.py -T W -C LP1 -c mu -S -s BulkGraviton
python do-btag-syst.py -T W -C LP2 -c mu -S -s BulkGraviton

python do-btag-syst.py -T Z -C HP0 -c mu -S -s BulkGraviton
python do-btag-syst.py -T Z -C HP1 -c mu -S -s BulkGraviton
python do-btag-syst.py -T Z -C HP2 -c mu -S -s BulkGraviton
python do-btag-syst.py -T Z -C LP0 -c mu -S -s BulkGraviton
python do-btag-syst.py -T Z -C LP1 -c mu -S -s BulkGraviton
python do-btag-syst.py -T Z -C LP2 -c mu -S -s BulkGraviton

mkdir BulkGravitonSys
mv *BTag* BulkGravitonSys/.
