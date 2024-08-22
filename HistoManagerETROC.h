/**
 * @file HistoManagerETROC.cc
 * @author Abhishek Hingrajiya (abhi.h123@gmail.com)
 * @brief Histogram Manager for ETROC Data Analysis
 * @version 0.1
 * @date 2024-08-20
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef HistoManagerETROC_h
#define HistoManagerETROC_h

// Jet analysis headers
#include "BaseHistoManager.h"

// ROOT headers
#include "TObject.h"
#include "TList.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TProfile.h"
#include "THnSparse.h"
#include "TMath.h"

class HistoManagerETROC : public BaseHistoManager
{
public:
    /// @brief Constructor
    HistoManagerETROC();
    /// @brief Destructor
    virtual ~HistoManagerETROC();

    void init();
    void projection();
    void writeOutput();

    /// Setter
    void setNumberOfBoard(const Int_t &nBoards = 2) { fNBoards = nBoards; }

    /// Getter
    Int_t NumberOfBoards() { return fNBoards; }

    ///@brief Descriptions of Acronyms
    /// TWC = Time walk corrected
    /// TWC0/1 = Time walk corrected for board 0 or 1
    /// C0 = No selections
    /// C1 = TOA selections applied
    /// C2 = TOA, TOT and CAL selctions applied

    /// @brief Difference of row and column hit between boards
    TH2D *hDROWvsDCOL;

    /// @brief TOA Code vs TOA Code Histograms

    TH2D *hTOA_Code1vsTOA_Code0_C0;
    TH2D *hTOA_Code1vsTOA_Code0_C1;
    TH2D *hTOA_Code1vsTOA_Code0_C2;

    TH2D *hTOA_Code1vsTOA_Code0_TWC_C0;
    TH2D *hTOA_Code1vsTOA_Code0_TWC_C1;
    TH2D *hTOA_Code1vsTOA_Code0_TWC_C2;

    /// @brief TOA vs TOA Histogram

    TH2D *hTOA1vsTOA0_C0;
    TH2D *hTOA1vsTOA0_C1;
    TH2D *hTOA1vsTOA0_C2;

    TH2D *hTOA1vsTOA0_TWC_C0;
    TH2D *hTOA1vsTOA0_TWC_C1;
    TH2D *hTOA1vsTOA0_TWC_C2;

    ///@brief TOA Code vs TOT Code Histograms
    TH2D *hTOACodevsTOTCode_C0[2];
    TH2D *hTOACodevsTOTCode_C1[2];
    TH2D *hTOACodevsTOTCode_C2[2];

    TH2D *hTOACode_TWCvsTOTCode_C0[2];
    TH2D *hTOACode_TWCvsTOTCode_C1[2];
    TH2D *hTOACode_TWCvsTOTCode_C2[2];

    ///@brief TOA  vs TOT  Histograms
    TH2D *hTOAvsTOT_C0[2];
    TH2D *hTOAvsTOT_C1[2];
    TH2D *hTOAvsTOT_C2[2];

    TH2D *hTOA_TWCvsTOT_C0[2];
    TH2D *hTOA_TWCvsTOT_C1[2];
    TH2D *hTOA_TWCvsTOT_C2[2];

    ///@brief Delta TOA Code vs TOT Code Histograms
    TH2D *hDTOACodevsTOTCode_C0[2];
    TH2D *hDTOACodevsTOTCode_C1[2];
    TH2D *hDTOACodevsTOTCode_C2[2];

    TH2D *hDTOACode_TWCvsTOTCode_C0[2];
    TH2D *hDTOACode_TWCvsTOTCode_C1[2];
    TH2D *hDTOACode_TWCvsTOTCode_C2[2];

    TH2D *hDTOACode_TWC0vsTOTCode_C0[2];
    TH2D *hDTOACode_TWC0vsTOTCode_C1[2];
    TH2D *hDTOACode_TWC0vsTOTCode_C2[2];

    TH2D *hDTOACode_TWC1vsTOTCode_C0[2];
    TH2D *hDTOACode_TWC1vsTOTCode_C1[2];
    TH2D *hDTOACode_TWC1vsTOTCode_C2[2];

    ///@brief Delta TOA  vs TOT  Histograms
    TH2D *hDTOAvsTOT_C0[2];
    TH2D *hDTOAvsTOT_C1[2];
    TH2D *hDTOAvsTOT_C2[2];

    TH2D *hDTOA_TWCvsTOT_C0[2];
    TH2D *hDTOA_TWCvsTOT_C1[2];
    TH2D *hDTOA_TWCvsTOT_C2[2];

    TH2D *hDTOA_TWC0vsTOT_C0[2];
    TH2D *hDTOA_TWC0vsTOT_C1[2];
    TH2D *hDTOA_TWC0vsTOT_C2[2];

    TH2D *hDTOA_TWC1vsTOT_C0[2];
    TH2D *hDTOA_TWC1vsTOT_C1[2];
    TH2D *hDTOA_TWC1vsTOT_C2[2];

    ///@brief TOA Code vs CAL Code Histograms
    TH2D *hTOACodevsCALCode_C0[2];
    TH2D *hTOACodevsCALCode_C1[2];
    TH2D *hTOACodevsCALCode_C2[2];

    TH2D *hTOACode_TWCvsCALCode_C0[2];
    TH2D *hTOACode_TWCvsCALCode_C1[2];
    TH2D *hTOACode_TWCvsCALCode_C2[2];

    ///@brief TOA  vs CAL  Histograms
    TH2D *hTOAvsCAL_C0[2];
    TH2D *hTOAvsCAL_C1[2];
    TH2D *hTOAvsCAL_C2[2];

    TH2D *hTOA_TWCvsCAL_C0[2];
    TH2D *hTOA_TWCvsCAL_C1[2];
    TH2D *hTOA_TWCvsCAL_C2[2];

    ///@brief TOT Code vs CAL Code Histograms
    TH2D *hTOTCodevsCALCode_C0[2];
    TH2D *hTOTCodevsCALCode_C1[2];
    TH2D *hTOTCodevsCALCode_C2[2];

    ///@brief TOT  vs CAL  Histograms
    TH2D *hTOTvsCAL_C0[2];
    TH2D *hTOTvsCAL_C1[2];
    TH2D *hTOTvsCAL_C2[2];

    ///@brief 1D TOA Code Histograms
    TH1D *hTOACode_C0[2];
    TH1D *hTOACode_C1[2];
    TH1D *hTOACode_C2[2];

    ///@brief 1D TOA Code TWC Histograms
    TH1D *hTOACode_TWC_C0[2];
    TH1D *hTOACode_TWC_C1[2];
    TH1D *hTOACode_TWC_C2[2];

    ///@brief 1D Delta TOA Code Histograms
    TH1D *hDTOACode_C0[2];
    TH1D *hDTOACode_C1[2];
    TH1D *hDTOACode_C2[2];

    TH1D *hDTOACode_TWC_C0[2];
    TH1D *hDTOACode_TWC_C1[2];
    TH1D *hDTOACode_TWC_C2[2];

    TH1D *hDTOACode_TWC0_C0[2];
    TH1D *hDTOACode_TWC0_C1[2];
    TH1D *hDTOACode_TWC0_C2[2];

    TH1D *hDTOACode_TWC1_C0[2];
    TH1D *hDTOACode_TWC1_C1[2];
    TH1D *hDTOACode_TWC1_C2[2];

    ///@brief 1D TOA Histograms
    TH1D *hTOA_C0[2];
    TH1D *hTOA_C1[2];
    TH1D *hTOA_C2[2];

    ///@brief 1D TOA TWC Histograms
    TH1D *hTOA_TWC_C0[2];
    TH1D *hTOA_TWC_C1[2];
    TH1D *hTOA_TWC_C2[2];

    ///@brief 1D Delta TOA Histograms

    TH1D *hDTOA_C0[2];
    TH1D *hDTOA_C1[2];
    TH1D *hDTOA_C2[2];

    TH1D *hDTOA_TWC_C0[2];
    TH1D *hDTOA_TWC_C1[2];
    TH1D *hDTOA_TWC_C2[2];

    TH1D *hDTOA_TWC0_C0[2];
    TH1D *hDTOA_TWC0_C1[2];
    TH1D *hDTOA_TWC0_C2[2];

    TH1D *hDTOA_TWC1_C0[2];
    TH1D *hDTOA_TWC1_C1[2];
    TH1D *hDTOA_TWC1_C2[2];

    ///@brief 1D TOT Code Histograms
    TH1D *hTOTCode_C0[2];
    TH1D *hTOTCode_C1[2];
    TH1D *hTOTCode_C2[2];

    ///@brief 1D TOT Histograms
    TH1D *hTOT_C0[2];
    TH1D *hTOT_C1[2];
    TH1D *hTOT_C2[2];

    ///@brief 1D TOT Histograms
    TH1D *hCAL_C0[2];
    TH1D *hCAL_C1[2];
    TH1D *hCAL_C2[2];

    TProfile *pDTOACodevsTOTCode[2];
    TProfile *pDTOAvsTOT[2];

private:
    ///@brief Number of Boards
    Int_t fNBoards;

    ClassDef(HistoManagerETROC, 0)
};

#endif // #define HistogramManagerETROC_h