//////////////////////////////////////////////////////////////////////////
// FineTriang.cc
// produced: 01 Oct 1999 jr
// last change: 01 Oct 1999 jr
/////////////////////////////////////////////////////////////////////////

#include <assert.h>
#include <iostream>

#include "Circuits.hh"

#include "FineTriang.hh"

namespace topcom {

  void FineTriang::_flip_in() {
    LabelSet not_used(LabelSet(0, _chiroptr->no()));
    not_used -= support();
    while (!not_used.empty()) {
      const size_type flip_vertex(*not_used.begin());
      _flip_in(not_used, flip_vertex);
      not_used -= flip_vertex;
    }
  }

  void FineTriang::_flip_in(LabelSet& not_used, const size_type i) {
    // search for all simplices that geometrically contain i:
    for (SimplicialComplex::const_iterator iter1 = begin();
	 iter1 != end();
	 ++iter1) {
      dependent_set_type dependent_set = *iter1;
      assert (!dependent_set.contains(i));
      dependent_set += i;
      const Circuit circuit(*_chiroptr, dependent_set);
      const SimplicialComplex upper = circuit.upper_facets();
      const SimplicialComplex lower = circuit.lower_facets();
      const LabelSet usupport = upper.support();
      const LabelSet lsupport = lower.support();
      if (usupport.contains(i) && !lsupport.contains(i)) {
	if (lower.empty()) {
	  continue;
	}
	// Copy the simplex before calling link() to avoid a dangling reference:
	// link() may grow _index_table[card]._index_data via result.insert(), and
	// when card == fl_card (circuit support size 3), this reallocates the very
	// vector that *lower.begin() refers into, making the reference dangling.
	const Simplex lower_facet(*lower.begin());
	const SimplicialComplex common_link(link(lower_facet));
	*this -= lower.join(common_link);
	*this += upper.join(common_link);
	break;
      }
      if (!usupport.contains(i) && lsupport.contains(i)) {
	if (upper.empty()) {
	  continue;
	}
	// Same dangling reference fix as the upper branch above.
	const Simplex upper_facet(*upper.begin());
	const SimplicialComplex common_link(link(upper_facet));
	*this -= upper.join(common_link);
	*this += lower.join(common_link);
	break;
      }
    }
  }

};

// eof FineTriang.cc
