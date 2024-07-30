from ModifiedPlot import HistogramInfo, stackPlot, Integral
import os
import ROOT
import sys

def main():
    # Define the histograms to be plotted. Append desired HistogramInfo to the Histograms array
    Histograms = []
    # HistogramInfo('name', [first_bin,...,last_bin], [0TH width, width from 1st to 2nd bin, ...], event per event (LMAO), title, left_cut, right_cut, units )
    
    # m3_star
    Histograms.append(HistogramInfo('m3_star', [0.0, 200.0], [1.0, 1.0, 1.0], 1.0, 'm_{3}* After Cuts',110,160,'GeV'))
    Histograms.append(HistogramInfo('m3_star_basic', [0.0, 200.0], [1.0, 1.0, 1.0], 1.0, 'm_{3}* Before Cuts',110,160,'GeV'))

    # Reconstructed Transverse Mass of W boson
    Histograms.append(HistogramInfo('m_vis', [0.0, 200.0], [1.0, 1.0, 1.0], 1.0, 'm*_{vis} After Cuts',0,85,'GeV'))
    Histograms.append(HistogramInfo('m_vis_basic', [0.0, 200.0], [1.0, 1.0, 1.0], 1.0, 'm*_{vis} After Cuts',0,85,'GeV'))

    # Tau Transverse Momentum
    Histograms.append(HistogramInfo('tau_pt_basic', [0.0, 100.0], [1.0, 1.0, 1.0], 1.0, 'pT(#tau) Before Cuts',0,300,'GeV',xRange=[0.0,120.0]))
    Histograms.append(HistogramInfo('tau_pt_basic_all', [0.0, 100.0], [1.0, 1.0, 1.0], 1.0, 'pT(#tau) After Cuts',0,300,'GeV',xRange=[0.0,120.0]))

    # Light Lepton Transverse Momentum
    Histograms.append(HistogramInfo('lep_pt_basic', [0.0, 100.0], [1.0, 1.0, 1.0], 1, 'pT(#mu) Before Cuts',0,1000,'GeV',xRange=[0.0,120.0]))
    Histograms.append(HistogramInfo('lep_pt_basic_all', [0.0, 100.0], [1.0, 1.0, 1.0], 1, 'pT(#mu) After Cuts',0,1000,'GeV',xRange=[0.0,120.0]))
    
    # Reconstructed Tau RNN 1-prong
    Histograms.append(HistogramInfo('rnn_score_1p_basic', [0.0, 1.0], [0.2, 0.05, 0.2], 0.05, '1-p#tau RNN Score Before Cuts', 0, 0.40,''))
    Histograms.append(HistogramInfo('rnn_score_1p', [0.0, 1.0], [0.2, 0.05, 0.2], 0.05 , '1-p#tau RNN Score After Cuts', 0, 0.40,''))
    # Reconstructed Tau RNN 3-prong
    Histograms.append(HistogramInfo('rnn_score_3p_basic', [0.0, 1.0], [0.2, 0.05, 0.2], 0.05 , '3-p#tau RNN Score Before Cuts', 0, 0.50,''))
    Histograms.append(HistogramInfo('rnn_score_3p', [0.0, 1.0], [0.2, 0.05, 0.2], 0.05, '3-p#tau RNN Score After Cuts', 0, 0.50,''))
    # SigmaCosDeltaPhi
    Histograms.append(HistogramInfo('sigma_cos_del_phi_basic', [-2.0, 2.0], [0.2, 0.04, 0.2], 0.04, '#Sigma cos#(#Delta#phi) Before Cuts' , -0.1, 2.0,''))
    Histograms.append(HistogramInfo('sigma_cos_del_phi', [-2.0, 2.0], [0.2, 0.04, 0.2], 0.04, '#Sigma cos#(#Delta#phi) After Cuts', -0.1, 2.0,''))

    # Configure histograms to use 
    folder = input("Path?\n")
    os.chdir(folder)
    name_suffix = "temp"
    Data = {"Data":["Root/data.root",ROOT.kBlack,0]}
    varInput = input("Sherpa or PoPy?\n").strip()
    if varInput == "PoPy":
        print("PoPy!")
        Signal = {"Signal":["Root/Ztautau_PoPy.root",ROOT.kRed+1,0]}

        Background = {"Zmumu":["Root/Zmumu_PoPy.root",ROOT.kGreen,0], 
                                "Zee":["Root/Zee_PoPy.root",ROOT.kTeal,0], 
                                "ttbar":["Root/ttbar.root",ROOT.kYellow-7,0], 
                                "singletop":["Root/singletop.root",ROOT.kSpring-7,0],
                                "Higgs":["Root/gg_Higgs.root",ROOT.kGray+3,0],
                                "VV": ["Root/VV.root", ROOT.kViolet+3,0],
                                "VBF": ["Root/VBF_PoPy.root", ROOT.kViolet-3,0],
                                "W+jets":["Root/Wjets.root",ROOT.kAzure,0],}
        save_file = "MJBG_PoPy.root"
    elif varInput == "Sherpa":
        print("Sherpa!")
        Signal = {"Signal":["Root/Ztautau_sherpa.root",ROOT.kRed+1,0]}

        Background = {"Zmumu":["Root/Zmumu_PoPy.root",ROOT.kGreen,0], 
                                "Zee":["Root/Zee_PoPy.root",ROOT.kTeal,0], 
                                "ttbar":["Root/ttbar.root",ROOT.kYellow-7,0], 
                                "singletop":["Root/singletop.root",ROOT.kSpring-7,0],
                                "Higgs":["Root/gg_Higgs.root",ROOT.kGray+3,0],
                                "VV": ["Root/VV.root", ROOT.kViolet+3,0],
                                "VBF": ["Root/VBF_sherpa.root", ROOT.kViolet-3,0],
                                "W+jets":["Root/Wjets.root",ROOT.kAzure,0],}
        save_file = "MJBG_Sherpa.root"
    else:
        print("Invalid input: ",varInput)
    if ("FailedORLNT" in folder or "SameSign" in folder):
        calculateRQCD = input("Calculate?\n").strip()
        if calculateRQCD == "yes":
            print("Calculating!")
            RQCD = float(input("RQCD"))
            ERRQCD = float(input("errQCD"))
            stackPlot(Data,Signal,Background,Histograms,name_suffix,lambda s,i : s,
                    blind=False,blindMass=False,final_state="Z#rightarrow#tau#tau", calculateDifference=True, export= True, exportName=save_file, rQCD=RQCD, errQCD=ERRQCD,
                    regionLabel="Z#rightarrow#tau#tau SR BUT FailedORLNT (#mu^{-}/#tau^{+} One-Prong)",unblindPurityLimit=100,printVersion=True)
            return 0
        elif calculateRQCD == "no":
            stackPlot(Data,Signal,Background,Histograms,name_suffix,lambda s,i : s,
                    blind=False,blindMass=False,final_state="Z#rightarrow#tau#tau", calculateDifference=True, export= False,
                    regionLabel="Z#rightarrow#tau#tau SR BUT FailedORLNT (#mu^{-}/#tau^{+} One-Prong)",unblindPurityLimit=100,printVersion=True)
            return 0
    else:
        stackPlot(Data,Signal,Background,Histograms,name_suffix,lambda s,i : s,
                blind=False,blindMass=False,final_state="Z#rightarrow#tau#tau", calculateDifference=True, export= False,
                regionLabel="Z#rightarrow#tau#tau SR BUT FailedORLNT (#mu^{-}/#tau^{+} One-Prong)",unblindPurityLimit=100,printVersion=True)
    return 0
main()
