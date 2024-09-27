/**
 * @file Correction.cc
 * @author Abhishek Hingrajiya (abhi.h123@gmail.com)
 * @brief
 * @version 0.1
 * @date 2024-09-27
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "Correction.h"

ClassImp(Correction)

    Correction::Correction() : Correction01_0{nullptr}, Correction02_0{nullptr}, Correction03_0{nullptr},
                               Correction01_1{nullptr}, Correction12_1{nullptr}, Correction13_1{nullptr},
                               Correction02_2{nullptr}, Correction12_2{nullptr}, Correction23_2{nullptr},
                               Correction03_3{nullptr}, Correction13_3{nullptr}, Correction23_3{nullptr},
                               CodeCorrection01_0{nullptr}, CodeCorrection02_0{nullptr}, CodeCorrection03_0{nullptr},
                               CodeCorrection01_1{nullptr}, CodeCorrection12_1{nullptr}, CodeCorrection13_1{nullptr},
                               CodeCorrection02_2{nullptr}, CodeCorrection12_2{nullptr}, CodeCorrection23_2{nullptr},
                               CodeCorrection03_3{nullptr}, CodeCorrection13_3{nullptr}, CodeCorrection23_3{nullptr}, fisLeft{kFALSE}

{
}

Correction::~Correction()
{
    if (Correction01_0)
        delete Correction01_0;
    if (Correction02_0)
        delete Correction02_0;
    if (Correction03_0)
        delete Correction03_0;
    if (Correction01_1)
        delete Correction01_1;
    if (Correction12_1)
        delete Correction12_1;
    if (Correction13_1)
        delete Correction13_1;
    if (Correction02_2)
        delete Correction02_2;
    if (Correction12_2)
        delete Correction12_2;
    if (Correction23_2)
        delete Correction23_2;
    if (Correction03_3)
        delete Correction03_3;
    if (Correction13_3)
        delete Correction13_3;
    if (Correction23_3)
        delete Correction23_3;
    if (CodeCorrection01_0)
        delete CodeCorrection01_0;
    if (CodeCorrection02_0)
        delete CodeCorrection02_0;
    if (CodeCorrection03_0)
        delete CodeCorrection03_0;
    if (CodeCorrection01_1)
        delete CodeCorrection01_1;
    if (CodeCorrection12_1)
        delete CodeCorrection12_1;
    if (CodeCorrection13_1)
        delete CodeCorrection13_1;
    if (CodeCorrection02_2)
        delete CodeCorrection02_2;
    if (CodeCorrection12_2)
        delete CodeCorrection12_2;
    if (CodeCorrection23_2)
        delete CodeCorrection23_2;
    if (CodeCorrection03_3)
        delete CodeCorrection03_3;
    if (CodeCorrection13_3)
        delete CodeCorrection13_3;
    if (CodeCorrection23_3)
        delete CodeCorrection23_3;
}

void Correction::init()
{
    if (fisLeft)
    {
        Correction01_0 = new TF1("Correction01_0", "pol2", 0.0, 12.0);
        Correction01_0->SetParameters(1.42308e+00, -1.40905e-01, -1.18960e-02);

        Correction02_0 = new TF1("Correction02_0", "pol2", 0.0, 12.0);
        Correction02_0->SetParameters(-7.32205e-01, -4.76048e-02, -2.18056e-02);

        Correction03_0 = new TF1("Correction03_0", "pol2", 0.0, 12.0);
        Correction03_0->SetParameters(-6.12578e-01, -1.45379e-01, -9.78255e-03);

        Correction01_1 = new TF1("Correction01_1", "pol2", 0.0, 12.0);
        Correction01_1->SetParameters(-8.49086e-01, 4.25710e-01, -2.19740e-02);

        Correction12_1 = new TF1("Correction12_1", "pol2", 0.0, 12.0);
        Correction12_1->SetParameters(-9.51812e-01, -2.42979e-01, 3.87838e-03);

        Correction13_1 = new TF1("Correction13_1", "pol2", 0.0, 12.0);
        Correction13_1->SetParameters(-7.55896e-01, -3.49154e-01, 1.38461e-02);

        Correction02_2 = new TF1("Correction02_2", "pol2", 0.0, 12.0);
        Correction02_2->SetParameters(-2.69812e+00, 4.74655e-01, -3.13529e-02);

        Correction12_2 = new TF1("Correction12_2", "pol2", 0.0, 12.0);
        Correction12_2->SetParameters(-3.19315e+00, 4.16924e-01, -2.27392e-02);

        Correction23_2 = new TF1("Correction23_2", "pol2", 0.0, 12.0);
        Correction23_2->SetParameters(1.50127e+00, -5.94480e-01, 4.67459e-02);

        Correction03_3 = new TF1("Correction03_3", "pol2", 0.0, 12.0);
        Correction03_3->SetParameters(-2.60622e+00, 3.48265e-01, -1.04115e-02);

        Correction13_3 = new TF1("Correction13_3", "pol2", 0.0, 12.0);
        Correction13_3->SetParameters(-3.08047e+00, 2.92109e-01, -3.66825e-03);

        Correction23_3 = new TF1("Correction23_3", "pol2", 0.0, 12.0);
        Correction23_3->SetParameters(-1.22676e+00, 3.45055e-01, -1.15216e-02);

        CodeCorrection01_0 = new TF1("CodeCorrection01_0", "pol2", 0.0, 200.0);
        CodeCorrection01_0->SetParameters(-5.12998e+01, 2.42212e-01, 9.50198e-04);

        CodeCorrection02_0 = new TF1("CodeCorrection02_0", "pol2", 0.0, 200.0);
        CodeCorrection02_0->SetParameters(8.05744e+01, -3.52180e-01, 3.15707e-03);

        CodeCorrection03_0 = new TF1("CodeCorrection03_0", "pol2", 0.0, 200.0);
        CodeCorrection03_0->SetParameters(6.25103e+01, 3.34642e-02, 1.68194e-03);

        CodeCorrection01_1 = new TF1("CodeCorrection01_1", "pol2", 0.0, 200.0);
        CodeCorrection01_1->SetParameters(9.31777e+01, -1.17607e+00, 3.11995e-03);

        CodeCorrection12_1 = new TF1("CodeCorrection12_1", "pol2", 0.0, 200.0);
        CodeCorrection12_1->SetParameters(4.13470e+01, 4.58053e-01, -3.43163e-04);

        CodeCorrection13_1 = new TF1("CodeCorrection13_1", "pol2", 0.0, 200.0);
        CodeCorrection13_1->SetParameters(3.25596e+01, 6.78707e-01, -1.08876e-03);

        CodeCorrection02_2 = new TF1("CodeCorrection02_2", "pol3", 0.0, 200.0);
        CodeCorrection02_2->SetParameters(2.66582e+01, 2.91548e+00, -3.29851e-02, 1.05610e-04);

        CodeCorrection12_2 = new TF1("CodeCorrection12_2", "pol2", 0.0, 200.0);
        CodeCorrection12_2->SetParameters(1.70415e+02, -9.35843e-01, 2.06726e-03);

        CodeCorrection23_2 = new TF1("CodeCorrection23_2", "pol2", 0.0, 200.0);
        CodeCorrection23_2->SetParameters(-8.35340e+01, 1.18017e+00, -3.25862e-03);

        CodeCorrection03_3 = new TF1("CodeCorrection03_3", "pol2", 0.0, 200.0);
        CodeCorrection03_3->SetParameters(1.63869e+02, -6.85552e-01, 6.24039e-04);

        CodeCorrection13_3 = new TF1("CodeCorrection13_3", "pol2", 0.0, 200.0);
        CodeCorrection13_3->SetParameters(1.62515e+02, -6.51645e-01, 7.27704e-04);

        CodeCorrection23_3 = new TF1("CodeCorrection23_3", "pol2", 0.0, 200.0);
        CodeCorrection23_3->SetParameters(7.83601e+01, -7.85694e-01, 1.27075e-03);
    }

    else
    {

        Correction01_0 = new TF1("Correction01_0", "pol2", 0.0, 12.0);
        Correction01_0->SetParameters(1.18255e+00, -5.96635e-02, -1.90690e-02);

        Correction02_0 = new TF1("Correction02_0", "pol2", 0.0, 12.0);
        Correction02_0->SetParameters(-5.31767e-01, -2.08768e-01, -1.13497e-03);

        Correction03_0 = new TF1("Correction03_0", "pol2", 0.0, 12.0);
        Correction03_0->SetParameters(-6.61685e-01, 1.22368e-01, -1.25654e-02);

        Correction01_1 = new TF1("Correction01_1", "pol2", 0.0, 12.0);
        Correction01_1->SetParameters(-5.25256e-01, 2.49885e-01, -4.97041e-04);

        Correction12_1 = new TF1("Correction12_1", "pol2", 0.0, 12.0);
        Correction12_1->SetParameters(-1.08998e+00, -1.93879e-01, -4.77691e-03);

        Correction13_1 = new TF1("Correction13_1", "pol2", 0.0, 12.0);
        Correction13_1->SetParameters(-1.12046e+00, -1.53253e-01, -1.11418e-02);

        Correction02_2 = new TF1("Correction02_2", "pol2", 0.0, 12.0);
        Correction02_2->SetParameters(-2.68203e+00, 3.81541e-01, -1.34024e-02);

        Correction12_2 = new TF1("Correction12_2", "pol2", 0.0, 12.0);
        Correction12_2->SetParameters(-3.22107e+00, 3.87875e-01, -1.56696e-02);

        Correction23_2 = new TF1("Correction23_2", "pol2", 0.0, 12.0);
        Correction23_2->SetParameters(1.23577e+00, -3.97744e-01, 1.75959e-02);

        Correction03_3 = new TF1("Correction03_3", "pol2", 0.0, 12.0);
        Correction03_3->SetParameters(-2.65029e+00, 3.52891e-01, -1.14104e-02);

        Correction13_3 = new TF1("Correction13_3", "pol2", 0.0, 12.0);
        Correction13_3->SetParameters(-3.17406e+00, 3.63621e-01, -1.09291e-02);

        Correction23_3 = new TF1("Correction23_3", "pol2", 0.0, 12.0);
        Correction23_3->SetParameters(-1.17182e+00, 3.45055e-01, -1.44385e-02);

        CodeCorrection01_0 = new TF1("CodeCorrection01_0", "pol2", 0.0, 200.0);
        CodeCorrection01_0->SetParameters(-4.24407e+01, 2.85547e-01, 7.11525e-04);

        CodeCorrection02_0 = new TF1("CodeCorrection02_0", "pol2", 0.0, 200.0);
        CodeCorrection02_0->SetParameters(3.75392e+01, 4.79095e-01, -2.04751e-04);

        CodeCorrection03_0 = new TF1("CodeCorrection03_0", "pol2", 0.0, 200.0);
        CodeCorrection03_0->SetParameters(5.06566e+01, 3.46193e-01, 4.46547e-04);

        CodeCorrection01_1 = new TF1("CodeCorrection01_1", "pol2", 0.0, 200.0);
        CodeCorrection01_1->SetParameters(3.95005e+01, -2.71651e-01, -9.09049e-04);

        CodeCorrection12_1 = new TF1("CodeCorrection12_1", "pol2", 0.0, 200.0);
        CodeCorrection12_1->SetParameters(4.55305e+01, 3.92757e-01, 2.28468e-04);

        CodeCorrection13_1 = new TF1("CodeCorrection13_1", "pol2", 0.0, 200.0);
        CodeCorrection13_1->SetParameters(6.41259e+01, 1.31701e-01, 1.60940e-03);

        CodeCorrection02_2 = new TF1("CodeCorrection02_2", "pol2", 0.0, 200.0);
        CodeCorrection02_2->SetParameters(1.54085e+02, -8.42638e-01, 1.56989e-03);

        CodeCorrection12_2 = new TF1("CodeCorrection12_2", "pol2", 0.0, 200.0);
        CodeCorrection12_2->SetParameters(1.48608e+02, -7.35305e-01, 1.03630e-03);

        CodeCorrection23_2 = new TF1("CodeCorrection23_2", "pol2", 0.0, 200.0);
        CodeCorrection23_2->SetParameters(-5.35979e+01, 7.86873e-01, -1.41074e-03);

        CodeCorrection03_3 = new TF1("CodeCorrection03_3", "pol3", 0.0, 200.0);
        CodeCorrection03_3->SetParameters(3.20064e+02, -5.75833e+00, 5.22430e-02, -1.72004e-04);

        CodeCorrection13_3 = new TF1("CodeCorrection13_3", "pol3", 0.0, 200.0);
        CodeCorrection13_3->SetParameters(1.79578e+02, -1.45787e+00, 8.58109e-03, -2.51114e-05);

        CodeCorrection23_3 = new TF1("CodeCorrection23_3", "pol2", 0.0, 200.0);
        CodeCorrection23_3->SetParameters(6.98014e+01, -8.06340e-01, 1.53052e-03);
    }
}

Float_t Correction::GetCorrection(const Float_t &tot, const Int_t &board, const string &combination, const Bool_t &isCode)
{
    if (!isCode)
    {
        if (board == 0)
        {
            if (combination == "01")
            {
                return Correction01_0->Eval(tot);
            }
            else if (combination == "02")
            {
                return Correction02_0->Eval(tot);
            }
            else if (combination == "03")
            {
                return Correction03_0->Eval(tot);
            }
            else
            {
                cout << "[ERROR] Combination not found for Board 0" << endl;
                return 0;
            }
        }
        else if (board == 1)
        {
            if (combination == "01")
            {
                return Correction01_1->Eval(tot);
            }
            else if (combination == "12")
            {
                return Correction12_1->Eval(tot);
            }
            else if (combination == "13")
            {
                return Correction13_1->Eval(tot);
            }
            else
            {
                cout << "[ERROR] Combination not found for Board 1" << endl;
                return 0;
            }
        }
        else if (board == 2)
        {
            if (combination == "02")
            {
                return Correction02_2->Eval(tot);
            }
            else if (combination == "12")
            {
                return Correction12_2->Eval(tot);
            }
            else if (combination == "23")
            {
                return Correction23_2->Eval(tot);
            }
            else
            {
                cout << "[ERROR] Combination not found for Board 2" << endl;
                return 0;
            }
        }
        else if (board == 3)
        {
            if (combination == "03")
            {
                return Correction03_3->Eval(tot);
            }
            else if (combination == "13")
            {
                return Correction13_3->Eval(tot);
            }
            else if (combination == "23")
            {
                return Correction23_3->Eval(tot);
            }
            else
            {
                cout << "[ERROR] Combination not found for Board 3" << endl;
                return 0;
            }
        }
        else
        {
            cout << "[ERROR] Board not found" << endl;
            return 0;
        }
    }
    else if (isCode)
    {
        if (board == 0)
        {
            if (combination == "01")
            {
                return CodeCorrection01_0->Eval(tot);
            }
            else if (combination == "02")
            {
                return CodeCorrection02_0->Eval(tot);
            }
            else if (combination == "03")
            {
                return CodeCorrection03_0->Eval(tot);
            }
            else
            {
                cout << "[ERROR] Combination not found for Board 0 Code" << endl;
                return 0;
            }
        }
        else if (board == 1)
        {
            if (combination == "01")
            {
                return CodeCorrection01_1->Eval(tot);
            }
            else if (combination == "12")
            {
                return CodeCorrection12_1->Eval(tot);
            }
            else if (combination == "13")
            {
                return CodeCorrection13_1->Eval(tot);
            }
            else
            {
                cout << "[ERROR] Combination not found for Board 1 Code" << endl;
                return 0;
            }
        }
        else if (board == 2)
        {
            if (combination == "02")
            {
                return CodeCorrection02_2->Eval(tot);
            }
            else if (combination == "12")
            {
                return CodeCorrection12_2->Eval(tot);
            }
            else if (combination == "23")
            {
                return CodeCorrection23_2->Eval(tot);
            }
            else
            {
                cout << "[ERROR] Combination not found for Board 2 Code" << endl;
                return 0;
            }
        }
        else if (board == 3)
        {
            if (combination == "03")
            {
                return CodeCorrection03_3->Eval(tot);
            }
            else if (combination == "13")
            {
                return CodeCorrection13_3->Eval(tot);
            }
            else if (combination == "23")
            {
                return CodeCorrection23_3->Eval(tot);
            }
            else
            {
                cout << "[ERROR] Combination not found for Board 3 Code" << endl;
                return 0;
            }
        }
        else
        {
            cout << "[ERROR] Board found" << endl;
            return 0;
        }
    }
    else
    {
        cout << "[ERROR] Invalid Input" << endl;
        return 0;
    }
}
