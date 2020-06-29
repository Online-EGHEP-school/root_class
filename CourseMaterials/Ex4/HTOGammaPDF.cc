//====this Macro For the Higgs analysis to di-Gamma=====//
//////////////////////////////////////////////////////////
#include <iostream>
#include "HTOGamma.h"
		int Higgs= 0;			 
   	 int binMass   = 1200;
	 float minMass = 0.0;
	 float maxMass = 300.0;
	// float EtaCut = 2.5;
int main(int argc, char* argv[]) {// Begin main program.
  // Check that correct number of command-line arguments
  if (argc != 2) {
    cerr << " Unexpected number of command-line arguments. \n"
         << " You are expected to provide a file name and nothing else. \n"
         << " Program stopped! " << endl;
    	return 1;
  		}
// Book histograms.
 TH1F *HiggsRecomass		= new TH1F("HiggsRecomass","",binMass,minMass,maxMass);
 TH1F *HiggsRecomassPDF		= new TH1F("HiggsRecomassPDF","",binMass,minMass,maxMass);
 TH1F *HiggsGenmass		= new TH1F("HiggsGenmass","",binMass,minMass,maxMass);
 TH1F *HiggsGenmassPDF		= new TH1F("HiggsGenmassPDF","",binMass,minMass,maxMass);
 TH1F *HiggsRecomassA		= new TH1F("Higgs","",binMass,minMass,maxMass);
 TH1F *HiggsRecomassAPDF	= new TH1F("HiggsPDF","",binMass,minMass,maxMass);
//////////////////////////////////////////////////////////////////////////////--------------------------------------------
	Pythia pythia;
// Confirm that external file will be used for settings..
  cout << " PYTHIA settings will be read from file " << argv[1] << endl;
// ============Set up pythia generation=============================.
// Declare Pythia object
  pythia.readFile(argv[1]);
  int nEvent = pythia.mode("Main:numberOfEvents");
  int nAbort = pythia.mode("Main:timesAllowErrors");
  bool hasPL = pythia.flag("PartonLevel:all");
  pythia.readString("SoftQCD:nonDiffractive = off"); 
  pythia.init(); // Initialize; incoming pp beams is default.

//Selection of PDF
	string pdfSet = "cteq66.LHgrid";
// Loop over one default run and one with new PDF.
  for (int iRun = 0; iRun < 2; ++iRun) {
// In second run pick new PDF set.
    if (iRun == 1) {
	pythia.readString("PDF:useLHAPDF = on");
	pythia.readString("PDF:LHAPDFset = " + pdfSet);
	pythia.readString("PDF:extrapolateLHAPDF = on");
 	//pythia.init(); // Initialize; incoming pp beams is default.
		    }

//=================Generate event(s) [Event Loop]=====================
  int iAbort = 0;
for (int iEvent = 0; iEvent < nEvent; ++iEvent) {
  // Generate events. Quit if too many failures.
    if (!pythia.next()) {
      	if (++iAbort < nAbort) continue;
	cout << " Event generation aborted prematurely, owing to error!\n";
   	 break;
			}
//========(1)===========Looking for the first Generated Candidate Gamma====================
  	for (unsigned i = 0; i < pythia.event.size(); ++i){
		int iDau1 = pythia.event[i].daughter1();
		Vec4 G1(pythia.event[iDau1].px(), pythia.event[iDau1].py(), pythia.event[iDau1].pz(), pythia.event[iDau1].e());
	  	if (abs(pythia.event[iDau1].id()) == 22// &&
			//pythia.event[iDau1].pT() > 33.0 &&
			//pythia.event[iDau1].eT() > 26.0 &&
		       //(pythia.event[iDau1].pT())*3.0 > G1.mCalc() &&
	   		//pythia.event[iDau1].eta()>1.37 && pythia.event[iDau1].eta()<2.5
			){
	   		iGflag1 =i;
			GDau1++;
	 	   }//cut Gamma1 
//========(2)===========Looking for the Second  Generated Candidate Gamma=============================
 	for (unsigned j = 0; j < pythia.event.size(); ++j){
		int iDau2 = pythia.event[j].daughter2();
		Vec4 G2(pythia.event[iDau2].px(), pythia.event[iDau2].py(), pythia.event[iDau2].pz(), pythia.event[iDau2].e());
 	 	 if (abs(pythia.event[iDau2].id()) == 22
		  	 //pythia.event[iDau2].pT() > 25.0 &&
			 //pythia.event[iDau2].eT() > 36.0 &&
		        //(pythia.event[iDau2].pT())*4.0 > G2.mCalc() &&
		  	 //pythia.event[iDau2].eta()> 1.37 && pythia.event[iDau2].eta()<=2.37
		 	 //i != iGflag1
				){
	  		 iGflag2 =i;
	  		 GDau2++;
		     }//cut Gamma2   
	 if (GDau1 > 0 && GDau2 > 0){
		        EnGENGama1         = pythia.event[pythia.event[iGflag1].daughter1()].e();
		 	pxGENGama1         = pythia.event[pythia.event[iGflag1].daughter1()].px();
			pyGENGama1         = pythia.event[pythia.event[iGflag1].daughter1()].py();
			pzGENGama1         = pythia.event[pythia.event[iGflag1].daughter1()].pz();
		        EnGENGama2         = pythia.event[pythia.event[iGflag2].daughter2()].e();
		 	pxGENGama2         = pythia.event[pythia.event[iGflag2].daughter2()].px();
			pyGENGama2         = pythia.event[pythia.event[iGflag2].daughter2()].py();
		        pzGENGama2         = pythia.event[pythia.event[iGflag2].daughter2()].pz();
//========(3)===========computing the invariant mass---================= 		
 		Vec4 GENG2(pxGENGama2, pyGENGama2, pzGENGama2, EnGENGama2);
		Vec4 GENG1(pxGENGama1, pyGENGama1, pzGENGama1, EnGENGama1);	
   		Vec4 mGEN(GENG1+GENG2);
		mGENMass = mGEN.mCalc();
        if (iRun == 0) {
   		HiggsGenmass->Fill(mGENMass);
			}
	else {
   		HiggsGenmassPDF->Fill(mGENMass);
			}
		     }// if both
		GDau2=0;						
		   }//end of Gamma 2 loop
		GDau1=0;
	 }//end of Gamma 1 loop
//================================================================================================//
//the next Three stages based on the experimental view of the event[Reconstructed]================
  	for (unsigned i = 0; i < pythia.event.size(); ++i){
		Vec4 R1(pythia.event[i].px(), pythia.event[i].py(), pythia.event[i].pz(), pythia.event[i].e());
	  	if (abs(pythia.event[i].id()) == 22 //&&
//			pythia.event[i].pT() > 33.0 &&
//			pythia.event[i].eT() > 26.0 &&
//		       (pythia.event[i].pT())*3.0 > R1.mCalc() &&
//	   		pythia.event[i].eta()>1.37 && pythia.event[i].eta()<2.5
				){
	   		iflag1 =i;
			Dau1++;
			}//cut Gamma1 
//========(2)===========Looking for the Second Candidate Gamma=============================
	for (int j = 0 ; j < pythia.event.size(); ++j){
		Vec4 R2(pythia.event[j].px(), pythia.event[j].py(), pythia.event[j].pz(), pythia.event[j].e());
 	 	 if (abs(pythia.event[j].id()) == 22 &&
//		  	 pythia.event[j].pT() > 25.0 &&
//			 pythia.event[j].eT() > 36.0 &&
//		        (pythia.event[j].pT())*4.0 > R2.mCalc() &&
//	   		 pythia.event[j].eta()>1.37 && pythia.event[j].eta()<2.5
		  	j != iflag1){
	  		iflag2 =j;
	  		Dau2++;
			 }//cut Gamma2
	if (Dau1 > 0 && Dau2 > 0){
		        EnRecoGama1            = pythia.event[iflag1].e();
		 	pxRecoGama1            = pythia.event[iflag1].px();
			pyRecoGama1            = pythia.event[iflag1].py();
		        pzRecoGama1    	       = pythia.event[iflag1].pz();
					
			EnRecoGama2            = pythia.event[iflag2].e();
			pxRecoGama2            = pythia.event[iflag2].px();
			pyRecoGama2            = pythia.event[iflag2].py();
			pzRecoGama2            = pythia.event[iflag2].pz();
//========(3)===========computing the invariant mass---================= 
		Vec4 RECR1(pxRecoGama1, pyRecoGama1, pzRecoGama1, EnRecoGama1);
		Vec4 RECR2(pxRecoGama2, pyRecoGama2, pzRecoGama2, EnRecoGama2);
   		Vec4 mReco(RECR1+RECR2);
		mRecoMass = mReco.mCalc();
        if (iRun == 0) {
        	HiggsRecomass->Fill(mRecoMass);
			}
	else {
        	HiggsRecomassPDF->Fill(mRecoMass);
			}
		  }//if both
		Dau2 = 0.0;
		 }//end of Gamma 2 loop
		Dau1 = 0.0;
 // cout << "( " <<iEvent <<" ) "<<"Run("<<i<<")"<< "RECO(Higgs) equals=" <<"  "<<mRecoMass<<endl;
    	   }//end of Gamma 1 loop
//=====================computing Generated Higgs mass from Diphoton---===================	 
  	for (unsigned i = 0; i < pythia.event.size(); ++i){
  	if (pythia.event[i].id()== 25 && 
	   (pythia.event[ pythia.event[i].daughter1()].idAbs()== 22 ||pythia.event[ pythia.event[i].daughter2()].idAbs()== 22)){ 
		iH = i;
		Higgs++;
//information for the first generated gamma
  	int idADau1 		= pythia.event[ pythia.event[iH].daughter1()].idAbs();
  	float pxADau1 		= pythia.event[ pythia.event[iH].daughter1()].px();
  	float pyADau1 		= pythia.event[ pythia.event[iH].daughter1()].py();
  	float pzADau1 		= pythia.event[ pythia.event[iH].daughter1()].pz();
  	float eADau1 		= pythia.event[ pythia.event[iH].daughter1()].e();
//information for the second generated gamma
  	int idADau2 		= pythia.event[ pythia.event[iH].daughter2()].idAbs();
  	float pxADau2 		= pythia.event[ pythia.event[iH].daughter2()].px();
  	float pyADau2 		= pythia.event[ pythia.event[iH].daughter2()].py();
  	float pzADau2 		= pythia.event[ pythia.event[iH].daughter2()].pz();
  	float eADau2 		= pythia.event[ pythia.event[iH].daughter2()].e();
 //calculating the Generated invariant mass
 		Vec4 AG1(pxADau1,pyADau1,pzADau1,eADau1);
 		Vec4 AG2(pxADau2,pyADau2,pzADau2,eADau2);
		Vec4 Am(AG1+AG2);
			mAMass = Am.mCalc();
        if (iRun == 0) {
		HiggsRecomassA->Fill(mAMass);
			}
	else {
		HiggsRecomassAPDF->Fill(mAMass);
			}
		   }//Finding Generated information
		}//for loop
       if(iEvent%100 == 0) cout << "ev.No. "<<iEvent << ", The Number of Generated Higgs=  " <<Higgs<<endl;
	} //Event Loop
cout << "Number of Generated Higgs=" <<"  "<<Higgs<<endl;
  // Final statistics.
  pythia.stat();
  }  // End of loop over two runs.
// Print histograms.
TFile *output = new TFile("HTOGammaPDF-ffbar2WW-FSR-10.root","recreate");
output->cd();
   HiggsRecomass->Draw();
   HiggsRecomassPDF->Draw();
   HiggsGenmass->Draw();
   HiggsGenmassPDF->Draw();
   HiggsRecomassA->Draw();
   HiggsRecomassAPDF->Draw();
  std::cout << "\nDouble click on the histogram window to quit.\n";
  gPad->WaitPrimitive();
// Save histogram on file and close file.
 HiggsRecomass->Write();
 HiggsRecomassPDF->Write();
 HiggsGenmass->Write();
 HiggsGenmassPDF->Write();
 HiggsRecomassA->Write();
 HiggsRecomassAPDF->Write();
output->Close();
  
 // delete outFile;
  // Done.
//  return 0;	
	}
