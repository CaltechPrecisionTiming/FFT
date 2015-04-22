//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Apr 22 09:58:19 2015 by ROOT version 6.03/03
// from TTree T/An example of ROOT tree with a few branches
// found on file: /Users/cmorgoth/Work/data/LaserDataAtCaltech/02282015/CIT_Laser_022015_69.root
//////////////////////////////////////////////////////////

#ifndef T_h
#define T_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1F.h>

// Header file for the classes stored in the TTree if any.

class T {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           event;
   Float_t         peaktime_ch1;
   Float_t         peaktime_ch2;
   Float_t         peaktime_ch3;
   Float_t         peaktime_ch4;
   Float_t         amplitude_ch1;
   Float_t         amplitude_ch2;
   Float_t         amplitude_ch3;
   Float_t         amplitude_ch4;
   Float_t         mean_ch1;
   Float_t         mean_ch2;
   Float_t         mean_ch3;
   Float_t         mean_ch4;
   Float_t         RMS_ch1;
   Float_t         RMS_ch2;
   Float_t         RMS_ch3;
   Float_t         RMS_ch4;
   Float_t         c1[1024];
   Float_t         c2[1024];
   Float_t         c3[1024];
   Float_t         c4[1024];
   Int_t           t1[1024];
   Int_t           t2[1024];
   Int_t           t3[1024];
   Int_t           t4[1024];

   // List of branches
   TBranch        *b_event;   //!
   TBranch        *b_peaktime;   //!
   TBranch        *b_amplitude;   //!
   TBranch        *b_mean;   //!
   TBranch        *b_RMS;   //!
   TBranch        *b_c1;   //!
   TBranch        *b_c2;   //!
   TBranch        *b_c3;   //!
   TBranch        *b_c4;   //!
   TBranch        *b_t1;   //!
   TBranch        *b_t2;   //!
   TBranch        *b_t3;   //!
   TBranch        *b_t4;   //!

   T(TTree *tree=0);
   virtual ~T();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);
  virtual bool     GetHisto( int channel, int entry, TH1F* );
};

#endif

#ifdef T_cxx
T::T(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/Users/cmorgoth/Work/data/LaserDataAtCaltech/02282015/CIT_Laser_022015_69.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/Users/cmorgoth/Work/data/LaserDataAtCaltech/02282015/CIT_Laser_022015_69.root");
      }
      f->GetObject("T",tree);

   }
   Init(tree);
}

T::~T()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t T::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t T::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void T::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("peaktime", &peaktime_ch1, &b_peaktime);
   fChain->SetBranchAddress("amplitude", &amplitude_ch1, &b_amplitude);
   fChain->SetBranchAddress("mean", &mean_ch1, &b_mean);
   fChain->SetBranchAddress("RMS", &RMS_ch1, &b_RMS);
   fChain->SetBranchAddress("c1", c1, &b_c1);
   fChain->SetBranchAddress("c2", c2, &b_c2);
   fChain->SetBranchAddress("c3", c3, &b_c3);
   fChain->SetBranchAddress("c4", c4, &b_c4);
   fChain->SetBranchAddress("t1", t1, &b_t1);
   fChain->SetBranchAddress("t2", t2, &b_t2);
   fChain->SetBranchAddress("t3", t3, &b_t3);
   fChain->SetBranchAddress("t4", t4, &b_t4);
   Notify();
}

Bool_t T::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void T::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t T::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef T_cxx
