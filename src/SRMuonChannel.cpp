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
float visible_mass(TLorentzVector* lepton, TLorentzVector* tau);

void CLoop::Fill(double weight, int z_sample, const std::string& sampleName) {

  double pi=TMath::Pi();
  if (sampleName.substr(0,4)!="data"){
    weight = weight*muon_0_NOMINAL_MuEffSF_HLT_mu26_ivarmedium_OR_HLT_mu50_QualMedium*muon_0_NOMINAL_MuEffSF_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_QualMedium
            *muon_0_NOMINAL_MuEffSF_IsoTightTrackOnly_FixedRad*muon_0_NOMINAL_MuEffSF_Reco_QualMedium*muon_0_NOMINAL_MuEffSF_TTVA;
  }
  //Charges and lepton ID
  bool one_muon{n_electrons == 0 && n_muons == 1 && muon_0_q != 0 && tau_0_q != 0}; // only one muon and one tau
  bool one_electron{n_electrons == 1 && n_muons == 0 && elec_0_q != 0 && tau_0_q != 0}; // only one electron and one tau

  bool no_bjets{n_bjets_MV2c10_FixedCutBEff_85==0};
  bool tight_muon{muon_0_iso_TightTrackOnly_FixedRad == 1};
  bool tau_eta{(tau_0_p4->Eta() > 0.1) || (tau_0_p4->Eta() < -0.1) };
  float ql;
  float qtau;
  if (one_electron) { // assigns charges to electron and tau
    ql = elec_0_q;
    qtau = tau_0_q; 
  }
  if (one_muon) { // assigns charges to muon and tau
    ql = muon_0_q;
    qtau = tau_0_q; 
  }
  bool electron_id=elec_0_id_medium;
  bool muon_id=muon_0_id_medium;
  // Same sign passed iso muonminus 1 prong
  if (ql==qtau && ql < 0 && tight_muon && muon_0_p4->Pt() > 27 && tau_0_n_charged_tracks == 1 && one_muon && n_taus==1 && muon_id && no_bjets && tau_eta){ // muon channel

    // defining selection variables
    double m_vis;
    float sigmaCosDelPhi;
    float m3;
    float mWT;
    sigmaCosDelPhi = sigmaCosDeltaPhi(met_reco_p4, muon_0_p4,tau_0_p4);
    mWT = W_transverse_mass(met_reco_p4,muon_0_p4);
    m_vis = visible_mass(muon_0_p4,tau_0_p4);
    if (ql<0) {m3 = m3_star(met_reco_p4, muon_0_p4, tau_0_p4);}
    if (ql>0) {m3 = m3_star(met_reco_p4, tau_0_p4, muon_0_p4);}

    // Cuts vector
    std::vector<int> cuts={0,0,0,0,0};
    // CUTS
    if (tau_0_n_charged_tracks == 3 || tau_0_n_charged_tracks == 1 && tau_0_jet_rnn_score_trans >= 0.40) {cuts[0] = 1;} // 1-pronged tau RNN
    if (tau_0_n_charged_tracks == 1 || (tau_0_n_charged_tracks == 3 && tau_0_jet_rnn_score_trans >= 0.50)) {cuts[1] = 1;} // 3-pronged tau RNN
    if (sigmaCosDelPhi > -0.1) {cuts[2] = 1;} // Orthogonality condition!
    if (m_vis < 85) {cuts[3] = 1;}
    if ((m3 > 60) && (m3 < 110)) {cuts[4] = 1;}


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
    tau_rnn_scoreContainer.Fill(tau_0_jet_rnn_score_trans,weight,notFullCutsVector);
    n_bjetsContainer.Fill(n_bjets_MV2c10_FixedCutBEff_85,weight,notFullCutsVector);
    sigma_cos_del_phiContainer.Fill(sigmaCosDelPhi,weight,cutsVector);
    mWTContainer.Fill(mWT,weight,notFullCutsVector);
    mETContainer.Fill(met_reco_p4->Et(),weight,notFullCutsVector);
    lep_ptContainer.Fill(muon_0_p4->Pt(),weight,notFullCutsVector); // muon transverse momentum
    tau_ptContainer.Fill(tau_0_p4->Pt(),weight,notFullCutsVector);
    delta_phiContainer.Fill(del_phi(tau_0_p4->Phi(), muon_0_p4->Phi()),weight,notFullCutsVector);
    ljet0_ptContainer.Fill(ljet_0_p4->Pt(),weight,notFullCutsVector);
    ljet1_ptContainer.Fill(ljet_1_p4->Pt(),weight,notFullCutsVector);
    lepEtaContainer.Fill(muon_0_p4->Eta(),weight,notFullCutsVector); //
    tauEtaContainer.Fill(tau_0_p4->Eta(),weight,notFullCutsVector);
    lepisoContainer.Fill(muon_0_iso_TightTrackOnly_FixedRad,weight,notFullCutsVector);
    m_visContainer.Fill(m_vis,weight,cutsVector);
    m3_starContainer.Fill(m3,weight,cutsVector);
    if (tau_0_n_charged_tracks==1) {rnn_score_1pContainer.Fill(tau_0_jet_rnn_score_trans,weight,cutsVector);}
    if (tau_0_n_charged_tracks==3) {rnn_score_3pContainer.Fill(tau_0_jet_rnn_score_trans,weight,cutsVector);}

    // Only for MC samples
    if (sampleName.substr(0,4)!="data"){
      if (tau_0_n_charged_tracks==1) {tau_matched_1pContainer.Fill(tau_0_truth_isHadTau,weight,notFullCutsVector);}
      if (tau_0_n_charged_tracks==3) {tau_matched_3pContainer.Fill(tau_0_truth_isHadTau,weight,notFullCutsVector);}
    }
  }
}

void CLoop::Style(double lumFactor) {
  nJets->Write();
  tauEta->Write();
}

void CLoop::FillTree(double weight, int z_sample, const std::string& sampleName) {

  double pi=TMath::Pi();
  if (sampleName.substr(0,4)!="data"){
    weight = weight*muon_0_NOMINAL_MuEffSF_HLT_mu26_ivarmedium_OR_HLT_mu50_QualMedium*muon_0_NOMINAL_MuEffSF_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_QualMedium
            *muon_0_NOMINAL_MuEffSF_IsoTightTrackOnly_FixedRad*muon_0_NOMINAL_MuEffSF_Reco_QualMedium*muon_0_NOMINAL_MuEffSF_TTVA;
  }
  //Charges and lepton ID
  bool one_muon{n_electrons == 0 && n_muons == 1 && muon_0_q != 0 && tau_0_q != 0}; // only one muon and one tau
  bool one_electron{n_electrons == 1 && n_muons == 0 && elec_0_q != 0 && tau_0_q != 0}; // only one electron and one tau

  bool no_bjets{n_bjets_MV2c10_FixedCutBEff_85==0};
  bool tight_muon{muon_0_iso_TightTrackOnly_FixedRad == 1};
  bool tau_eta{(tau_0_p4->Eta() > 0.1) || (tau_0_p4->Eta() < -0.1) };
  float ql;
  float qtau;
  if (one_electron) { // assigns charges to electron and tau
    ql = elec_0_q;
    qtau = tau_0_q; 
  }
  if (one_muon) { // assigns charges to muon and tau
    ql = muon_0_q;
    qtau = tau_0_q; 
  }
  bool electron_id=elec_0_id_medium;
  bool muon_id=muon_0_id_medium;

  if (ql!=qtau && one_muon && n_taus==1 && muon_id && no_bjets && tight_muon && tau_eta){ // muon channel

    // defining selection variables
    double m_vis;
    float sigmaCosDelPhi;
    float m3;
    float mWT;
    sigmaCosDelPhi = sigmaCosDeltaPhi(met_reco_p4, muon_0_p4,tau_0_p4);
    mWT = W_transverse_mass(met_reco_p4,muon_0_p4);
    m_vis = visible_mass(muon_0_p4,tau_0_p4);
    if (ql<0) {m3 = m3_star(met_reco_p4, muon_0_p4, tau_0_p4);}
    if (ql>0) {m3 = m3_star(met_reco_p4, tau_0_p4, muon_0_p4);}

    // Cuts vector
    std::vector<int> cuts={0,0,0,0,0};
    // CUTS
    if (tau_0_n_charged_tracks == 3 || tau_0_n_charged_tracks == 1 && tau_0_jet_rnn_score_trans >= 0.40) {cuts[0] = 1;} // 1-pronged tau RNN
    if (tau_0_n_charged_tracks == 1 || (tau_0_n_charged_tracks == 3 && tau_0_jet_rnn_score_trans >= 0.50)) {cuts[1] = 1;} // 3-pronged tau RNN
    if (sigmaCosDelPhi > -0.1) {cuts[2] = 1;} // Orthogonality condition!
    if (m_vis < 85) {cuts[3] = 1;}
    if ((m3 > 60) && (m3 < 110)) {cuts[4] = 1;}


    // SUM OF THE VECTOR STORING IF CUTS PASS OR NOT
    size_t sum{0};
    for(auto &j : cuts){sum=sum+j;}

    std::vector<int> cutsVector{1};
    cutsVector.insert(cutsVector.end(),cuts.begin(),cuts.end());
    bool passedAllCuts = (sum+1==cutsVector.size());
    std::vector<int> notFullCutsVector{1,static_cast<int>(passedAllCuts)};

    if (passedAllCuts){
        m_backgroundTree.m_mcWeight = weight;
        m_backgroundTree.m_tau_pT = tau_0_p4->Pt();
        // Modified
        m_backgroundTree.m_n_bjets = n_bjets_MV2c10_FixedCutBEff_85;
        m_backgroundTree.m_jetRNNScore = tau_0_jet_rnn_score;
        m_backgroundTree.m_sigmaCosDelPhi = sigmaCosDelPhi;
        m_backgroundTree.m_m3_star = m3;
        m_backgroundTree.m_mET = met_reco_p4->E();
        m_backgroundTree.m_mWT = mWT;
        m_backgroundTree.m_lep_pT = muon_0_p4->Pt();
        m_backgroundTree.m_tauProngs = tau_0_n_charged_tracks;
        if (tau_0_n_charged_tracks==1) {m_backgroundTree.m_tau1ProngScore = tau_0_jet_rnn_score_trans;}
        if (tau_0_n_charged_tracks==3) {m_backgroundTree.m_tau3ProngScore = tau_0_jet_rnn_score_trans;}
        m_backgroundTree.m_mVis = m_vis;
        m_backgroundTree.m_m3star = m3;
        //
        m_backgroundTree.m_jet0_pT = ljet_0_p4->Pt();
        m_backgroundTree.m_jet1_pT = ljet_1_p4->Pt();
        m_backgroundTree.m_met_pT = met_reco_p4->Pt();
        m_backgroundTree.m_event_number = event_number;
        // Fill tree
        m_backgroundTree.FillTree();
    }
  }
}