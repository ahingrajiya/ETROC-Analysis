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
#include "HistoManagerETROC.h"

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
    // TString InputFile = argv[0];
    Bool_t isLeftSide = kTRUE;
    Bool_t isRightSide = kFALSE;

    const Char_t *inFileName = "/home/abhishek/analysis/etroc_analysis/ETROC2/build/oEtroc2Trans.root";

    // TFile *inFile = TFile::Open(Form("%s", InputFile.Data()));
    TFile *inFile = TFile::Open(inFileName);

    if (!inFile->IsOpen() || inFile->IsZombie())
    {
        std::cout << "[ERROR] File is opened or zombie" << std::endl;
        return 1;
    }

    //
    // Histogram manager
    //
    HistoManagerETROC *hm = new HistoManagerETROC{};
    hm->init();

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
    // std::vector<Hit> *mBoard3{nullptr};

    const Int_t nBoards = 2;

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

        Bool_t LeftPass[nBoards] = {kFALSE, kFALSE};  // Flip it to true if the pixels are on "Left Side Board"
        Bool_t RightPass[nBoards] = {kFALSE, kFALSE}; // Flip it to true if the pixels are on "Left Side Board"
        Bool_t AllPass[nBoards] = {kFALSE, kFALSE};   // Flip it to true if all the selections are satisfied
        Bool_t TOAPass[nBoards] = {kFALSE, kFALSE};   // Flip it to true if TOACode selections are satisfied

        if (mBoard0->size() == 1 && mBoard1->size() == 1)
        {

            Hit hit1, hit2;

            for (UInt_t iHit{0}; iHit < mBoard0->size(); iHit++)
            {
                hit1 = mBoard0->at(iHit);

                if ((hit1.toacode() > 250) && (hit1.toacode() < 500))
                {
                    TOAPass[0] = kTRUE;
                    if (hit1.totcode() > 70 && hit1.totcode() < 130)
                        AllPass[0] = kTRUE;
                }
                if (isLeftSide)
                {
                    if (hit1.column() < 8)
                    {
                        LeftPass[0] = kTRUE;
                        hm->hTOACodevsTOTCode_C0[0]->Fill(hit1.totcode(), hit1.toacode());
                        hm->hTOAvsTOT_C0[0]->Fill(hit1.tot(), hit1.toa());
                        hm->hTOACodevsCALCode_C0[0]->Fill(hit1.calcode(), hit1.toacode());
                        hm->hTOAvsCAL_C0[0]->Fill(hit1.calcode(), hit1.toa());
                        hm->hTOTCodevsCALCode_C0[0]->Fill(hit1.calcode(), hit1.totcode());
                        hm->hTOTvsCAL_C0[0]->Fill(hit1.calcode(), hit1.tot());
                        if (TOAPass[0])
                        {
                            hm->hTOACodevsTOTCode_C1[0]->Fill(hit1.totcode(), hit1.toacode());
                            hm->hTOAvsTOT_C1[0]->Fill(hit1.tot(), hit1.toa());
                            hm->hTOACodevsCALCode_C1[0]->Fill(hit1.calcode(), hit1.toacode());
                            hm->hTOAvsCAL_C1[0]->Fill(hit1.calcode(), hit1.toa());
                            hm->hTOTCodevsCALCode_C1[0]->Fill(hit1.calcode(), hit1.totcode());
                            hm->hTOTvsCAL_C1[0]->Fill(hit1.calcode(), hit1.tot());
                            if (AllPass[0])
                            {
                                hm->hTOACodevsTOTCode_C2[0]->Fill(hit1.totcode(), hit1.toacode());
                                hm->hTOAvsTOT_C2[0]->Fill(hit1.tot(), hit1.toa());
                                hm->hTOACodevsCALCode_C2[0]->Fill(hit1.calcode(), hit1.toacode());
                                hm->hTOAvsCAL_C2[0]->Fill(hit1.calcode(), hit1.toa());
                                hm->hTOTCodevsCALCode_C2[0]->Fill(hit1.calcode(), hit1.totcode());
                                hm->hTOTvsCAL_C2[0]->Fill(hit1.calcode(), hit1.tot());
                            }
                        }
                    }
                }
                if (isRightSide)
                {
                    if (hit1.column() > 7)
                    {
                        RightPass[0] = kTRUE;
                        hm->hTOACodevsTOTCode_C0[0]->Fill(hit1.totcode(), hit1.toacode());
                        hm->hTOAvsTOT_C0[0]->Fill(hit1.tot(), hit1.toa());
                        hm->hTOACodevsCALCode_C0[0]->Fill(hit1.calcode(), hit1.toacode());
                        hm->hTOAvsCAL_C0[0]->Fill(hit1.calcode(), hit1.toa());
                        hm->hTOTCodevsCALCode_C0[0]->Fill(hit1.calcode(), hit1.totcode());
                        hm->hTOTvsCAL_C0[0]->Fill(hit1.calcode(), hit1.tot());
                        if (TOAPass[0])
                        {
                            hm->hTOACodevsTOTCode_C1[0]->Fill(hit1.totcode(), hit1.toacode());
                            hm->hTOAvsTOT_C1[0]->Fill(hit1.tot(), hit1.toa());
                            hm->hTOACodevsCALCode_C1[0]->Fill(hit1.calcode(), hit1.toacode());
                            hm->hTOAvsCAL_C1[0]->Fill(hit1.calcode(), hit1.toa());
                            hm->hTOTCodevsCALCode_C1[0]->Fill(hit1.calcode(), hit1.totcode());
                            hm->hTOTvsCAL_C1[0]->Fill(hit1.calcode(), hit1.tot());
                            if (AllPass[0])
                            {
                                hm->hTOACodevsTOTCode_C2[0]->Fill(hit1.totcode(), hit1.toacode());
                                hm->hTOAvsTOT_C2[0]->Fill(hit1.tot(), hit1.toa());
                                hm->hTOACodevsCALCode_C2[0]->Fill(hit1.calcode(), hit1.toacode());
                                hm->hTOAvsCAL_C2[0]->Fill(hit1.calcode(), hit1.toa());
                                hm->hTOTCodevsCALCode_C2[0]->Fill(hit1.calcode(), hit1.totcode());
                                hm->hTOTvsCAL_C2[0]->Fill(hit1.calcode(), hit1.tot());
                            }
                        }
                    }
                }
            }
            for (UInt_t iHit{0}; iHit < mBoard1->size(); iHit++)
            {
                hit2 = mBoard1->at(iHit);

                if ((hit2.toacode() > 250) && (hit2.toacode() < 500))
                {
                    TOAPass[1] = kTRUE;
                    if (hit2.totcode() > 70 && hit2.totcode() < 130)
                        AllPass[1] = kTRUE;
                }
                if (isLeftSide)
                {
                    if (hit2.column() < 8)
                    {
                        LeftPass[1] = kTRUE;
                        hm->hTOACodevsTOTCode_C0[1]->Fill(hit2.totcode(), hit2.toacode());
                        hm->hTOAvsTOT_C0[1]->Fill(hit2.tot(), hit2.toa());
                        hm->hTOACodevsCALCode_C0[1]->Fill(hit2.calcode(), hit2.toacode());
                        hm->hTOAvsCAL_C0[1]->Fill(hit2.calcode(), hit2.toa());
                        hm->hTOTCodevsCALCode_C0[1]->Fill(hit2.calcode(), hit2.totcode());
                        hm->hTOTvsCAL_C0[1]->Fill(hit2.calcode(), hit2.tot());
                        if (TOAPass[1])
                        {
                            hm->hTOACodevsTOTCode_C1[1]->Fill(hit2.totcode(), hit2.toacode());
                            hm->hTOAvsTOT_C1[1]->Fill(hit2.tot(), hit2.toa());
                            hm->hTOACodevsCALCode_C1[1]->Fill(hit2.calcode(), hit2.toacode());
                            hm->hTOAvsCAL_C1[1]->Fill(hit2.calcode(), hit2.toa());
                            hm->hTOTCodevsCALCode_C1[1]->Fill(hit2.calcode(), hit2.totcode());
                            hm->hTOTvsCAL_C1[1]->Fill(hit2.calcode(), hit2.tot());
                            if (AllPass[1])
                            {
                                hm->hTOACodevsTOTCode_C2[1]->Fill(hit2.totcode(), hit2.toacode());
                                hm->hTOAvsTOT_C2[1]->Fill(hit2.tot(), hit2.toa());
                                hm->hTOACodevsCALCode_C2[1]->Fill(hit2.calcode(), hit2.toacode());
                                hm->hTOAvsCAL_C2[1]->Fill(hit2.calcode(), hit2.toa());
                                hm->hTOTCodevsCALCode_C2[1]->Fill(hit2.calcode(), hit2.totcode());
                                hm->hTOTvsCAL_C2[1]->Fill(hit2.calcode(), hit2.tot());
                            }
                        }
                    }
                }
                if (isRightSide)
                {
                    if (hit2.column() > 7)
                    {
                        RightPass[1] = kTRUE;
                        hm->hTOACodevsTOTCode_C0[1]->Fill(hit2.totcode(), hit2.toacode());
                        hm->hTOAvsTOT_C0[1]->Fill(hit2.tot(), hit2.toa());
                        hm->hTOACodevsCALCode_C0[1]->Fill(hit2.calcode(), hit2.toacode());
                        hm->hTOAvsCAL_C0[1]->Fill(hit2.calcode(), hit2.toa());
                        hm->hTOTCodevsCALCode_C0[1]->Fill(hit2.calcode(), hit2.totcode());
                        hm->hTOTvsCAL_C0[1]->Fill(hit2.calcode(), hit2.tot());
                        if (TOAPass[1])
                        {
                            hm->hTOACodevsTOTCode_C1[1]->Fill(hit2.totcode(), hit2.toacode());
                            hm->hTOAvsTOT_C1[1]->Fill(hit2.tot(), hit2.toa());
                            hm->hTOACodevsCALCode_C1[1]->Fill(hit2.calcode(), hit2.toacode());
                            hm->hTOAvsCAL_C1[1]->Fill(hit2.calcode(), hit2.toa());
                            hm->hTOTCodevsCALCode_C1[1]->Fill(hit2.calcode(), hit2.totcode());
                            hm->hTOTvsCAL_C1[1]->Fill(hit2.calcode(), hit2.tot());
                            if (AllPass[1])
                            {
                                hm->hTOACodevsTOTCode_C2[1]->Fill(hit2.totcode(), hit2.toacode());
                                hm->hTOAvsTOT_C2[1]->Fill(hit2.tot(), hit2.toa());
                                hm->hTOACodevsCALCode_C2[1]->Fill(hit2.calcode(), hit2.toacode());
                                hm->hTOAvsCAL_C2[1]->Fill(hit2.calcode(), hit2.toa());
                                hm->hTOTCodevsCALCode_C2[1]->Fill(hit2.calcode(), hit2.totcode());
                                hm->hTOTvsCAL_C2[1]->Fill(hit2.calcode(), hit2.tot());
                            }
                        }
                    }
                }
            }
            if (isLeftSide && LeftPass[0] && LeftPass[1])
            {
                hm->hDROWvsDCOL->Fill(hit1.column() - hit2.column(), hit1.row() - hit2.row());
                hm->hTOA_Code1vsTOA_Code0_C0->Fill(hit1.toacode(), hit2.toacode());
                hm->hTOA1vsTOA0_C0->Fill(hit1.toa(), hit2.toa());
                hm->hDTOACodevsTOTCode_C0[0]->Fill(hit1.totcode(), hit1.toacode() - hit2.toacode());
                hm->hDTOAvsTOT_C0[0]->Fill(hit1.tot(), hit1.toa() - hit2.toa());
                hm->hDTOACodevsTOTCode_C0[1]->Fill(hit2.totcode(), hit1.toacode() - hit2.toacode());
                hm->hDTOAvsTOT_C0[1]->Fill(hit2.tot(), hit1.toa() - hit2.toa());
                if (TOAPass[0] && TOAPass[1])
                {
                    hm->hTOA_Code1vsTOA_Code0_C1->Fill(hit1.toacode(), hit2.toacode());
                    hm->hTOA1vsTOA0_C1->Fill(hit1.toa(), hit2.toa());
                    hm->hDTOACodevsTOTCode_C1[0]->Fill(hit1.totcode(), hit1.toacode() - hit2.toacode());
                    hm->hDTOAvsTOT_C1[0]->Fill(hit1.tot(), hit1.toa() - hit2.toa());
                    hm->hDTOACodevsTOTCode_C1[1]->Fill(hit2.totcode(), hit1.toacode() - hit2.toacode());
                    hm->hDTOAvsTOT_C1[1]->Fill(hit2.tot(), hit1.toa() - hit2.toa());
                    if (AllPass[0] && AllPass[1])
                    {
                        hm->hTOA_Code1vsTOA_Code0_C2->Fill(hit1.toacode(), hit2.toacode());
                        hm->hTOA1vsTOA0_C2->Fill(hit1.toa(), hit2.toa());
                        hm->hDTOACodevsTOTCode_C2[0]->Fill(hit1.totcode(), hit1.toacode() - hit2.toacode());
                        hm->hDTOAvsTOT_C2[0]->Fill(hit1.tot(), hit1.toa() - hit2.toa());
                        hm->hDTOACodevsTOTCode_C2[1]->Fill(hit2.totcode(), hit1.toacode() - hit2.toacode());
                        hm->hDTOAvsTOT_C2[1]->Fill(hit2.tot(), hit1.toa() - hit2.toa());
                        hm->pDTOACodevsTOTCode[0]->Fill(hit1.totcode(), hit1.toacode() - hit2.toacode());
                        hm->pDTOAvsTOT[0]->Fill(hit1.tot(), hit1.toa() - hit2.toa());
                        hm->pDTOACodevsTOTCode[1]->Fill(hit2.totcode(), hit1.toacode() - hit2.toacode());
                        hm->pDTOAvsTOT[1]->Fill(hit2.tot(), hit1.toa() - hit2.toa());
                    }
                }
            }
        }
    }

    hm->projection();
    TString outFile;
    if (isLeftSide)
    {
        outFile = "oReadEtroc2_LeftSide.root";
    }

    if (isRightSide)
    {
        outFile = "oReadEtroc2_RightSide.root";
    }

    if (isLeftSide && isRightSide)
    {
        outFile = "oReadEtroc2_Combined.root";
    }

    TFile *oFile = new TFile(Form("%s", outFile.Data()), "recreate");
    hm->writeOutput();
    oFile->Write();
    oFile->Close();

    return 0;
}
