// TCB.hh --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: Thu Jun 21 15:11:56 2018 (-0400)
// Last-Updated: Thu Jun 21 16:07:02 2018 (-0400)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 2
// URL: http://wuhongyi.cn 

#ifndef _TCB_H_
#define _TCB_H_

#include "RVersion.h"//版本判断
#include "TBenchmark.h"
#include "TBranch.h"
#include "TChain.h"
#include "TFile.h"
#include "TGraph.h"
#include "TH1.h"
#include "TH2.h"
#include "TRandom.h"
#include "TROOT.h"
#include "TString.h"
#include "TStyle.h"
#include "TSystem.h"
#include "TTree.h"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class TCB
{
public:
  TCB(TString rawfilepath,TString outfilepath,int runnumber);
  virtual ~TCB();

  void Process();
  
private:
  
  void Init();
  void Convert(UShort_t* data,int off = 0);


private:
  Long64_t tcb_trigger_number;//trigger  !raw
  Int_t tcb_trigger_type;// !raw
  Long64_t tcb_ttime;//timestamp  !raw
  UShort_t tcb_trigger_pattern[20]; // !raw


  Long64_t tcb_ttime0;// init time
  Long64_t tcb_ntime;//ns
  Long64_t tcb_time;//s

  TBenchmark *Benchmark;
  Long64_t TotalEnery;
  
  TFile *file_in;
  TTree *tree_in;
  UShort_t TCBData[8196];

  TFile *file_out;
  TTree *tree_out;
};

#endif /* _TCB_H_ */
// 
// TCB.hh ends here
