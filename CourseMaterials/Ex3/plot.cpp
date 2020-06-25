//simple plotting code. See instrutions here:
// http://www.hep.ucl.ac.uk/~hesketh/Summer_Project/sandbox.php
// Gavin Hesketh, gavin.hesketh@ucl.ac.uk



#include "TString.h"
#include "TFile.h"
#include "TH1.h"
#include "TLegend.h"
#include "TCanvas.h"


int main() {

	TString file1 = "Zbb_histograms.root";
	TString file2 = "VH_histograms.root";
	TString plotname = "mass";

	TFile * f = new TFile(file1, "READ");
	f->cd();
	TH1 * plot1 = (TH1F*)gDirectory->Get(plotname);
	plot1->SetDirectory(0);
	plot1->SetStats(0);
	f->Close();

	f = new TFile(file2, "READ");
	f->cd();
	TH1 * plot2 = (TH1F*)gDirectory->Get(plotname);
	plot2->SetDirectory(0);
	plot2->SetStats(0);
	f->Close();



	plot1->SetLineColor(2);
	plot2->SetLineColor(4);
	plot2->Scale(0.9);

	TLegend * legend = new TLegend(0.8,0.8,1,1, "", "NDC");
	legend->AddEntry(plot1, file1, "LEP");
	legend->AddEntry(plot2, file2, "LEP");



	TCanvas * c = new TCanvas();

	plot1->DrawCopy();
	plot2->DrawCopy("SAME");
	legend->Draw();

	c->Print(plotname+".eps");


	return 1;
}
