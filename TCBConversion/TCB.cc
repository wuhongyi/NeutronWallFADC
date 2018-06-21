// TCB.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: Thu Jun 21 15:14:15 2018 (-0400)
// Last-Updated: Thu Jun 21 16:53:22 2018 (-0400)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 17
// URL: http://wuhongyi.cn 

#include "TCB.hh"
#include <iostream>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TCB::TCB(TString rawfilepath,TString outfilepath,int runnumber)
{
  Benchmark = new TBenchmark;

  file_in = new TFile(TString::Format("%sRUN_%d_tcb_bin.root",rawfilepath.Data(),runnumber).Data(),"READ");//"RECREATE" "READ"
  if(!file_in->IsOpen())
    {
      std::cout<<"Can't open root file"<<std::endl;
    }
  
  tree_in = (TTree*)file_in->Get("TCBBTree");
  tree_in->SetBranchAddress("TCBData",&TCBData);
  TotalEnery = tree_in->GetEntries();
  // tree_in->Print();
  
  file_out = new TFile(TString::Format("%srun_%04d_tcb.root",outfilepath.Data(),runnumber).Data(),"RECREATE");//"RECREATE" "READ"
  if(!file_out->IsOpen())
    {
      std::cout<<"Can't open root file"<<std::endl;
    }
  file_out->cd();
  tree_out = new TTree("t","");
  tree_out->Branch("tcb_trigger_number",&tcb_trigger_number,"tcb_trigger_number/L");
  tree_out->Branch("tcb_trigger_type",&tcb_trigger_type,"tcb_trigger_type/I");
  tree_out->Branch("tcb_ttime",&tcb_ttime,"tcb_ttime/L");
  tree_out->Branch("tcb_trigger_pattern",&tcb_trigger_pattern,"tcb_trigger_pattern[20]/s");
  // tree_out->Print();

}

TCB::~TCB()
{

}

void TCB::Init()
{
  tcb_trigger_number = 0;
  tcb_trigger_type = 0;
  tcb_ttime = 0;
  
  for( int i = 0; i< 20; i++)
    {
      tcb_trigger_pattern[i] = 0;
    }
}

void TCB::Convert(UShort_t* TCBData,int off)
{
  tcb_trigger_number = TCBData[0+off] + (((Long64_t)(TCBData[1+off])) << 16);    
  tcb_trigger_type = (TCBData[2+off] & 0x00FF);


  tcb_ttime = ((TCBData[2+off] & 0xFF00) >> 5);
  tcb_ttime += (Long64_t)(TCBData[3+off])*1000;
  tcb_ttime += ((Long64_t)(TCBData[4+off]) << 16)*1000;
  tcb_ttime += ((Long64_t)(TCBData[5+off]) << 32)*1000; 

  
  tcb_ntime = tcb_ttime % 1000000000;/// ns
  tcb_time  = tcb_ttime/1000000000;/// sec  

  for( int ch = 0; ch < 20; ch++)
    {
      tcb_trigger_pattern[ch] = TCBData[6+ch+off];
    }  
}

void TCB::Process()
{
  Benchmark->Start("tree");//计时开始

  Init();
  
  for (Long64_t entry = 0; entry < TotalEnery; ++entry)
    {
      if(entry % 10000 == 0)
	{
	  std::cout<<"\r"<<"Entry: "<<entry<<" / "<<TotalEnery;
	  std::cout<< std::flush;
	}

      file_in->cd();
      tree_in->GetEvent(entry);
      // tree_in->GetEntry(entry);

      int off = 0;
      while(off < 8192)
	{
	  Convert(TCBData,off);

	  if(tcb_trigger_number == 0 && tcb_ttime == 0)
	    {
	      break;
	    }

	  file_out->cd();
	  tree_out->Fill();
	  off += 32;
	}
      
      
    }


  file_in->cd();
  file_in->Close();

  file_out->cd();
  tree_out->Write();
  file_out->Close();
  
  std::cout<<std::endl;
  Benchmark->Show("tree");//计时结束并输出时间
}




// 
// TCB.cc ends here
