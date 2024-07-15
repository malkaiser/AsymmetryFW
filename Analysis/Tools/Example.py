from Plot import HistogramInfo, stackPlot, Integral

# Define the histograms to be plotted. Append desired HistogramInfo to the Histograms array
Histograms = []
# HistogramInfo('name', [first_bin,...,last_bin], [0TH width, width from 1st to 2nd bin, ...], event per event (LMAO), title, left_cut, right_cut, units )
'''
# Missing Transverse Energy
Histograms.append(HistogramInfo('mET', [0.0, 120.0], [1.0, 2.0, 5.0], 1.0, 'E_{T}^{miss} After Cuts',60,300,'GeV'))
Histograms.append(HistogramInfo('mET_basic', [0.0, 120.0], [1.0, 2.0, 5.0], 1.0, 'E_{T}^{miss} Before Cuts',60,300,'GeV'))

# Tau Transverse Momentum
Histograms.append(HistogramInfo('tau_pt_basic', [0.0, 100.0], [1.0, 2.0, 5.0], 1.0, 'pT(#tau) Before Cuts',25,300,'GeV'))
Histograms.append(HistogramInfo('tau_pt_basic_all', [0.0, 100.0], [1.0, 2.0, 5.0], 1.0, 'pT(#tau) After Cuts',25,300,'GeV'))

# Light Lepton Transverse Momentum
Histograms.append(HistogramInfo('lep_pt_basic', [0.0, 100.0], [1.0, 2.0, 5.0], 1, 'pT(l) Before Cuts',27,1000,'GeV'))
Histograms.append(HistogramInfo('lep_pt_basic_all', [0.0, 100.0], [1.0, 2.0, 5.0], 1, 'pT(l)Before Cuts',27,1000,'GeV'))

# Reconstructed Transverse Mass of W boson
Histograms.append(HistogramInfo('mWT_basic', [0.0, 120.0], [1.0, 2.0, 1.0], 1.0, 'm_{T}#mu, MET) Before Cuts',0,60.0,'GeV'))
Histograms.append(HistogramInfo('mWT', [0.0, 120.0], [1.0, 2.0, 1.0], 1.0, 'm_{T}(#mu, MET) After Cuts',0,60.0,'GeV'))

# Reconstructed Tau RNN 1-prong
Histograms.append(HistogramInfo('rnn_score_1p_basic', [0.0, 1.0], [0.2, 0.05, 0.2], 1.0, '1-p#tau RNN Score Before Cuts', 0, 0.40,''))
Histograms.append(HistogramInfo('rnn_score_1p', [0.0, 1.0], [0.2, 0.05, 0.2], 1.0 , '1-p#tau RNN Score After Cuts', 0, 0.40,''))
# Reconstructed Tau RNN 3-prong
Histograms.append(HistogramInfo('rnn_score_3p_basic', [0.0, 1.0], [0.2, 0.05, 0.2], 1.0 , '3-p#tau RNN Score Before Cuts', 0, 0.40,''))
Histograms.append(HistogramInfo('rnn_score_3p', [0.0, 1.0], [0.2, 0.05, 0.2], 1.0, '3-p#tau RNN Score After Cuts', 0, 0.40,''))
# SigmaCosDeltaPhi
Histograms.append(HistogramInfo('sigma_cos_del_phi_basic', [-2.0, 2.0], [0.2, 0.04, 0.2], 1.0, '#Sigma cos#(#Delta#phi) Before Cuts' , -2.0, -0.1,''))
Histograms.append(HistogramInfo('sigma_cos_del_phi', [-2.0, 2.0], [0.2, 0.04, 0.2], 1.0, '#Sigma cos#(#Delta#phi) After Cuts', -2.0, -0.10,''))
'''
tau_Histo = HistogramInfo('tau_pt_basic', [0.0, 100.0], [1.0, 2.0, 5.0], 1.0, 'pT(#tau) Before Cuts',25,300,'GeV')
tau_Histo_after = HistogramInfo('tau_pt_basic_all', [0.0, 100.0], [1.0, 2.0, 5.0], 1.0, 'pT(#tau) After Cuts',25,300,'GeV')

import os
import ROOT
import sys

# Configure histograms to use 

name_suffix = "temp"
Data = {"Data":["Root/data.root",ROOT.kBlack,0]}

Signal = {"Signal":["Root/Wjets.root",ROOT.kOrange+1,0]}

Background = {"Zmumu":["Root/Zmumu_PoPy.root",ROOT.kGreen,0], 
                        "Zee":["Root/Zee_PoPy.root",ROOT.kTeal,0], 
                        "ttbar":["Root/ttbar.root",ROOT.kYellow-7,0], 
                        "singletop":["Root/singletop.root",ROOT.kSpring-7,0], 
                        "VV": ["Root/VV.root", ROOT.kViolet,0],
                        "Ztautau":["Root/Ztautau_PoPy.root",ROOT.kAzure,0],}
'''
stackPlot(Data,Signal,Background,Histograms,name_suffix,lambda s,i : s,
          blind=False,blindMass=False,final_state="W+Jets",
          regionLabel="W+Jets CR",unblindPurityLimit=100,printVersion=True)
'''
Integral(Data,Signal,Background, tau_Histo)
Integral(Data,Signal,Background, tau_Histo_after)