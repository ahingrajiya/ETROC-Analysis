/**
 * @file Correction.h
 * @author Abhishek Hingrajiya (abhi.h123@gmail.com)
 * @brief Time walk corrections for the ETROC2
 * @version 0.1
 * @date 2024-09-27
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>
#include "TF1.h"
#include "TProfile.h"
#include "TMath.h"

#ifndef Correction_h
#define Correction_h

using namespace std;

class Correction
{
public:
    /// @brief Default constructor
    Correction();
    /// @brief Destructor
    virtual ~Correction();
    /// @brief Get the time walk correction
    Float_t GetCorrection(const Float_t &tot, const Int_t &board, const string &combination, const Bool_t &isCode);
    /// @brief Initialize all the functions
    void init();
    /// @brief Set the left side
    void setLeftSide(const Bool_t &side) { fisLeft = side; }

private:
    /// @brief Time walk correction functions for Board 0
    TF1 *Correction01_0;
    TF1 *Correction02_0;
    TF1 *Correction03_0;

    TF1 *CodeCorrection01_0;
    TF1 *CodeCorrection02_0;
    TF1 *CodeCorrection03_0;

    /// @brief Time walk correction functions for Board 1
    TF1 *Correction01_1;
    TF1 *Correction12_1;
    TF1 *Correction13_1;

    TF1 *CodeCorrection01_1;
    TF1 *CodeCorrection12_1;
    TF1 *CodeCorrection13_1;

    /// @brief Time walk correction functions for Board 2
    TF1 *Correction02_2;
    TF1 *Correction12_2;
    TF1 *Correction23_2;

    TF1 *CodeCorrection02_2;
    TF1 *CodeCorrection12_2;
    TF1 *CodeCorrection23_2;

    /// @brief Time walk correction functions for Board 3
    TF1 *Correction03_3;
    TF1 *Correction13_3;
    TF1 *Correction23_3;

    TF1 *CodeCorrection03_3;
    TF1 *CodeCorrection13_3;
    TF1 *CodeCorrection23_3;

    Bool_t fisLeft;

    ClassDef(Correction, 1)
};

#endif