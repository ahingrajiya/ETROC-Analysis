/**
 * @file readEtroc4Boards.cxx
 * @author Abhishek Hingrajiya (abhi.h123@gmail.com)
 * @brief ETROC 4 Boards Data Analysis
 * @version 0.1
 * @date 2024-09-26
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "HistoManagerETROC4Boards.h"
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
#include "Hit.h"
#include "Correction.h"

using namespace std;

// C++ headers
#include <iostream>
#include <vector>

Int_t status = gSystem->Load("/home/abhishek/analysis/etroc_analysis/ETROC2/build/libETROC2.dylib");

#if ROOT_VERSION_CODE >= ROOT_VERSION(6, 0, 0)
R__LOAD_LIBRARY(build / libETROC2.dylib);
#endif

//________________
int main(int argc, char const *argv[])
{
    // TString InputFile = argv[0];
    Bool_t isLeftSide = kFALSE;
    Bool_t isRightSide = kTRUE;

    const Char_t *inFileName = "/home/abhishek/analysis/etroc_analysis/ETROC2/build/oEtroc2Trans_4Boards.root";

    // TFile *inFile = TFile::Open(Form("%s", InputFile.Data()));
    TFile *inFile = TFile::Open(inFileName);

    if (!inFile->IsOpen() || inFile->IsZombie())
    {
        std::cout << "[ERROR] File is opened or zombie" << std::endl;
        return 1;
    }

    Int_t fTOACodeBins, fTOTCodeBins, fCALCodeBins, fDTOACodeBins, fTOABins, fTOTBins, fDTOABins;
    Float_t fTOACodeRange[2], fTOTCodeRange[2], fCALCodeRange[2], fDTOACodeRange[2], fTOARange[2], fTOTRange[2], fDTOARange[2];
    if (isLeftSide)
    {
        fTOACodeBins = 700;
        fTOACodeRange[0] = 0.0;
        fTOACodeRange[1] = 700.0;
        fTOTCodeBins = 160;
        fTOTCodeRange[0] = 40.0;
        fTOTCodeRange[1] = 200.0;
        fCALCodeBins = 30;
        fCALCodeRange[0] = 165.0;
        fCALCodeRange[1] = 195.0;
        fDTOACodeBins = 200;
        fDTOACodeRange[0] = -50.0;
        fDTOACodeRange[1] = 150.0;
        fTOABins = 250;
        fTOARange[0] = 0.0;
        fTOARange[1] = 12.5;
        fTOTBins = 160;
        fTOTRange[0] = 0.0;
        fTOTRange[1] = 8.0;
        fDTOABins = 160;
        fDTOARange[0] = -4.0;
        fDTOARange[1] = 4.0;
    }
    else
    {
        fTOACodeBins = 700;
        fTOACodeRange[0] = 0.0;
        fTOACodeRange[1] = 700.0;
        fTOTCodeBins = 160;
        fTOTCodeRange[0] = 40.0;
        fTOTCodeRange[1] = 200.0;
        fCALCodeBins = 30;
        fCALCodeRange[0] = 140.0;
        fCALCodeRange[1] = 170.0;
        fDTOACodeBins = 200;
        fDTOACodeRange[0] = -50.0;
        fDTOACodeRange[1] = 150.0;
        fTOABins = 250;
        fTOARange[0] = 0.0;
        fTOARange[1] = 12.5;
        fTOTBins = 160;
        fTOTRange[0] = 0.0;
        fTOTRange[1] = 8.0;
        fDTOABins = 160;
        fDTOARange[0] = -4.0;
        fDTOARange[1] = 4.0;
    }

    Correction *co = new Correction{};
    co->setLeftSide(isLeftSide);

    HistoManagerETROC4Boards *hm = new HistoManagerETROC4Boards{};
    hm->setTOABins(fTOABins);
    hm->setTOARange(fTOARange[0], fTOARange[1]);
    hm->setTOTBins(fTOTBins);
    hm->setTOTRange(fTOTRange[0], fTOTRange[1]);
    hm->setCALCodeBins(fCALCodeBins);
    hm->setCALCodeRange(fCALCodeRange[0], fCALCodeRange[1]);
    hm->setDTOACodeBins(fDTOACodeBins);
    hm->setDTOACodeRange(fDTOACodeRange[0], fDTOACodeRange[1]);
    hm->setTOACodeBins(fTOACodeBins);
    hm->setTOACodeRange(fTOACodeRange[0], fTOACodeRange[1]);
    hm->setTOTCodeBins(fTOTCodeBins);
    hm->setTOTCodeRange(fTOTCodeRange[0], fTOTCodeRange[1]);
    hm->setDTOABins(fDTOABins);
    hm->setDTOARange(fDTOARange[0], fDTOARange[1]);
    hm->init();

    UInt_t runId;
    UInt_t loopId;
    UInt_t eventId;

    std::vector<Hit> *mBoard0{nullptr};
    std::vector<Hit> *mBoard1{nullptr};
    std::vector<Hit> *mBoard2{nullptr};
    std::vector<Hit> *mBoard3{nullptr};

    const Int_t nBoards = 4;

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
    T->SetBranchAddress("mBoard2", &mBoard2);
    T->SetBranchAddress("mBoard3", &mBoard3);

    // Retrieve number of events
    Long64_t nEntries = T->GetEntries();
    // nEntries = 100;

    for (Long64_t iEntry{0}; iEntry < nEntries; ++iEntry)
    {

        // Load the entry from the tree
        T->GetEntry(iEntry);

        Bool_t LeftPass[nBoards] = {kFALSE, kFALSE, kFALSE, kFALSE};  // Flip it to true if the pixels are on "Left Side Board"
        Bool_t RightPass[nBoards] = {kFALSE, kFALSE, kFALSE, kFALSE}; // Flip it to true if the pixels are on "Left Side Board"
        Bool_t AllPass[nBoards] = {kFALSE, kFALSE, kFALSE, kFALSE};   // Flip it to true if all the selections are satisfied
        Bool_t TOAPass[nBoards] = {kFALSE, kFALSE, kFALSE, kFALSE};   // Flip it to true if TOACode selections are satisfied

        // cout << Form("Board Sizes Before : %i %i %i %i", mBoard0->size(), mBoard1->size(), mBoard2->size(), mBoard3->size()) << endl;

        if (mBoard0->size() == 1 && mBoard1->size() == 1 && mBoard2->size() == 1 && mBoard3->size() == 1)
        {
            // cout << Form("Board Sizes After : %i %i %i %i", mBoard0->size(), mBoard1->size(), mBoard2->size(), mBoard3->size()) << endl;

            Hit hit0, hit1, hit2, hit3;

            for (UInt_t iHit{0}; iHit < mBoard0->size(); iHit++)
            {
                hit0 = mBoard0->at(iHit);
                hit0.setBoardNumber(hit0.boardNumber());

                if (isLeftSide)
                {
                    if (hit0.column() < 8)
                    {
                        LeftPass[0] = kTRUE;
                        hm->hTOACode0vsTOTCode0_C0->Fill(hit0.totcode(), hit0.toacode());
                        hm->hTOTCode0vsCALCode0_C0->Fill(hit0.calcode(), hit0.totcode());
                        hm->hTOACode0vsCALCode0_C0->Fill(hit0.calcode(), hit0.toacode());
                        hm->hTOA0vsTOT0_C0->Fill(hit0.tot(), hit0.toa());
                        hm->hTOA0vsCALCode0_C0->Fill(hit0.calcode(), hit0.toa());
                        hm->hTOT0vsCALCode0_C0->Fill(hit0.calcode(), hit0.tot());
                        if (hit0.toacode() > 250 && hit0.toacode() < 500)
                        {
                            TOAPass[0] = kTRUE;
                            hm->hTOACode0vsTOTCode0_C1->Fill(hit0.totcode(), hit0.toacode());
                            hm->hTOTCode0vsCALCode0_C1->Fill(hit0.calcode(), hit0.totcode());
                            hm->hTOACode0vsCALCode0_C1->Fill(hit0.calcode(), hit0.toacode());
                            hm->hTOA0vsTOT0_C1->Fill(hit0.tot(), hit0.toa());
                            hm->hTOA0vsCALCode0_C1->Fill(hit0.calcode(), hit0.toa());
                            hm->hTOT0vsCALCode0_C1->Fill(hit0.calcode(), hit0.tot());
                            if (hit0.totcode() > 110 && hit0.totcode() < 151)
                            {
                                AllPass[0] = kTRUE;
                                hm->hTOACode0vsTOTCode0_C2->Fill(hit0.totcode(), hit0.toacode());
                                hm->hTOTCode0vsCALCode0_C2->Fill(hit0.calcode(), hit0.totcode());
                                hm->hTOACode0vsCALCode0_C2->Fill(hit0.calcode(), hit0.toacode());
                                hm->hTOA0vsTOT0_C2->Fill(hit0.tot(), hit0.toa());
                                hm->hTOA0vsCALCode0_C2->Fill(hit0.calcode(), hit0.toa());
                                hm->hTOT0vsCALCode0_C2->Fill(hit0.calcode(), hit0.tot());
                            }
                        }
                    }
                }
                if (isRightSide)
                {
                    if (hit0.column() > 7)
                    {
                        RightPass[0] = kTRUE;

                        hm->hTOACode0vsTOTCode0_C0->Fill(hit0.totcode(), hit0.toacode());
                        hm->hTOTCode0vsCALCode0_C0->Fill(hit0.calcode(), hit0.totcode());
                        hm->hTOACode0vsCALCode0_C0->Fill(hit0.calcode(), hit0.toacode());
                        hm->hTOA0vsTOT0_C0->Fill(hit0.tot(), hit0.toa());
                        hm->hTOA0vsCALCode0_C0->Fill(hit0.calcode(), hit0.toa());
                        hm->hTOT0vsCALCode0_C0->Fill(hit0.calcode(), hit0.tot());
                        if (hit0.toacode() > 250 && hit0.toacode() < 500)
                        {
                            TOAPass[0] = kTRUE;
                            hm->hTOACode0vsTOTCode0_C1->Fill(hit0.totcode(), hit0.toacode());
                            hm->hTOTCode0vsCALCode0_C1->Fill(hit0.calcode(), hit0.totcode());
                            hm->hTOACode0vsCALCode0_C1->Fill(hit0.calcode(), hit0.toacode());
                            hm->hTOA0vsTOT0_C1->Fill(hit0.tot(), hit0.toa());
                            hm->hTOA0vsCALCode0_C1->Fill(hit0.calcode(), hit0.toa());
                            hm->hTOT0vsCALCode0_C1->Fill(hit0.calcode(), hit0.tot());
                            if (hit0.totcode() > 93 && hit0.totcode() < 141)
                            {
                                AllPass[0] = kTRUE;
                                hm->hTOACode0vsTOTCode0_C2->Fill(hit0.totcode(), hit0.toacode());
                                hm->hTOTCode0vsCALCode0_C2->Fill(hit0.calcode(), hit0.totcode());
                                hm->hTOACode0vsCALCode0_C2->Fill(hit0.calcode(), hit0.toacode());
                                hm->hTOA0vsTOT0_C2->Fill(hit0.tot(), hit0.toa());
                                hm->hTOA0vsCALCode0_C2->Fill(hit0.calcode(), hit0.toa());
                                hm->hTOT0vsCALCode0_C2->Fill(hit0.calcode(), hit0.tot());
                            }
                        }
                    }
                }
            }

            for (UInt_t iHit{0}; iHit < mBoard1->size(); iHit++)
            {
                hit1 = mBoard1->at(iHit);
                hit1.setBoardNumber(hit1.boardNumber());

                if (isLeftSide)
                {
                    if (hit1.column() < 8)
                    {
                        LeftPass[1] = kTRUE;
                        hm->hTOACode1vsTOTCode1_C0->Fill(hit1.totcode(), hit1.toacode());
                        hm->hTOTCode1vsCALCode1_C0->Fill(hit1.calcode(), hit1.totcode());
                        hm->hTOACode1vsCALCode1_C0->Fill(hit1.calcode(), hit1.toacode());
                        hm->hTOA1vsTOT1_C0->Fill(hit1.tot(), hit1.toa());
                        hm->hTOA1vsCALCode1_C0->Fill(hit1.calcode(), hit1.toa());
                        hm->hTOT1vsCALCode1_C0->Fill(hit1.calcode(), hit1.tot());
                        if (hit1.toacode() > 250 && hit1.toacode() < 500)
                        {
                            TOAPass[1] = kTRUE;
                            hm->hTOACode1vsTOTCode1_C1->Fill(hit1.totcode(), hit1.toacode());
                            hm->hTOTCode1vsCALCode1_C1->Fill(hit1.calcode(), hit1.totcode());
                            hm->hTOACode1vsCALCode1_C1->Fill(hit1.calcode(), hit1.toacode());
                            hm->hTOA1vsTOT1_C1->Fill(hit1.tot(), hit1.toa());
                            hm->hTOA1vsCALCode1_C1->Fill(hit1.calcode(), hit1.toa());
                            hm->hTOT1vsCALCode1_C1->Fill(hit1.calcode(), hit1.tot());
                            if (hit1.totcode() > 105 && hit1.totcode() < 141)
                            {
                                AllPass[1] = kTRUE;
                                hm->hTOACode1vsTOTCode1_C2->Fill(hit1.totcode(), hit1.toacode());
                                hm->hTOTCode1vsCALCode1_C2->Fill(hit1.calcode(), hit1.totcode());
                                hm->hTOACode1vsCALCode1_C2->Fill(hit1.calcode(), hit1.toacode());
                                hm->hTOA1vsTOT1_C2->Fill(hit1.tot(), hit1.toa());
                                hm->hTOA1vsCALCode1_C2->Fill(hit1.calcode(), hit1.toa());
                                hm->hTOT1vsCALCode1_C2->Fill(hit1.calcode(), hit1.tot());
                            }
                        }
                    }
                }
                if (isRightSide)
                {
                    if (hit1.column() > 7)
                    {
                        RightPass[1] = kTRUE;
                        hm->hTOACode1vsTOTCode1_C0->Fill(hit1.totcode(), hit1.toacode());
                        hm->hTOTCode1vsCALCode1_C0->Fill(hit1.calcode(), hit1.totcode());
                        hm->hTOACode1vsCALCode1_C0->Fill(hit1.calcode(), hit1.toacode());
                        hm->hTOA1vsTOT1_C0->Fill(hit1.tot(), hit1.toa());
                        hm->hTOA1vsCALCode1_C0->Fill(hit1.calcode(), hit1.toa());
                        hm->hTOT1vsCALCode1_C0->Fill(hit1.calcode(), hit1.tot());
                        if (hit1.toacode() > 250 && hit1.toacode() < 500)
                        {
                            TOAPass[1] = kTRUE;
                            hm->hTOACode1vsTOTCode1_C1->Fill(hit1.totcode(), hit1.toacode());
                            hm->hTOTCode1vsCALCode1_C1->Fill(hit1.calcode(), hit1.totcode());
                            hm->hTOACode1vsCALCode1_C1->Fill(hit1.calcode(), hit1.toacode());
                            hm->hTOA1vsTOT1_C1->Fill(hit1.tot(), hit1.toa());
                            hm->hTOA1vsCALCode1_C1->Fill(hit1.calcode(), hit1.toa());
                            hm->hTOT1vsCALCode1_C1->Fill(hit1.calcode(), hit1.tot());
                            if (hit1.totcode() > 86 && hit1.totcode() < 128)
                            {
                                AllPass[1] = kTRUE;
                                hm->hTOACode1vsTOTCode1_C2->Fill(hit1.totcode(), hit1.toacode());
                                hm->hTOTCode1vsCALCode1_C2->Fill(hit1.calcode(), hit1.totcode());
                                hm->hTOACode1vsCALCode1_C2->Fill(hit1.calcode(), hit1.toacode());
                                hm->hTOA1vsTOT1_C2->Fill(hit1.tot(), hit1.toa());
                                hm->hTOA1vsCALCode1_C2->Fill(hit1.calcode(), hit1.toa());
                                hm->hTOT1vsCALCode1_C2->Fill(hit1.calcode(), hit1.tot());
                            }
                        }
                    }
                }
            }
            for (UInt_t iHit{0}; iHit < mBoard2->size(); iHit++)
            {
                hit2 = mBoard2->at(iHit);
                hit2.setBoardNumber(hit2.boardNumber());

                if (isLeftSide)
                {
                    if (hit2.column() < 8)
                    {
                        LeftPass[2] = kTRUE;
                        hm->hTOACode2vsTOTCode2_C0->Fill(hit2.totcode(), hit2.toacode());
                        hm->hTOTCode2vsCALCode2_C0->Fill(hit2.calcode(), hit2.totcode());
                        hm->hTOACode2vsCALCode2_C0->Fill(hit2.calcode(), hit2.toacode());
                        hm->hTOA2vsTOT2_C0->Fill(hit2.tot(), hit2.toa());
                        hm->hTOA2vsCALCode2_C0->Fill(hit2.calcode(), hit2.toa());
                        hm->hTOT2vsCALCode2_C0->Fill(hit2.calcode(), hit2.tot());
                        if (hit2.toacode() > 250 && hit2.toacode() < 500)
                        {
                            TOAPass[2] = kTRUE;
                            hm->hTOTCode2vsCALCode2_C1->Fill(hit2.calcode(), hit2.totcode());
                            hm->hTOACode2vsCALCode2_C1->Fill(hit2.calcode(), hit2.toacode());
                            hm->hTOACode2vsTOTCode2_C1->Fill(hit2.totcode(), hit2.toacode());
                            hm->hTOA2vsTOT2_C1->Fill(hit2.tot(), hit2.toa());
                            hm->hTOA2vsCALCode2_C1->Fill(hit2.calcode(), hit2.toa());
                            hm->hTOT2vsCALCode2_C1->Fill(hit2.calcode(), hit2.tot());
                            if (hit2.totcode() > 81 && hit2.totcode() < 140)
                            {
                                AllPass[2] = kTRUE;
                                hm->hTOTCode2vsCALCode2_C2->Fill(hit2.calcode(), hit2.totcode());
                                hm->hTOACode2vsCALCode2_C2->Fill(hit2.calcode(), hit2.toacode());
                                hm->hTOACode2vsTOTCode2_C2->Fill(hit2.totcode(), hit2.toacode());
                                hm->hTOA2vsTOT2_C2->Fill(hit2.tot(), hit2.toa());
                                hm->hTOA2vsCALCode2_C2->Fill(hit2.calcode(), hit2.toa());
                                hm->hTOT2vsCALCode2_C2->Fill(hit2.calcode(), hit2.tot());
                            }
                        }
                    }
                }
                if (isRightSide)
                {
                    if (hit2.column() > 7)
                    {
                        RightPass[2] = kTRUE;
                        hm->hTOACode2vsTOTCode2_C0->Fill(hit2.totcode(), hit2.toacode());
                        hm->hTOTCode2vsCALCode2_C0->Fill(hit2.calcode(), hit2.totcode());
                        hm->hTOACode2vsCALCode2_C0->Fill(hit2.calcode(), hit2.toacode());
                        hm->hTOA2vsTOT2_C0->Fill(hit2.tot(), hit2.toa());
                        hm->hTOA2vsCALCode2_C0->Fill(hit2.calcode(), hit2.toa());
                        hm->hTOT2vsCALCode2_C0->Fill(hit2.calcode(), hit2.tot());
                        if (hit2.toacode() > 250 && hit2.toacode() < 500)
                        {
                            TOAPass[2] = kTRUE;
                            hm->hTOTCode2vsCALCode2_C1->Fill(hit2.calcode(), hit2.totcode());
                            hm->hTOACode2vsCALCode2_C1->Fill(hit2.calcode(), hit2.toacode());
                            hm->hTOACode2vsTOTCode2_C1->Fill(hit2.totcode(), hit2.toacode());
                            hm->hTOA2vsTOT2_C1->Fill(hit2.tot(), hit2.toa());
                            hm->hTOA2vsCALCode2_C1->Fill(hit2.calcode(), hit2.toa());
                            hm->hTOT2vsCALCode2_C1->Fill(hit2.calcode(), hit2.tot());
                            if (hit2.totcode() > 66 && hit2.totcode() < 120)
                            {
                                AllPass[2] = kTRUE;
                                hm->hTOTCode2vsCALCode2_C2->Fill(hit2.calcode(), hit2.totcode());
                                hm->hTOACode2vsCALCode2_C2->Fill(hit2.calcode(), hit2.toacode());
                                hm->hTOACode2vsTOTCode2_C2->Fill(hit2.totcode(), hit2.toacode());
                                hm->hTOA2vsTOT2_C2->Fill(hit2.tot(), hit2.toa());
                                hm->hTOA2vsCALCode2_C2->Fill(hit2.calcode(), hit2.toa());
                                hm->hTOT2vsCALCode2_C2->Fill(hit2.calcode(), hit2.tot());
                            }
                        }
                    }
                }
            }
            for (UInt_t iHit{0}; iHit < mBoard3->size(); iHit++)
            {
                hit3 = mBoard3->at(iHit);
                hit3.setBoardNumber(hit3.boardNumber());

                if (isLeftSide)
                {
                    if (hit3.column() < 8)
                    {
                        LeftPass[3] = kTRUE;
                        hm->hTOACode3vsTOTCode3_C0->Fill(hit3.totcode(), hit3.toacode());
                        hm->hTOTCode3vsCALCode3_C0->Fill(hit3.calcode(), hit3.totcode());
                        hm->hTOACode3vsCALCode3_C0->Fill(hit3.calcode(), hit3.toacode());
                        hm->hTOA3vsTOT3_C0->Fill(hit3.tot(), hit3.toa());
                        hm->hTOA3vsCALCode3_C0->Fill(hit3.calcode(), hit3.toa());
                        hm->hTOT3vsCALCode3_C0->Fill(hit3.calcode(), hit3.tot());
                        if (hit3.toacode() > 250 && hit3.toacode() < 500)
                        {
                            TOAPass[3] = kTRUE;
                            hm->hTOTCode3vsCALCode3_C1->Fill(hit3.calcode(), hit3.totcode());
                            hm->hTOACode3vsCALCode3_C1->Fill(hit3.calcode(), hit3.toacode());
                            hm->hTOACode3vsTOTCode3_C1->Fill(hit3.totcode(), hit3.toacode());
                            hm->hTOA3vsTOT3_C1->Fill(hit3.tot(), hit3.toa());
                            hm->hTOA3vsCALCode3_C1->Fill(hit3.calcode(), hit3.toa());
                            hm->hTOT3vsCALCode3_C1->Fill(hit3.calcode(), hit3.tot());
                            if (hit3.totcode() > 82 && hit3.totcode() < 141)
                            {
                                AllPass[3] = kTRUE;
                                hm->hTOTCode3vsCALCode3_C2->Fill(hit3.calcode(), hit3.totcode());
                                hm->hTOACode3vsCALCode3_C2->Fill(hit3.calcode(), hit3.toacode());
                                hm->hTOACode3vsTOTCode3_C2->Fill(hit3.totcode(), hit3.toacode());
                                hm->hTOA3vsTOT3_C2->Fill(hit3.tot(), hit3.toa());
                                hm->hTOA3vsCALCode3_C2->Fill(hit3.calcode(), hit3.toa());
                                hm->hTOT3vsCALCode3_C2->Fill(hit3.calcode(), hit3.tot());
                            }
                        }
                    }
                }
                if (isRightSide)
                {
                    if (hit3.column() > 7)
                    {
                        RightPass[3] = kTRUE;
                        hm->hTOACode3vsTOTCode3_C0->Fill(hit3.totcode(), hit3.toacode());
                        hm->hTOTCode3vsCALCode3_C0->Fill(hit3.calcode(), hit3.totcode());
                        hm->hTOACode3vsCALCode3_C0->Fill(hit3.calcode(), hit3.toacode());
                        hm->hTOA3vsTOT3_C0->Fill(hit3.tot(), hit3.toa());
                        hm->hTOA3vsCALCode3_C0->Fill(hit3.calcode(), hit3.toa());
                        hm->hTOT3vsCALCode3_C0->Fill(hit3.calcode(), hit3.tot());
                        if (hit3.toacode() > 250 && hit3.toacode() < 500)
                        {
                            TOAPass[3] = kTRUE;
                            hm->hTOTCode3vsCALCode3_C1->Fill(hit3.calcode(), hit3.totcode());
                            hm->hTOACode3vsCALCode3_C1->Fill(hit3.calcode(), hit3.toacode());
                            hm->hTOACode3vsTOTCode3_C1->Fill(hit3.totcode(), hit3.toacode());
                            hm->hTOA3vsTOT3_C1->Fill(hit3.tot(), hit3.toa());
                            hm->hTOA3vsCALCode3_C1->Fill(hit3.calcode(), hit3.toa());
                            hm->hTOT3vsCALCode3_C1->Fill(hit3.calcode(), hit3.tot());
                            if (hit3.totcode() > 73 && hit3.totcode() < 122)
                            {
                                AllPass[3] = kTRUE;
                                hm->hTOTCode3vsCALCode3_C2->Fill(hit3.calcode(), hit3.totcode());
                                hm->hTOACode3vsCALCode3_C2->Fill(hit3.calcode(), hit3.toacode());
                                hm->hTOACode3vsTOTCode3_C2->Fill(hit3.totcode(), hit3.toacode());
                                hm->hTOA3vsTOT3_C2->Fill(hit3.tot(), hit3.toa());
                                hm->hTOA3vsCALCode3_C2->Fill(hit3.calcode(), hit3.toa());
                                hm->hTOT3vsCALCode3_C2->Fill(hit3.calcode(), hit3.tot());
                            }
                        }
                    }
                }
            }

            if (isLeftSide && LeftPass[0] && LeftPass[1] && LeftPass[2] && LeftPass[3])
            {
                hm->hTOACode0vsTOACode1_C0->Fill(hit1.toacode(), hit0.toacode());
                hm->hTOACode0vsTOACode2_C0->Fill(hit2.toacode(), hit0.toacode());
                hm->hTOACode0vsTOACode3_C0->Fill(hit3.toacode(), hit0.toacode());
                hm->hTOACode1vsTOACode2_C0->Fill(hit2.toacode(), hit1.toacode());
                hm->hTOACode1vsTOACode3_C0->Fill(hit3.toacode(), hit1.toacode());
                hm->hTOACode2vsTOACode3_C0->Fill(hit3.toacode(), hit2.toacode());

                hm->hTOA0vsTOA1_C0->Fill(hit1.toa(), hit0.toa());
                hm->hTOA0vsTOA2_C0->Fill(hit2.toa(), hit0.toa());
                hm->hTOA0vsTOA3_C0->Fill(hit3.toa(), hit0.toa());
                hm->hTOA1vsTOA2_C0->Fill(hit2.toa(), hit1.toa());
                hm->hTOA1vsTOA3_C0->Fill(hit3.toa(), hit1.toa());
                hm->hTOA2vsTOA3_C0->Fill(hit3.toa(), hit2.toa());
                if (TOAPass[0] && TOAPass[1] && TOAPass[2] && TOAPass[3])
                {

                    hm->hTOACode0vsTOACode1_C1->Fill(hit1.toacode(), hit0.toacode());
                    hm->hTOACode0vsTOACode2_C1->Fill(hit2.toacode(), hit0.toacode());
                    hm->hTOACode0vsTOACode3_C1->Fill(hit3.toacode(), hit0.toacode());
                    hm->hTOACode1vsTOACode2_C1->Fill(hit2.toacode(), hit1.toacode());
                    hm->hTOACode1vsTOACode3_C1->Fill(hit3.toacode(), hit1.toacode());
                    hm->hTOACode2vsTOACode3_C1->Fill(hit3.toacode(), hit2.toacode());

                    hm->hTOA0vsTOA1_C1->Fill(hit1.toa(), hit0.toa());
                    hm->hTOA0vsTOA2_C1->Fill(hit2.toa(), hit0.toa());
                    hm->hTOA0vsTOA3_C1->Fill(hit3.toa(), hit0.toa());
                    hm->hTOA1vsTOA2_C1->Fill(hit2.toa(), hit1.toa());
                    hm->hTOA1vsTOA3_C1->Fill(hit3.toa(), hit1.toa());
                    hm->hTOA2vsTOA3_C1->Fill(hit3.toa(), hit2.toa());
                }

                if (AllPass[0] && AllPass[1] && AllPass[2] && AllPass[3])
                {
                    hm->pDTOA01CodevsTOTCode[0]->Fill(hit0.totcode(), hit0.toacode() - hit1.toacode());
                    hm->hDTOA01CodevsTOTCode[0]->Fill(hit0.totcode(), hit0.toacode() - hit1.toacode());
                    hm->pDTOA01CodevsTOTCode[1]->Fill(hit1.totcode(), hit0.toacode() - hit1.toacode());
                    hm->hDTOA01CodevsTOTCode[1]->Fill(hit1.totcode(), hit0.toacode() - hit1.toacode());
                    hm->pDTOA02CodevsTOTCode[0]->Fill(hit0.totcode(), hit0.toacode() - hit2.toacode());
                    hm->hDTOA02CodevsTOTCode[0]->Fill(hit0.totcode(), hit0.toacode() - hit2.toacode());
                    hm->pDTOA02CodevsTOTCode[1]->Fill(hit2.totcode(), hit0.toacode() - hit2.toacode());
                    hm->hDTOA02CodevsTOTCode[1]->Fill(hit2.totcode(), hit0.toacode() - hit2.toacode());
                    hm->pDTOA03CodevsTOTCode[0]->Fill(hit0.totcode(), hit0.toacode() - hit3.toacode());
                    hm->hDTOA03CodevsTOTCode[0]->Fill(hit0.totcode(), hit0.toacode() - hit3.toacode());
                    hm->pDTOA03CodevsTOTCode[1]->Fill(hit3.totcode(), hit0.toacode() - hit3.toacode());
                    hm->hDTOA03CodevsTOTCode[1]->Fill(hit3.totcode(), hit0.toacode() - hit3.toacode());
                    hm->pDTOA12CodevsTOTCode[0]->Fill(hit1.totcode(), hit1.toacode() - hit2.toacode());
                    hm->hDTOA12CodevsTOTCode[0]->Fill(hit1.totcode(), hit1.toacode() - hit2.toacode());
                    hm->pDTOA12CodevsTOTCode[1]->Fill(hit2.totcode(), hit1.toacode() - hit2.toacode());
                    hm->hDTOA12CodevsTOTCode[1]->Fill(hit2.totcode(), hit1.toacode() - hit2.toacode());
                    hm->pDTOA13CodevsTOTCode[0]->Fill(hit1.totcode(), hit1.toacode() - hit3.toacode());
                    hm->hDTOA13CodevsTOTCode[0]->Fill(hit1.totcode(), hit1.toacode() - hit3.toacode());
                    hm->pDTOA13CodevsTOTCode[1]->Fill(hit3.totcode(), hit1.toacode() - hit3.toacode());
                    hm->hDTOA13CodevsTOTCode[1]->Fill(hit3.totcode(), hit1.toacode() - hit3.toacode());
                    hm->pDTOA23CodevsTOTCode[0]->Fill(hit2.totcode(), hit2.toacode() - hit3.toacode());
                    hm->hDTOA23CodevsTOTCode[0]->Fill(hit2.totcode(), hit2.toacode() - hit3.toacode());
                    hm->pDTOA23CodevsTOTCode[1]->Fill(hit3.totcode(), hit2.toacode() - hit3.toacode());
                    hm->hDTOA23CodevsTOTCode[1]->Fill(hit3.totcode(), hit2.toacode() - hit3.toacode());

                    hm->pDTOA01vsTOT[0]->Fill(hit0.tot(), hit0.toa() - hit1.toa());
                    hm->hDTOA01vsTOT[0]->Fill(hit0.tot(), hit0.toa() - hit1.toa());
                    hm->pDTOA01vsTOT[1]->Fill(hit1.tot(), hit0.toa() - hit1.toa());
                    hm->hDTOA01vsTOT[1]->Fill(hit1.tot(), hit0.toa() - hit1.toa());
                    hm->pDTOA02vsTOT[0]->Fill(hit0.tot(), hit0.toa() - hit2.toa());
                    hm->hDTOA02vsTOT[0]->Fill(hit0.tot(), hit0.toa() - hit2.toa());
                    hm->pDTOA02vsTOT[1]->Fill(hit2.tot(), hit0.toa() - hit2.toa());
                    hm->hDTOA02vsTOT[1]->Fill(hit2.tot(), hit0.toa() - hit2.toa());
                    hm->pDTOA03vsTOT[0]->Fill(hit0.tot(), hit0.toa() - hit3.toa());
                    hm->hDTOA03vsTOT[0]->Fill(hit0.tot(), hit0.toa() - hit3.toa());
                    hm->pDTOA03vsTOT[1]->Fill(hit3.tot(), hit0.toa() - hit3.toa());
                    hm->hDTOA03vsTOT[1]->Fill(hit3.tot(), hit0.toa() - hit3.toa());
                    hm->pDTOA12vsTOT[0]->Fill(hit1.tot(), hit1.toa() - hit2.toa());
                    hm->hDTOA12vsTOT[0]->Fill(hit1.tot(), hit1.toa() - hit2.toa());
                    hm->pDTOA12vsTOT[1]->Fill(hit2.tot(), hit1.toa() - hit2.toa());
                    hm->hDTOA12vsTOT[1]->Fill(hit2.tot(), hit1.toa() - hit2.toa());
                    hm->pDTOA13vsTOT[0]->Fill(hit1.tot(), hit1.toa() - hit3.toa());
                    hm->hDTOA13vsTOT[0]->Fill(hit1.tot(), hit1.toa() - hit3.toa());
                    hm->pDTOA13vsTOT[1]->Fill(hit3.tot(), hit1.toa() - hit3.toa());
                    hm->hDTOA13vsTOT[1]->Fill(hit3.tot(), hit1.toa() - hit3.toa());
                    hm->pDTOA23vsTOT[0]->Fill(hit2.tot(), hit2.toa() - hit3.toa());
                    hm->hDTOA23vsTOT[0]->Fill(hit2.tot(), hit2.toa() - hit3.toa());
                    hm->pDTOA23vsTOT[1]->Fill(hit3.tot(), hit2.toa() - hit3.toa());
                    hm->hDTOA23vsTOT[1]->Fill(hit3.tot(), hit2.toa() - hit3.toa());

                    hm->hTOACode0vsTOACode1_C2->Fill(hit1.toacode(), hit0.toacode());
                    hm->hTOACode0vsTOACode2_C2->Fill(hit2.toacode(), hit0.toacode());
                    hm->hTOACode0vsTOACode3_C2->Fill(hit3.toacode(), hit0.toacode());
                    hm->hTOACode1vsTOACode2_C2->Fill(hit2.toacode(), hit1.toacode());
                    hm->hTOACode1vsTOACode3_C2->Fill(hit3.toacode(), hit1.toacode());
                    hm->hTOACode2vsTOACode3_C2->Fill(hit3.toacode(), hit2.toacode());

                    hm->hTOA0vsTOA1_C2->Fill(hit1.toa(), hit0.toa());
                    hm->hTOA0vsTOA2_C2->Fill(hit2.toa(), hit0.toa());
                    hm->hTOA0vsTOA3_C2->Fill(hit3.toa(), hit0.toa());
                    hm->hTOA1vsTOA2_C2->Fill(hit2.toa(), hit1.toa());
                    hm->hTOA1vsTOA3_C2->Fill(hit3.toa(), hit1.toa());
                    hm->hTOA2vsTOA3_C2->Fill(hit3.toa(), hit2.toa());
                }
            }

            if (isRightSide && RightPass[0] && RightPass[1] && RightPass[2] && RightPass[3])
            {
                hm->hTOACode0vsTOACode1_C0->Fill(hit0.toacode(), hit1.toacode());
                hm->hTOACode0vsTOACode2_C0->Fill(hit0.toacode(), hit2.toacode());
                hm->hTOACode0vsTOACode3_C0->Fill(hit0.toacode(), hit3.toacode());
                hm->hTOACode1vsTOACode2_C0->Fill(hit1.toacode(), hit2.toacode());
                hm->hTOACode1vsTOACode3_C0->Fill(hit1.toacode(), hit3.toacode());
                hm->hTOACode2vsTOACode3_C0->Fill(hit2.toacode(), hit3.toacode());

                hm->hTOA0vsTOA1_C0->Fill(hit1.toa(), hit0.toa());
                hm->hTOA0vsTOA2_C0->Fill(hit2.toa(), hit0.toa());
                hm->hTOA0vsTOA3_C0->Fill(hit3.toa(), hit0.toa());
                hm->hTOA1vsTOA2_C0->Fill(hit2.toa(), hit1.toa());
                hm->hTOA1vsTOA3_C0->Fill(hit3.toa(), hit1.toa());
                hm->hTOA2vsTOA3_C0->Fill(hit3.toa(), hit2.toa());
                if (TOAPass[0] && TOAPass[1] && TOAPass[2] && TOAPass[3])
                {

                    hm->hTOACode0vsTOACode1_C1->Fill(hit1.toacode(), hit0.toacode());
                    hm->hTOACode0vsTOACode2_C1->Fill(hit2.toacode(), hit0.toacode());
                    hm->hTOACode0vsTOACode3_C1->Fill(hit3.toacode(), hit0.toacode());
                    hm->hTOACode1vsTOACode2_C1->Fill(hit2.toacode(), hit1.toacode());
                    hm->hTOACode1vsTOACode3_C1->Fill(hit3.toacode(), hit1.toacode());
                    hm->hTOACode2vsTOACode3_C1->Fill(hit3.toacode(), hit2.toacode());

                    hm->hTOA0vsTOA1_C1->Fill(hit1.toa(), hit0.toa());
                    hm->hTOA0vsTOA2_C1->Fill(hit2.toa(), hit0.toa());
                    hm->hTOA0vsTOA3_C1->Fill(hit3.toa(), hit0.toa());
                    hm->hTOA1vsTOA2_C1->Fill(hit2.toa(), hit1.toa());
                    hm->hTOA1vsTOA3_C1->Fill(hit3.toa(), hit1.toa());
                    hm->hTOA2vsTOA3_C1->Fill(hit3.toa(), hit2.toa());
                }

                if (AllPass[0] && AllPass[1] && AllPass[2] && AllPass[3])
                {
                    hm->pDTOA01CodevsTOTCode[0]->Fill(hit0.totcode(), hit0.toacode() - hit1.toacode());
                    hm->hDTOA01CodevsTOTCode[0]->Fill(hit0.totcode(), hit0.toacode() - hit1.toacode());
                    hm->pDTOA01CodevsTOTCode[1]->Fill(hit1.totcode(), hit0.toacode() - hit1.toacode());
                    hm->hDTOA01CodevsTOTCode[1]->Fill(hit1.totcode(), hit0.toacode() - hit1.toacode());
                    hm->pDTOA02CodevsTOTCode[0]->Fill(hit0.totcode(), hit0.toacode() - hit2.toacode());
                    hm->hDTOA02CodevsTOTCode[0]->Fill(hit0.totcode(), hit0.toacode() - hit2.toacode());
                    hm->pDTOA02CodevsTOTCode[1]->Fill(hit2.totcode(), hit0.toacode() - hit2.toacode());
                    hm->hDTOA02CodevsTOTCode[1]->Fill(hit2.totcode(), hit0.toacode() - hit2.toacode());
                    hm->pDTOA03CodevsTOTCode[0]->Fill(hit0.totcode(), hit0.toacode() - hit3.toacode());
                    hm->hDTOA03CodevsTOTCode[0]->Fill(hit0.totcode(), hit0.toacode() - hit3.toacode());
                    hm->pDTOA03CodevsTOTCode[1]->Fill(hit3.totcode(), hit0.toacode() - hit3.toacode());
                    hm->hDTOA03CodevsTOTCode[1]->Fill(hit3.totcode(), hit0.toacode() - hit3.toacode());
                    hm->pDTOA12CodevsTOTCode[0]->Fill(hit1.totcode(), hit1.toacode() - hit2.toacode());
                    hm->hDTOA12CodevsTOTCode[0]->Fill(hit1.totcode(), hit1.toacode() - hit2.toacode());
                    hm->pDTOA12CodevsTOTCode[1]->Fill(hit2.totcode(), hit1.toacode() - hit2.toacode());
                    hm->hDTOA12CodevsTOTCode[1]->Fill(hit2.totcode(), hit1.toacode() - hit2.toacode());
                    hm->pDTOA13CodevsTOTCode[0]->Fill(hit1.totcode(), hit1.toacode() - hit3.toacode());
                    hm->hDTOA13CodevsTOTCode[0]->Fill(hit1.totcode(), hit1.toacode() - hit3.toacode());
                    hm->pDTOA13CodevsTOTCode[1]->Fill(hit3.totcode(), hit1.toacode() - hit3.toacode());
                    hm->hDTOA13CodevsTOTCode[1]->Fill(hit3.totcode(), hit1.toacode() - hit3.toacode());
                    hm->pDTOA23CodevsTOTCode[0]->Fill(hit2.totcode(), hit2.toacode() - hit3.toacode());
                    hm->hDTOA23CodevsTOTCode[0]->Fill(hit2.totcode(), hit2.toacode() - hit3.toacode());
                    hm->pDTOA23CodevsTOTCode[1]->Fill(hit3.totcode(), hit2.toacode() - hit3.toacode());
                    hm->hDTOA23CodevsTOTCode[1]->Fill(hit3.totcode(), hit2.toacode() - hit3.toacode());

                    hm->pDTOA01vsTOT[0]->Fill(hit0.tot(), hit0.toa() - hit1.toa());
                    hm->hDTOA01vsTOT[0]->Fill(hit0.tot(), hit0.toa() - hit1.toa());
                    hm->pDTOA01vsTOT[1]->Fill(hit1.tot(), hit0.toa() - hit1.toa());
                    hm->hDTOA01vsTOT[1]->Fill(hit1.tot(), hit0.toa() - hit1.toa());
                    hm->pDTOA02vsTOT[0]->Fill(hit0.tot(), hit0.toa() - hit2.toa());
                    hm->hDTOA02vsTOT[0]->Fill(hit0.tot(), hit0.toa() - hit2.toa());
                    hm->pDTOA02vsTOT[1]->Fill(hit2.tot(), hit0.toa() - hit2.toa());
                    hm->hDTOA02vsTOT[1]->Fill(hit2.tot(), hit0.toa() - hit2.toa());
                    hm->pDTOA03vsTOT[0]->Fill(hit0.tot(), hit0.toa() - hit3.toa());
                    hm->hDTOA03vsTOT[0]->Fill(hit0.tot(), hit0.toa() - hit3.toa());
                    hm->pDTOA03vsTOT[1]->Fill(hit3.tot(), hit0.toa() - hit3.toa());
                    hm->hDTOA03vsTOT[1]->Fill(hit3.tot(), hit0.toa() - hit3.toa());
                    hm->pDTOA12vsTOT[0]->Fill(hit1.tot(), hit1.toa() - hit2.toa());
                    hm->hDTOA12vsTOT[0]->Fill(hit1.tot(), hit1.toa() - hit2.toa());
                    hm->pDTOA12vsTOT[1]->Fill(hit2.tot(), hit1.toa() - hit2.toa());
                    hm->hDTOA12vsTOT[1]->Fill(hit2.tot(), hit1.toa() - hit2.toa());
                    hm->pDTOA13vsTOT[0]->Fill(hit1.tot(), hit1.toa() - hit3.toa());
                    hm->hDTOA13vsTOT[0]->Fill(hit1.tot(), hit1.toa() - hit3.toa());
                    hm->pDTOA13vsTOT[1]->Fill(hit3.tot(), hit1.toa() - hit3.toa());
                    hm->hDTOA13vsTOT[1]->Fill(hit3.tot(), hit1.toa() - hit3.toa());
                    hm->pDTOA23vsTOT[0]->Fill(hit2.tot(), hit2.toa() - hit3.toa());
                    hm->hDTOA23vsTOT[0]->Fill(hit2.tot(), hit2.toa() - hit3.toa());
                    hm->pDTOA23vsTOT[1]->Fill(hit3.tot(), hit2.toa() - hit3.toa());
                    hm->hDTOA23vsTOT[1]->Fill(hit3.tot(), hit2.toa() - hit3.toa());

                    hm->hTOACode0vsTOACode1_C2->Fill(hit1.toacode(), hit0.toacode());
                    hm->hTOACode0vsTOACode2_C2->Fill(hit2.toacode(), hit0.toacode());
                    hm->hTOACode0vsTOACode3_C2->Fill(hit3.toacode(), hit0.toacode());
                    hm->hTOACode1vsTOACode2_C2->Fill(hit2.toacode(), hit1.toacode());
                    hm->hTOACode1vsTOACode3_C2->Fill(hit3.toacode(), hit1.toacode());
                    hm->hTOACode2vsTOACode3_C2->Fill(hit3.toacode(), hit2.toacode());

                    hm->hTOA0vsTOA1_C2->Fill(hit1.toa(), hit0.toa());
                    hm->hTOA0vsTOA2_C2->Fill(hit2.toa(), hit0.toa());
                    hm->hTOA0vsTOA3_C2->Fill(hit3.toa(), hit0.toa());
                    hm->hTOA1vsTOA2_C2->Fill(hit2.toa(), hit1.toa());
                    hm->hTOA1vsTOA3_C2->Fill(hit3.toa(), hit1.toa());
                    hm->hTOA2vsTOA3_C2->Fill(hit3.toa(), hit2.toa());
                }
            }
        }
    }

    hm->projection();
    TString outFile;
    if (isLeftSide)
    {
        outFile = "oReadEtroc2_4Boards_LeftSide.root";
    }

    if (isRightSide)
    {
        outFile = "oReadEtroc2_4Boards_RightSide.root";
    }

    if (isLeftSide && isRightSide)
    {
        outFile = "oReadEtroc2_4Boards_Combined.root";
    }

    TFile *oFile = new TFile(Form("%s", outFile.Data()), "recreate");
    hm->writeOutput();
    oFile->Write();
    oFile->Close();

    return 0;
}