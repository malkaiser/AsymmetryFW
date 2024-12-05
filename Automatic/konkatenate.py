import sys
import os
import ROOT as r
import time
# For parallel processing and timing
import multiprocessing

# For parsing the script arguments
import argparse

def concatenate(process):
    if process == "gg_Higgs":
        os.system("hadd gg_Higgs.root ggH*.root WmH*.root ZHlltautau*.root ZHllbb*.root VBFH*.root")
        os.system("mv gg_Higgs.root ../Root/")

    elif process == "singletop":
        os.system("hadd singletop.root st_schan_atop*.root st_schan_top*.root st_tchan_atop*.root st_tchan_top*.root st_wt_atop*.root st_wt_top*.root")
        os.system("mv singletop.root ../Root/")

    elif process == "ttbar":
        os.system("hadd ttbar.root ttbar*.root")
        os.system("mv ttbar.root ../Root/")

    elif process == "VBF_PoPy":
        os.system("hadd VBF_PoPy.root VBF_Zee_201*.root VBF_Zmumu_201*.root VBF_Ztautau_201*.root W_EWK_PoPy*.root")
        os.system("mv VBF_PoPy.root ../Root/")

    elif process == "VBF_sherpa":
        os.system("hadd VBF_sherpa.root VBF_Zee_sherpa*.root VBF_Zmumu_sherpa*.root VBF_Ztautau_sherpa*.root W_EWK_sherpa*.root")
        os.system("mv VBF_sherpa.root ../Root/")

    elif process == "Wjets":
        os.system("hadd Wjets.root Wminusenu*.root Wminusmunu*.root Wminustaunu*.root Wplusenu*.root Wplusmunu*.root Wplustaunu*.root")
        os.system("mv Wjets.root ../Root/")

    elif process == "Zee_PoPy":
        os.system("hadd Zee_PoPy.root Zee*.root")
        os.system("mv Zee_PoPy.root ../Root/")

    elif process == "Zmumu_PoPy":
        os.system("hadd Zmumu_PoPy.root Zmumu_201*.root")
        os.system("mv Zmumu_PoPy.root ../Root/")

    elif process == "Ztautau_PoPy":
        os.system("hadd Ztautau_PoPy.root Ztautau_201*.root")
        os.system("mv Ztautau_PoPy.root ../Root/")

    elif process == "Ztautau_MG":
        os.system("hadd Ztautau_MG.root Ztautau_MG1*.root Ztautau_MG2*.root Ztautau_MG3*.root Ztautau_MG4*.root Ztautau_MG5*.root")
        os.system("mv Ztautau_MG.root ../Root/")

    elif process == "Ztautau_MGNLO":
        os.system("hadd Ztautau_MGNLO.root Ztautau_MGNLO*.root")
        os.system("mv Ztautau_MGNLO.root ../Root/")

    elif process == "Ztautau_sherpa":
        os.system("hadd Ztautau_sherpa.root Ztautau_sherpa*.root")
        os.system("mv Ztautau_sherpa.root ../Root/")

    elif process == "Ztautau_SherpaNLO":
        os.system("hadd Ztautau_SherpaNLO.root Ztautau_SherpaNLO*.root")
        os.system("mv Ztautau_SherpaNLO.root ../Root/")
        
    elif process == "VV":
        os.system("hadd VV.root llll_*.root lllv_*.root llvv_*.root lvvv_*.root ZqqZvv_*.root ZqqZll_*.root WqqZvv_*.root WqqZll_*.root WlvZqq_*.root VV_EWK1*.root  VV_EWK2*.root  VV_EWK3*.root  VV_EWK4*.root VV_EWK5*.root VV_EWK6*.root VV_EWK7*.root VV_EWK8*.root VV_EWK_SemiLep*.root")
        os.system("mv VV.root ../Root/")

    elif process == "ZPrime200":
        os.system("hadd ZPrime200_MG.root ZPrime200*.root")
        os.system("mv ZPrime200_MG.root ../Root/")

    elif process == "ZPrime":
        os.system("hadd ZPrime250_MG.root ZPrime250*.root")
        os.system("mv ZPrime250_MG.root ../Root/")
        os.system("hadd ZPrime300_MG.root ZPrime300*.root")
        os.system("mv ZPrime300_MG.root ../Root/")
        os.system("hadd ZPrime350_MG.root ZPrime350*.root")
        os.system("mv ZPrime350_MG.root ../Root/")
        os.system("hadd ZPrime400_MG.root ZPrime400*.root")
        os.system("mv ZPrime400_MG.root ../Root/")
        os.system("hadd ZPrime450_MG.root ZPrime450*.root")
        os.system("mv ZPrime450_MG.root ../Root/")
        os.system("hadd ZPrime500_MG.root ZPrime500*.root")
        os.system("mv ZPrime500_MG.root ../Root/")

    elif process == "Z_SM_tt":
        os.system("hadd Z_SM_tt_hm.root Z_SM_tt_hm*.root")
        os.system("mv Z_SM_tt_hm.root ../Root/")
        os.system("hadd Z_SM_tt_lm.root Z_SM_tt_lm*.root")
        os.system("mv Z_SM_tt_lm.root ../Root/")

    elif process == "data":
        os.system("hadd data.root data*.root")
        os.system("mv data.root ../Root/")

    else:
        print("Process not found!")

def createArgumentParser():
    # Parse the script arguments
    parser = argparse.ArgumentParser()
    parser.add_argument("--j", help="Number of cores to use.",type=int,default=1)
    return parser

if __name__ == "__main__":
    # Parse the script arguments
    parser = createArgumentParser()
    args = parser.parse_args()

    # Start timer and greet the user
    initTime = time.time()
    print("Welcome to the new age!")


    # Define number of cores
    nCPU = args.j
    print("nCpus = "+str(nCPU))

    procTuple = ["gg_Higgs","singletop","ttbar","VBF_PoPy","VBF_sherpa","Wjets","Zee_PoPy","Zmumu_PoPy","Ztautau_PoPy","Ztautau_MG","Ztautau_MGNLO","Ztautau_sherpa","Ztautau_SherpaNLO","VV","ZPrime","Z_SM_tt","data"]

    os.system("mkdir -p ../Root/")
    print("Running...\n")
    with multiprocessing.Pool(processes=nCPU) as pool:
        pool.map(concatenate, procTuple)

    # Say goodbye and print the time taken
    print("Concatenation done")
    print("Time taken: "+str(time.time()-initTime))