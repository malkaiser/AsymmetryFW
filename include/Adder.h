//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Dec 10 15:57:16 2019 by ROOT version 6.18/04
// from TTree NOMINAL/NOMINAL
// found on file: user.sdysch.19616269._000010.LepUniv_ttbar.root
//////////////////////////////////////////////////////////

#ifndef ADDER_H
#define ADDER_H

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <vector>
#include <time.h>
#include <math.h>
#include <memory>
#include "OutputTree.h"

// Header file for the classes stored in the TTree if any.
#include <TLorentzVector.h>

class Adder {
   public :
   void AddTrees(const std::string& treeName);
   void setBranches();
   void ActivateBranches();
   Long64_t LoadTree(Long64_t entry);
   Adder(std::string file1, std::string file2);
   ~Adder();
   private:
   std::unique_ptr<TFile> myFile1;
   std::unique_ptr<TFile> myFile2;
   std::unique_ptr<TFile> m_output_file;
   Int_t myCurrent;
   TTree *myChain;
   // Declare Branches
   #include "DeclareTreeBranches.h"
   #include "DeclareCustomBranches.h"
   // Output trees
   OutputTree m_signalTree{"SIGNAL", "Signal TTree"};
   OutputTree m_backgroundTree{"BG", "Background TTree"};
};

#endif



