#pragma once
#include <TMVA/Reader.h>
#include <memory>
#include <string>
// Class to manage the BDT
class VBFBDT {
  public:
    VBFBDT() = default;
    
    VBFBDT(const std::string& weightsFilePath) {
        m_weightsFilePath = weightsFilePath.c_str();
        m_reader = std::make_unique<TMVA::Reader>("Silent");

        m_reader->AddVariable("m_met_pT",&m_bdt_met_pT);
        m_reader->AddVariable("m_mWT",&m_bdt_mWT);
        m_reader->AddVariable("m_sigmaCosDelPhi",&m_bdt_sigmaCosDelPhi);
        m_reader->AddVariable("m_pT_asymm",&m_bdt_pT_asymm);
        m_reader->AddVariable("m_d_zeta",&m_bdt_d_zeta);
        m_reader->AddVariable("m_ratioMetTauPT",&m_bdt_ratioMetTauPT);
        m_reader->AddVariable("m_etaSeparation",&m_bdt_etaSeparation);
        m_reader->AddVariable("m_pTSumMag",&m_bdt_pTSumMag);
        m_reader->AddVariable("m_pTSumPhi",&m_bdt_pTSumPhi);
        m_reader->AddVariable("m_pTSumEta",&m_bdt_pTSumEta);
        m_reader->BookMVA("VBF_BDT", weightsFilePath.c_str());
    }

    ~VBFBDT() {}

    VBFBDT& operator=(const VBFBDT& other) {
        if (this != &other) {
            m_reader = std::make_unique<TMVA::Reader>("Silent");
            m_weightsFilePath = other.m_weightsFilePath;
            m_bdt_eventNumber = other.m_bdt_eventNumber;
        
            m_bdt_met_pT = other.m_bdt_met_pT;
            m_bdt_mWT = other.m_bdt_mWT;
            m_bdt_sigmaCosDelPhi = other.m_bdt_mWT;
            m_bdt_pT_asymm = other.m_bdt_pT_asymm;
            m_bdt_d_zeta = other.m_bdt_d_zeta;
            m_bdt_ratioMetTauPT = other.m_bdt_ratioMetTauPT;
            m_bdt_etaSeparation = other.m_bdt_etaSeparation;
            m_bdt_pTSumMag = other.m_bdt_pTSumMag;
            m_bdt_pTSumPhi = other.m_bdt_pTSumPhi;
            m_bdt_pTSumEta = other.m_bdt_pTSumEta;

            m_reader->AddVariable("m_met_pT",&m_bdt_met_pT);
            m_reader->AddVariable("m_mWT",&m_bdt_mWT);
            m_reader->AddVariable("m_sigmaCosDelPhi",&m_bdt_sigmaCosDelPhi);
            m_reader->AddVariable("m_pT_asymm",&m_bdt_pT_asymm);
            m_reader->AddVariable("m_d_zeta",&m_bdt_d_zeta);
            m_reader->AddVariable("m_ratioMetTauPT",&m_bdt_ratioMetTauPT);
            m_reader->AddVariable("m_etaSeparation",&m_bdt_etaSeparation);
            m_reader->AddVariable("m_pTSumMag",&m_bdt_pTSumMag);
            m_reader->AddVariable("m_pTSumPhi",&m_bdt_pTSumPhi);
            m_reader->AddVariable("m_pTSumEta",&m_bdt_pTSumEta);

            m_reader->BookMVA("VBF_BDT",  other.m_weightsFilePath);
        }
        return *this;
    }

    void update(float met_pT, float mWT, float sigmaCosDelPhi, float pT_asymm, float d_zeta, float ratioMetTauPT, float etaSeparation, float pTSumMag, float pTSumPhi, float pTSumEta, float eventNumber) {

        m_bdt_eventNumber = eventNumber;
        
        m_bdt_met_pT = met_pT;
        m_bdt_mWT = mWT;
        m_bdt_sigmaCosDelPhi = sigmaCosDelPhi;
        m_bdt_pT_asymm = pT_asymm;
        m_bdt_d_zeta = d_zeta;
        m_bdt_ratioMetTauPT = ratioMetTauPT;
        m_bdt_etaSeparation = etaSeparation;
        m_bdt_pTSumMag = pTSumMag;
        m_bdt_pTSumPhi = pTSumPhi;
        m_bdt_pTSumEta = pTSumEta;
    }

    double evaluate() {
        double bdtScore = m_reader->EvaluateMVA("VBF_BDT");
        reset();
        return bdtScore;
    }

    void reset() {
        m_bdt_eventNumber = 0;

        m_bdt_met_pT = 0;
        m_bdt_mWT = 0;
        m_bdt_sigmaCosDelPhi = 0;
        m_bdt_pT_asymm = 0;
        m_bdt_d_zeta = 0;
        m_bdt_ratioMetTauPT = 0;
        m_bdt_etaSeparation = 0;
        m_bdt_pTSumMag = 0;
        m_bdt_pTSumPhi = 0;
        m_bdt_pTSumEta = 0;
    }

  private:
    std::unique_ptr<TMVA::Reader> m_reader;
    float m_bdt_eventNumber;
    
    float m_bdt_met_pT;
    float m_bdt_mWT;
    float m_bdt_sigmaCosDelPhi;
    float m_bdt_pT_asymm;
    float m_bdt_d_zeta;
    float m_bdt_ratioMetTauPT;
    float m_bdt_etaSeparation;
    float m_bdt_pTSumMag;
    float m_bdt_pTSumPhi;
    float m_bdt_pTSumEta;
    
    const char* m_weightsFilePath;

};