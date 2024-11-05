#include "OutputTree.h"

OutputTree::OutputTree(const char* treeName, const char* treeDescription){
    // Creating the tree
    m_Tree = std::make_unique<TTree>(treeName, treeDescription);

    // Setting tree branches

    m_Tree->Branch("m_event_number",&m_event_number);
    m_Tree->Branch("m_mcWeight",&m_mcWeight);
    m_Tree->Branch("m_n_jets",&m_n_jets);

    m_Tree->Branch("m_tau_pT", &m_tau_pT);
    m_Tree->Branch("m_lep_pT",&m_lep_pT);
    m_Tree->Branch("m_met_pT",&m_met_pT);
    m_Tree->Branch("m_ljet_0_pT",&m_ljet_0_pT);
    m_Tree->Branch("m_ljet_1_pT",&m_ljet_1_pT);
    m_Tree->Branch("m_pT_sum",&m_pT_sum);
    m_Tree->Branch("m_tau_nu_pT",&m_tau_nu_pT);
    m_Tree->Branch("m_lep_nu_pT",&m_lep_nu_pT);

    m_Tree->Branch("m_tau_pT_norm",&m_tau_pT_norm);
    m_Tree->Branch("m_lep_pT_norm",&m_lep_pT_norm);
    m_Tree->Branch("m_met_pT_norm",&m_met_pT_norm);

    m_Tree->Branch("m_tau_eta",&m_tau_eta);
    m_Tree->Branch("m_lep_eta",&m_lep_eta);
    m_Tree->Branch("m_met_eta",&m_met_eta);
    
    m_Tree->Branch("m_delta_phiTauLep",&m_delta_phiTauLep);
    m_Tree->Branch("m_delta_phiTauMet",&m_delta_phiTauMet);
    m_Tree->Branch("m_delta_phiLepMet",&m_delta_phiLepMet);

    m_Tree->Branch("m_mtransTauLep",&m_mtransTauLep);
    m_Tree->Branch("m_mtransTauMet",&m_mtransTauMet);
    m_Tree->Branch("m_mtransLepMet",&m_mtransLepMet);

    m_Tree->Branch("m_mtransTauLep_norm",&m_mtransTauLep_norm);
    m_Tree->Branch("m_mtransTauMet_norm",&m_mtransTauMet_norm);
    m_Tree->Branch("m_mtransLepMet_norm",&m_mtransLepMet_norm);
    
    m_Tree->Branch("m_truth_m_z",&m_truth_m_z);
    m_Tree->Branch("m_m_vis",&m_m_vis);
    m_Tree->Branch("m_m3",&m_m3);
    m_Tree->Branch("m_mWT",&m_mWT);
    m_Tree->Branch("m_mcollinear",&m_mcollinear);
    m_Tree->Branch("m_mtransverse",&m_mtransverse);

    m_Tree->Branch("m_truth_m_z_norm",&m_truth_m_z_norm);
    m_Tree->Branch("m_m3_norm",&m_m3_norm);
    m_Tree->Branch("m_mcollinear_norm",&m_mcollinear_norm);

    m_Tree->Branch("m_sigmaCosDelPhi",&m_sigmaCosDelPhi);
    m_Tree->Branch("m_pT_asymm",&m_pT_asymm);
    m_Tree->Branch("m_ratioMetTauPT",&m_ratioMetTauPT);
    m_Tree->Branch("m_ratioMuonTauPT",&m_ratioMuonTauPT);
    m_Tree->Branch("m_ratioMetMuonPT",&m_ratioMetMuonPT);
    m_Tree->Branch("m_ratioMuonTauM3",&m_ratioMuonTauM3);
    m_Tree->Branch("m_ratioMuonMetM3",&m_ratioMuonMetM3);
    m_Tree->Branch("m_ratioMetTauM3",&m_ratioMetTauM3);
}