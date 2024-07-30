from ModifiedPlot import HistogramInfo, stackPlot, Integral

# Define the histograms to be plotted. Append desired HistogramInfo to the Histograms array
Histograms = []
# HistogramInfo('name', [first_bin,...,last_bin], [0TH width, width from 1st to 2nd bin, ...], event per event (LMAO), title, left_cut, right_cut, units )

# m3_star
import os
import ROOT
import sys

# Configure histograms to use 
def main():
    Histograms.append(HistogramInfo('m3_star', [0.0, 200.0], [1.0, 1.0, 1.0], 1.0, 'm_{3}* After Cuts',160,300,'GeV'))
    Histograms.append(HistogramInfo('m3_star_basic', [0.0, 200.0], [1.0, 1.0, 1.0], 1.0, 'm_{3}* Before Cuts',160,300,'GeV'))

    # Reconstructed Transverse Mass of W boson
    Histograms.append(HistogramInfo('m_vis', [0.0, 200.0], [1.0, 1.0, 1.0], 1.0, 'm*_{vis} After Cuts',0,85,'GeV'))
    Histograms.append(HistogramInfo('m_vis_basic', [0.0, 200.0], [1.0, 1.0, 1.0], 1.0, 'm*_{vis} After Cuts',0,85,'GeV'))

    # Tau Transverse Momentum
    Histograms.append(HistogramInfo('tau_pt_basic', [0.0, 100.0], [1.0, 1.0, 1.0], 1.0, 'pT(#tau) Before Cuts',0,300,'GeV',xRange=[20.0,75.0]))
    Histograms.append(HistogramInfo('tau_pt_basic_all', [0.0, 100.0], [1.0, 1.0, 1.0], 1.0, 'pT(#tau) After Cuts',0,300,'GeV',xRange=[20.0,75.0]))

    # Light Lepton Transverse Momentum
    Histograms.append(HistogramInfo('lep_pt_basic', [0.0, 100.0], [1.0, 1.0, 1.0], 1, 'pT(#mu) Before Cuts',0,1000,'GeV',xRange=[20.0,75.0]))
    Histograms.append(HistogramInfo('lep_pt_basic_all', [0.0, 100.0], [1.0, 1.0, 1.0], 1, 'pT(#mu) After Cuts',0,1000,'GeV',xRange=[20.0,75.0]))

    # Reconstructed Tau RNN 1-prong
    Histograms.append(HistogramInfo('rnn_score_1p_basic', [0.0, 1.0], [0.2, 0.05, 0.2], 0.05, '1-p#tau RNN Score Before Cuts', 0, 0.40,''))
    Histograms.append(HistogramInfo('rnn_score_1p', [0.0, 1.0], [0.2, 0.05, 0.2], 0.05 , '1-p#tau RNN Score After Cuts', 0, 0.40,''))
    # Reconstructed Tau RNN 3-prong
    Histograms.append(HistogramInfo('rnn_score_3p_basic', [0.0, 1.0], [0.2, 0.05, 0.2], 0.05 , '3-p#tau RNN Score Before Cuts', 0, 0.50,''))
    Histograms.append(HistogramInfo('rnn_score_3p', [0.0, 1.0], [0.2, 0.05, 0.2], 0.05, '3-p#tau RNN Score After Cuts', 0, 0.50,''))
    # SigmaCosDeltaPhi
    Histograms.append(HistogramInfo('sigma_cos_del_phi_basic', [-2.0, 2.0], [0.2, 0.04, 0.2], 0.04, '#Sigma cos#(#Delta#phi) Before Cuts' , -0.1, 2.0,''))
    Histograms.append(HistogramInfo('sigma_cos_del_phi', [-2.0, 2.0], [0.2, 0.04, 0.2], 0.04, '#Sigma cos#(#Delta#phi) After Cuts', -0.1, 2.0,''))

    tau_Histo = HistogramInfo('tau_pt_basic', [0.0, 100.0], [1.0, 2.0, 5.0], 1.0, 'pT(#tau) Before Cuts',25,300,'GeV')
    tau_Histo_after = HistogramInfo('tau_pt_basic_all', [0.0, 100.0], [1.0, 2.0, 5.0], 1.0, 'pT(#tau) After Cuts',25,300,'GeV')

    name_suffix = "temp"
    Data = {"Data":["Root/data.root",ROOT.kBlack,0]}

    varInputGen = input("Sherpa or PoPy?")
    varInput = input("MJBG?")
    if varInputGen == "PoPy":
        Signal = {"Signal":["Root/Ztautau_PoPy.root",ROOT.kRed+1,0]}
        if varInput == "None":
            Background = {"Zmumu":["Root/Zmumu_PoPy.root",ROOT.kGreen,0], 
                                "Zee":["Root/Zee_PoPy.root",ROOT.kTeal,0], 
                                "ttbar":["Root/ttbar.root",ROOT.kYellow-7,0], 
                                "singletop":["Root/singletop.root",ROOT.kSpring-7,0],
                                "Higgs":["Root/gg_Higgs.root",ROOT.kGray+3,0],
                                "VV": ["Root/VV.root", ROOT.kViolet+3,0],
                                "VBF": ["Root/VBF_PoPy.root", ROOT.kViolet-3,0],
                                "W+jets":["Root/Wjets.root",ROOT.kAzure,0],}
        elif varInput == "Prime":
            Background = {"Zmumu":["Root/Zmumu_PoPy.root",ROOT.kGreen,0], 
                                "Zee":["Root/Zee_PoPy.root",ROOT.kTeal,0], 
                                "ttbar":["Root/ttbar.root",ROOT.kYellow-7,0], 
                                "singletop":["Root/singletop.root",ROOT.kSpring-7,0],
                                "Higgs":["Root/gg_Higgs.root",ROOT.kGray+3,0],
                                "MJBG":["Root/MJBG_prime_PoPy.root",ROOT.kPearl,0],
                                "VV": ["Root/VV.root", ROOT.kViolet+3,0],
                                "VBF": ["Root/VBF_PoPy.root", ROOT.kViolet-3,0],
                                "W+jets":["Root/Wjets.root",ROOT.kAzure,0],}
        elif varInput == "Unprimed":
            Background = {"Zmumu":["Root/Zmumu_PoPy.root",ROOT.kGreen,0], 
                                "Zee":["Root/Zee_PoPy.root",ROOT.kTeal,0], 
                                "ttbar":["Root/ttbar.root",ROOT.kYellow-7,0], 
                                "singletop":["Root/singletop.root",ROOT.kSpring-7,0],
                                "Higgs":["Root/gg_Higgs.root",ROOT.kGray+3,0],
                                "MJBG":["Root/MJBG_PoPy.root",ROOT.kPearl,0],
                                "VV": ["Root/VV.root", ROOT.kViolet+3,0],
                                "VBF": ["Root/VBF_PoPy.root", ROOT.kViolet-3,0],
                                "W+jets":["Root/Wjets.root",ROOT.kAzure,0],}
        else:
            print("Invalid input!")
            return -1
    elif varInputGen == "Sherpa":
        Signal = {"Signal":["Root/Ztautau_Sherpa.root",ROOT.kRed+1,0]}
        if varInput == "None":
            Background = {"Zmumu":["Root/Zmumu_PoPy.root",ROOT.kGreen,0], 
                                "Zee":["Root/Zee_PoPy.root",ROOT.kTeal,0], 
                                "ttbar":["Root/ttbar.root",ROOT.kYellow-7,0], 
                                "singletop":["Root/singletop.root",ROOT.kSpring-7,0],
                                "Higgs":["Root/gg_Higgs.root",ROOT.kGray+3,0],
                                "VV": ["Root/VV.root", ROOT.kViolet+3,0],
                                "VBF": ["Root/VBF_Sherpa.root", ROOT.kViolet-3,0],
                                "W+jets":["Root/Wjets.root",ROOT.kAzure,0],}
        elif varInput == "Prime":
            Background = {"Zmumu":["Root/Zmumu_PoPy.root",ROOT.kGreen,0], 
                                "Zee":["Root/Zee_PoPy.root",ROOT.kTeal,0], 
                                "ttbar":["Root/ttbar.root",ROOT.kYellow-7,0], 
                                "singletop":["Root/singletop.root",ROOT.kSpring-7,0],
                                "Higgs":["Root/gg_Higgs.root",ROOT.kGray+3,0],
                                "MJBG":["Root/MJBG_prime_Sherpa.root",ROOT.kPearl,0],
                                "VV": ["Root/VV.root", ROOT.kViolet+3,0],
                                "VBF": ["Root/VBF_Sherpa.root", ROOT.kViolet-3,0],
                                "W+jets":["Root/Wjets.root",ROOT.kAzure,0],}
        elif varInput == "Unprimed":
            Background = {"Zmumu":["Root/Zmumu_PoPy.root",ROOT.kGreen,0], 
                                "Zee":["Root/Zee_PoPy.root",ROOT.kTeal,0], 
                                "ttbar":["Root/ttbar.root",ROOT.kYellow-7,0], 
                                "singletop":["Root/singletop.root",ROOT.kSpring-7,0],
                                "Higgs":["Root/gg_Higgs.root",ROOT.kGray+3,0],
                                "MJBG":["Root/MJBG_Sherpa.root",ROOT.kPearl,0],
                                "VV": ["Root/VV.root", ROOT.kViolet+3,0],
                                "VBF": ["Root/VBF_Sherpa.root", ROOT.kViolet-3,0],
                                "W+jets":["Root/Wjets.root",ROOT.kAzure,0],}
        else:
            print("Invalid input!")
            return -1
    else:
        print("Invalid generator!")
        return -1
    stackPlot(Data,Signal,Background,Histograms,name_suffix,lambda s,i : s,
            blind=False,blindMass=False,final_state="Z#rightarrow#tau#tau", calculateDifference=False,
            regionLabel="Z#rightarrow#tau#tau Signal Region (#mu^{-}/#tau^{+})",unblindPurityLimit=100,printVersion=True)
    return 0

main()