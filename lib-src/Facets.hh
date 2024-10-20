////////////////////////////////////////////////////////////////////////////////
// 
// Facets.hh 
//
//    produced: 12/03/98 jr
// last change: 12/03/98 jr
//
////////////////////////////////////////////////////////////////////////////////
#ifndef FACETS_HH
#define FACETS_HH

#include <assert.h>

#include "SimplicialComplex.hh"

#include "CommandlineOptions.hh"

#include "PointConfiguration.hh"
#include "Chirotope.hh"
#include "Circuits.hh"

typedef IntegerSet                               facet_type;
typedef SimplicialComplex                        facets_data;

class Facets : public facets_data {
private:
  parameter_type _no;
  parameter_type _rank;
public:
  // constructors:
  inline Facets();
  inline Facets(const Facets&);
  Facets(const Cocircuits&);
  // destructor:
  inline ~Facets();
  // accessors:
  inline const parameter_type no() const;
  inline const parameter_type rank() const;
  // stream output/input:
  std::ostream& print_string(std::ostream&);
  std::istream& read_string(std::istream&);
};

// constructors:
inline Facets::Facets() : facets_data(), _no(0), _rank(_rank) {}
inline Facets::Facets(const Facets& facets) : 
  facets_data(facets), _no(facets._no), _rank(facets._rank) {}
// destructor:
inline Facets::~Facets() {}
// accessors:
inline const parameter_type Facets::no()   const { return _no; }
inline const parameter_type Facets::rank() const { return _rank; }


#endif

// eof Facets.hh
