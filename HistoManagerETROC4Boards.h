/**
 * @file HistoManagerETROC4Boards.h
 * @author Abhishek Hingrajiya (abhi.h123@gmail.com)
 * @brief Histogram Manager for 4 Boards ETROC Data Analysis
 * @version 0.1
 * @date 2024-09-25
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef HistoManagerETROC4Boards_h
#define HistoManagerETROC4Boards_h

#include "BaseHistoManager.h"
#include "TObject.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TProfile.h"
#include "TString.h"
#include "TMath.h"
#include <iostream>
#include "TFile.h"
#include "THnSparse.h"

class HistoManagerETROC4Boards : public BaseHistoManager
{
public:
    HistoManagerETROC4Boards();
    virtual ~HistoManagerETROC4Boards();

    void init();
    void projection();
    void writeOutput();

    void setNumberOfBoard(const Int_t &nBoards) { fNBoards = nBoards; }

    void setTOABins(const Int_t &nBins) { TOABins = nBins; }
    void setTOARange(const Double_t &min, const Double_t &max)
    {
        TOARange[0] = min;
        TOARange[1] = max;
    }

    void setTOTBins(const Int_t &nBins) { TOTBins = nBins; }
    void setTOTRange(const Double_t &min, const Double_t &max)
    {
        TOTRange[0] = min;
        TOTRange[1] = max;
    }

    void setCALCodeBins(const Int_t &nBins) { CALCodeBins = nBins; }
    void setCALCodeRange(const Double_t &min, const Double_t &max)
    {
        CALCodeRange[0] = min;
        CALCodeRange[1] = max;
    }

    void setDTOACodeBins(const Int_t &nBins) { DTOACodeBins = nBins; }
    void setDTOACodeRange(const Double_t &min, const Double_t &max)
    {
        DTOACodeRange[0] = min;
        DTOACodeRange[1] = max;
    }

    void setTOACodeBins(const Int_t &nBins) { TOACodeBins = nBins; }
    void setTOACodeRange(const Double_t &min, const Double_t &max)
    {
        TOACodeRange[0] = min;
        TOACodeRange[1] = max;
    }

    void setTOTCodeBins(const Int_t &nBins) { TOTCodeBins = nBins; }
    void setTOTCodeRange(const Double_t &min, const Double_t &max)
    {
        TOTCodeRange[0] = min;
        TOTCodeRange[1] = max;
    }

    void setDTOABins(const Int_t &nBins) { DTOABins = nBins; }
    void setDTOARange(const Double_t &min, const Double_t &max)
    {
        DTOARange[0] = min;
        DTOARange[1] = max;
    }

    Int_t NumberOfBoards() { return fNBoards; }

    TH2D *hTOACode0vsTOTCode0_C0;
    TH2D *hTOACode0vsTOTCode0_C1;
    TH2D *hTOACode0vsTOTCode0_C2;

    TH2D *hTOACode1vsTOTCode1_C0;
    TH2D *hTOACode1vsTOTCode1_C1;
    TH2D *hTOACode1vsTOTCode1_C2;

    TH2D *hTOACode2vsTOTCode2_C0;
    TH2D *hTOACode2vsTOTCode2_C1;
    TH2D *hTOACode2vsTOTCode2_C2;

    TH2D *hTOACode3vsTOTCode3_C0;
    TH2D *hTOACode3vsTOTCode3_C1;
    TH2D *hTOACode3vsTOTCode3_C2;

    TH1D *hTOACode0_C0;
    TH1D *hTOACode0_C1;
    TH1D *hTOACode0_C2;

    TH1D *hTOACode1_C0;
    TH1D *hTOACode1_C1;
    TH1D *hTOACode1_C2;

    TH1D *hTOACode2_C0;
    TH1D *hTOACode2_C1;
    TH1D *hTOACode2_C2;

    TH1D *hTOACode3_C0;
    TH1D *hTOACode3_C1;
    TH1D *hTOACode3_C2;

    TH1D *hTOTCode0_C0;
    TH1D *hTOTCode0_C1;
    TH1D *hTOTCode0_C2;

    TH1D *hTOTCode1_C0;
    TH1D *hTOTCode1_C1;
    TH1D *hTOTCode1_C2;

    TH1D *hTOTCode2_C0;
    TH1D *hTOTCode2_C1;
    TH1D *hTOTCode2_C2;

    TH1D *hTOTCode3_C0;
    TH1D *hTOTCode3_C1;
    TH1D *hTOTCode3_C2;

    TH2D *hTOACode0vsCALCode0_C0;
    TH2D *hTOACode0vsCALCode0_C1;
    TH2D *hTOACode0vsCALCode0_C2;

    TH2D *hTOACode1vsCALCode1_C0;
    TH2D *hTOACode1vsCALCode1_C1;
    TH2D *hTOACode1vsCALCode1_C2;

    TH2D *hTOACode2vsCALCode2_C0;
    TH2D *hTOACode2vsCALCode2_C1;
    TH2D *hTOACode2vsCALCode2_C2;

    TH2D *hTOACode3vsCALCode3_C0;
    TH2D *hTOACode3vsCALCode3_C1;
    TH2D *hTOACode3vsCALCode3_C2;

    TH1D *hCALCode0_C0;
    TH1D *hCALCode0_C1;
    TH1D *hCALCode0_C2;

    TH1D *hCALCode1_C0;
    TH1D *hCALCode1_C1;
    TH1D *hCALCode1_C2;

    TH1D *hCALCode2_C0;
    TH1D *hCALCode2_C1;
    TH1D *hCALCode2_C2;

    TH1D *hCALCode3_C0;
    TH1D *hCALCode3_C1;
    TH1D *hCALCode3_C2;

    TH2D *hTOTCode0vsCALCode0_C0;
    TH2D *hTOTCode0vsCALCode0_C1;
    TH2D *hTOTCode0vsCALCode0_C2;

    TH2D *hTOTCode1vsCALCode1_C0;
    TH2D *hTOTCode1vsCALCode1_C1;
    TH2D *hTOTCode1vsCALCode1_C2;

    TH2D *hTOTCode2vsCALCode2_C0;
    TH2D *hTOTCode2vsCALCode2_C1;
    TH2D *hTOTCode2vsCALCode2_C2;

    TH2D *hTOTCode3vsCALCode3_C2;
    TH2D *hTOTCode3vsCALCode3_C0;
    TH2D *hTOTCode3vsCALCode3_C1;

    TH2D *hTOA0vsTOT0_C0;
    TH2D *hTOA0vsTOT0_C1;
    TH2D *hTOA0vsTOT0_C2;

    TH2D *hTOA1vsTOT1_C0;
    TH2D *hTOA1vsTOT1_C1;
    TH2D *hTOA1vsTOT1_C2;

    TH2D *hTOA2vsTOT2_C0;
    TH2D *hTOA2vsTOT2_C1;
    TH2D *hTOA2vsTOT2_C2;

    TH2D *hTOA3vsTOT3_C0;
    TH2D *hTOA3vsTOT3_C1;
    TH2D *hTOA3vsTOT3_C2;

    TH1D *hTOA0_C0;
    TH1D *hTOA0_C1;
    TH1D *hTOA0_C2;

    TH1D *hTOA1_C0;
    TH1D *hTOA1_C1;
    TH1D *hTOA1_C2;

    TH1D *hTOA2_C0;
    TH1D *hTOA2_C1;
    TH1D *hTOA2_C2;

    TH1D *hTOA3_C0;
    TH1D *hTOA3_C1;
    TH1D *hTOA3_C2;

    TH1D *hTOT0_C0;
    TH1D *hTOT0_C1;
    TH1D *hTOT0_C2;

    TH1D *hTOT1_C0;
    TH1D *hTOT1_C1;
    TH1D *hTOT1_C2;

    TH1D *hTOT2_C0;
    TH1D *hTOT2_C1;
    TH1D *hTOT2_C2;

    TH1D *hTOT3_C0;
    TH1D *hTOT3_C1;
    TH1D *hTOT3_C2;

    TH2D *hTOA0vsCALCode0_C0;
    TH2D *hTOA0vsCALCode0_C1;
    TH2D *hTOA0vsCALCode0_C2;

    TH2D *hTOA1vsCALCode1_C0;
    TH2D *hTOA1vsCALCode1_C1;
    TH2D *hTOA1vsCALCode1_C2;

    TH2D *hTOA2vsCALCode2_C0;
    TH2D *hTOA2vsCALCode2_C1;
    TH2D *hTOA2vsCALCode2_C2;

    TH2D *hTOA3vsCALCode3_C0;
    TH2D *hTOA3vsCALCode3_C1;
    TH2D *hTOA3vsCALCode3_C2;

    TH2D *hTOT0vsCALCode0_C0;
    TH2D *hTOT0vsCALCode0_C1;
    TH2D *hTOT0vsCALCode0_C2;

    TH2D *hTOT1vsCALCode1_C0;
    TH2D *hTOT1vsCALCode1_C1;
    TH2D *hTOT1vsCALCode1_C2;

    TH2D *hTOT2vsCALCode2_C0;
    TH2D *hTOT2vsCALCode2_C1;
    TH2D *hTOT2vsCALCode2_C2;

    TH2D *hTOT3vsCALCode3_C0;
    TH2D *hTOT3vsCALCode3_C1;
    TH2D *hTOT3vsCALCode3_C2;

    TH2D *hTOACode0vsTOACode1_C0;
    TH2D *hTOACode0vsTOACode2_C0;
    TH2D *hTOACode0vsTOACode3_C0;
    TH2D *hTOACode1vsTOACode2_C0;
    TH2D *hTOACode1vsTOACode3_C0;
    TH2D *hTOACode2vsTOACode3_C0;

    TH2D *hTOACode0vsTOACode1_C1;
    TH2D *hTOACode0vsTOACode2_C1;
    TH2D *hTOACode0vsTOACode3_C1;
    TH2D *hTOACode1vsTOACode2_C1;
    TH2D *hTOACode1vsTOACode3_C1;
    TH2D *hTOACode2vsTOACode3_C1;

    TH2D *hTOACode0vsTOACode1_C2;
    TH2D *hTOACode0vsTOACode2_C2;
    TH2D *hTOACode0vsTOACode3_C2;
    TH2D *hTOACode1vsTOACode2_C2;
    TH2D *hTOACode1vsTOACode3_C2;
    TH2D *hTOACode2vsTOACode3_C2;

    TH2D *hDTOA01CodevsTOTCode[2];
    TH2D *hDTOA02CodevsTOTCode[2];
    TH2D *hDTOA03CodevsTOTCode[2];
    TH2D *hDTOA12CodevsTOTCode[2];
    TH2D *hDTOA13CodevsTOTCode[2];
    TH2D *hDTOA23CodevsTOTCode[2];

    TH1D *hDTOA01Code;
    TH1D *hDTOA02Code;
    TH1D *hDTOA03Code;
    TH1D *hDTOA12Code;
    TH1D *hDTOA13Code;
    TH1D *hDTOA23Code;

    TH2D *hDTOA01vsTOT[2];
    TH2D *hDTOA02vsTOT[2];
    TH2D *hDTOA03vsTOT[2];
    TH2D *hDTOA12vsTOT[2];
    TH2D *hDTOA13vsTOT[2];
    TH2D *hDTOA23vsTOT[2];

    TH1D *hDTOA01;
    TH1D *hDTOA02;
    TH1D *hDTOA03;
    TH1D *hDTOA12;
    TH1D *hDTOA13;
    TH1D *hDTOA23;

    TH2D *hTOA0vsTOA1_C0;
    TH2D *hTOA0vsTOA2_C0;
    TH2D *hTOA0vsTOA3_C0;
    TH2D *hTOA1vsTOA2_C0;
    TH2D *hTOA1vsTOA3_C0;
    TH2D *hTOA2vsTOA3_C0;

    TH2D *hTOA0vsTOA1_C1;
    TH2D *hTOA0vsTOA2_C1;
    TH2D *hTOA0vsTOA3_C1;
    TH2D *hTOA1vsTOA2_C1;
    TH2D *hTOA1vsTOA3_C1;
    TH2D *hTOA2vsTOA3_C1;

    TH2D *hTOA0vsTOA1_C2;
    TH2D *hTOA0vsTOA2_C2;
    TH2D *hTOA0vsTOA3_C2;
    TH2D *hTOA1vsTOA2_C2;
    TH2D *hTOA1vsTOA3_C2;
    TH2D *hTOA2vsTOA3_C2;

    TProfile *pDTOA01CodevsTOTCode[2];
    TProfile *pDTOA02CodevsTOTCode[2];
    TProfile *pDTOA03CodevsTOTCode[2];
    TProfile *pDTOA12CodevsTOTCode[2];
    TProfile *pDTOA13CodevsTOTCode[2];
    TProfile *pDTOA23CodevsTOTCode[2];

    TProfile *pDTOA01vsTOT[2];
    TProfile *pDTOA02vsTOT[2];
    TProfile *pDTOA03vsTOT[2];
    TProfile *pDTOA12vsTOT[2];
    TProfile *pDTOA13vsTOT[2];
    TProfile *pDTOA23vsTOT[2];

private:
    Int_t fNBoards;

    Int_t TOTCodeBins;
    Float_t TOTCodeRange[2];

    Int_t TOTBins;
    Float_t TOTRange[2];

    Int_t CALCodeBins;
    Float_t CALCodeRange[2];

    Int_t DTOACodeBins;
    Float_t DTOACodeRange[2];

    Int_t DTOABins;
    Float_t DTOARange[2];

    Int_t TOACodeBins;
    Float_t TOACodeRange[2];

    Int_t TOABins;
    Float_t TOARange[2];

    ClassDef(HistoManagerETROC4Boards, 0);
};

#endif