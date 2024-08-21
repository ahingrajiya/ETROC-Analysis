#include "TChain.h"
#include "TFile.h"
#include "TROOT.h"
#include "TTree.h"
#include "TString.h"
#include "TLatex.h"
#include "TH1.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TH2.h"
#include "TH2F.h"
#include "TH2D.h"
#include "TSystem.h"
#include "TCanvas.h"
#include "TProfile.h"
#include "TF1.h"

// C++ headers
#include <iostream>
#include <vector>

Int_t status = gSystem->Load("/home/abhi/etroc_analysis/ETROC2/build/libETROC2.dylib");

using namespace std;

#if ROOT_VERSION_CODE >= ROOT_VERSION(6, 0, 0)
R__LOAD_LIBRARY(build / libETROC2.dylib);
#endif

int main(int argc, char const *argv[])
{
    TFile *f_in = TFile::Open("/home/abhi/etroc_analysis/ETROC2/build/oReadEtroc2.root");

    TProfile *DTOA_TOT0_Code = (TProfile *)f_in->Get("pDTOA_CodevsTOT_Code_0");
    TProfile *DTOA_TOT1_Code = (TProfile *)f_in->Get("pDTOA_CodevsTOT_Code_1");

    TProfile *DTOA_TOT0 = (TProfile *)f_in->Get("pDTOAvsTOT_0");
    TProfile *DTOA_TOT1 = (TProfile *)f_in->Get("pDTOAvsTOT_1");

    TH1D *DTOA_Code = (TH1D *)f_in->Get("h3");
    DTOA_Code->Rebin(2);
    TH1D *DTOA_Code_Corrected = (TH1D *)f_in->Get("h4");
    TH1D *DTOA_Code_Corrected0 = (TH1D *)f_in->Get("h5");
    TH1D *DTOA_Code_Corrected1 = (TH1D *)f_in->Get("h6");

    TH1D *DTOA = (TH1D *)f_in->Get("h7");
    TH1D *DTOA_Corrected = (TH1D *)f_in->Get("h8");
    TH1D *DTOA_Corrected0 = (TH1D *)f_in->Get("h9");
    TH1D *DTOA_Corrected1 = (TH1D *)f_in->Get("h10");

    TF1 *DTOA_TOT_Code_Fit = new TF1("DTOA_TOT_Code_Fit", "pol5", 40.0, 160.0);
    DTOA_TOT0_Code->Fit("DTOA_TOT_Code_Fit", "", "", 40.0, 160.0);
    DTOA_TOT1_Code->Fit("DTOA_TOT_Code_Fit", "", "", 40.0, 160.0);

    TF1 *DTOA_TOT_Fit = new TF1("DTOA_TOT_Fit", "pol8", 0.0, 6.20);
    DTOA_TOT0->Fit("DTOA_TOT_Fit", "", "", 1.1, 6.2);
    DTOA_TOT1->Fit("DTOA_TOT_Fit", "", "", 1.1, 6.2);

    TF1 *DTOA_Fit = new TF1("DTOA_Fit", "gaus", -100.0, 100.0);
    DTOA_Code->Fit("DTOA_Fit", "", "", -60.0, 60.0);
    DTOA_Code_Corrected->Fit("DTOA_Fit", "", "", -60.0, 60.0);
    DTOA_Code_Corrected0->Fit("DTOA_Fit", "", "", -60.0, 60.0);
    DTOA_Code_Corrected1->Fit("DTOA_Fit", "", "", -60.0, 60.0);

    DTOA->Fit("DTOA_Fit", "", "", -1.5, 1.5);
    DTOA_Corrected->Fit("DTOA_Fit", "", "", -1.5, 1.5);
    DTOA_Corrected0->Fit("DTOA_Fit", "", "", -1.5, 1.5);
    DTOA_Corrected1->Fit("DTOA_Fit", "", "", -1.5, 1.5);

    TFile *f_out = TFile::Open("oFitResult.root", "RECREATE");
    DTOA_TOT0_Code->Write();
    DTOA_TOT1_Code->Write();
    DTOA_TOT0->Write();
    DTOA_TOT1->Write();
    DTOA_Code->Write();
    DTOA_Code_Corrected->Write();
    DTOA_Code_Corrected0->Write();
    DTOA_Code_Corrected1->Write();
    DTOA->Write();
    DTOA_Corrected->Write();
    DTOA_Corrected0->Write();
    DTOA_Corrected1->Write();
    f_out->Write();
    f_out->Close();

    return 0;
}