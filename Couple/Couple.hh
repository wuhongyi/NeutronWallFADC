// Couple.hh --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: Sun Jul  1 19:39:06 2018 (-0400)
// Last-Updated: Mon Jul  2 11:14:50 2018 (-0400)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 6
// URL: http://wuhongyi.cn 

#ifndef _COUPLE_H_
#define _COUPLE_H_

#include "RVersion.h"//版本判断
#include "TApplication.h"
#include "TArrow.h"
#include "TAxis.h"
#include "TBenchmark.h"
#include "TBranch.h"
#include "TBrowser.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TColor.h"
#include "TCutG.h"
#include "TDatime.h"
#include "TError.h"
#include "TF1.h"
#include "TF2.h"
#include "TFile.h"
#include "TFitResult.h"
#include "TFormula.h"
#include "TGaxis.h"
#include "TGraph.h"
#include "TGraph2D.h"
#include "TGraphErrors.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "THStack.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#include "TLine.h"
#include "TList.h"
#include "TLorentzVector.h"
#include "TMarker.h"
#include "TMath.h"
#include "TMatrixD.h"
#include "TMatrixDEigen.h"
#include "TMultiGraph.h"
#include "TNtuple.h"
#include "TObject.h"
#include "TPad.h"
#include "TPaveLabel.h"
#include "TPaveStats.h"
#include "TPaveText.h"
#include "TRandom.h"
#include "TRandom1.h"
#include "TRandom2.h"
#include "TRandom3.h"
#include "TRint.h"
#include "TROOT.h"
#include "TSlider.h"
#include "TSpectrum.h"
#include "TSpectrum2.h"
#include "TStopwatch.h"
#include "TString.h"
#include "TStyle.h"
#include "TSystem.h"
#include "TTimer.h"
#include "TTimeStamp.h"
#include "TTree.h"
#include "TVector3.h"
#include "TVectorD.h"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class Couple
{
public:
  Couple(TString rawfilepath,TString outfilepath,int runnumber,int numl,int chl,int numr,int chr);
  virtual ~Couple();

  void Process();
  
private:
  TFile *f1;
  TFile *f2;
  TTree *t1;
  TTree *t2;
  int ch1,ch2;
  TFile *file_out;
  TTree *tree_out;
  
  TBenchmark *Benchmark;
  UShort_t runid;
  
  Long64_t TotalEnery1;
  UInt_t          tnum1;
  Short_t         cid1;
  UShort_t      ped1;
  Short_t         ADC1[240];
  Long64_t TotalEnery2;
  UInt_t          tnum2;
  Short_t         cid2;
  UShort_t      ped2;
  Short_t         ADC2[240];
  Short_t sample[240];
  Int_t         nevt;
  
  Long64_t entrystatus;
};

#endif /* _COUPLE_H_ */
// 
// Couple.hh ends here
