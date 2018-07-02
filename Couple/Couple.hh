// Couple.hh --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: Sun Jul  1 19:39:06 2018 (-0400)
// Last-Updated: Sun Jul  1 21:05:33 2018 (-0400)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 1
// URL: http://wuhongyi.cn 

#ifndef _COUPLE_H_
#define _COUPLE_H_

class TFile;
class TTree;

class Couple
{
public:
  Couple(TString rawfilepath,TString outfilepath,int runnumber,int numl,int chl,int numr,int chr);
  virtual ~Couple();

  void Process();
  
private:
  TFile *f1;
  TFile *f2;
  TTree *t1;
  TTree *t2;
  int ch1,ch2;
  

  UInt_t          tnum1;
  Short_t         cid1;
  Short_t         ADC1[240];

  UInt_t          tnum2;
  Short_t         cid2;
  Short_t         ADC2[240];
  
};

#endif /* _COUPLE_H_ */
// 
// Couple.hh ends here
