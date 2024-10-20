////////////////////////////////////////////////////////////////////////////////
// 
// StairCaseMatrix.cc
//
//    produced: 13/03/98 jr
// last change: 13/03/98 jr
// 
////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <ctype.h>
#include <string.h>

#include "StairCaseMatrix.hh"

StairCaseMatrix& StairCaseMatrix::augment(const Matrix& matrix) {
  if (matrix.coldim() == 0) {
    return *this;
  }
#ifdef INDEX_CHECK
  assert(rowdim() == matrix.rowdim());
  assert(coldim() + matrix.coldim() <= rowdim());
#endif
  size_type m = coldim();
  Matrix::augment(matrix);
  size_type n = rowdim();
#ifdef SUPER_VERBOSE
  std::cerr << "before stair case transformation:" << std::endl;
  pretty_print(std::cerr);
#endif
  for (size_type i = 0; i < m; ++i) {
    if ((*this)(i,i) == ZERO) {
      for (size_type k = m; k < m + matrix.coldim(); ++k) {
	if ((*this)(i,k) != ZERO) {
	  (*this).swap_cols(i,k);
	  _coefficient *= MINUSONE;
	  continue;
	}
      }
      if ((*this)(i,i) == ZERO) {
	continue;
      }
    }
    const Field& eraser = (*this)(i,i);
#ifdef SUPER_VERBOSE
    std::cerr << "eraser = " << eraser << "; row : " << i << ", col: " << i << std::endl;
#endif
    for (size_type j = m; j < m + matrix.coldim(); ++j) {
      const Field& delinquent = (*this)(i,j);
#ifdef SUPER_VERBOSE
      std::cerr << "delinquent = " << delinquent << "; row : " << i << ", col: " << j << std::endl;
#endif
      if (delinquent == ZERO) {
	continue;
      }
      for (size_type k = i + 1; k < n; ++k) {
	(*this)(k,j) -= (*this)(k,i) * delinquent / eraser;
      }
      (*this)(i,j) = ZERO;
    }
#ifdef SUPER_VERBOSE
    std::cerr << "after step " << i << " of stair case transformation: " << std::endl;
    (*this).pretty_print(std::cerr);
#endif
  }
#ifdef SUPER_VERBOSE
  std::cerr << "after stair case transformation: " << std::endl;
  (*this).pretty_print(std::cerr);
#endif
  return *this;
}

const Field det(const StairCaseMatrix& matrix) {
#ifdef INDEX_CHECK
  assert(matrix.coldim() == matrix.rowdim());
#endif
  Field result(ONE);
  for (size_type i = 0; i < matrix.coldim(); ++i) {
    result *= matrix(i,i);
    if (result == ZERO) {
      return result;
    }
  }
  return result * matrix._coefficient;
}

std::ostream& StairCaseMatrix::pretty_print(std::ostream& ost) {
  ost << "matrix: " << '\n';
  Matrix::pretty_print(ost);
  ost << "coefficient: " << _coefficient << '\n';
  return ost;
}
 
std::ostream& operator<<(std::ostream& ost, const StairCaseMatrix& matrix) {
  ost << (Matrix)matrix << '/' << matrix._coefficient;
  return ost;
}

// eof StairCaseMatrix.cc
