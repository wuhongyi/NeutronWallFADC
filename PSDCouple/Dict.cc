// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME Dict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "DataClass.h"
#include "UserClass.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_DataClass(void *p = 0);
   static void *newArray_DataClass(Long_t size, void *p);
   static void delete_DataClass(void *p);
   static void deleteArray_DataClass(void *p);
   static void destruct_DataClass(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::DataClass*)
   {
      ::DataClass *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::DataClass >(0);
      static ::ROOT::TGenericClassInfo 
         instance("DataClass", ::DataClass::Class_Version(), "DataClass.h", 17,
                  typeid(::DataClass), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::DataClass::Dictionary, isa_proxy, 4,
                  sizeof(::DataClass) );
      instance.SetNew(&new_DataClass);
      instance.SetNewArray(&newArray_DataClass);
      instance.SetDelete(&delete_DataClass);
      instance.SetDeleteArray(&deleteArray_DataClass);
      instance.SetDestructor(&destruct_DataClass);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::DataClass*)
   {
      return GenerateInitInstanceLocal((::DataClass*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::DataClass*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_UserClass(void *p = 0);
   static void *newArray_UserClass(Long_t size, void *p);
   static void delete_UserClass(void *p);
   static void deleteArray_UserClass(void *p);
   static void destruct_UserClass(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::UserClass*)
   {
      ::UserClass *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::UserClass >(0);
      static ::ROOT::TGenericClassInfo 
         instance("UserClass", ::UserClass::Class_Version(), "UserClass.h", 107,
                  typeid(::UserClass), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::UserClass::Dictionary, isa_proxy, 4,
                  sizeof(::UserClass) );
      instance.SetNew(&new_UserClass);
      instance.SetNewArray(&newArray_UserClass);
      instance.SetDelete(&delete_UserClass);
      instance.SetDeleteArray(&deleteArray_UserClass);
      instance.SetDestructor(&destruct_UserClass);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::UserClass*)
   {
      return GenerateInitInstanceLocal((::UserClass*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::UserClass*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr DataClass::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *DataClass::Class_Name()
{
   return "DataClass";
}

//______________________________________________________________________________
const char *DataClass::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::DataClass*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int DataClass::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::DataClass*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *DataClass::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::DataClass*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *DataClass::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::DataClass*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr UserClass::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *UserClass::Class_Name()
{
   return "UserClass";
}

//______________________________________________________________________________
const char *UserClass::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::UserClass*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int UserClass::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::UserClass*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *UserClass::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::UserClass*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *UserClass::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::UserClass*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void DataClass::Streamer(TBuffer &R__b)
{
   // Stream an object of class DataClass.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(DataClass::Class(),this);
   } else {
      R__b.WriteClassBuffer(DataClass::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_DataClass(void *p) {
      return  p ? new(p) ::DataClass : new ::DataClass;
   }
   static void *newArray_DataClass(Long_t nElements, void *p) {
      return p ? new(p) ::DataClass[nElements] : new ::DataClass[nElements];
   }
   // Wrapper around operator delete
   static void delete_DataClass(void *p) {
      delete ((::DataClass*)p);
   }
   static void deleteArray_DataClass(void *p) {
      delete [] ((::DataClass*)p);
   }
   static void destruct_DataClass(void *p) {
      typedef ::DataClass current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::DataClass

//______________________________________________________________________________
void UserClass::Streamer(TBuffer &R__b)
{
   // Stream an object of class UserClass.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(UserClass::Class(),this);
   } else {
      R__b.WriteClassBuffer(UserClass::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_UserClass(void *p) {
      return  p ? new(p) ::UserClass : new ::UserClass;
   }
   static void *newArray_UserClass(Long_t nElements, void *p) {
      return p ? new(p) ::UserClass[nElements] : new ::UserClass[nElements];
   }
   // Wrapper around operator delete
   static void delete_UserClass(void *p) {
      delete ((::UserClass*)p);
   }
   static void deleteArray_UserClass(void *p) {
      delete [] ((::UserClass*)p);
   }
   static void destruct_UserClass(void *p) {
      typedef ::UserClass current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::UserClass

namespace {
  void TriggerDictionaryInitialization_Dict_Impl() {
    static const char* headers[] = {
"DataClass.h",
"UserClass.h",
0
    };
    static const char* includePaths[] = {
"/projects/hira/software/ROOT-v6.13.02/include",
"/evtdata/hira/wuhongyi/NeutronWallFADC/PSDCouple/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "Dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$DataClass.h")))  DataClass;
class __attribute__((annotate("$clingAutoload$UserClass.h")))  UserClass;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "Dict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "DataClass.h"
#include "UserClass.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"DataClass", payloadCode, "@",
"UserClass", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("Dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_Dict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_Dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_Dict() {
  TriggerDictionaryInitialization_Dict_Impl();
}
