////////////////////////////////////////////////////////////////////////////////
// 
// CompressedIntegerSet.cc
//
//    produced: 2002/06/24 jr
// last change: 2002/06/24 jr
// 
////////////////////////////////////////////////////////////////////////////////

#include <assert.h>

#include "CommandlineOptions.hh"
#include "CompressedIntegerSet.hh"

namespace topcom {

  unsigned char CompressedIntegerSet::_S_first_one[] = {
    0, /*   0 */ 0, /*   1 */ 1, /*   2 */ 0, /*   3 */ 2, /*   4 */
    0, /*   5 */ 1, /*   6 */ 0, /*   7 */ 3, /*   8 */ 0, /*   9 */
    1, /*  10 */ 0, /*  11 */ 2, /*  12 */ 0, /*  13 */ 1, /*  14 */
    0, /*  15 */ 4, /*  16 */ 0, /*  17 */ 1, /*  18 */ 0, /*  19 */
    2, /*  20 */ 0, /*  21 */ 1, /*  22 */ 0, /*  23 */ 3, /*  24 */
    0, /*  25 */ 1, /*  26 */ 0, /*  27 */ 2, /*  28 */ 0, /*  29 */
    1, /*  30 */ 0, /*  31 */ 5, /*  32 */ 0, /*  33 */ 1, /*  34 */
    0, /*  35 */ 2, /*  36 */ 0, /*  37 */ 1, /*  38 */ 0, /*  39 */
    3, /*  40 */ 0, /*  41 */ 1, /*  42 */ 0, /*  43 */ 2, /*  44 */
    0, /*  45 */ 1, /*  46 */ 0, /*  47 */ 4, /*  48 */ 0, /*  49 */
    1, /*  50 */ 0, /*  51 */ 2, /*  52 */ 0, /*  53 */ 1, /*  54 */
    0, /*  55 */ 3, /*  56 */ 0, /*  57 */ 1, /*  58 */ 0, /*  59 */
    2, /*  60 */ 0, /*  61 */ 1, /*  62 */ 0, /*  63 */ 6, /*  64 */
    0, /*  65 */ 1, /*  66 */ 0, /*  67 */ 2, /*  68 */ 0, /*  69 */
    1, /*  70 */ 0, /*  71 */ 3, /*  72 */ 0, /*  73 */ 1, /*  74 */
    0, /*  75 */ 2, /*  76 */ 0, /*  77 */ 1, /*  78 */ 0, /*  79 */
    4, /*  80 */ 0, /*  81 */ 1, /*  82 */ 0, /*  83 */ 2, /*  84 */
    0, /*  85 */ 1, /*  86 */ 0, /*  87 */ 3, /*  88 */ 0, /*  89 */
    1, /*  90 */ 0, /*  91 */ 2, /*  92 */ 0, /*  93 */ 1, /*  94 */
    0, /*  95 */ 5, /*  96 */ 0, /*  97 */ 1, /*  98 */ 0, /*  99 */
    2, /* 100 */ 0, /* 101 */ 1, /* 102 */ 0, /* 103 */ 3, /* 104 */
    0, /* 105 */ 1, /* 106 */ 0, /* 107 */ 2, /* 108 */ 0, /* 109 */
    1, /* 110 */ 0, /* 111 */ 4, /* 112 */ 0, /* 113 */ 1, /* 114 */
    0, /* 115 */ 2, /* 116 */ 0, /* 117 */ 1, /* 118 */ 0, /* 119 */
    3, /* 120 */ 0, /* 121 */ 1, /* 122 */ 0, /* 123 */ 2, /* 124 */
    0, /* 125 */ 1, /* 126 */ 0, /* 127 */ 7, /* 128 */ 0, /* 129 */
    1, /* 130 */ 0, /* 131 */ 2, /* 132 */ 0, /* 133 */ 1, /* 134 */
    0, /* 135 */ 3, /* 136 */ 0, /* 137 */ 1, /* 138 */ 0, /* 139 */
    2, /* 140 */ 0, /* 141 */ 1, /* 142 */ 0, /* 143 */ 4, /* 144 */
    0, /* 145 */ 1, /* 146 */ 0, /* 147 */ 2, /* 148 */ 0, /* 149 */
    1, /* 150 */ 0, /* 151 */ 3, /* 152 */ 0, /* 153 */ 1, /* 154 */
    0, /* 155 */ 2, /* 156 */ 0, /* 157 */ 1, /* 158 */ 0, /* 159 */
    5, /* 160 */ 0, /* 161 */ 1, /* 162 */ 0, /* 163 */ 2, /* 164 */
    0, /* 165 */ 1, /* 166 */ 0, /* 167 */ 3, /* 168 */ 0, /* 169 */
    1, /* 170 */ 0, /* 171 */ 2, /* 172 */ 0, /* 173 */ 1, /* 174 */
    0, /* 175 */ 4, /* 176 */ 0, /* 177 */ 1, /* 178 */ 0, /* 179 */
    2, /* 180 */ 0, /* 181 */ 1, /* 182 */ 0, /* 183 */ 3, /* 184 */
    0, /* 185 */ 1, /* 186 */ 0, /* 187 */ 2, /* 188 */ 0, /* 189 */
    1, /* 190 */ 0, /* 191 */ 6, /* 192 */ 0, /* 193 */ 1, /* 194 */
    0, /* 195 */ 2, /* 196 */ 0, /* 197 */ 1, /* 198 */ 0, /* 199 */
    3, /* 200 */ 0, /* 201 */ 1, /* 202 */ 0, /* 203 */ 2, /* 204 */
    0, /* 205 */ 1, /* 206 */ 0, /* 207 */ 4, /* 208 */ 0, /* 209 */
    1, /* 210 */ 0, /* 211 */ 2, /* 212 */ 0, /* 213 */ 1, /* 214 */
    0, /* 215 */ 3, /* 216 */ 0, /* 217 */ 1, /* 218 */ 0, /* 219 */
    2, /* 220 */ 0, /* 221 */ 1, /* 222 */ 0, /* 223 */ 5, /* 224 */
    0, /* 225 */ 1, /* 226 */ 0, /* 227 */ 2, /* 228 */ 0, /* 229 */
    1, /* 230 */ 0, /* 231 */ 3, /* 232 */ 0, /* 233 */ 1, /* 234 */
    0, /* 235 */ 2, /* 236 */ 0, /* 237 */ 1, /* 238 */ 0, /* 239 */
    4, /* 240 */ 0, /* 241 */ 1, /* 242 */ 0, /* 243 */ 2, /* 244 */
    0, /* 245 */ 1, /* 246 */ 0, /* 247 */ 3, /* 248 */ 0, /* 249 */
    1, /* 250 */ 0, /* 251 */ 2, /* 252 */ 0, /* 253 */ 1, /* 254 */
    0, /* 255 */
  }; // end _First_one


  // conversion:
  CompressedIntegerSet::operator IntegerSet() const {
    IntegerSet result;
    for (const_iterator iter = begin();
	 iter != end();
	 ++iter) {
      result += *iter;
    }
    return result;
  }


  // constructors:
  CompressedIntegerSet::CompressedIntegerSet() : 
    _non_zero  (),
    _compressed() {
  }

  CompressedIntegerSet::CompressedIntegerSet(const CompressedIntegerSet& cis) : 
    _non_zero  (cis._non_zero),
    _compressed(cis._compressed) {
  }

  CompressedIntegerSet::CompressedIntegerSet(const IntegerSet& is) : 
    _non_zero  (),
    _compressed() {
    for (IntegerSet::const_iterator iter = is.begin();
	 iter != is.end();
	 ++iter) {
      *this += *iter;
    }
  }

  CompressedIntegerSet::CompressedIntegerSet(const SparseIntegerSet& sis) : 
    _non_zero  (),
    _compressed() {
    for (SparseIntegerSet::const_iterator iter = sis.begin();
	 iter != sis.end();
	 ++iter) {
      *this += *iter;
    }
  }

  CompressedIntegerSet::CompressedIntegerSet(const size_type start, const size_type stop) : 
    _non_zero  (),
    _compressed() {
    for (size_type i = start; i < stop; ++i) {
      *this += i;
    }
  }

  CompressedIntegerSet::CompressedIntegerSet(const size_type elem) : 
    _non_zero  (),
    _compressed() {
    *this += elem;
  }

  CompressedIntegerSet::CompressedIntegerSet(const size_type len, const size_type* init) : 
    _non_zero  (),
    _compressed() {
    for (size_type i = 0; i < len; ++i) {
      *this += init[i];
    }
  }

#ifndef STL_CONTAINERS
  CompressedIntegerSet::CompressedIntegerSet(const Array<size_type>& a) :
    _non_zero  (),
    _compressed() {
    for (size_type i = 0; i < a.size(); ++i) {
      *this += a[i];
    }
  }

  CompressedIntegerSet::CompressedIntegerSet(const PlainArray<size_type>& pa) : 
    _non_zero  (),
    _compressed() {
    for (size_type i = 0; i < pa.size(); ++i) {
      *this += pa[i];
    }  
  }
#endif

  // destructor:
  CompressedIntegerSet::~CompressedIntegerSet() {} // destructor

  // assignment:
  CompressedIntegerSet& CompressedIntegerSet::operator=(const CompressedIntegerSet& cis) {
    if (this == &cis) {
      return *this;
    }
    _non_zero      = cis._non_zero;
    _compressed    = cis._compressed;
    return *this;
  }

  // keys for containers:
  const size_type CompressedIntegerSet::keysize() const {
#ifndef STL_CONTAINERS
    return _non_zero.keysize() + _compressed.keysize();
#else
    return 1 + _compressed.size();
#endif
  }

  const size_type CompressedIntegerSet::key(size_type n) const {
    if (n == 0) {
      return _non_zero.invariant();
    }
    else {
      return _compressed[n - 1];
    }
  }

  // accessors:
  const IntegerSet& CompressedIntegerSet::non_zero() const { return _non_zero; }

  const compressed_type& CompressedIntegerSet::compressed() const { return _compressed; }

  // functions:
  const size_type CompressedIntegerSet::card() const {
    size_type count(0);

    // algorithm taken from "http://www.caam.rice.edu/~dougm/twiddle/BitCount.html"
    for (size_type i = 0; i < _compressed.size(); i++) {
      size_type tmpbits = _compressed[i];
      while (tmpbits) {
	++count;
	tmpbits &= tmpbits - 1;
      }
    }
    return count;
  }


  // boolean functions:
  const bool CompressedIntegerSet::contains(const size_type elem) const {
#ifdef DEBUG
    std::cerr << "Does " << *this << " contain " << elem << "?" << std::endl;
#endif
    const size_type block_pos(elem / block_len);
    if (!_non_zero.contains(block_pos)) {
      if (CommandlineOptions::debug()) {
	std::cerr << "No." << std::endl;
      }
      return false;
    }
    const size_type bit_pos(elem % block_len);
    size_type non_zero_index(0);
    for (IntegerSet::const_iterator iter = _non_zero.begin();
	 iter != _non_zero.end();
	 ++iter) {
      if (*iter == block_pos) {
	break;
      }
      else {
	++non_zero_index;
      }
    }
    const bool result(((bit_one << bit_pos) & _compressed[non_zero_index]) != 0);
#ifdef DEBUG
    if (result) {
      std::cerr << "Yes." << std::endl;
    } 
    else {
      std::cerr << "No." << std::endl;
    }
#endif
    return result;
  }

  const bool CompressedIntegerSet::superset(const CompressedIntegerSet& cis) const {
#ifdef DEBUG
    std::cerr << "Is " << *this << " a superset of " << cis << "?" << std::endl;
#endif
    if (!_non_zero.superset(cis._non_zero)) {
      if (CommandlineOptions::debug()) {
	std::cerr << "No." << std::endl;
      }
      return false;
    }
    size_type non_zero_index(0);
    size_type cis_non_zero_index(0);
    IntegerSet::const_iterator iter(_non_zero.begin());
    IntegerSet::const_iterator cis_iter(cis._non_zero.begin());
    while ((iter != _non_zero.end()) && (cis_iter != cis._non_zero.end())) {
      while ((*iter < *cis_iter) && (iter != _non_zero.end())) {
	++non_zero_index;
	++iter;
      }
      while ((*cis_iter < *iter) && (cis_iter != cis._non_zero.end())) {
	++cis_non_zero_index;
	++cis_iter;
      }
      if (~_compressed[non_zero_index] & cis._compressed[cis_non_zero_index]) {
#ifdef DEBUG
	std::cerr << "No." << std::endl;
#endif
	return false;
      }
      ++iter;
      ++cis_iter;
    }
#ifdef DEBUG
    std::cerr << "Yes." << std::endl;
#endif
    return true;
  }

  const bool CompressedIntegerSet::subset(const CompressedIntegerSet& cis) const {
    return cis.superset(*this);
  }

  const bool CompressedIntegerSet::disjoint(const CompressedIntegerSet& cis) const {
#ifdef DEBUG
    std::cerr << "Is " << *this << " a disjoint from " << cis << "?" << std::endl;
#endif
    if (_non_zero.disjoint(cis._non_zero)) {
#ifdef DEBUG
      std::cerr << "Yes." << std::endl;
#endif
      return true;
    }

    size_type non_zero_index(0);
    size_type cis_non_zero_index(0);
    IntegerSet::const_iterator iter(_non_zero.begin());
    IntegerSet::const_iterator cis_iter(cis._non_zero.begin());
    while ((iter != _non_zero.end()) && (cis_iter != cis._non_zero.end())) {
      while ((*iter < *cis_iter) && (iter != _non_zero.end())) {
	++non_zero_index;
	++iter;
      }
      while ((*cis_iter < *iter) && (cis_iter != cis._non_zero.end())) {
	++cis_non_zero_index;
	++cis_iter;
      }
      if (_compressed[non_zero_index] & cis._compressed[cis_non_zero_index]) {
#ifdef DEBUG
	std::cerr << "No." << std::endl;
#endif
	return false;
      }
      ++iter;
      ++cis_iter;
    }
#ifdef DEBUG
    std::cerr << "Yes." << std::endl;
#endif
    return true;
  }


  const bool CompressedIntegerSet::empty() const {
    return _non_zero.empty();
  }

  // iterator functions:
  CompressedIntegerSet::const_iterator CompressedIntegerSet::begin() const {
    return CompressedIntegerSet::const_iterator(*this);
  }

  CompressedIntegerSet::const_iterator CompressedIntegerSet::end() const {
    return CompressedIntegerSet::const_iterator(*this, 0);  
  }

  CompressedIntegerSet::const_iterator CompressedIntegerSet::find(const size_type elem) const {
    const_iterator result(begin());
    while (++result != end()) {
      if (*result == elem) {
	return result;
      }
    }
    return result;
  }

  // boolean operators:
  const bool CompressedIntegerSet::operator==(const CompressedIntegerSet& cis) const {
#ifdef DEBUG
    std::cerr << "Is " << *this << " equal to " << cis << "?" << std::endl;
#endif
    const bool result((_non_zero == cis._non_zero) && (_compressed == cis._compressed));
#ifdef DEBUG
    if (result) {
      std::cerr << "Yes." << std::endl;
    }
    else {
      std::cerr << "No." << std::endl;
    }
#endif
    return result;
  }

  const bool CompressedIntegerSet::operator!=(const CompressedIntegerSet& cis) const {
    return (!(*this == cis));
  }

  const bool CompressedIntegerSet::operator<(const CompressedIntegerSet& cis) const {
#ifdef DEBUG
    std::cerr << "Is " << *this << " less than " << cis << "?" << std::endl;
#endif
    if (_non_zero < cis._non_zero) {
#ifdef DEBUG
      std::cerr << "Yes." << std::endl;
#endif
      return true;
    }
    else if (cis._non_zero < _non_zero) {
#ifdef DEBUG
      std::cerr << "No." << std::endl;
#endif
      return false;
    }
    assert(_non_zero == cis._non_zero);
    for (size_type i = 0; i < _compressed.size(); ++i) {
      if (_compressed[i] < cis._compressed[i]) {
#ifdef DEBUG
	std::cerr << "Yes." << std::endl;
#endif
	return true;
      }
      else if (cis._compressed[i] < _compressed[i]) {
#ifdef DEBUG
	std::cerr << "No." << std::endl;
#endif
	return false;
      }
    }
    assert(_compressed == cis._compressed);
#ifdef DEBUG
    std::cerr << "No." << std::endl;
#endif
    return false;
  }

  const bool CompressedIntegerSet::operator>(const CompressedIntegerSet& cis) const {
    return (cis < *this);
  }

  const size_type CompressedIntegerSet::operator[](const size_type index) const {
    size_type count(0);
    size_type non_zero_index(0);
    for (IntegerSet::const_iterator iter = _non_zero.begin();
	 iter != _non_zero.end();
	 ++iter) {
      const IntegerSet current_block_set(_compressed[non_zero_index], 1);
      const size_type block_card = current_block_set.card();
      count += block_card;
      if (count > index) {
	return (*iter * block_len + current_block_set[count - index]);
      }
    }
    return 0; // never reached; just to prevent compiler warnings.
  }

  
  CompressedIntegerSet& CompressedIntegerSet::clear() {
    _non_zero.clear();
    _compressed.resize(0UL);
    return *this;
  }

  CompressedIntegerSet& CompressedIntegerSet::fill(const size_type start, const size_type stop) {
    for (size_type i = start; i < stop; ++i) {
      *this += i;
    }
    return *this;
  }

  
  // adding and deleting an element:
  CompressedIntegerSet& CompressedIntegerSet::operator+=(const size_type elem) {
#ifdef DEBUG
    std::cerr << "*this before adding " << elem << ": " << *this << std::endl;
#endif
    const size_type block_pos = elem / block_len;
    const size_type bit_pos = elem % block_len;
    _non_zero += block_pos;
    size_type non_zero_index(0);
    for (IntegerSet::const_iterator iter = _non_zero.begin();
	 iter != _non_zero.end();
	 ++iter) {
      if (*iter == block_pos) {
	break;
      }
      else {
	++non_zero_index;
      }
    }
    const size_type non_zero_card(_non_zero.card());
    if (_compressed.size() < non_zero_card) {
      _compressed.resize(non_zero_card);
      for (size_type i = _compressed.size() - 1; i > non_zero_index; --i) {
	_compressed[i] = _compressed[i-1];
      }
      _compressed[non_zero_index] = (bit_one << bit_pos);
    }
    else {
      _compressed[non_zero_index] |= (bit_one << bit_pos);
    }
#ifdef DEBUG
    std::cerr << "*this after adding " << elem << ": " << *this << std::endl;
#endif
    assert(_compressed.size() == _non_zero.card());
    return *this;  
  }

  CompressedIntegerSet& CompressedIntegerSet::operator-=(const size_type elem){
#ifdef DEBUG
    std::cerr << "*this before deleting " << elem << ": " << *this << std::endl;
#endif
    const size_type block_pos = elem / block_len;
    const size_type bit_pos = elem % block_len;
    if (!_non_zero.contains(block_pos)) {
      return *this;
    }
    size_type non_zero_index(0);
    for (IntegerSet::const_iterator iter = _non_zero.begin();
	 iter != _non_zero.end();
	 ++iter) {
      if (*iter == block_pos) {
	break;
      }
      else {
	++non_zero_index;
      }
    }
    _compressed[non_zero_index] &= ~(bit_one << bit_pos);
    if (_compressed[non_zero_index] == 0UL) {
      _non_zero -= non_zero_index;
      for (size_type i = non_zero_index; i < _compressed.size() - 1; ++i) {
	_compressed[i] = _compressed[i+1];
      }
      _compressed.resize(_compressed.size() - 1);
    }
#ifdef DEBUG
    std::cerr << "*this after deleting " << elem << ": " << *this << std::endl;
#endif
    assert(_compressed.size() == _non_zero.card());
    return *this;  
  }

  CompressedIntegerSet& CompressedIntegerSet::operator^=(const size_type elem){
    if (contains(elem)) {
      *this -= elem;
    }
    else {
      *this += elem;
    }
    assert(_compressed.size() == _non_zero.card());
    return *this;  
  }


  // union, difference, and intersection with sets:
  CompressedIntegerSet& CompressedIntegerSet::operator+=(const CompressedIntegerSet& cis) {
#ifdef DEBUG
    std::cerr << "*this before adding " << cis << ": " << *this << std::endl;
#endif
    const CompressedIntegerSet this_copy(*this);
    size_type non_zero_index(0);
    size_type this_non_zero_index(0);
    size_type cis_non_zero_index(0);
    _non_zero += cis._non_zero;
    _compressed.resize(_non_zero.card());
    for (IntegerSet::const_iterator iter = _non_zero.begin();
	 iter != _non_zero.end();
	 ++iter) {
      _compressed[non_zero_index] = 0UL;
      if (cis._non_zero.contains(*iter)) {
	_compressed[non_zero_index] |= cis._compressed[cis_non_zero_index];
	++cis_non_zero_index;
      }
      if (this_copy._non_zero.contains(*iter)) {
	_compressed[non_zero_index] |= this_copy._compressed[this_non_zero_index];
	++this_non_zero_index;
      }
      ++non_zero_index;
    }
#ifdef DEBUG
    std::cerr << "*this after adding " << cis << ": " << *this << std::endl;
#endif
    assert(_compressed.size() == _non_zero.card());
    return *this;
  }

  CompressedIntegerSet& CompressedIntegerSet::operator-=(const CompressedIntegerSet& cis) {
#ifdef DEBUG
    std::cerr << "*this before substracting " << cis << ": " << *this << std::endl;
#endif
    size_type non_zero_index(0);
    size_type cis_non_zero_index(0);
    IntegerSet non_zero_union(_non_zero);
    non_zero_union += cis._non_zero;
    for (IntegerSet::const_iterator iter = non_zero_union.begin();
	 iter != non_zero_union.end();
	 ++iter) {
      if (cis._non_zero.contains(*iter) && _non_zero.contains(*iter)) {
	_compressed[non_zero_index] &= ~cis._compressed[cis_non_zero_index];
	++non_zero_index;
	++cis_non_zero_index;
      }
      else if (_non_zero.contains(*iter)) {
	++non_zero_index;
      }
      else if (cis._non_zero.contains(*iter)) {
	++cis_non_zero_index;
      }
    }
    _compactify();
#ifdef DEBUG
    std::cerr << "*this after substracting " << cis << ": " << *this << std::endl;
#endif
    return *this;
  }

  CompressedIntegerSet& CompressedIntegerSet::operator*=(const CompressedIntegerSet& cis) {
    IntegerSet test_result(*this);
#ifdef DEBUG
    std::cerr << "*this before intersecting " << cis << ": " << *this << std::endl;
    std::cerr << "_non_zero before intersecting " << cis._non_zero << ": " << _non_zero << std::endl;
    std::cerr << "_compressed before intersecting " << cis._compressed << ": " << _compressed << std::endl;
#endif
    size_type non_zero_index(0);
    size_type cis_non_zero_index(0);
    IntegerSet non_zero_union(_non_zero);
    non_zero_union += cis._non_zero;
    for (IntegerSet::const_iterator iter = non_zero_union.begin();
	 iter != non_zero_union.end();
	 ++iter) {
      if (cis._non_zero.contains(*iter) && _non_zero.contains(*iter)) {
	_compressed[non_zero_index] &= cis._compressed[cis_non_zero_index];
	++non_zero_index;
	++cis_non_zero_index;
      }
      else if (_non_zero.contains(*iter)) {
	_compressed[non_zero_index] = 0UL;
	++non_zero_index;
      }
      else if (cis._non_zero.contains(*iter)) {
	++cis_non_zero_index;
      }
#ifdef DEBUG
      std::cerr << "non_zero_index: " << non_zero_index << std::endl;
      std::cerr << "cis_non_zero_index: " << cis_non_zero_index << std::endl;
#endif
    }
    assert(non_zero_index == _compressed.size());
    assert(cis_non_zero_index == cis._compressed.size());
    _compactify();
#ifdef DEBUG
    std::cerr << "*this after intersecting " << cis << ": " << *this << std::endl;
    test_result *= IntegerSet(cis);
    assert(*this == CompressedIntegerSet(test_result));
#endif
    return *this;
  }

  CompressedIntegerSet& CompressedIntegerSet::operator^=(const CompressedIntegerSet& cis) {
#ifdef DEBUG
    std::cerr << "*this before xoring " << cis << ": " << *this << std::endl;
#endif
    const CompressedIntegerSet this_copy(*this);
    size_type non_zero_index(0);
    size_type this_non_zero_index(0);
    size_type cis_non_zero_index(0);
    _non_zero += cis._non_zero;
    _compressed.resize(_non_zero.card());
    for (IntegerSet::const_iterator iter = _non_zero.begin();
	 iter != _non_zero.end();
	 ++iter) {
      _compressed[non_zero_index] = 0UL;
      if (cis._non_zero.contains(*iter)) {
	_compressed[non_zero_index] ^= cis._compressed[cis_non_zero_index];
	++cis_non_zero_index;
      }
      if (this_copy._non_zero.contains(*iter)) {
	_compressed[non_zero_index] ^= this_copy._compressed[this_non_zero_index];
	++this_non_zero_index;
      }
      ++non_zero_index;
    }
    _compactify();
#ifdef DEBUG
    std::cerr << "*this after xoring " << cis << ": " << *this << std::endl;
#endif
    return *this;
  }

  
  // the same but a new set is returned:
  CompressedIntegerSet CompressedIntegerSet::operator+(const size_type elem) const {
    CompressedIntegerSet result(*this);
    result += elem;
    return result;  
  }

  CompressedIntegerSet CompressedIntegerSet::operator-(const size_type elem) const {
    CompressedIntegerSet result(*this);
    result -= elem;
    return result;  
  }

  CompressedIntegerSet CompressedIntegerSet::operator+(const CompressedIntegerSet& cis) const {
    CompressedIntegerSet result(*this);
    result += cis;
    return result;  
  }

  CompressedIntegerSet CompressedIntegerSet::operator-(const CompressedIntegerSet& cis) const {
    CompressedIntegerSet result(*this);
    result -= cis;
    return result;  
  }

  CompressedIntegerSet CompressedIntegerSet::operator*(const CompressedIntegerSet& cis) const {
    CompressedIntegerSet result(*this);
    result *= cis;
    return result;  
  }

  CompressedIntegerSet CompressedIntegerSet::operator^(const CompressedIntegerSet& cis) const {
    CompressedIntegerSet result(*this);
    result ^= cis;
    return result;  
  }


  // returns the cardinalities
  // 0, 1, or 2 (2 or more) of
  // the intersection of several CompressedIntegerSet's:
  const size_type CompressedIntegerSet::intersection_card(const CompressedIntegerSet** setarray, 
							  const size_type size, 
							  size_type& common_index) const {
    if (size == 0) {
      return 0;
    }
    CompressedIntegerSet intersection(*setarray[0]);
    for (size_type i = 1; i < size; ++i) {
      if ((intersection *= *setarray[i]).empty()) {
	return 0;
      }
    }
    common_index = *intersection.begin();
    if (intersection.card() == 1) {
      return 1;
    }
    else {
      return 2;
    }
  }

  const size_type CompressedIntegerSet::intersection_nonempty(const CompressedIntegerSet** setarray, 
							      const size_type size, 
							      size_type& common_index) const {
    if (size == 0) {
      return 0;
    }
    CompressedIntegerSet intersection(*setarray[0]);
    for (size_type i = 1; i < size; ++i) {
      if ((intersection *= *setarray[i]).empty()) {
	return 0;
      }
    }
    common_index = *intersection.begin();
    return 1;
  }

  // iostream:
  std::istream& CompressedIntegerSet::read(std::istream& ist) {
    IntegerSet reader;
    reader.read(ist);
    *this = CompressedIntegerSet(reader);
    return ist;
  }

  std::ostream& CompressedIntegerSet::write(std::ostream& ost) const {
    IntegerSet(*this).write(ost);
    if (CommandlineOptions::debug()) {
      ost << ':' << _non_zero << ':' << _compressed;
    }
    return ost;
  }


  // CompressedIntegerSet::const_iterator:

  __cis_const_iterator::__cis_const_iterator() : 
    _container       (0),
    _current_non_zero(0),
    _current_block   (0), 
    _current_bit     (0) {
  }

  __cis_const_iterator::__cis_const_iterator(const __cis_const_iterator& iter) :
    _container       (iter._container),
    _current_non_zero(iter._current_non_zero),
    _current_block   (iter._current_block),
    _current_bit     (iter._current_bit) {
  }


  __cis_const_iterator::__cis_const_iterator(const CompressedIntegerSet& s) :
    _container       (&s),
    _current_non_zero(0),
    _current_block   (0),
    _current_bit     (0) {
#ifdef CONSTRUCTOR_DEBUG
    std::cerr << "__cis_const_iterator::__cis_const_iterator(const IntegerSet&):" << std::endl;
#endif

    IntegerSet::const_iterator non_zero_iter(_container->_non_zero.begin());
    for (size_type i = 0; i < _container->_compressed.size(); i++) {
      block_type b = _container->_compressed[i];

      for (size_type j = 0; j < bytes_per_block; ++j) {
	unsigned char current_byte(static_cast<unsigned char>(b & ~(unsigned char)0UL));
	if (current_byte) {
	  _current_non_zero = i;
	  _current_block    = *non_zero_iter;
	  _current_bit      = j * byte_len + CompressedIntegerSet::_S_first_one[current_byte];
#ifdef COMPUTATIONS_DEBUG
	  std::cout << "first set bit is " << _current_bit << " in block " << _current_block << std::endl;
#endif
	  return;
	}
	b >>= byte_len;
      }
      ++non_zero_iter;
    }
    _current_non_zero = _container->_compressed.size();
    _current_block    = 0;
    _current_bit      = block_len;
  }
 
  __cis_const_iterator::__cis_const_iterator(const CompressedIntegerSet& s, int) :
    _container       (&s),
    _current_non_zero(_container->_compressed.size()),
    _current_block   (0),
    _current_bit     (block_len) {}
 
  __cis_const_iterator::__cis_const_iterator(const CompressedIntegerSet& s,
					     const size_type current_non_zero,
					     const size_type current_block,
					     const size_type current_bit) :
    _container       (&s),
    _current_non_zero(current_non_zero),
    _current_block   (current_block),
    _current_bit     (current_bit) {}
 
  __cis_const_iterator::~__cis_const_iterator() {
  }

  __cis_const_iterator& __cis_const_iterator::operator=(const __cis_const_iterator& iter) {
    if (this == &iter) {
      return *this;
    }
    _container        = iter._container;
    _current_non_zero = iter._current_non_zero;
    _current_block    = iter._current_block;
    _current_bit      = iter._current_bit;
    return *this;
  }

  const bool __cis_const_iterator::valid() const {
    return (_current_bit < block_len);
  }

  const bool __cis_const_iterator::operator==(const __cis_const_iterator& iter) const {
    return ((_container == iter._container)
	    && (_current_non_zero == iter._current_non_zero)
	    && (_current_block    == iter._current_block)
	    && (_current_bit      == iter._current_bit));
  }

  const bool __cis_const_iterator::operator!=(const __cis_const_iterator& iter) const {
    return !((*this) == iter);
  }

  const size_type __cis_const_iterator::operator*() const {
#ifdef INDEX_CHECK
    if (!valid()) {
      std::cerr << "__cis_const_iterator::operator*(): invalid __cis_const_iterator."
		<< std::endl;
      exit(1);
    }
#endif
    return (_current_block * block_len + _current_bit);
  }

  __cis_const_iterator __cis_const_iterator::operator++(int) {
    __cis_const_iterator tmp = *this;
    ++(*this);
    return tmp;
  }

  __cis_const_iterator& __cis_const_iterator::operator++() {  
#ifdef CONSTRUCTOR_DEBUG
    std::cerr << "__cis_const_iterator::operator++():" << std::endl;
#endif
    if (_current_non_zero >= _container->_compressed.size()) {
      _current_non_zero = _container->_compressed.size();
      _current_block    = 0;
      _current_bit      = block_len;
      return *this;
    }

    if (++_current_bit < block_len) {  

      // we might find another bit in the same block:
      block_type b = _container->_compressed[_current_non_zero];
    
      // mask away bits before _current_bit:
      b &= (all_bits << _current_bit);
    
#ifdef COMPUTATIONS_DEBUG
      std::cout << "current bit is " << _current_bit << " in block " << _current_block << std::endl;
#endif
    
      for (size_type j = _current_bit / byte_len; j < bytes_per_block; ++j) {
	for (size_type j = 0; j < bytes_per_block; ++j) {
	  unsigned char current_byte(static_cast<unsigned char>(b & ~(unsigned char)0UL));
#ifdef COMPUTATIONS_DEBUG
	  std::cout << "checking byte " << j << "=" << (size_type)current_byte 
		    << " in block " << _current_block << std::endl;
#endif
	  if (current_byte) {
	    _current_bit = j * byte_len + CompressedIntegerSet::_S_first_one[current_byte];
	    return *this;
	  }
	  b >>= byte_len;
	}
      }
    }

    IntegerSet::const_iterator non_zero_iter(_container->_non_zero.find(_current_block));
    if (++non_zero_iter == _container->_non_zero.end()) {
      _current_non_zero = _container->_compressed.size();
      _current_block    = 0;
      _current_bit      = block_len;
      return *this;
    }
    else {
      ++_current_non_zero;
      _current_block = *non_zero_iter;
      block_type b = _container->_compressed[_current_non_zero];
      for (size_type j = 0; j < bytes_per_block; ++j) {
	unsigned char current_byte(static_cast<unsigned char>(b & ~(unsigned char)0UL));
#ifdef COMPUTATIONS_DEBUG
	std::cout << "checking byte " << j << "=" << (size_type)current_byte 
		  << " in subsequent block " << *non_zero_iter << std::endl;
#endif
	if (current_byte) {
	  _current_bit      = j * byte_len + CompressedIntegerSet::_S_first_one[current_byte];
	  return *this;
	}
	b >>= byte_len;
      }
    }
    std::cerr << "Error: zero block found in corrupted container " << *_container << std::endl;
    exit(1);
  }

  // internal functions:
  void CompressedIntegerSet::_compactify() {
    if (CommandlineOptions::debug()) {
      std::cerr << "_compressed before compactification:" << std::endl;
      std::cerr << _compressed << std::endl;
      std::cerr << "_non_zero before compactification:" << std::endl;
      std::cerr << _non_zero << std::endl;
    }
    size_type next_index(0);
    size_type next_non_zero_index(0);
    const IntegerSet non_zero_copy(_non_zero);
    for (IntegerSet::const_iterator iter = non_zero_copy.begin();
	 iter != non_zero_copy.end(); 
	 ++iter) {
      if (_compressed[next_index] == 0UL) {
	_non_zero -= *iter;
	++next_index;
	continue;
      }
      else {
	_compressed[next_non_zero_index] = _compressed[next_index];
	++next_non_zero_index;
	++next_index;
      }
    }
    _compressed.resize(next_non_zero_index);
    if (CommandlineOptions::debug()) {
      std::cerr << "_compressed after compactification:" << std::endl;
      std::cerr << _compressed << std::endl;
      std::cerr << "_non_zero after compactification:" << std::endl;
      std::cerr << _non_zero << std::endl;
    }
    assert(_compressed.size() == _non_zero.card());
  }

}; // namespace topcom

// eof IntegerSet.cc
