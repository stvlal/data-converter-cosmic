//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Mar  2 18:21:44 2020 by ROOT version 6.18/04
// from TTree T/UMainz TRBv3 HLD Data (Calibrated)
// found on file: xx18348110559.hld.root_calibrated.root
//////////////////////////////////////////////////////////

#ifndef trb3_h
#define trb3_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>


// Headers needed by this particular selector

#include <TObject.h>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;


class trb3 : public TSelector {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

   // Readers to access the data (delete the ones you do not need).
   TTreeReaderValue<unsigned int> fUniqueID = {fReader, "fUniqueID"};
   TTreeReaderValue<unsigned int> fBits = {fReader, "fBits"};
   TTreeReaderValue<unsigned int> nEvtSize = {fReader, "nEvtSize"};
   TTreeReaderValue<unsigned int> nEvtDecoding = {fReader, "nEvtDecoding"};
   TTreeReaderValue<unsigned int> nEvtId = {fReader, "nEvtId"};
   TTreeReaderValue<unsigned int> nEvtSeqNr = {fReader, "nEvtSeqNr"};
   TTreeReaderValue<unsigned int> nEvtDate = {fReader, "nEvtDate"};
   TTreeReaderValue<unsigned int> nEvtTime = {fReader, "nEvtTime"};
   TTreeReaderValue<unsigned int> nEvtRun = {fReader, "nEvtRun"};
   TTreeReaderValue<unsigned int> nEvtPad = {fReader, "nEvtPad"};
   TTreeReaderValue<unsigned int> nSubEvtSize = {fReader, "nSubEvtSize"};
   TTreeReaderValue<unsigned int> nSubEvtDecoding = {fReader, "nSubEvtDecoding"};
   TTreeReaderValue<unsigned int> nSubEvtId = {fReader, "nSubEvtId"};
   TTreeReaderValue<unsigned int> nSubEvtTrigger = {fReader, "nSubEvtTrigger"};
   TTreeReaderValue<unsigned int> nSebErrCode = {fReader, "nSebErrCode"};
   TTreeReaderValue<unsigned int> nTrbs = {fReader, "nTrbs"};
   TTreeReaderValue<unsigned int> nTdcs = {fReader, "nTdcs"};
   TTreeReaderValue<unsigned int> nCTSExtTrigger = {fReader, "nCTSExtTrigger"};
   TTreeReaderValue<unsigned int> nCTSExtTriggerStatus = {fReader, "nCTSExtTriggerStatus"};
   TTreeReaderValue<unsigned int> nSubEvtDecError = {fReader, "nSubEvtDecError"};
   TTreeReaderArray<unsigned int> Hits_fUniqueID = {fReader, "Hits.fUniqueID"};
   TTreeReaderArray<unsigned int> Hits_fBits = {fReader, "Hits.fBits"};
   TTreeReaderArray<unsigned int> Hits_nTrbAddress = {fReader, "Hits.nTrbAddress"};
   TTreeReaderArray<unsigned int> Hits_nTdcChannel = {fReader, "Hits.nTdcChannel"};
   TTreeReaderArray<unsigned int> Hits_nSubEvtId = {fReader, "Hits.nSubEvtId"};
   TTreeReaderArray<unsigned int> Hits_nTdcErrCode = {fReader, "Hits.nTdcErrCode"};
   TTreeReaderArray<unsigned int> Hits_nSignalEdge = {fReader, "Hits.nSignalEdge"};
   TTreeReaderArray<unsigned int> Hits_nEpochCounter = {fReader, "Hits.nEpochCounter"};
   TTreeReaderArray<unsigned int> Hits_nCoarseTime = {fReader, "Hits.nCoarseTime"};
   TTreeReaderArray<unsigned int> Hits_nFineTime = {fReader, "Hits.nFineTime"};
   TTreeReaderArray<Double_t> Hits_fTime = {fReader, "Hits.fTime"};
   TTreeReaderArray<Bool_t> Hits_bIsCalibrated = {fReader, "Hits.bIsCalibrated"};
   TTreeReaderArray<Bool_t> Hits_bIsRefChannel = {fReader, "Hits.bIsRefChannel"};
   TTreeReaderArray<Bool_t> Hits_bVerboseMode = {fReader, "Hits.bVerboseMode"};


   trb3(TTree * /*tree*/ =0) { }
   virtual ~trb3() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Init(TChain *tree) { fReader.SetTree(tree); }
   virtual Bool_t  Notify(){ return kTRUE; }
   virtual Bool_t  Process(unsigned long &N, Int_t chan0, Int_t chan1, Int_t chan2);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }


   ClassDef(trb3,0);

};

#endif


