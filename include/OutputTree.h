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
    double m_mcWeight;
    double m_tau_pT;
    double m_lep_pT;
    double m_met_pT;
    double m_event_number;
    double m_m_vis;
    float m_m3;
    float m_mWT;
    float m_m_jtau;
    float m_delta_phiTauLep;
    float m_delta_phiTauMet;
    float m_etaSeparation;
    float m_pTSumEta;
    float m_pTSumPhi;
    float m_pTSumMag;

    // Used
    float m_sigmaCosDelPhi;
    float m_d_zeta;
    float m_pT_asymm;
    float m_ratioMetTauPT;
    float m_ratioMuonTauPT;
    float m_ratioMetMuonPT;
    
    float m_ratioMuonTauM3;
    float m_ratioMuonMetM3;
    float m_ratioMetTauM3;
};