////////////////////////////////////////////////////////////////////////////////
// 
// Matrix.cc
//
//    produced: 13/03/98 jr
// last change: 13/03/98 jr
// 
////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <ctype.h>
#include <string.h>

#include "Matrix.hh"

const char Matrix::col_delim_char = '\t';

const Vector Matrix::row(const size_type index) const {
  Vector result(coldim());
  for (size_type i = 0; i < coldim(); ++i) {
    result[i] = (*this)[i][index];
  }
  return result;
}
void Matrix::row_resize(const size_type new_size, const Field& init_entry) {
  for (size_type i = 0; i < rowdim(); ++i) {
    (*this)[i].resize(new_size,init_entry);
  }
}

Matrix& Matrix::add(const Matrix& matrix) {
#ifdef INDEX_CHECK
  assert((rowdim() == matrix.rowdim()) && (coldim() == matrix.coldim()));
#endif
  for (size_type i = 0; i < coldim(); ++i) {
    (*this)[i].add(matrix[i]);
  }
  return *this;
}
Matrix& Matrix::scale(const Field& entry) {
  for (size_type i = 0; i < coldim(); ++i) {
    (*this)[i].scale(entry);
  }
  return *this;
}

Matrix& Matrix::augment(const Matrix& matrix) {
#ifdef INDEX_CHECK
  if (coldim() > 0) {
    assert(rowdim() == matrix.rowdim());
  }
#endif
  append(matrix);
  return *this;
}
Matrix& Matrix::stack(const Matrix& matrix) {
#ifdef INDEX_CHECK
  assert(coldim() == matrix.coldim());
#endif
  for (size_type i = 0; i < coldim(); ++i) {
    (*this)[i].stack(matrix[i]);
  }
  return *this;
}

Matrix& Matrix::swap_cols(const size_type i, const size_type j) {
#ifdef INDEX_CHECK
  assert((i < coldim()) && (j < coldim()));
#endif
  const Vector tmp = (*this)[i];
  (*this)[i] = (*this)[j];
  (*this)[j] = tmp;
  return *this;
}
Matrix& Matrix::swap_rows(const size_type i, const size_type j) {
#ifdef INDEX_CHECK
  assert((i < rowdim()) && (j < rowdim()));
#endif
  for (size_type k = 0; k < coldim(); ++k) {
    Vector& col = (*this)[k];
    const Field tmp = col[i];
    col[i] = col[j];
    col[j] = tmp;
  }
  return *this;
}

const Field left_upper_det(const Matrix& matrix) {
  size_type n = matrix.coldim();
  if (matrix.coldim() > matrix.rowdim())
    n = matrix.rowdim();

  Matrix tmp = matrix;
  tmp.resize(n);
  Field scale(ONE);
  for (size_type i = 0; i < n - 1; ++i) {
    if (tmp(i,i) == ZERO) {
      for (size_type k = i + 1; k < n; ++k) {
	if (tmp(i,k) != ZERO) {
	  tmp.swap_cols(i,k);
	  scale *= -1;
	  continue;
	}
      }
      if (tmp(i,i) == ZERO) {
	return ZERO;
      }
    }
    Field eraser = tmp(i,i);
#ifdef SUPER_VERBOSE
    std::cerr << "eraser = " << eraser << std::endl;
#endif
    for (size_type j = i + 1; j < n; ++j) {
      Field delinquent = tmp(i,j);
      if (delinquent == ZERO) {
	continue;
      }
#ifdef SUPER_VERBOSE
      std::cerr << "delinquent = " << delinquent << std::endl;
#endif
      for (size_type k = i + 1; k < n; ++k) {
	tmp(k,j) -= (tmp(k,i) * delinquent / eraser);
      }
      tmp(i,j) = ZERO;
    }
#ifdef SUPER_VERBOSE
    std::cerr << "current tmp = " << std::endl;
    tmp.pretty_print(std::cerr);
#endif
  }
#ifdef SUPER_VERBOSE
  std::cerr << "Triangular transformation is:" << std::endl;
  tmp.pretty_print(std::cerr);
  std::cerr << "Scale factor is " << scale << std::endl;
#endif
  Field result(ONE);
  for (size_type i = 0; i < n; ++i) {
    result *= tmp(i,i);
  }
#ifdef SUPER_VERBOSE
  std::cerr << "Triangular determinant is " << result << std::endl;
#endif
  return result * scale;
}

const Matrix transpose(const Matrix& matrix) {
  Matrix result(matrix.coldim(), matrix.rowdim());
  for (size_type i = 0; i < matrix.coldim(); ++i) {
    for (size_type j = 0; j < matrix.rowdim(); ++j) {
      result[j][i] = matrix[i][j];
    }
  }
  return result;
}
const Matrix multiply(const Matrix& matrix1, const Matrix& matrix2) {
#ifdef INDEX_CHECK
  assert(matrix1.coldim() == matrix2.rowdim());
#endif
  Matrix result(matrix1.rowdim(), matrix2.coldim());
  for (size_type i = 0; i < matrix1.rowdim(); ++i) {
    const Vector row = matrix1.row(i);
    for (size_type j = 0; j < matrix2.coldim(); ++j) {
      result[j][i] = inner_product(row, matrix2.col(j));
    }
  }
  return result;
}

std::ostream& Matrix::pretty_print(std::ostream& ost) const {
  for (size_type i = 0; i < rowdim(); ++i) {
    const Vector row_vector = row(i);
    for (size_type j = 0; j < coldim(); ++j) {
      ost << row_vector[j] << col_delim_char;
    }
    ost << std::endl;
  }
  return ost;
}

// eof Matrix.cc
