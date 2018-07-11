// UserClass.C --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 二 6月  5 04:03:08 2018 (+0800)
// Last-Updated: Tue Jul 10 21:28:00 2018 (-0400)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 88
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

   selectch = 3;
   
   cutgup = new TCutG("CUTGUP",4);
   // cutgup->SetPoint(0,4595.93,0.921618);
   // cutgup->SetPoint(1,4608.97,0.865687);
   // cutgup->SetPoint(2,7548.23,0.856582);
   // cutgup->SetPoint(3,7528.68,0.906009);
   // cutgup->SetPoint(0,2569.08,0.921457);
   // cutgup->SetPoint(1,2556.05,0.877176);
   // cutgup->SetPoint(2,4146.25,0.872115);
   // cutgup->SetPoint(3,4146.25,0.903745);
   // cutgup->SetPoint(0,16170.4,0.874559);
   // cutgup->SetPoint(1,16199.1,0.839632);
   // cutgup->SetPoint(2,27616.2,0.840368);
   // cutgup->SetPoint(3,27444.1,0.876765);
   cutgup->SetPoint(0,2229.22,0.966144);
   cutgup->SetPoint(1,2242.23,0.928947);
   cutgup->SetPoint(2,2853.62,0.916549);
   cutgup->SetPoint(3,2860.13,0.963664);

   
   cutgdown = new TCutG("CUTGDOWN",4);
   // cutgdown->SetPoint(0,5215.07,0.826665);
   // cutgdown->SetPoint(1,8102.19,0.818861);
   // cutgdown->SetPoint(2,8102.19,0.786342);
   // cutgdown->SetPoint(3,5254.17,0.770734);
   // cutgdown->SetPoint(0,2705.94,0.805061);
   // cutgdown->SetPoint(1,2751.56,0.751923);
   // cutgdown->SetPoint(2,4446.04,0.76584);
   // cutgdown->SetPoint(3,4426.49,0.801265);
   // cutgdown->SetPoint(0,16887.6,0.794044);
   // cutgdown->SetPoint(1,16916.2,0.766103);
   // cutgdown->SetPoint(2,25522.1,0.763529);
   // cutgdown->SetPoint(3,25263.9,0.802132);
   cutgdown->SetPoint(0,2294.26,0.757844);
   cutgdown->SetPoint(1,2957.69,0.760324);
   cutgdown->SetPoint(2,3003.22,0.713209);
   cutgdown->SetPoint(3,2326.79,0.69833);
   
   countup = 0;
   countdown = 0;

   aven = 1000;
   rootfile = new TFile("output.root","RECREATE");//"RECREATE" "READ"
   if(!rootfile->IsOpen())
     {
       std::cout<<"Can't open root file"<<std::endl;
     }
   
   roottree = new TTree("tree","Hongyi Wu Data");
   roottree->Branch("tnum",&tnum,"tnum/i");
   roottree->Branch("rp",&rp,"rp/S");
   roottree->Branch("peak",&peak,"peak/S");
   roottree->Branch("peakm",&peakm,"peakm/S");
   roottree->Branch("ffpeak",&ffpeak,"ffpeak/D");
   roottree->Branch("data",&data,"data[256]/S");
   roottree->Branch("dt",&dt,"dt[256]/S");
   roottree->Branch("fastfilter",&fastfilter,"fastfilter[256]/D");
   roottree->Branch("ADC",&ADC,"ADC[240]/S");
   roottree->Branch("sample",&sample,"sample[240]/S");
   roottree->Branch("ofr",&ofr,"ofr/O");
   roottree->Branch("num",&num,"num/I");
   roottree->Branch("energy",&energy,"energy/I");
   roottree->Branch("energy1",&energy1,"energy1/I");
   roottree->Branch("energy2",&energy2,"energy2/I");
   roottree->Branch("energy3",&energy3,"energy3/I");
   roottree->Branch("energy4",&energy4,"energy4/I");
   // roottree->Branch("fft0",&fft0,"fft0/D");
   // roottree->Branch("fft1",&fft1,"fft1/D");
   // roottree->Branch("fftsum",&fftsum,"fftsum/D");
   // roottree->Branch("fftdata",&fftdata,"fftdata[120]/D");
   // roottree->Branch("fftdt",&fftdt,"fftdt[120]/D");

   for (int i = 0; i < 120; ++i)
     {
       fftdt[i] = i;
     }
   
   for (int i = 0; i < 256; ++i)
     {
       dt[i] = i;
       dataupf1[i] = 0;
       datadownf1[i] = 0;
       dataups1[i] = 0;
       datadowns1[i] = 0;
     }
   num = 0;

   in = Malloc_fftw_complex(240);
   out = Malloc_fftw_real(240);
   fft1d = new fftw1d(240,-1);
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
  if(cid != selectch) return kTRUE;

  b_ped->GetEntry(entry);
  b_ADC->GetEntry(entry);
  b_sample->GetEntry(entry);
  b_tnum->GetEntry(entry);
  
  baseline = 4096-ped;
  rp = -1;
  peak = -4096;
  peakm = 4096;
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
      if(ADC[i] < peakm)
	{
	  peakm = ADC[i];
	}

      in[i][0] = ADC[i];
      in[i][1] = 0;
    }

  // fft
  // fft1d->ForwardGetAmplitude(in,out);
  // fft0 = out[0];
  // fft1 = out[1];
  // fftsum = 0;
  // for (int i = 0; i < 120; ++i)
  //   {
  //     fftdata[i] = out[i];
  //     fftsum += out[i];
  //   }

  
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
  energy4 = 0;

  for (int i = 58; i < 72; ++i)//69 71 73
    {
      energy1 += data[i];
    }

  for (int i = 20; i < 60; ++i)
    {
      energy2 += ADC[i];
    }

  for (int i = 0; i < 240; ++i)
    {
      energy += ADC[i];
    }
  for (int i = 0; i < 256; ++i)
    {
      energy3 += data[i];
    }

  for (int i = 50; i < 134; ++i)
    {
      energy4 += data[i];
    }
  
  if(countup < aven)
    {
      if(cutgup->IsInside(energy3,(energy1+0.01)/energy3)&&rp>30&&rp<50&&peak>100/*cutgup->IsInside(energy3,energy1) && rp>120 && rp<170*/)//energy,energy2
	{
	  for (int i = 0; i < 256; ++i)
	    {
	      dataupf1[i] += ((double)data[i]/peak);
	      dataups1[i] += ((double)data[i]/energy3);
	    }
	  countup++;
	}
    }
  if(countdown < aven)
    {
      if(cutgdown->IsInside(energy3,(energy1+0.01)/energy3)&&rp>30&&rp<50&&peak>100/*cutgdown->IsInside(energy3,energy1) && rp>120 && rp<170*/)//energy,energy2
	{
	  for (int i = 0; i < 256; ++i)
	    {
	      datadownf1[i] += ((double)data[i]/peak);
	      datadowns1[i] += ((double)data[i]/energy3);
	    }
	  countdown++;
	}
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

  TGraph *gupf1 = new TGraph;
  gupf1->SetName("gupf1");
  TGraph *gdownf1 = new TGraph;
  gdownf1->SetName("gdownf1");
  TGraph *gdiff1 = new TGraph;
  gdiff1->SetName("gdiff1");

  TGraph *gups1 = new TGraph;
  gups1->SetName("gups1");
  TGraph *gdowns1 = new TGraph;
  gdowns1->SetName("gdowns1");
  TGraph *gdifs1 = new TGraph;
  gdifs1->SetName("gdifs1");
  
  for (int i = 0; i < 256; ++i)
    {
      gupf1->SetPoint(i,i,dataupf1[i]/aven);
      gdownf1->SetPoint(i,i,datadownf1[i]/aven);
      gdiff1->SetPoint(i,i,(datadownf1[i]-dataupf1[i])/aven);

      gups1->SetPoint(i,i,dataups1[i]/aven);
      gdowns1->SetPoint(i,i,datadowns1[i]/aven);
      gdifs1->SetPoint(i,i,(dataups1[i]-datadowns1[i])/aven);      
    }

  gupf1->Write();
  gdownf1->Write();
  gdiff1->Write();
  gups1->Write();
  gdowns1->Write();
  gdifs1->Write();

  
  roottree->Write();
  rootfile->Close();

  std::cout<<std::endl<<countup<<"  "<<countdown<<std::endl;
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
