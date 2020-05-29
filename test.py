import numpy as np
import os
from analysis import rootUtils
import ROOT
from ROOT import TCanvas, TPad, TFormula, TF1, TPaveLabel, TH1F, TFile, TH1D, gROOT, gBenchmark
import matplotlib.pyplot as plt

rootdir = os.path.dirname(os.path.abspath(__file__))
ro = rootUtils.RootUtils()
file = rootdir+"/test_files/gammaSpectrum_RD53.root"
histogram = "53"
Entries = []
f = ROOT.TFile(file)
t = f.Get(histogram)
Entries = t.GetEntries()
t.Draw()
data, x = ro.readHistogram(file, t, False)
entries = np.nonzero(data)
plt.plot(x[1:], data[1:])
plt.show()
