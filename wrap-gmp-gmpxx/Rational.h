////////////////////////////////////////////////////////////////////////////////
// 
// Integer.h
//
//    produced: 2009/04/30 jr
// last change: 2009/04/30 jr
// 
////////////////////////////////////////////////////////////////////////////////
#ifndef _RATIONAL_H
#define _RATIONAL_H

#include "gmpxx.h"
#include "Integer.h"

typedef mpq_class Rational;

namespace std_ext {
   template <typename _Key> struct hash;

   template <> struct hash<Rational> {
   public:
      size_t operator() (const Rational& a) const {
	return std_ext::hash<Integer>()(Integer(a.get_num())) ^ std_ext::hash<Integer>()(Integer(a.get_den()));
      }
   };
}

#endif // RATIONAL_H

// Local Variables:
// mode:C++
// End:
