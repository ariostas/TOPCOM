//////////////////////////////////////////////////////////////////////////
// PlacingTriang.hh
// produced: 06/07/98 jr
// last change: 06/07/98 jr
/////////////////////////////////////////////////////////////////////////
#ifndef PLACINGTRIANG_HH
#define PLACINGTRIANG_HH

#include <assert.h>

#include "HashSet.hh"
#include "SimplicialComplex.hh"

#include "CommandlineOptions.hh"

#include "Permutation.hh"
#include "Chirotope.hh"

class PlacingTriang : public SimplicialComplex {
private:
  const Chirotope* _chiroptr;
public:
  inline PlacingTriang();
  inline PlacingTriang(const PlacingTriang& pt);
  inline PlacingTriang(const Chirotope& chiro);
  inline ~PlacingTriang();
  inline PlacingTriang& operator=(const PlacingTriang& pt);
private:
  void _place();
  void _place(SimplicialComplex& current_facets, 
	      IntegerSet& not_placed, 
	      IntegerSet& placed, 
	      const size_type i);
  const bool _is_visible_from(const IntegerSet placed, 
			      const Simplex& facet, 
			      const size_type i) const;
};

inline PlacingTriang::PlacingTriang() :
  SimplicialComplex(), _chiroptr(0) {}

inline PlacingTriang::PlacingTriang(const PlacingTriang& pt) : 
  SimplicialComplex(pt), _chiroptr(pt._chiroptr) {}

inline PlacingTriang::PlacingTriang(const Chirotope& chiro) : 
  SimplicialComplex(), _chiroptr(&chiro) {
  _place();
}

inline PlacingTriang::~PlacingTriang() {}

inline PlacingTriang& PlacingTriang::operator=(const PlacingTriang& pt) {
  if (this == &pt) return *this;
  SimplicialComplex::operator=(pt);
  _chiroptr = pt._chiroptr;
  return *this;
}

#endif

// eof PlacingTriang.hh
