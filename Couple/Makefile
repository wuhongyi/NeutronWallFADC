### Makefile --- 
## 
## Description: 
## Author: Hongyi Wu(吴鸿毅)
## Email: wuhongyi@qq.com 
## Created: 日 10月  2 19:40:07 2016 (+0800)
## Last-Updated: Mon Jul  2 10:13:58 2018 (-0400)
##           By: Hongyi Wu(吴鸿毅)
##     Update #: 6
## URL: http://wuhongyi.cn 

OBJ = wu
sourcefile = main.cc Couple.hh Couple.cc UserDefine.hh 

ROOTCFLAGS  = $(shell root-config --cflags)
ROOTLIBS    = $(shell root-config --libs)

CFLAGS = -g -Wall -O2 -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64

GXX = g++ 

all:$(OBJ)

$(OBJ): $(sourcefile)
	$(GXX) $(CFLAGS) $(ROOTCFLAGS) $(ROOTLIBS) -o $@ $(filter %.cc ,$(sourcefile))

clean:
	rm -f *~ *.o $(OBJ)


######################################################################
### Makefile ends here
