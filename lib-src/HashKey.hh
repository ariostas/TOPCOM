////////////////////////////////////////////////////////////////////////////////
// 
// HashKey.hh
//    produced: 01/09/97 jr
// last change: 24/01/99 jr
//
////////////////////////////////////////////////////////////////////////////////
#ifndef HASHKEY_HH
#define HASHKEY_HH

template<class Key>
class HashKeySize {
public:
  inline size_type operator()(const Key& key) { return key.keysize(); }
};

template<class Key>
class HashKey {
public:
  inline size_type operator()(const Key& key, const size_type n) { return key.key(n); }
};

#endif
// eof HashKey.hh
