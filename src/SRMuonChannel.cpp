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
float mLjetTau(TLorentzVector* ljet, TLorentzVector* tau);
float pTAsymm(TLorentzVector* lepton, TLorentzVector* tau);
float deltaR(TLorentzVector* lepton, TLorentzVector* tau);
float DZeta(TLorentzVector* tau, TLorentzVector* muon, TLorentzVector* met);
float EtaSeparation(TLorentzVector* tau, TLorentzVector* muon);
float myTransverseMass2(TLorentzVector* vector1, TLorentzVector* vector2);

TVector3 VectorialSum(TLorentzVector* tau, TLorentzVector* muon);

bool CLoop::PassPreSelection(const std::string& usr_signCon, const std::string& usr_isoRNN, const std::string& usr_lepCharge, const std::string& usr_prongness){
  double pi=TMath::Pi();
  //Charges and lepton ID
  bool one_muon{n_electrons == 0 && n_muons == 1 && muon_0_q != 0 && tau_0_q != 0}; // only one muon and one tau
  bool one_electron{n_electrons == 1 && n_muons == 0 && elec_0_q != 0 && tau_0_q != 0}; // only one electron and one tau
  bool no_bjets{n_bjets_MV2c10_FixedCutBEff_85==0};
  bool tight_muon{muon_0_iso_TightTrackOnly_FixedRad == 1};
  bool loose_but_not_tight{0};
  if (tau_0_n_charged_tracks == 3 || tau_0_n_charged_tracks == 1 && tau_0_jet_rnn_score_trans >= 0.15 && tau_0_jet_rnn_score_trans <=0.40){
    loose_but_not_tight = 1;
  }
  if (tau_0_n_charged_tracks == 1 || tau_0_n_charged_tracks == 3 && tau_0_jet_rnn_score_trans >= 0.25 && tau_0_jet_rnn_score_trans <= 0.55){
    loose_but_not_tight = 1;
  }
  bool tau_eta{(tau_0_p4->Eta() > 0.1) || (tau_0_p4->Eta() < -0.1) };

  // Charge section
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
  bool signCondition;
  if (usr_signCon =="oppSign")
    signCondition = (ql != qtau);
  if (usr_signCon =="sameSign")
    signCondition = (ql == qtau);

  bool lepCharge;
  if (usr_lepCharge =="positive")
    lepCharge = (ql > 0);
  if (usr_lepCharge =="negative")
    lepCharge = (ql < 0);
  
  bool isoRNN;
  if (usr_isoRNN == "passed")
    isoRNN = (tight_muon);
  if (usr_isoRNN == "failedORLNT")
    isoRNN = (!tight_muon || loose_but_not_tight);

  bool prongness;
  if (usr_prongness == "three")
    prongness = (tau_0_n_charged_tracks == 3);
  if (usr_prongness == "one")
    prongness = (tau_0_n_charged_tracks == 1);
  if (signCondition && isoRNN && lepCharge && prongness && muon_0_p4->Pt() > 27 && one_muon && n_taus==1 && muon_id && no_bjets && tau_eta){
    return true;
  }
  else {
    return false;
  }
}

void CLoop::Fill(double weight, int z_sample, const std::string& sampleName, const std::string& usr_signCon, const std::string& usr_isoRNN, const std::string& usr_lepCharge, const std::string& usr_prongness) {

  double pi=TMath::Pi();
  // Weights section
  if (sampleName.substr(0,4)!="data"){
    weight = weight*muon_0_NOMINAL_MuEffSF_HLT_mu26_ivarmedium_OR_HLT_mu50_QualMedium*muon_0_NOMINAL_MuEffSF_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_QualMedium
            *muon_0_NOMINAL_MuEffSF_Reco_QualMedium*muon_0_NOMINAL_MuEffSF_TTVA*jet_NOMINAL_central_jets_global_effSF_JVT*jet_NOMINAL_central_jets_global_ineffSF_JVT
             *jet_NOMINAL_forward_jets_global_effSF_JVT*jet_NOMINAL_forward_jets_global_ineffSF_JVT
             *jet_NOMINAL_global_effSF_MV2c10_FixedCutBEff_85*jet_NOMINAL_global_ineffSF_MV2c10_FixedCutBEff_85*tau_0_NOMINAL_TauEffSF_reco;
    if (muon_0_iso_TightTrackOnly_FixedRad == 1) {
      weight=weight*muon_0_NOMINAL_MuEffSF_IsoTightTrackOnly_FixedRad;
    }
    else {
      weight = weight*muon_0_NOMINAL_MuEffSF_IsoLoose_FixedRad;
    }
    // tight reweighting
    if ((tau_0_n_charged_tracks == 1 && tau_0_jet_rnn_score_trans >= 0.40) || tau_0_n_charged_tracks == 3 && tau_0_jet_rnn_score_trans >= 0.55) {
      weight = weight*tau_0_NOMINAL_TauEffSF_JetRNNtight;
    }
    else {
      weight=weight*tau_0_NOMINAL_TauEffSF_JetRNNloose;
    }
  }
  bool passedPreSelection{false};
  passedPreSelection = PassPreSelection(usr_signCon, usr_isoRNN, usr_lepCharge, usr_prongness);
//  Opp sign passed iso muonplus 3 prong
//  if (ql==qtau && (!tight_muon || loose_but_not_tight)  && ql < 0 && tau_0_n_charged_tracks == 1 && muon_0_p4->Pt() > 27 && one_muon && n_taus==1 && muon_id && no_bjets && tau_eta){ // muon channel
  if (passedPreSelection){ // muon channel

    // defining selection variables
    float m3;
    float sigmaCosDelPhi = sigmaCosDeltaPhi(met_reco_p4, muon_0_p4,tau_0_p4);
    float mWT = W_transverse_mass(met_reco_p4,muon_0_p4);
    double m_vis = visible_mass(muon_0_p4,tau_0_p4);
    float m_jtau = mLjetTau(ljet_0_p4, tau_0_p4);
    float pT_asymm = pTAsymm(muon_0_p4, tau_0_p4);
    float delta_R_tau_muon = deltaR(muon_0_p4, tau_0_p4);
    float delta_R_tau_met = deltaR(met_reco_p4, tau_0_p4);
    float delta_R_met_muon = deltaR(muon_0_p4, met_reco_p4);
    float d_zeta = DZeta(tau_0_p4, muon_0_p4, met_reco_p4);
    float ratioMetTauPT = met_reco_p4->E()/tau_0_p4->Pt();
    float ratioMetMuonPT = met_reco_p4->E()/muon_0_p4->Pt();
    float ratioMuonTauPT = muon_0_p4->Pt()/tau_0_p4->Pt();

    float etaSeparation = EtaSeparation(tau_0_p4, muon_0_p4);
    TVector3 pT_sum = VectorialSum(tau_0_p4,muon_0_p4);
    if (muon_0_q < 0) {m3 = m3_star(met_reco_p4, muon_0_p4, tau_0_p4);}
    if (muon_0_q > 0) {m3 = m3_star(met_reco_p4, tau_0_p4, muon_0_p4);}
    float ratioMuonTauM3 = sqrt(myTransverseMass2(muon_0_p4, tau_0_p4))/m3;
    float ratioMuonMetM3 = sqrt(myTransverseMass2(muon_0_p4, met_reco_p4))/m3;
    float ratioMetTauM3 = sqrt(myTransverseMass2(met_reco_p4, tau_0_p4))/m3;

    m_zttBDT.update(d_zeta, pT_asymm, sigmaCosDelPhi, ratioMetTauPT, ratioMuonTauPT, ratioMetMuonPT, ratioMuonTauM3, ratioMuonMetM3, ratioMetTauM3, event_number%2147483647);
    double BDT_score = m_zttBDT.evaluate();
    // Cuts vector
    std::vector<int> cuts={0,0,0,0,0,0,0,0,0};
    // CUTS
    // ORDER MATTERS, CHECK CUTNAMES VECTOR IN DECLARE HISTOGRAMS
    if (usr_isoRNN == "failedORLNT") {
      cuts[0] = 1;
      cuts[1] = 1;
    }
    else {
      if (tau_0_n_charged_tracks == 3 || tau_0_n_charged_tracks == 1 && tau_0_jet_rnn_score_trans >= 0.40) {cuts[0] = 1;} // 1-pronged tau RNN
      if (tau_0_n_charged_tracks == 1 || (tau_0_n_charged_tracks == 3 && tau_0_jet_rnn_score_trans >= 0.55)) {cuts[1] = 1;} // 3-pronged tau RNN
    }
    if (sigmaCosDelPhi > -0.05) {cuts[2] = 1;} // Orthogonality condition!
    //if (m_vis < 85) {cuts[3] = 1;}
    //if ((m3 > 60) && (m3 < 110)) {cuts[4] = 1;}

    // if (m_vis < 85) {cuts[3] = 1;}
    if ((m3 > 160) && (m3 < 300)) {cuts[3] = 1;}
    if (mWT < 40) {cuts[4] = 1;}
    if (pT_asymm > 0) {cuts[5] = 1;}
    if (tau_0_p4->Pt() > 60) {cuts[6] = 1;}
    if (muon_0_p4->Pt() > 25) {cuts[7] = 1;}
    if (BDT_score > -0.2) {cuts[8] = 1;}


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

    EtaSeparationContainer.Fill(etaSeparation,weight,notFullCutsVector);

    pTSumMagContainer.Fill(pT_sum.Mag(),weight,notFullCutsVector);
    pTSumEtaContainer.Fill(pT_sum.Eta(),weight,notFullCutsVector);
    pTSumPhiContainer.Fill(pT_sum.Phi(),weight,notFullCutsVector);

    tau_rnn_scoreContainer.Fill(tau_0_jet_rnn_score_trans,weight,notFullCutsVector);
    n_bjetsContainer.Fill(n_bjets_MV2c10_FixedCutBEff_85,weight,notFullCutsVector);
    n_ljetsContainer.Fill(n_jets,weight,notFullCutsVector);
    sigma_cos_del_phiContainer.Fill(sigmaCosDelPhi,weight,cutsVector);
    mWTContainer.Fill(mWT,weight,cutsVector);
    mETContainer.Fill(met_reco_p4->Et(),weight,notFullCutsVector);
    lep_ptContainer.Fill(muon_0_p4->Pt(),weight,cutsVector); // muon transverse momentum
    tau_ptContainer.Fill(tau_0_p4->Pt(),weight,cutsVector);
    delta_phiTauLepContainer.Fill(del_phi(tau_0_p4->Phi(), muon_0_p4->Phi()),weight,notFullCutsVector);
    delta_phiTauMetContainer.Fill(del_phi(tau_0_p4->Phi(), met_reco_p4->Phi()),weight,notFullCutsVector);
    TauLepdeltaRContainer.Fill(delta_R_tau_muon,weight,notFullCutsVector);
    TauMetdeltaRContainer.Fill(delta_R_tau_met,weight,notFullCutsVector);
    MetLepdeltaRContainer.Fill(delta_R_met_muon,weight,notFullCutsVector);
    if (n_jets > 0) {
      ljet0_ptContainer.Fill(ljet_0_p4->Pt(),weight,notFullCutsVector);
      m_ljettauContainer.Fill(m_jtau,weight,notFullCutsVector);
      delta_phiTauJetContainer.Fill(del_phi(ljet_0_p4->Phi(), tau_0_p4->Phi()),weight,notFullCutsVector);
    }
    if (n_jets > 1) {
      ljet1_ptContainer.Fill(ljet_1_p4->Pt(),weight,notFullCutsVector);
      delta_phiJetJetContainer.Fill(del_phi(ljet_0_p4->Phi(), ljet_1_p4->Phi()),weight,notFullCutsVector);
    }
    lepEtaContainer.Fill(muon_0_p4->Eta(),weight,notFullCutsVector); //
    tauEtaContainer.Fill(tau_0_p4->Eta(),weight,notFullCutsVector);
    lepisoContainer.Fill(muon_0_iso_TightTrackOnly_FixedRad,weight,notFullCutsVector);
    m_visContainer.Fill(m_vis,weight,notFullCutsVector);
    m3_starContainer.Fill(m3,weight,cutsVector);
    pTAsymmContainer.Fill(pT_asymm, weight,cutsVector);
    dZetaContainer.Fill(d_zeta, weight,notFullCutsVector);
    ratioMetTauPTContainer.Fill(ratioMetTauPT, weight, notFullCutsVector);
    ZTTBDTContainer.Fill(BDT_score,weight,cutsVector);
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

void CLoop::FillTree(double weight, int z_sample, const std::string& sampleName, const std::string& usr_signCon, const std::string& usr_isoRNN, const std::string& usr_lepCharge, const std::string& usr_prongness) {

  double pi=TMath::Pi();
  // Weights section
  if (sampleName.substr(0,4)!="data"){
    weight = weight*muon_0_NOMINAL_MuEffSF_HLT_mu26_ivarmedium_OR_HLT_mu50_QualMedium*muon_0_NOMINAL_MuEffSF_HLT_mu20_iloose_L1MU15_OR_HLT_mu50_QualMedium
            *muon_0_NOMINAL_MuEffSF_Reco_QualMedium*muon_0_NOMINAL_MuEffSF_TTVA*jet_NOMINAL_central_jets_global_effSF_JVT*jet_NOMINAL_central_jets_global_ineffSF_JVT
             *jet_NOMINAL_forward_jets_global_effSF_JVT*jet_NOMINAL_forward_jets_global_ineffSF_JVT
             *jet_NOMINAL_global_effSF_MV2c10_FixedCutBEff_85*jet_NOMINAL_global_ineffSF_MV2c10_FixedCutBEff_85;
    if (muon_0_iso_TightTrackOnly_FixedRad == 1) {
      weight=weight*muon_0_NOMINAL_MuEffSF_IsoTightTrackOnly_FixedRad;
    }
    else {
      weight = weight*muon_0_NOMINAL_MuEffSF_IsoLoose_FixedRad;
    }
    // tight reweighting
    if ((tau_0_n_charged_tracks == 1 && tau_0_jet_rnn_score_trans >= 0.40) || tau_0_n_charged_tracks == 3 && tau_0_jet_rnn_score_trans >= 0.55) {
      weight = weight*tau_0_NOMINAL_TauEffSF_JetRNNtight;
    }
    else {
      weight=weight*tau_0_NOMINAL_TauEffSF_JetRNNloose;
    }
  }
  bool passedPreSelection{false};
  passedPreSelection = PassPreSelection(usr_signCon, usr_isoRNN, usr_lepCharge, usr_prongness);
//  Opp sign passed iso muonplus 3 prong
//  if (ql==qtau && (!tight_muon || loose_but_not_tight)  && ql < 0 && tau_0_n_charged_tracks == 1 && muon_0_p4->Pt() > 27 && one_muon && n_taus==1 && muon_id && no_bjets && tau_eta){ // muon channel
  if (passedPreSelection){ // muon channel

    float m3;
    float sigmaCosDelPhi = sigmaCosDeltaPhi(met_reco_p4, muon_0_p4,tau_0_p4);
    float mWT = W_transverse_mass(met_reco_p4,muon_0_p4);
    double m_vis = visible_mass(muon_0_p4,tau_0_p4);
    float m_jtau = mLjetTau(ljet_0_p4, tau_0_p4);
    float pT_asymm = pTAsymm(muon_0_p4, tau_0_p4);
    float delta_R_tau_muon = deltaR(muon_0_p4, tau_0_p4);
    float delta_R_tau_met = deltaR(met_reco_p4, tau_0_p4);
    float delta_R_met_muon = deltaR(muon_0_p4, met_reco_p4);
    float d_zeta = DZeta(tau_0_p4, muon_0_p4, met_reco_p4);
    float ratioMetTauPT = met_reco_p4->E()/tau_0_p4->Pt();
    float ratioMetMuonPT = met_reco_p4->E()/muon_0_p4->Pt();
    float ratioMuonTauPT = muon_0_p4->Pt()/tau_0_p4->Pt();
    float etaSeparation = EtaSeparation(tau_0_p4, muon_0_p4);

    TVector3 pT_sum = VectorialSum(tau_0_p4,muon_0_p4);
    if (muon_0_q < 0) {m3 = m3_star(met_reco_p4, muon_0_p4, tau_0_p4);}
    if (muon_0_q > 0) {m3 = m3_star(met_reco_p4, tau_0_p4, muon_0_p4);}

    float ratioMuonTauM3 = sqrt(myTransverseMass2(muon_0_p4, tau_0_p4))/m3;
    float ratioMuonMetM3 = sqrt(myTransverseMass2(muon_0_p4, met_reco_p4))/m3;
    float ratioMetTauM3 = sqrt(myTransverseMass2(met_reco_p4, tau_0_p4))/m3;
    // Cuts vector
    std::vector<int> cuts={0,0,0,0,0,0,0,0};
    // CUTS
    // ORDER MATTERS, CHECK CUTNAMES VECTOR IN DECLARE HISTOGRAMS
    if (usr_isoRNN == "failedORLNT") {
      cuts[0] = 1;
      cuts[1] = 1;
    }
    else {
      if (tau_0_n_charged_tracks == 3 || tau_0_n_charged_tracks == 1 && tau_0_jet_rnn_score_trans >= 0.40) {cuts[0] = 1;} // 1-pronged tau RNN
      if (tau_0_n_charged_tracks == 1 || (tau_0_n_charged_tracks == 3 && tau_0_jet_rnn_score_trans >= 0.55)) {cuts[1] = 1;} // 3-pronged tau RNN
    }
    if (sigmaCosDelPhi > -0.05) {cuts[2] = 1;} // Orthogonality condition!
    //if (m_vis < 85) {cuts[3] = 1;}
    //if ((m3 > 60) && (m3 < 110)) {cuts[4] = 1;}

    // if (m_vis < 85) {cuts[3] = 1;}
    if ((m3 > 160) && (m3 < 300)) {cuts[3] = 1;}
    if (mWT < 40) {cuts[4] = 1;}
    if (pT_asymm > 0) {cuts[5] = 1;}
    if (tau_0_p4->Pt() > 60) {cuts[6] = 1;}
    if (muon_0_p4->Pt() > 25) {cuts[7] = 1;}


    // SUM OF THE VECTOR STORING IF CUTS PASS OR NOT
    size_t sum{0};
    for(auto &j : cuts){sum=sum+j;}

    std::vector<int> cutsVector{1};
    cutsVector.insert(cutsVector.end(),cuts.begin(),cuts.end());
    bool passedAllCuts = (sum+1==cutsVector.size());
    std::vector<int> notFullCutsVector{1,static_cast<int>(passedAllCuts)};

    if (passedAllCuts && (sampleName.substr(0,4)!="data")){
      if (sampleName.substr(0,7)=="Ztautau"){
        m_signalTree.m_mcWeight = weight;
        m_signalTree.m_tau_pT = tau_0_p4->Pt();
        m_signalTree.m_lep_pT = muon_0_p4->Pt();
        m_signalTree.m_met_pT = met_reco_p4->Pt();
        m_signalTree.m_event_number = event_number;
        m_signalTree.m_m_vis = m_vis;
        m_signalTree.m_m3 = m3;
        m_signalTree.m_mWT = mWT;
        m_signalTree.m_m_jtau = m_jtau;
        m_signalTree.m_delta_phiTauLep = del_phi(tau_0_p4->Phi(), muon_0_p4->Phi());
        m_signalTree.m_delta_phiTauMet = del_phi(tau_0_p4->Phi(), met_reco_p4->Phi());
        m_signalTree.m_etaSeparation = etaSeparation;
        m_signalTree.m_pTSumEta = pT_sum.Eta();
        m_signalTree.m_pTSumPhi = pT_sum.Phi();
        m_signalTree.m_pTSumMag = pT_sum.Mag();

        m_signalTree.m_sigmaCosDelPhi = sigmaCosDelPhi;
        m_signalTree.m_pT_asymm = pT_asymm;
        m_signalTree.m_d_zeta = d_zeta;
        m_signalTree.m_ratioMetTauPT = ratioMetTauPT;
        m_signalTree.m_ratioMetMuonPT = ratioMetMuonPT;
        m_signalTree.m_ratioMuonTauPT = ratioMuonTauPT;
        m_signalTree.m_ratioMuonTauM3 = ratioMuonTauM3;
        m_signalTree.m_ratioMuonMetM3 = ratioMuonMetM3;
        m_signalTree.m_ratioMetTauM3 = ratioMetTauM3;

        // Fill tree
        m_signalTree.FillTree();
      }
      else {
        m_backgroundTree.m_mcWeight = weight;
        m_backgroundTree.m_tau_pT = tau_0_p4->Pt();
        m_backgroundTree.m_lep_pT = muon_0_p4->Pt();
        m_backgroundTree.m_met_pT = met_reco_p4->Pt();
        m_backgroundTree.m_event_number = event_number;
        m_backgroundTree.m_m_vis = m_vis;
        m_backgroundTree.m_m3 = m3;
        m_backgroundTree.m_mWT = mWT;
        m_backgroundTree.m_m_jtau = m_jtau;
        m_backgroundTree.m_delta_phiTauLep = del_phi(tau_0_p4->Phi(), muon_0_p4->Phi());
        m_backgroundTree.m_delta_phiTauMet = del_phi(tau_0_p4->Phi(), met_reco_p4->Phi());
        m_backgroundTree.m_etaSeparation = etaSeparation;
        m_backgroundTree.m_pTSumEta = pT_sum.Eta();
        m_backgroundTree.m_pTSumPhi = pT_sum.Phi();
        m_backgroundTree.m_pTSumMag = pT_sum.Mag();


        m_backgroundTree.m_sigmaCosDelPhi = sigmaCosDelPhi;
        m_backgroundTree.m_pT_asymm = pT_asymm;
        m_backgroundTree.m_d_zeta = d_zeta;
        m_backgroundTree.m_ratioMetTauPT = ratioMetTauPT;
        m_backgroundTree.m_ratioMetMuonPT = ratioMetMuonPT;
        m_backgroundTree.m_ratioMuonTauPT = ratioMuonTauPT;

        m_backgroundTree.m_ratioMuonTauM3 = ratioMuonTauM3;
        m_backgroundTree.m_ratioMuonMetM3 = ratioMuonMetM3;
        m_backgroundTree.m_ratioMetTauM3 = ratioMetTauM3;
        // Fill tree
        m_backgroundTree.FillTree();
      }
    }
  }
}