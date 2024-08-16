#include <cmath>
#include <TMacro.h>
#include "ReweightingTools.h"
#include "CLoop.h"
#include "CLoopConfig.h"

std::vector<std::string> split(const std::string& s, char delimiter);

void CLoop::Loop(float lumFactor, int z_sample, std::string key, const CLoopConfig& config, std::string usr_signCon, std::string usr_isoRNN, std::string usr_lepCharge, std::string usr_prongness)
{
    clock_t startTime = clock(); // get start time

    if (fChain == 0) return;

    Long64_t nentries = fChain->GetEntriesFast();
    
    Long64_t nLoop = nentries;

    std::cout<<"Analysing "<<nLoop<<" Events!"<<std::endl;

    Long64_t nbytes = 0, nb = 0;

    ActivateBranches(key);
    // Create output file
    key = key+".root";
    createOutputFile(key);

    // Create BDT
    m_zttBDT = ZTTBDT(config.m_bdtWeightsPath);

    // Create TTree
    bool saveHistograms = config.m_saveHistograms;
    bool saveEvents = config.m_saveEvents;   
    // loop over number of entries
    for (Long64_t jentry=0; jentry<nLoop;jentry++) {
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry,0);    nbytes += nb;
        double eventWeight = 1;
        // check if event is from real data
        if (!(key.substr(0,4)=="data")) {
            if (!(NOMINAL_pileup_combined_weight > -1)) continue; // TO AVOID FILLING HUGE WEIGHTS IN EWK Sample
            // take product of all scale factors
            /*
            std::cout << "weight_mc: " << weight_mc << std::endl;
            std::cout << "NOMINAL_pileup_combined_weight: " << NOMINAL_pileup_combined_weight << std::endl;
            std::cout << "lumFactor: " << lumFactor << std::endl;
            std::cout << "mjj_w: " << mjj_w << std::endl;
            std::cout << "muon_0_NOMINAL_MuEffSF_HLT_mu26_ivarmedium_OR_HLT_mu50_QualMedium: " << muon_0_NOMINAL_MuEffSF_HLT_mu26_ivarmedium_OR_HLT_mu50_QualMedium << std::endl;
            std::cout << "muon_0_NOMINAL_MuEffSF_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_QualMedium: " << muon_0_NOMINAL_MuEffSF_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_QualMedium << std::endl;
            std::cout << "muon_0_NOMINAL_MuEffSF_IsoTightTrackOnly_FixedRad: " << muon_0_NOMINAL_MuEffSF_IsoTightTrackOnly_FixedRad << std::endl;
            std::cout << "muon_0_NOMINAL_MuEffSF_Reco_QualMedium: " << muon_0_NOMINAL_MuEffSF_Reco_QualMedium << std::endl;
            std::cout << "jet_NOMINAL_central_jets_global_effSF_JVT: " << jet_NOMINAL_central_jets_global_effSF_JVT << std::endl;
            std::cout << "jet_NOMINAL_central_jets_global_ineffSF_JVT: " << jet_NOMINAL_central_jets_global_ineffSF_JVT << std::endl;
            std::cout << "jet_NOMINAL_forward_jets_global_effSF_JVT: " << jet_NOMINAL_forward_jets_global_effSF_JVT << std::endl;
            std::cout << "jet_NOMINAL_forward_jets_global_ineffSF_JVT: " << jet_NOMINAL_forward_jets_global_ineffSF_JVT << std::endl;
            std::cout << "jet_NOMINAL_global_effSF_MV2c10_FixedCutBEff_85: " << jet_NOMINAL_global_effSF_MV2c10_FixedCutBEff_85 << std::endl;
            std::cout << "jet_NOMINAL_global_ineffSF_MV2c10_FixedCutBEff_85: " << jet_NOMINAL_global_ineffSF_MV2c10_FixedCutBEff_85 << std::endl;
            std::cout << "tau_0_NOMINAL_TauEffSF_reco: " << tau_0_NOMINAL_TauEffSF_reco << std::endl;
            std::cout << "tau_0_NOMINAL_TauEffSF_JetRNNmedium: " << tau_0_NOMINAL_TauEffSF_JetRNNmedium << std::endl;
            */
            eventWeight = weight_mc*NOMINAL_pileup_combined_weight*lumFactor; /*
            *muon_0_NOMINAL_MuEffSF_HLT_mu26_ivarmedium_OR_HLT_mu50_QualMedium*muon_0_NOMINAL_MuEffSF_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_QualMedium
            *muon_0_NOMINAL_MuEffSF_IsoTightTrackOnly_FixedRad*muon_0_NOMINAL_MuEffSF_Reco_QualMedium // muon_0_NOMINAL_MuEffSF_TTVA */
            /* *jet_NOMINAL_central_jets_global_effSF_JVT*jet_NOMINAL_central_jets_global_ineffSF_JVT*jet_NOMINAL_forward_jets_global_effSF_JVT
            *jet_NOMINAL_forward_jets_global_ineffSF_JVT*jet_NOMINAL_global_effSF_MV2c10_FixedCutBEff_85*jet_NOMINAL_global_ineffSF_MV2c10_FixedCutBEff_85
            *tau_0_NOMINAL_TauEffSF_reco*tau_0_NOMINAL_TauEffSF_JetRNNmedium; */
        }
        // fill histograms
        //cout << eventWeight;
        if (saveHistograms) Fill(eventWeight, z_sample, key, usr_signCon, usr_isoRNN, usr_lepCharge, usr_prongness);
        if (saveEvents) FillTree(eventWeight, z_sample, key, usr_signCon, usr_isoRNN, usr_lepCharge, usr_prongness);
        // end filling

    }
    // end style and writing
    if (saveHistograms) Style(lumFactor);   
    if (saveEvents) {
        m_outputFile->WriteObject(m_signalTree.GetTree(),"SIGNAL");
        m_outputFile->WriteObject(m_backgroundTree.GetTree(),"BACKGROUND");
    }
    // Add the code to the file if it is the first sample of the kind
    std::vector<std::string> tokens = split(key,'_');
    std::string lastToken = tokens[tokens.size()-1];
    bool isFirstSample = lastToken=="0NOMINAL.root";
    if (isFirstSample) {
        TMacro sourceCode("Analysis.cpp");
        sourceCode.Write();
    }

    clock_t endTime = clock(); // get end time
    // calculate time taken and print it
    double time_spent = (endTime - startTime) / CLOCKS_PER_SEC;
    std::cout << "Time processing == " <<time_spent << std::endl;
}