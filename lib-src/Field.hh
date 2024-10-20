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

#endif

// eof Field.hh
