// Include the file that lets the program know about the data
#include <vector>
#include <algorithm>
#include "Adder.h"
#include "OutputTree.h"

Adder::Adder(std::string file1, std::string file2):
  myFile1(std::make_unique<TFile>("/gluster/home/htan/AnalysisFW/Results/MuonChannel/NOMINAL/data_2017_0NOMINAL.root", "READ")),
    myFile2(std::make_unique<TFile>("/gluster/home/htan/AnalysisFW/Results/MuonChannel/NOMINAL/data_2017_0NOMINAL.root", "READ")),
      m_output_file(std::make_unique<TFile>("LOVE.root", "RECREATE")) {}

Adder::~Adder() {}

Long64_t Adder::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!myChain) return -5;
   Long64_t centry = myChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (myChain->GetTreeNumber() != myCurrent) {
      myCurrent = myChain->GetTreeNumber();
   }
   return centry;
}

void Adder::AddTrees(const std::string& treeName){
  const char* name = treeName.c_str();
  std::cout << "DEBUG MODE ACTIVATE!" << std::endl;
  myFile1 = std::make_unique<TFile>("/gluster/home/htan/AnalysisFW/Results/MuonChannel/NOMINAL/data_2017_0NOMINAL.root", "READ");
  myFile2 = std::make_unique<TFile>("/gluster/home/htan/AnalysisFW/Results/MuonChannel/NOMINAL/data_2017_0NOMINAL.root", "READ");
  m_output_file = std::make_unique<TFile>("LOVE.root", "RECREATE");
  
  myChain = (TTree*) myFile1->Get(name);
  if (myChain == 0) return;

  Long64_t nentries = myChain->GetEntriesFast();
  std::cout << "Entries: " << nentries << std::endl;

  // if in fast mode only loop over 1% of the entries

  Long64_t nbytes = 0, nb = 0;
  int i{0};
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    std::cout << "Tree loaded!" << std::endl;
    if (ientry < 0) break;
    nb = myChain->GetEntry(jentry,0);
    nbytes += nb;
    ActivateBranches();
    setBranches();
    std::cout << "Activated!" << std::endl;
    m_backgroundTree.FillTree();
    i++;
  }
  std::cout << "ADELAIDE!" << std::endl;
  m_output_file->WriteObject(m_backgroundTree.GetTree(),"BACKGROUND");
  std::cout << "Done!" << std::endl;
}


void Adder::setBranches(){
  myChain->SetBranchAddress("mcWeight", &mcWeight, &b_mcWeight);
  myChain->SetBranchAddress("mjj", &mjj, &b_mjj);
  myChain->SetBranchAddress("deltaPhiLT",&deltaPhiLT, &b_deltaPhiLT);
  myChain->SetBranchAddress("jetRNNScore",&jetRNNScore, &b_jetRNNScore);
  myChain->SetBranchAddress("transverseMassLep",&transverseMassLep, &b_transverseMassLep);
  myChain->SetBranchAddress("massTauLep",&massTauLep, &b_massTauLep);
  myChain->SetBranchAddress("tau_p4", &tau_p4, &b_tau_p4);
  myChain->SetBranchAddress("lep_p4", &lep_p4), &b_lep_p4;
  myChain->SetBranchAddress("jet0_p4", &jet0_p4, &b_jet0_p4);
  myChain->SetBranchAddress("jet1_p4", &jet1_p4, &b_jet1_p4);
  myChain->SetBranchAddress("met_p4", &met_p4, &b_met_p4);
  
  myChain->SetBranchAddress("mWT", &mWT, &b_mWT); // mET
  myChain->SetBranchAddress("mET", &mET, &b_mET); // mWT
  myChain->SetBranchAddress("m3_star", &m3_star, &b_m3_star); // m3_star
  myChain->SetBranchAddress("sigmaCosDelPhi", &sigmaCosDelPhi, &b_m3_star); // novel selection
}

void Adder::ActivateBranches(){
  myChain->SetBranchStatus("mcWeight",1);
  myChain->SetBranchStatus("mjj",1);
  myChain->SetBranchStatus("deltaPhiLT",1);
  myChain->SetBranchStatus("jetRNNScore",1);
  myChain->SetBranchStatus("transverseMassLep",1);
  myChain->SetBranchStatus("massTauLep",1);
  myChain->SetBranchStatus("tau_p4",1);
  myChain->SetBranchStatus("lep_p4",1);
  myChain->SetBranchStatus("jet0_p4",1);
  myChain->SetBranchStatus("jet1_p4",1);
  myChain->SetBranchStatus("met_p4",1);
  
  myChain->SetBranchStatus("mWT",1); // mET
  myChain->SetBranchStatus("mET",1); // mWT
  myChain->SetBranchStatus("m3_star",1); // m3_star
  myChain->SetBranchStatus("sigmaCosDelPhi",1); // novel selection
  myChain->SetBranchStatus("n_bjets",1); // n_bjets
}