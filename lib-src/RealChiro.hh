////////////////////////////////////////////////////////////////////////////////
// 
// RealChiro.hh 
//
//    produced: 13/03/98 jr
// last change: 13/03/98 jr
//
////////////////////////////////////////////////////////////////////////////////
#ifndef REALCHIRO_HH
#define REALCHIRO_HH

#include <assert.h>
#include <iostream>


#include "Array.hh"
#ifdef USE_SPARSEINTSET
#include "SparseIntegerSet.hh"
#else
#include "IntegerSet.hh"
#endif
#include "HashMap.hh"

#include "CommandlineOptions.hh"

#include "StairCaseMatrix.hh"
#include "PointConfiguration.hh"
#include "Permutation.hh"

#ifdef USE_SPARSEINTSET
typedef SparseIntegerSet                basis_type;
#else
typedef IntegerSet                      basis_type;
#endif
typedef HashMap<basis_type, int>        chirotope_data;

inline const char int2sign(const int i) {
  switch(i) {
  case  1:	return '+';
  case -1:	return '-';
  default:	return '0';
  }
}

inline const int sign2int(const char c) {
  switch(c) {
  case '+':	return 1;
  case '-':	return -1;
  default:	return 0;
  }
}

class RealChiro : public chirotope_data {
  parameter_type  _no;
  parameter_type  _rank;
public:
  // constructors:
  inline RealChiro();
  inline RealChiro(const RealChiro&);
  inline RealChiro(const parameter_type&, const parameter_type&);
  RealChiro(const PointConfiguration&);
  //assignment:
  inline RealChiro& operator=(const RealChiro& chiro);
  // accessors:
  inline parameter_type no() const;
  inline parameter_type rank() const;  
  // functions:
  const basis_type find_non_deg_basis() const;
  RealChiro dual() const;
  // operators:
  inline const int operator()(const basis_type&) const;
  inline const bool operator==(const RealChiro&) const;
  inline const bool operator!=(const RealChiro&) const;
  // stream output/input:
  std::ostream& print_string(std::ostream&) const;
  std::ostream& print_dualstring(std::ostream&) const;
  std::istream& read_string(std::istream&);
  inline friend std::ostream& operator<<(std::ostream&, const RealChiro& chiro);
  inline friend std::istream& operator>>(std::istream&, RealChiro& chiro);
private:
  // internal algorithms:
  void _recursive_chiro(const StairCaseMatrix&    current,
			const PointConfiguration& points,
			const basis_type&         basis,
			const parameter_type      start,
			const parameter_type      step,
			const bool                already_dependent);
  void _recursive_find_nd_basis(const StairCaseMatrix&    current,
				const PointConfiguration& points,
				const basis_type&         basis,
				const parameter_type      start,
				const parameter_type      step,
				const bool                already_dependent);
};

inline RealChiro::RealChiro() : chirotope_data(), _no(0), _rank(0) {
}
inline RealChiro::RealChiro(const RealChiro& chiro) : 
  chirotope_data(chiro), _no(chiro._no), _rank(chiro._rank) {
}
inline RealChiro::RealChiro(const parameter_type& no,
			    const parameter_type& rank) :
  chirotope_data(), _no(no), _rank(rank) {}

//assignment:
inline RealChiro& RealChiro::operator=(const RealChiro& chiro) {
  if (this == &chiro) {
    return *this;
  }
  chirotope_data::operator=(chiro);
  _no = chiro._no;
  _rank = chiro._rank;
  return *this;
}

// accessors:
inline parameter_type RealChiro::no()   const { return _no; }
inline parameter_type RealChiro::rank() const { return _rank; }

// operators:
inline const int RealChiro::operator()(const basis_type& basis) const {
#ifdef INDEX_CHECK
  if (!(member(basis))) {
    std::cerr << *this << " does not contain " << basis << std::endl;
    exit(1);
  }
#endif
  return *member(basis);
}

inline const bool RealChiro::operator==(const RealChiro& chiro) const {
  return chirotope_data::operator==(chiro);
}

inline const bool RealChiro::operator!=(const RealChiro& chiro) const {
  return !operator==(chiro);
}

// stream output/input:
inline std::ostream& operator<<(std::ostream& ost, const RealChiro& chiro) {
  ost << chiro._no << ',' << chiro._rank << ':' << (chirotope_data&)(chiro);
  return ost;
}

inline std::istream& operator>>(std::istream& ist, RealChiro& chiro) {
  char c;

  ist >> std::ws >> chiro._no >> std::ws >> c >> std::ws >> chiro._rank >> std::ws >> c >> std::ws >> (chirotope_data&)(chiro);
  return ist;
}

#endif

// eof RealChiro.hh
