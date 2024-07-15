// Header file with common tools used in analysis.
#include <vector>
#include <TLorentzVector.h>
#include <sstream>
#include <string>

// Function to split a string by a delimiter and return a vector of strings.
// Like Python's split function.
std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Run numbers
const int run2015Begin = 276262;
const int run2015End   = 284484;

const int run2016Begin = 297730;
const int run2016End   = 311481;

const int run2017Begin = 323427;
const int run2017End   = 341649;

const int run2018Begin = 341649;
const int run2018End   = 364292;


// Function to calculate delta phi between two angles
// @param phi_1: angle 1
// @param phi_2: angle 2
double del_phi(double phi_1, double phi_2){
    double pi=TMath::Pi();
    double phi_1_norm, phi_2_norm;
    if (phi_1<0.0){
        phi_1_norm=phi_1+2*pi;
    }else {
        phi_1_norm=phi_1;
    }

    if (phi_2<0.0){
        phi_2_norm=phi_2+2*pi;
    }else {
        phi_2_norm=phi_2;
    }
    double delta=std::abs(phi_1_norm-phi_2_norm);
    if (delta>pi){
        delta=2*pi-delta;
        delta=std::abs(delta);
    }

    return delta;
}

// Function to calculate the minimum delta R between a test particle and a container of particles
// @param test_particle: particle to test
// @param bool_vector_container: container of booleans to select particles
// @param jet_container: container of particles to test against
double min_deltaR(TLorentzVector* test_particle, std::vector<UInt_t>& bool_vector_container,const std::vector<TLorentzVector*>& jet_container){

  std::vector<double> delta_Rs{};

  for (size_t index{0};index<jet_container.size();index++){
    if (bool_vector_container[index]!=0){
      delta_Rs.push_back(jet_container[index]->DeltaR(*test_particle));
    }
    else {break;}
  }

  double min_dR=*std::min_element(delta_Rs.begin(),delta_Rs.end());
  return min_dR;
}

// tutorial
float metProjectionClosestLepton(TLorentzVector* met, TLorentzVector* muon, TLorentzVector* tau){
  // Calculate the delta phi between the MET, the muon and the tau
  double deltaPhiMuon = del_phi(muon->Phi(), met->Phi());
  double deltaPhiTau = del_phi(tau->Phi(), met->Phi());
  // Check which one is the closest
  bool muonIsClosest = deltaPhiMuon < deltaPhiTau;
  // Calculate the projection
  float projection = muonIsClosest ? met->Pt() * cos(deltaPhiMuon) : met->Pt() * cos(deltaPhiTau);
  return projection;

}

float sigmaCosDeltaPhi(TLorentzVector* met, TLorentzVector* lepton, TLorentzVector* tau){
  return cos(del_phi(met->Phi(), lepton->Phi())) + cos(del_phi(met->Phi(), tau->Phi()));
}

float visible_mass(TLorentzVector* lepton, TLorentzVector* tau){
  float add_square = ((lepton->E()+tau->E())*(lepton->E()+tau->E()));
  TVector3 vector = lepton->Vect() + tau->Vect();
  float add = sqrt(add_square-vector.Mag2());
  return add;
}

float m3_star(TLorentzVector* met, TLorentzVector* negative_lepton, TLorentzVector* positive_lepton) {
  TLorentzVector met_negative_lepton = met->operator+(*negative_lepton);
  TLorentzVector met_positive_lepton = met->operator+(*positive_lepton);
  TLorentzVector negative_positive_lepton = negative_lepton->operator+(*positive_lepton);
  float mT_combined = sqrt(met_negative_lepton.Mt2() + met_positive_lepton.Mt2() + negative_positive_lepton.Mt2());
  float cosThetaEtaStar = tanh((negative_lepton->Eta()-positive_lepton->Eta())/2);
  float sinThetaEtaStar = sqrt(1-cosThetaEtaStar*cosThetaEtaStar);
  float m3_star = mT_combined/sinThetaEtaStar;
  return m3_star;
}

float W_transverse_mass(TLorentzVector* met, TLorentzVector* lepton){
  float delta_phi = del_phi(lepton->Phi(),met->Phi());
  float transverse_mass = sqrt(2*(lepton->Pt())*(met->Et())*(1-cos(delta_phi)));
  return transverse_mass;
}