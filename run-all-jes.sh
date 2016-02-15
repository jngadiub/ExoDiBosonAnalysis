#!/bin/bash

#python do-jes-dijet.py -s BulkGraviton_ZZ -S
#python do-jes-dijet.py -s BulkGraviton_WW -S
#python do-jes-dijet.py -s Wprime -S

python do-jes.py -c el -S -s Wprime
python do-jes.py -c el -S -s Zprime
python do-jes.py -c el -S -s BulkGraviton

python do-jms.py -c mu -S -s Wprime
python do-jms.py -c mu -S -s Zprime
python do-jms.py -c mu -S -s BulkGraviton

python do-jms.py -c el -S -s Wprime
python do-jms.py -c el -S -s Zprime
python do-jms.py -c el -S -s BulkGraviton

python do-jmr.py -c mu -S -s Wprime
python do-jmr.py -c mu -S -s Zprime
python do-jmr.py -c mu -S -s BulkGraviton

python do-jmr.py -c el -S -s Wprime
python do-jmr.py -c el -S -s Zprime
python do-jmr.py -c el -S -s BulkGraviton
