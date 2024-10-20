////////////////////////////////////////////////////////////////////////////////
// 
// Field.hh 
//
//    produced: 21/08/97 jr
// last change: 30/10/97 jr
//
////////////////////////////////////////////////////////////////////////////////
#ifndef FIELD_HH
#define FIELD_HH

// #include <iostream>
//#include <bool.h>

#ifdef DOUBLE_ARITHMETIC
// typedef double FIELD;

// class Field {
// private:
//   double _x;
// public:
//   static const Field EPSILON;
//   static const Field ZERO;
//   static const Field ONE;
//   static const Field MINUSONE;
// public:
//   inline Field()               : _x(0)    {}
//   inline Field(const Field& x) : _x(x._x) {}
//   inline Field(const FIELD& x) : _x(x)    {}
//   inline const bool  is_zero() const {
// #ifdef SUPER_VERBOSE
//     std::cerr << "zero test for " << _x << " gives " << ((_x < EPSILON._x) && (_x > -EPSILON._x)) << std::endl;
// #endif
//     return ((_x < EPSILON._x) && (_x > -EPSILON._x));
//   }
//   inline const bool  is_one()  const { return (_x < ONE._x + EPSILON._x && _x > ONE._x - EPSILON._x); }
//   inline friend int  sign(const Field& x) {
//     if (x._x < -EPSILON._x) return -1;
//     else if (x._x > EPSILON._x) return 1;
//     else return 0;
//   }
//   inline friend Field abs(const Field& x) {
//     if (x._x < -EPSILON._x) return -x;
//     else if (x._x > EPSILON._x) return x;
//     else return ZERO;
//   }
//   inline const Field operator-() const { if (is_zero()) return ZERO; else return Field(-_x); }
//   inline friend bool operator==(const Field& x1, const Field& x2) { return (x1 - x2).is_zero(); }
//   inline friend bool operator!=(const Field& x1, const Field& x2) { return !(x1 == x2); }
//   inline friend bool operator<(const Field& x1, const Field& x2)  { return (x2._x - x1._x > EPSILON._x); }
//   inline friend bool operator>(const Field& x1, const Field& x2)  { return (x1._x - x2._x > EPSILON._x); }
//   inline Field operator+=(const Field& x) { return Field(_x += x._x); }
//   inline Field operator-=(const Field& x) { return Field(_x -= x._x); }
//   inline Field operator*=(const Field& x) { return Field(_x *= x._x); }
//   inline Field operator/=(const Field& x) { return Field(_x /= x._x); }
//   inline friend Field operator+(const Field& x1, const Field& x2) { return Field(x1._x + x2._x); }
//   inline friend Field operator-(const Field& x1, const Field& x2) { return Field(x1._x - x2._x); }
//   inline friend Field operator*(const Field& x1, const Field& x2) { return Field(x1._x * x2._x); }
//   inline friend Field operator/(const Field& x1, const Field& x2) { return Field(x1._x / x2._x); }
//   inline friend std::ostream& operator<<(std::ostream& ost, const Field& x) { return ost << x._x; }
//   inline friend std::istream& operator>>(std::istream& ist, Field& x) { return ist >> x._x; }
// };
#else

#include <Rational.h>
typedef Rational Field;

static const Field ZERO     = Field(0);
static const Field ONE      = Field(1);
static const Field MINUSONE = Field(-1);

inline const Field sign(const Field& f) { 
  if (f == 0) { 
    return ZERO; 
  }
  else if (f > ZERO) {
    return ONE;
  }
  else {
    return MINUSONE;
  }
}

// class Field : public FIELD {
// public:
//   static const Field ZERO;
//   static const Field ONE;
//   static const Field MINUSONE;
// public:
//   inline Field() : FIELD() {}
//   inline Field(const Field& x) : FIELD(x) {
//     std::cerr << "WARNING: superfluous constructor call" << std::endl;
//   }
//   inline Field(const FIELD& x) : FIELD(x) {
//     std::cerr << "WARNING: superfluous constructor call" << std::endl;
//   }
//   inline Field(const int x)    : FIELD(x) {}
//   inline const bool is_zero() const { return (*this == ZERO); }
//   inline const bool is_one()  const { return (*this == ONE); }
//   inline friend std::istream& operator>>(std::istream& ist, Field& x) {
//     FIELD y;
//     if (ist >> y) {
//       x = Field(y);
//     }
//     return ist;
//   }
//   inline friend std::ostream& operator<<(std::ostream& ost, const Field& x) {
//     return (ost << (FIELD)x);
//   }
// };
#endif

#endif

// eof Field.hh
