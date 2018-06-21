// FADC.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: Thu Jun 21 16:50:43 2018 (-0400)
// Last-Updated: Thu Jun 21 19:08:49 2018 (-0400)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 6
// URL: http://wuhongyi.cn 

#include "FADC.hh"
#include <iostream>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

FADC::FADC(TString rawfilepath,TString outfilepath,int runnumber, int mod)
{
  Benchmark = new TBenchmark;
  runid = runnumber;
  int temp1 = (mod-1)/7;
  
  file_in = new TFile(TString::Format("%sData%d/RUN_%d_fadc_%d_bin.root",rawfilepath.Data(),temp1,runnumber,mod).Data(),"READ");//"RECREATE" "READ"
  if(!file_in->IsOpen())
    {
      std::cout<<"Can't open root file"<<std::endl;
    }
  
  tree_in = (TTree*)file_in->Get("FADCBTree");
  tree_in->SetBranchAddress("FADCData",&FADCData);
  TotalEnery = tree_in->GetEntries();
  // tree_in->Print();


  file_out = new TFile(TString::Format("%srun_%04d_fadc_%02d.root",outfilepath.Data(),runnumber,mod).Data(),"RECREATE");//"RECREATE" "READ"
  if(!file_out->IsOpen())
    {
      std::cout<<"Can't open root file"<<std::endl;
    }
  file_out->cd();
  tree_out = new TTree("t","");
  tree_out->Branch("data_length",&data_length,"data_length/i");
  tree_out->Branch("rid",&rid,"rid/s");
  tree_out->Branch("ttype",&ttype,"ttype/S");
  tree_out->Branch("tnum",&tnum,"tnum/i");
  tree_out->Branch("ttime",&ttime,"ttime/L");
  tree_out->Branch("mid",&mid,"mid/S");
  tree_out->Branch("cid",&cid,"cid/S");
  tree_out->Branch("lnum",&lnum,"lnum/i");
  tree_out->Branch("ltime",&ltime,"ltime/L");
  tree_out->Branch("tpattern",&tpattern,"tpattern/s");
  tree_out->Branch("ped",&ped,"ped/s");
  tree_out->Branch("ADC",&ADC,"ADC[240]/S");
  tree_out->Branch("TDC",&TDC,"TDC[60]/I");
  tree_out->Branch("sample",&sample,"sample[240]/S");
  tree_out->Branch("nevt",&nevt,"nevt/I");
  // tree_out->Print();
  

  for (int i = 0; i < 240; ++i)
    {
      sample[i] = i;
    }
}

FADC::~FADC()
{

}

void FADC::Clear()
{
  data_length = 0;
  rid = 0;
  ttype = 0;
  tnum = 0;
  ttime = 0;
  mid = 0;
  cid = 0;
  lnum = 0;
  ltime = 0;
  tpattern = 0;
  ped = 0;
  
  for( int i = 0; i< 240; i++)
    {
      ADC[i] = 0;
    }
  for( int i = 0; i< 60; i++)
    {
      TDC[i] = 0;
    }
}

void FADC::Convert(UShort_t* data, int off)
{
  data_length  = data[0+off];
  data_length += ((UInt_t)(data[1+off]) << 16);
  
  rid          = (UShort_t)data[2+off];
  ttype        = (Short_t)(data[3+off] & 0x00FF);
  

  tnum  = ((UInt_t)(data[3+off] & 0xFF00) >> 8);
  tnum += ((UInt_t)(data[4+off]) << 8 );
  tnum += (((UInt_t)(data[5+off]) & 0x00FF) << 24);

  
  ttime  = ((ULong64_t)(data[5+off] & 0xFF00) >> 8)*8;
  ttime += ((ULong64_t)(data[6+off]))*1000;
  ttime += (((ULong64_t)(data[7+off] & 0x00FF)) << 16)*1000;
  
  mid    = (Short_t)((data[7+off] & 0xFF00) >> 8);
  
  ////////////////////////////////////////
  cid    = (Short_t)(data[8+off] & 0x00FF);

  lnum = ((UInt_t)(data[8+off] & 0xFF00)) >> 8;
  lnum += ((UInt_t)(data[9+off]) << 8);
  lnum += ((UInt_t)(data[10+off] & 0x00FF)) << 24;

  tpattern = (UShort_t)(data[10+off] & 0xFF00) >> 8;
  tpattern += (UShort_t)(data[11+off] & 0x00FF) << 8;

  ped = (UShort_t)(data[11+off] & 0xFF00 ) >> 8;
  ped += (UShort_t)(data[12+off] & 0x00FF) << 8;

  ltime = (((Long64_t)(data[12+off] & 0xFF00 )) >> 8 )*8;
  ltime+= ((Long64_t)(data[13+off]))*1000;
  ltime+= ((Long64_t)(data[14+off]) << 16)*1000;
  ltime+= ((Long64_t)(data[15+off]) << 32)*1000;

  //nADC = (data_length -32)/2;
  //nTDC = nADC/4;
  nADC = 240;
  nTDC = 60; 
  ////////////////////////////////////////
  for( int ip = 0; ip < nADC; ip++)
    {
      Short_t iadc = (Short_t)(data[16+ip+off]&0x0FFF);// 12bit
      ADC[ip] = 4096 - iadc;
    }
  
  for( int ip = 0; ip < nTDC; ip++)// ! wuhongyi ERROR
    {
      UShort_t itdc = ((data[16+ip*4+off] & 0xF000) >> 24);
      itdc += ((data[17+ip*4+off] & 0xF000) >> 16);
      itdc += ((data[18+ip*4+off] & 0xF000) >> 8 );
      TDC[ip] = itdc;
    }

}

void FADC::Process()
{
  Benchmark->Start("tree");//计时开始

  bool GoodData = true;
  
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
      while(off < 8192 && GoodData)
	{
	  Clear();
	  Convert(FADCData,off);
	  off += 256;

	  if(rid != runid) continue;
	  if(cid < 1 || cid > 4) continue;
	  
	  file_out->cd();
	  tree_out->Fill();
	  nevt++;
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
// FADC.cc ends here
