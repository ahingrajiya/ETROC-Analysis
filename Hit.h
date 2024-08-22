#ifndef Hit_t
#define Hit_t

// ROOT headers
#include <TObject.h>
#include <Rtypes.h>
#include <iostream>
#include <cmath>
using namespace std;

//________________
class Hit : public TObject
{

public:
  /// @brief Default constructor
  Hit();
  /// @brief Parametrized constructor
  Hit(const Int_t &b, const Int_t &ec, const Int_t &c, const Int_t &r, const Int_t &tot, const Int_t &toa, const Int_t &cal);
  /// @brief Destructor
  virtual ~Hit();

  // Setters
  void setBoardNumber(const Int_t &n) { fBoardNumber = (UChar_t)n; }
  void setErrorCode(const Int_t &ec) { fErrorCode = (Char_t)ec; }
  void setColumn(const Int_t &c) { fColumn = (UChar_t)c; }
  void setRow(const Int_t &r) { fRow = (UChar_t)r; }
  void setTotCode(const Int_t &tot) { fTotCode = (UShort_t)tot; }
  void setToaCode(const Int_t &toa) { fToaCode = (UShort_t)toa; }
  void setCalCode(const Int_t &cal) { fCalCode = (UShort_t)cal; }

  // Getters
  Int_t boardNumber() const { return (Int_t)fBoardNumber; }
  Int_t errorCode() const { return (Int_t)fErrorCode; }
  Int_t column() const { return (Int_t)fColumn; }
  Int_t row() const { return (Int_t)fRow; }
  Int_t totcode() const { return (Int_t)fTotCode; }
  Int_t toacode() const { return (Int_t)fToaCode; }
  Int_t calcode() const { return (Int_t)fCalCode; }
  Float_t bins() const { return 3.125 / calcode(); }
  Float_t toa() const { return 12.5 - toacode() * bins(); }
  Float_t tot() { return (2.0 * totcode() - floor(totcode() / 32.0)) * bins(); }

private:
  /// @brief Board number
  UChar_t fBoardNumber;
  /// @brief Error code
  Char_t fErrorCode;
  /// @brief Pixel column number (-1 if disabled)
  Char_t fColumn;
  /// @brief Pixel row number (-1 if disabled)
  Char_t fRow;
  /// @brief Time over threshold
  UShort_t fTotCode;
  /// @brief Time of arrival
  UShort_t fToaCode;
  /// @brief Charge
  UShort_t fCalCode;

  ClassDef(Hit, 1)
};

#endif // #define Hit_t