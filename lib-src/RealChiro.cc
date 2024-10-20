////////////////////////////////////////////////////////////////////////////////
// 
// RealChiro.cc
//
//    produced: 13 Mar 1998 jr
// last change: 30 Jun 2000 jr
// 
////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <ctype.h>
#include <string.h>
#include <assert.h>

#include "RealChiro.hh"

RealChiro::RealChiro(const PointConfiguration& points) : 
  chirotope_data(), _no(points.coldim()), _rank(points.rowdim()) {
  for (parameter_type i = 0; i < _no - _rank + 1; ++i) {
    _recursive_chiro(points[i], points, basis_type(i), i + 1, 1, false);
  }
  if (CommandlineOptions::verbose()) {
    std::cerr << std::endl;
    std::cerr << load() << " signs in total." << std::endl;
  }
}

// functions:
const basis_type RealChiro::find_non_deg_basis() const {
  basis_type result;
  if (_no == 0) {
    return result;
  }
  if (_rank == 0) {
    return result;
  }
  Permutation perm(_no, _rank);
  result = basis_type(perm);
  while ( ((*this)(result) == 0) && (perm.lexnext()) ) {
    result = basis_type(perm);
  }
  assert((*this)(result) != 0);
  return result;
}

RealChiro RealChiro::dual() const {
  static long count;
  const basis_type groundset(0, _no);
  RealChiro result;
  result._no = _no;
  result._rank = _no - _rank;
  for (const_iterator iter = begin(); iter != end(); ++iter) {
    const basis_type basis = iter->key();
    const int basis_sign = iter->data();
    const basis_type dualbasis(groundset - basis);
    Permutation perm(dualbasis);
    perm.append(Permutation(basis));
    int perm_sign = perm.sign(result._rank);
    result.insert(dualbasis, perm_sign * basis_sign);
#ifdef COMPUTATIONS_DEBUG
    if (perm.sign() != perm_sign) {
      std::cerr << "RealChiro RealChiro::dual() const: "
	   << "perm_sign error." << std::endl;
    }
#endif
#ifdef SUPER_VERBOSE
    std::cerr << perm_sign * (*this)(basis) << ',';
#endif
    if (CommandlineOptions::verbose() && (++count % 1000 == 0)) {
#ifdef SUPER_VERBOSE
      std::cerr << std::endl;
#endif
      std::cerr << count << " signs computed so far." << std::endl;
    }
  }
  if (CommandlineOptions::verbose()) {
    std::cerr << load() << " signs in total." << std::endl;
  }
  return result;
}

// stream output/input:
std::ostream& RealChiro::print_string(std::ostream& ost) const {
  size_type count(0);
  ost << _no << ',' << _rank << ':' << std::endl;
  Permutation perm(_no, _rank);
  do {
    int chiro_on_perm = (*this)(basis_type(perm));
#ifdef SUPER_VERBOSE
    std::cerr << "chiro(" << basis_type(perm) << ") = " << chiro_on_perm << std::endl;
#endif
    ost << int2sign(chiro_on_perm);
    if (++count % 100 == 0) {
      ost << '\n';
    }
  } while (perm.lexnext());
  ost << std::endl;
#ifdef WATCH_MAXCHAINLEN
  std::cerr << "max chain length of hash table: " << maxchainlen() << std::endl;
#endif
  return ost;
}

std::ostream& RealChiro::print_dualstring(std::ostream& ost) const {
  static long count;
  const basis_type groundset(0, _no);
  ost << _no << ',' << _no - _rank << ':' << std::endl;
  Permutation dualperm(_no, _no -_rank);
  do {
    const Permutation primalperm(groundset - basis_type(dualperm));
    const basis_type basis(primalperm);
    Permutation perm(dualperm);
    perm.append(primalperm);
    const int perm_sign = perm.sign(_no - _rank);
    const int chiro_on_perm = perm_sign * (*this)(basis);
    ost << int2sign(chiro_on_perm);
    if (++count % 100 == 0) {
      ost << '\n';
    }
#ifdef COMPUTATIONS_DEBUG
    if (perm.sign() != perm_sign) {
      std::cerr << "RealChiro RealChiro::print_dualstring() const: "
	   << "perm_sign error." << std::endl;
    }
#endif
#ifdef SUPER_VERBOSE
    std::cerr << perm_sign * (*this)(basis) << ',';
#endif
    if (count % 1000 == 0) {
      if (CommandlineOptions::verbose()) {
#ifdef SUPER_VERBOSE
	std::cerr << std::endl;
#endif
	std::cerr << count << " signs computed so far." << std::endl;
      }
    }
  } while (dualperm.lexnext());
  ost << std::endl;
  if (CommandlineOptions::verbose()) {
    std::cerr << count << " signs in total." << std::endl;
  }
  return ost;
}

std::istream& RealChiro::read_string(std::istream& ist) {
  char c;

  clear();
  if (!(ist >> std::ws >> _no)) {
#ifdef READ_DEBUG
    std::cerr << "Circuits::read_string(std::istream&): "
	 << "number of points not found." << std::endl;
#endif
    ist.clear(std::ios::failbit);
    return ist;
  }
  if (!(ist >> std::ws >> c)) {
#ifdef READ_DEBUG
    std::cerr << "Circuits::read_string(std::istream&): "
	 << "separator not found." << std::endl;
#endif
    ist.clear(std::ios::failbit);
    return ist;
  }
  if (!(ist >> std::ws >> _rank)) {
#ifdef READ_DEBUG
    std::cerr << "Circuits::read_string(std::istream&): "
	 << "rank not found." << std::endl;
#endif
    ist.clear(std::ios::failbit);
    return ist;
  }
  if (!(ist >> std::ws >> c)) {
#ifdef READ_DEBUG
    std::cerr << "Circuits::read_string(std::istream&): "
	 << "separator not found." << std::endl;
#endif
    ist.clear(std::ios::failbit);
    return ist;
  }
  if (_rank > _no) {
#ifdef READ_DEBUG
    std::cerr << "Circuits::read_string(std::istream&): "
	 << "rank must not be larger than number of points." << std::endl;
#endif
    ist.clear(std::ios::failbit);
    return ist;    
  }
  Permutation perm(_no, _rank);
  do {
    if (ist >> c) {
      insert(basis_type(perm), sign2int(c));
    }
    else {
#ifdef READ_DEBUG
      std::cerr << "Circuits::read_string(std::istream&): "
	   << "not enough signs." << std::endl;
#endif
      ist.clear(std::ios::failbit);
      return ist;
    }
  } while (perm.lexnext());
  return ist;
}

// internal algorithms:
void RealChiro::_recursive_chiro(const StairCaseMatrix&    current,
				 const PointConfiguration& points,
				 const basis_type&         basis,
				 const parameter_type      start,
				 const parameter_type      step,
				 const bool                already_dependent) {
  static long count;
  if (already_dependent) {
    for (parameter_type i = start; i < _no - _rank + step + 1; ++i) {
      basis_type newbasis(basis);
      newbasis += i;
      if (step + 1 == _rank) {
	insert(newbasis, sign(ZERO));
	if (CommandlineOptions::verbose()) {
#ifdef MEGA_VERBOSE
	  std::cerr << "inserting sign for basis: " << basis << std::endl;
#endif
	  if (++count % 1000 == 0) {
#ifdef SUPER_VERBOSE
	    std::cerr << std::endl;
#endif
	    std::cerr << count << " signs computed so far." << std::endl;
	  }
	}
      }
      else {
	_recursive_chiro(current, points, newbasis, i + 1, step + 1, true);
      }
    }
  }
  else {
    for (parameter_type i = start; i < _no - _rank + step + 1; ++i) {
      StairCaseMatrix next = current;
      next.augment(points[i]);
      basis_type newbasis(basis);
      newbasis += i;
      if (step + 1 == _rank) {
#ifdef SUPER_VERBOSE
	std::cerr << det(next) << ',';
#endif
	insert(newbasis, sign(det(next)));
	if (CommandlineOptions::verbose()) {
#ifdef MEGA_VERBOSE
	  std::cerr << "inserting sign for basis: " << basis << std::endl;
#endif
	  if (++count % 1000 == 0) {
#ifdef SUPER_VERBOSE
	    std::cerr << std::endl;
#endif
	    std::cerr << count << " signs computed so far." << std::endl;
	  }
	}
      }
      else {
	if (next.has_full_rank()) {
	  _recursive_chiro(next, points, newbasis, i + 1, step + 1, false);
	}
	else {	  
#ifdef SUPER_VERBOSE
	  std::cerr << "premature dependence found in corank " << _rank - step << std::endl;
#endif
	  _recursive_chiro(next, points, newbasis, i + 1, step + 1, true);
	}
      }
    }
  }
}

// eof RealChiro.cc
