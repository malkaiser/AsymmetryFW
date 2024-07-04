from Plot import HistogramInfo

# Define the histograms to be plotted
Histograms = []
# HistogramInfo('name', [first_bin,...,last_bin], [0TH width, width from 1st to 2nd bin, ...], bin_norm?, title, left_cut, right_cut, units )
# Histograms.append(HistogramInfo('n_bjets', [], [], 1.0, 'n_bjets',0,1,''))
Histograms.append(HistogramInfo('tau_pt_basic', [24.0, 240.0], [24.0, 12.0, 60.0], 100.0, 'pT(#tau)',25,300,'GeV'))
# Histograms.append(HistogramInfo('lepiso_basic', [0.0, 2.0], [1.0, 1.0, 1.0], 1, 'lepiso_basic', 0, 1,''))
# Histograms.append(HistogramInfo('lepiso_basic_all', [0.0, 2.0], [1.0, 1.0, 1.0], 1, 'lepiso_basic_all', 0, 1,''))
Histograms.append(HistogramInfo('lep_pt_basic', [24.0, 240.0], [24.0, 12.0, 60.0], 27, 'pT(l)',27,1000,'GeV'))
# Histograms.append(HistogramInfo('lepEta_basic', [-3, 3], [1.0, 0.1, 1.0], 1.0, 'eta(l) before',27,1000,''))
# Histograms.append(HistogramInfo('lepEta_basic_all', [-3, 3], [1.0, 0.1, 1.0], 1.0, 'eta(l) before',27,1000,''))
Histograms.append(HistogramInfo('mWT', [0, 12.0], [1.0, 1.2, 1.2], 2.0, 'Reconstructed W mass after all but',0,60.0,'GeV'))
Histograms.append(HistogramInfo('mWT', [0, 12.0], [1.0, 1.2, 1.2], 2.0, 'Reconstructed W mass after all but',0,60.0,'GeV'))

from Plot import stackPlot
import os
import ROOT
import sys

# Configure histograms to use 

name_suffix = "temp"
Data = {"Data":["data.root",ROOT.kBlack,0]}   
Signal = {"Signal":["Wjets.root",ROOT.kOrange+1,0]} 
Background = {"Zmumu":["Zmumu_PoPy.root",ROOT.kGreen,0], 
                        "Zee":["Zee_PoPy.root",ROOT.kTeal,0], 
                        "Ztautau":["Ztautau_PoPy.root",ROOT.kAzure,0],
                        "ttbar":["ttbar.root",ROOT.kYellow-7,0], 
                        "singletop":["singletop.root",ROOT.kSpring-7,0], 
                        "VV": ["VV.root", ROOT.kViolet,0]}

stackPlot(Data,Signal,Background,Histograms,name_suffix,lambda s,i : s,
          blind=False,blindMass=False,final_state="Z#rightarrow #tau#tau",
          regionLabel="Your region tittle",unblindPurityLimit=100,printVersion=True)