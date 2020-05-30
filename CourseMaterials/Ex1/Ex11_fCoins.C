{
TFile *fcoins = new TFile("coins.root", "New");
TCanvas *mc = new TCanvas("mc"," mass canvas");
TH1F* hmass = new TH1F("mass","mass distribution;mass (g)",10,0,100);
float masses[20]={36,25,38,46,55,68,72,55,36,38,67,45,22,48,91,46,52,61,58,55};
for (int i=0; i<20; ++i) hmass->Fill(masses[i]);
hmass->Draw();
mc->Modified();
mc->Update();
TDirectory *directory = fcoins->mkdir("RandomMass");
TCanvas *rmc = new TCanvas("rmc","random mass canvas");
TH1F* hrmass = new TH1F("random mass","mass distribution [gauss];mass (g)",100,0,100);
for (int i=0; i<20000; ++i) hrmass->Fill(gRandom->Gaus(40.,2.));
hrmass->Draw();
rmc->Modified();
rmc->Update();
directory->Append(rmc);
fcoins->Write();
fcoins->Close();
}
