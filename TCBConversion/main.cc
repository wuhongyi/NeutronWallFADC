// main.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: Thu Jun 21 15:15:27 2018 (-0400)
// Last-Updated: Thu Jun 21 16:07:44 2018 (-0400)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 3
// URL: http://wuhongyi.cn 

#include "UserDefine.hh"
#include "TCB.hh"

#include "TString.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc, char *argv[])
{
  TString rawfilepath = RAWFILEPATH;
  TString outfilepath = OUTFILEPATH;

  if(argc != 2)
    {
      std::cout<<"error(argc!=2)   "<<argv[0]<<" [Run Number]"<<std::endl;
      return 1;
    }
  TString RunNumber(argv[1]);
  int runnumber = RunNumber.Atoi();
  
  TCB *tcb = new TCB(rawfilepath,outfilepath,runnumber);
  tcb->Process();
  delete tcb;
  
  return 0;
}

// 
// main.cc ends here
