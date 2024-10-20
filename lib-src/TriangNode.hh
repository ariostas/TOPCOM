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
public:
  TriangNode();
public:
  // constructors:
  inline TriangNode(const parameter_type, 
		    const parameter_type,
		    const SimplicialComplex&);
  inline TriangNode(const TriangNode&);
  inline TriangNode(const TriangNode&, const Flip&);

  // destructor:
  inline ~TriangNode();

  // assignments:
  inline TriangNode& operator=(const TriangNode&);

  // accessors:
  inline const parameter_type no()                const { return _no; }
  inline const parameter_type rank()              const { return _rank; }

  // modifiers for mutables:
  void mark_flip(const flip_type&);
  // functions:
  bool containment_ok(const Circuit& c) const;
  bool link_ok(const Circuit& c) const;

  // stream output/input:
  inline std::ostream& write(std::ostream& ost) const;
  inline std::istream& read(std::istream& ost);
  friend inline std::ostream& operator<<(std::ostream& ost, const TriangNode& tn);
  friend inline std::istream& operator>>(std::istream& ist, TriangNode& tn);
};

// constructors:
inline TriangNode::TriangNode() : 
  SimplicialComplex(), _no(0), _rank(0) {}

inline TriangNode::TriangNode(const parameter_type no, 
			      const parameter_type rank,
			      const SimplicialComplex& triang) : 
  SimplicialComplex(triang),
  _no(no), _rank(rank) {
}

inline TriangNode::TriangNode(const TriangNode& tn) : 
  SimplicialComplex(tn), 
  _no(tn._no), _rank(tn._rank) {}

inline TriangNode::TriangNode(const TriangNode& tn, const Flip& flip) :
  SimplicialComplex(tn), 
  _no(tn._no), _rank(tn._rank) {
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
  return *this;
}

// stream output/input:
inline std::ostream& TriangNode::write(std::ostream& ost) const {
  ost << '[' << _no << ',' << _rank << ':' << (SimplicialComplex)(*this) << ']';
  return ost;
}

inline std::istream& TriangNode::read(std::istream& ist) {
  char c;

  ist >> c >> _no >> c >> _rank >> c;
  SimplicialComplex::read(ist);
  ist >> c;
  return ist;
}

inline std::ostream& operator<<(std::ostream& ost, const TriangNode& tn) {
  return tn.write(ost);
}

inline std::istream& operator>>(std::istream& ist, TriangNode& tn) {
  return tn.read(ist);
}


#endif

// eof TriangNode.hh
