////////////////////////////////////////////////////////////////////////////////
// 
// Facets.cc
//
//    produced: 13/03/98 jr
// last change: 06/07/98 jr
// 
////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <ctype.h>
#include <string.h>

#include "Facets.hh"

Facets::Facets(const Cocircuits& cocircuits) : 
  facets_data(), _no(cocircuits.no()), _rank(cocircuits.no() - cocircuits.rank()) {
  const IntegerSet groundset(0, cocircuits.no());
  for (Cocircuits::const_iterator iter = cocircuits.begin();
       iter != cocircuits.end();
       ++iter) {
    if (iter->dataptr()->first.is_empty()) {
      insert(groundset - iter->dataptr()->second);
    }
    else if (iter->dataptr()->second.is_empty()) {
      insert(groundset - iter->dataptr()->first);
    }
  }
}

std::ostream& Facets::print_string(std::ostream& ost) {
  ost << _no << ',' << _rank << ':' << std::endl;
  ost << '{' << std::endl;
  for (iterator iter = begin(); iter != end(); ++iter) {
    ost << *iter << '\n';
  }
  ost << '}' << std::endl;
  return ost;
}

std::istream& Facets::read_string(std::istream& ist) {
  char c;

  clear();
  if (!(ist >> std::ws >> _no)) {
#ifdef READ_DEBUG
    std::cerr << "Facets::read_string(std::istream&): "
	 << "number of points not found." << std::endl;
#endif
    ist.clear(std::ios::failbit);
    return ist;
  }
  if (!(ist >> std::ws >> c)) {
#ifdef READ_DEBUG
    std::cerr << "Facets::read_string(std::istream&): "
	 << "separator not found." << std::endl;
#endif
    ist.clear(std::ios::failbit);
    return ist;
  }
  if (!(ist >> std::ws >> _rank)) {
#ifdef READ_DEBUG
    std::cerr << "Facets::read_string(std::istream&): "
	 << "rank not found." << std::endl;
#endif
    ist.clear(std::ios::failbit);
    return ist;
  }
  if (!(ist >> std::ws >> c)) {
#ifdef READ_DEBUG
    std::cerr << "Facets::read_string(std::istream&): "
	 << "separator not found." << std::endl;
#endif
    ist.clear(std::ios::failbit);
    return ist;
  }
  ist >> *this;
  return ist;
}

// eof Facets.cc
