// UserClass.h --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 二 6月  5 03:59:43 2018 (+0800)
// Last-Updated: Sun Jun 24 11:23:07 2018 (-0400)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 28
// URL: http://wuhongyi.cn 

#ifndef _USERCLASS_H_
#define _USERCLASS_H_

#include "DataClass.h"
#include "pkuFFTW.hh"

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
#include "TDirectory.h"
#include "TDirectoryFile.h"
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

// #define NDEBUG
#include <algorithm>
#include <cassert>
#include <cfloat>
#include <climits>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
/* class DataClass; */

class UserClass : public DataClass
{
public:
  UserClass() {}
  virtual ~UserClass() {}
  
  virtual void    Begin(TTree *tree);
  virtual void    SlaveBegin(TTree *tree);
  virtual Bool_t  Process(Long64_t entry);
  virtual void    SlaveTerminate();
  virtual void    Terminate();

  virtual Bool_t  Notify();
  virtual void    Init(TTree *tree);

private:
  Long64_t CountEntry;//用来统计已经处理的enery个数
  Int_t Percent;//用来表示处理进度
  Int_t PercentOld;//用来表示处理进度
  void ProgressBar(Long64_t i,Long64_t total);

  TBenchmark *Benchmark;
  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

public:
  // 用户定义
  int FL,FG;
  
  Short_t baseline;

  int energy,energy1,energy2,energy3,energy4;
  double fft0,fft1,fftsum;
  double fftdata[120];
  double fftdt[120];
  
  Short_t data[256];//max in point 64
  double fastfilter[256];
  Short_t dt[256];
  TFile *rootfile;
  TTree *roottree;
  Short_t rp;//max point bin in raw data
  Short_t peak;//peak
  Short_t peakm;//peak
  double ffpeak;
  int num;
  bool ofr;

  int aven;
  TCutG *cutgup,*cutgdown;
  int countup,countdown;
  double dataupf1[256];
  double datadownf1[256];
  double dataups1[256];
  double datadowns1[256];

  int selectch;

  fftw_complex *in;
  double *out;
  fftw1d *fft1d;
  ClassDef(UserClass,0);
};

#endif /* _USERCLASS_H_ */

// 
// UserClass.h ends here
