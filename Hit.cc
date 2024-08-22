// ETROC2 headers
#include "Hit.h"

ClassImp(Hit)

    //________________
    Hit::Hit() : TObject(), fBoardNumber{0}, fErrorCode{0},
                 fColumn{0}, fRow{0}, fTotCode{0}, fToaCode{0}, fCalCode{0}
{
    /* empty */
}

//________________
Hit::Hit(const Int_t &b, const Int_t &ec, const Int_t &c,
         const Int_t &r, const Int_t &tot, const Int_t &toa,
         const Int_t &cal)
{
    setBoardNumber(b);
    setErrorCode(ec);
    setColumn(c);
    setRow(r);
    setTotCode(tot);
    setToaCode(toa);
    setCalCode(cal);
}

//________________
Hit::~Hit()
{
    /* empty */
}