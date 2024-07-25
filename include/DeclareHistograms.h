#pragma once

double pi=TMath::Pi();
std::vector<std::string> cutNames{"basic","1prnnscore","3prnnscore","sigmacosdelphi","mvis","m3"};
// std::vector<std::string> cutNames{"basic","1prnnscore","3prnnscore","sigmacosdelphi","mWT","mET"};
std::vector<std::string> notFull{"basic","all"};

// Raw historgrams
TH1F* nJets = new TH1F("nJets","Number of jets",10,0,10);
TH1F* tauEta = new TH1F("tauEta","Tau Eta",60,-3,3);

// Histogram containers
histogramContainer lep_ptContainer{"lep_pt","Lep pT",300,0,300,notFull};
histogramContainer tau_ptContainer{"tau_pt","Tau pT",300,0,300,notFull};
histogramContainer n_bjetsContainer{"n_bjets","Number of b_jets",5,0,5,notFull};
histogramContainer lepisoContainer{"lepiso","Lep Isolation",2,0,2,notFull};
histogramContainer delta_phiContainer{"delta_phi","Delta phi between tau and lep",320,0,3.2,notFull};
// histogramContainer mass_jjContainer{"mass_jj","Invariant mass di_jet system",5000,0,5000,notFull};
histogramContainer ljet0_ptContainer{"ljet0_pt","Light jet0 pT",1000,0,1000,notFull};
histogramContainer ljet1_ptContainer{"ljet1_pt","Light jet1 pT",1000,0,1000,notFull};
// histogramContainer visibleMassContainer{"visibleMass","Visible mass tau-lep",1000,0,1000,notFull};
// histogramContainer lepTransMassContainer{"lepTransMass","Transverse mass lepton",500,0,500,notFull};
histogramContainer rnn_score_1pContainer{"rnn_score_1p","RNN Score 1 prong taus",100,0,1,cutNames,"1prnnscore"};
histogramContainer rnn_score_3pContainer{"rnn_score_3p","RNN Score 3 prong taus",100,0,1,cutNames,"3prnnscore"};
histogramContainer tau_matched_1pContainer{"tau_matched_1p","Tau truth matched 1 prong",2,0,2,notFull};
histogramContainer tau_matched_3pContainer{"tau_matched_3p","Tau truth matched 3 prong",2,0,2,notFull};
// histogramContainer delta_R_lepjetContainer{"delta_R_lepjet","Delta R lep-jet",60,0,6,notFull};
// histogramContainer delta_R_taujetContainer{"delta_R_taujet","Delta R tau-jet",60,0,6,notFull};
histogramContainer lepEtaContainer{"lepEta","Lepton Eta",300,-3,3,notFull};
histogramContainer tauEtaContainer{"tauEta","Tau Eta",300,-3,3,notFull};

histogramContainer tau_rnn_scoreContainer{"tau_rnn_score","RNN Score all taus",100,0,1,notFull}; // rnnscore
histogramContainer sigma_cos_del_phiContainer{"sigma_cos_del_phi","Sum of cos delta phi",400,-2,2,cutNames,"sigmacosdelphi"}; // sigma cos delta phi

// SR

histogramContainer m3_starContainer{"m3_star","Novel selection m3_star",300,0,300,cutNames,"m3"}; // m3_star
histogramContainer m_visContainer{"m_vis", "Visible mass of dilepton",300,0,300,cutNames,"mvis"};
histogramContainer mWTContainer{"mWT","Reconstructed W transverse mass",160,0,160,notFull};
histogramContainer mETContainer{"mET","Reconstructed missing transverse energy",160,0,160,notFull};


// W+Jets
/*
histogramContainer mWTContainer{"mWT","Reconstructed W transverse mass",160,0,160,cutNames,"mWT"}; // mWT
histogramContainer mETContainer{"mET","Reconstructed missing transverse energy",160,0,160,cutNames,"mET"}; // mET
histogramContainer m3_starContainer{"m3_star","Novel selection m3_star",200,0,200,notFull}; //m3_star
histogramContainer m_visContainer{"m_vis", "Visible mass of dilepton",200,0,200,notFull}; // m_vis
*/

// histogramContainer metProjecClosestLepContainer{"projec_closest_lep","MET projection to the closest lepton",100,-200,200,notFull}; // tutorial