////////////////////////////////////////////////////////////////////////////////
// 
// CommandlineOptions.cc
//
//    produced: 04 Oct 1999 jr
// last change: 04 Oct 1999 jr
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include "CommandlineOptions.hh"

bool      CommandlineOptions::_verbose                 = false;
bool      CommandlineOptions::_debug                   = false;
bool      CommandlineOptions::_memopt                  = false;
bool      CommandlineOptions::_check                   = false;
bool      CommandlineOptions::_simple                  = false;
bool      CommandlineOptions::_neighborcount           = false;
bool      CommandlineOptions::_input_chiro             = false;
bool      CommandlineOptions::_fine_only               = false;
bool      CommandlineOptions::_reduce_points           = false;
bool      CommandlineOptions::_dont_add_points         = false;
bool      CommandlineOptions::_output_triangs          = false;
bool      CommandlineOptions::_compute_all             = false;
bool      CommandlineOptions::_preprocess              = false;
bool      CommandlineOptions::_check_regular           = false;
bool      CommandlineOptions::_check_sometimes         = false;
bool      CommandlineOptions::_ignore_symmetries       = false;
bool      CommandlineOptions::_symmetries_are_affine   = false;
bool      CommandlineOptions::_output_heights          = false;
bool      CommandlineOptions::_use_soplex              = false;
size_type CommandlineOptions::_sometimes_frequency     = 10000UL;
size_type CommandlineOptions::_chirocache              = 1000000UL;
size_type CommandlineOptions::_localcache              = 1000000UL;
size_type CommandlineOptions::_no_of_simplices         = 0L;
//polymake:Poly CommandlineOptions::_polymakeobj;

void CommandlineOptions::init(const int argc, const char** argv) {
  for (int i = 1; i < argc; ++i) {

    // print usage message:
    if ((strcmp(argv[i], "--help") == 0) || (strcmp(argv[i], "-h") == 0)) {
      std::cout << "Usage:" << std::endl;
      std::cout << argv[0] << "[options]" << std::endl;
      std::cout << "where the input is read from stdin" << std::endl;
      std::cout << "and the output is written to stdout." << std::endl;
      std::cout << std::endl;

      std::cout << "options concerning shell output:" << std::endl;
      std::cout << "-h or --help         : print this help message" << std::endl;
      std::cout << "-v                   : write verbose information to stderr." << std::endl;
      std::cout << "-d                   : write debug information to stderr." << std::endl;
      std::cout << "--heights            : write height vectors for triangulations to stdout (implies -r)." 
		<< std::endl;
      std::cout << std::endl;
     
      std::cout << "options for checking input:" << std::endl;
      std::cout << "--checktriang        : check any given triangulations for correctness." << std::endl;
      std::cout << std::endl;

      std::cout << "options for reporting properties of discovered triangulations:" << std::endl;
      std::cout << "--flipdeficiency     : report flip deficiency in triangulations to stderr." << std::endl;
      std::cout << "--frequency [n]      : check for regularity every [n]th triangulation and exit if regular." 
		<< std::endl;
      std::cout << std::endl;

      std::cout << "options concerning which triangulations are output (no influence on exploration):" << std::endl;
      std::cout << "--cardinality [n]    : count/output only triangulations of cardinality [n]." << std::endl;
      std::cout << std::endl;

      std::cout << "options concerning which triangulations are explored:" << std::endl;
      std::cout << "--regular            : consider only regular triangulations" << std::endl;
      std::cout << "--noinsertion        : never use a point that is unused in the seed triangulation." << std::endl;
      std::cout << "--reducepoints       : try to remove the number of use points, reported to stderr." << std::endl;
      std::cout << std::endl;

      std::cout << "options concerning symmetries:" << std::endl;
      std::cout << "--affine             : assume that given symmetries are affine." << std::endl;
      std::cout << "--nosymmetries       : ignore symmetries." << std::endl;
      std::cout << std::endl;

      std::cout << "options concerning internal behaviour:" << std::endl;
      std::cout << "--memopt             : try to reduce memory consumption." << std::endl;
      std::cout << "--chirocache [n]     : set the chirotope cache to [n] elements." << std::endl;
      std::cout << "--localcache [n]     : set the cache for local data to [n] elements ." << std::endl;
      std::cout << "--soplex             : use soplex for regularity checks." << std::endl;

      exit(0);
    }

    // output options:
    if (strcmp(argv[i], "-v") == 0) {
      _verbose = true;
    }
    if (strcmp(argv[i], "-d") == 0) {
      _debug = true;
    }
    if (strcmp(argv[i], "--heights") == 0) {
      _output_heights = true;
      _check_sometimes = false;
      _check_regular = true;
    }

    // options for checking input:
    if (strcmp(argv[i], "--checktriang") == 0) {
      _check = true;
    }

    // options for reporting properties of discovered triangulations:
    if (strcmp(argv[i], "--flipdeficiency") == 0) {
      _neighborcount = true;
    }
    if (strcmp(argv[i], "--frequency") == 0) {
      if (_check_regular) {
	std::cerr << "--frequency cannot be used with --regular, ignoring --frequency." << std::endl;
      }
      else {
	_check_regular = false;
	_check_sometimes = true;
	if (argc > i + 1) {
	  _sometimes_frequency = (size_type)atol(argv[i+1]);
	}
      }
    }

    // options concerning which triangulations are output (no influence on explorartion):
    if (strcmp(argv[i], "--cardinality") == 0) {
      if (argc > i + 1) {
	_no_of_simplices = (size_type)atol(argv[i+1]);
      }
    }

    // options concerning which triangulations are explored:
    if (strcmp(argv[i], "--regular") == 0) {
      if (_check_sometimes) {
	std::cerr << "--regular cannot be used with --frequency, ignoring --regular." << std::endl;
      }
      else {
	_check_sometimes = false;
	_check_regular = true;
      }
    }
    if (strcmp(argv[i], "--reducepoints") == 0) {
      _reduce_points = true;
    }
    if (strcmp(argv[i], "--noinsertion") == 0) {
      _dont_add_points = true;
    }

    // options concerning symmetries:
    if (strcmp(argv[i], "--affine") == 0) {
      _symmetries_are_affine = true;
    }
    if (strcmp(argv[i], "--nosymmetries") == 0) {
      _ignore_symmetries = true;
    }

    // options concerning internals:
    if (strcmp(argv[i], "--memopt") == 0) {
      _memopt = true;
    }
    if (strcmp(argv[i], "--chirocache") == 0) {
      if (argc > i + 1) {
	_chirocache = (size_type)atol(argv[i+1]);
      }
    }
    if (strcmp(argv[i], "--localcache") == 0) {
      if (argc > i + 1) {
	_localcache = (size_type)atol(argv[i+1]);
      }
    }
    if (strcmp(argv[i], "--soplex") == 0) {
#ifdef HAVE_LIBSOPLEX      
      _use_soplex = true;
#else
      std::cerr << "This binary was compiled without soplex support, ignoring --soplex." << std::endl;
#endif
    }

    // some options that are not documented:
    if (strcmp(argv[i], "-s") == 0) {
      _simple = true;
    }
    if (strcmp(argv[i], "-A") == 0) {
      _compute_all = true;
    }
    if (strcmp(argv[i], "-C") == 0) {
      _input_chiro = true;
    }
    if (strcmp(argv[i], "-F") == 0) {
      _fine_only = true;
    }
    if (strcmp(argv[i], "-O") == 0) {
      _output_triangs = true;
    }
    if (strcmp(argv[i], "-P") == 0) {
      _preprocess = true;
    }
  }
}

// eof CommandlineOptions.cc
