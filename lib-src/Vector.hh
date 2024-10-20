////////////////////////////////////////////////////////////////////////////////
// 
// Vector.hh 
//
//    produced: 21/08/97 jr
// last change: 30/10/97 jr
//
////////////////////////////////////////////////////////////////////////////////
#ifndef VECTOR_HH
#define VECTOR_HH

#include <assert.h>
#include <cmath>

#include "Array.hh"
#include "Field.hh"

#include "CommandlineOptions.hh"

typedef Array<Field> vector_data;

class Vector : public vector_data {
public:
  // constructors:
  inline Vector();
  inline Vector(const Vector&);
  inline Vector(const Field&);
  inline Vector(const size_type, const Field& = ZERO);
  // destructor:
  inline ~Vector();
  // accessors:
  bool is_zero() const;
  // operations in place:
  Vector& add(const Vector&);
  Vector& scale(const Field&);
  Vector& stack(const Vector&);
  // operations out of place:
  friend Field inner_product(const Vector&, const Vector&);
  // boolean expressions:
  friend bool lex_abs_compare(const Vector&, const Vector&, const size_type = 0);
};

// constructors:
inline Vector::Vector() : 
  vector_data() {
}
inline Vector::Vector(const Vector& vector) : 
  vector_data(vector) {
}
inline Vector::Vector(const Field& init_entry) : 
  vector_data(1, init_entry) {
}
inline Vector::Vector(const size_type init_size, const Field& init_entry) :
  vector_data(init_size, init_entry) {
}

// destructor:
inline Vector::~Vector() {}

#endif

// eof Vector.hh