// main.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: Thu Jun 21 17:46:54 2018 (-0400)
// Last-Updated: Thu Jun 21 17:50:10 2018 (-0400)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 1
// URL: http://wuhongyi.cn 

#include "UserDefine.hh"
#include "FADC.hh"

#include "TString.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc, char *argv[])
{
  TString rawfilepath = RAWFILEPATH;
  TString outfilepath = OUTFILEPATH;

  if(argc != 3)
    {
      std::cout<<"error(argc!=3)   "<<argv[0]<<" [Run Number] [Mod Number 1-28]"<<std::endl;
      return 1;
    }

  TString RunNumber(argv[1]);
  int runnumber = RunNumber.Atoi();

  TString ModNumber(argv[2]);
  int modnumber = ModNumber.Atoi();

  FADC *fadc = new FADC(rawfilepath,outfilepath,runnumber,modnumber);
  fadc->Process();
  delete fadc;
  
  return 0;
}

// 
// main.cc ends here
