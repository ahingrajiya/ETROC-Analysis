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
    TFile *f_inLeft = TFile::Open("/home/abhishek/analysis/etroc_analysis/ETROC2/build/oReadEtroc2_4Boards_LeftSide.root");
    TFile *f_inRight = TFile::Open("/home/abhishek/analysis/etroc_analysis/ETROC2/build/oReadEtroc2_4Boards_RightSide.root");

    Bool_t isCode = kFALSE;
    Bool_t isActual = kTRUE;

    TProfile *DTOA01Code_TOTCode0_L = (TProfile *)f_inLeft->Get("Board0/pDTOA01CodevsTOTCode0");
    TProfile *DTOA02Code_TOTCode0_L = (TProfile *)f_inLeft->Get("Board0/pDTOA02CodevsTOTCode0");
    TProfile *DTOA03Code_TOTCode0_L = (TProfile *)f_inLeft->Get("Board0/pDTOA03CodevsTOTCode0");

    TProfile *DTOA01Code_TOTCode0_R = (TProfile *)f_inRight->Get("Board0/pDTOA01CodevsTOTCode0");
    TProfile *DTOA02Code_TOTCode0_R = (TProfile *)f_inRight->Get("Board0/pDTOA02CodevsTOTCode0");
    TProfile *DTOA03Code_TOTCode0_R = (TProfile *)f_inRight->Get("Board0/pDTOA03CodevsTOTCode0");

    TProfile *DTOA01Code_TOTCode1_L = (TProfile *)f_inLeft->Get("Board1/pDTOA01CodevsTOTCode1");
    TProfile *DTOA12Code_TOTCode1_L = (TProfile *)f_inLeft->Get("Board1/pDTOA12CodevsTOTCode1");
    TProfile *DTOA13Code_TOTCode1_L = (TProfile *)f_inLeft->Get("Board1/pDTOA13CodevsTOTCode1");

    TProfile *DTOA01Code_TOTCode1_R = (TProfile *)f_inRight->Get("Board1/pDTOA01CodevsTOTCode1");
    TProfile *DTOA12Code_TOTCode1_R = (TProfile *)f_inRight->Get("Board1/pDTOA12CodevsTOTCode1");
    TProfile *DTOA13Code_TOTCode1_R = (TProfile *)f_inRight->Get("Board1/pDTOA13CodevsTOTCode1");

    TProfile *DTOA02Code_TOTCode2_L = (TProfile *)f_inLeft->Get("Board2/pDTOA02CodevsTOTCode2");
    TProfile *DTOA12Code_TOTCode2_L = (TProfile *)f_inLeft->Get("Board2/pDTOA12CodevsTOTCode2");
    TProfile *DTOA23Code_TOTCode2_L = (TProfile *)f_inLeft->Get("Board2/pDTOA23CodevsTOTCode2");

    TProfile *DTOA02Code_TOTCode2_R = (TProfile *)f_inRight->Get("Board2/pDTOA02CodevsTOTCode2");
    TProfile *DTOA12Code_TOTCode2_R = (TProfile *)f_inRight->Get("Board2/pDTOA12CodevsTOTCode2");
    TProfile *DTOA23Code_TOTCode2_R = (TProfile *)f_inRight->Get("Board2/pDTOA23CodevsTOTCode2");

    TProfile *DTOA03Code_TOTCode3_L = (TProfile *)f_inLeft->Get("Board3/pDTOA03CodevsTOTCode3");
    TProfile *DTOA13Code_TOTCode3_L = (TProfile *)f_inLeft->Get("Board3/pDTOA13CodevsTOTCode3");
    TProfile *DTOA23Code_TOTCode3_L = (TProfile *)f_inLeft->Get("Board3/pDTOA23CodevsTOTCode3");

    TProfile *DTOA03Code_TOTCode3_R = (TProfile *)f_inRight->Get("Board3/pDTOA03CodevsTOTCode3");
    TProfile *DTOA13Code_TOTCode3_R = (TProfile *)f_inRight->Get("Board3/pDTOA13CodevsTOTCode3");
    TProfile *DTOA23Code_TOTCode3_R = (TProfile *)f_inRight->Get("Board3/pDTOA23CodevsTOTCode3");

    TF1 *DTOACode_TOTCode_Fit = new TF1("DTOACode_TOTCode_Fit", "pol2", 40.0, 160.0);
    TF1 *DTOACode_TOTCode_Fit_Pol3 = new TF1("DTOACode_TOTCode_Fit_Pol3", "pol3", 40.0, 160.0);

    if (isCode)
    {
        cout << "==============================" << endl;
        cout << "        Right Side Code       " << endl;
        cout << "==============================" << endl;

        cout << "==============================" << endl;
        cout << "          DTOA 01_0 Code           " << endl;
        cout << "==============================" << endl;
        DTOA01Code_TOTCode0_R->Fit("DTOACode_TOTCode_Fit", "SRME", "", 94.0, 141.0);

        cout << "==============================" << endl;
        cout << "          DTOA 02_0 Code          " << endl;
        cout << "==============================" << endl;
        DTOA02Code_TOTCode0_R->Fit("DTOACode_TOTCode_Fit", "SRME", "", 94.0, 141.0);

        cout << "==============================" << endl;
        cout << "          DTOA 03_0 Code          " << endl;
        cout << "==============================" << endl;
        DTOA03Code_TOTCode0_R->Fit("DTOACode_TOTCode_Fit", "SRME", "", 94.0, 141.0);

        cout << "==============================" << endl;
        cout << "          DTOA 01_1 Code          " << endl;
        cout << "==============================" << endl;
        DTOA01Code_TOTCode1_R->Fit("DTOACode_TOTCode_Fit", "SRME", "", 87.0, 127.0);

        cout << "==============================" << endl;
        cout << "          DTOA 12_1 Code          " << endl;
        cout << "==============================" << endl;
        DTOA12Code_TOTCode1_R->Fit("DTOACode_TOTCode_Fit", "SRME", "", 87.0, 127.0);

        cout << "==============================" << endl;
        cout << "          DTOA 13_1 Code          " << endl;
        cout << "==============================" << endl;
        DTOA13Code_TOTCode1_R->Fit("DTOACode_TOTCode_Fit", "SRME", "", 87.0, 127.0);

        cout << "==============================" << endl;
        cout << "          DTOA 02_2 Code          " << endl;
        cout << "==============================" << endl;
        DTOA02Code_TOTCode2_R->Fit("DTOACode_TOTCode_Fit", "SRME", "", 67.0, 119.0);

        cout << "==============================" << endl;
        cout << "          DTOA 12_2 Code          " << endl;
        cout << "==============================" << endl;
        DTOA12Code_TOTCode2_R->Fit("DTOACode_TOTCode_Fit", "SRME", "", 67.0, 119.0);

        cout << "==============================" << endl;
        cout << "          DTOA 23_2 Code          " << endl;
        cout << "==============================" << endl;
        DTOA23Code_TOTCode2_R->Fit("DTOACode_TOTCode_Fit", "SRME", "", 67.0, 119.0);

        cout << "==============================" << endl;
        cout << "          DTOA 03_3 Code          " << endl;
        cout << "==============================" << endl;
        DTOA03Code_TOTCode3_R->Fit("DTOACode_TOTCode_Fit_Pol3", "SRME", "", 74.0, 121.0);

        cout << "==============================" << endl;
        cout << "          DTOA 13_3 Code          " << endl;
        cout << "==============================" << endl;
        DTOA13Code_TOTCode3_R->Fit("DTOACode_TOTCode_Fit_Pol3", "SRME", "", 74.0, 121.0);

        cout << "==============================" << endl;
        cout << "          DTOA 23_3 Code          " << endl;
        cout << "==============================" << endl;
        DTOA23Code_TOTCode3_R->Fit("DTOACode_TOTCode_Fit", "SRME", "", 74.0, 121.0);

        cout << "==============================" << endl;
        cout << "        Left Side Code            " << endl;
        cout << "==============================" << endl;

        cout << "==============================" << endl;
        cout << "          DTOA 01_0 Code          " << endl;
        cout << "==============================" << endl;
        DTOA01Code_TOTCode0_L->Fit("DTOACode_TOTCode_Fit", "SRME", "", 111.0, 150.0);

        cout << "==============================" << endl;
        cout << "          DTOA 02_0 Code          " << endl;
        cout << "==============================" << endl;
        DTOA02Code_TOTCode0_L->Fit("DTOACode_TOTCode_Fit", "SRME", "", 111.0, 150.0);

        cout << "==============================" << endl;
        cout << "          DTOA 03_0 Code          " << endl;
        cout << "==============================" << endl;
        DTOA03Code_TOTCode0_L->Fit("DTOACode_TOTCode_Fit", "SRME", "", 111.0, 150.0);

        cout << "==============================" << endl;
        cout << "          DTOA 01_1 Code          " << endl;
        cout << "==============================" << endl;
        DTOA01Code_TOTCode1_L->Fit("DTOACode_TOTCode_Fit", "SRME", "", 106.0, 140.0);

        cout << "==============================" << endl;
        cout << "          DTOA 12_1 Code          " << endl;
        cout << "==============================" << endl;
        DTOA12Code_TOTCode1_L->Fit("DTOACode_TOTCode_Fit", "SRME", "", 106.0, 140.0);

        cout << "==============================" << endl;
        cout << "          DTOA 13_1 Code          " << endl;
        cout << "==============================" << endl;
        DTOA13Code_TOTCode1_L->Fit("DTOACode_TOTCode_Fit", "SRME", "", 106.0, 140.0);

        cout << "==============================" << endl;
        cout << "          DTOA 02_2 Code          " << endl;
        cout << "==============================" << endl;
        DTOA02Code_TOTCode2_L->Fit("DTOACode_TOTCode_Fit_Pol3", "SRME", "", 82.0, 139.0);

        cout << "==============================" << endl;
        cout << "          DTOA 12_2 Code          " << endl;
        cout << "==============================" << endl;
        DTOA12Code_TOTCode2_L->Fit("DTOACode_TOTCode_Fit", "SRME", "", 82.0, 139.0);

        cout << "==============================" << endl;
        cout << "          DTOA 23_2 Code          " << endl;
        cout << "==============================" << endl;
        DTOA23Code_TOTCode2_L->Fit("DTOACode_TOTCode_Fit", "SRME", "", 82.0, 139.0);

        cout << "==============================" << endl;
        cout << "          DTOA 03_3 Code          " << endl;
        cout << "==============================" << endl;
        DTOA03Code_TOTCode3_L->Fit("DTOACode_TOTCode_Fit", "SRME", "", 83.0, 140.0);

        cout << "==============================" << endl;
        cout << "          DTOA 13_3 Code          " << endl;
        cout << "==============================" << endl;
        DTOA13Code_TOTCode3_L->Fit("DTOACode_TOTCode_Fit", "SRME", "", 83.0, 140.0);

        cout << "==============================" << endl;
        cout << "          DTOA 23_3 Code          " << endl;
        cout << "==============================" << endl;
        DTOA23Code_TOTCode3_L->Fit("DTOACode_TOTCode_Fit", "SRME", "", 83.0, 140.0);
    }

    TProfile *DTOA01_TOT0_L = (TProfile *)f_inLeft->Get("Board0/pDTOA01vsTOT0");
    TProfile *DTOA02_TOT0_L = (TProfile *)f_inLeft->Get("Board0/pDTOA02vsTOT0");
    TProfile *DTOA03_TOT0_L = (TProfile *)f_inLeft->Get("Board0/pDTOA03vsTOT0");

    TProfile *DTOA01_TOT0_R = (TProfile *)f_inRight->Get("Board0/pDTOA01vsTOT0");
    TProfile *DTOA02_TOT0_R = (TProfile *)f_inRight->Get("Board0/pDTOA02vsTOT0");
    TProfile *DTOA03_TOT0_R = (TProfile *)f_inRight->Get("Board0/pDTOA03vsTOT0");

    TProfile *DTOA01_TOT1_L = (TProfile *)f_inLeft->Get("Board1/pDTOA01vsTOT1");
    TProfile *DTOA12_TOT1_L = (TProfile *)f_inLeft->Get("Board1/pDTOA12vsTOT1");
    TProfile *DTOA13_TOT1_L = (TProfile *)f_inLeft->Get("Board1/pDTOA13vsTOT1");

    TProfile *DTOA01_TOT1_R = (TProfile *)f_inRight->Get("Board1/pDTOA01vsTOT1");
    TProfile *DTOA12_TOT1_R = (TProfile *)f_inRight->Get("Board1/pDTOA12vsTOT1");
    TProfile *DTOA13_TOT1_R = (TProfile *)f_inRight->Get("Board1/pDTOA13vsTOT1");

    TProfile *DTOA02_TOT2_L = (TProfile *)f_inLeft->Get("Board2/pDTOA02vsTOT2");
    TProfile *DTOA12_TOT2_L = (TProfile *)f_inLeft->Get("Board2/pDTOA12vsTOT2");
    TProfile *DTOA23_TOT2_L = (TProfile *)f_inLeft->Get("Board2/pDTOA23vsTOT2");

    TProfile *DTOA02_TOT2_R = (TProfile *)f_inRight->Get("Board2/pDTOA02vsTOT2");
    TProfile *DTOA12_TOT2_R = (TProfile *)f_inRight->Get("Board2/pDTOA12vsTOT2");
    TProfile *DTOA23_TOT2_R = (TProfile *)f_inRight->Get("Board2/pDTOA23vsTOT2");

    TProfile *DTOA03_TOT3_L = (TProfile *)f_inLeft->Get("Board3/pDTOA03vsTOT3");
    TProfile *DTOA13_TOT3_L = (TProfile *)f_inLeft->Get("Board3/pDTOA13vsTOT3");
    TProfile *DTOA23_TOT3_L = (TProfile *)f_inLeft->Get("Board3/pDTOA23vsTOT3");

    TProfile *DTOA03_TOT3_R = (TProfile *)f_inRight->Get("Board3/pDTOA03vsTOT3");
    TProfile *DTOA13_TOT3_R = (TProfile *)f_inRight->Get("Board3/pDTOA13vsTOT3");
    TProfile *DTOA23_TOT3_R = (TProfile *)f_inRight->Get("Board3/pDTOA23vsTOT3");

    TF1 *DTOA_TOT_Fit = new TF1("DTOA_TOT_Fit", "pol2", 0.0, 6.20);
    TF1 *DTOA_TOT_Fit_Pol3 = new TF1("DTOA_TOT_Fit_Pol3", "pol3", 0.0, 6.20);

    if (isActual)
    {
        cout << "==============================" << endl;
        cout << "        Right Side            " << endl;
        cout << "==============================" << endl;

        cout << "==============================" << endl;
        cout << "          DTOA 01_0           " << endl;
        cout << "==============================" << endl;
        DTOA01_TOT0_R->Fit("DTOA_TOT_Fit", "SRME", "", 3.5, 5.4);

        cout << "==============================" << endl;
        cout << "          DTOA 02_0           " << endl;
        cout << "==============================" << endl;
        DTOA02_TOT0_R->Fit("DTOA_TOT_Fit", "SRME", "", 3.5, 5.4);

        cout << "==============================" << endl;
        cout << "          DTOA 03_0           " << endl;
        cout << "==============================" << endl;
        DTOA03_TOT0_R->Fit("DTOA_TOT_Fit", "SRME", "", 3.5, 5.4);

        cout << "==============================" << endl;
        cout << "          DTOA 01_1           " << endl;
        cout << "==============================" << endl;
        DTOA01_TOT1_R->Fit("DTOA_TOT_Fit", "SRME", "", 3.5, 5.3);

        cout << "==============================" << endl;
        cout << "          DTOA 12_1           " << endl;
        cout << "==============================" << endl;
        DTOA12_TOT1_R->Fit("DTOA_TOT_Fit", "SRME", "", 3.5, 5.3);

        cout << "==============================" << endl;
        cout << "          DTOA 13_1           " << endl;
        cout << "==============================" << endl;
        DTOA13_TOT1_R->Fit("DTOA_TOT_Fit", "SRME", "", 3.5, 5.3);

        cout << "==============================" << endl;
        cout << "          DTOA 02_2           " << endl;
        cout << "==============================" << endl;
        DTOA02_TOT2_R->Fit("DTOA_TOT_Fit", "SRME", "", 2.6, 4.9);

        cout << "==============================" << endl;
        cout << "          DTOA 12_2           " << endl;
        cout << "==============================" << endl;
        DTOA12_TOT2_R->Fit("DTOA_TOT_Fit", "SRME", "", 2.6, 4.9);

        cout << "==============================" << endl;
        cout << "          DTOA 23_2           " << endl;
        cout << "==============================" << endl;
        DTOA23_TOT2_R->Fit("DTOA_TOT_Fit", "SRME", "", 2.6, 4.9);

        cout << "==============================" << endl;
        cout << "          DTOA 03_3           " << endl;
        cout << "==============================" << endl;
        DTOA03_TOT3_R->Fit("DTOA_TOT_Fit", "SRME", "", 2.9, 5.0);

        cout << "==============================" << endl;
        cout << "          DTOA 13_3           " << endl;
        cout << "==============================" << endl;
        DTOA13_TOT3_R->Fit("DTOA_TOT_Fit", "SRME", "", 2.9, 5.0);

        cout << "==============================" << endl;
        cout << "          DTOA 23_3           " << endl;
        cout << "==============================" << endl;
        DTOA23_TOT3_R->Fit("DTOA_TOT_Fit", "SRME", "", 2.9, 5.0);

        cout << "==============================" << endl;
        cout << "        Left Side             " << endl;
        cout << "==============================" << endl;

        cout << "==============================" << endl;
        cout << "          DTOA 01_0           " << endl;
        cout << "==============================" << endl;
        DTOA01_TOT0_L->Fit("DTOA_TOT_Fit", "SRME", "", 3.6, 5.1);

        cout << "==============================" << endl;
        cout << "          DTOA 02_0           " << endl;
        cout << "==============================" << endl;
        DTOA02_TOT0_L->Fit("DTOA_TOT_Fit", "SRME", "", 3.6, 5.1);

        cout << "==============================" << endl;
        cout << "          DTOA 03_0           " << endl;
        cout << "==============================" << endl;
        DTOA03_TOT0_L->Fit("DTOA_TOT_Fit", "SRME", "", 3.6, 5.1);

        cout << "==============================" << endl;
        cout << "          DTOA 01_1           " << endl;
        cout << "==============================" << endl;
        DTOA01_TOT1_L->Fit("DTOA_TOT_Fit", "SRME", "", 3.7, 5.0);

        cout << "==============================" << endl;
        cout << "          DTOA 12_1           " << endl;
        cout << "==============================" << endl;
        DTOA12_TOT1_L->Fit("DTOA_TOT_Fit", "SRME", "", 3.7, 5.0);

        cout << "==============================" << endl;
        cout << "          DTOA 13_1           " << endl;
        cout << "==============================" << endl;
        DTOA13_TOT1_L->Fit("DTOA_TOT_Fit", "SRME", "", 3.7, 5.0);

        cout << "==============================" << endl;
        cout << "          DTOA 02_2           " << endl;
        cout << "==============================" << endl;
        DTOA02_TOT2_L->Fit("DTOA_TOT_Fit", "SRME", "", 2.7, 4.8);

        cout << "==============================" << endl;
        cout << "          DTOA 12_2           " << endl;
        cout << "==============================" << endl;
        DTOA12_TOT2_L->Fit("DTOA_TOT_Fit", "SRME", "", 2.7, 4.8);

        cout << "==============================" << endl;
        cout << "          DTOA 23_2           " << endl;
        cout << "==============================" << endl;
        DTOA23_TOT2_L->Fit("DTOA_TOT_Fit", "SRME", "", 2.7, 4.8);

        cout << "==============================" << endl;
        cout << "          DTOA 03_3           " << endl;
        cout << "==============================" << endl;
        DTOA03_TOT3_L->Fit("DTOA_TOT_Fit", "SRME", "", 2.8, 5.0);

        cout << "==============================" << endl;
        cout << "          DTOA 13_3           " << endl;
        cout << "==============================" << endl;
        DTOA13_TOT3_L->Fit("DTOA_TOT_Fit", "SRME", "", 2.8, 5.0);

        cout << "==============================" << endl;
        cout << "          DTOA 23_3           " << endl;
        cout << "==============================" << endl;
        DTOA23_TOT3_L->Fit("DTOA_TOT_Fit", "SRME", "", 2.8, 5.0);
    }
    // TFile *f_out = TFile::Open("oFitResult4Boards_DTOA.root", "RECREATE");
    // gDirectory->mkdir("LeftSide");
    // gDirectory->cd("LeftSide");

    // gDirectory->cd("../");
    // gDirectory->mkdir("RightSide");
    // gDirectory->cd("RightSide");

    // f_out->Write();
    // f_out->Close();

    return 0;
}