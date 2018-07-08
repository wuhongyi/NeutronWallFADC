//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Jun 22 12:42:50 2018 by ROOT version 6.13/02
// from TChain t/
//////////////////////////////////////////////////////////

#ifndef DataClass_h
#define DataClass_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>

// Header file for the classes stored in the TTree if any.

class DataClass : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   UInt_t          data_length;
   UShort_t        rid;
   Short_t         ttype;
   UInt_t          tnum;
   Long64_t        ttime;
   Short_t         mid;
   Short_t         cid;
   UInt_t          lnum;
   Long64_t        ltime;
   UShort_t        tpattern;
   UShort_t        ped;
   Short_t         ADC[240];
   Int_t           TDC[60];
   Short_t         sample[240];
   Int_t           nevt;

   // List of branches
   TBranch        *b_data_length;   //!
   TBranch        *b_rid;   //!
   TBranch        *b_ttype;   //!
   TBranch        *b_tnum;   //!
   TBranch        *b_ttime;   //!
   TBranch        *b_mid;   //!
   TBranch        *b_cid;   //!
   TBranch        *b_lnum;   //!
   TBranch        *b_ltime;   //!
   TBranch        *b_tpattern;   //!
   TBranch        *b_ped;   //!
   TBranch        *b_ADC;   //!
   TBranch        *b_TDC;   //!
   TBranch        *b_sample;   //!
   TBranch        *b_nevt;   //!

   DataClass(TTree * /*tree*/ =0) : fChain(0) { }
   virtual ~DataClass() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   ClassDef(DataClass,0);
};

#endif

#ifdef DataClass_cxx
void DataClass::Init(TTree *tree)
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
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("data_length", &data_length, &b_data_length);
   fChain->SetBranchAddress("rid", &rid, &b_rid);
   fChain->SetBranchAddress("ttype", &ttype, &b_ttype);
   fChain->SetBranchAddress("tnum", &tnum, &b_tnum);
   fChain->SetBranchAddress("ttime", &ttime, &b_ttime);
   fChain->SetBranchAddress("mid", &mid, &b_mid);
   fChain->SetBranchAddress("cid", &cid, &b_cid);
   fChain->SetBranchAddress("lnum", &lnum, &b_lnum);
   fChain->SetBranchAddress("ltime", &ltime, &b_ltime);
   fChain->SetBranchAddress("tpattern", &tpattern, &b_tpattern);
   fChain->SetBranchAddress("ped", &ped, &b_ped);
   fChain->SetBranchAddress("ADC", ADC, &b_ADC);
   fChain->SetBranchAddress("TDC", TDC, &b_TDC);
   fChain->SetBranchAddress("sample", sample, &b_sample);
   fChain->SetBranchAddress("nevt", &nevt, &b_nevt);
}

Bool_t DataClass::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef DataClass_cxx
