/**
 * @file HistoManagerETROC4Boards.cc
 * @author Abhishek Hingrajiya (abhi.h123@gmail.com)
 * @brief Histogram Manager for 4 Boards ETROC Data Analysis
 * @version 0.1
 * @date 2024-09-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "HistoManagerETROC4Boards.h"
// ROOT Objects
#include "TObject.h"
#include "TIterator.h"
#include "TString.h"
#include "TClass.h"
#include "TKey.h"
#include "TROOT.h"
#include "TSystem.h"

ClassImp(HistoManagerETROC4Boards)

    HistoManagerETROC4Boards::HistoManagerETROC4Boards() : fNBoards{4}, hTOACode0vsTOTCode0_C0{nullptr}, hTOACode0vsTOTCode0_C1{nullptr}, hTOACode0vsTOTCode0_C2{nullptr}, TOTBins{0}, TOTRange{0},
                                                           TOABins{0}, TOARange{0}, TOTCodeBins{0}, TOTCodeRange{0}, CALCodeBins{0}, CALCodeRange{0}, DTOACodeBins{0}, DTOACodeRange{0},
                                                           TOACodeBins{0}, TOACodeRange{0}, DTOABins{0}, DTOARange{0},
                                                           hTOACode1vsTOTCode1_C0{nullptr}, hTOACode1vsTOTCode1_C1{nullptr}, hTOACode1vsTOTCode1_C2{nullptr}, hTOACode2vsTOTCode2_C0{nullptr}, hTOACode2vsTOTCode2_C1{nullptr}, hTOACode2vsTOTCode2_C2{nullptr},
                                                           hTOACode3vsTOTCode3_C0{nullptr}, hTOACode3vsTOTCode3_C1{nullptr}, hTOACode3vsTOTCode3_C2{nullptr}, hTOACode0_C0{nullptr}, hTOACode0_C1{nullptr}, hTOACode0_C2{nullptr},
                                                           hTOACode1_C0{nullptr}, hTOACode1_C1{nullptr}, hTOACode1_C2{nullptr}, hTOACode2_C0{nullptr}, hTOACode2_C1{nullptr}, hTOACode2_C2{nullptr}, hTOACode3_C0{nullptr}, hTOACode3_C1{nullptr}, hTOACode3_C2{nullptr},
                                                           hTOTCode0_C0{nullptr}, hTOTCode0_C1{nullptr}, hTOTCode0_C2{nullptr}, hTOTCode1_C0{nullptr}, hTOTCode1_C1{nullptr}, hTOTCode1_C2{nullptr}, hTOTCode2_C0{nullptr}, hTOTCode2_C1{nullptr}, hTOTCode2_C2{nullptr},
                                                           hTOTCode3_C0{nullptr}, hTOTCode3_C1{nullptr}, hTOTCode3_C2{nullptr}, hTOACode0vsCALCode0_C0{nullptr}, hTOACode0vsCALCode0_C1{nullptr}, hTOACode0vsCALCode0_C2{nullptr},
                                                           hTOACode1vsCALCode1_C0{nullptr}, hTOACode1vsCALCode1_C1{nullptr}, hTOACode1vsCALCode1_C2{nullptr}, hTOACode2vsCALCode2_C0{nullptr}, hTOACode2vsCALCode2_C1{nullptr}, hTOACode2vsCALCode2_C2{nullptr},
                                                           hTOACode3vsCALCode3_C0{nullptr}, hTOACode3vsCALCode3_C1{nullptr}, hTOACode3vsCALCode3_C2{nullptr}, hTOTCode0vsCALCode0_C0{nullptr}, hTOTCode0vsCALCode0_C1{nullptr}, hTOTCode0vsCALCode0_C2{nullptr},
                                                           hTOTCode1vsCALCode1_C0{nullptr}, hTOTCode1vsCALCode1_C1{nullptr}, hTOTCode1vsCALCode1_C2{nullptr}, hTOTCode2vsCALCode2_C0{nullptr}, hTOTCode2vsCALCode2_C1{nullptr}, hTOTCode2vsCALCode2_C2{nullptr},
                                                           hTOTCode3vsCALCode3_C0{nullptr}, hTOTCode3vsCALCode3_C1{nullptr}, hTOTCode3vsCALCode3_C2{nullptr}, hTOA0vsTOT0_C0{nullptr}, hTOA0vsTOT0_C1{nullptr}, hTOA0vsTOT0_C2{nullptr},
                                                           hTOA1vsTOT1_C0{nullptr}, hTOA1vsTOT1_C1{nullptr}, hTOA1vsTOT1_C2{nullptr}, hTOA2vsTOT2_C0{nullptr}, hTOA2vsTOT2_C1{nullptr}, hTOA2vsTOT2_C2{nullptr},
                                                           hTOA3vsTOT3_C0{nullptr}, hTOA3vsTOT3_C1{nullptr}, hTOA3vsTOT3_C2{nullptr}, hTOA0_C0{nullptr}, hTOA0_C1{nullptr}, hTOA0_C2{nullptr},
                                                           hTOA1_C0{nullptr}, hTOA1_C1{nullptr}, hTOA1_C2{nullptr}, hTOA2_C0{nullptr}, hTOA2_C1{nullptr}, hTOA2_C2{nullptr},
                                                           hTOA3_C0{nullptr}, hTOA3_C1{nullptr}, hTOA3_C2{nullptr}, hTOT0_C0{nullptr}, hTOT0_C1{nullptr}, hTOT0_C2{nullptr},
                                                           hTOT1_C0{nullptr}, hTOT1_C1{nullptr}, hTOT1_C2{nullptr}, hTOT2_C0{nullptr}, hTOT2_C1{nullptr}, hTOT2_C2{nullptr},
                                                           hTOT3_C0{nullptr}, hTOT3_C1{nullptr}, hTOT3_C2{nullptr}, hCALCode0_C0{nullptr}, hCALCode0_C1{nullptr}, hCALCode0_C2{nullptr},
                                                           hCALCode1_C0{nullptr}, hCALCode1_C1{nullptr}, hCALCode1_C2{nullptr}, hCALCode2_C0{nullptr}, hCALCode2_C1{nullptr}, hCALCode2_C2{nullptr},
                                                           hCALCode3_C0{nullptr}, hCALCode3_C1{nullptr}, hCALCode3_C2{nullptr}, hTOA0vsCALCode0_C0{nullptr}, hTOA0vsCALCode0_C1{nullptr}, hTOA0vsCALCode0_C2{nullptr},
                                                           hTOA1vsCALCode1_C0{nullptr}, hTOA1vsCALCode1_C1{nullptr}, hTOA1vsCALCode1_C2{nullptr}, hTOA2vsCALCode2_C0{nullptr}, hTOA2vsCALCode2_C1{nullptr}, hTOA2vsCALCode2_C2{nullptr},
                                                           hTOA3vsCALCode3_C0{nullptr}, hTOA3vsCALCode3_C1{nullptr}, hTOA3vsCALCode3_C2{nullptr}, pDTOA01CodevsTOTCode{nullptr}, pDTOA02CodevsTOTCode{nullptr}, pDTOA03CodevsTOTCode{nullptr},
                                                           pDTOA12CodevsTOTCode{nullptr}, pDTOA13CodevsTOTCode{nullptr}, pDTOA23CodevsTOTCode{nullptr}, pDTOA01vsTOT{nullptr}, pDTOA02vsTOT{nullptr}, pDTOA03vsTOT{nullptr},
                                                           pDTOA12vsTOT{nullptr}, pDTOA13vsTOT{nullptr}, pDTOA23vsTOT{nullptr}, hTOACode0vsTOACode1_C0{nullptr}, hTOACode0vsTOACode2_C0{nullptr}, hTOACode0vsTOACode3_C0{nullptr},
                                                           hTOACode1vsTOACode2_C0{nullptr}, hTOACode1vsTOACode3_C0{nullptr}, hTOACode2vsTOACode3_C0{nullptr}, hTOACode0vsTOACode1_C1{nullptr}, hTOACode0vsTOACode2_C1{nullptr},
                                                           hTOACode0vsTOACode3_C1{nullptr}, hTOACode1vsTOACode2_C1{nullptr}, hTOACode1vsTOACode3_C1{nullptr}, hTOACode2vsTOACode3_C1{nullptr}, hTOACode0vsTOACode1_C2{nullptr},
                                                           hTOACode0vsTOACode2_C2{nullptr}, hTOACode0vsTOACode3_C2{nullptr}, hTOACode1vsTOACode2_C2{nullptr}, hTOACode1vsTOACode3_C2{nullptr}, hTOACode2vsTOACode3_C2{nullptr},
                                                           hTOA0vsTOA1_C0{nullptr}, hTOA0vsTOA2_C0{nullptr}, hTOA0vsTOA3_C0{nullptr}, hTOA1vsTOA2_C0{nullptr}, hTOA1vsTOA3_C0{nullptr}, hTOA2vsTOA3_C0{nullptr},
                                                           hTOA0vsTOA1_C1{nullptr}, hTOA0vsTOA2_C1{nullptr}, hTOA0vsTOA3_C1{nullptr}, hTOA1vsTOA2_C1{nullptr}, hTOA1vsTOA3_C1{nullptr}, hTOA2vsTOA3_C1{nullptr},
                                                           hTOA0vsTOA1_C2{nullptr}, hTOA0vsTOA2_C2{nullptr}, hTOA0vsTOA3_C2{nullptr}, hTOA1vsTOA2_C2{nullptr}, hTOA1vsTOA3_C2{nullptr}, hTOA2vsTOA3_C2{nullptr},
                                                           hDTOA01CodevsTOTCode{nullptr}, hDTOA02CodevsTOTCode{nullptr}, hDTOA03CodevsTOTCode{nullptr}, hDTOA12CodevsTOTCode{nullptr}, hDTOA13CodevsTOTCode{nullptr}, hDTOA23CodevsTOTCode{nullptr},
                                                           hDTOA01vsTOT{nullptr}, hDTOA02vsTOT{nullptr}, hDTOA03vsTOT{nullptr}, hDTOA12vsTOT{nullptr}, hDTOA13vsTOT{nullptr}, hDTOA23vsTOT{nullptr},
                                                           hDTOA01Code{nullptr}, hDTOA02Code{nullptr}, hDTOA03Code{nullptr}, hDTOA12Code{nullptr}, hDTOA13Code{nullptr}, hDTOA23Code{nullptr},
                                                           hDTOA01{nullptr}, hDTOA02{nullptr}, hDTOA03{nullptr}, hDTOA12{nullptr}, hDTOA13{nullptr}, hDTOA23{nullptr}
{
    /*empty*/
}
HistoManagerETROC4Boards::~HistoManagerETROC4Boards()
{
    if (hTOACode0vsTOTCode0_C0)
        delete hTOACode0vsTOTCode0_C0;
    if (hTOACode0vsTOTCode0_C1)
        delete hTOACode0vsTOTCode0_C1;
    if (hTOACode0vsTOTCode0_C2)
        delete hTOACode0vsTOTCode0_C2;
    if (hTOACode1vsTOTCode1_C0)
        delete hTOACode1vsTOTCode1_C0;
    if (hTOACode1vsTOTCode1_C1)
        delete hTOACode1vsTOTCode1_C1;
    if (hTOACode1vsTOTCode1_C2)
        delete hTOACode1vsTOTCode1_C2;
    if (hTOACode2vsTOTCode2_C0)
        delete hTOACode2vsTOTCode2_C0;
    if (hTOACode2vsTOTCode2_C1)
        delete hTOACode2vsTOTCode2_C1;
    if (hTOACode2vsTOTCode2_C2)
        delete hTOACode2vsTOTCode2_C2;
    if (hTOACode3vsTOTCode3_C0)
        delete hTOACode3vsTOTCode3_C0;
    if (hTOACode3vsTOTCode3_C1)
        delete hTOACode3vsTOTCode3_C1;
    if (hTOACode3vsTOTCode3_C2)
        delete hTOACode3vsTOTCode3_C2;
    if (hTOACode0_C0)
        delete hTOACode0_C0;
    if (hTOACode0_C1)
        delete hTOACode0_C1;
    if (hTOACode0_C2)
        delete hTOACode0_C2;
    if (hTOACode1_C0)
        delete hTOACode1_C0;
    if (hTOACode1_C1)
        delete hTOACode1_C1;
    if (hTOACode1_C2)
        delete hTOACode1_C2;
    if (hTOACode2_C0)
        delete hTOACode2_C0;
    if (hTOACode2_C1)
        delete hTOACode2_C1;
    if (hTOACode2_C2)
        delete hTOACode2_C2;
    if (hTOACode3_C0)
        delete hTOACode3_C0;
    if (hTOACode3_C1)
        delete hTOACode3_C1;
    if (hTOACode3_C2)
        delete hTOACode3_C2;
    if (hTOTCode0_C0)
        delete hTOTCode0_C0;
    if (hTOTCode0_C1)
        delete hTOTCode0_C1;
    if (hTOTCode0_C2)
        delete hTOTCode0_C2;
    if (hTOTCode1_C0)
        delete hTOTCode1_C0;
    if (hTOTCode1_C1)
        delete hTOTCode1_C1;
    if (hTOTCode1_C2)
        delete hTOTCode1_C2;
    if (hTOTCode2_C0)
        delete hTOTCode2_C0;
    if (hTOTCode2_C1)
        delete hTOTCode2_C1;
    if (hTOTCode2_C2)
        delete hTOTCode2_C2;
    if (hTOTCode3_C0)
        delete hTOTCode3_C0;
    if (hTOTCode3_C1)
        delete hTOTCode3_C1;
    if (hTOTCode3_C2)
        delete hTOTCode3_C2;
    if (hTOACode0vsCALCode0_C0)
        delete hTOACode0vsCALCode0_C0;
    if (hTOACode0vsCALCode0_C1)
        delete hTOACode0vsCALCode0_C1;
    if (hTOACode0vsCALCode0_C2)
        delete hTOACode0vsCALCode0_C2;
    if (hTOACode1vsCALCode1_C0)
        delete hTOACode1vsCALCode1_C0;
    if (hTOACode1vsCALCode1_C1)
        delete hTOACode1vsCALCode1_C1;
    if (hTOACode1vsCALCode1_C2)
        delete hTOACode1vsCALCode1_C2;
    if (hTOACode2vsCALCode2_C0)
        delete hTOACode2vsCALCode2_C0;
    if (hTOACode2vsCALCode2_C1)
        delete hTOACode2vsCALCode2_C1;
    if (hTOACode2vsCALCode2_C2)
        delete hTOACode2vsCALCode2_C2;
    if (hTOACode3vsCALCode3_C0)
        delete hTOACode3vsCALCode3_C0;
    if (hTOACode3vsCALCode3_C1)
        delete hTOACode3vsCALCode3_C1;
    if (hTOACode3vsCALCode3_C2)
        delete hTOACode3vsCALCode3_C2;
    if (hTOTCode0vsCALCode0_C0)
        delete hTOTCode0vsCALCode0_C0;
    if (hTOTCode0vsCALCode0_C1)
        delete hTOTCode0vsCALCode0_C1;
    if (hTOTCode0vsCALCode0_C2)
        delete hTOTCode0vsCALCode0_C2;
    if (hTOTCode1vsCALCode1_C0)
        delete hTOTCode1vsCALCode1_C0;
    if (hTOTCode1vsCALCode1_C1)
        delete hTOTCode1vsCALCode1_C1;
    if (hTOTCode1vsCALCode1_C2)
        delete hTOTCode1vsCALCode1_C2;
    if (hTOTCode2vsCALCode2_C0)
        delete hTOTCode2vsCALCode2_C0;
    if (hTOTCode2vsCALCode2_C1)
        delete hTOTCode2vsCALCode2_C1;
    if (hTOTCode2vsCALCode2_C2)
        delete hTOTCode2vsCALCode2_C2;
    if (hTOTCode3vsCALCode3_C0)
        delete hTOTCode3vsCALCode3_C0;
    if (hTOTCode3vsCALCode3_C1)
        delete hTOTCode3vsCALCode3_C1;
    if (hTOTCode3vsCALCode3_C2)
        delete hTOTCode3vsCALCode3_C2;
    if (hCALCode0_C0)
        delete hCALCode0_C0;
    if (hCALCode0_C1)
        delete hCALCode0_C1;
    if (hCALCode0_C2)
        delete hCALCode0_C2;
    if (hCALCode1_C0)
        delete hCALCode1_C0;
    if (hCALCode1_C1)
        delete hCALCode1_C1;
    if (hCALCode1_C2)
        delete hCALCode1_C2;
    if (hCALCode2_C0)
        delete hCALCode2_C0;
    if (hCALCode2_C1)
        delete hCALCode2_C1;
    if (hCALCode2_C2)
        delete hCALCode2_C2;
    if (hCALCode3_C0)
        delete hCALCode3_C0;
    if (hCALCode3_C1)
        delete hCALCode3_C1;
    if (hCALCode3_C2)
        delete hCALCode3_C2;
    if (hTOA0vsTOT0_C0)
        delete hTOA0vsTOT0_C0;
    if (hTOA0vsTOT0_C1)
        delete hTOA0vsTOT0_C1;
    if (hTOA0vsTOT0_C2)
        delete hTOA0vsTOT0_C2;
    if (hTOA1vsTOT1_C0)
        delete hTOA1vsTOT1_C0;
    if (hTOA1vsTOT1_C1)
        delete hTOA1vsTOT1_C1;
    if (hTOA1vsTOT1_C2)
        delete hTOA1vsTOT1_C2;
    if (hTOA2vsTOT2_C0)
        delete hTOA2vsTOT2_C0;
    if (hTOA2vsTOT2_C1)
        delete hTOA2vsTOT2_C1;
    if (hTOA2vsTOT2_C2)
        delete hTOA2vsTOT2_C2;
    if (hTOA3vsTOT3_C0)
        delete hTOA3vsTOT3_C0;
    if (hTOA3vsTOT3_C1)
        delete hTOA3vsTOT3_C1;
    if (hTOA3vsTOT3_C2)
        delete hTOA3vsTOT3_C2;
    if (hTOA0_C0)
        delete hTOA0_C0;
    if (hTOA0_C1)
        delete hTOA0_C1;
    if (hTOA0_C2)
        delete hTOA0_C2;
    if (hTOA1_C0)
        delete hTOA1_C0;
    if (hTOA1_C1)
        delete hTOA1_C1;
    if (hTOA1_C2)
        delete hTOA1_C2;
    if (hTOA2_C0)
        delete hTOA2_C0;
    if (hTOA2_C1)
        delete hTOA2_C1;
    if (hTOA2_C2)
        delete hTOA2_C2;
    if (hTOA3_C0)
        delete hTOA3_C0;
    if (hTOA3_C1)
        delete hTOA3_C1;
    if (hTOA3_C2)
        delete hTOA3_C2;
    if (hTOT0_C0)
        delete hTOT0_C0;
    if (hTOT0_C1)
        delete hTOT0_C1;
    if (hTOT0_C2)
        delete hTOT0_C2;
    if (hTOT1_C0)
        delete hTOT1_C0;
    if (hTOT1_C1)
        delete hTOT1_C1;
    if (hTOT1_C2)
        delete hTOT1_C2;
    if (hTOT2_C0)
        delete hTOT2_C0;
    if (hTOT2_C1)
        delete hTOT2_C1;
    if (hTOT2_C2)
        delete hTOT2_C2;
    if (hTOT3_C0)
        delete hTOT3_C0;
    if (hTOT3_C1)
        delete hTOT3_C1;
    if (hTOT3_C2)
        delete hTOT3_C2;
    if (hTOA0vsCALCode0_C0)
        delete hTOA0vsCALCode0_C0;
    if (hTOA0vsCALCode0_C1)
        delete hTOA0vsCALCode0_C1;
    if (hTOA0vsCALCode0_C2)
        delete hTOA0vsCALCode0_C2;
    if (hTOA1vsCALCode1_C0)
        delete hTOA1vsCALCode1_C0;
    if (hTOA1vsCALCode1_C1)
        delete hTOA1vsCALCode1_C1;
    if (hTOA1vsCALCode1_C2)
        delete hTOA1vsCALCode1_C2;
    if (hTOA2vsCALCode2_C0)
        delete hTOA2vsCALCode2_C0;
    if (hTOA2vsCALCode2_C1)
        delete hTOA2vsCALCode2_C1;
    if (hTOA2vsCALCode2_C2)
        delete hTOA2vsCALCode2_C2;
    if (hTOA3vsCALCode3_C0)
        delete hTOA3vsCALCode3_C0;
    if (hTOA3vsCALCode3_C1)
        delete hTOA3vsCALCode3_C1;
    if (hTOA3vsCALCode3_C2)
        delete hTOA3vsCALCode3_C2;
    if (hTOT0vsCALCode0_C0)
        delete hTOT0vsCALCode0_C0;
    if (hTOT0vsCALCode0_C1)
        delete hTOT0vsCALCode0_C1;
    if (hTOT0vsCALCode0_C2)
        delete hTOT0vsCALCode0_C2;
    if (hTOT1vsCALCode1_C0)
        delete hTOT1vsCALCode1_C0;
    if (hTOT1vsCALCode1_C1)
        delete hTOT1vsCALCode1_C1;
    if (hTOT1vsCALCode1_C2)
        delete hTOT1vsCALCode1_C2;
    if (hTOT2vsCALCode2_C0)
        delete hTOT2vsCALCode2_C0;
    if (hTOT2vsCALCode2_C1)
        delete hTOT2vsCALCode2_C1;
    if (hTOT2vsCALCode2_C2)
        delete hTOT2vsCALCode2_C2;
    if (hTOT3vsCALCode3_C0)
        delete hTOT3vsCALCode3_C0;
    if (hTOT3vsCALCode3_C1)
        delete hTOT3vsCALCode3_C1;
    if (hTOT3vsCALCode3_C2)
        delete hTOT3vsCALCode3_C2;
    if (hTOACode0vsTOACode1_C0)
        delete hTOACode0vsTOACode1_C0;
    if (hTOACode0vsTOACode2_C0)
        delete hTOACode0vsTOACode2_C0;
    if (hTOACode0vsTOACode3_C0)
        delete hTOACode0vsTOACode3_C0;
    if (hTOACode1vsTOACode2_C0)
        delete hTOACode1vsTOACode2_C0;
    if (hTOACode1vsTOACode3_C0)
        delete hTOACode1vsTOACode3_C0;
    if (hTOACode2vsTOACode3_C0)
        delete hTOACode2vsTOACode3_C0;

    if (hTOACode0vsTOACode1_C1)
        delete hTOACode0vsTOACode1_C1;
    if (hTOACode0vsTOACode2_C1)
        delete hTOACode0vsTOACode2_C1;
    if (hTOACode0vsTOACode3_C1)
        delete hTOACode0vsTOACode3_C1;
    if (hTOACode1vsTOACode2_C1)
        delete hTOACode1vsTOACode2_C1;
    if (hTOACode1vsTOACode3_C1)
        delete hTOACode1vsTOACode3_C1;
    if (hTOACode2vsTOACode3_C1)
        delete hTOACode2vsTOACode3_C1;

    if (hTOACode0vsTOACode1_C2)
        delete hTOACode0vsTOACode1_C2;
    if (hTOACode0vsTOACode2_C2)
        delete hTOACode0vsTOACode2_C2;
    if (hTOACode0vsTOACode3_C2)
        delete hTOACode0vsTOACode3_C2;
    if (hTOACode1vsTOACode2_C2)
        delete hTOACode1vsTOACode2_C2;
    if (hTOACode1vsTOACode3_C2)
        delete hTOACode1vsTOACode3_C2;
    if (hTOACode2vsTOACode3_C2)
        delete hTOACode2vsTOACode3_C2;

    if (hTOA0vsTOA1_C0)
        delete hTOA0vsTOA1_C0;
    if (hTOA0vsTOA2_C0)
        delete hTOA0vsTOA2_C0;
    if (hTOA0vsTOA3_C0)
        delete hTOA0vsTOA3_C0;
    if (hTOA1vsTOA2_C0)
        delete hTOA1vsTOA2_C0;
    if (hTOA1vsTOA3_C0)
        delete hTOA1vsTOA3_C0;
    if (hTOA2vsTOA3_C0)
        delete hTOA2vsTOA3_C0;

    if (hDTOA01Code)
        delete hDTOA01Code;
    if (hDTOA02Code)
        delete hDTOA02Code;
    if (hDTOA03Code)
        delete hDTOA03Code;
    if (hDTOA12Code)
        delete hDTOA12Code;
    if (hDTOA13Code)
        delete hDTOA13Code;
    if (hDTOA23Code)
        delete hDTOA23Code;

    if (hDTOA01)
        delete hDTOA01;
    if (hDTOA02)
        delete hDTOA02;
    if (hDTOA03)
        delete hDTOA03;
    if (hDTOA12)
        delete hDTOA12;
    if (hDTOA13)
        delete hDTOA13;
    if (hDTOA23)
        delete hDTOA23;

    for (int i = 0; i < 2; i++)
    {
        if (pDTOA01CodevsTOTCode[i])
            delete pDTOA01CodevsTOTCode[i];
        if (pDTOA02CodevsTOTCode[i])
            delete pDTOA02CodevsTOTCode[i];
        if (pDTOA03CodevsTOTCode[i])
            delete pDTOA03CodevsTOTCode[i];
        if (pDTOA12CodevsTOTCode[i])
            delete pDTOA12CodevsTOTCode[i];
        if (pDTOA13CodevsTOTCode[i])
            delete pDTOA13CodevsTOTCode[i];
        if (pDTOA23CodevsTOTCode[i])
            delete pDTOA23CodevsTOTCode[i];

        if (pDTOA01vsTOT[i])
            delete pDTOA01vsTOT[i];
        if (pDTOA02vsTOT[i])
            delete pDTOA02vsTOT[i];
        if (pDTOA03vsTOT[i])
            delete pDTOA03vsTOT[i];
        if (pDTOA12vsTOT[i])
            delete pDTOA12vsTOT[i];
        if (pDTOA13vsTOT[i])
            delete pDTOA13vsTOT[i];
        if (pDTOA23vsTOT[i])
            delete pDTOA23vsTOT[i];

        if (hDTOA01CodevsTOTCode[i])
            delete hDTOA01CodevsTOTCode[i];
        if (hDTOA02CodevsTOTCode[i])
            delete hDTOA02CodevsTOTCode[i];
        if (hDTOA03CodevsTOTCode[i])
            delete hDTOA03CodevsTOTCode[i];
        if (hDTOA12CodevsTOTCode[i])
            delete hDTOA12CodevsTOTCode[i];
        if (hDTOA13CodevsTOTCode[i])
            delete hDTOA13CodevsTOTCode[i];
        if (hDTOA23CodevsTOTCode[i])
            delete hDTOA23CodevsTOTCode[i];

        if (hDTOA01vsTOT[i])
            delete hDTOA01vsTOT[i];
        if (hDTOA02vsTOT[i])
            delete hDTOA02vsTOT[i];
        if (hDTOA03vsTOT[i])
            delete hDTOA03vsTOT[i];
        if (hDTOA12vsTOT[i])
            delete hDTOA12vsTOT[i];
        if (hDTOA13vsTOT[i])
            delete hDTOA13vsTOT[i];
        if (hDTOA23vsTOT[i])
            delete hDTOA23vsTOT[i];
    }
}

void HistoManagerETROC4Boards::init()
{

    hTOACode0vsTOTCode0_C0 = new TH2D("hTOACode0vsTOTCode0_C0", "TOA Code 0 vs TOT Code 0 C0;TOT Code 0;TOA Code 0", TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
    hTOACode0vsTOTCode0_C0->Sumw2();
    hTOACode0vsTOTCode0_C1 = new TH2D("hTOACode0vsTOTCode0_C1", "TOA Code 0 vs TOT Code 0 C1;TOT Code 0;TOA Code 0", TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
    hTOACode0vsTOTCode0_C1->Sumw2();
    hTOACode0vsTOTCode0_C2 = new TH2D("hTOACode0vsTOTCode0_C2", "TOA Code 0 vs TOT Code 0 C2;TOT Code 0;TOA Code 0", TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
    hTOACode0vsTOTCode0_C2->Sumw2();

    hTOACode1vsTOTCode1_C0 = new TH2D("hTOACode1vsTOTCode1_C0", "TOA Code 1 vs TOT Code 1 C0;TOT Code 1;TOA Code 1", TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
    hTOACode1vsTOTCode1_C0->Sumw2();
    hTOACode1vsTOTCode1_C1 = new TH2D("hTOACode1vsTOTCode1_C1", "TOA Code 1 vs TOT Code 1 C1;TOT Code 1;TOA Code 1", TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
    hTOACode1vsTOTCode1_C1->Sumw2();
    hTOACode1vsTOTCode1_C2 = new TH2D("hTOACode1vsTOTCode1_C2", "TOA Code 1 vs TOT Code 1 C2;TOT Code 1;TOA Code 1", TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
    hTOACode1vsTOTCode1_C2->Sumw2();

    hTOACode2vsTOTCode2_C0 = new TH2D("hTOACode2vsTOTCode2_C0", "TOA Code 2 vs TOT Code 2 C0;TOT Code 2;TOA Code 2", TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
    hTOACode2vsTOTCode2_C0->Sumw2();
    hTOACode2vsTOTCode2_C1 = new TH2D("hTOACode2vsTOTCode2_C1", "TOA Code 2 vs TOT Code 2 C1;TOT Code 2;TOA Code 2", TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
    hTOACode2vsTOTCode2_C1->Sumw2();
    hTOACode2vsTOTCode2_C2 = new TH2D("hTOACode2vsTOTCode2_C2", "TOA Code 2 vs TOT Code 2 C2;TOT Code 2;TOA Code 2", TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
    hTOACode2vsTOTCode2_C2->Sumw2();

    hTOACode3vsTOTCode3_C0 = new TH2D("hTOACode3vsTOTCode3_C0", "TOA Code 3 vs TOT Code 3 C0;TOT Code 3;TOA Code 3", TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
    hTOACode3vsTOTCode3_C0->Sumw2();
    hTOACode3vsTOTCode3_C1 = new TH2D("hTOACode3vsTOTCode3_C1", "TOA Code 3 vs TOT Code 3 C1;TOT Code 3;TOA Code 3", TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
    hTOACode3vsTOTCode3_C1->Sumw2();
    hTOACode3vsTOTCode3_C2 = new TH2D("hTOACode3vsTOTCode3_C2", "TOA Code 3 vs TOT Code 3 C2;TOT Code 3;TOA Code 3", TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
    hTOACode3vsTOTCode3_C2->Sumw2();

    hTOACode0vsCALCode0_C0 = new TH2D("hTOACode0vsCALCode0_C0", "TOA Code 0 vs CAL Code 0 C0;CAL Code 0;TOA Code 0", CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
    hTOACode0vsCALCode0_C0->Sumw2();
    hTOACode0vsCALCode0_C1 = new TH2D("hTOACode0vsCALCode0_C1", "TOA Code 0 vs CAL Code 0 C1;CAL Code 0;TOA Code 0", CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
    hTOACode0vsCALCode0_C1->Sumw2();
    hTOACode0vsCALCode0_C2 = new TH2D("hTOACode0vsCALCode0_C2", "TOA Code 0 vs CAL Code 0 C2;CAL Code 0;TOA Code 0", CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
    hTOACode0vsCALCode0_C2->Sumw2();

    hTOACode1vsCALCode1_C0 = new TH2D("hTOACode1vsCALCode1_C0", "TOA Code 1 vs CAL Code 1 C0;CAL Code 1;TOA Code 1", CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
    hTOACode1vsCALCode1_C0->Sumw2();
    hTOACode1vsCALCode1_C1 = new TH2D("hTOACode1vsCALCode1_C1", "TOA Code 1 vs CAL Code 1 C1;CAL Code 1;TOA Code 1", CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
    hTOACode1vsCALCode1_C1->Sumw2();
    hTOACode1vsCALCode1_C2 = new TH2D("hTOACode1vsCALCode1_C2", "TOA Code 1 vs CAL Code 1 C2;CAL Code 1;TOA Code 1", CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
    hTOACode1vsCALCode1_C2->Sumw2();

    hTOACode2vsCALCode2_C0 = new TH2D("hTOACode2vsCALCode2_C0", "TOA Code 2 vs CAL Code 2 C0;CAL Code 2;TOA Code 2", CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
    hTOACode2vsCALCode2_C0->Sumw2();
    hTOACode2vsCALCode2_C1 = new TH2D("hTOACode2vsCALCode2_C1", "TOA Code 2 vs CAL Code 2 C1;CAL Code 2;TOA Code 2", CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
    hTOACode2vsCALCode2_C1->Sumw2();
    hTOACode2vsCALCode2_C2 = new TH2D("hTOACode2vsCALCode2_C2", "TOA Code 2 vs CAL Code 2 C2;CAL Code 2;TOA Code 2", CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
    hTOACode2vsCALCode2_C2->Sumw2();

    hTOACode3vsCALCode3_C0 = new TH2D("hTOACode3vsCALCode3_C0", "TOA Code 3 vs CAL Code 3 C0;CAL Code 3;TOA Code 3", CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
    hTOACode3vsCALCode3_C0->Sumw2();
    hTOACode3vsCALCode3_C1 = new TH2D("hTOACode3vsCALCode3_C1", "TOA Code 3 vs CAL Code 3 C1;CAL Code 3;TOA Code 3", CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
    hTOACode3vsCALCode3_C1->Sumw2();
    hTOACode3vsCALCode3_C2 = new TH2D("hTOACode3vsCALCode3_C2", "TOA Code 3 vs CAL Code 3 C2;CAL Code 3;TOA Code 3", CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
    hTOACode3vsCALCode3_C2->Sumw2();

    hTOTCode0vsCALCode0_C0 = new TH2D("hTOTCode0vsCALCode0_C0", "TOT Code 0 vs CAL Code 0 C0;CAL Code 0;TOT Code 0", CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1]);
    hTOTCode0vsCALCode0_C0->Sumw2();
    hTOTCode0vsCALCode0_C1 = new TH2D("hTOTCode0vsCALCode0_C1", "TOT Code 0 vs CAL Code 0 C1;CAL Code 0;TOT Code 0", CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1]);
    hTOTCode0vsCALCode0_C1->Sumw2();
    hTOTCode0vsCALCode0_C2 = new TH2D("hTOTCode0vsCALCode0_C2", "TOT Code 0 vs CAL Code 0 C2;CAL Code 0;TOT Code 0", CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1]);
    hTOTCode0vsCALCode0_C2->Sumw2();

    hTOTCode1vsCALCode1_C0 = new TH2D("hTOTCode1vsCALCode1_C0", "TOT Code 1 vs CAL Code 1 C0;CAL Code 1;TOT Code 1", CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1]);
    hTOTCode1vsCALCode1_C0->Sumw2();
    hTOTCode1vsCALCode1_C1 = new TH2D("hTOTCode1vsCALCode1_C1", "TOT Code 1 vs CAL Code 1 C1;CAL Code 1;TOT Code 1", CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1]);
    hTOTCode1vsCALCode1_C1->Sumw2();
    hTOTCode1vsCALCode1_C2 = new TH2D("hTOTCode1vsCALCode1_C2", "TOT Code 1 vs CAL Code 1 C2;CAL Code 1;TOT Code 1", CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1]);
    hTOTCode1vsCALCode1_C2->Sumw2();

    hTOTCode2vsCALCode2_C0 = new TH2D("hTOTCode2vsCALCode2_C0", "TOT Code 2 vs CAL Code 2 C0;CAL Code 2;TOT Code 2", CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1]);
    hTOTCode2vsCALCode2_C0->Sumw2();
    hTOTCode2vsCALCode2_C1 = new TH2D("hTOTCode2vsCALCode2_C1", "TOT Code 2 vs CAL Code 2 C1;CAL Code 2;TOT Code 2", CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1]);
    hTOTCode2vsCALCode2_C1->Sumw2();
    hTOTCode2vsCALCode2_C2 = new TH2D("hTOTCode2vsCALCode2_C2", "TOT Code 2 vs CAL Code 2 C2;CAL Code 2;TOT Code 2", CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1]);
    hTOTCode2vsCALCode2_C2->Sumw2();

    hTOTCode3vsCALCode3_C0 = new TH2D("hTOTCode3vsCALCode3_C0", "TOT Code 3 vs CAL Code 3 C0;CAL Code 3;TOT Code 3", CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1]);
    hTOTCode3vsCALCode3_C0->Sumw2();
    hTOTCode3vsCALCode3_C1 = new TH2D("hTOTCode3vsCALCode3_C1", "TOT Code 3 vs CAL Code 3 C1;CAL Code 3;TOT Code 3", CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1]);
    hTOTCode3vsCALCode3_C1->Sumw2();
    hTOTCode3vsCALCode3_C2 = new TH2D("hTOTCode3vsCALCode3_C2", "TOT Code 3 vs CAL Code 3 C2;CAL Code 3;TOT Code 3", CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1]);
    hTOTCode3vsCALCode3_C2->Sumw2();

    hTOA0vsTOT0_C0 = new TH2D("hTOA0vsTOT0_C0", "TOA 0 vs TOT 0 C0;TOT 0;TOA 0", TOTBins, TOTRange[0], TOTRange[1], TOABins, TOARange[0], TOARange[1]);
    hTOA0vsTOT0_C0->Sumw2();
    hTOA0vsTOT0_C1 = new TH2D("hTOA0vsTOT0_C1", "TOA 0 vs TOT 0 C1;TOT 0;TOA 0", TOTBins, TOTRange[0], TOTRange[1], TOABins, TOARange[0], TOARange[1]);
    hTOA0vsTOT0_C1->Sumw2();
    hTOA0vsTOT0_C2 = new TH2D("hTOA0vsTOT0_C2", "TOA 0 vs TOT 0 C2;TOT 0;TOA 0", TOTBins, TOTRange[0], TOTRange[1], TOABins, TOARange[0], TOARange[1]);
    hTOA0vsTOT0_C2->Sumw2();

    hTOA1vsTOT1_C0 = new TH2D("hTOA1vsTOT1_C0", "TOA 1 vs TOT 1 C0;TOT 1;TOA 1", TOTBins, TOTRange[0], TOTRange[1], TOABins, TOARange[0], TOARange[1]);
    hTOA1vsTOT1_C0->Sumw2();
    hTOA1vsTOT1_C1 = new TH2D("hTOA1vsTOT1_C1", "TOA 1 vs TOT 1 C1;TOT 1;TOA 1", TOTBins, TOTRange[0], TOTRange[1], TOABins, TOARange[0], TOARange[1]);
    hTOA1vsTOT1_C1->Sumw2();
    hTOA1vsTOT1_C2 = new TH2D("hTOA1vsTOT1_C2", "TOA 1 vs TOT 1 C2;TOT 1;TOA 1", TOTBins, TOTRange[0], TOTRange[1], TOABins, TOARange[0], TOARange[1]);
    hTOA1vsTOT1_C2->Sumw2();

    hTOA2vsTOT2_C0 = new TH2D("hTOA2vsTOT2_C0", "TOA 2 vs TOT 2 C0;TOT 2;TOA 2", TOTBins, TOTRange[0], TOTRange[1], TOABins, TOARange[0], TOARange[1]);
    hTOA2vsTOT2_C0->Sumw2();
    hTOA2vsTOT2_C1 = new TH2D("hTOA2vsTOT2_C1", "TOA 2 vs TOT 2 C1;TOT 2;TOA 2", TOTBins, TOTRange[0], TOTRange[1], TOABins, TOARange[0], TOARange[1]);
    hTOA2vsTOT2_C1->Sumw2();
    hTOA2vsTOT2_C2 = new TH2D("hTOA2vsTOT2_C2", "TOA 2 vs TOT 2 C2;TOT 2;TOA 2", TOTBins, TOTRange[0], TOTRange[1], TOABins, TOARange[0], TOARange[1]);
    hTOA2vsTOT2_C2->Sumw2();

    hTOA3vsTOT3_C0 = new TH2D("hTOA3vsTOT3_C0", "TOA 3 vs TOT 3 C0;TOT 3;TOA 3", TOTBins, TOTRange[0], TOTRange[1], TOABins, TOARange[0], TOARange[1]);
    hTOA3vsTOT3_C0->Sumw2();
    hTOA3vsTOT3_C1 = new TH2D("hTOA3vsTOT3_C1", "TOA 3 vs TOT 3 C1;TOT 3;TOA 3", TOTBins, TOTRange[0], TOTRange[1], TOABins, TOARange[0], TOARange[1]);
    hTOA3vsTOT3_C1->Sumw2();
    hTOA3vsTOT3_C2 = new TH2D("hTOA3vsTOT3_C2", "TOA 3 vs TOT 3 C2;TOT 3;TOA 3", TOTBins, TOTRange[0], TOTRange[1], TOABins, TOARange[0], TOARange[1]);
    hTOA3vsTOT3_C2->Sumw2();

    hTOA0vsCALCode0_C0 = new TH2D("hTOA0vsCALCode0_C0", "TOA 0 vs CAL Code 0 C0;CAL Code 0;TOA 0", CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOABins, TOARange[0], TOARange[1]);
    hTOA0vsCALCode0_C0->Sumw2();
    hTOA0vsCALCode0_C1 = new TH2D("hTOA0vsCALCode0_C1", "TOA 0 vs CAL Code 0 C1;CAL Code 0;TOA 0", CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOABins, TOARange[0], TOARange[1]);
    hTOA0vsCALCode0_C1->Sumw2();
    hTOA0vsCALCode0_C2 = new TH2D("hTOA0vsCALCode0_C2", "TOA 0 vs CAL Code 0 C2;CAL Code 0;TOA 0", CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOABins, TOARange[0], TOARange[1]);
    hTOA0vsCALCode0_C2->Sumw2();

    hTOA1vsCALCode1_C0 = new TH2D("hTOA1vsCALCode1_C0", "TOA 1 vs CAL Code 1 C0;CAL Code 1;TOA 1", CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOABins, TOARange[0], TOARange[1]);
    hTOA1vsCALCode1_C0->Sumw2();
    hTOA1vsCALCode1_C1 = new TH2D("hTOA1vsCALCode1_C1", "TOA 1 vs CAL Code 1 C1;CAL Code 1;TOA 1", CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOABins, TOARange[0], TOARange[1]);
    hTOA1vsCALCode1_C1->Sumw2();
    hTOA1vsCALCode1_C2 = new TH2D("hTOA1vsCALCode1_C2", "TOA 1 vs CAL Code 1 C2;CAL Code 1;TOA 1", CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOABins, TOARange[0], TOARange[1]);
    hTOA1vsCALCode1_C2->Sumw2();

    hTOA2vsCALCode2_C0 = new TH2D("hTOA2vsCALCode2_C0", "TOA 2 vs CAL Code 2 C0;CAL Code 2;TOA 2", CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOABins, TOARange[0], TOARange[1]);
    hTOA2vsCALCode2_C0->Sumw2();
    hTOA2vsCALCode2_C1 = new TH2D("hTOA2vsCALCode2_C1", "TOA 2 vs CAL Code 2 C1;CAL Code 2;TOA 2", CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOABins, TOARange[0], TOARange[1]);
    hTOA2vsCALCode2_C1->Sumw2();
    hTOA2vsCALCode2_C2 = new TH2D("hTOA2vsCALCode2_C2", "TOA 2 vs CAL Code 2 C2;CAL Code 2;TOA 2", CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOABins, TOARange[0], TOARange[1]);
    hTOA2vsCALCode2_C2->Sumw2();

    hTOA3vsCALCode3_C0 = new TH2D("hTOA3vsCALCode3_C0", "TOA 3 vs CAL Code 3 C0;CAL Code 3;TOA 3", CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOABins, TOARange[0], TOARange[1]);
    hTOA3vsCALCode3_C0->Sumw2();
    hTOA3vsCALCode3_C1 = new TH2D("hTOA3vsCALCode3_C1", "TOA 3 vs CAL Code 3 C1;CAL Code 3;TOA 3", CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOABins, TOARange[0], TOARange[1]);
    hTOA3vsCALCode3_C1->Sumw2();
    hTOA3vsCALCode3_C2 = new TH2D("hTOA3vsCALCode3_C2", "TOA 3 vs CAL Code 3 C2;CAL Code 3;TOA 3", CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOABins, TOARange[0], TOARange[1]);
    hTOA3vsCALCode3_C2->Sumw2();

    hTOT0vsCALCode0_C0 = new TH2D("hTOT0vsCALCode0_C0", "TOT 0 vs CAL Code 0 C0;CAL Code 0;TOT 0", CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOTBins, TOTRange[0], TOTRange[1]);
    hTOT0vsCALCode0_C0->Sumw2();
    hTOT0vsCALCode0_C1 = new TH2D("hTOT0vsCALCode0_C1", "TOT 0 vs CAL Code 0 C1;CAL Code 0;TOT 0", CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOTBins, TOTRange[0], TOTRange[1]);
    hTOT0vsCALCode0_C1->Sumw2();
    hTOT0vsCALCode0_C2 = new TH2D("hTOT0vsCALCode0_C2", "TOT 0 vs CAL Code 0 C2;CAL Code 0;TOT 0", CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOTBins, TOTRange[0], TOTRange[1]);
    hTOT0vsCALCode0_C2->Sumw2();

    hTOT1vsCALCode1_C0 = new TH2D("hTOT1vsCALCode1_C0", "TOT 1 vs CAL Code 1 C0;CAL Code 1;TOT 1", CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOTBins, TOTRange[0], TOTRange[1]);
    hTOT1vsCALCode1_C0->Sumw2();
    hTOT1vsCALCode1_C1 = new TH2D("hTOT1vsCALCode1_C1", "TOT 1 vs CAL Code 1 C1;CAL Code 1;TOT 1", CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOTBins, TOTRange[0], TOTRange[1]);
    hTOT1vsCALCode1_C1->Sumw2();
    hTOT1vsCALCode1_C2 = new TH2D("hTOT1vsCALCode1_C2", "TOT 1 vs CAL Code 1 C2;CAL Code 1;TOT 1", CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOTBins, TOTRange[0], TOTRange[1]);
    hTOT1vsCALCode1_C2->Sumw2();

    hTOT2vsCALCode2_C0 = new TH2D("hTOT2vsCALCode2_C0", "TOT 2 vs CAL Code 2 C0;CAL Code 2;TOT 2", CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOTBins, TOTRange[0], TOTRange[1]);
    hTOT2vsCALCode2_C0->Sumw2();
    hTOT2vsCALCode2_C1 = new TH2D("hTOT2vsCALCode2_C1", "TOT 2 vs CAL Code 2 C1;CAL Code 2;TOT 2", CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOTBins, TOTRange[0], TOTRange[1]);
    hTOT2vsCALCode2_C1->Sumw2();
    hTOT2vsCALCode2_C2 = new TH2D("hTOT2vsCALCode2_C2", "TOT 2 vs CAL Code 2 C2;CAL Code 2;TOT 2", CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOTBins, TOTRange[0], TOTRange[1]);
    hTOT2vsCALCode2_C2->Sumw2();

    hTOT3vsCALCode3_C0 = new TH2D("hTOT3vsCALCode3_C0", "TOT 3 vs CAL Code 3 C0;CAL Code 3;TOT 3", CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOTBins, TOTRange[0], TOTRange[1]);
    hTOT3vsCALCode3_C0->Sumw2();
    hTOT3vsCALCode3_C1 = new TH2D("hTOT3vsCALCode3_C1", "TOT 3 vs CAL Code 3 C1;CAL Code 3;TOT 3", CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOTBins, TOTRange[0], TOTRange[1]);
    hTOT3vsCALCode3_C1->Sumw2();
    hTOT3vsCALCode3_C2 = new TH2D("hTOT3vsCALCode3_C2", "TOT 3 vs CAL Code 3 C2;CAL Code 3;TOT 3", CALCodeBins, CALCodeRange[0], CALCodeRange[1], TOTBins, TOTRange[0], TOTRange[1]);
    hTOT3vsCALCode3_C2->Sumw2();

    pDTOA01CodevsTOTCode[0] = new TProfile("pDTOA01CodevsTOTCode0", "DTOA 01 Code vs TOT Code 0;TOT Code 0;DTOA 01 Code", TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1]);
    pDTOA01CodevsTOTCode[1] = new TProfile("pDTOA01CodevsTOTCode1", "DTOA 01 Code vs TOT Code 1;TOT Code 1;DTOA 01 Code", TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1]);

    pDTOA02CodevsTOTCode[0] = new TProfile("pDTOA02CodevsTOTCode0", "DTOA 02 Code vs TOT Code 0;TOT Code 0;DTOA 02 Code", TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1]);
    pDTOA02CodevsTOTCode[1] = new TProfile("pDTOA02CodevsTOTCode2", "DTOA 02 Code vs TOT Code 2;TOT Code 2;DTOA 02 Code", TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1]);

    pDTOA03CodevsTOTCode[0] = new TProfile("pDTOA03CodevsTOTCode0", "DTOA 03 Code vs TOT Code 0;TOT Code 0;DTOA 03 Code", TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1]);
    pDTOA03CodevsTOTCode[1] = new TProfile("pDTOA03CodevsTOTCode3", "DTOA 03 Code vs TOT Code 3;TOT Code 3;DTOA 03 Code", TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1]);

    pDTOA12CodevsTOTCode[0] = new TProfile("pDTOA12CodevsTOTCode1", "DTOA 12 Code vs TOT Code 1;TOT Code 1;DTOA 12 Code", TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1]);
    pDTOA12CodevsTOTCode[1] = new TProfile("pDTOA12CodevsTOTCode2", "DTOA 12 Code vs TOT Code 2;TOT Code 2;DTOA 12 Code", TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1]);

    pDTOA13CodevsTOTCode[0] = new TProfile("pDTOA13CodevsTOTCode1", "DTOA 13 Code vs TOT Code 1;TOT Code 1;DTOA 13 Code", TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1]);
    pDTOA13CodevsTOTCode[1] = new TProfile("pDTOA13CodevsTOTCode3", "DTOA 13 Code vs TOT Code 3;TOT Code 3;DTOA 13 Code", TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1]);

    pDTOA23CodevsTOTCode[0] = new TProfile("pDTOA23CodevsTOTCode2", "DTOA 23 Code vs TOT Code 2;TOT Code 2;DTOA 23 Code", TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1]);
    pDTOA23CodevsTOTCode[1] = new TProfile("pDTOA23CodevsTOTCode3", "DTOA 23 Code vs TOT Code 3;TOT Code 3;DTOA 23 Code", TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1]);

    pDTOA01vsTOT[0] = new TProfile("pDTOA01vsTOT0", "DTOA 01 vs TOT 0;TOT 0;DTOA 01", TOTBins, TOTRange[0], TOTRange[1]);
    pDTOA01vsTOT[1] = new TProfile("pDTOA01vsTOT1", "DTOA 01 vs TOT 1;TOT 1;DTOA 01", TOTBins, TOTRange[0], TOTRange[1]);

    pDTOA02vsTOT[0] = new TProfile("pDTOA02vsTOT0", "DTOA 02 vs TOT 0;TOT 0;DTOA 02", TOTBins, TOTRange[0], TOTRange[1]);
    pDTOA02vsTOT[1] = new TProfile("pDTOA02vsTOT2", "DTOA 02 vs TOT 2;TOT 2;DTOA 02", TOTBins, TOTRange[0], TOTRange[1]);

    pDTOA03vsTOT[0] = new TProfile("pDTOA03vsTOT0", "DTOA 03 vs TOT 0;TOT 0;DTOA 03", TOTBins, TOTRange[0], TOTRange[1]);
    pDTOA03vsTOT[1] = new TProfile("pDTOA03vsTOT3", "DTOA 03 vs TOT 3;TOT 3;DTOA 03", TOTBins, TOTRange[0], TOTRange[1]);

    pDTOA12vsTOT[0] = new TProfile("pDTOA12vsTOT1", "DTOA 12 vs TOT 1;TOT 1;DTOA 12", TOTBins, TOTRange[0], TOTRange[1]);
    pDTOA12vsTOT[1] = new TProfile("pDTOA12vsTOT2", "DTOA 12 vs TOT 2;TOT 2;DTOA 12", TOTBins, TOTRange[0], TOTRange[1]);

    pDTOA13vsTOT[0] = new TProfile("pDTOA13vsTOT1", "DTOA 13 vs TOT 1;TOT 1;DTOA 13", TOTBins, TOTRange[0], TOTRange[1]);
    pDTOA13vsTOT[1] = new TProfile("pDTOA13vsTOT3", "DTOA 13 vs TOT 3;TOT 3;DTOA 13", TOTBins, TOTRange[0], TOTRange[1]);

    pDTOA23vsTOT[0] = new TProfile("pDTOA23vsTOT2", "DTOA 23 vs TOT 2;TOT 2;DTOA 23", TOTBins, TOTRange[0], TOTRange[1]);
    pDTOA23vsTOT[1] = new TProfile("pDTOA23vsTOT3", "DTOA 23 vs TOT 3;TOT 3;DTOA 23", TOTBins, TOTRange[0], TOTRange[1]);

    hTOACode0vsTOACode1_C0 = new TH2D("hTOACode0vsTOACode1_C0", "TOA Code 0 vs TOA Code 1 C0;TOA Code 1;TOA Code 0", TOACodeBins, TOACodeRange[0], TOACodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
    hTOACode0vsTOACode1_C0->Sumw2();
    hTOACode0vsTOACode2_C0 = new TH2D("hTOACode0vsTOACode2_C0", "TOA Code 0 vs TOA Code 2 C0;TOA Code 2;TOA Code 0", TOACodeBins, TOACodeRange[0], TOACodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
    hTOACode0vsTOACode2_C0->Sumw2();
    hTOACode0vsTOACode3_C0 = new TH2D("hTOACode0vsTOACode3_C0", "TOA Code 0 vs TOA Code 3 C0;TOA Code 3;TOA Code 0", TOACodeBins, TOACodeRange[0], TOACodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
    hTOACode0vsTOACode3_C0->Sumw2();
    hTOACode1vsTOACode2_C0 = new TH2D("hTOACode1vsTOACode2_C0", "TOA Code 1 vs TOA Code 2 C0;TOA Code 2;TOA Code 1", TOACodeBins, TOACodeRange[0], TOACodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
    hTOACode1vsTOACode2_C0->Sumw2();
    hTOACode1vsTOACode3_C0 = new TH2D("hTOACode1vsTOACode3_C0", "TOA Code 1 vs TOA Code 3 C0;TOA Code 3;TOA Code 1", TOACodeBins, TOACodeRange[0], TOACodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
    hTOACode1vsTOACode3_C0->Sumw2();
    hTOACode2vsTOACode3_C0 = new TH2D("hTOACode2vsTOACode3_C0", "TOA Code 2 vs TOA Code 3 C0;TOA Code 3;TOA Code 2", TOACodeBins, TOACodeRange[0], TOACodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
    hTOACode2vsTOACode3_C0->Sumw2();

    hTOACode0vsTOACode1_C1 = new TH2D("hTOACode0vsTOACode1_C1", "TOA Code 0 vs TOA Code 1 C1;TOA Code 1;TOA Code 0", TOACodeBins, TOACodeRange[0], TOACodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
    hTOACode0vsTOACode1_C1->Sumw2();
    hTOACode0vsTOACode2_C1 = new TH2D("hTOACode0vsTOACode2_C1", "TOA Code 0 vs TOA Code 2 C1;TOA Code 2;TOA Code 0", TOACodeBins, TOACodeRange[0], TOACodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
    hTOACode0vsTOACode2_C1->Sumw2();
    hTOACode0vsTOACode3_C1 = new TH2D("hTOACode0vsTOACode3_C1", "TOA Code 0 vs TOA Code 3 C1;TOA Code 3;TOA Code 0", TOACodeBins, TOACodeRange[0], TOACodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
    hTOACode0vsTOACode3_C1->Sumw2();
    hTOACode1vsTOACode2_C1 = new TH2D("hTOACode1vsTOACode2_C1", "TOA Code 1 vs TOA Code 2 C1;TOA Code 2;TOA Code 1", TOACodeBins, TOACodeRange[0], TOACodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
    hTOACode1vsTOACode2_C1->Sumw2();
    hTOACode1vsTOACode3_C1 = new TH2D("hTOACode1vsTOACode3_C1", "TOA Code 1 vs TOA Code 3 C1;TOA Code 3;TOA Code 1", TOACodeBins, TOACodeRange[0], TOACodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
    hTOACode1vsTOACode3_C1->Sumw2();
    hTOACode2vsTOACode3_C1 = new TH2D("hTOACode2vsTOACode3_C1", "TOA Code 2 vs TOA Code 3 C1;TOA Code 3;TOA Code 2", TOACodeBins, TOACodeRange[0], TOACodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
    hTOACode2vsTOACode3_C1->Sumw2();

    hTOACode0vsTOACode1_C2 = new TH2D("hTOACode0vsTOACode1_C2", "TOA Code 0 vs TOA Code 1 C2;TOA Code 1;TOA Code 0", TOACodeBins, TOACodeRange[0], TOACodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
    hTOACode0vsTOACode1_C2->Sumw2();
    hTOACode0vsTOACode2_C2 = new TH2D("hTOACode0vsTOACode2_C2", "TOA Code 0 vs TOA Code 2 C2;TOA Code 2;TOA Code 0", TOACodeBins, TOACodeRange[0], TOACodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
    hTOACode0vsTOACode2_C2->Sumw2();
    hTOACode0vsTOACode3_C2 = new TH2D("hTOACode0vsTOACode3_C2", "TOA Code 0 vs TOA Code 3 C2;TOA Code 3;TOA Code 0", TOACodeBins, TOACodeRange[0], TOACodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
    hTOACode0vsTOACode3_C2->Sumw2();
    hTOACode1vsTOACode2_C2 = new TH2D("hTOACode1vsTOACode2_C2", "TOA Code 1 vs TOA Code 2 C2;TOA Code 2;TOA Code 1", TOACodeBins, TOACodeRange[0], TOACodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
    hTOACode1vsTOACode2_C2->Sumw2();
    hTOACode1vsTOACode3_C2 = new TH2D("hTOACode1vsTOACode3_C2", "TOA Code 1 vs TOA Code 3 C2;TOA Code 3;TOA Code 1", TOACodeBins, TOACodeRange[0], TOACodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
    hTOACode1vsTOACode3_C2->Sumw2();
    hTOACode2vsTOACode3_C2 = new TH2D("hTOACode2vsTOACode3_C2", "TOA Code 2 vs TOA Code 3 C2;TOA Code 3;TOA Code 2", TOACodeBins, TOACodeRange[0], TOACodeRange[1], TOACodeBins, TOACodeRange[0], TOACodeRange[1]);
    hTOACode2vsTOACode3_C2->Sumw2();

    hTOA0vsTOA1_C0 = new TH2D("hTOA0vsTOA1_C0", "TOA 0 vs TOA 1 C0;TOA 1;TOA 0", TOABins, TOARange[0], TOARange[1], TOABins, TOARange[0], TOARange[1]);
    hTOA0vsTOA1_C0->Sumw2();
    hTOA0vsTOA2_C0 = new TH2D("hTOA0vsTOA2_C0", "TOA 0 vs TOA 2 C0;TOA 2;TOA 0", TOABins, TOARange[0], TOARange[1], TOABins, TOARange[0], TOARange[1]);
    hTOA0vsTOA2_C0->Sumw2();
    hTOA0vsTOA3_C0 = new TH2D("hTOA0vsTOA3_C0", "TOA 0 vs TOA 3 C0;TOA 3;TOA 0", TOABins, TOARange[0], TOARange[1], TOABins, TOARange[0], TOARange[1]);
    hTOA0vsTOA3_C0->Sumw2();
    hTOA1vsTOA2_C0 = new TH2D("hTOA1vsTOA2_C0", "TOA 1 vs TOA 2 C0;TOA 2;TOA 1", TOABins, TOARange[0], TOARange[1], TOABins, TOARange[0], TOARange[1]);
    hTOA1vsTOA2_C0->Sumw2();
    hTOA1vsTOA3_C0 = new TH2D("hTOA1vsTOA3_C0", "TOA 1 vs TOA 3 C0;TOA 3;TOA 1", TOABins, TOARange[0], TOARange[1], TOABins, TOARange[0], TOARange[1]);
    hTOA1vsTOA3_C0->Sumw2();
    hTOA2vsTOA3_C0 = new TH2D("hTOA2vsTOA3_C0", "TOA 2 vs TOA 3 C0;TOA 3;TOA 2", TOABins, TOARange[0], TOARange[1], TOABins, TOARange[0], TOARange[1]);
    hTOA2vsTOA3_C0->Sumw2();

    hTOA0vsTOA1_C1 = new TH2D("hTOA0vsTOA1_C1", "TOA 0 vs TOA 1 C1;TOA 1;TOA 0", TOABins, TOARange[0], TOARange[1], TOABins, TOARange[0], TOARange[1]);
    hTOA0vsTOA1_C1->Sumw2();
    hTOA0vsTOA2_C1 = new TH2D("hTOA0vsTOA2_C1", "TOA 0 vs TOA 2 C1;TOA 2;TOA 0", TOABins, TOARange[0], TOARange[1], TOABins, TOARange[0], TOARange[1]);
    hTOA0vsTOA2_C1->Sumw2();
    hTOA0vsTOA3_C1 = new TH2D("hTOA0vsTOA3_C1", "TOA 0 vs TOA 3 C1;TOA 3;TOA 0", TOABins, TOARange[0], TOARange[1], TOABins, TOARange[0], TOARange[1]);
    hTOA0vsTOA3_C1->Sumw2();
    hTOA1vsTOA2_C1 = new TH2D("hTOA1vsTOA2_C1", "TOA 1 vs TOA 2 C1;TOA 2;TOA 1", TOABins, TOARange[0], TOARange[1], TOABins, TOARange[0], TOARange[1]);
    hTOA1vsTOA2_C1->Sumw2();
    hTOA1vsTOA3_C1 = new TH2D("hTOA1vsTOA3_C1", "TOA 1 vs TOA 3 C1;TOA 3;TOA 1", TOABins, TOARange[0], TOARange[1], TOABins, TOARange[0], TOARange[1]);
    hTOA1vsTOA3_C1->Sumw2();
    hTOA2vsTOA3_C1 = new TH2D("hTOA2vsTOA3_C1", "TOA 2 vs TOA 3 C1;TOA 3;TOA 2", TOABins, TOARange[0], TOARange[1], TOABins, TOARange[0], TOARange[1]);
    hTOA2vsTOA3_C1->Sumw2();

    hTOA0vsTOA1_C2 = new TH2D("hTOA0vsTOA1_C2", "TOA 0 vs TOA 1 C2;TOA 1;TOA 0", TOABins, TOARange[0], TOARange[1], TOABins, TOARange[0], TOARange[1]);
    hTOA0vsTOA1_C2->Sumw2();
    hTOA0vsTOA2_C2 = new TH2D("hTOA0vsTOA2_C2", "TOA 0 vs TOA 2 C2;TOA 2;TOA 0", TOABins, TOARange[0], TOARange[1], TOABins, TOARange[0], TOARange[1]);
    hTOA0vsTOA2_C2->Sumw2();
    hTOA0vsTOA3_C2 = new TH2D("hTOA0vsTOA3_C2", "TOA 0 vs TOA 3 C2;TOA 3;TOA 0", TOABins, TOARange[0], TOARange[1], TOABins, TOARange[0], TOARange[1]);
    hTOA0vsTOA3_C2->Sumw2();
    hTOA1vsTOA2_C2 = new TH2D("hTOA1vsTOA2_C2", "TOA 1 vs TOA 2 C2;TOA 2;TOA 1", TOABins, TOARange[0], TOARange[1], TOABins, TOARange[0], TOARange[1]);
    hTOA1vsTOA2_C2->Sumw2();
    hTOA1vsTOA3_C2 = new TH2D("hTOA1vsTOA3_C2", "TOA 1 vs TOA 3 C2;TOA 3;TOA 1", TOABins, TOARange[0], TOARange[1], TOABins, TOARange[0], TOARange[1]);
    hTOA1vsTOA3_C2->Sumw2();
    hTOA2vsTOA3_C2 = new TH2D("hTOA2vsTOA3_C2", "TOA 2 vs TOA 3 C2;TOA 3;TOA 2", TOABins, TOARange[0], TOARange[1], TOABins, TOARange[0], TOARange[1]);
    hTOA2vsTOA3_C2->Sumw2();

    hDTOA01CodevsTOTCode[0] = new TH2D("hDTOA01CodevsTOTCode0", "DTOA 01 Code vs TOT Code 0;TOT Code 0;DTOA 01 Code", TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1], DTOACodeBins, DTOACodeRange[0], DTOACodeRange[1]);
    hDTOA01CodevsTOTCode[0]->Sumw2();
    hDTOA01CodevsTOTCode[1] = new TH2D("hDTOA01CodevsTOTCode1", "DTOA 01 Code vs TOT Code 1;TOT Code 1;DTOA 01 Code", TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1], DTOACodeBins, DTOACodeRange[0], DTOACodeRange[1]);
    hDTOA01CodevsTOTCode[1]->Sumw2();

    hDTOA02CodevsTOTCode[0] = new TH2D("hDTOA02CodevsTOTCode0", "DTOA 02 Code vs TOT Code 0;TOT Code 0;DTOA 02 Code", TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1], DTOACodeBins, DTOACodeRange[0], DTOACodeRange[1]);
    hDTOA02CodevsTOTCode[0]->Sumw2();
    hDTOA02CodevsTOTCode[1] = new TH2D("hDTOA02CodevsTOTCode2", "DTOA 02 Code vs TOT Code 2;TOT Code 2;DTOA 02 Code", TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1], DTOACodeBins, DTOACodeRange[0], DTOACodeRange[1]);
    hDTOA02CodevsTOTCode[1]->Sumw2();

    hDTOA03CodevsTOTCode[0] = new TH2D("hDTOA03CodevsTOTCode0", "DTOA 03 Code vs TOT Code 0;TOT Code 0;DTOA 03 Code", TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1], DTOACodeBins, DTOACodeRange[0], DTOACodeRange[1]);
    hDTOA03CodevsTOTCode[0]->Sumw2();
    hDTOA03CodevsTOTCode[1] = new TH2D("hDTOA03CodevsTOTCode3", "DTOA 03 Code vs TOT Code 3;TOT Code 3;DTOA 03 Code", TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1], DTOACodeBins, DTOACodeRange[0], DTOACodeRange[1]);
    hDTOA03CodevsTOTCode[1]->Sumw2();

    hDTOA12CodevsTOTCode[0] = new TH2D("hDTOA12CodevsTOTCode1", "DTOA 12 Code vs TOT Code 1;TOT Code 1;DTOA 12 Code", TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1], DTOACodeBins, DTOACodeRange[0], DTOACodeRange[1]);
    hDTOA12CodevsTOTCode[0]->Sumw2();
    hDTOA12CodevsTOTCode[1] = new TH2D("hDTOA12CodevsTOTCode2", "DTOA 12 Code vs TOT Code 2;TOT Code 2;DTOA 12 Code", TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1], DTOACodeBins, DTOACodeRange[0], DTOACodeRange[1]);
    hDTOA12CodevsTOTCode[1]->Sumw2();

    hDTOA13CodevsTOTCode[0] = new TH2D("hDTOA13CodevsTOTCode1", "DTOA 13 Code vs TOT Code 1;TOT Code 1;DTOA 13 Code", TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1], DTOACodeBins, DTOACodeRange[0], DTOACodeRange[1]);
    hDTOA13CodevsTOTCode[0]->Sumw2();
    hDTOA13CodevsTOTCode[1] = new TH2D("hDTOA13CodevsTOTCode3", "DTOA 13 Code vs TOT Code 3;TOT Code 3;DTOA 13 Code", TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1], DTOACodeBins, DTOACodeRange[0], DTOACodeRange[1]);
    hDTOA13CodevsTOTCode[1]->Sumw2();

    hDTOA23CodevsTOTCode[0] = new TH2D("hDTOA23CodevsTOTCode2", "DTOA 23 Code vs TOT Code 2;TOT Code 2;DTOA 23 Code", TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1], DTOACodeBins, DTOACodeRange[0], DTOACodeRange[1]);
    hDTOA23CodevsTOTCode[0]->Sumw2();
    hDTOA23CodevsTOTCode[1] = new TH2D("hDTOA23CodevsTOTCode3", "DTOA 23 Code vs TOT Code 3;TOT Code 3;DTOA 23 Code", TOTCodeBins, TOTCodeRange[0], TOTCodeRange[1], DTOACodeBins, DTOACodeRange[0], DTOACodeRange[1]);
    hDTOA23CodevsTOTCode[1]->Sumw2();

    hDTOA01vsTOT[0] = new TH2D("hDTOA01vsTOT0", "DTOA 01 vs TOT 0;TOT 0;DTOA 01", TOTBins, TOTRange[0], TOTRange[1], DTOABins, DTOARange[0], DTOARange[1]);
    hDTOA01vsTOT[0]->Sumw2();
    hDTOA01vsTOT[1] = new TH2D("hDTOA01vsTOT1", "DTOA 01 vs TOT 1;TOT 1;DTOA 01", TOTBins, TOTRange[0], TOTRange[1], DTOABins, DTOARange[0], DTOARange[1]);
    hDTOA01vsTOT[1]->Sumw2();

    hDTOA02vsTOT[0] = new TH2D("hDTOA02vsTOT0", "DTOA 02 vs TOT 0;TOT 0;DTOA 02", TOTBins, TOTRange[0], TOTRange[1], DTOABins, DTOARange[0], DTOARange[1]);
    hDTOA02vsTOT[0]->Sumw2();
    hDTOA02vsTOT[1] = new TH2D("hDTOA02vsTOT2", "DTOA 02 vs TOT 2;TOT 2;DTOA 02", TOTBins, TOTRange[0], TOTRange[1], DTOABins, DTOARange[0], DTOARange[1]);
    hDTOA02vsTOT[1]->Sumw2();

    hDTOA03vsTOT[0] = new TH2D("hDTOA03vsTOT0", "DTOA 03 vs TOT 0;TOT 0;DTOA 03", TOTBins, TOTRange[0], TOTRange[1], DTOABins, DTOARange[0], DTOARange[1]);
    hDTOA03vsTOT[0]->Sumw2();
    hDTOA03vsTOT[1] = new TH2D("hDTOA03vsTOT3", "DTOA 03 vs TOT 3;TOT 3;DTOA 03", TOTBins, TOTRange[0], TOTRange[1], DTOABins, DTOARange[0], DTOARange[1]);
    hDTOA03vsTOT[1]->Sumw2();

    hDTOA12vsTOT[0] = new TH2D("hDTOA12vsTOT1", "DTOA 12 vs TOT 1;TOT 1;DTOA 12", TOTBins, TOTRange[0], TOTRange[1], DTOABins, DTOARange[0], DTOARange[1]);
    hDTOA12vsTOT[0]->Sumw2();
    hDTOA12vsTOT[1] = new TH2D("hDTOA12vsTOT2", "DTOA 12 vs TOT 2;TOT 2;DTOA 12", TOTBins, TOTRange[0], TOTRange[1], DTOABins, DTOARange[0], DTOARange[1]);
    hDTOA12vsTOT[1]->Sumw2();

    hDTOA13vsTOT[0] = new TH2D("hDTOA13vsTOT1", "DTOA 13 vs TOT 1;TOT 1;DTOA 13", TOTBins, TOTRange[0], TOTRange[1], DTOABins, DTOARange[0], DTOARange[1]);
    hDTOA13vsTOT[0]->Sumw2();
    hDTOA13vsTOT[1] = new TH2D("hDTOA13vsTOT3", "DTOA 13 vs TOT 3;TOT 3;DTOA 13", TOTBins, TOTRange[0], TOTRange[1], DTOABins, DTOARange[0], DTOARange[1]);
    hDTOA13vsTOT[1]->Sumw2();

    hDTOA23vsTOT[0] = new TH2D("hDTOA23vsTOT2", "DTOA 23 vs TOT 2;TOT 2;DTOA 23", TOTBins, TOTRange[0], TOTRange[1], DTOABins, DTOARange[0], DTOARange[1]);
    hDTOA23vsTOT[0]->Sumw2();
    hDTOA23vsTOT[1] = new TH2D("hDTOA23vsTOT3", "DTOA 23 vs TOT 3;TOT 3;DTOA 23", TOTBins, TOTRange[0], TOTRange[1], DTOABins, DTOARange[0], DTOARange[1]);
    hDTOA23vsTOT[1]->Sumw2();
}

void HistoManagerETROC4Boards::projection()
{
    hTOACode0_C0 = hTOACode0vsTOTCode0_C0->ProjectionY("hTOACode0_C0");
    hTOACode0_C1 = hTOACode0vsTOTCode0_C1->ProjectionY("hTOACode0_C1");
    hTOACode0_C2 = hTOACode0vsTOTCode0_C2->ProjectionY("hTOACode0_C2");

    hTOACode1_C0 = hTOACode1vsTOTCode1_C0->ProjectionY("hTOACode1_C0");
    hTOACode1_C1 = hTOACode1vsTOTCode1_C1->ProjectionY("hTOACode1_C1");
    hTOACode1_C2 = hTOACode1vsTOTCode1_C2->ProjectionY("hTOACode1_C2");

    hTOACode2_C0 = hTOACode2vsTOTCode2_C0->ProjectionY("hTOACode2_C0");
    hTOACode2_C1 = hTOACode2vsTOTCode2_C1->ProjectionY("hTOACode2_C1");
    hTOACode2_C2 = hTOACode2vsTOTCode2_C2->ProjectionY("hTOACode2_C2");

    hTOACode3_C0 = hTOACode3vsTOTCode3_C0->ProjectionY("hTOACode3_C0");
    hTOACode3_C1 = hTOACode3vsTOTCode3_C1->ProjectionY("hTOACode3_C1");
    hTOACode3_C2 = hTOACode3vsTOTCode3_C2->ProjectionY("hTOACode3_C2");

    hTOTCode0_C0 = hTOTCode0vsCALCode0_C0->ProjectionY("hTOTCode0_C0");
    hTOTCode0_C1 = hTOTCode0vsCALCode0_C1->ProjectionY("hTOTCode0_C1");
    hTOTCode0_C2 = hTOTCode0vsCALCode0_C2->ProjectionY("hTOTCode0_C2");

    hTOTCode1_C0 = hTOTCode1vsCALCode1_C0->ProjectionY("hTOTCode1_C0");
    hTOTCode1_C1 = hTOTCode1vsCALCode1_C1->ProjectionY("hTOTCode1_C1");
    hTOTCode1_C2 = hTOTCode1vsCALCode1_C2->ProjectionY("hTOTCode1_C2");

    hTOTCode2_C0 = hTOTCode2vsCALCode2_C0->ProjectionY("hTOTCode2_C0");
    hTOTCode2_C1 = hTOTCode2vsCALCode2_C1->ProjectionY("hTOTCode2_C1");
    hTOTCode2_C2 = hTOTCode2vsCALCode2_C2->ProjectionY("hTOTCode2_C2");

    hTOTCode3_C0 = hTOTCode3vsCALCode3_C0->ProjectionY("hTOTCode3_C0");
    hTOTCode3_C1 = hTOTCode3vsCALCode3_C1->ProjectionY("hTOTCode3_C1");
    hTOTCode3_C2 = hTOTCode3vsCALCode3_C2->ProjectionY("hTOTCode3_C2");

    hCALCode0_C0 = hTOTCode0vsCALCode0_C0->ProjectionX("hCALCode0_C0");
    hCALCode0_C1 = hTOTCode0vsCALCode0_C1->ProjectionX("hCALCode0_C1");
    hCALCode0_C2 = hTOTCode0vsCALCode0_C2->ProjectionX("hCALCode0_C2");

    hCALCode1_C0 = hTOTCode1vsCALCode1_C0->ProjectionX("hCALCode1_C0");
    hCALCode1_C1 = hTOTCode1vsCALCode1_C1->ProjectionX("hCALCode1_C1");
    hCALCode1_C2 = hTOTCode1vsCALCode1_C2->ProjectionX("hCALCode1_C2");

    hCALCode2_C0 = hTOTCode2vsCALCode2_C0->ProjectionX("hCALCode2_C0");
    hCALCode2_C1 = hTOTCode2vsCALCode2_C1->ProjectionX("hCALCode2_C1");
    hCALCode2_C2 = hTOTCode2vsCALCode2_C2->ProjectionX("hCALCode2_C2");

    hCALCode3_C0 = hTOTCode3vsCALCode3_C0->ProjectionX("hCALCode3_C0");
    hCALCode3_C1 = hTOTCode3vsCALCode3_C1->ProjectionX("hCALCode3_C1");
    hCALCode3_C2 = hTOTCode3vsCALCode3_C2->ProjectionX("hCALCode3_C2");

    hTOA0_C0 = hTOA0vsTOT0_C0->ProjectionY("hTOA0_C0");
    hTOA0_C1 = hTOA0vsTOT0_C1->ProjectionY("hTOA0_C1");
    hTOA0_C2 = hTOA0vsTOT0_C2->ProjectionY("hTOA0_C2");

    hTOA1_C0 = hTOA1vsTOT1_C0->ProjectionY("hTOA1_C0");
    hTOA1_C1 = hTOA1vsTOT1_C1->ProjectionY("hTOA1_C1");
    hTOA1_C2 = hTOA1vsTOT1_C2->ProjectionY("hTOA1_C2");

    hTOA2_C0 = hTOA2vsTOT2_C0->ProjectionY("hTOA2_C0");
    hTOA2_C1 = hTOA2vsTOT2_C1->ProjectionY("hTOA2_C1");
    hTOA2_C2 = hTOA2vsTOT2_C2->ProjectionY("hTOA2_C2");

    hTOA3_C0 = hTOA3vsTOT3_C0->ProjectionY("hTOA3_C0");
    hTOA3_C1 = hTOA3vsTOT3_C1->ProjectionY("hTOA3_C1");
    hTOA3_C2 = hTOA3vsTOT3_C2->ProjectionY("hTOA3_C2");

    hTOT0_C0 = hTOT0vsCALCode0_C0->ProjectionY("hTOT0_C0");
    hTOT0_C1 = hTOT0vsCALCode0_C1->ProjectionY("hTOT0_C1");
    hTOT0_C2 = hTOT0vsCALCode0_C2->ProjectionY("hTOT0_C2");

    hTOT1_C0 = hTOT1vsCALCode1_C0->ProjectionY("hTOT1_C0");
    hTOT1_C1 = hTOT1vsCALCode1_C1->ProjectionY("hTOT1_C1");
    hTOT1_C2 = hTOT1vsCALCode1_C2->ProjectionY("hTOT1_C2");

    hTOT2_C0 = hTOT2vsCALCode2_C0->ProjectionY("hTOT2_C0");
    hTOT2_C1 = hTOT2vsCALCode2_C1->ProjectionY("hTOT2_C1");
    hTOT2_C2 = hTOT2vsCALCode2_C2->ProjectionY("hTOT2_C2");

    hTOT3_C0 = hTOT3vsCALCode3_C0->ProjectionY("hTOT3_C0");
    hTOT3_C1 = hTOT3vsCALCode3_C1->ProjectionY("hTOT3_C1");
    hTOT3_C2 = hTOT3vsCALCode3_C2->ProjectionY("hTOT3_C2");

    hDTOA01Code = hDTOA01CodevsTOTCode[0]->ProjectionY("hDTOA01Code");
    hDTOA02Code = hDTOA02CodevsTOTCode[0]->ProjectionY("hDTOA02Code");
    hDTOA03Code = hDTOA03CodevsTOTCode[0]->ProjectionY("hDTOA03Code");
    hDTOA12Code = hDTOA12CodevsTOTCode[0]->ProjectionY("hDTOA12Code");
    hDTOA13Code = hDTOA13CodevsTOTCode[0]->ProjectionY("hDTOA13Code");
    hDTOA23Code = hDTOA23CodevsTOTCode[0]->ProjectionY("hDTOA23Code");

    hDTOA01 = hDTOA01vsTOT[0]->ProjectionY("hDTOA01");
    hDTOA02 = hDTOA02vsTOT[0]->ProjectionY("hDTOA02");
    hDTOA03 = hDTOA03vsTOT[0]->ProjectionY("hDTOA03");
    hDTOA12 = hDTOA12vsTOT[0]->ProjectionY("hDTOA12");
    hDTOA13 = hDTOA13vsTOT[0]->ProjectionY("hDTOA13");
    hDTOA23 = hDTOA23vsTOT[0]->ProjectionY("hDTOA23");
}

void HistoManagerETROC4Boards::writeOutput()
{

    gDirectory->mkdir("Board0");
    gDirectory->cd("Board0");
    hTOACode0vsTOTCode0_C0->Write();
    hTOTCode0vsCALCode0_C0->Write();
    hTOACode0vsCALCode0_C0->Write();
    hTOACode0_C0->Write();
    hTOTCode0_C0->Write();
    hCALCode0_C0->Write();
    hTOACode0vsTOTCode0_C1->Write();
    hTOTCode0vsCALCode0_C1->Write();
    hTOACode0vsCALCode0_C1->Write();
    hTOACode0_C1->Write();
    hTOTCode0_C1->Write();
    hCALCode0_C1->Write();
    hTOACode0vsTOTCode0_C2->Write();
    hTOTCode0vsCALCode0_C2->Write();
    hTOACode0vsCALCode0_C2->Write();
    hTOACode0_C2->Write();
    hTOTCode0_C2->Write();
    hCALCode0_C2->Write();
    pDTOA01CodevsTOTCode[0]->Write();
    pDTOA02CodevsTOTCode[0]->Write();
    pDTOA03CodevsTOTCode[0]->Write();

    hTOA0vsTOT0_C0->Write();
    hTOA0vsCALCode0_C0->Write();
    hTOT0vsCALCode0_C0->Write();
    hTOA0_C0->Write();
    hTOT0_C0->Write();
    hTOA0vsTOT0_C1->Write();
    hTOA0vsCALCode0_C1->Write();
    hTOT0vsCALCode0_C1->Write();
    hTOA0_C1->Write();
    hTOT0_C1->Write();
    hTOA0vsTOT0_C2->Write();
    hTOA0vsCALCode0_C2->Write();
    hTOT0vsCALCode0_C2->Write();
    hTOA0_C2->Write();
    hTOT0_C2->Write();
    pDTOA01vsTOT[0]->Write();
    pDTOA02vsTOT[0]->Write();
    pDTOA03vsTOT[0]->Write();

    gDirectory->cd("../");
    gDirectory->mkdir("Board1");
    gDirectory->cd("Board1");
    hTOACode1vsTOTCode1_C0->Write();
    hTOTCode1vsCALCode1_C0->Write();
    hTOACode1vsCALCode1_C0->Write();
    hTOACode1_C0->Write();
    hTOTCode1_C0->Write();
    hCALCode1_C0->Write();
    hTOACode1vsTOTCode1_C1->Write();
    hTOTCode1vsCALCode1_C1->Write();
    hTOACode1vsCALCode1_C1->Write();
    hTOACode1_C1->Write();
    hTOTCode1_C1->Write();
    hCALCode1_C1->Write();
    hTOACode1vsTOTCode1_C2->Write();
    hTOTCode1vsCALCode1_C2->Write();
    hTOACode1vsCALCode1_C2->Write();
    hTOACode1_C2->Write();
    hTOTCode1_C2->Write();
    hCALCode1_C2->Write();
    pDTOA01CodevsTOTCode[1]->Write();
    pDTOA12CodevsTOTCode[0]->Write();
    pDTOA13CodevsTOTCode[0]->Write();

    hTOA1vsTOT1_C0->Write();
    hTOA1vsCALCode1_C0->Write();
    hTOT1vsCALCode1_C0->Write();
    hTOA1_C0->Write();
    hTOT1_C0->Write();
    hTOA1vsTOT1_C1->Write();
    hTOA1vsCALCode1_C1->Write();
    hTOT1vsCALCode1_C1->Write();
    hTOA1_C1->Write();
    hTOT1_C1->Write();
    hTOA1vsTOT1_C2->Write();
    hTOA1vsCALCode1_C2->Write();
    hTOT1vsCALCode1_C2->Write();
    hTOA1_C2->Write();
    hTOT1_C2->Write();

    pDTOA01vsTOT[1]->Write();
    pDTOA12vsTOT[0]->Write();
    pDTOA13vsTOT[0]->Write();

    gDirectory->cd("../");
    gDirectory->mkdir("Board2");
    gDirectory->cd("Board2");
    hTOACode2vsTOTCode2_C0->Write();
    hTOTCode2vsCALCode2_C0->Write();
    hTOACode2vsCALCode2_C0->Write();
    hTOACode2_C0->Write();
    hTOTCode2_C0->Write();
    hCALCode2_C0->Write();
    hTOACode2vsTOTCode2_C1->Write();
    hTOTCode2vsCALCode2_C1->Write();
    hTOACode2vsCALCode2_C1->Write();
    hTOACode2_C1->Write();
    hTOTCode2_C1->Write();
    hCALCode2_C1->Write();
    hTOACode2vsTOTCode2_C2->Write();
    hTOTCode2vsCALCode2_C2->Write();
    hTOACode2vsCALCode2_C2->Write();
    hTOACode2_C2->Write();
    hTOTCode2_C2->Write();
    hCALCode2_C2->Write();
    pDTOA02CodevsTOTCode[1]->Write();
    pDTOA12CodevsTOTCode[1]->Write();
    pDTOA23CodevsTOTCode[0]->Write();

    hTOA2vsTOT2_C0->Write();
    hTOA2vsCALCode2_C0->Write();
    hTOT2vsCALCode2_C0->Write();
    hTOA2_C0->Write();
    hTOT2_C0->Write();
    hTOA2vsTOT2_C1->Write();
    hTOA2vsCALCode2_C1->Write();
    hTOT2vsCALCode2_C1->Write();
    hTOA2_C1->Write();
    hTOT2_C1->Write();
    hTOA2vsTOT2_C2->Write();
    hTOA2vsCALCode2_C2->Write();
    hTOT2vsCALCode2_C2->Write();
    hTOA2_C2->Write();
    hTOT2_C2->Write();
    pDTOA02vsTOT[1]->Write();
    pDTOA12vsTOT[1]->Write();
    pDTOA23vsTOT[0]->Write();

    gDirectory->cd("../");
    gDirectory->mkdir("Board3");
    gDirectory->cd("Board3");
    hTOACode3vsTOTCode3_C0->Write();
    hTOTCode3vsCALCode3_C0->Write();
    hTOACode3vsCALCode3_C0->Write();
    hTOACode3_C0->Write();
    hTOTCode3_C0->Write();
    hCALCode3_C0->Write();
    hTOACode3vsTOTCode3_C1->Write();
    hTOTCode3vsCALCode3_C1->Write();
    hTOACode3vsCALCode3_C1->Write();
    hTOACode3_C1->Write();
    hTOTCode3_C1->Write();
    hCALCode3_C1->Write();
    hTOACode3vsTOTCode3_C2->Write();
    hTOTCode3vsCALCode3_C2->Write();
    hTOACode3vsCALCode3_C2->Write();
    hTOACode3_C2->Write();
    hTOTCode3_C2->Write();
    hCALCode3_C2->Write();
    pDTOA03CodevsTOTCode[1]->Write();
    pDTOA13CodevsTOTCode[1]->Write();
    pDTOA23CodevsTOTCode[1]->Write();

    hTOA3vsTOT3_C0->Write();
    hTOA3vsCALCode3_C0->Write();
    hTOT3vsCALCode3_C0->Write();
    hTOA3_C0->Write();
    hTOT3_C0->Write();
    hTOA3vsTOT3_C1->Write();
    hTOA3vsCALCode3_C1->Write();
    hTOT3vsCALCode3_C1->Write();
    hTOA3_C1->Write();
    hTOT3_C1->Write();
    hTOA3vsTOT3_C2->Write();
    hTOA3vsCALCode3_C2->Write();
    hTOT3vsCALCode3_C2->Write();
    hTOA3_C2->Write();
    hTOT3_C2->Write();
    pDTOA03vsTOT[1]->Write();
    pDTOA13vsTOT[1]->Write();
    pDTOA23vsTOT[1]->Write();

    gDirectory->cd("../");
    gDirectory->mkdir("TOAvsTOA");
    gDirectory->cd("TOAvsTOA");
    hTOACode0vsTOACode1_C0->Write();
    hTOACode0vsTOACode2_C0->Write();
    hTOACode0vsTOACode3_C0->Write();
    hTOACode1vsTOACode2_C0->Write();
    hTOACode1vsTOACode3_C0->Write();
    hTOACode2vsTOACode3_C0->Write();
    hTOA0vsTOA1_C0->Write();
    hTOA0vsTOA2_C0->Write();
    hTOA0vsTOA3_C0->Write();
    hTOA1vsTOA2_C0->Write();
    hTOA1vsTOA3_C0->Write();
    hTOA2vsTOA3_C0->Write();
    hTOACode0vsTOACode1_C1->Write();
    hTOACode0vsTOACode2_C1->Write();
    hTOACode0vsTOACode3_C1->Write();
    hTOACode1vsTOACode2_C1->Write();
    hTOACode1vsTOACode3_C1->Write();
    hTOACode2vsTOACode3_C1->Write();
    hTOA0vsTOA1_C1->Write();
    hTOA0vsTOA2_C1->Write();
    hTOA0vsTOA3_C1->Write();
    hTOA1vsTOA2_C1->Write();
    hTOA1vsTOA3_C1->Write();
    hTOA2vsTOA3_C1->Write();
    hTOACode0vsTOACode1_C2->Write();
    hTOACode0vsTOACode2_C2->Write();
    hTOACode0vsTOACode3_C2->Write();
    hTOACode1vsTOACode2_C2->Write();
    hTOACode1vsTOACode3_C2->Write();
    hTOACode2vsTOACode3_C2->Write();
    hTOA0vsTOA1_C2->Write();
    hTOA0vsTOA2_C2->Write();
    hTOA0vsTOA3_C2->Write();
    hTOA1vsTOA2_C2->Write();
    hTOA1vsTOA3_C2->Write();
    hTOA2vsTOA3_C2->Write();

    gDirectory->cd("../");
    gDirectory->mkdir("DTOA");
    gDirectory->cd("DTOA");
    for (int i = 0; i < 2; i++)
    {
        hDTOA01CodevsTOTCode[i]->Write();
        hDTOA01vsTOT[i]->Write();
        hDTOA02CodevsTOTCode[i]->Write();
        hDTOA02vsTOT[i]->Write();
        hDTOA03CodevsTOTCode[i]->Write();
        hDTOA03vsTOT[i]->Write();
        hDTOA12CodevsTOTCode[i]->Write();
        hDTOA12vsTOT[i]->Write();
        hDTOA13CodevsTOTCode[i]->Write();
        hDTOA13vsTOT[i]->Write();
        hDTOA23CodevsTOTCode[i]->Write();
        hDTOA23vsTOT[i]->Write();
    }
    hDTOA01Code->Write();
    hDTOA02Code->Write();
    hDTOA03Code->Write();
    hDTOA12Code->Write();
    hDTOA13Code->Write();
    hDTOA23Code->Write();
    hDTOA01->Write();
    hDTOA02->Write();
    hDTOA03->Write();
    hDTOA12->Write();
    hDTOA13->Write();
    hDTOA23->Write();
}
