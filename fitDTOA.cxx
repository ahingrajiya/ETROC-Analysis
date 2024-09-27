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

Int_t status = gSystem->Load("/home/abhishek/analysis/etroc_analysis/ETROC2/build/libETROC2.dylib");

using namespace std;

#if ROOT_VERSION_CODE >= ROOT_VERSION(6, 0, 0)
R__LOAD_LIBRARY(build / libETROC2.dylib);
#endif

int main(int argc, char const *argv[])
{
    TFile *f_inLeft = TFile::Open("/home/abhishek/analysis/etroc_analysis/ETROC2/build/oReadEtroc2_LeftSide_Mean.root");
    TFile *f_inRight = TFile::Open("/home/abhishek/analysis/etroc_analysis/ETROC2/build/oReadEtroc2_RightSide_Mean.root");

    TProfile *DTOA_TOT0_Code_L = (TProfile *)f_inLeft->Get("pDTOACodevsTOTCode_B0");
    TProfile *DTOA_TOT1_Code_L = (TProfile *)f_inLeft->Get("pDTOACodevsTOTCode_B1");
    TProfile *DTOA_TOT0_L = (TProfile *)f_inLeft->Get("pDTOAvsTOT_B0");
    TProfile *DTOA_TOT1_L = (TProfile *)f_inLeft->Get("pDTOAvsTOT_B1");

    TProfile *DTOA_TOT0_Code_R = (TProfile *)f_inRight->Get("pDTOACodevsTOTCode_B0");
    TProfile *DTOA_TOT1_Code_R = (TProfile *)f_inRight->Get("pDTOACodevsTOTCode_B1");
    TProfile *DTOA_TOT0_R = (TProfile *)f_inRight->Get("pDTOAvsTOT_B0");
    TProfile *DTOA_TOT1_R = (TProfile *)f_inRight->Get("pDTOAvsTOT_B1");

    TF1 *DTOACode_TOTCode_Fit = new TF1("DTOACode_TOTCode_Fit", "pol2", 40.0, 160.0);
    TF1 *DTOA_TOT_Fit = new TF1("DTOA_TOT_Fit", "pol2", 0.0, 6.20);
    cout << "Left Side" << endl;
    cout << "Board0 Code Fit" << endl;
    DTOA_TOT0_Code_L->Fit("DTOACode_TOTCode_Fit", "SRME", "", 85.0, 120.0);
    cout << "Board1 Code Fit" << endl;
    DTOA_TOT1_Code_L->Fit("DTOACode_TOTCode_Fit", "SRME", "", 85.0, 120.0);

    cout << "Board0 Fit" << endl;
    DTOA_TOT0_L->Fit("DTOA_TOT_Fit", "SRME", "", 2.9, 4.1);
    cout << "Board1 Fit" << endl;
    DTOA_TOT1_L->Fit("DTOA_TOT_Fit", "SRME", "", 2.9, 4.1);

    cout << "Right Side" << endl;
    cout << "Board0 Code Fit" << endl;
    DTOA_TOT0_Code_R->Fit("DTOACode_TOTCode_Fit", "SRME", "", 85.0, 120.0);
    cout << "Board1 Code Fit" << endl;
    DTOA_TOT1_Code_R->Fit("DTOACode_TOTCode_Fit", "SRME", "", 85.0, 120.0);

    cout << "Board0 Fit" << endl;
    DTOA_TOT0_R->Fit("DTOA_TOT_Fit", "SRME", "", 3.1, 4.3);
    cout << "Board1 Fit" << endl;
    DTOA_TOT1_R->Fit("DTOA_TOT_Fit", "SRME", "", 3.15, 4.55);

    TF1 *DTOA_Fit = new TF1("DTOA_Fit", "gaus", -1.0, 1.0);

    cout << "DTOA Fits for Board0" << endl;
    TH1D *DTOA_C2_L = (TH1D *)f_inLeft->Get("hDTOA_C2_B0");
    TH1D *DTOA_TWC_C2_L = (TH1D *)f_inLeft->Get("hDTOA_TWC_C2_B0");
    TH1D *DTOA_TWC0_C2_L = (TH1D *)f_inLeft->Get("hDTOA_TWC0_C2_B0");
    TH1D *DTOA_TWC1_C2_L = (TH1D *)f_inLeft->Get("hDTOA_TWC1_C2_B0");

    DTOA_C2_L->Fit("DTOA_Fit", "SRME", "", -0.05, 0.4);
    DTOA_TWC_C2_L->Fit("DTOA_Fit", "SRME", "", -0.325, -0.075);
    DTOA_TWC0_C2_L->Fit("DTOA_Fit", "SRME", "", -0.2, 0.2);
    DTOA_TWC1_C2_L->Fit("DTOA_Fit", "SRME", "", -0.25, 0.25);

    cout << "DTOA Fits for Board1" << endl;
    TH1D *DTOA_C2_R = (TH1D *)f_inRight->Get("hDTOA_C2_B0");
    TH1D *DTOA_TWC_C2_R = (TH1D *)f_inRight->Get("hDTOA_TWC_C2_B0");
    TH1D *DTOA_TWC0_C2_R = (TH1D *)f_inRight->Get("hDTOA_TWC0_C2_B0");
    TH1D *DTOA_TWC1_C2_R = (TH1D *)f_inRight->Get("hDTOA_TWC1_C2_B0");

    DTOA_C2_R->Fit("DTOA_Fit", "SRME", "", -0.1, 0.425);
    DTOA_TWC_C2_R->Fit("DTOA_Fit", "SRME", "", -0.275, -0.05);
    DTOA_TWC0_C2_R->Fit("DTOA_Fit", "SRME", "", -0.25, 0.25);
    DTOA_TWC1_C2_R->Fit("DTOA_Fit", "SRME", "", -0.2, 0.2);

    TFile *f_out = TFile::Open("oFitResult_DTOA.root", "RECREATE");
    gDirectory->mkdir("LeftSide");
    gDirectory->cd("LeftSide");
    DTOA_TOT0_Code_L->Write();
    DTOA_TOT1_Code_L->Write();
    DTOA_TOT0_L->Write();
    DTOA_TOT1_L->Write();
    DTOA_C2_L->Write();
    DTOA_TWC_C2_L->Write();
    DTOA_TWC0_C2_L->Write();
    DTOA_TWC1_C2_L->Write();

    gDirectory->cd("../");
    gDirectory->mkdir("RightSide");
    gDirectory->cd("RightSide");
    DTOA_TOT0_Code_R->Write();
    DTOA_TOT1_Code_R->Write();
    DTOA_TOT0_R->Write();
    DTOA_TOT1_R->Write();
    DTOA_C2_R->Write();
    DTOA_TWC_C2_R->Write();
    DTOA_TWC0_C2_R->Write();
    DTOA_TWC1_C2_R->Write();

    f_out->Write();
    f_out->Close();

    return 0;
}