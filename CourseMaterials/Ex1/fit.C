void fit()
{//Use the randomly generated gaussian distribution as data, perform fit with a gaussian function and inspect the parameters (write a simple macro: fit.C):
        // style setting
        gROOT->SetStyle("Plain");
        gStyle->SetOptFit(111111);
        gStyle->SetFrameBorderMode(0);
        gStyle->SetFillColor(0);
        gStyle->SetCanvasColor(0);
        gStyle->SetFrameFillColor(0);
        gStyle->SetCanvasBorderMode(0);

        // create a random number generator
        gRandom = new TRandom3();

        // create a histogram 
        TH1D * hist = new TH1D("data", "; x; N", 50, 0.0, 100.0);

        // fill in the histogram
        for (int i = 0; i < 10000; ++i)
                hist->Fill(gRandom->Gaus(65.0, 5.0));


        // define a fit function = gauss
        TF1 * f1 = new TF1("gauss", "[0] / sqrt(2.0 * TMath::Pi()) / [2] * exp(-(x-[1])*(x-[1])/2./[2]/[2])", 0, 100);

        //set parameter start values (mandatory). 
        f1->SetParNames("Constant","Mean","Sigma");
        f1->SetParameters(700.,hist->GetMean(),hist->GetRMS());
        //f1->SetParLimits(0,  100.0, 700.0);
        f1->SetParLimits(1, 50.0,  80.0);
        //f1->SetParLimits(2,  0.1,  10.0);
        f1->SetLineWidth(2);
        f1->SetLineColor(kRed);
        // create a canvas to draw the histogram
        TCanvas * c1= new TCanvas("c1", "fitted data",5,5,800,600);
        // perform fit
        hist->Fit("gauss");
        hist->Draw();
        hist->SaveAs("fit.png");
}
