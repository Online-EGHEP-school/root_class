/*
Compile with:
g++ Ex11_histograms.cpp -o Ex11_histograms `root-config --cflags --libs`
./histograms
*/

#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <vector>
#include <cstring>

/****** Include the required ROOT Classes *****/
#include "TH2.h"
#include "TH1.h"
#include "TRandom.h"
#include "TStyle.h"
#include "TPad.h"
#include "TCanvas.h"
#include "TPostScript.h"
#include "TGaxis.h"
#include "TAxis.h"

using namespace std;

int main() {
  // Load style libraries
  gStyle->SetPadBottomMargin(0.14);
  gStyle->SetPadTopMargin(0.09);
  gStyle->SetPadLeftMargin(0.14);
  gStyle->SetPadRightMargin(0.14);
  //Styles for the statistic box
  gStyle->SetOptFit(1111);
  gStyle->SetOptStat(0);
  TGaxis::SetMaxDigits(3);

  TH1F * h1 = new TH1F("h1","h1",40,-10.,10); // 1-D histogram with float
  // Arguments: name, title, bin no, xmin, xmax

  TH2F * h2 = new TH2F("h2","h2",40,-10.,10,80,-20.,20); // 2-D histogram with float
  // Arguments: name, title, x bin no, xmin, xmax, y bin no, ymin, ymax,


  TCanvas *c1 = new TCanvas("c1","c1",900,1200);
  c1->Divide(1,2);		// Divide into 1x2 pads

  //save the results later in a ps file
  TPostScript *pss = new TPostScript("Ex11_histograms.ps",111);
  pss->NewPage();

  for(int ij=0;ij<10000000;ij++) {	// Filling the histograms with 10000000 no of Gaussian Distribution
    h1->Fill(gRandom->Gaus(0.,3.));	// 1-D
    h2->Fill(gRandom->Gaus(0.,3.),gRandom->Gaus(0.,7.)); // 2-D
  }

  // set plotting parameters like (axis name, titles, offset,.......)
  h1->SetTitle("TH1F Plot");
  h1->GetXaxis()->SetTitle("X Axis");
  h1->GetXaxis()->SetTitleOffset(1.4);
  h1->GetXaxis()->CenterTitle();
  h1->GetYaxis()->SetTitle("Frequency");
  h1->GetYaxis()->SetTitleOffset(1.4);
  h1->GetYaxis()->CenterTitle();

  h2->GetXaxis()->SetTitle("X Axis");
  h2->GetXaxis()->SetTitleOffset(1.4);
  h2->GetXaxis()->CenterTitle();
  h2->GetYaxis()->SetTitle("Y Axis");
  h2->GetYaxis()->SetTitleOffset(1.4);
  h2->GetYaxis()->CenterTitle();
  h2->GetZaxis()->SetTitle("Frequency");
  h2->GetZaxis()->SetTitleOffset(1.4);
  h2->GetZaxis()->CenterTitle();

  pss->NewPage();

  c1->cd(1);
  h1->Draw();
  c1->cd(2);
  h2->SetTitle("COLZ Plot: With Colour/Frequency (Z) Side Bar");
  // I will use the Function Draw with two options ("COLZ" to get 2d plot and "LEGO" to get a 3d histogram)
  h2->Draw("COLZ");
  c1->Update();

  pss->NewPage();

  c1->cd(1);
  h2->SetTitle("LEGO Plot");
  h2->Draw("LEGO");
  c1->Update();

  pss->Close();

  return 0;

}
