#include "TMath.h" 
#include "TROOT.h" 
#include "TStyle.h" 
#include "TFile.h"
#include "TAxis.h"
#include "TPostScript.h"
#include "TProfile.h"
#include <map>
#include <set>
#include <TROOT.h>
#include "TCanvas.h"
#include "TGClient.h"
#include "TProfile.h"
#include "TLegend.h"
#include "TROOT.h"
#include "TVirtualPad.h"
// Headers and Namespaces.
#include "Pythia8/Pythia.h" // Include Pythia headers.
#include "TH1.h" // ROOT, for histogramming.
#include "TVirtualPad.h" // ROOT, for interactive graphics.
#include "TApplication.h"
#include "TFile.h" // ROOT, for saving file.
#include "TLorentzVector.h"
#include <vector>
//Libraries for PDF

using namespace Pythia8;
using namespace std;
	int Dau1,Dau2,GDau1,GDau2,REC=0,GEN=0;
	unsigned iflag1 = -10,iflag2 = -10,iGflag1 = -10,iGflag2 = -10;
	Vec4 G1,G2,GENG1,GENG2,AG1,AG2,mGEN;
	int idGENDau1,idGENDau2,idRecoDau1,idRecoDau2,idADau1,idADau2;
	float pxGENGama1,pyGENGama1,pzGENGama1,EnGENGama1,EtaGENGama1,PhiGENGama1,pTGENGama1; 
	float pxGENGama2,pyGENGama2,pzGENGama2,EnGENGama2,EtaGENGama2,PhiGENGama2,pTGENGama2;
	float pxRecoGama1,pyRecoGama1,pzRecoGama1,EnRecoGama1,EtaRecoGama1,PhiRecoGama1,pTRecoGama1; 
	float pxRecoGama2,pyRecoGama2,pzRecoGama2,EnRecoGama2,EtaRecoGama2,PhiRecoGama2,pTRecoGama2;
	float pxAGama1,pyAGama1,pzAGama1,EnAGama1,EtaAGama1,phiAGama1,pTAGama1; 
	float pxAGama2,pyAGama2,pzAGama2,EnAGama2,EtaAGama2,phiAGama2,pTAGama2; 
        float mGENMass,mRecoMass,mAMass,mRecoPT,MaxRecoM,sqrtmRecoMass;
	 int iH;


