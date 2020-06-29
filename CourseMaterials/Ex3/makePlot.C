// this macro allows to make a standard plot with data and monte carlo superimposed
// it is useful once the cuts have been decided
{

///////////////////////////////////////////////////////////////////////////////
//  CONFIGURATION                                                            //
///////////////////////////////////////////////////////////////////////////////
// some initialization
gROOT->LoadMacro("functions.C");
gStyle->SetOptFit(111111);
gStyle->SetOptDate(0);
gStyle->SetOptTitle(0);
// constants to be adapted if you want
TString plotname = "mass";
Float_t low = 0;
Float_t high = 140;
// input files
// these points to the default files for this lab. 
// data_file is the data ntuple you want to use. Pick either electrons or muons 
// by uncommenting one of the lines below.
//Load the signal file
TFile * signal_file = new TFile("VH_histograms.root", "READ");
signal_file->cd();
//=======================create the histograms to fill====================================
TH1 * hsignal = (TH1F*)gDirectory->Get(plotname);
hsignal->SetDirectory(0);
hsignal->SetStats(0);
signal_file->Close();

//Load the background file
TFile * bkg_file = new TFile("Zbb_histograms.root", "READ");
bkg_file->cd();
//=======================create the histograms to fill====================================
TH1 * hbkg = (TH1F*)gDirectory->Get(plotname);
hbkg->SetDirectory(0);
hbkg->SetStats(0);
hbkg->SetLineColor(3);
hbkg->SetFillColor(3);
bkg_file->Close();
///////////////////////////////////////////////////////////////////////////////
//  ANALYSIS SCRIPT - MAKE A STANDARD PLOT WITH DATA AND MONTE CARLO         //
///////////////////////////////////////////////////////////////////////////////
THStack *hs  = new THStack("hs","Stacked 1 D histogram");
//=======================Create a Canvas==================================================
TCanvas *c = new TCanvas("c","Z Boson  mass",600.0,600.0);
c->cd(1);
gPad->SetTickx();
gPad->SetTicky();
gPad->SetGridx();
gPad->SetGridy();
//=======================Stacking the Histograms===========================================

hs->Add(hbkg);
//hs->Add(hsignal);

hs->Draw();
hsignal->Draw("E0,same");
hsignal->SetLineStyle(0);
hsignal->SetLineColor(1);
hsignal->SetLineWidth(2);
hsignal->SetMarkerColor(1);
hsignal->SetMarkerStyle(20);
hsignal->SetMarkerSize(0.875);

hs->GetXaxis()->SetTitle("M(#mu^{-}#mu^{+}) [GeV/c^{2}]");
hs->GetYaxis()->SetTitle("Nb. events");
hs->GetXaxis()->SetTitleOffset(1.0);
hs->GetYaxis()->SetTitleOffset(1.0);
hs->GetXaxis()->SetRangeUser(low,high);


// add a legend
leg = new TLegend(0.70, 0.7, 0.85,0.85);
leg->AddEntry(hsignal,"Signal ZH(#mu^{-}#mu^{+}bb)","p");
leg->AddEntry(hbkg,"Drell-Yann Z(#mu^{-}#mu^{+})","f");
leg->SetBorderSize(0);
leg->SetShadowColor(0);
leg->SetFillColor(0);
leg->Draw("same");
// conclude
gPad->Update();
//==============Saving the informations==============================
c->Update();
c->SaveAs("Ex3-ZBosonMass.png");
}
