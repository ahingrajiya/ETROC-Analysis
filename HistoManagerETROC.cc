/**
 * @file HistoManagerETROC.cc
 * @author Abhishek Hingrajiya (abhi.h123@gmail.com)
 * @brief Histogram Manager for ETROC
 * @version 0.1
 * @date 2024-08-21
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "HistoManagerETROC.h"

// ROOT Objects
#include "TObject.h"
#include "TIterator.h"
#include "TString.h"
#include "TClass.h"
#include "TKey.h"
#include "TROOT.h"
#include "TSystem.h"

ClassImp(HistoManagerETROC)

    HistoManagerETROC::HistoManagerETROC() : fNBoards{2}, hDROWvsDCOL{nullptr},
                                             hTOA_Code1vsTOA_Code0_C0{nullptr}, hTOA_Code1vsTOA_Code0_C1{nullptr}, hTOA_Code1vsTOA_Code0_C2{nullptr},
                                             hTOA_Code1vsTOA_Code0_TWC_C0{nullptr}, hTOA_Code1vsTOA_Code0_TWC_C1{nullptr}, hTOA_Code1vsTOA_Code0_TWC_C2{nullptr},
                                             hTOA1vsTOA0_C0{nullptr}, hTOA1vsTOA0_C1{nullptr}, hTOA1vsTOA0_C2{nullptr},
                                             hTOA1vsTOA0_TWC_C0{nullptr}, hTOA1vsTOA0_TWC_C1{nullptr}, hTOA1vsTOA0_TWC_C2{nullptr},
                                             hTOACodevsTOTCode_C0{nullptr}, hTOACodevsTOTCode_C1{nullptr}, hTOACodevsTOTCode_C2{nullptr},
                                             hTOACode_TWCvsTOTCode_C0{nullptr}, hTOACode_TWCvsTOTCode_C1{nullptr}, hTOACode_TWCvsTOTCode_C2{nullptr},
                                             hTOAvsTOT_C0{nullptr}, hTOAvsTOT_C1{nullptr}, hTOAvsTOT_C2{nullptr},
                                             hTOA_TWCvsTOT_C0{nullptr}, hTOA_TWCvsTOT_C1{nullptr}, hTOA_TWCvsTOT_C2{nullptr},
                                             hDTOACodevsTOTCode_C0{nullptr}, hDTOACodevsTOTCode_C1{nullptr}, hDTOACodevsTOTCode_C2{nullptr},
                                             hDTOACode_TWCvsTOTCode_C0{nullptr}, hDTOACode_TWCvsTOTCode_C1{nullptr}, hDTOACode_TWCvsTOTCode_C2{nullptr},
                                             hDTOACode_TWC0vsTOTCode_C0{nullptr}, hDTOACode_TWC0vsTOTCode_C1{nullptr}, hDTOACode_TWC0vsTOTCode_C2{nullptr},
                                             hDTOACode_TWC1vsTOTCode_C0{nullptr}, hDTOACode_TWC1vsTOTCode_C1{nullptr}, hDTOACode_TWC1vsTOTCode_C2{nullptr},
                                             hDTOAvsTOT_C0{nullptr}, hDTOAvsTOT_C1{nullptr}, hDTOAvsTOT_C2{nullptr},
                                             hDTOA_TWCvsTOT_C0{nullptr}, hDTOA_TWCvsTOT_C1{nullptr}, hDTOA_TWCvsTOT_C2{nullptr},
                                             hDTOA_TWC0vsTOT_C0{nullptr}, hDTOA_TWC0vsTOT_C1{nullptr}, hDTOA_TWC0vsTOT_C2{nullptr},
                                             hDTOA_TWC1vsTOT_C0{nullptr}, hDTOA_TWC1vsTOT_C1{nullptr}, hDTOA_TWC1vsTOT_C2{nullptr},
                                             hTOACodevsCALCode_C0{nullptr}, hTOACodevsCALCode_C1{nullptr}, hTOACodevsCALCode_C2{nullptr},
                                             hTOACode_TWCvsCALCode_C0{nullptr}, hTOACode_TWCvsCALCode_C1{nullptr}, hTOACode_TWCvsCALCode_C2{nullptr},
                                             hTOAvsCAL_C0{nullptr}, hTOAvsCAL_C1{nullptr}, hTOAvsCAL_C2{nullptr},
                                             hTOA_TWCvsCAL_C0{nullptr}, hTOA_TWCvsCAL_C1{nullptr}, hTOA_TWCvsCAL_C2{nullptr},
                                             hTOTCodevsCALCode_C0{nullptr}, hTOTCodevsCALCode_C1{nullptr}, hTOTCodevsCALCode_C2{nullptr},
                                             hTOTvsCAL_C0{nullptr}, hTOTvsCAL_C1{nullptr}, hTOTvsCAL_C2{nullptr},
                                             hTOACode_C0{nullptr}, hTOACode_C1{nullptr}, hTOACode_C2{nullptr},
                                             hDTOACode_C0{nullptr}, hDTOACode_C1{nullptr}, hDTOACode_C2{nullptr},
                                             hTOACode_TWC_C0{nullptr}, hTOACode_TWC_C1{nullptr}, hTOACode_TWC_C2{nullptr},
                                             hDTOACode_TWC_C0{nullptr}, hDTOACode_TWC_C1{nullptr}, hDTOACode_TWC_C2{nullptr},
                                             hDTOACode_TWC0_C0{nullptr}, hDTOACode_TWC0_C1{nullptr}, hDTOACode_TWC0_C2{nullptr},
                                             hDTOACode_TWC1_C0{nullptr}, hDTOACode_TWC1_C1{nullptr}, hDTOACode_TWC1_C2{nullptr},
                                             hTOA_C0{nullptr}, hTOA_C1{nullptr}, hTOA_C2{nullptr},
                                             hDTOA_C0{nullptr}, hDTOA_C1{nullptr}, hDTOA_C2{nullptr},
                                             hTOA_TWC_C0{nullptr}, hTOA_TWC_C1{nullptr}, hTOA_TWC_C2{nullptr},
                                             hDTOA_TWC_C0{nullptr}, hDTOA_TWC_C1{nullptr}, hDTOA_TWC_C2{nullptr},
                                             hDTOA_TWC0_C0{nullptr}, hDTOA_TWC0_C1{nullptr}, hDTOA_TWC0_C2{nullptr},
                                             hDTOA_TWC1_C0{nullptr}, hDTOA_TWC1_C1{nullptr}, hDTOA_TWC1_C2{nullptr},
                                             hTOTCode_C0{nullptr}, hTOTCode_C1{nullptr}, hTOTCode_C2{nullptr},
                                             hTOT_C0{nullptr}, hTOT_C1{nullptr}, hTOT_C2{nullptr},
                                             hCAL_C0{nullptr}, hCAL_C1{nullptr}, hCAL_C2{nullptr},
                                             pDTOACodevsTOTCode{nullptr}, pDTOAvsTOT{nullptr}

{
    /* Empty */
}
HistoManagerETROC::~HistoManagerETROC()
{
    if (hDROWvsDCOL)
        delete hDROWvsDCOL;

    if (hTOA_Code1vsTOA_Code0_C0)
        delete hTOA_Code1vsTOA_Code0_C0;
    if (hTOA_Code1vsTOA_Code0_C1)
        delete hTOA_Code1vsTOA_Code0_C1;
    if (hTOA_Code1vsTOA_Code0_C2)
        delete hTOA_Code1vsTOA_Code0_C2;

    if (hTOA_Code1vsTOA_Code0_TWC_C0)
        delete hTOA_Code1vsTOA_Code0_TWC_C0;
    if (hTOA_Code1vsTOA_Code0_TWC_C1)
        delete hTOA_Code1vsTOA_Code0_TWC_C1;
    if (hTOA_Code1vsTOA_Code0_TWC_C2)
        delete hTOA_Code1vsTOA_Code0_TWC_C2;

    if (hTOA1vsTOA0_C0)
        delete hTOA1vsTOA0_C0;
    if (hTOA1vsTOA0_C1)
        delete hTOA1vsTOA0_C1;
    if (hTOA1vsTOA0_C2)
        delete hTOA1vsTOA0_C2;

    if (hTOA1vsTOA0_TWC_C0)
        delete hTOA1vsTOA0_TWC_C0;
    if (hTOA1vsTOA0_TWC_C1)
        delete hTOA1vsTOA0_TWC_C1;
    if (hTOA1vsTOA0_TWC_C2)
        delete hTOA1vsTOA0_TWC_C0;

    for (int i = 0; i < fNBoards; i++)
    {
        if (hTOACodevsTOTCode_C0[i])
            delete hTOACodevsTOTCode_C0[i];
        if (hTOACodevsTOTCode_C1[i])
            delete hTOACodevsTOTCode_C1[i];
        if (hTOACodevsTOTCode_C2[i])
            delete hTOACodevsTOTCode_C2[i];

        if (hTOACode_TWCvsTOTCode_C0[i])
            delete hTOACode_TWCvsTOTCode_C0[i];
        if (hTOACode_TWCvsTOTCode_C1[i])
            delete hTOACode_TWCvsTOTCode_C1[i];
        if (hTOACode_TWCvsTOTCode_C2[i])
            delete hTOACode_TWCvsTOTCode_C2[i];

        if (hTOAvsTOT_C0[i])
            delete hTOAvsTOT_C0[i];
        if (hTOAvsTOT_C1[i])
            delete hTOAvsTOT_C1[i];
        if (hTOAvsTOT_C2[i])
            delete hTOAvsTOT_C2[i];

        if (hTOA_TWCvsTOT_C0[i])
            delete hTOA_TWCvsTOT_C0[i];
        if (hTOA_TWCvsTOT_C1[i])
            delete hTOA_TWCvsTOT_C1[i];
        if (hTOA_TWCvsTOT_C2[i])
            delete hTOA_TWCvsTOT_C2[i];

        if (hDTOACodevsTOTCode_C0[i])
            delete hDTOACodevsTOTCode_C0[i];
        if (hDTOACodevsTOTCode_C1[i])
            delete hDTOACodevsTOTCode_C1[i];
        if (hDTOACodevsTOTCode_C2[i])
            delete hDTOACodevsTOTCode_C2[i];

        if (hDTOACode_TWCvsTOTCode_C0[i])
            delete hDTOACode_TWCvsTOTCode_C0[i];
        if (hDTOACode_TWCvsTOTCode_C1[i])
            delete hDTOACode_TWCvsTOTCode_C1[i];
        if (hDTOACode_TWCvsTOTCode_C2[i])
            delete hDTOACode_TWCvsTOTCode_C2[i];

        if (hDTOACode_TWC0vsTOTCode_C0[i])
            delete hDTOACode_TWC0vsTOTCode_C0[i];
        if (hDTOACode_TWC0vsTOTCode_C1[i])
            delete hDTOACode_TWC0vsTOTCode_C1[i];
        if (hDTOACode_TWC0vsTOTCode_C2[i])
            delete hDTOACode_TWC0vsTOTCode_C2[i];

        if (hDTOACode_TWC1vsTOTCode_C0[i])
            delete hDTOACode_TWC1vsTOTCode_C0[i];
        if (hDTOACode_TWC1vsTOTCode_C1[i])
            delete hDTOACode_TWC1vsTOTCode_C1[i];
        if (hDTOACode_TWC1vsTOTCode_C2[i])
            delete hDTOACode_TWC1vsTOTCode_C2[i];

        if (hDTOAvsTOT_C0[i])
            delete hDTOAvsTOT_C0[i];
        if (hDTOAvsTOT_C1[i])
            delete hDTOAvsTOT_C1[i];
        if (hDTOAvsTOT_C2[i])
            delete hDTOAvsTOT_C2[i];

        if (hDTOA_TWCvsTOT_C0[i])
            delete hDTOA_TWCvsTOT_C0[i];
        if (hDTOA_TWCvsTOT_C1[i])
            delete hDTOA_TWCvsTOT_C1[i];
        if (hDTOA_TWCvsTOT_C2[i])
            delete hDTOA_TWCvsTOT_C2[i];

        if (hDTOA_TWC0vsTOT_C0[i])
            delete hDTOA_TWC0vsTOT_C0[i];
        if (hDTOA_TWC0vsTOT_C1[i])
            delete hDTOA_TWC0vsTOT_C1[i];
        if (hDTOA_TWC0vsTOT_C2[i])
            delete hDTOA_TWC0vsTOT_C2[i];

        if (hDTOA_TWC1vsTOT_C0[i])
            delete hDTOA_TWC1vsTOT_C0[i];
        if (hDTOA_TWC1vsTOT_C1[i])
            delete hDTOA_TWC1vsTOT_C1[i];
        if (hDTOA_TWC1vsTOT_C2[i])
            delete hDTOA_TWC1vsTOT_C2[i];

        if (hTOACodevsCALCode_C0[i])
            delete hTOACodevsCALCode_C0[i];
        if (hTOACodevsCALCode_C1[i])
            delete hTOACodevsCALCode_C1[i];
        if (hTOACodevsCALCode_C2[i])
            delete hTOACodevsCALCode_C2[i];

        if (hTOACode_TWCvsCALCode_C0[i])
            delete hTOACode_TWCvsCALCode_C0[i];
        if (hTOACode_TWCvsCALCode_C1[i])
            delete hTOACode_TWCvsCALCode_C1[i];
        if (hTOACode_TWCvsCALCode_C2[i])
            delete hTOACode_TWCvsCALCode_C2[i];

        if (hTOAvsCAL_C0[i])
            delete hTOAvsCAL_C0[i];
        if (hTOAvsCAL_C1[i])
            delete hTOAvsCAL_C1[i];
        if (hTOAvsCAL_C2[i])
            delete hTOAvsCAL_C2[i];

        if (hTOA_TWCvsCAL_C0[i])
            delete hTOA_TWCvsCAL_C0[i];
        if (hTOA_TWCvsCAL_C1[i])
            delete hTOA_TWCvsCAL_C1[i];
        if (hTOA_TWCvsCAL_C2[i])
            delete hTOA_TWCvsCAL_C2[i];

        if (hTOTCodevsCALCode_C0[i])
            delete hTOTCodevsCALCode_C0[i];
        if (hTOTCodevsCALCode_C1[i])
            delete hTOTCodevsCALCode_C1[i];
        if (hTOTCodevsCALCode_C2[i])
            delete hTOTCodevsCALCode_C2[i];

        if (hTOTvsCAL_C0[i])
            delete hTOTvsCAL_C0[i];
        if (hTOTvsCAL_C1[i])
            delete hTOTvsCAL_C1[i];
        if (hTOTvsCAL_C2[i])
            delete hTOTvsCAL_C2[i];

        if (hTOACode_C0[i])
            delete hTOACode_C0[i];
        if (hTOACode_C1[i])
            delete hTOACode_C1[i];
        if (hTOACode_C2[i])
            delete hTOACode_C2[i];

        if (hTOACode_TWC_C0[i])
            delete hTOACode_TWC_C0[i];
        if (hTOACode_TWC_C1[i])
            delete hTOACode_TWC_C1[i];
        if (hTOACode_TWC_C2[i])
            delete hTOACode_TWC_C2[i];

        if (hDTOACode_C0[i])
            delete hDTOACode_C0[i];
        if (hDTOACode_C1[i])
            delete hDTOACode_C1[i];
        if (hDTOACode_C2[i])
            delete hDTOACode_C2[i];

        if (hDTOACode_TWC_C0[i])
            delete hDTOACode_TWC_C0[i];
        if (hDTOACode_TWC_C1[i])
            delete hDTOACode_TWC_C1[i];
        if (hDTOACode_TWC_C2[i])
            delete hDTOACode_TWC_C2[i];

        if (hDTOACode_TWC0_C0[i])
            delete hDTOACode_TWC0_C0[i];
        if (hDTOACode_TWC0_C1[i])
            delete hDTOACode_TWC0_C1[i];
        if (hDTOACode_TWC0_C2[i])
            delete hDTOACode_TWC0_C2[i];

        if (hDTOACode_TWC1_C0[i])
            delete hDTOACode_TWC1_C0[i];
        if (hDTOACode_TWC1_C1[i])
            delete hDTOACode_TWC1_C1[i];
        if (hDTOACode_TWC1_C2[i])
            delete hDTOACode_TWC1_C2[i];

        if (hTOA_C0[i])
            delete hTOA_C0[i];
        if (hTOA_C1[i])
            delete hTOA_C1[i];
        if (hTOA_C2[i])
            delete hTOA_C2[i];

        if (hTOA_TWC_C0[i])
            delete hTOA_TWC_C0[i];
        if (hTOA_TWC_C1[i])
            delete hTOA_TWC_C1[i];
        if (hTOA_TWC_C2[i])
            delete hTOA_TWC_C2[i];

        if (hDTOA_C0[i])
            delete hDTOA_C0[i];
        if (hDTOA_C1[i])
            delete hDTOA_C1[i];
        if (hDTOA_C2[i])
            delete hDTOA_C2[i];

        if (hDTOA_TWC_C0[i])
            delete hDTOA_TWC_C0[i];
        if (hDTOA_TWC_C1[i])
            delete hDTOA_TWC_C1[i];
        if (hDTOA_TWC_C2[i])
            delete hDTOA_TWC_C2[i];

        if (hDTOA_TWC0_C0[i])
            delete hDTOA_TWC0_C0[i];
        if (hDTOA_TWC0_C1[i])
            delete hDTOA_TWC0_C1[i];
        if (hDTOA_TWC0_C2[i])
            delete hDTOA_TWC0_C2[i];

        if (hDTOA_TWC1_C0[i])
            delete hDTOA_TWC1_C0[i];
        if (hDTOA_TWC1_C1[i])
            delete hDTOA_TWC1_C1[i];
        if (hDTOA_TWC1_C2[i])
            delete hDTOA_TWC1_C2[i];

        if (hTOTCode_C0[i])
            delete hTOTCode_C0[i];
        if (hTOTCode_C1[i])
            delete hTOTCode_C1[i];
        if (hTOTCode_C2[i])
            delete hTOTCode_C2[i];

        if (hTOT_C0[i])
            delete hTOT_C0[i];
        if (hTOT_C1[i])
            delete hTOT_C1[i];
        if (hTOT_C2[i])
            delete hTOT_C2[i];

        if (hCAL_C0[i])
            delete hCAL_C0[i];
        if (hCAL_C1[i])
            delete hCAL_C1[i];
        if (hCAL_C2[i])
            delete hCAL_C2[i];

        if (pDTOACodevsTOTCode[i])
            delete pDTOACodevsTOTCode[i];
        if (pDTOAvsTOT[i])
            delete pDTOAvsTOT[i];
    }
}

void HistoManagerETROC::init()
{
    hDROWvsDCOL = new TH2D("hDROWvsDCOL", "DROW vs DCOL;#DeltaCOL;#DeltaROW", 32, -16., 16., 32, -16., 16.);

    Int_t TOACodeBins = 750;
    Float_t TOACodeRange[2] = {0.0, 750.};

    hTOA_Code1vsTOA_Code0_C0 = new TH2D("hTOA_Code1vsTOA_Code0_C0", "TOA_Code1 TOA_Code0 C0; TOACode0; TOACode1", TOACodeBins, TOACodeRange[0], TOACodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
    hTOA_Code1vsTOA_Code0_C0->Sumw2();
    hTOA_Code1vsTOA_Code0_C1 = new TH2D("hTOA_Code1vsTOA_Code0_C1", "TOA_Code1 TOA_Code0 C1; TOACode0; TOACode1", TOACodeBins, TOACodeRange[0], TOACodeRange[1], TOACodeBins, TOACodeRange[1], TOACodeRange[1]);
    hTOA_Code1vsTOA_Code0_C1->Sumw2();
    hTOA_Code1vsTOA_Code0_C2 = new TH2D("hTOA_Code1vsTOA_Code0_C2", "TOA_Code1 TOA_Code0 C2; TOACode0; TOACode1", TOACodeBins, TOACodeRange[0], TOACodeRange[1], TOACodeBins, TOACodeRange[1], TOACodeRange[1]);
    hTOA_Code1vsTOA_Code0_C2->Sumw2();

    hTOA_Code1vsTOA_Code0_TWC_C0 = new TH2D("hTOA_Code1vsTOA_Code0_TWC_C0", "TOA_Code1 TOA_Code0 TWC C0; TOACode0; TOACode1", TOACodeBins, TOACodeRange[0], TOACodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
    hTOA_Code1vsTOA_Code0_TWC_C0->Sumw2();
    hTOA_Code1vsTOA_Code0_TWC_C1 = new TH2D("hTOA_Code1vsTOA_Code0_TWC_C1", "TOA_Code1 TOA_Code0 TWC C1; TOACode0; TOACode1", TOACodeBins, TOACodeRange[0], TOACodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
    hTOA_Code1vsTOA_Code0_TWC_C1->Sumw2();
    hTOA_Code1vsTOA_Code0_TWC_C2 = new TH2D("hTOA_Code1vsTOA_Code0_TWC_C2", "TOA_Code1 TOA_Code0 TWC C2; TOACode0; TOACode1", TOACodeBins, TOACodeRange[0], TOACodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
    hTOA_Code1vsTOA_Code0_TWC_C2->Sumw2();

    Int_t TOABins = 250;
    Float_t TOARange[4] = {0.0, 12.5};

    hTOA1vsTOA0_C0 = new TH2D("hTOA1vsTOA0_C0", "TOA1 vs TOA0 C0; TOA0; TOA1", TOABins, TOARange[0], TOARange[1], TOABins, TOARange[0], TOARange[1]);
    hTOA1vsTOA0_C0->Sumw2();
    hTOA1vsTOA0_C1 = new TH2D("hTOA1vsTOA0_C1", "TOA1 vs TOA0 C1; TOA0; TOA1", TOABins, TOARange[0], TOARange[1], TOABins, TOARange[0], TOARange[1]);
    hTOA1vsTOA0_C1->Sumw2();
    hTOA1vsTOA0_C2 = new TH2D("hTOA1vsTOA0_C2", "TOA1 vs TOA0 C2; TOA0; TOA1", TOABins, TOARange[0], TOARange[1], TOABins, TOARange[0], TOARange[1]);
    hTOA1vsTOA0_C2->Sumw2();

    hTOA1vsTOA0_TWC_C0 = new TH2D("hTOA1vsTOA0_TWC_C0", "TOA1 vs TOA0 TWC C0; TOA0; TOA1", TOABins, TOARange[0], TOARange[1], TOABins, TOARange[0], TOARange[1]);
    hTOA1vsTOA0_TWC_C0->Sumw2();
    hTOA1vsTOA0_TWC_C1 = new TH2D("hTOA1vsTOA0_TWC_C1", "TOA1 vs TOA0 TWC C1; TOA0; TOA1", TOABins, TOARange[0], TOARange[1], TOABins, TOARange[0], TOARange[1]);
    hTOA1vsTOA0_TWC_C1->Sumw2();
    hTOA1vsTOA0_TWC_C2 = new TH2D("hTOA1vsTOA0_TWC_C2", "TOA1 vs TOA0 TWC C2; TOA0; TOA1", TOABins, TOARange[0], TOARange[1], TOABins, TOARange[0], TOARange[1]);
    hTOA1vsTOA0_TWC_C2->Sumw2();

    Int_t TOTCodeBins = 200;
    Float_t TOTCodeRange[2] = {0.0, 200.0};

    Int_t TOTBins = 120;
    Float_t TOTRange[2] = {0.0, 6.0};

    Int_t CALCodeBins = 30;
    Float_t CALCodeRange[2] = {160.0, 190.0};

    Int_t DTOACodeBins = 120;
    Float_t DTOACodeRange[2] = {-60.0, 60.0};

    Int_t DTOABins = 52;
    Float_t DTOARange[2] = {-1.3, 1.3};

    for (int i = 0; i < fNBoards; i++)
    {
        hTOACodevsTOTCode_C0[i] = new TH2D(Form("hTOACodevsTOTCode_C0_B%d", i), Form("TOACode%d vs TOTCode%d C0 For Board %d ; TOTCode%d; TOACode%d", i, i, i, i, i), TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
        hTOACodevsTOTCode_C0[i]->Sumw2();
        hTOACodevsTOTCode_C1[i] = new TH2D(Form("hTOACodevsTOTCode_C1_B%d", i), Form("TOACode%d vs TOTCode%d C1 For Board %d ; TOTCode%d; TOACode%d", i, i, i, i, i), TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
        hTOACodevsTOTCode_C1[i]->Sumw2();
        hTOACodevsTOTCode_C2[i] = new TH2D(Form("hTOACodevsTOTCode_C2_B%d", i), Form("TOACode%d vs TOTCode%d C2 For Board %d ; TOTCode%d; TOACode%d", i, i, i, i, i), TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
        hTOACodevsTOTCode_C2[i]->Sumw2();

        hTOACode_TWCvsTOTCode_C0[i] = new TH2D(Form("hTOACode_TWCvsTOTCode_C0_B%d", i), Form("TOACode%d TWC vs TOTCode%d C0 For Board %d ; TOTCode%d; TOACode%d", i, i, i, i, i), TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
        hTOACode_TWCvsTOTCode_C0[i]->Sumw2();
        hTOACode_TWCvsTOTCode_C1[i] = new TH2D(Form("hTOACode_TWCvsTOTCode_C1_B%d", i), Form("TOACode%d TWC vs TOTCode%d C1 For Board %d ; TOTCode%d; TOACode%d", i, i, i, i, i), TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
        hTOACode_TWCvsTOTCode_C1[i]->Sumw2();
        hTOACode_TWCvsTOTCode_C2[i] = new TH2D(Form("hTOACode_TWCvsTOTCode_C2_B%d", i), Form("TOACode%d TWC vs TOTCode%d C2 For Board %d ; TOTCode%d; TOACode%d", i, i, i, i, i), TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
        hTOACode_TWCvsTOTCode_C2[i]->Sumw2();

        hTOAvsTOT_C0[i] = new TH2D(Form("hTOAvsTOT_C0_B%d", i), Form("TOA%d vs TOT%d C0 For Board %d ; TOT%d; TOA%d", i, i, i, i, i), TOTBins, TOTRange[0], TOTRange[1], TOABins, TOARange[0], TOARange[1]);
        hTOAvsTOT_C0[i]->Sumw2();
        hTOAvsTOT_C1[i] = new TH2D(Form("hTOAvsTOT_C1_B%d", i), Form("TOA%d vs TOT%d C1 For Board %d ; TOT%d; TOA%d", i, i, i, i, i), TOTBins, TOTRange[0], TOTRange[1], TOABins, TOARange[0], TOARange[1]);
        hTOAvsTOT_C1[i]->Sumw2();
        hTOAvsTOT_C2[i] = new TH2D(Form("hTOAvsTOT_C2_B%d", i), Form("TOA%d vs TOT%d C2 For Board %d ; TOT%d; TOA%d", i, i, i, i, i), TOTBins, TOTRange[0], TOTRange[1], TOABins, TOARange[0], TOARange[1]);
        hTOAvsTOT_C2[i]->Sumw2();

        hTOA_TWCvsTOT_C0[i] = new TH2D(Form("hTOA_TWCvsTOT_C0_B%d", i), Form("TOA%d TWC vs TOT%d C0 For Board %d ; TOT%d; TOA%d", i, i, i, i, i), TOTBins, TOTRange[0], TOTRange[1], TOABins, TOARange[0], TOARange[1]);
        hTOA_TWCvsTOT_C0[i]->Sumw2();
        hTOA_TWCvsTOT_C1[i] = new TH2D(Form("hTOA_TWCvsTOT_C1_B%d", i), Form("TOA%d TWC vs TOT%d C1 For Board %d ; TOT%d; TOA%d", i, i, i, i, i), TOTBins, TOTRange[0], TOTRange[1], TOABins, TOARange[0], TOARange[1]);
        hTOA_TWCvsTOT_C1[i]->Sumw2();
        hTOA_TWCvsTOT_C2[i] = new TH2D(Form("hTOA_TWCvsTOT_C2_B%d", i), Form("TOA%d TWC vs TOT%d C2 For Board %d ; TOT%d; TOA%d", i, i, i, i, i), TOTBins, TOTRange[0], TOTRange[1], TOABins, TOARange[0], TOARange[1]);
        hTOA_TWCvsTOT_C2[i]->Sumw2();

        hDTOACodevsTOTCode_C0[i] = new TH2D(Form("hDTOACodevsTOTCode_C0_B%d", i), Form("#DeltaTOACode vs TOTCode%d C0 For Board %d ; TOTCode%d; #DeltaTOA", i, i, i), TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1], DTOACodeBins, DTOACodeRange[0], DTOACodeRange[1]);
        hDTOACodevsTOTCode_C0[i]->Sumw2();
        hDTOACodevsTOTCode_C1[i] = new TH2D(Form("hDTOACodevsTOTCode_C1_B%d", i), Form("#DeltaTOACode vs TOTCode%d C1 For Board %d ; TOTCode%d; #DeltaTOA", i, i, i), TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1], DTOACodeBins, DTOACodeRange[0], DTOACodeRange[1]);
        hDTOACodevsTOTCode_C1[i]->Sumw2();
        hDTOACodevsTOTCode_C2[i] = new TH2D(Form("hDTOACodevsTOTCode_C2_B%d", i), Form("#DeltaTOACode vs TOTCode%d C2 For Board %d ; TOTCode%d; #DeltaTOA", i, i, i), TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1], DTOACodeBins, DTOACodeRange[0], DTOACodeRange[1]);
        hDTOACodevsTOTCode_C2[i]->Sumw2();

        hDTOACode_TWCvsTOTCode_C0[i] = new TH2D(Form("hDTOACode_TWCvsTOTCode_C0_B%d", i), Form("#DeltaTOACode TWC vs TOTCode%d C0 For Board %d ; TOTCode%d; #DeltaTOA", i, i, i), TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1], DTOACodeBins, DTOACodeRange[0], DTOACodeRange[1]);
        hDTOACode_TWCvsTOTCode_C0[i]->Sumw2();
        hDTOACode_TWCvsTOTCode_C1[i] = new TH2D(Form("hDTOACode_TWCvsTOTCode_C1_B%d", i), Form("#DeltaTOACode TWC vs TOTCode%d C1 For Board %d ; TOTCode%d; #DeltaTOA", i, i, i), TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1], DTOACodeBins, DTOACodeRange[0], DTOACodeRange[1]);
        hDTOACode_TWCvsTOTCode_C1[i]->Sumw2();
        hDTOACode_TWCvsTOTCode_C2[i] = new TH2D(Form("hDTOACode_TWCvsTOTCode_C2_B%d", i), Form("#DeltaTOACode TWC vs TOTCode%d C2 For Board %d ; TOTCode%d; #DeltaTOA", i, i, i), TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1], DTOACodeBins, DTOACodeRange[0], DTOACodeRange[1]);
        hDTOACode_TWCvsTOTCode_C2[i]->Sumw2();

        hDTOACode_TWC0vsTOTCode_C0[i] = new TH2D(Form("hDTOACode_TWC0vsTOTCode_C0_B%d", i), Form("#DeltaTOACode TWC0 vs TOTCode%d C0 For Board %d ; TOTCode%d; #DeltaTOA", i, i, i), TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1], DTOACodeBins, DTOACodeRange[0], DTOACodeRange[1]);
        hDTOACode_TWC0vsTOTCode_C0[i]->Sumw2();
        hDTOACode_TWC0vsTOTCode_C1[i] = new TH2D(Form("hDTOACode_TWC0vsTOTCode_C1_B%d", i), Form("#DeltaTOACode TWC0 vs TOTCode%d C1 For Board %d ; TOTCode%d; #DeltaTOA", i, i, i), TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1], DTOACodeBins, DTOACodeRange[0], DTOACodeRange[1]);
        hDTOACode_TWC0vsTOTCode_C1[i]->Sumw2();
        hDTOACode_TWC0vsTOTCode_C2[i] = new TH2D(Form("hDTOACode_TWC0vsTOTCode_C2_B%d", i), Form("#DeltaTOACode TWC0 vs TOTCode%d C2 For Board %d ; TOTCode%d; #DeltaTOA", i, i, i), TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1], DTOACodeBins, DTOACodeRange[0], DTOACodeRange[1]);
        hDTOACode_TWC0vsTOTCode_C2[i]->Sumw2();

        hDTOACode_TWC1vsTOTCode_C0[i] = new TH2D(Form("hDTOACode_TWC1vsTOTCode_C0_B%d", i), Form("#DeltaTOACode TWC1 vs TOTCode%d C0 For Board %d ; TOTCode%d; #DeltaTOA", i, i, i), TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1], DTOACodeBins, DTOACodeRange[0], DTOACodeRange[1]);
        hDTOACode_TWC1vsTOTCode_C0[i]->Sumw2();
        hDTOACode_TWC1vsTOTCode_C1[i] = new TH2D(Form("hDTOACode_TWC1vsTOTCode_C1_B%d", i), Form("#DeltaTOACode TWC1 vs TOTCode%d C1 For Board %d ; TOTCode%d; #DeltaTOA", i, i, i), TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1], DTOACodeBins, DTOACodeRange[0], DTOACodeRange[1]);
        hDTOACode_TWC1vsTOTCode_C1[i]->Sumw2();
        hDTOACode_TWC1vsTOTCode_C2[i] = new TH2D(Form("hDTOACode_TWC1vsTOTCode_C2_B%d", i), Form("#DeltaTOACode TWC1 vs TOTCode%d C2 For Board %d ; TOTCode%d; #DeltaTOA", i, i, i), TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1], DTOACodeBins, DTOACodeRange[0], DTOACodeRange[1]);
        hDTOACode_TWC1vsTOTCode_C2[i]->Sumw2();

        hDTOAvsTOT_C0[i] = new TH2D(Form("hDTOAvsTOT_C0_B%d", i), Form("#DeltaTOA vs TOT%d C0 For Board %d ; TOT%d; #DeltaTOA", i, i, i), TOTBins, TOTRange[0], TOTRange[1], DTOABins, DTOARange[0], DTOARange[1]);
        hDTOAvsTOT_C0[i]->Sumw2();
        hDTOAvsTOT_C1[i] = new TH2D(Form("hDTOAvsTOT_C1_B%d", i), Form("#DeltaTOA vs TOT%d C1 For Board %d ; TOT%d; #DeltaTOA", i, i, i), TOTBins, TOTRange[0], TOTRange[1], DTOABins, DTOARange[0], DTOARange[1]);
        hDTOAvsTOT_C1[i]->Sumw2();
        hDTOAvsTOT_C2[i] = new TH2D(Form("hDTOAvsTOT_C2_B%d", i), Form("#DeltaTOA vs TOT%d C2 For Board %d ; TOT%d; #DeltaTOA", i, i, i), TOTBins, TOTRange[0], TOTRange[1], DTOABins, DTOARange[0], DTOARange[1]);
        hDTOAvsTOT_C2[i]->Sumw2();

        hDTOA_TWCvsTOT_C0[i] = new TH2D(Form("hDTOA_TWCvsTOT_C0_B%d", i), Form("#DeltaTOA TWC vs TOT%d C0 For Board %d ; TOT%d; #DeltaTOA", i, i, i), TOTBins, TOTRange[0], TOTRange[1], DTOABins, DTOARange[0], DTOARange[1]);
        hDTOA_TWCvsTOT_C0[i]->Sumw2();
        hDTOA_TWCvsTOT_C1[i] = new TH2D(Form("hDTOA_TWCvsTOT_C1_B%d", i), Form("#DeltaTOA TWC vs TOT%d C1 For Board %d ; TOT%d; #DeltaTOA", i, i, i), TOTBins, TOTRange[0], TOTRange[1], DTOABins, DTOARange[0], DTOARange[1]);
        hDTOA_TWCvsTOT_C1[i]->Sumw2();
        hDTOA_TWCvsTOT_C2[i] = new TH2D(Form("hDTOA_TWCvsTOT_C2_B%d", i), Form("#DeltaTOA TWC vs TOT%d C2 For Board %d ; TOT%d; #DeltaTOA", i, i, i), TOTBins, TOTRange[0], TOTRange[1], DTOABins, DTOARange[0], DTOARange[1]);
        hDTOA_TWCvsTOT_C2[i]->Sumw2();

        hDTOA_TWC0vsTOT_C0[i] = new TH2D(Form("hDTOA_TWC0vsTOT_C0_B%d", i), Form("#DeltaTOA TWC0 vs TOT%d C0 For Board %d ; TOT%d; #DeltaTOA", i, i, i), TOTBins, TOTRange[0], TOTRange[1], DTOABins, DTOARange[0], DTOARange[1]);
        hDTOA_TWC0vsTOT_C0[i]->Sumw2();
        hDTOA_TWC0vsTOT_C1[i] = new TH2D(Form("hDTOA_TWC0vsTOT_C1_B%d", i), Form("#DeltaTOA TWC0 vs TOT%d C1 For Board %d ; TOT%d; #DeltaTOA", i, i, i), TOTBins, TOTRange[0], TOTRange[1], DTOABins, DTOARange[0], DTOARange[1]);
        hDTOA_TWC0vsTOT_C1[i]->Sumw2();
        hDTOA_TWC0vsTOT_C2[i] = new TH2D(Form("hDTOA_TWC0vsTOT_C2_B%d", i), Form("#DeltaTOA TWC0 vs TOT%d C2 For Board %d ; TOT%d; #DeltaTOA", i, i, i), TOTBins, TOTRange[0], TOTRange[1], DTOABins, DTOARange[0], DTOARange[1]);
        hDTOA_TWC0vsTOT_C2[i]->Sumw2();

        hDTOA_TWC1vsTOT_C0[i] = new TH2D(Form("hDTOA_TWC1vsTOT_C0_B%d", i), Form("#DeltaTOA TWC1 vs TOT%d C0 For Board %d ; TOT%d; #DeltaTOA", i, i, i), TOTBins, TOTRange[0], TOTRange[1], DTOABins, DTOARange[0], DTOARange[1]);
        hDTOA_TWC1vsTOT_C0[i]->Sumw2();
        hDTOA_TWC1vsTOT_C1[i] = new TH2D(Form("hDTOA_TWC1vsTOT_C1_B%d", i), Form("#DeltaTOA TWC1 vs TOT%d C1 For Board %d ; TOT%d; #DeltaTOA", i, i, i), TOTBins, TOTRange[0], TOTRange[1], DTOABins, DTOARange[0], DTOARange[1]);
        hDTOA_TWC1vsTOT_C1[i]->Sumw2();
        hDTOA_TWC1vsTOT_C2[i] = new TH2D(Form("hDTOA_TWC1vsTOT_C2_B%d", i), Form("#DeltaTOA TWC1 vs TOT%d C2 For Board %d ; TOT%d; #DeltaTOA", i, i, i), TOTBins, TOTRange[0], TOTRange[1], DTOABins, DTOARange[0], DTOARange[1]);
        hDTOA_TWC1vsTOT_C2[i]->Sumw2();

        hTOACodevsCALCode_C0[i] = new TH2D(Form("hTOACodevsCALCode_C0_B%d", i), Form("TOACode%d vs CALCode%d C0 For Board %d; CALCode%d; TOACode%d", i, i, i, i, i), CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
        hTOACodevsCALCode_C0[i]->Sumw2();
        hTOACodevsCALCode_C1[i] = new TH2D(Form("hTOACodevsCALCode_C1_B%d", i), Form("TOACode%d vs CALCode%d C1 For Board %d; CALCode%d; TOACode%d", i, i, i, i, i), CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
        hTOACodevsCALCode_C1[i]->Sumw2();
        hTOACodevsCALCode_C2[i] = new TH2D(Form("hTOACodevsCALCode_C2_B%d", i), Form("TOACode%d vs CALCode%d C2 For Board %d; CALCode%d; TOACode%d", i, i, i, i, i), CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
        hTOACodevsCALCode_C2[i]->Sumw2();

        hTOACode_TWCvsCALCode_C0[i] = new TH2D(Form("hTOACode_TWCvsCALCode_C0_B%d", i), Form("TOACode%d TWC vs CALCode%d C0 For Board %d; CALCode%d; TOACode%d", i, i, i, i, i), CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
        hTOACode_TWCvsCALCode_C0[i]->Sumw2();
        hTOACode_TWCvsCALCode_C1[i] = new TH2D(Form("hTOACode_TWCvsCALCode_C1_B%d", i), Form("TOACode%d TWC vs CALCode%d C1 For Board %d; CALCode%d; TOACode%d", i, i, i, i, i), CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
        hTOACode_TWCvsCALCode_C1[i]->Sumw2();
        hTOACode_TWCvsCALCode_C2[i] = new TH2D(Form("hTOACode_TWCvsCALCode_C2_B%d", i), Form("TOACode%d TWC vs CALCode%d C2 For Board %d; CALCode%d; TOACode%d", i, i, i, i, i), CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
        hTOACode_TWCvsCALCode_C2[i]->Sumw2();

        hTOAvsCAL_C0[i] = new TH2D(Form("hTOAvsCAL_C0_B%d", i), Form("TOA%d vs CALCode%d C0 For Board %d; CALCode%d; TOA%d", i, i, i, i, i), CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOABins, TOARange[0], TOARange[1]);
        hTOAvsCAL_C0[i]->Sumw2();
        hTOAvsCAL_C1[i] = new TH2D(Form("hTOAvsCAL_C1_B%d", i), Form("TOA%d vs CALCode%d C1 For Board %d; CALCode%d; TOA%d", i, i, i, i, i), CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOABins, TOARange[0], TOARange[1]);
        hTOAvsCAL_C1[i]->Sumw2();
        hTOAvsCAL_C2[i] = new TH2D(Form("hTOAvsCAL_C2_B%d", i), Form("TOA%d vs CALCode%d C2 For Board %d; CALCode%d; TOA%d", i, i, i, i, i), CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOABins, TOARange[0], TOARange[1]);
        hTOAvsCAL_C2[i]->Sumw2();

        hTOA_TWCvsCAL_C0[i] = new TH2D(Form("hTOA_TWCvsCAL_C0_B%d", i), Form("TOA%d TWC vs CALCode%d C0 For Board %d; CALCode%d; TOA%d", i, i, i, i, i), CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOABins, TOARange[0], TOARange[1]);
        hTOA_TWCvsCAL_C0[i]->Sumw2();
        hTOA_TWCvsCAL_C1[i] = new TH2D(Form("hTOA_TWCvsCAL_C1_B%d", i), Form("TOA%d TWC vs CALCode%d C1 For Board %d; CALCode%d; TOA%d", i, i, i, i, i), CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOABins, TOARange[0], TOARange[1]);
        hTOA_TWCvsCAL_C1[i]->Sumw2();
        hTOA_TWCvsCAL_C2[i] = new TH2D(Form("hTOA_TWCvsCAL_C2_B%d", i), Form("TOA%d TWC vs CALCode%d C2 For Board %d; CALCode%d; TOA%d", i, i, i, i, i), CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOABins, TOARange[0], TOARange[1]);
        hTOA_TWCvsCAL_C2[i]->Sumw2();

        hTOTCodevsCALCode_C0[i] = new TH2D(Form("hTOTCodevsCALCode_C0_B%d", i), Form("TOTCode%d vs CALCode%d C0 For Board %d; CALCode%d; TOTCode%d", i, i, i, i, i), CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1]);
        hTOTCodevsCALCode_C0[i]->Sumw2();
        hTOTCodevsCALCode_C1[i] = new TH2D(Form("hTOTCodevsCALCode_C1_B%d", i), Form("TOTCode%d vs CALCode%d C1 For Board %d; CALCode%d; TOTCode%d", i, i, i, i, i), CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1]);
        hTOTCodevsCALCode_C1[i]->Sumw2();
        hTOTCodevsCALCode_C2[i] = new TH2D(Form("hTOTCodevsCALCode_C2_B%d", i), Form("TOTCode%d vs CALCode%d C2 For Board %d; CALCode%d; TOTCode%d", i, i, i, i, i), CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1]);
        hTOTCodevsCALCode_C2[i]->Sumw2();

        hTOTvsCAL_C0[i] = new TH2D(Form("hTOTvsCAL_C0_B%d", i), Form("TOT%d vs CALCode%d C0 For Board %d; CALCode%d; TOT%d", i, i, i, i, i), CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOTBins, TOTRange[0], TOTRange[1]);
        hTOTvsCAL_C0[i]->Sumw2();
        hTOTvsCAL_C1[i] = new TH2D(Form("hTOTvsCAL_C1_B%d", i), Form("TOT%d vs CALCode%d C1 For Board %d; CALCode%d; TOT%d", i, i, i, i, i), CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOTBins, TOTRange[0], TOTRange[1]);
        hTOTvsCAL_C1[i]->Sumw2();
        hTOTvsCAL_C2[i] = new TH2D(Form("hTOTvsCAL_C2_B%d", i), Form("TOT%d vs CALCode%d C2 For Board %d; CALCode%d; TOT%d", i, i, i, i, i), CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOTBins, TOTRange[0], TOTRange[1]);
        hTOTvsCAL_C2[i]->Sumw2();

        pDTOACodevsTOTCode[i] = new TProfile(Form("pDTOACodevsTOTCode_B%d", i), Form("Profile for DTOACode For B%d;TOTCode%d;DTOACode", i, i), TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1]);
        pDTOAvsTOT[i] = new TProfile(Form("pDTOAvsTOT_B%d", i), Form("Profile for DTOA For B%d;TOT%d;DTOA", i, i), TOTBins, TOTRange[0], TOTRange[1]);
    }
}

void HistoManagerETROC::projection()
{
    for (int i = 0; i < fNBoards; i++)
    {
        hTOACode_C0[i] = hTOACodevsTOTCode_C0[i]->ProjectionY(Form("hTOACode_C0_B%d", i));
        hTOACode_C0[i]->SetTitle(Form("TOACode C0 For Board %d;TOACode%d", i, i));
        hTOACode_C1[i] = hTOACodevsTOTCode_C1[i]->ProjectionY(Form("hTOACode_C1_B%d", i));
        hTOACode_C1[i]->SetTitle(Form("TOACode C1 For Board %d;TOACode%d", i, i));
        hTOACode_C2[i] = hTOACodevsTOTCode_C2[i]->ProjectionY(Form("hTOACode_C2_B%d", i));
        hTOACode_C2[i]->SetTitle(Form("TOACode C2 For Board %d;TOACode%d", i, i));

        hTOACode_TWC_C0[i] = hTOACode_TWCvsTOTCode_C0[i]->ProjectionY(Form("hTOACode_TWC_C0_B%d", i));
        hTOACode_TWC_C0[i]->SetTitle(Form("TOACode TWC C0 For Board %d;TOACode%d", i, i));
        hTOACode_TWC_C1[i] = hTOACode_TWCvsTOTCode_C1[i]->ProjectionY(Form("hTOACode_TWC_C1_B%d", i));
        hTOACode_TWC_C1[i]->SetTitle(Form("TOACode TWC C1 For Board %d;TOACode%d", i, i));
        hTOACode_TWC_C2[i] = hTOACode_TWCvsTOTCode_C2[i]->ProjectionY(Form("hTOACode_TWC_C2_B%d", i));
        hTOACode_TWC_C2[i]->SetTitle(Form("TOACode TWC C2 For Board %d;TOACode%d", i, i));

        hDTOACode_C0[i] = hDTOACodevsTOTCode_C0[i]->ProjectionY(Form("hDTOACode_C0_B%d", i));
        hDTOACode_C0[i]->SetTitle(Form("#DeltaTOACode C0 For Board %d;#DeltaTOACode%d", i, i));
        hDTOACode_C1[i] = hDTOACodevsTOTCode_C1[i]->ProjectionY(Form("hDTOACode_C1_B%d", i));
        hDTOACode_C1[i]->SetTitle(Form("#DeltaTOACode C1 For Board %d;#DeltaTOACode%d", i, i));
        hDTOACode_C2[i] = hDTOACodevsTOTCode_C2[i]->ProjectionY(Form("hDTOACode_C2_B%d", i));
        hDTOACode_C2[i]->SetTitle(Form("#DeltaTOACode C2 For Board %d;#DeltaTOACode%d", i, i));

        hDTOACode_TWC_C0[i] = hDTOACode_TWCvsTOTCode_C0[i]->ProjectionY(Form("hDTOACode_TWC_C0_B%d", i));
        hDTOACode_TWC_C0[i]->SetTitle(Form("#DeltaTOACode TWC C0 For Board %d;#DeltaTOACode%d", i, i));
        hDTOACode_TWC_C1[i] = hDTOACode_TWCvsTOTCode_C1[i]->ProjectionY(Form("hDTOACode_TWC_C1_B%d", i));
        hDTOACode_TWC_C1[i]->SetTitle(Form("#DeltaTOACode TWC C1 For Board %d;#DeltaTOACode%d", i, i));
        hDTOACode_TWC_C2[i] = hDTOACode_TWCvsTOTCode_C2[i]->ProjectionY(Form("hDTOACode_TWC_C2_B%d", i));
        hDTOACode_TWC_C2[i]->SetTitle(Form("#DeltaTOACode TWC C2 For Board %d;#DeltaTOACode%d", i, i));

        hDTOACode_TWC0_C0[i] = hDTOACode_TWC0vsTOTCode_C0[i]->ProjectionY(Form("hDTOACode_TWC0_C0_B%d", i));
        hDTOACode_TWC0_C0[i]->SetTitle(Form("#DeltaTOACode TWC0 C0 For Board %d;#DeltaTOACode%d", i, i));
        hDTOACode_TWC0_C1[i] = hDTOACode_TWC0vsTOTCode_C1[i]->ProjectionY(Form("hDTOACode_TWC0_C1_B%d", i));
        hDTOACode_TWC0_C1[i]->SetTitle(Form("#DeltaTOACode TWC0 C1 For Board %d;#DeltaTOACode%d", i, i));
        hDTOACode_TWC0_C2[i] = hDTOACode_TWC0vsTOTCode_C2[i]->ProjectionY(Form("hDTOACode_TWC0_C2_B%d", i));
        hDTOACode_TWC0_C2[i]->SetTitle(Form("#DeltaTOACode TWC0 C2 For Board %d;#DeltaTOACode%d", i, i));

        hDTOACode_TWC1_C0[i] = hDTOACode_TWC1vsTOTCode_C0[i]->ProjectionY(Form("hDTOACode_TWC1_C0_B%d", i));
        hDTOACode_TWC1_C0[i]->SetTitle(Form("#DeltaTOACode TWC1 C0 For Board %d;#DeltaTOACode%d", i, i));
        hDTOACode_TWC1_C1[i] = hDTOACode_TWC1vsTOTCode_C1[i]->ProjectionY(Form("hDTOACode_TWC1_C1_B%d", i));
        hDTOACode_TWC1_C1[i]->SetTitle(Form("#DeltaTOACode TWC1 C1 For Board %d;#DeltaTOACode%d", i, i));
        hDTOACode_TWC1_C2[i] = hDTOACode_TWC1vsTOTCode_C2[i]->ProjectionY(Form("hDTOACode_TWC1_C2_B%d", i));
        hDTOACode_TWC1_C2[i]->SetTitle(Form("#DeltaTOACode TWC1 C2 For Board %d;#DeltaTOACode%d", i, i));

        hTOA_C0[i] = hTOAvsTOT_C0[i]->ProjectionY(Form("hTOA_C0_B%d", i));
        hTOA_C0[i]->SetTitle(Form("TOA C0 For Board %d;TOA%d", i, i));
        hTOA_C1[i] = hTOAvsTOT_C1[i]->ProjectionY(Form("hTOA_C1_B%d", i));
        hTOA_C1[i]->SetTitle(Form("TOA C1 For Board %d;TOA%d", i, i));
        hTOA_C2[i] = hTOAvsTOT_C2[i]->ProjectionY(Form("hTOA_C2_B%d", i));
        hTOA_C2[i]->SetTitle(Form("TOA C2 For Board %d;TOA%d", i, i));

        hTOA_TWC_C0[i] = hTOA_TWCvsTOT_C0[i]->ProjectionY(Form("hTOA_TWC_C0_B%d", i));
        hTOA_TWC_C0[i]->SetTitle(Form("TOA TWC C0 For Board %d;TOA%d", i, i));
        hTOA_TWC_C1[i] = hTOA_TWCvsTOT_C1[i]->ProjectionY(Form("hTOA_TWC_C1_B%d", i));
        hTOA_TWC_C1[i]->SetTitle(Form("TOA TWC C1 For Board %d;TOA%d", i, i));
        hTOA_TWC_C2[i] = hTOA_TWCvsTOT_C2[i]->ProjectionY(Form("hTOA_TWC_C2_B%d", i));
        hTOA_TWC_C2[i]->SetTitle(Form("TOA TWC C2 For Board %d;TOA%d", i, i));

        hDTOA_C0[i] = hDTOAvsTOT_C0[i]->ProjectionY(Form("hDTOA_C0_B%d", i));
        hDTOA_C0[i]->SetTitle(Form("#DeltaTOA C0 For Board %d;#DeltaTOA%d", i, i));
        hDTOA_C1[i] = hDTOAvsTOT_C1[i]->ProjectionY(Form("hDTOA_C1_B%d", i));
        hDTOA_C1[i]->SetTitle(Form("#DeltaTOA C1 For Board %d;#DeltaTOA%d", i, i));
        hDTOA_C2[i] = hDTOAvsTOT_C2[i]->ProjectionY(Form("hDTOA_C2_B%d", i));
        hDTOA_C2[i]->SetTitle(Form("#DeltaTOA C2 For Board %d;#DeltaTOA%d", i, i));

        hDTOA_TWC_C0[i] = hDTOA_TWCvsTOT_C0[i]->ProjectionY(Form("hDTOA_TWC_C0_B%d", i));
        hDTOA_TWC_C0[i]->SetTitle(Form("#DeltaTOA TWC C0 For Board %d;#DeltaTOA%d", i, i));
        hDTOA_TWC_C1[i] = hDTOA_TWCvsTOT_C1[i]->ProjectionY(Form("hDTOA_TWC_C1_B%d", i));
        hDTOA_TWC_C1[i]->SetTitle(Form("#DeltaTOA TWC C1 For Board %d;#DeltaTOA%d", i, i));
        hDTOA_TWC_C2[i] = hDTOA_TWCvsTOT_C2[i]->ProjectionY(Form("hDTOA_TWC_C2_B%d", i));
        hDTOA_TWC_C2[i]->SetTitle(Form("#DeltaTOA TWC C2 For Board %d;#DeltaTOA%d", i, i));

        hDTOA_TWC0_C0[i] = hDTOA_TWC0vsTOT_C0[i]->ProjectionY(Form("hDTOA_TWC0_C0_B%d", i));
        hDTOA_TWC0_C0[i]->SetTitle(Form("#DeltaTOA TWC0 C0 For Board %d;#DeltaTOA%d", i, i));
        hDTOA_TWC0_C1[i] = hDTOA_TWC0vsTOT_C1[i]->ProjectionY(Form("hDTOA_TWC0_C1_B%d", i));
        hDTOA_TWC0_C1[i]->SetTitle(Form("#DeltaTOA TWC0 C1 For Board %d;#DeltaTOA%d", i, i));
        hDTOA_TWC0_C2[i] = hDTOA_TWC0vsTOT_C2[i]->ProjectionY(Form("hDTOA_TWC0_C2_B%d", i));
        hDTOA_TWC0_C2[i]->SetTitle(Form("#DeltaTOA TWC0 C2 For Board %d;#DeltaTOA%d", i, i));

        hDTOA_TWC1_C0[i] = hDTOA_TWC1vsTOT_C0[i]->ProjectionY(Form("hDTOA_TWC1_C0_B%d", i));
        hDTOA_TWC1_C0[i]->SetTitle(Form("#DeltaTOA TWC1 C0 For Board %d;#DeltaTOA%d", i, i));
        hDTOA_TWC1_C1[i] = hDTOA_TWC1vsTOT_C1[i]->ProjectionY(Form("hDTOA_TWC1_C1_B%d", i));
        hDTOA_TWC1_C1[i]->SetTitle(Form("#DeltaTOA TWC1 C1 For Board %d;#DeltaTOA%d", i, i));
        hDTOA_TWC1_C2[i] = hDTOA_TWC1vsTOT_C2[i]->ProjectionY(Form("hDTOA_TWC1_C2_B%d", i));
        hDTOA_TWC1_C2[i]->SetTitle(Form("#DeltaTOA TWC1 C2 For Board %d;#DeltaTOA%d", i, i));

        hTOTCode_C0[i] = hTOACodevsTOTCode_C0[i]->ProjectionX(Form("hTOTCode_C0_B%d", i));
        hTOTCode_C0[i]->SetTitle(Form("TOTCode C0 For Board %d;TOTCode%d", i, i));
        hTOTCode_C1[i] = hTOACodevsTOTCode_C1[i]->ProjectionX(Form("hTOTCode_C1_B%d", i));
        hTOTCode_C1[i]->SetTitle(Form("TOTCode C1 For Board %d;TOTCode%d", i, i));
        hTOTCode_C2[i] = hTOACodevsTOTCode_C2[i]->ProjectionX(Form("hTOTCode_C2_B%d", i));
        hTOTCode_C2[i]->SetTitle(Form("TOTCode C2 For Board %d;TOTCode%d", i, i));

        hTOT_C0[i] = hTOAvsTOT_C0[i]->ProjectionX(Form("hTOT_C0_B%d", i));
        hTOT_C0[i]->SetTitle(Form("TOT C0 For Board %d;TOT%d", i, i));
        hTOT_C1[i] = hTOAvsTOT_C1[i]->ProjectionX(Form("hTOT_C1_B%d", i));
        hTOT_C1[i]->SetTitle(Form("TOT C1 For Board %d;TOT%d", i, i));
        hTOT_C2[i] = hTOAvsTOT_C2[i]->ProjectionX(Form("hTOT_C2_B%d", i));
        hTOT_C2[i]->SetTitle(Form("TOT C2 For Board %d;TOT%d", i, i));

        hCAL_C0[i] = hTOAvsCAL_C0[i]->ProjectionX(Form("hCAL_C0_B%d", i));
        hCAL_C0[i]->SetTitle(Form("CALCode C0 For Board %d;CALCode%d", i, i));
        hCAL_C1[i] = hTOAvsCAL_C1[i]->ProjectionX(Form("hCAL_C1_B%d", i));
        hCAL_C1[i]->SetTitle(Form("CALCode C1 For Board %d;CALCode%d", i, i));
        hCAL_C2[i] = hTOAvsCAL_C2[i]->ProjectionX(Form("hCAL_C2_B%d", i));
        hCAL_C2[i]->SetTitle(Form("CALCode C2 For Board %d;CALCode%d", i, i));
    }
}

void HistoManagerETROC::writeOutput()
{
    hTOA_Code1vsTOA_Code0_C0->Write();
    hTOA_Code1vsTOA_Code0_C1->Write();
    hTOA_Code1vsTOA_Code0_C2->Write();

    hTOA_Code1vsTOA_Code0_TWC_C0->Write();
    hTOA_Code1vsTOA_Code0_TWC_C1->Write();
    hTOA_Code1vsTOA_Code0_TWC_C2->Write();

    hTOA1vsTOA0_C0->Write();
    hTOA1vsTOA0_C1->Write();
    hTOA1vsTOA0_C2->Write();

    hTOA1vsTOA0_TWC_C0->Write();
    hTOA1vsTOA0_TWC_C1->Write();
    hTOA1vsTOA0_TWC_C2->Write();

    for (int i = 0; i < fNBoards; i++)
    {
        hTOACodevsTOTCode_C0[i]->Write();
        hTOACodevsTOTCode_C1[i]->Write();
        hTOACodevsTOTCode_C2[i]->Write();

        hTOACode_TWCvsTOTCode_C0[i]->Write();
        hTOACode_TWCvsTOTCode_C1[i]->Write();
        hTOACode_TWCvsTOTCode_C2[i]->Write();

        hTOAvsTOT_C0[i]->Write();
        hTOAvsTOT_C1[i]->Write();
        hTOAvsTOT_C2[i]->Write();

        hTOA_TWCvsTOT_C0[i]->Write();
        hTOA_TWCvsTOT_C1[i]->Write();
        hTOA_TWCvsTOT_C2[i]->Write();

        hDTOACodevsTOTCode_C0[i]->Write();
        hDTOACodevsTOTCode_C1[i]->Write();
        hDTOACodevsTOTCode_C2[i]->Write();

        hDTOACode_TWCvsTOTCode_C0[i]->Write();
        hDTOACode_TWCvsTOTCode_C1[i]->Write();
        hDTOACode_TWCvsTOTCode_C2[i]->Write();

        hDTOACode_TWC0vsTOTCode_C0[i]->Write();
        hDTOACode_TWC0vsTOTCode_C1[i]->Write();
        hDTOACode_TWC0vsTOTCode_C2[i]->Write();

        hDTOACode_TWC1vsTOTCode_C0[i]->Write();
        hDTOACode_TWC1vsTOTCode_C1[i]->Write();
        hDTOACode_TWC1vsTOTCode_C2[i]->Write();

        hDTOAvsTOT_C0[i]->Write();
        hDTOAvsTOT_C1[i]->Write();
        hDTOAvsTOT_C2[i]->Write();

        hDTOA_TWCvsTOT_C0[i]->Write();
        hDTOA_TWCvsTOT_C1[i]->Write();
        hDTOA_TWCvsTOT_C2[i]->Write();

        hDTOA_TWC0vsTOT_C0[i]->Write();
        hDTOA_TWC0vsTOT_C1[i]->Write();
        hDTOA_TWC0vsTOT_C2[i]->Write();

        hDTOA_TWC1vsTOT_C0[i]->Write();
        hDTOA_TWC1vsTOT_C1[i]->Write();
        hDTOA_TWC1vsTOT_C2[i]->Write();

        hTOACodevsCALCode_C0[i]->Write();
        hTOACodevsCALCode_C1[i]->Write();
        hTOACodevsCALCode_C2[i]->Write();

        hTOACode_TWCvsCALCode_C0[i]->Write();
        hTOACode_TWCvsCALCode_C1[i]->Write();
        hTOACode_TWCvsCALCode_C2[i]->Write();

        hTOAvsCAL_C0[i]->Write();
        hTOAvsCAL_C1[i]->Write();
        hTOAvsCAL_C2[i]->Write();

        hTOA_TWCvsCAL_C0[i]->Write();
        hTOA_TWCvsCAL_C1[i]->Write();
        hTOA_TWCvsCAL_C2[i]->Write();

        hTOTCodevsCALCode_C0[i]->Write();
        hTOTCodevsCALCode_C1[i]->Write();
        hTOTCodevsCALCode_C2[i]->Write();

        hTOTvsCAL_C0[i]->Write();
        hTOTvsCAL_C1[i]->Write();
        hTOTvsCAL_C2[i]->Write();

        hTOACode_C0[i]->Write();
        hTOACode_C1[i]->Write();
        hTOACode_C2[i]->Write();

        hTOACode_TWC_C0[i]->Write();
        hTOACode_TWC_C1[i]->Write();
        hTOACode_TWC_C2[i]->Write();

        hDTOACode_C0[i]->Write();
        hDTOACode_C1[i]->Write();
        hDTOACode_C2[i]->Write();

        (TBrowser *)0x57ef2eeb8f70

            hDTOACode_TWC_C0[i]
                ->Write();
        hDTOACode_TWC_C1[i]->Write();
        hDTOACode_TWC_C2[i]->Write();

        hDTOACode_TWC0_C0[i]->Write();
        hDTOACode_TWC0_C1[i]->Write();
        hDTOACode_TWC0_C2[i]->Write();

        hDTOACode_TWC1_C0[i]->Write();
        hDTOACode_TWC1_C1[i]->Write();
        hDTOACode_TWC1_C2[i]->Write();

        hTOA_C0[i]->Write();
        hTOA_C1[i]->Write();
        hTOA_C2[i]->Write();

        hTOA_TWC_C0[i]->Write();
        hTOA_TWC_C1[i]->Write();
        hTOA_TWC_C2[i]->Write();

        hDTOA_C0[i]->Write();
        hDTOA_C1[i]->Write();
        hDTOA_C2[i]->Write();

        hDTOA_TWC_C0[i]->Write();
        hDTOA_TWC_C1[i]->Write();
        hDTOA_TWC_C2[i]->Write();

        hDTOA_TWC0_C0[i]->Write();
        hDTOA_TWC0_C1[i]->Write();
        hDTOA_TWC0_C2[i]->Write();

        hDTOA_TWC1_C0[i]->Write();
        hDTOA_TWC1_C1[i]->Write();
        hDTOA_TWC1_C2[i]->Write();

        hTOTCode_C0[i]->Write();
        hTOTCode_C1[i]->Write();
        hTOTCode_C2[i]->Write();

        hTOT_C0[i]->Write();
        hTOT_C1[i]->Write();
        hTOT_C2[i]->Write();

        hCAL_C0[i]->Write();
        hCAL_C1[i]->Write();
        hCAL_C2[i]->Write();

        pDTOACodevsTOTCode[i]->Write();
        pDTOAvsTOT[i]->Write();
    }
}