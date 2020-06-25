{
	//read data from a root file
	// get the NTuple
	TFile *f = new TFile("hsimple.root","READ");
	TTree *ntuple = (TTree*)f->Get("ntuple");
	//Define the variable to hold the read value.
	Float_t xdata;
	Int_t nEntries = (Int_t)ntuple->GetEntries();
	//tell the tree to populate the variable x  when reading an entry
	ntuple->SetBranchAddress("x",&xdata);
	//create a new histogram
	TH1F* hist = new TH1F("x","x",40,-4,4);
	// read all the entries and fill the histogram
	for (Int_t i=0; i<nEntries; ++i){
		ntuple->GetEntry(i);
		hist->Fill(xdata);
		}
	hist->Draw();
}
