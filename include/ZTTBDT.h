#pragma once
#include <TMVA/Reader.h>
#include <memory>
#include <string>
// Class to manage the BDT
class ZTTBDT {
  public:
    ZTTBDT() = default;
    
    ZTTBDT(const std::string& weightsFilePath) {
        m_weightsFilePath = weightsFilePath.c_str();
        m_reader = std::make_unique<TMVA::Reader>("Silent");

        m_reader->AddVariable("m_d_zeta",&m_bdt_d_zeta);
        m_reader->AddVariable("m_pT_asymm",&m_bdt_pT_asymm);
        m_reader->AddVariable("m_sigmaCosDelPhi",&m_bdt_sigmaCosDelPhi);
        m_reader->AddVariable("m_ratioMetTauPT",&m_bdt_ratioMetTauPT);
        m_reader->AddVariable("m_ratioMuonTauPT",&m_bdt_ratioMuonTauPT);
        m_reader->AddVariable("m_ratioMetMuonPT",&m_bdt_ratioMetMuonPT);
        m_reader->AddVariable("m_ratioMuonTauM3",&m_bdt_ratioMuonTauM3);
        m_reader->AddVariable("m_ratioMuonMetM3",&m_bdt_ratioMuonMetM3);
        m_reader->AddVariable("m_ratioMetTauM3",&m_bdt_ratioMetTauM3);
        m_reader->AddSpectator("m_event_number",&m_bdt_event_number);
        
        m_reader->BookMVA("VBF_BDT", weightsFilePath.c_str());
    }

    ~ZTTBDT() {}

    ZTTBDT& operator=(const ZTTBDT& other) {
        if (this != &other) {
            m_reader = std::make_unique<TMVA::Reader>("Silent");
            m_weightsFilePath = other.m_weightsFilePath;
            m_bdt_event_number = other.m_bdt_event_number;
        
            m_bdt_d_zeta = other.m_bdt_d_zeta;
            m_bdt_pT_asymm = other.m_bdt_pT_asymm;
            m_bdt_sigmaCosDelPhi = other.m_bdt_sigmaCosDelPhi;
            m_bdt_ratioMetTauPT = other.m_bdt_ratioMetTauPT;
            m_bdt_ratioMuonTauPT = other.m_bdt_ratioMuonTauPT;
            m_bdt_ratioMetMuonPT = other.m_bdt_ratioMetMuonPT;
            m_bdt_ratioMuonTauM3 = other.m_bdt_ratioMuonTauM3;
            m_bdt_ratioMuonMetM3 = other.m_bdt_ratioMuonMetM3;
            m_bdt_ratioMetTauM3 = other.m_bdt_ratioMetTauM3;

            m_reader->AddVariable("m_d_zeta",&m_bdt_d_zeta);
            m_reader->AddVariable("m_pT_asymm",&m_bdt_pT_asymm);
            m_reader->AddVariable("m_sigmaCosDelPhi",&m_bdt_sigmaCosDelPhi);
            m_reader->AddVariable("m_ratioMetTauPT",&m_bdt_ratioMetTauPT);
            m_reader->AddVariable("m_ratioMuonTauPT",&m_bdt_ratioMuonTauPT);
            m_reader->AddVariable("m_ratioMetMuonPT",&m_bdt_ratioMetMuonPT);
            m_reader->AddVariable("m_ratioMuonTauM3",&m_bdt_ratioMuonTauM3);
            m_reader->AddVariable("m_ratioMuonMetM3",&m_bdt_ratioMuonMetM3);
            m_reader->AddVariable("m_ratioMetTauM3",&m_bdt_ratioMetTauM3);
            m_reader->AddSpectator("m_event_number",&m_bdt_event_number);
        
            m_reader->BookMVA("ZTT_BDT",  other.m_weightsFilePath);
        }
        return *this;
    }

    void update(float d_zeta, float pT_asymm, float sigmaCosDelPhi, float ratioMetTauPT, float ratioMuonTauPT, float ratioMetMuonPT, float ratioMuonTauM3, float ratioMuonMetM3, float ratioMetTauM3, float eventNumber) {

        m_bdt_d_zeta = d_zeta;
        m_bdt_pT_asymm = pT_asymm;
        m_bdt_sigmaCosDelPhi = sigmaCosDelPhi;
        m_bdt_ratioMetTauPT = ratioMetTauPT;
        m_bdt_ratioMuonTauPT = ratioMetMuonPT;
        m_bdt_ratioMetMuonPT = ratioMetMuonPT;

        m_bdt_ratioMuonTauM3 = ratioMuonTauM3;
        m_bdt_ratioMuonMetM3 = ratioMuonMetM3;
        m_bdt_ratioMetTauM3 = ratioMetTauM3;
    
        m_bdt_event_number = eventNumber;
    }

    double evaluate() {
        double bdtScore = m_reader->EvaluateMVA("ZTT_BDT");
        reset();
        return bdtScore;
    }

    void reset() {
        m_bdt_event_number = 0;

        m_bdt_d_zeta = 0;
        m_bdt_pT_asymm = 0;
        m_bdt_sigmaCosDelPhi = 0;
        m_bdt_ratioMetTauPT = 0;
        m_bdt_ratioMuonTauPT = 0;
        m_bdt_ratioMetMuonPT = 0;
        m_bdt_ratioMuonTauM3 = 0;
        m_bdt_ratioMuonMetM3 = 0;
        m_bdt_ratioMetTauM3 = 0;
    }

  private:
    std::unique_ptr<TMVA::Reader> m_reader;
    float m_bdt_event_number;
    float m_bdt_d_zeta;
    float m_bdt_pT_asymm;
    float m_bdt_sigmaCosDelPhi;
    float m_bdt_ratioMetTauPT;
    float m_bdt_ratioMuonTauPT;
    float m_bdt_ratioMetMuonPT;

    float m_bdt_ratioMuonTauM3;
    float m_bdt_ratioMuonMetM3;
    float m_bdt_ratioMetTauM3;

    const char* m_weightsFilePath;

};