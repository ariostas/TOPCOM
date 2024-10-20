#include <iostream>
#include <algorithm>
#include <iterator>
#include <set>
#include <map>
#include <tr1/unordered_set>
#include <tr1/unordered_map>
//#include <ext/hash_set>
//#include <ext/hash_map>
//#include <hash_set>
//#include <hash_map>
#include <vector>

#include <sys/times.h>
#include <time.h>
#include <unistd.h>
#include <limits.h>

#define WATCH_MAXCHAINLEN

////////////////////////////////////////////////////////////////////////////////
// the following class is used statically to keep track of elapsed times
// (C++-wrapper for the times()-function):
////////////////////////////////////////////////////////////////////////////////
class timer {
public:
  inline static double cpu_time(void) {
    struct tms now;

#ifndef CLK_TCK
    const int clocks_per_second = (int)sysconf(_SC_CLK_TCK);
#else
    const int clocks_per_second = (int)CLK_TCK;
#endif /* CLK_TCK */

    (void)times(&now);
   
    const int    hun   = ((now.tms_utime % clocks_per_second) * 100) / clocks_per_second;
    const int    sec   = (now.tms_utime / clocks_per_second);
    const double total = (double)sec + ((double)(hun) / 100.0);
   
    return(total);
  }

  inline static double system_time(void) {
    struct tms now;
   
#ifndef CLK_TCK
    const int clocks_per_second = (int)sysconf(_SC_CLK_TCK);
#else
    const int clocks_per_second = (int)CLK_TCK;
#endif /* CLK_TCK */
    
    (void)times(&now);
   
    const int    hun   = ((now.tms_stime % clocks_per_second) * 100) / clocks_per_second;
    const int    sec   = (now.tms_stime / clocks_per_second);
    const double total = (double)sec + ((double)(hun) / 100.0);
   
    return(total);
  }
};

#include "SimplicialComplex.hh"
#include "Permutation.hh"
#include "Symmetry.hh"
#include "Chirotope.hh"

typedef std::set< std::vector<int> > SimplicialComplexOfArrays;
typedef std::set<Simplex>            SimplicialComplexOfBitsets;
typedef SimplicialComplex            SimplicialComplexTOPCOM;

#if !defined (STL_CONTAINERS) && !defined (STL_SYMMETRIES) && !defined (STL_CHIROTOPE)

#include <tr1/unordered_map>
#include <tr1/unordered_set>

namespace std {
  namespace tr1 {
    template<>				
    struct hash<IntegerSet> {
      std::size_t operator()(const IntegerSet& is) const {
 	long res(0);
 	for (int i = 0; i < is.keysize(); ++i) {
 	  res ^= is.key(i);
 	}
 	return res;
      }
    };      
  };
};                                            
#endif

int main (const int argc, const char** argv) {
  long n(32), r(6), N(1000), M(100000), K(1);

  if (argc > 1) {

    // number of points:
    n = atol(argv[1]);
  }
  if (argc > 2) {

    // rank:
    r = atol(argv[2]);
  }
  if (argc > 3) {

    // typical number of simplices in a triangulation:
    N = atol(argv[3]);
  }
  if (argc > 4) {
    
    // typical number of triangulations:
    M = atol(argv[4]);
  }
  if (argc > 5) {
    
    // repeat this often:
    K = atol(argv[5]);
  }

  if ((n < 1) || (r < 1) || (N < 1) || (M < 1) || (K < 1)) {
    std::cerr << "Only positive parameters allowed!" << std::endl;
    exit(1);
  }

  std::cout << "Operations for " << n << " points in rank " << r << std::endl;
  
  long L(K*10000); // repeat factor for elementary operations

  SimplicialComplexOfArrays  sc11, sc12, sc13;
  SimplicialComplexOfBitsets sc21, sc22, sc23;
  SimplicialComplexTOPCOM    sc31, sc32, sc33;

  //////////////////////////////////////////////////////////////////////////////
  // create many simplices:
  //////////////////////////////////////////////////////////////////////////////

  std::cout << "Creating universe of simplices ..." << std::endl;
  std::vector<std::vector<int> > array_universe;
  std::vector<std::vector<int> > array_random_insert;
  std::vector<std::vector<int> > array_random_delete;
  std::vector<Simplex>      bitset_universe;
  std::vector<Simplex>      bitset_random_insert;
  std::vector<Simplex>      bitset_random_delete;
  SimplicialComplex    universe;

  Permutation p(n,r);
  long upper_bound(1000000L);
  do {
    universe.insert(Simplex(p));
  } while (p.lexnext() && (--upper_bound > 0));

  p = Permutation(n,r);
  
  long count_down(N);
  upper_bound = 1000000L;
  do {
    std::vector<int> new_simp;
    for (int i = 0; i < r; ++i) {
      new_simp.push_back(p[i]);
    }
    array_universe.push_back(new_simp);
    bitset_universe.push_back(Simplex(p));
    if (count_down > 0) {
      if (random() % 2) {
	array_random_insert.push_back(new_simp);
	bitset_random_insert.push_back(Simplex(p));
      }
      if (random() % 2) {
	array_random_delete.push_back(new_simp);
	bitset_random_delete.push_back(Simplex(p));
      }
      --count_down;
    }
  } while (p.lexnext() && (--upper_bound > 0));

  const std::vector<int> array_element  = *array_universe.begin();
  const Simplex     bitset_element = *bitset_universe.begin();

  std::cout << "#array_random_insert: \t" << array_random_insert.size() << std::endl;
  std::cout << "#bitset_random_insert: \t" << bitset_random_insert.size() << std::endl;
  std::cout << "#array_random_delete: \t" << array_random_delete.size() << std::endl;
  std::cout << "#bitset_random_delete: \t" << bitset_random_delete.size() << std::endl;
  std::cout << "#array_universe: \t" << array_universe.size() << std::endl;
  std::cout << "#bitset_universe: \t" << bitset_universe.size() << std::endl;

  std::cout << "... done." << std::endl << std::endl;

  timer t;
  double start, stop, durSoA, durSoB, durSCT;

  long increase(1);

  //////////////////////////////////////////////////////////////////////////////
  // insertion:
  //////////////////////////////////////////////////////////////////////////////

  std::cout << "==============================================================================" << std::endl;
  std::cout << 2 * increase * L << " times unique insertion of " << array_random_insert.size()
	    << " random elements:" << std::endl;
  std::cout << "------------------------------------------------------------------------------" << std::endl;

  std::cout << "SimplicialComplexOfArrays: \t";
  start = t.cpu_time();
  for (int i = 0; i < increase * L; ++i) {
    for (std::vector< std::vector<int> >::const_iterator iter = array_random_insert.begin();
	 iter != array_random_insert.end();
	 ++iter) {
      sc11.insert(*iter);
      sc12.insert(*iter);
    }
  }
  stop = t.cpu_time();
  durSoA = stop - start;

  std::cout << durSoA << " seconds (" << (durSoA * 100)/durSoA << "%)" << std::endl;
  std::cout << "#elements: " << sc11.size() << std::endl;

  std::cout << "SimplicialComplexOfBitsets: \t";
  start = t.cpu_time();
  for (int i = 0; i < increase * L; ++i) {
    for (std::vector<Simplex>::const_iterator iter = bitset_random_insert.begin();
	 iter != bitset_random_insert.end();
	 ++iter) {
      sc21.insert(*iter);
      sc22.insert(*iter);
    }
  }
  stop = t.cpu_time();
  durSoB = stop - start;

  std::cout << durSoB << " seconds (" << (durSoB * 100)/durSoA << "%)" << std::endl;
  std::cout << "#elements: " << sc21.size() << std::endl;

  std::cout << "SimplicialComplexTOPCOM: \t";
  start = t.cpu_time();
  for (int i = 0; i < increase * L; ++i) {
    for (std::vector<Simplex>::const_iterator iter = bitset_random_insert.begin();
	 iter != bitset_random_insert.end();
	 ++iter) {
      sc31.insert(*iter, r);
      sc32.insert(*iter, r);
    }
  }
  stop = t.cpu_time();
  durSCT = stop - start;
  std::cout << durSCT << " seconds (" << (durSCT * 100)/durSoA << "%)" << std::endl;
  std::cout << "#elements: " << sc31.card() << std::endl;

  //////////////////////////////////////////////////////////////////////////////
  // assignment:
  //////////////////////////////////////////////////////////////////////////////

  std::cout << "==============================================================================" << std::endl;
  std::cout << L << " times assignment of Simplicial Complex:" << std::endl;
  std::cout << "------------------------------------------------------------------------------" << std::endl;

  std::cout << "SimplicialComplexOfArrays: \t";
  start = t.cpu_time();
  for (int i = 0; i < L; ++i) {
    sc13 = sc11;
  }
  stop = t.cpu_time();
  durSoA = stop - start;
  std::cout << durSoA << " seconds (" << (durSoA * 100)/durSoA << "%)" << std::endl;

  std::cout << "SimplicialComplexOfBitsets: \t";
  start = t.cpu_time();
  for (int i = 0; i < L; ++i) {
    sc23 = sc21;
  }
  stop = t.cpu_time();
  durSoB = stop - start;
  std::cout << durSoB << " seconds (" << (durSoB * 100)/durSoA << "%)" << std::endl;

  std::cout << "SimplicialComplexTOPCOM: \t";
  start = t.cpu_time();
  for (int i = 0; i < L; ++i) {
    sc33 = sc31;
  }
  stop = t.cpu_time();
  durSCT = stop - start;
  std::cout << durSCT << " seconds (" << (durSCT * 100)/durSoA << "%)" << std::endl;

  //////////////////////////////////////////////////////////////////////////////
  // deletion:
  //////////////////////////////////////////////////////////////////////////////

  std::cout << "==============================================================================" << std::endl;
  std::cout << L << " times deletion of " << array_random_delete.size() 
	    << " random elements:" << std::endl;
  std::cout << "------------------------------------------------------------------------------" << std::endl;

  std::cout << "SimplicialComplexOfArrays: \t";
  start = t.cpu_time();
  for (int j = 0; j < L; ++j) {
    for (int i = 0; i < array_random_delete.size(); ++i) {
      sc12.erase(array_random_delete[i]);
    }
  }
  stop = t.cpu_time();
  durSoA = stop - start;
  std::cout << durSoA << " seconds (" << (durSoA * 100)/durSoA << "%)" << std::endl;
  std::cout << "#elements: " << sc12.size() << std::endl;

  std::cout << "SimplicialComplexOfBitsets: \t";
  start = t.cpu_time();
  for (int j = 0; j < L; ++j) {
    for (int i = 0; i < bitset_random_delete.size(); ++i) {
      sc22.erase(bitset_random_delete[i]);
    }
  }
  stop = t.cpu_time();
  durSoB = stop - start;
  std::cout << durSoB << " seconds (" << (durSoB * 100)/durSoA << "%)" << std::endl;
  std::cout << "#elements: " << sc22.size() << std::endl;

  std::cout << "SimplicialComplexTOPCOM: \t";
  start = t.cpu_time();
  for (int j = 0; j < L; ++j) {
    for (int i = 0; i < bitset_random_delete.size(); ++i) {
      sc32.erase(bitset_random_delete[i]);
    }
  }
  stop = t.cpu_time();
  durSCT = stop - start;
  std::cout << durSCT << " seconds (" << (durSCT * 100)/durSoA << "%)" << std::endl;
  std::cout << "#elements: " << sc32.card() << std::endl;

  //////////////////////////////////////////////////////////////////////////////
  // intersection:
  //////////////////////////////////////////////////////////////////////////////


  std::cout << "==============================================================================" << std::endl;
  std::cout << L << " times intersection of Simplicial Complexes:" << std::endl;
  std::cout << "------------------------------------------------------------------------------" << std::endl;

  std::cout << "SimplicialComplexOfArrays: \t";
  start = t.cpu_time();
  for (int i = 0; i < L; ++i) {
    sc13.clear();
    std::set_intersection< SimplicialComplexOfArrays::const_iterator,
      SimplicialComplexOfArrays::const_iterator,
      std::insert_iterator<SimplicialComplexOfArrays> >(sc11.begin(), 
							sc11.end(), 
							sc12.begin(), 
							sc12.end(), 
							std::insert_iterator<SimplicialComplexOfArrays>(sc13, sc13.begin()));
  }
  stop = t.cpu_time();
  durSoA = stop - start;
  std::cout << durSoA << " seconds (" << (durSoA * 100)/durSoA << "%)" << std::endl;
  std::cout << "#elements: " << sc13.size() << std::endl;

  std::cout << "SimplicialComplexOfBitsets: \t";
  start = t.cpu_time();

  for (int i = 0; i < L; ++i) {
    sc23.clear();
    std::set_intersection< SimplicialComplexOfBitsets::const_iterator,
      SimplicialComplexOfBitsets::const_iterator,
      std::insert_iterator<SimplicialComplexOfBitsets> >(sc21.begin(), 
							 sc21.end(), 
							 sc22.begin(), 
							 sc22.end(), 
							 std::insert_iterator<SimplicialComplexOfBitsets>(sc23, sc23.begin()));
  }
  stop = t.cpu_time();
  durSoB = stop - start;
  std::cout << durSoB << " seconds (" << (durSoB * 100)/durSoA << "%)" << std::endl;
  std::cout << "#elements: " << sc23.size() << std::endl;

  std::cout << "SimplicialComplexTOPCOM: \t";
  start = t.cpu_time();
  for (int i = 0; i < L; ++i) {
    sc33.clear();
    sc33 = sc31 * sc32;
  }
  stop = t.cpu_time();
  durSCT = stop - start;
  std::cout << durSCT << " seconds (" << (durSCT * 100)/durSoA << "%)" << std::endl;
  std::cout << "#elements: " << sc33.card() << std::endl;

  //////////////////////////////////////////////////////////////////////////////
  // comparison:
  //////////////////////////////////////////////////////////////////////////////
  
  increase = 10000;

  std::cout << "==============================================================================" << std::endl;
  std::cout << increase * L << " times comparison of Simplicial Complexes:" << std::endl;
  std::cout << "------------------------------------------------------------------------------" << std::endl;

  std::cout << "SimplicialComplexOfArrays: \t";
  start = t.cpu_time();
  for (int i = 0; i < increase * L; ++i) {
    if (sc11 < sc12) {
    }
  }
  stop = t.cpu_time();
  durSoA = stop - start;
  std::cout << durSoA << " seconds (" << (durSoA * 100)/durSoA << "%)" << std::endl;

  std::cout << "SimplicialComplexOfBitsets: \t";
  start = t.cpu_time();

  for (int i = 0; i < increase * L; ++i) {
    if (sc21 < sc22) {
    }
  }
  stop = t.cpu_time();
  durSoB = stop - start;
  std::cout << durSoB << " seconds (" << (durSoB * 100)/durSoA << "%)" << std::endl;

  std::cout << "SimplicialComplexTOPCOM: \t";
  start = t.cpu_time();
  for (int i = 0; i < increase * L; ++i) {
    if (sc31 < sc32) {
    }
  }
  stop = t.cpu_time();
  durSCT = stop - start;
  std::cout << durSCT << " seconds (" << (durSCT * 100)/durSoA << "%)" << std::endl;

  //////////////////////////////////////////////////////////////////////////////
  // cardinality:
  //////////////////////////////////////////////////////////////////////////////
  
  increase = 10000;
  
  sc11.erase(*sc11.begin());
  sc21.erase(*sc21.begin());
  sc31.erase(*sc31.begin());

  std::cout << "==============================================================================" << std::endl;
  std::cout << increase * L << " times cardinality of Simplicial Complexes:" << std::endl;
  std::cout << "------------------------------------------------------------------------------" << std::endl;

  std::cout << "SimplicialComplexOfArrays: \t";
  start = t.cpu_time();
  for (int i = 0; i < increase * L; ++i) {
    long card = sc11.size();
  }
  stop = t.cpu_time();
  durSoA = stop - start;
  std::cout << durSoA << " seconds (" << (durSoA * 100)/durSoA << "%)" << std::endl;

  std::cout << "SimplicialComplexOfBitsets: \t";
  start = t.cpu_time();

  for (int i = 0; i < increase * L; ++i) {
    long card = sc21.size();
  }
  stop = t.cpu_time();
  durSoB = stop - start;
  std::cout << durSoB << " seconds (" << (durSoB * 100)/durSoA << "%)" << std::endl;

  std::cout << "SimplicialComplexTOPCOM: \t";
  start = t.cpu_time();
  for (int i = 0; i < increase * L; ++i) {
    long card = sc31.card();
  }
  stop = t.cpu_time();
  durSCT = stop - start;
  std::cout << durSCT << " seconds (" << (durSCT * 100)/durSoA << "%)" << std::endl;

  //////////////////////////////////////////////////////////////////////////////
  // equality check `not equal':
  //////////////////////////////////////////////////////////////////////////////

  sc11.erase(*sc11.begin());
  sc21.erase(*sc21.begin());
  sc31.erase(*sc31.begin());

  increase = 100000L;

  std::cout << "==============================================================================" << std::endl;
  std::cout << increase * L << " times negative equality check of Simplicial Complexes:" << std::endl;
  std::cout << "------------------------------------------------------------------------------" << std::endl;

  std::cout << "SimplicialComplexOfArrays: \t";
  start = t.cpu_time();
  for (int i = 0; i < increase * L; ++i) {
    if (sc11 == sc12) {
      std::cout << "Error" << std::endl;
      exit(1);
    }
  }
  stop = t.cpu_time();
  durSoA = stop - start;
  std::cout << durSoA << " seconds (" << (durSoA * 100)/durSoA << "%)" << std::endl;

  std::cout << "SimplicialComplexOfBitsets: \t";
  start = t.cpu_time();

  for (int i = 0; i < increase * L; ++i) {
    if (sc21 == sc22) {
      std::cout << "Error" << std::endl;
      exit(1);
    }
  }
  stop = t.cpu_time();
  durSoB = stop - start;
  std::cout << durSoB << " seconds (" << (durSoB * 100)/durSoA << "%)" << std::endl;

  std::cout << "SimplicialComplexTOPCOM: \t";
  start = t.cpu_time();

  for (int i = 0; i < increase * L; ++i) {
    if (sc31 == sc32) {
      std::cout << "Error" << std::endl;
      exit(1);
    }
  }
  stop = t.cpu_time();
  durSCT = stop - start;
  std::cout << durSCT << " seconds (" << (durSCT * 100)/durSoA << "%)" << std::endl;

  //////////////////////////////////////////////////////////////////////////////
  // equality check `equal':
  //////////////////////////////////////////////////////////////////////////////

  increase = 100;

  std::cout << "==============================================================================" << std::endl;
  std::cout << increase * L << " times positive equality check of Simplicial Complexes:" << std::endl;
  std::cout << "------------------------------------------------------------------------------" << std::endl;

  std::cout << "SimplicialComplexOfArrays: \t";
  start = t.cpu_time();
  for (int i = 0; i < increase * L; ++i) {
    if (sc13 != sc12) {
      std::cout << "Error" << std::endl;
      exit(1);
    }
  }
  stop = t.cpu_time();
  double durSoA2 = stop - start;
  std::cout << durSoA2 << " seconds (" << (durSoA2 * 100)/durSoA << "% of negative equality check of SimplicialComplexofArrays)" << std::endl;

  std::cout << "SimplicialComplexOfBitsets: \t";
  start = t.cpu_time();

  for (int i = 0; i < increase * L; ++i) {
    if (sc23 != sc22) {
      std::cout << "Error" << std::endl;
      exit(1);
    }
  }
  stop = t.cpu_time();
  double durSoB2 = stop - start;
  std::cout << durSoB2 << " seconds (" << (durSoB2 * 100)/durSoA << "% of negative equality check of SimplicialComplexofArrays)" << std::endl;

  std::cout << "SimplicialComplexTOPCOM: \t";
  start = t.cpu_time();
  for (int i = 0; i < increase * L; ++i) {
    if (sc33 != sc32) {
      std::cout << "Error" << std::endl;
      exit(1);
    }
  }
  stop = t.cpu_time();
  double durSCT2 = stop - start;
  std::cout << durSCT2 << " seconds (" << (durSCT2 * 100)/durSoA << "% of negative equality check of SimplicialComplexofArrays)" << std::endl;

  //////////////////////////////////////////////////////////////////////////////
  // unique insert of new simplicial complexes into containers:
  //////////////////////////////////////////////////////////////////////////////

  std::vector<SimplicialComplexOfArrays>   sc_of_arrays_container;
  std::vector<SimplicialComplexOfBitsets>  sc_of_bitsets_container;
  std::vector<SimplicialComplexTOPCOM>     sc_TOPCOM_container;
  std::set<SimplicialComplexOfArrays>      sc_of_arrays_set;
  std::set<SimplicialComplexOfBitsets>     sc_of_bitsets_set;
  std::set<SimplicialComplexTOPCOM>        sc_TOPCOM_set;
  HashSet<SimplicialComplexTOPCOM>    sc_TOPCOM_hashset;
  
  std::cout << "==============================================================================" << std::endl;
  std::cout << K << " times unique insertion of " << std::min<double>(M, array_universe.size() * array_universe.size())
	    << " new elements into container:" << std::endl;
  std::cout << "------------------------------------------------------------------------------" << std::endl;

  std::cout << "SimplicialComplexOfArrays into STL-set: \t";
  count_down = M;
  for (std::vector< std::vector<int> >::const_iterator iter = array_universe.begin();
       (iter != array_universe.end() && (count_down > 0));
       ++iter) {
    sc12.insert(*iter);
    for (std::vector< std::vector<int> >::const_iterator iter2 = array_universe.begin();
	 (iter2 != array_universe.end() && (count_down > 0));
	 ++iter2, --count_down) {
      sc12.insert(*iter2);
      sc_of_arrays_container.push_back(sc12);
      sc12.erase(*iter2);
    }
    sc12.erase(*iter);
  }

  start = t.cpu_time();
  for (int i = 0; i < K; ++i) {
    sc_of_arrays_set.clear();
    for (std::vector<SimplicialComplexOfArrays>::reverse_iterator iter = sc_of_arrays_container.rbegin();
	 iter != sc_of_arrays_container.rend();
	 ++iter) {
      sc_of_arrays_set.insert(*iter);
    }
  }
  stop = t.cpu_time();
  std::cout << stop - start << " seconds" << std::endl;
  std::cout << "#elements: " << sc_of_arrays_set.size() << std::endl;
  sc_of_arrays_container.clear();
  sc_of_arrays_set.clear();

  std::cout << "SimplicialComplexOfBitsets into STL-set: \t";
  count_down = M;
  for (std::vector<Simplex>::const_iterator iter = bitset_universe.begin();
       ((iter != bitset_universe.end()) && (count_down > 0));
       ++iter) {
    sc22.insert(*iter);
    for (std::vector<Simplex>::const_iterator iter2 = bitset_universe.begin();
	 ((iter2 != bitset_universe.end()) && (count_down > 0));
	 ++iter2, --count_down) {
      sc22.insert(*iter2);
      sc_of_bitsets_container.push_back(sc22);
      sc22.erase(*iter2);
    }
    sc22.erase(*iter);
  }

  start = t.cpu_time();
  for (int i = 0; i < K; ++i) {
    sc_of_bitsets_set.clear();
    for (std::vector<SimplicialComplexOfBitsets>::reverse_iterator iter = sc_of_bitsets_container.rbegin();
	 iter != sc_of_bitsets_container.rend();
	 ++iter) {
      sc_of_bitsets_set.insert(*iter);
    }
  }
  stop = t.cpu_time();
  std::cout << stop - start << " seconds" << std::endl;
  std::cout << "#elements: " << sc_of_bitsets_set.size() << std::endl;
  sc_of_bitsets_container.clear();
  sc_of_bitsets_set.clear();

  std::cout << "SimplicialComplexTOPCOM into set: \t";
  count_down = M;
  for (std::vector<Simplex>::const_iterator iter = bitset_universe.begin();
       ((iter != bitset_universe.end()) && (count_down > 0));
       ++iter) {
    sc32.insert(*iter);
    for (std::vector<Simplex>::const_iterator iter2 = bitset_universe.begin();
	 ((iter2 != bitset_universe.end()) && (count_down > 0));
	 ++iter2, --count_down) {
      sc32.insert(*iter2);
      sc_TOPCOM_container.push_back(sc32);
      sc32.erase(*iter2);
    }
    sc32.erase(*iter);
  }

  start = t.cpu_time();
  for (int i = 0; i < K; ++i) {
    sc_TOPCOM_set.clear();
    for (std::vector<SimplicialComplexTOPCOM>::reverse_iterator iter = sc_TOPCOM_container.rbegin();
	 iter != sc_TOPCOM_container.rend();
	 ++iter) {
      sc_TOPCOM_set.insert(*iter);
    }
  }
  stop = t.cpu_time();
  std::cout << stop - start << " seconds" << std::endl;
  std::cout << "#elements: " << sc_TOPCOM_set.size() << std::endl;

  std::cout << "SimplicialComplexTOPCOM into TOPCOM-HashSet: \t";
  start = t.cpu_time();
  for (int i = 0; i < K; ++i) {
    count_down = M;
    sc_TOPCOM_hashset.clear();
    for (std::vector<SimplicialComplexTOPCOM>::reverse_iterator iter = sc_TOPCOM_container.rbegin();
	 ((iter != sc_TOPCOM_container.rend()) && (count_down > 0));
	 ++iter) {
      sc_TOPCOM_hashset.insert(*iter);
    }
  }
  stop = t.cpu_time();
  std::cout << stop - start << " seconds" << std::endl;
  std::cout << "#elements: " << sc_TOPCOM_hashset.load() << std::endl;
  sc_TOPCOM_container.clear();
  sc_TOPCOM_set.clear();
  sc_TOPCOM_hashset.clear();

  //////////////////////////////////////////////////////////////////////////////
  // access to chirotope values:
  //////////////////////////////////////////////////////////////////////////////

  increase = 100;

  std::map<Simplex, int>      chiro_via_map;
  HashMap<Simplex, int>  chiro_via_hashmap;
  std::tr1::unordered_map<Simplex, int> chiro_via_stl_hashmap;

  std::cout << "==============================================================================" << std::endl;
  std::cout << increase * K << " times store " << array_universe.size() <<  " chirotope values:" << std::endl;
  std::cout << "------------------------------------------------------------------------------" << std::endl;

  std::cout << "Chirotope as map: \t";
  start = t.cpu_time();
  for (int i = 0; i < increase * K; ++i) {
    for (int i = 1; i < array_universe.size(); ++i) {
      chiro_via_map[bitset_universe[i]] = i % 2;
    }
  }
  stop = t.cpu_time();
  std::cout << stop - start << " seconds" << std::endl;

  std::cout << "Chirotope as HashMap: \t";
  start = t.cpu_time();
  for (int i = 0; i < increase * K; ++i) {
    for (int i = 1; i < array_universe.size(); ++i) {
      chiro_via_hashmap[bitset_universe[i]] = i % 2;
    }
  }
  stop = t.cpu_time();
  std::cout << stop - start << " seconds" << std::endl;

  std::cout << "Chirotope as STL-hash_map: \t";
  start = t.cpu_time();
  for (int i = 0; i < increase * K; ++i) {
    for (int i = 1; i < array_universe.size(); ++i) {
      chiro_via_stl_hashmap[bitset_universe[i]] = i % 2;
    }
  }
  stop = t.cpu_time();
  std::cout << stop - start << " seconds" << std::endl;

  std::cout << "==============================================================================" << std::endl;
  std::cout << increase * K << " times retrieval of " << array_universe.size() << " chirotope values:" << std::endl;
  std::cout << "------------------------------------------------------------------------------" << std::endl;

  std::cout << "Chirotope as map: \t";
  start = t.cpu_time();
  for (int i = 0; i < increase * K; ++i) {
    for (int i = 1; i < array_universe.size(); ++i) {
      int result = chiro_via_map[bitset_universe[i]];
    }
  }
  stop = t.cpu_time();
  std::cout << stop - start << " seconds" << std::endl;

  std::cout << "Chirotope as HashMap: \t";
  start = t.cpu_time();

  for (int i = 0; i < increase * K; ++i) {
    for (int i = 1; i < array_universe.size(); ++i) {
      int result = chiro_via_hashmap[bitset_universe[i]];
    }
  }
  stop = t.cpu_time();
  std::cout << stop - start << " seconds" << std::endl;
  std::cout << "Maximal length of a chain in hashmap: " << chiro_via_hashmap.maxchainlen() << std::endl;

  std::cout << "Chirotope as STL-hash_map: \t";
  start = t.cpu_time();

  for (int i = 0; i < increase * K; ++i) {
    for (int i = 1; i < array_universe.size(); ++i) {
      int result = chiro_via_stl_hashmap[bitset_universe[i]];
    }
  }
  stop = t.cpu_time();
  std::cout << stop - start << " seconds" << std::endl;

  std::cout << "==============================================================================" << std::endl;

  return 0;
}
