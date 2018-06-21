// FADC.hh --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: Thu Jun 21 16:50:15 2018 (-0400)
// Last-Updated: Thu Jun 21 19:08:49 2018 (-0400)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 4
// URL: http://wuhongyi.cn 

#ifndef _FADC_H_
#define _FADC_H_

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

class FADC
{
public:
  FADC(TString rawfilepath,TString outfilepath,int runnumber, int mod);
  virtual ~FADC();

  void Process();

private:
  void Clear();
  void Convert(UShort_t* data,int off = 0);

private:
  UInt_t        data_length;// !raw
  UShort_t      rid;// !raw  run id
  
  Short_t      ttype;// !raw
  
  UInt_t        tnum;// !raw
  Long64_t     ttime;// !raw

  Short_t      mid;// !raw
  Short_t      cid;// !raw  channel id
  
  UInt_t        lnum;// !raw
  Long64_t     ltime;// !raw

  UShort_t      tpattern;// !raw
  UShort_t      ped;// !raw

  Short_t       ADC[240];// !raw
  Int_t         TDC[60];// !raw

  Short_t sample[240];
  Int_t         nevt;

  
  Short_t        nADC;
  Short_t        nTDC;
  UInt_t        t0;
  

  //Int_t    ADCT[16384];
  Double_t      ADCSum;
  Double_t      ADCPeak;
  Double_t      ADCPart;//partial ADC sum//
  Double_t      ADCTime;
  Double_t      ADCPed;


  TBenchmark *Benchmark;
  Long64_t TotalEnery;
  UShort_t runid;
  TFile *file_in;
  TTree *tree_in;
  UShort_t FADCData[8192];

  TFile *file_out;
  TTree *tree_out;
  
};

#endif /* _FADC_H_ */
// 
// FADC.hh ends here
