////////////////////////////////////////////////////////////////////////////////
// 
// TriangFlips.hh 
//
//    produced: 27/05/98 jr
// last change: 18/06/98 jr
//
////////////////////////////////////////////////////////////////////////////////
#ifndef TRIANGFLIPS_HH
#define TRIANGFLIPS_HH

#include "Pair.hh"
#include "HashSet.hh"
#include "SimplicialComplex.hh"

#include "CommandlineOptions.hh"

#include "Circuits.hh"
#include "Flip.hh"
#include "MarkedFlips.hh"
#include "TriangNode.hh"
#include "Symmetry.hh"

class TriangFlips {
private:
  parameter_type   _no;
  parameter_type   _rank;
  MarkedFlips      _flips;
public:
  // constructors:
  inline TriangFlips();
  inline TriangFlips(const TriangFlips&);
  inline TriangFlips(const TriangNode&,
		     const SymmetryGroup&,
		     const bool = false);
  inline TriangFlips(const TriangNode&, 
		     const TriangFlips&, 
		     const TriangNode&, 
		     const Flip&, 
		     const SymmetryGroup&,
		     const SymmetryGroup&,
		     const bool = false);
  // destructor:
  inline ~TriangFlips();
  // assignment:
  inline TriangFlips& operator=(const TriangFlips& tn);
  // accessors:
  inline const parameter_type no()        const { return _no; }
  inline const parameter_type rank()      const { return _rank; }
  inline const MarkedFlips&   flips()     const { return _flips; }
  // modifiers:
  inline void mark_flip       (const FlipRep&);
  inline void mark_all_flips  ();
  // internal algorithms:
  void _remove_destroyed_flips(const TriangNode& tn, 
			       const Flip&,
			       const SymmetryGroup&);
  void _add_new_flips         (const TriangNode& tn, 
			       const SimplicialComplex&,
			       const SymmetryGroup&,
			       const SymmetryGroup&, 
			       const bool = false);
  // stream input/output:
  inline friend std::ostream& operator<<(std::ostream&, const TriangFlips&);
};

// constructors:
inline TriangFlips::TriangFlips() : _no(0), _rank(0), _flips() {}
inline TriangFlips::TriangFlips(const TriangFlips& tf) :
  _no(tf._no), _rank(tf._rank), _flips(tf._flips) {}
inline TriangFlips::TriangFlips(const TriangNode& tn, 
				const SymmetryGroup& node_symmetries,
				const bool forbid_vertex_removal) :
  _no(tn.no()), _rank(tn.rank()), _flips() {
  _add_new_flips(tn, tn, SymmetryGroup(tn.no()), node_symmetries, forbid_vertex_removal);
}
inline TriangFlips::TriangFlips(const TriangNode&    tn_before_flip,
				const TriangFlips&   tf_before_flip,
				const TriangNode&    tn_after_flip,
				const Flip&          flip,
				const SymmetryGroup& symmetries,
				const SymmetryGroup& tn_after_symmetries,
				const bool           forbid_vertex_removal) :
  _no(tf_before_flip._no), _rank(tf_before_flip._rank),
  _flips(tf_before_flip._flips) {
  _remove_destroyed_flips(tn_before_flip, flip, symmetries);
  _flips.unmark_all();
  _add_new_flips(tn_after_flip, 
		 flip.second, 
		 symmetries, 
		 tn_after_symmetries, 
		 forbid_vertex_removal);
}

// destructor:
inline TriangFlips::~TriangFlips() {}
// assignment:
inline TriangFlips& TriangFlips::operator=(const TriangFlips& tf) {
  if (this == &tf) {
    return *this;
  }
  _no        = tf._no;
  _rank      = tf._rank;
  _flips     = tf._flips;
  return *this;
}

// modifiers:
inline void TriangFlips::mark_flip(const FlipRep& fliprep) {
  _flips.mark(fliprep);
}
inline void TriangFlips::mark_all_flips() {
  _flips.mark_all();
}

// stream input/output:
inline std::ostream& operator<<(std::ostream& ost, const TriangFlips& tf) {
#ifndef STL_FLIPS
  ost << '[' << tf._no << ',' << tf._rank << ":\n\t" << tf._flips << ']';
#else
#endif
  return ost;
}

#endif

// eof TriangFlips.hh