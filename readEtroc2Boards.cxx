// ROOT headers
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

// ETROC2 headers
#include "Hit.h"
using namespace std;

#if ROOT_VERSION_CODE >= ROOT_VERSION(6, 0, 0)
R__LOAD_LIBRARY(build / libETROC2.dylib);
#endif

//________________
int main(int argc, char const *argv[])
{
    TString InputFile = argv[0];
    Bool_t isLeftSide = argv[1];
    Bool_t isRightSide = argv[2];
    TString OutputFile = argv[3];

    // int readEtroc2Boards() {

    // const Char_t *inFileName = "/home/abhi/etroc_analysis/ETROC2/build/oEtroc2Trans.root";

    TFile *inFile = TFile::Open(Form("%s", InputFile.Data()));

    if (!inFile->IsOpen() || inFile->IsZombie())
    {
        std::cout << "[ERROR] File is opened or zombie" << std::endl;
        return 1;
    }

    //
    // Histograms
    //

    // TCanvas *canv = new TCanvas("canv","canv", 1200, 800);
    auto *h1 = new TH1D("h1", "h;TOT;Entries", 50, 0., 500.);
    h1->Sumw2();
    auto *h2 = new TH1D("h2", "Event", 10000, 0., 10000);
    h2->Sumw2();
    // auto *h3 = new TH1D("h3", "#DeltaTOA Code", 200, -100., 100.);
    // h3->Sumw2();
    // auto *h4 = new TH1D("h4", "#DeltaTOA Code after Correction", 200, -100., 100.);
    // h4->Sumw2();
    // auto *h5 = new TH1D("h5", "#DeltaTOA Code after Correction For Board 0", 200, -100., 100.);
    // h5->Sumw2();
    // auto *h6 = new TH1D("h6", "#DeltaTOA Code after Correction For Board 1", 200, -100., 100.);
    // h6->Sumw2();

    // auto *h7 = new TH1D("h7", "#DeltaTOA", 200, -2., 2.);
    // h7->Sumw2();
    // auto *h8 = new TH1D("h8", "#DeltaTOA after Correction", 200, -2., 2.);
    // h8->Sumw2();
    // auto *h9 = new TH1D("h9", "#DeltaTOA after Correction For Board 0", 200, -2., 2.);
    // h9->Sumw2();
    // auto *h10 = new TH1D("h10", "#DeltaTOA after Correction For Board 1", 200, -2., 2.);
    // h10->Sumw2();

    // auto *h11 = new TH1D("h11", "#DeltaTOA BC", 200, -2., 2.);
    // h11->Sumw2();

    // auto *h12 = new TH1D("h12", "#DeltaTOA AC", 200, -2., 2.);
    // h12->Sumw2();

    ///@brief Description of C0, C1 and C2
    /// C0 = No Selections
    /// C1 = TOA Selections Applied
    /// C2 = TOT and TOT and CAL Selections Applied

    TH2D *hDROWvsDCOL = new TH2D("hDROWvsDCOL", "DROW vs DCOL", 32, -16., 16., 32, -16., 16.);
    hDROWvsDCOL->Sumw2();

    TH2D *hTOA_Code1vsTOA_Code0_C0 = new TH2D("hTOA_Code1vsTOA_Code0_C0", "TOA Code vs. TOA Code;TOA Code #0;TOA Code #1", 750, 0., 750., 750, 0., 750.);
    hTOA_Code1vsTOA_Code0_C0->Sumw2();
    TH2D *hTOA_Code0vsTOA_Code1_Corrected_C0 = new TH2D("hTOA_Code1VsTOA_Code0_Corrected_C0", "TOA Code Corrected vs. TOA Code Corrected ;TOA Code #0;TOA Code #1", 750, 0., 750., 750, 0., 750.);
    hTOA_Code0vsTOA_Code1_Corrected_C0->Sumw2();

    TH2D *hTOA_Code1vsTOA_Code0_C1 = new TH2D("hTOA_Code1vsTOA_Code0_C1", "TOA Code vs. TOA Code;TOA Code #0;TOA Code #1", 750, 0., 750., 750, 0., 750.);
    hTOA_Code1vsTOA_Code0_C1->Sumw2();
    TH2D *hTOA_Code0vsTOA_Code1_Corrected_C1 = new TH2D("hTOA_Code1VsTOA_Code0_Corrected_C1", "TOA Code Corrected vs. TOA Code Corrected ;TOA Code #0;TOA Code #1", 750, 0., 750., 750, 0., 750.);
    hTOA_Code0vsTOA_Code1_Corrected_C1->Sumw2();

    TH2D *hTOA1vsTOA0 = new TH2D("hTOA1vsTOA0", "TOA vs. TOA ; TOA #0; TOA #1", 150, 0., 15., 150, 0., 15.);
    hTOA1vsTOA0->Sumw2();
    TH2D *hTOA1vsTOA0_Corrected = new TH2D("hTOA1vsTOA0_Corrected", "TOA Corrected vs. TOA Corrected ;TOA #0;TOA #1", 150, 0., 15., 150, 0., 15.);
    hTOA1vsTOA0_Corrected->Sumw2();

    const Int_t nBoards = 2;
    TH1D *hNHits[nBoards];
    TH1D *hTOT[nBoards];
    TH1D *hTOA[nBoards];
    TH1D *hTOA_Corrected[nBoards];
    TH1D *hCAL[nBoards];
    TH2D *hTOAvsTOT[nBoards];
    TH2D *hTOAvsTOT_Corrected[nBoards];
    TH2D *hDTOAvsTOT[nBoards];
    TH2D *hDTOAvsTOT_Corrected[nBoards];
    TH2D *hTOTvsCAL[nBoards];
    TH2D *hTOAvsCAL[nBoards];
    TH2D *hTOAvsCAL_Corrected[nBoards];
    TProfile *pDTOAvsTOT[nBoards];
    float Correction[nBoards];

    TH1D *hActualTOT[nBoards];
    TH1D *hActualTOA[nBoards];
    TH1D *hActualTOA_Corrected[nBoards];
    TH2D *hActualTOAvsActualTOT[nBoards];
    TH2D *hActualTOAvsActualTOT_Corrected[nBoards];
    TH2D *hActualDTOAvsActualTOT[nBoards];
    TH2D *hActualDTOAvsActualTOT_Corrected[nBoards];
    TH2D *hActualTOTvsCAL[nBoards];
    TH2D *hActualTOAvsCAL[nBoards];
    TH2D *hActualTOAvsCAL_Corrected[nBoards];
    TProfile *pActualDTOAvsActualTOT[nBoards];
    float Actual_Correction[nBoards];

    TH1D *hTOT_SR_BC[nBoards];
    TH1D *hTOA_SR_BC[nBoards];
    TH1D *hCAL_SR_BC[nBoards];
    TH1D *hTOT_SR_AC[nBoards];
    TH1D *hTOA_SR_AC[nBoards];
    TH1D *hCAL_SR_AC[nBoards];

    TH1D *hActualTOT_SR_BC[nBoards];
    TH1D *hActualTOA_SR_BC[nBoards];
    TH1D *hActualTOT_SR_AC[nBoards];
    TH1D *hActualTOA_SR_AC[nBoards];

    for (Int_t i{0}; i < 2; i++)
    {
        hNHits[i] = new TH1D(Form("hNHits_%d", i), Form("Number of hits in board #%d", i), 10, -0.5, 9.5);
        hNHits[i]->Sumw2();
        hCAL[i] = new TH1D(Form("hCAL_%d", i), Form("Cal for board #%d", i), 50, 150.0, 200.);
        hCAL[i]->Sumw2();
        hTOT[i] = new TH1D(Form("hTOT_Code_%d", i), Form("TOT Code for the board #%d", i), 200, 0, 200);
        hTOT[i]->Sumw2();
        hTOA[i] = new TH1D(Form("hTOA_Code_%d", i), Form("TOA Code for the board #%d", i), 750, 0, 750);
        hTOA[i]->Sumw2();
        hTOA_Corrected[i] = new TH1D(Form("hTOA_Code_Corrected_%d", i), Form("TOA Code Corrected for the board #%d", i), 750, 0, 750);
        hTOA_Corrected[i]->Sumw2();
        hTOAvsTOT[i] = new TH2D(Form("hTOA_CodevsTOT_Code_%d", i), Form("TOA Code vs. TOT  Code for board #%d ;TOT%d Code;TOA%d Code", i, i, i), 200, 0., 200., 700, 0., 700.);
        hTOAvsTOT[i]->Sumw2();
        hTOAvsTOT_Corrected[i] = new TH2D(Form("hTOA_CodevsTOT_Code_Corrected_%d", i), Form("TOA Code Corrected vs. TOT Code for board #%d ;TOT%d Code;TOA%d Code", i, i, i), 200, 0., 200., 700, 0., 700.);
        hTOAvsTOT_Corrected[i]->Sumw2();
        hDTOAvsTOT[i] = new TH2D(Form("hDTOA_CodevsTOT_Code_%d", i), Form("DTOA Code vs. TOT Code for board #%d ;TOT%d Code;DTOA Code", i, i), 200, 0., 200., 200, -100., 100.);
        hDTOAvsTOT[i]->Sumw2();
        hDTOAvsTOT_Corrected[i] = new TH2D(Form("hDTOA_CodevsTOT_Code_Corrected_%d", i), Form("DTOA Code vs. TOT Code Corrected for board #%d;TOT%d Code;DTOA Code", i, i), 200, 0., 200., 200, -100., 100.);
        hDTOAvsTOT_Corrected[i]->Sumw2();
        hTOAvsCAL[i] = new TH2D(Form("hTOA_CodevsCAL_%d", i), Form("TOA Code vs. CAL for board #%d;CAL%d;TOA%d Code", i, i, i), 50, 150., 200., 700, 0., 700.);
        hTOAvsCAL[i]->Sumw2();
        hTOAvsCAL_Corrected[i] = new TH2D(Form("hTOA_CodevsCAL_Corrected_%d", i), Form("TOA Code Corrected vs. CAL for board #%d;CAL%d;TOA%d Code", i, i, i), 50, 150., 200., 700, 0., 700.);
        hTOAvsCAL_Corrected[i]->Sumw2();
        hTOTvsCAL[i] = new TH2D(Form("hTOT_CodevsCAL_%d", i), Form("TOT Code vs. CAL for board #%d;CAL%d;TOT%d Code", i, i, i), 50, 150., 200., 200, 0., 200.);
        hTOTvsCAL[i]->Sumw2();
        pDTOAvsTOT[i] = new TProfile(Form("pDTOA_CodevsTOT_Code_%d", i), Form("Profile for DTOA_Code_#%d;TOT%d Code;DTOA Code", i, i), 200, 0.0, 200.0);

        // Actual TOA and TOT histograms
        pActualDTOAvsActualTOT[i] = new TProfile(Form("pDTOAvsTOT_%d", i), Form("Profile for DTOA_#%d;TOT;DTOA", i), 100, 0., 10.);
        hActualTOT[i] = new TH1D(Form("hTOT_%d", i), Form("TOT for the board #%d", i), 200, 0., 20.);
        hActualTOT[i]->Sumw2();
        hActualTOA[i] = new TH1D(Form("hTOA_%d", i), Form("TOA for the board #%d", i), 150, 0., 15.0);
        hActualTOA[i]->Sumw2();
        hActualTOA_Corrected[i] = new TH1D(Form("hTOA_Corrected_%d", i), Form("TOA Corrected for the board #%d", i), 150, 0., 15.);
        hActualTOA_Corrected[i]->Sumw2();
        hActualTOAvsActualTOT[i] = new TH2D(Form("hTOAvsTOT_%d", i), Form("TOA vs. TOT for board #%d ;TOT%d;TOA%d", i, i, i), 200, 0., 20., 150, 0., 15.);
        hActualTOAvsActualTOT[i]->Sumw2();
        hActualTOAvsActualTOT_Corrected[i] = new TH2D(Form("hTOAvsTOT_Corrected_%d", i), Form("TOA Corrected vs. TOT for board #%d ;TOT%d; TOA%d", i, i, i), 200, 0., 20., 150, 0., 15.);
        hActualTOAvsActualTOT_Corrected[i]->Sumw2();
        hActualDTOAvsActualTOT[i] = new TH2D(Form("hDTOAvsTOT_%d", i), Form("DTOA vs. TOT for board #%d ;TOT%d;DTOA", i, i), 80, 0.0, 8.0, 200, -2., 2.);
        hActualDTOAvsActualTOT[i]->Sumw2();
        hActualDTOAvsActualTOT_Corrected[i] = new TH2D(Form("hDTOAvsTOT_Corrected_%d", i), Form("DTOA vs. TOT Corrected for board #%d;TOT%d;DTOA", i, i), 80, 0.0, 8.0, 200, -2., 2.);
        hActualDTOAvsActualTOT_Corrected[i]->Sumw2();
        hActualTOAvsCAL[i] = new TH2D(Form("hTOAvsCAL_%d", i), Form("TOA vs. CAL for board #%d;CAL%d;TOA%d", i, i, i), 50, 150., 200., 150, 0., 15.0);
        hActualTOAvsCAL[i]->Sumw2();
        hActualTOAvsCAL_Corrected[i] = new TH2D(Form("hTOAvsCAL_Corrected_%d", i), Form("TOA Corrected vs. CAL for board #%d;CAL%d;TOA%d", i, i, i), 50, 150., 200., 150, 0., 15.0);
        hActualTOAvsCAL_Corrected[i]->Sumw2();
        hActualTOTvsCAL[i] = new TH2D(Form("hTOTvsCAL_%d", i), Form("TOT vs. CAL for board #%d;CAL%d;TOT%d", i, i, i), 50, 150., 200., 200, 0., 20.);
        hActualTOTvsCAL[i]->Sumw2();

        // Specific Range TOT_CODE plots
        hTOT_SR_BC[i] = new TH1D(Form("hTOT_Code_SR_BC_%d", i), Form("TOT Code SR for the board #%d", i), 750, 0, 750);
        hTOT_SR_BC[i]->Sumw2();
        hTOA_SR_BC[i] = new TH1D(Form("hTOA_Code_SR_BC_%d", i), Form("TOA Code SR for the board #%d", i), 750, 0, 750);
        hTOA_SR_BC[i]->Sumw2();
        hCAL_SR_BC[i] = new TH1D(Form("hCAL_SR_BC_%d", i), Form("Cal SR for board #%d", i), 50, 150.0, 200.);
        hCAL_SR_BC[i]->Sumw2();
        hTOT_SR_AC[i] = new TH1D(Form("hTOT_Code_SR_AC_%d", i), Form("TOT Code SR for the board #%d", i), 750, 0, 750);
        hTOT_SR_AC[i]->Sumw2();
        hTOA_SR_AC[i] = new TH1D(Form("hTOA_Code_SR_AC_%d", i), Form("TOA Code SR for the board #%d", i), 750, 0, 750);
        hTOA_SR_AC[i]->Sumw2();
        hCAL_SR_AC[i] = new TH1D(Form("hCAL_SR_AC_%d", i), Form("Cal SR for board #%d", i), 50, 150.0, 200.);
        hCAL_SR_AC[i]->Sumw2();

        hActualTOT_SR_BC[i] = new TH1D(Form("hTOT_SR_BC_%d", i), Form("TOT SR for the board #%d", i), 200, 0., 20.);
        hActualTOT_SR_BC[i]->Sumw2();
        hActualTOA_SR_BC[i] = new TH1D(Form("hTOA_SR_BC_%d", i), Form("TOA SR for the board #%d", i), 150, 0., 15.0);
        hActualTOA_SR_BC[i]->Sumw2();
        hActualTOT_SR_AC[i] = new TH1D(Form("hTOT_SR_AC_%d", i), Form("TOT SR for the board #%d", i), 200, 0., 20.);
        hActualTOT_SR_AC[i]->Sumw2();
        hActualTOA_SR_AC[i] = new TH1D(Form("hTOA_SR_AC_%d", i), Form("TOA SR for the board #%d", i), 150, 0., 15.0);
        hActualTOA_SR_AC[i]->Sumw2();
    }

    //
    // Fitting functions for the Time Walk corrections
    //

    TF1 *board0_fit = new TF1("board0_fit", "pol5", 40, 160);
    board0_fit->SetParameters(281.326, -16.7643, 0.364222, -0.0037943, 1.93689e-05, -3.86596e-08);
    TF1 *board1_fit = new TF1("board1_fit", "pol5", 40.0, 160.0);
    board1_fit->SetParameters(-119.109, 10.7384, -0.275222, 0.00316887, -1.72771e-05, 3.60563e-08);

    TF1 *actual_board0_fit = new TF1("actual_board0_fit", "pol8", 1.1, 6.2);
    actual_board0_fit->SetParameters(-12.4467, 41.1888, -52.767, 36.8273, -15.4872, 4.02893, -0.634154, 0.0552851, -0.00204631);
    TF1 *actual_board1_fit = new TF1("actual_board1_fit", "pol8", 1.1, 6.2);
    actual_board1_fit->SetParameters(24.8491, -69.4859, 79.9827, -50.7076, 19.5084, -4.67229, 0.680823, -0.0552109, 0.00190872);
    //
    // Create variables to fill
    //

    UInt_t runId;
    UInt_t loopId;
    UInt_t eventId;

    std::vector<Hit> *mBoard0{nullptr};
    std::vector<Hit> *mBoard1{nullptr};
    // std::vector<Hit> *mBoard2{nullptr};
    // std::vector<Hit> *mBoard3{nullptr};    h11->Write();

    auto T = dynamic_cast<TTree *>(inFile->Get("T"));
    if (!T)
    {
        std::cout << "[ERROR] No tree was found" << std::endl;
        inFile->Close();
        return 1;
    }

    //
    // Set branches to read (do not mess with naming)
    //

    T->SetBranchAddress("mEventId", &eventId);
    T->SetBranchAddress("mBoard0", &mBoard0);
    T->SetBranchAddress("mBoard1", &mBoard1);
    // T->SetBranchAddress( "mBoard2", &mBoard2 );
    // T->SetBranchAddress( "mBoard3", &mBoard3 );

    // Retrieve number of events
    Long64_t nEntries = T->GetEntries();
    // nEntries = 100;

    // Loop over event in TTree
    for (Long64_t iEntry{0}; iEntry < nEntries; ++iEntry)
    {

        // Load the entry from the tree
        T->GetEntry(iEntry);

        h2->Fill(eventId);
        if (mBoard0->size() == 1 && mBoard1->size() == 1)
        {

            Hit hit1, hit2;

            for (UInt_t iHit{0}; iHit < mBoard0->size(); iHit++)
            {
                hit1 = mBoard0->at(iHit);
                if (hit1.column() < 8)
                {
                    Correction[0] = board0_fit->Eval(hit1.tot());
                    Actual_Correction[0] = actual_board0_fit->Eval(hit1.actual_tot());
                    hTOA[0]->Fill(hit1.toa());
                    hActualTOA[0]->Fill(hit1.actual_toa());
                    hTOA_Corrected[0]->Fill(hit1.toa() - Correction[0]);
                    hActualTOA_Corrected[0]->Fill(hit1.actual_toa() - Actual_Correction[0]);
                    hTOT[0]->Fill(hit1.tot());
                    hActualTOT[0]->Fill(hit1.actual_tot());
                    hTOAvsTOT[0]->Fill(hit1.tot(), hit1.toa());
                    hActualTOAvsActualTOT[0]->Fill(hit1.actual_tot(), hit1.actual_toa());
                    hTOAvsTOT_Corrected[0]->Fill(hit1.tot(), hit1.toa() - Correction[0]);
                    hActualTOAvsActualTOT_Corrected[0]->Fill(hit1.actual_tot(), hit1.actual_toa() - Actual_Correction[0]);
                    hTOAvsCAL[0]->Fill(hit1.cal(), hit1.toa());
                    hActualTOAvsCAL[0]->Fill(hit1.cal(), hit1.actual_toa());
                    hTOAvsCAL_Corrected[0]->Fill(hit1.cal(), hit1.toa() - Correction[0]);
                    hActualTOAvsCAL_Corrected[0]->Fill(hit1.cal(), hit1.actual_toa() - Actual_Correction[0]);
                    hTOTvsCAL[0]->Fill(hit1.cal(), hit1.tot());
                    hActualTOTvsCAL[0]->Fill(hit1.cal(), hit1.actual_tot());
                    hCAL[0]->Fill(hit1.cal());
                    if (hit1.toa() > 500 || hit1.toa() < 250)
                        continue;
                    hTOA_SR_BC[0]->Fill(hit1.toa());
                    hTOT_SR_BC[0]->Fill(hit1.tot());
                    hCAL_SR_BC[0]->Fill(hit1.cal());
                    hActualTOA_SR_BC[0]->Fill(hit1.actual_toa());
                    hActualTOT_SR_BC[0]->Fill(hit1.actual_tot());
                    if (hit1.tot() > 160 || hit1.tot() < 40)
                        continue;
                    hTOA_SR_AC[0]->Fill(hit1.toa());
                    hTOT_SR_AC[0]->Fill(hit1.tot());
                    hCAL_SR_AC[0]->Fill(hit1.cal());
                    hActualTOA_SR_AC[0]->Fill(hit1.actual_toa());
                    hActualTOT_SR_AC[0]->Fill(hit1.actual_tot());
                }
            }
            for (UInt_t iHit{0}; iHit < mBoard1->size(); iHit++)
            {
                hit2 = mBoard1->at(iHit);
                if (hit2.column() < 8)
                {
                    Correction[1] = board1_fit->Eval(hit2.tot());
                    Actual_Correction[1] = actual_board1_fit->Eval(hit2.actual_tot());
                    hTOA[1]->Fill(hit2.toa());
                    hActualTOA[1]->Fill(hit2.actual_toa());
                    hTOA_Corrected[1]->Fill(hit2.toa() + Correction[1]);
                    hActualTOA_Corrected[1]->Fill(hit2.actual_toa() + Actual_Correction[1]);
                    hTOT[1]->Fill(hit2.tot());
                    hActualTOT[1]->Fill(hit2.actual_tot());
                    hTOAvsTOT[1]->Fill(hit2.tot(), hit2.toa());
                    hActualTOAvsActualTOT[1]->Fill(hit2.actual_tot(), hit2.actual_toa());
                    hTOAvsTOT_Corrected[1]->Fill(hit2.tot(), hit2.toa() + Correction[1]);
                    hActualTOAvsActualTOT_Corrected[1]->Fill(hit2.actual_tot(), hit2.actual_toa() + Actual_Correction[1]);
                    hTOAvsCAL[1]->Fill(hit2.cal(), hit2.toa());
                    hActualTOAvsCAL[1]->Fill(hit2.cal(), hit2.actual_toa());
                    hTOAvsCAL_Corrected[1]->Fill(hit2.cal(), hit2.toa() + Correction[1]);
                    hActualTOAvsCAL_Corrected[1]->Fill(hit2.cal(), hit2.actual_toa() + Actual_Correction[1]);
                    hTOTvsCAL[1]->Fill(hit2.cal(), hit2.tot());
                    hActualTOTvsCAL[1]->Fill(hit2.cal(), hit2.actual_tot());
                    hCAL[1]->Fill(hit2.cal());
                    if (hit2.toa() > 500 || hit2.toa() < 250)
                        continue;
                    hTOA_SR_BC[1]->Fill(hit2.toa());
                    hTOT_SR_BC[1]->Fill(hit2.tot());
                    hCAL_SR_BC[1]->Fill(hit2.cal());
                    hActualTOA_SR_BC[1]->Fill(hit2.actual_toa());
                    hActualTOT_SR_BC[1]->Fill(hit2.actual_tot());
                    if (hit2.tot() > 160 || hit2.tot() < 40)
                        continue;
                    hTOA_SR_AC[1]->Fill(hit2.toa());
                    hTOT_SR_AC[1]->Fill(hit2.tot());
                    hCAL_SR_AC[1]->Fill(hit2.cal());
                    hActualTOA_SR_AC[1]->Fill(hit2.actual_toa());
                    hActualTOT_SR_AC[1]->Fill(hit2.actual_tot());
                }
            }
            if (hit1.column() < 8 && hit2.column() < 8)
            {
                if (hit1.toa() > 500 || hit1.toa() < 250)
                    continue;
                if (hit2.toa() > 500 || hit2.toa() < 250)
                    continue;
                h11->Fill(hit1.actual_toa() - hit2.actual_toa());

                if (hit1.tot() > 160 || hit1.tot() < 40)
                    continue;
                if (hit2.tot() > 160 || hit2.tot() < 40)
                    continue;
                h3->Fill(hit1.toa() - hit2.toa());
                h4->Fill(hit1.toa() - Correction[0] - hit2.toa() - Correction[1]);
                h5->Fill(hit1.toa() - Correction[0] - hit2.toa());
                h6->Fill(hit1.toa() - hit2.toa() - Correction[1]);
                h12->Fill(hit1.actual_toa() - hit2.actual_toa());
                hDTOAvsTOT[0]->Fill(hit1.tot(), hit1.toa() - hit2.toa());
                hDTOAvsTOT_Corrected[0]->Fill(hit1.tot(), hit1.toa() - Correction[0] - hit2.toa() - Correction[1]);
                hDTOAvsTOT[1]->Fill(hit2.tot(), hit1.toa() - hit2.toa());
                hDTOAvsTOT_Corrected[1]->Fill(hit2.tot(), hit1.toa() - Correction[0] - hit2.toa() - Correction[1]);
                hTOAvsTOA->Fill(hit1.toa(), hit2.toa());
                hTOAvsTOA_Corrected->Fill(hit1.toa() - Correction[0], hit2.toa() + Correction[1]);
                hDROWvsDCOL->Fill(hit1.column() - hit2.column(), hit1.row() - hit2.row());
                pDTOAvsTOT[0]->Fill(hit1.tot(), hit1.toa() - hit2.toa());
                pActualDTOAvsActualTOT[0]->Fill(hit1.actual_tot(), hit1.actual_toa() - hit2.actual_toa());
                pDTOAvsTOT[1]->Fill(hit2.tot(), hit1.toa() - hit2.toa());
                pActualDTOAvsActualTOT[1]->Fill(hit2.actual_tot(), hit1.actual_toa() - hit2.actual_toa());

                if (hit1.actual_tot() > 6.2 || hit1.actual_tot() < 1.1)
                    continue;
                if (hit2.actual_tot() > 6.2 || hit2.actual_tot() < 1.1)
                    continue;
                h7->Fill(hit1.actual_toa() - hit2.actual_toa());
                h8->Fill(hit1.actual_toa() - Actual_Correction[0] - hit2.actual_toa() - Actual_Correction[1]);
                h9->Fill(hit1.actual_toa() - Actual_Correction[0] - hit2.actual_toa());
                h10->Fill(hit1.actual_toa() - hit2.actual_toa() - Actual_Correction[1]);
                hActualDTOAvsActualTOT[0]->Fill(hit1.actual_tot(), hit1.actual_toa() - hit2.actual_toa());
                hActualDTOAvsActualTOT_Corrected[0]->Fill(hit1.actual_tot(), hit1.actual_toa() - Actual_Correction[0] - hit2.actual_toa() - Actual_Correction[1]);
                hActualDTOAvsActualTOT[1]->Fill(hit2.actual_tot(), hit1.actual_toa() - hit2.actual_toa());
                hActualDTOAvsActualTOT_Corrected[1]->Fill(hit2.actual_tot(), hit1.actual_toa() - Actual_Correction[0] - hit2.actual_toa() - Actual_Correction[1]);
                hActualTOAvsActualTOA->Fill(hit1.actual_toa(), hit2.actual_toa());
                hActualTOAvsActualTOA_Corrected->Fill(hit1.actual_toa() - Actual_Correction[0], hit2.actual_toa() + Actual_Correction[1]);
            }
        }
    }

    TFile *oFile = new TFile("oReadEtroc2_TOACUT_LeftssSide.root", "recreate");
    h1->Write();
    h2->Write();
    h3->Write();
    h4->Write();
    h5->Write();
    h6->Write();
    h7->Write();
    h8->Write();
    h9->Write();
    h10->Write();
    h11->Write();
    h12->Write();
    hDROWvsDCOL->Write();
    hTOAvsTOA->Write();
    hActualTOAvsActualTOA->Write();
    hTOAvsTOA_Corrected->Write();
    hActualTOAvsActualTOA_Corrected->Write();

    for (Int_t i{0}; i < nBoards; i++)
    {
        hNHits[i]->Write();
        hTOA[i]->Write();
        hActualTOA[i]->Write();
        hTOA_Corrected[i]->Write();
        hActualTOA_Corrected[i]->Write();
        hTOT[i]->Write();
        hActualTOT[i]->Write();
        hTOAvsTOT[i]->Write();
        hActualTOAvsActualTOT[i]->Write();
        hTOAvsTOT_Corrected[i]->Write();
        hActualTOAvsActualTOT_Corrected[i]->Write();
        hDTOAvsTOT[i]->Write();
        hActualDTOAvsActualTOT[i]->Write();
        hDTOAvsTOT_Corrected[i]->Write();
        hActualDTOAvsActualTOT_Corrected[i]->Write();
        hTOAvsCAL[i]->Write();
        hActualTOAvsCAL[i]->Write();
        hTOAvsCAL_Corrected[i]->Write();
        hActualTOAvsCAL_Corrected[i]->Write();
        hTOTvsCAL[i]->Write();
        hActualTOTvsCAL[i]->Write();
        hCAL[i]->Write();
        pDTOAvsTOT[i]->Write();
        pActualDTOAvsActualTOT[i]->Write();
        hTOA_SR_BC[i]->Write();
        hTOT_SR_BC[i]->Write();
        hCAL_SR_BC[i]->Write();
        hActualTOA_SR_BC[i]->Write();
        hActualTOT_SR_BC[i]->Write();
        hTOA_SR_AC[i]->Write();
        hTOT_SR_AC[i]->Write();
        hCAL_SR_AC[i]->Write();
        hActualTOA_SR_AC[i]->Write();
        hActualTOT_SR_AC[i]->Write();
    }

    oFile->Close();

    return 0;
}
