////////////////////////////////////////////////////////////////////////////////
// 
// TriangNode.hh 
//
//    produced: 30/04/98 jr
// last change: 18/06/98 jr
//
////////////////////////////////////////////////////////////////////////////////
#ifndef TRIANGNODE_HH
#define TRIANGNODE_HH

#include "Pair.hh"
#include "HashSet.hh"
#include "IntegerSet.hh"
#include "SimplicialComplex.hh"

#include "CommandlineOptions.hh"

#include "Chirotope.hh"
#include "Symmetry.hh"
#include "Flip.hh"

class TriangNode : public SimplicialComplex {
private:
  parameter_type        _no;
  parameter_type        _rank;
  const Chirotope*      _chiroptr;
private:
  TriangNode();
public:
  // constructors:
  inline TriangNode(const parameter_type, 
		    const parameter_type,
		    const SimplicialComplex&,
		    const Chirotope&);
  inline TriangNode(const TriangNode&);
  inline TriangNode(const TriangNode&, const Flip&);
  // destructor:
  inline ~TriangNode();
  // assignments:
  inline TriangNode& operator=(const TriangNode&);
  // accessors:
  inline const parameter_type no()                const { return _no; }
  inline const parameter_type rank()              const { return _rank; }
  inline const Chirotope*     chiroptr()          const { return _chiroptr; }
  // modifiers for mutables:
  void mark_flip(const flip_type&);
  // functions:
  bool containment_ok(const Circuit& c) const;
  bool link_ok(const Circuit& c) const;
};

// constructors:
inline TriangNode::TriangNode() : 
  SimplicialComplex(), _no(0), _rank(0), _chiroptr(0) {}

inline TriangNode::TriangNode(const parameter_type no, 
			      const parameter_type rank,
			      const SimplicialComplex& triang,
			      const Chirotope& chiro) : 
  SimplicialComplex(triang),
  _no(no), _rank(rank),
  _chiroptr(&chiro) {
}

inline TriangNode::TriangNode(const TriangNode& tn) : 
  SimplicialComplex(tn), 
  _no(tn._no), _rank(tn._rank),
  _chiroptr(tn._chiroptr) {}

inline TriangNode::TriangNode(const TriangNode& tn, const Flip& flip) :
  SimplicialComplex(tn), 
  _no(tn._no), _rank(tn._rank),
  _chiroptr(tn._chiroptr) {
  // unmark flips:
  *this -= flip.first;
  *this += flip.second;
}

// destructor:
inline TriangNode::~TriangNode() {}

// assignment:
inline TriangNode& TriangNode::operator=(const TriangNode& tn) {
  if (this == &tn) {
    return *this;
  }
  SimplicialComplex::operator=(tn);
  _no = tn._no;
  _rank = tn._rank;
  _chiroptr = tn._chiroptr;
  return *this;
}

#endif

// eof TriangNode.hh
