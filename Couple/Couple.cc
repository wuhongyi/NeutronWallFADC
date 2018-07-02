// Couple.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: Sun Jul  1 19:40:59 2018 (-0400)
// Last-Updated: Mon Jul  2 13:22:25 2018 (-0400)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 16
// URL: http://wuhongyi.cn 

#include "Couple.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

Couple::Couple(TString rawfilepath,TString outfilepath,int runnumber,int numl,int chl,int numr,int chr)
{
  ch1 = chl;
  ch2 = chr;
  Benchmark = new TBenchmark;
  entrystatus = 0;
  tnum1 = 0;
  tnum2 = 0;
  runid = runnumber;


  
  f1 = new TFile(TString::Format("%srun_%04d_fadc_%02d.root",rawfilepath.Data(),runnumber,numl).Data(),"READ");
  if(!f1->IsOpen())
    {
      std::cout<<"Can't open root file"<<std::endl;
    }
  t1 = (TTree*)f1->Get("t");
  t1->SetBranchAddress("tnum",&tnum1);
  t1->SetBranchAddress("cid",&cid1);
  t1->SetBranchAddress("ped",&ped1);
  t1->SetBranchAddress("ADC",&ADC1);
  TotalEnery1 = t1->GetEntries();
  t1->Print();
  

  f2 = new TFile(TString::Format("%srun_%04d_fadc_%02d.root",rawfilepath.Data(),runnumber,numr).Data(),"READ");
  if(!f2->IsOpen())
    {
      std::cout<<"Can't open root file"<<std::endl;
    }
  t2 = (TTree*)f2->Get("t");
  t2->SetBranchAddress("tnum",&tnum2);
  t2->SetBranchAddress("cid",&cid2);
  t1->SetBranchAddress("ped",&ped2);
  t2->SetBranchAddress("ADC",&ADC2);
  TotalEnery2 = t2->GetEntries();
  t2->Print();


  file_out = new TFile(TString::Format("%srun_%04d_fadc_%02d_%02d_%d_%d.root",outfilepath.Data(),runnumber,numl,numr,ch1,ch2).Data(),"RECREATE");//"RECREATE" "READ"
  if(!file_out->IsOpen())
    {
      std::cout<<"Can't open root file"<<std::endl;
    }
  file_out->cd();
  tree_out = new TTree("t","");
  tree_out->Branch("tnum",&tnum1,"tnum/i");
  // tree_out->Branch("ped1",&ped1,"ped1/s");
  // tree_out->Branch("ped2",&ped2,"ped2/s");
  tree_out->Branch("ADC1",&ADC1,"ADC1[240]/S");
  tree_out->Branch("ADC2",&ADC2,"ADC2[240]/S");
  tree_out->Branch("sample",&sample,"sample[240]/S");
  tree_out->Branch("nevt",&nevt,"nevt/I");

  nevt = 0;
  for (int i = 0; i < 240; ++i)
    {
      sample[i] = i;
    }  
}

Couple::~Couple()
{


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


void Couple::Process()
{
  Benchmark->Start("tree");//计时开始


  for (Long64_t entry1 = 0; entry1 < TotalEnery1; ++entry1)
    {
      if(entry1 % 10000 == 0)
	{
	  std::cout<<"\r"<<"Entry: "<<entry1<<" / "<<TotalEnery1;
	  std::cout<< std::flush;
	}

      f1->cd();
      t1->GetEvent(entry1);
      if(cid1 != ch1) continue;

      
      for (Long64_t entry2 = entrystatus; entry2 < TotalEnery2; ++entry2)
	{
	  f2->cd();
	  t2->GetEvent(entry2);
	  if(cid2 != ch2) continue;

	  if(tnum2 >= tnum1 || entry2 == TotalEnery2-1)
	    {
	      entrystatus = entry2;
	      break;
	    }
	}


      
      if(tnum1 == tnum2)
	{
	  // if(entry1 < 100)
	  // std::cout<<entry1<<"  "<<entrystatus<<"  "<<tnum1<<std::endl;
	  for (int i = 0; i < 240; ++i)
	    {
	      ADC1[i] = ADC1[i] - (4096-ped1);
	      ADC2[i] = ADC2[i] - (4096-ped2);  
	    }
	  
	  file_out->cd();
	  tree_out->Fill();

	  nevt++;
	}

      
      
    }


  
  f1->cd();
  f1->Close();
  
  f2->cd();
  f2->Close();

  file_out->cd();
  tree_out->Write();
  file_out->Close();
  

  std::cout<<std::endl;
  Benchmark->Show("tree");//计时结束并输出时间
}








// 
// Couple.cc ends here
