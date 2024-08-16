#include "OutputTree.h"

OutputTree::OutputTree(const char* treeName, const char* treeDescription){
    // Creating the tree
    m_Tree = std::make_unique<TTree>(treeName, treeDescription);

    // Setting tree branches

    m_Tree->Branch("m_mcWeight",&m_mcWeight);
    m_Tree->Branch("m_tau_pT", &m_tau_pT);
    m_Tree->Branch("m_lep_pT",&m_lep_pT);
    m_Tree->Branch("m_met_pT",&m_met_pT);
    m_Tree->Branch("m_event_number",&m_event_number);
    m_Tree->Branch("m_m_vis",&m_m_vis);
    m_Tree->Branch("m_m3",&m_m3);
    m_Tree->Branch("m_mWT",&m_mWT);
    m_Tree->Branch("m_m_jtau",&m_m_jtau);
    m_Tree->Branch("m_delta_phiTauLep",&m_delta_phiTauLep);
    m_Tree->Branch("m_delta_phiTauMet",&m_delta_phiTauMet);
    m_Tree->Branch("m_ratioMetTauPT",&m_ratioMetTauPT);
    m_Tree->Branch("m_ratioMuonTauPT",&m_ratioMuonTauPT);
    m_Tree->Branch("m_ratioMetMuonPT",&m_ratioMetMuonPT);
    m_Tree->Branch("m_etaSeparation",&m_etaSeparation);

    m_Tree->Branch("m_sigmaCosDelPhi",&m_sigmaCosDelPhi);
    m_Tree->Branch("m_pT_asymm",&m_pT_asymm);
    m_Tree->Branch("m_d_zeta",&m_d_zeta);
    m_Tree->Branch("m_pTSumMag",&m_pTSumMag);
    m_Tree->Branch("m_pTSumEta",&m_pTSumEta);
    m_Tree->Branch("m_pTSumPhi",&m_pTSumPhi);
    m_Tree->Branch("m_ratioMuonTauM3",&m_ratioMuonTauM3);
    m_Tree->Branch("m_ratioMuonMetM3",&m_ratioMuonMetM3);
    m_Tree->Branch("m_ratioMetTauM3",&m_ratioMetTauM3);
}