//simple analysis code. See instrutions here:

#define analysis_cxx
#include "analysis.h"
#include "TH1.h"

int main(void) {
	//analysis * a = new analysis("Zbb_events.root", "Zbb_histograms.root"); //VH_events.root, VH_histograms.root
	analysis * a = new analysis("VH_events.root", "VH_histograms.root");
	a->Loop();
	delete a;
}
void analysis::Loop() {
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
	TH1 * h_mass = new TH1F("mass", "mass", 100, 0, 300);

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

