// UserClass.C --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 二 6月  5 04:03:08 2018 (+0800)
// Last-Updated: Fri Jun 22 20:24:38 2018 (-0400)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 36
// URL: http://wuhongyi.cn 

#define  UserClass_cxx
#include "UserClass.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void UserClass::Init(TTree *tree)
{
  DataClass::Init(tree);
}

Bool_t UserClass::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

  
   return kTRUE;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void UserClass::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
   Benchmark = new TBenchmark;
   Benchmark->Start("tree");//计时开始
   CountEntry = 0;
   Percent = 0;
   PercentOld = 100;

   std::cout<<"Option: "<<option<<std::endl;
   // ----------------------------------------

   FL = 4;
   FG = 0;

   
   rootfile = new TFile("output.root","RECREATE");//"RECREATE" "READ"
   if(!rootfile->IsOpen())
     {
       std::cout<<"Can't open root file"<<std::endl;
     }
   
   roottree = new TTree("tree","Hongyi Wu Data");
   roottree->Branch("rp",&rp,"rp/S");
   roottree->Branch("peak",&peak,"peak/S");
   roottree->Branch("ffpeak",&ffpeak,"ffpeak/D");
   roottree->Branch("data",&data,"data[256]/S");
   roottree->Branch("dt",&dt,"dt[256]/S");
   roottree->Branch("fastfilter",&fastfilter,"fastfilter[256]/D");
   roottree->Branch("ofr",&ofr,"ofr/O");
   roottree->Branch("num",&num,"num/I");
   roottree->Branch("energy",&energy,"energy/I");
   roottree->Branch("energy1",&energy1,"energy1/I");
   roottree->Branch("energy2",&energy2,"energy2/I");
   roottree->Branch("energy3",&energy3,"energy3/I");
   
   

   for (int i = 0; i < 256; ++i)
     {
       dt[i] = i;
     }
   num = 0;
}

void UserClass::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

Bool_t UserClass::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either DataClass::GetEntry() or TBranch::GetEntry()
   // to read either all or the required parts of the data. When processing
   // keyed objects with PROOF, the object is already loaded and is available
   // via the fObject pointer.
   //
   // This function should contain the "body" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.

  CountEntry++;//自加，每执行一次自加一
  ProgressBar(CountEntry,fChain->GetEntries());
  // ----------------------------------------

  b_cid->GetEntry(entry);
  if(cid != 4) return kTRUE;

  b_ped->GetEntry(entry);
  b_ADC->GetEntry(entry);

  baseline = 4096-ped;
  rp = -1;
  peak = -4096;
  ofr = false;
  for (int i = 0; i < 240; ++i)
    {
      if(ADC[i] > 4090) ofr = true;
      ADC[i] -= baseline;
      if(ADC[i] > peak)
	{
	  rp = i;
	  peak = ADC[i];
	}
    }

  for (int i = 0; i < 256; ++i)
    {
      data[i] = 0;
    }

  for (int i = rp; i < 240; ++i)
    {
      if(64+i-rp >= 256) break;
      data[64+i-rp] = ADC[i];
    }
  for (int i = rp-1; i >= 0; --i)
    {
      if(64+i-rp < 0) break;
      data[64+i-rp] = ADC[i];
    }

  int offset = 2*FL+FG-1;
  ffpeak = -1000;
  for (int x = offset; x < 256; ++x)
    {
      fastfilter[x] = 0;
      for (int y = (x-offset); y < (x-offset+FL); ++y)
	{
	  fastfilter[x] -= data[y];
	}
      for (int y = (x-offset+FL+FG); y < (x-offset+2*FL+FG); ++y)
	{
	  fastfilter[x] += data[y];
	}
      fastfilter[x] /= FL;
      if(fastfilter[x] > ffpeak) ffpeak = fastfilter[x];
    }

  for (int x = 0; x < offset; ++x)
    {
      fastfilter[x] = fastfilter[offset];
    }
  
  energy = 0;
  energy1 = 0;
  energy2 = 0;
  energy3 = 0;
  
  for (int i = 0; i < 240; ++i)
    {
      energy += ADC[i];
    }

  for (int i = 50; i < 70; ++i)
    {
      energy1 += ADC[i];
    }

  for (int i = 50; i < 90; ++i)
    {
      energy2 += ADC[i];
    }

  for (int i = 50; i < 110; ++i)
    {
      energy3 += ADC[i];
    }
  

  roottree->Fill();//loop
  num++;
   return kTRUE;
}

void UserClass::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void UserClass::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

  rootfile->cd();
  roottree->Write();
   rootfile->Close();
   // ----------------------------------------
  std::cout<<std::endl;
  Benchmark->Show("tree");//计时结束并输出时间
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void UserClass::ProgressBar(Long64_t i,Long64_t total)
{
  Percent = (int)(100.0*(double)i/(double)total);
  if(Percent != PercentOld)
    {
      std::cout<<"\r"<<Percent<<"% [";

      int temp = (int)((double)Percent/(double)100 * 50);
      for (int i = 0; i < temp-1; ++i)
	{
	  std::cout << "=";
	}
      std::cout<<">";
      for (int j = 0; j < 50-temp-1; ++j)
	{
	  std::cout<<" ";
	}
      std::cout<<"]  ";
    }
  else
    {
      std::cout << "\r" ;
    }
  std::cout << std::flush;
  PercentOld = Percent;
}


// 
// UserClass.C ends here
