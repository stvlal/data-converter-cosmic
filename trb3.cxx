

using namespace std;

#include "trb3.h" // The definition of the input files three and necessary classes

#include "t20.h" // The definition of the output file three



int main(int argc, char** argv) {

//TApplication *theApp = new TApplication("App", &argc, argv);
//This option is needed if graphics (such as canvases) is used


if ((string(argv[1]) == "-h")) {
      
        std::cerr << "Usage: -i <input_file1> <input_file2> ... -o <output_file> " << std::endl;
       
        return 1;
    } 

if ((argc < 5)||(string(argv[1]) != "-i")||(string(argv[argc-2]) != "-o")) {
      
        std::cerr << "Usage: -i <input_file1> <input_file2> ... -o <output_file> " << std::endl;
       
        return 1;
    } // Checking for right usage of the command line options



unsigned long N=0; // Number of good (survived) events

Int_t chan0 = 23; //Channel for PMT 0
Int_t chan1 = 24; //Channel for PMT 1
Int_t chan2 = 26; //Channel for PMT 2


trb3 new_trb; //Define variable of the class trb3




TChain *fChain; //Define the input files chain
fChain = new TChain("T");

for (Int_t i = 2; i < argc-2; i++) {
cout << argv[i] << endl;
fChain->Add(argv[i]);
}; //Adding input files into the chain




//Long64_t entry = fChain->GetEntries();
//cout << "N enteries = " << entry << endl; 
//Printing out number of entries in the chain

new_trb.Init(fChain); //Initialization of a new chain (branch addresses and branch pointers set)

        TFile *outFile = new TFile(argv[argc-1],"recreate");
	//Creating the output file
	
        t20->Branch("eventn",&eventn,"adc0/D:adc1/D:adc2/D:tdc0/D:tdc1/D:tdc2/D");
	//Define output three branches 	


	
//for(Long64_t i=0;i<=entry;i++) {



new_trb.Process(N, chan0, chan1, chan2); 



//};
//Looping over entries in the input files


t20->Write("", TObject::kOverwrite);
//Writing down the output three

outFile->Close(); 
//Closing the output file


//  theApp->Run(kTRUE); 
//This option is needed if graphics (such as canvases) is used (see the definition of theApp above)

 cout << "Number of good (survived) events = " << N << endl;
  
  return 0;
 

};




Bool_t trb3::Process(unsigned long &N,Int_t chan0,Int_t chan1, Int_t chan2)
{


Long64_t entry= 0;

//fChain->GetEntry(entry);
//Taking the entry from the chain

Double_t adc00,tdc00;  // Declaring ToT and TDC for PMT 0

while (fReader.Next()) {

fReader.SetEntry(entry);


Int_t Hits_ = Hits_nTdcChannel.GetSize();
 
if(entry%100000==0) printf("+%ld %d\n",(long)entry,Hits_);
//Printing out for each 100000 entries
 

int Kk=(Hits_-1); // Number of hits in the entry (-1 since hit zero is reserved for header)

if (Hits_ >= 5) { // Number of hits should be greater than 5. Hit zero reserved for header, two hits for PMT 1 front and rear edge times, and two hits for PMT 2 front and rear edge times


for(int i=1;i<=Kk-3;i++) // Searching for PMT 1 front edge hit
   {  

   if ((Hits_nTdcChannel[i] == chan1)&&(Hits_nSignalEdge[i]==1)) { // Checking the channel number

for(int j=i+1;j<=Kk-2;j++) // Searching for PMT 1 rear edge hit
   {   
   
   if ((Hits_nTdcChannel[j] == chan1)&&(Hits_nSignalEdge[j]==0)) { // Checking the channel number
   
   if (Hits_nEpochCounter[i] == Hits_nEpochCounter[j]) { // Checking that both hits are from the same physical event. 
   
   
   
for(int k=j+1;k<=Kk-1;k++) // Searching for PMT 2 front edge hit
   {  
   
   if ((Hits_nTdcChannel[k] == chan2)&&(Hits_nSignalEdge[k]==1)) { // Checking the channel number
   
   if (Hits_nEpochCounter[j] == Hits_nEpochCounter[k]) { // Checking that hit came from the same physical event as previous two.

for(int l=k+1;l<=Kk;l++) // Searching for PMT 2 rear edge hit
   {   
    
   if ((Hits_nTdcChannel[l] == chan2)&&(Hits_nSignalEdge[l]==0)) { // Checking the channel number

   if (Hits_nEpochCounter[k] == Hits_nEpochCounter[l]) {  // Checking that hit came from the same physical event as previous three.  
   
   
   // Setting of ToT and TDC for PMT 0. To make it immediately clear that they have no physical meaning
   adc00 = -1000.;
   tdc00 = -1000.;

if ((Hits_ >= 7)&&(i >= 3)) {  //  Condition for the availability of data from PMT 0

for(int qq=1;qq<i;qq++) {  // Searching for PMT 0 front edge hit

   if ((Hits_nTdcChannel[qq] == chan0)&&(Hits_nEpochCounter[qq] == Hits_nEpochCounter[l])&&(Hits_nSignalEdge[qq]==1)) {

for(int ww=qq+1;ww<i;ww++) {  // Searching for PMT 0 rear edge hit

   if ((Hits_nTdcChannel[ww] == chan0)&&(Hits_nEpochCounter[ww] == Hits_nEpochCounter[i])&&(Hits_nSignalEdge[ww]==0)) { 

   
   adc00 = Hits_fTime[ww]-Hits_fTime[qq]-(57.4-30.);  // Calculating adc0 as the difference between PMT 0 rear edge time and PMT 0 front edge time
   tdc00 = Hits_fTime[qq]; // Define tdc0 as PMT 0 front edge time
   
   };
   
   };  // End of the searching for PMT 0 rear edge hit

}; 


}; // End of the searching for PMT 0 front edge hit

}; // End of the if ((Hits_ >= 7)&&(i >= 3))


      eventn.adc0 = adc00;       
      eventn.adc1 = Hits_fTime[j]-Hits_fTime[i]-(57.4-30.); // Calculating adc1 as the difference between PMT 1 rear edge time and PMT 1 front edge time (time-over-threshold method).      
      eventn.adc2 = Hits_fTime[l]-Hits_fTime[k]-(57.87-30.); // Calculating adc2 as the difference between PMT 2 rear edge time and PMT 2 front edge time (time-over-threshold method)
      
      eventn.tdc0 = tdc00; // Define tdc0 as PMT 0 front edge time
      eventn.tdc1 = Hits_fTime[i]; // Define tdc1 as PMT 1 front edge time
      eventn.tdc2 = Hits_fTime[k]; // Define tdc2 as PMT 2 front edge time
    
      
      t20->Fill(); //Filling out the output three


 
   N++; //Increment of the number of good (survived) events
	 
	       
         }; // end of channels match if
         }; // end of EpochCounters match if  

   };
   };
   };
   };
   };
   }; // end of loop over the hits
   };
   };
   };
   }; // end of number of hits >= 7 if
   entry++;
   }; // end of entry (while) loop
   
return kTRUE;
}

