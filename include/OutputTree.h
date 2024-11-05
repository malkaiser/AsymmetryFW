#pragma once
#include <TTree.h>
#include <memory>

class OutputTree {
    public:
    OutputTree() = default;

    OutputTree(const char* treeName, const char* treeDescription);

    ~OutputTree(){};

    void FillTree(){
        m_Tree->Fill();
    }

    const TTree* GetTree() const {
        return m_Tree.get();
    }

    private:
    std::unique_ptr<TTree> m_Tree = nullptr;
    public: // To be able to access this members directly and assign in FillTree.
    float m_event_number;
    float m_mcWeight;
    float m_n_jets;

    // pTs
    float m_tau_pT;
    float m_lep_pT;
    float m_met_pT;
    float m_ljet_0_pT;
    float m_ljet_1_pT;
    float m_pT_sum;
    float m_tau_nu_pT;
    float m_lep_nu_pT;

    // pT Norms
    float m_tau_pT_norm;
    float m_lep_pT_norm;
    float m_met_pT_norm;

    // etas
    float m_tau_eta;
    float m_lep_eta;
    float m_met_eta;

    // delta_phis
    float m_delta_phiTauLep;
    float m_delta_phiLepMet;
    float m_delta_phiTauMet;

    // transverse masses
    float m_mtransTauLep;
    float m_mtransTauMet;
    float m_mtransLepMet;

    // transverse masses norms
    float m_mtransTauLep_norm;
    float m_mtransTauMet_norm;
    float m_mtransLepMet_norm;

    // Mass estimators
    float m_truth_m_z;
    float m_m_vis;
    float m_m3;
    float m_mWT;
    float m_mcollinear;
    float m_mtransverse;

    // Mass estimators norm
    float m_truth_m_z_norm;
    float m_m3_norm;
    float m_mcollinear_norm;

    // Classifier
    float m_sigmaCosDelPhi;
    float m_pT_asymm;
    float m_ratioMetTauPT;
    float m_ratioMuonTauPT;
    float m_ratioMetMuonPT;
    
    float m_ratioMuonTauM3;
    float m_ratioMuonMetM3;
    float m_ratioMetTauM3;
};