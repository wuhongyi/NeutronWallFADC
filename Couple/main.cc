// main.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: Sun Jul  1 21:08:48 2018 (-0400)
// Last-Updated: Mon Jul  2 10:28:10 2018 (-0400)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 6
// URL: http://wuhongyi.cn 

#include "UserDefine.hh"
#include "Couple.hh"

#include "TString.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc, char *argv[])
{
  TString rawfilepath = RAWFILEPATH;
  TString outfilepath = OUTFILEPATH;

  if(argc != 6)
    {
      std::cout<<"error(argc!=6)   "<<argv[0]<<" [Run Number]"<<std::endl;
      return 1;
    }
  TString RunNumber(argv[1]);
  int runnumber = RunNumber.Atoi();

  TString NumLeft(argv[2]);
  int numl = NumLeft.Atoi();
  TString ChLeft(argv[3]);
  int chl = ChLeft.Atoi();
 
  TString NumRight(argv[4]);
  int numr = NumRight.Atoi();
  TString ChRight(argv[5]);
  int chr = ChRight.Atoi();

  std::cout<<runnumber<<"  "<<numl<<"  "<<chl<<"  "<<numr<<"  "<<chr<<std::endl;
  
  Couple *couple = new Couple(rawfilepath,outfilepath,runnumber,numl,chl,numr,chr);
  couple->Process();
  delete couple;

  return 0;
}

// 
// main.cc ends here
