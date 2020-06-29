//simple analysis code. See instrutions here:

#define analysis_cxx
#include "analysis.h"
#include "TH1.h"

int main(void) {
	//analysis * a = new analysis("Zbb_events.root", "Zbb_histograms.root");
	analysis * a = new analysis("VH_events.root", "VH_histograms.root");
	a->Loop();
	delete a;
}
void analysis::Loop() {
	//   In a ROOT session, you can do:
	//      root> .L analysis.C
	//      root> analysis t
	//      root> t.GetEntry(12); // Fill t data members with entry number 12
	//      root> t.Show();       // Show values of entry 12
	//      root> t.Show(16);     // Read and show values of entry 16
	//      root> t.Loop();       // Loop on all entries
	//file:///home/dcs/Pictures/Screenshot%20from%202020-06-29%2010-45-41.png

	//     This is the loop skeleton where:
	//    jentry is the global entry number in the chain
	//    ientry is the entry number in the current Tree
	//  Note that the argument to GetEntry must be:
	//    jentry for TChain::GetEntry
	//    ientry for TTree::GetEntry and TBranch::GetEntry
	//
	//       To read only selected branches, Insert statements like:
	// METHOD1:
	//    fChain->SetBranchStatus("*",0);  // disable all branches
	//    fChain->SetBranchStatus("branchname",1);  // activate branchname
	// METHOD2: replace line
	//    fChain->GetEntry(jentry);       //read all branches
	//by  b_branchname->GetEntry(ientry); //read only this branch

	//there are only 6 variables in the ntuple (vectors, one entry per particle):
	//	_pt
	//	_eta
	//	_phi
	//	_m
	//	_pdgid
	//	_status
	//and a vector of TLorentzVector for the jets, _jets

	//---------------------------------------
	//declare some histograms to be filled:
	TFile * output_file = new TFile(output_name, "RECREATE");
	output_file->cd();

	//here you can declare new histograms:
	Int_t bins = 100;
	Float_t low = 0;
	Float_t high = 300;
	TH1 * h_mass = new TH1F("mass", "mass",bins,low,high);

	//---------------------------------------

	//load in the events:
	Long64_t nentries = fChain->GetEntriesFast();
	cout << "Looping over " << nentries << " events" << endl;

//loop over every event in the file:
	for (Long64_t jentry = 0; jentry < nentries; jentry++) {
		//read in this event:
		ReadEvent(jentry);
		cout << "In this event there are " << _pdgid.size() << " particles"
				<< endl;

		int number_of_muons = 0;
		int number_of_anti_muons = 0;
		//vectors to store the muons:
		TLorentzVector v1, v2;
		//now loop over every particle in the event:
		for (int i = 0; i < _pdgid.size(); i++) {
			//so here you can look at verious things and fill the plots:
			cout << "Particle: " << _pt[i] << " " << _phi[i] << " " << _eta[i]
					<< " " << _m[i] << " " << _pdgid[i] << " " << _status[i]
					<< endl;

			if (_status[i] == 1) {
				if (_pdgid[i] == 13) {
					number_of_muons++;
					cout << "event " << jentry << ":  muon number:" << " "
							<< number_of_muons << " " << endl << "  pt:"
							<< _pt[i] << "  phi:" << _phi[i] << "  eta:"
							<< _eta[i] << "  m:" << _m[i] << "  pdgid:"
							<< _pdgid[i] << "  status:" << _status[i] << endl;
					v1.SetPtEtaPhiM(_pt[i], _eta[i], _phi[i], _m[i]);
				}

				if (_pdgid[i] == -13) {
					number_of_anti_muons++;
					if (number_of_anti_muons != 0)
						cout << "event " << jentry << ": anti_muon number: "
								<< " " << number_of_anti_muons << " " << endl
								<< " pt:" << _pt[i] << " phi" << _phi[i]
								<< " eta:" << _eta[i] << " m:" << _m[i]
								<< " pdgid:" << _pdgid[i] << " status:"
								<< _status[i] << endl;
					v2.SetPtEtaPhiM(_pt[i], _eta[i], _phi[i], _m[i]);
				}

			}	//status == 1

		}	//loop over particles

		if (number_of_muons > 0 && number_of_anti_muons > 0) {
			TLorentzVector sum = v1 + v2;
			cout << "Combined Mass: " << sum.M() << endl
					<< "Combined Momentum: " << sum.Pt() << endl;
			h_mass->Fill(sum.M());
		}
	}
	output_file->Write();
	return 0;
}
//Add some methods
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

