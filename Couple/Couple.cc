// Couple.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: Sun Jul  1 19:40:59 2018 (-0400)
// Last-Updated: Sun Jul  1 22:25:38 2018 (-0400)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 2
// URL: http://wuhongyi.cn 

#include "Couple.h"

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

Couple::Couple(TString rawfilepath,TString outfilepath,int runnumber,int numl,int chl,int numr,int chr)
{
  ch1 = chl;
  ch2 = chr;
  
  f1 = new TFile(TString::Format("%srun_%04d_fadc_%02d.root",rawfilepath.Data(),runnumber,numl).Data(),"READ");//"RECREATE" "READ"
  if(!f1->IsOpen())
    {
      std::cout<<"Can't open root file"<<std::endl;
    }
  t1 = (TTree*)f1->Get("t");
  t1->SetBranchAddress("tnum",&tnum1);
  t1->SetBranchAddress("cid",&cid1);
  t1->SetBranchAddress("ADC",&ADC1);

  t1->Print();
  






  

  f2 = new TFile(TString::Format("%srun_%04d_fadc_%02d.root",rawfilepath.Data(),runnumber,numr).Data(),"READ");//"RECREATE" "READ"
  if(!f2->IsOpen())
    {
      std::cout<<"Can't open root file"<<std::endl;
    }
  t2 = (TTree*)f2->Get("t");
  t2->SetBranchAddress("tnum",&tnum2);
  t2->SetBranchAddress("cid",&cid2);
  t2->SetBranchAddress("ADC",&ADC2);

  t2->Print();

  
  f1->cd();
  f1->Close();
  
  f2->cd();
  f2->Close();
  
}

Couple::~Couple()
{


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


void Couple::Process()
{


}








// 
// Couple.cc ends here
