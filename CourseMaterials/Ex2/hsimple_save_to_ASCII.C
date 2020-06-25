{
	gROOT->Reset();
	 TFile *f = new TFile("hsimple.root","READ");
	 TTree *ntuple = (TTree*)f->Get("ntuple");
	  float xdata,ydata,zdata; // create variables of the same type as the branches you want to access
	   ntuple->SetBranchAddress("x",&xdata); // for all the TTree branches you need this
	  ntuple->SetBranchAddress("y",&ydata);
	  ntuple->SetBranchAddress("z",&zdata);
	  FILE *fp = fopen("hsimple.dat","w+");
	  // adds content to the file 
	 // fprintf(fp, "%s %s %s\n", "xdata", "ydata", "zdata");
	for (int i=0;i<ntuple->GetEntries();i++){
    // loop over the tree
    ntuple->GetEntry(i);
    cout << xdata << " " << ydata << " "<< zdata << endl; //print to the screen
    fprintf(fp, "%f %f %f\n", xdata, ydata, zdata);
  	}
    fclose(fp);
    f->Close();
}
