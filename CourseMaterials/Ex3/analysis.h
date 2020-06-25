#ifndef analysis_h
#define analysis_h

#include <TROOT.h>
#include <TFile.h>
#include "TLorentzVector.h"
//#include "fastjet/ClusterSequence.hh"

//using namespace fastjet;

// Header file for the classes stored in the TTree if any.
#include <vector>
#include <iostream>
using std::vector;
using std::cout;
using std::endl;

class analysis {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

	//for easier access:
  vector<float>   _pt;
   vector<float>  _eta;
   vector<float>  _phi;
   vector<float>  _m;
   vector<int>    _pdgid;
   vector<int>    _status;
   vector<TLorentzVector> _jets;



   // Declaration of leaf types
   vector<float>   *mc_pt;
   vector<float>   *mc_eta;
   vector<float>   *mc_phi;
   vector<float>   *mc_m;
   vector<int>     *mc_pdgid;
   vector<int>     *mc_status;

   // List of branches
   TBranch        *b_mc_pt;   //!
   TBranch        *b_mc_eta;   //!
   TBranch        *b_mc_phi;   //!
   TBranch        *b_mc_m;   //!
   TBranch        *b_mc_pdgid;   //!
   TBranch        *b_mc_status;   //!

   analysis(TString file="", TString outputfile="");
   virtual ~analysis();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
	virtual void     ReadEvent(int jentry);

	TString output_name;

};

#endif

#ifdef analysis_cxx

void analysis::ReadEvent(int jentry) {
	LoadTree(jentry);
	fChain->GetEntry(jentry);
	_pt = (*mc_pt);
	_eta = (*mc_eta);
	_phi = (*mc_phi);
	_m = (*mc_m);
	_pdgid = (*mc_pdgid);
	_status = (*mc_status);

/*
	//-------------------------------------
	//build some jets:
	vector<fastjet::PseudoJet> particles;
	TLorentzVector tmp;
	for(int i=0; i<_pdgid.size();i++) {
		if( _status[i]==1){
			tmp.SetPtEtaPhiM(_pt[i],_eta[i],_phi[i],_m[i]);
			particles.push_back( fastjet::PseudoJet(tmp.Px(), tmp.Py(), tmp.Pz(), tmp.E() ) );
		}
	}
	// choose a jet definition
	double R = 0.4;
	fastjet::JetDefinition jet_def(fastjet::antikt_algorithm, R);
	// run the clustering
	fastjet::ClusterSequence cs(particles, jet_def);

	//here we can extract the jets for this event:
	vector<fastjet::PseudoJet> jets = sorted_by_pt(cs.inclusive_jets());
	for(int i=0; i<jets.size(); i++) {
		TLorentzVector tmp;
		tmp.SetPtEtaPhiM( jets[i].pt(), jets[i].eta(), jets[i].phi(), jets[i].m() );
		_jets.push_back(tmp);
	}
	*/
}
analysis::analysis(TString file, TString outputfile) : fChain(0)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
	TTree * tree=0;
	cout<<"Reading events from "<<file<<endl;
	TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(file);
	if (!f || !f->IsOpen()) {
		f = new TFile(file);
	}
	f->GetObject("analysis",tree);

   Init(tree);

	output_name=outputfile;

}
analysis::~analysis()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t analysis::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t analysis::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void analysis::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   mc_pt = 0;
   mc_eta = 0;
   mc_phi = 0;
   mc_m = 0;
   mc_pdgid = 0;
   mc_status = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("mc_pt", &mc_pt, &b_mc_pt);
   fChain->SetBranchAddress("mc_eta", &mc_eta, &b_mc_eta);
   fChain->SetBranchAddress("mc_phi", &mc_phi, &b_mc_phi);
   fChain->SetBranchAddress("mc_m", &mc_m, &b_mc_m);
   fChain->SetBranchAddress("mc_pdgid", &mc_pdgid, &b_mc_pdgid);
   fChain->SetBranchAddress("mc_status", &mc_status, &b_mc_status);
   Notify();
}

Bool_t analysis::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void analysis::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t analysis::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}

#endif // #ifdef analysis_cxx






