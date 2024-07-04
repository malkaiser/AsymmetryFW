// Include the file that lets the program know about the data
#include <vector>
#include <algorithm>
#include "CLoop.h"
#include "OutputTree.h"

double del_phi(double phi_1, double phi_2);
double min_deltaR(TLorentzVector* test_particle, std::vector<UInt_t>& bool_vector_container,const std::vector<TLorentzVector*>& jet_container);
float metProjectionClosestLepton(TLorentzVector* met, TLorentzVector* muon, TLorentzVector* tau); // tutorial
float sigmaCosDeltaPhi(TLorentzVector* met, TLorentzVector* lepton, TLorentzVector* tau);
float W_transverse_mass(TLorentzVector* met, TLorentzVector* lepton);
float m3_star(TLorentzVector* met, TLorentzVector* negative_lepton, TLorentzVector* positive_lepton);


void CLoop::Fill(double weight, int z_sample, const std::string& sampleName) {
  double pi=TMath::Pi();
  //Charges and lepton ID
  bool one_muon{n_electrons == 0 && n_muons == 1 && muon_0_q != 0 && tau_0_q != 0}; // only one muon and one tau
  bool one_electron{n_electrons == 1 && n_muons == 0 && elec_0_q != 0 && tau_0_q != 0}; // only one electron and one tau
  float ql;
  float qtau;
  int no_bjets{n_bjets_MV2c10_FixedCutBEff_85==0};
  if (one_electron) {
    ql = elec_0_q;
    qtau = tau_0_q; 
  }
  if (one_muon) {
    ql = muon_0_q;
    qtau = tau_0_q; 
  }
  bool electron_id=elec_0_id_medium;
  bool muon_id=muon_0_id_medium;

  if (ql!=qtau && one_electron && n_taus_rnn_loose==1 && electron_id && no_bjets){ // electron channel

    // defining selection variables
    double m_vis;
    float sigmaCosDelPhi;
    float m3;
    float mWT;
    sigmaCosDelPhi = sigmaCosDeltaPhi(met_reco_p4, elec_0_p4,tau_0_p4);
    mWT = W_transverse_mass(met_reco_p4,elec_0_p4);
    m_vis=sqrt((tau_0_p4->Dot(*elec_0_p4)));
    if (ql<0) {m3 = m3_star(met_reco_p4, elec_0_p4, tau_0_p4);}
    if (ql>0) {m3 = m3_star(met_reco_p4, tau_0_p4, elec_0_p4);}

    // Cuts vector
    std::vector<int> cuts={0,0,0,0,0}; // tutorial
    // CUTS
    if (tau_0_n_charged_tracks == 3 || tau_0_n_charged_tracks == 1 && tau_0_jet_rnn_score_trans >= 0.40) {cuts[0] = 1;} // 1-pronged tau RNN
    if (tau_0_n_charged_tracks == 1 || (tau_0_n_charged_tracks == 3 && tau_0_jet_rnn_score_trans >= 0.50)) {cuts[1] = 1;} // 3-pronged tau RNN
    if (sigmaCosDelPhi < -0.1) {cuts[2] = 1;}
    if (mWT > 60) {cuts[3] = 1;}
    if (met_reco_p4->E() > 25) {cuts[4] = 1;}

    // SUM OF THE VECTOR STORING IF CUTS PASS OR NOT
    size_t sum{0};
    for(auto &j : cuts){sum=sum+j;}

    std::vector<int> cutsVector{1};
    cutsVector.insert(cutsVector.end(),cuts.begin(),cuts.end());
    bool passedAllCuts = (sum+1==cutsVector.size());
    std::vector<int> notFullCutsVector{1,static_cast<int>(passedAllCuts)};

    // FILL RAW HISTOGRAMS
    if (passedAllCuts){
      nJets->Fill(n_jets,weight);
      tauEta->Fill(tau_0_p4->Eta(),weight);
    }
    
    // FILLING CONATINER HISTOGRAMS
    lepEtaContainer.Fill(tau_0_jet_rnn_score_trans,weight,notFullCutsVector);
    tau_rnn_scoreContainer.Fill(tau_0_jet_rnn_score_trans,weight,notFullCutsVector);
    n_bjetsContainer.Fill(n_bjets_MV2c10_FixedCutBEff_85,weight,notFullCutsVector);
    sigma_cos_del_phiContainer.Fill(sigmaCosDelPhi,weight,cutsVector);
    mWTContainer.Fill(mWT,weight,cutsVector);
    mETContainer.Fill(met_reco_p4->E(),weight,cutsVector);
    lep_ptContainer.Fill(elec_0_p4->Pt(),weight,notFullCutsVector); // electron transverse momentum
    tau_ptContainer.Fill(tau_0_p4->Pt(),weight,notFullCutsVector);
    delta_phiContainer.Fill(del_phi(tau_0_p4->Phi(), elec_0_p4->Phi()),weight,notFullCutsVector);
    ljet0_ptContainer.Fill(ljet_0_p4->Pt(),weight,notFullCutsVector);
    ljet1_ptContainer.Fill(ljet_1_p4->Pt(),weight,notFullCutsVector);
    lepisoContainer.Fill(muon_0_iso_TightTrackOnly_FixedRad,weight,notFullCutsVector);
    m_visContainer.Fill(m_vis,weight,notFullCutsVector);
    m3_starContainer.Fill(m3,weight,notFullCutsVector);
    lepEtaContainer.Fill(elec_0_p4->Eta(),weight,notFullCutsVector); // 
    tauEtaContainer.Fill(tau_0_p4->Eta(),weight,notFullCutsVector);
    if (tau_0_n_charged_tracks==1) {rnn_score_1pContainer.Fill(tau_0_jet_rnn_score_trans,weight,cutsVector);}
    if (tau_0_n_charged_tracks==3) {rnn_score_3pContainer.Fill(tau_0_jet_rnn_score_trans,weight,cutsVector);}

    // Only for MC samplesmuon_0_p4
    if (sampleName.substr(0,4)!="data"){
      if (tau_0_n_charged_tracks==1) tau_matched_1pContainer.Fill(tau_0_truth_isHadTau,weight,notFullCutsVector);
      if (tau_0_n_charged_tracks==3) tau_matched_3pContainer.Fill(tau_0_truth_isHadTau,weight,notFullCutsVector);
    }
  }
}

void CLoop::Style(double lumFactor) {
  nJets->Write();
  tauEta->Write();
}

void CLoop::FillTree(double weight, int z_sample, const std::string& sampleName) {
  double pi=TMath::Pi();
  //Charges and lepton ID
  bool one_muon{n_electrons == 0 && n_muons == 1 && muon_0_q != 0 && tau_0_q != 0}; // only one muon and one tau
  bool one_electron{n_electrons == 1 && n_muons == 0 && elec_0_q != 0 && tau_0_q != 0}; // only one electron and one tau
  float ql;
  float qtau;
  if (one_electron) {
    ql = elec_0_q;
    qtau = tau_0_q; 
  }
  if (one_muon) {
    ql = muon_0_q;
    qtau = tau_0_q; 
  }
  bool electron_id=elec_0_id_medium;
  bool muon_id=muon_0_id_medium;

  if (ql!=qtau && one_electron && n_taus_rnn_loose==1 && electron_id){ // electron channel

    // defining selection variables
    double m_vis;
    float sigmaCosDelPhi;
    float m3;
    float mWT;
    sigmaCosDelPhi = sigmaCosDeltaPhi(met_reco_p4, elec_0_p4,tau_0_p4);
    mWT = W_transverse_mass(met_reco_p4,elec_0_p4);
    m_vis=sqrt(2*(tau_0_p4->Dot(*elec_0_p4)));
    if (ql<0) {m3 = m3_star(met_reco_p4, elec_0_p4, tau_0_p4);}
    if (ql>0) {m3 = m3_star(met_reco_p4, tau_0_p4, elec_0_p4);}

    // Cuts vector
    std::vector<int> cuts={0,0,0,0,0}; // tutorial
    // CUTS
    if (tau_0_n_charged_tracks == 1 && tau_0_jet_rnn_score_trans >= 0.40) {cuts[0] = 1;} // 1-pronged tau RNN
    else if (tau_0_n_charged_tracks == 3 && tau_0_jet_rnn_score_trans >= 0.50) {cuts[0] = 1;} // 3-pronged tau RNN

    if (n_bjets_MV2c10_FixedCutBEff_85 == 0) {cuts[1] = 1;}
    if (sigmaCosDelPhi < -0.1) {cuts[2] = 1;}
    if (mWT > 60) {cuts[3] = 1;}
    if (met_reco_p4->E() > 25) {cuts[4] = 1;}

    // SUM OF THE VECTOR STORING IF CUTS PASS OR NOT
    size_t sum{0};
    for(auto &j : cuts){sum=sum+j;}

    std::vector<int> cutsVector{1};
    cutsVector.insert(cutsVector.end(),cuts.begin(),cuts.end());
    bool passedAllCuts = (sum+1==cutsVector.size());
    
      if (passedAllCuts){
      // FILLING TTree
      // Check if sample is VBF Ztautau
      bool isZtautau = sampleName.find("Ztautau") != std::string::npos;
      if (isZtautau) {
        m_signalTree.m_mcWeight = weight;
        m_signalTree.m_tau_pT = tau_0_p4->Pt();
        // Modified
        m_signalTree.m_n_bjets = n_bjets_MV2c10_FixedCutBEff_85;
        m_signalTree.m_jetRNNScore = tau_0_jet_rnn_score;
        m_signalTree.m_sigmaCosDelPhi = sigmaCosDelPhi;
        m_signalTree.m_m3_star = m3;
        m_signalTree.m_mET = met_reco_p4->E();
        m_signalTree.m_mWT = mWT;
        m_signalTree.m_lep_pT = elec_0_p4->Pt();

        //
        m_signalTree.m_jet0_pT = ljet_0_p4->Pt();
        m_signalTree.m_jet1_pT = ljet_1_p4->Pt();
        m_signalTree.m_met_pT = met_reco_p4->Pt();
        m_signalTree.m_event_number = event_number;
        // Fill tree
        m_signalTree.FillTree();
      } else {
        m_backgroundTree.m_mcWeight = weight;
        m_backgroundTree.m_tau_pT = tau_0_p4->Pt();
        // Modified
        m_backgroundTree.m_n_bjets = n_bjets_MV2c10_FixedCutBEff_85;
        m_backgroundTree.m_jetRNNScore = tau_0_jet_rnn_score;
        m_backgroundTree.m_sigmaCosDelPhi = sigmaCosDelPhi;
        m_backgroundTree.m_m3_star = m3;
        m_backgroundTree.m_mET = met_reco_p4->E();
        m_backgroundTree.m_mWT = mWT;
        m_backgroundTree.m_lep_pT = elec_0_p4->Pt();
        //
        m_backgroundTree.m_lep_pT = elec_0_p4->Pt();
        m_backgroundTree.m_jet0_pT = ljet_0_p4->Pt();
        m_backgroundTree.m_jet1_pT = ljet_1_p4->Pt();
        m_backgroundTree.m_met_pT = met_reco_p4->Pt();
        m_backgroundTree.m_event_number = event_number;
        // Fill tree
        m_backgroundTree.FillTree();
      }
    }
  }
}