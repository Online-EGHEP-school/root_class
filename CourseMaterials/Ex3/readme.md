# Working With Simulated data
This is a simple example of analysing a simulated LHC data using C++. It is based on two samples:
1. ZH production, with Z→μμ and H→bb (the signal),
2. Zbb production with Z→ee (the background).
The aim of this excercise is to find similarities and differences between the signal and background events, by making histograms of various quantities.

## Analysis code and dataset
The analysis code hirarchy is as follow:
Ex3
 |-analysis.cpp
 |-analysis.h
 |-plot.cpp 
In addition, two files represents signal (**H_events.root**)nd background (**Zbb_events.root**) are also exist.
## About code
The main file to edit will be analysis.cpp. This code loops over all the events in the file:
```
for (Long64_t jentry=0; jentry<nentries;jentry++){
```
Inside this loop, it loops over all the particles in each event:
```
for(int i=0; i<_pdgid.size();i++) {
```
and it looks for stable particles *(if( _status[i]==1))* that are muons *(if(_pdgid[i]==13))*. A full list of particle ID codes is [available here](http://pdg.lbl.gov/2002/montecarlorpp.pdf).
Further down, the code makes the combined dimuon 4-vector *(TLorentzVector sum = v1 + v2;)* and fills the histogram with the invariant mass of this new 4-vector.
## Main Excercise
Here are some good exercises. After making changes to the code, you will need to recompile (make), fixing any compilation errors, before you can run the updated code.
1) Add some more histograms. The histogram is declared near the top of the code:
TH1 * h_mass = new TH1F("mass", "mass", 100,0,300);
which has 100 bins, between 0 and 300. Some interesting things to plot: the number of muons per event; the muon transverse momentum (pT), muon rapidity (y), dimuon rapidity, dimuon pT.2) Modify the code to find b quarks and b antiquarks (pdgid 5 and -5) - note that b-quarks will not have status 1! Then make similar plots to the muons: number of b-quarks, b and anti-b combined mass, etc.3) Look at the reconstructed jets in the event, stored in a vector _jets. Try matching jets to b-quarks, based on ΔR (see here, for example.) Plot the ΔR distribution, then require a jet to be with, for example ΔR<0.4 of a b-quark. After matching a jet to the b-quark and b-antiquark, plot the mass of the combined jets.
## Fitting
Finally, it is quite often worth fitting a parametric curve to the data. This code is a basic fitting example provided by the root authors. You could try including this into the plot.cpp code and fitting the dimuon mass distribution.
