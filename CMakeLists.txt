cmake_minimum_required(VERSION 3.14...3.30)

project(TOPCOM
  VERSION
    1.1.2
  DESCRIPTION
    "Triangulations Of Point Configurations and Oriented Matroids"
  LANGUAGES
    CXX
)

# Try to find GMP and GMPXX
find_path(GMP_INCLUDE_DIR gmp.h
    PATHS
        $ENV{CONDA_PREFIX}/include
        /usr/include
        /usr/local/include
)
find_library(GMP_LIBRARY NAMES gmp
    PATHS
        $ENV{CONDA_PREFIX}/lib
        /usr/lib
        /usr/local/lib
)
find_path(GMPXX_INCLUDE_DIR gmpxx.h
    PATHS
        $ENV{CONDA_PREFIX}/include
        /usr/include
        /usr/local/include
)
find_library(GMPXX_LIBRARY NAMES gmpxx
    PATHS
        $ENV{CONDA_PREFIX}/lib
        /usr/lib
        /usr/local/lib
)
if (GMP_INCLUDE_DIR AND GMP_LIBRARY AND GMPXX_INCLUDE_DIR AND GMPXX_LIBRARY)
    message(STATUS "Found GMP and GMPXX")
    set(GMP_INCLUDE_DIRECTORIES ${GMP_INCLUDE_DIR} ${GMPXX_INCLUDE_DIR})
    set(GMP_LIBRARIES ${GMP_LIBRARY} ${GMPXX_LIBRARY})
else()
    message(FATAL_ERROR "Could not find GMP and GMPXX. Please set GMP_INCLUDE_DIR, GMP_LIBRARY, GMPXX_INCLUDE_DIR, and GMPXX_LIBRARY manually.")
endif()

# Try to find CDD and CDDGMP
find_path(CDD_INCLUDE_DIR cdd.h
    PATHS
        $ENV{CONDA_PREFIX}/include
        $ENV{CONDA_PREFIX}/include/cddlib
        /usr/include
        /usr/local/include
)
find_library(CDD_LIBRARY NAMES cdd
    PATHS
        $ENV{CONDA_PREFIX}/lib
        /usr/lib
        /usr/local/lib
)
find_library(CDDGMP_LIBRARY NAMES cddgmp
    PATHS
        $ENV{CONDA_PREFIX}/lib
        /usr/lib
        /usr/local/lib
)
if (CDD_INCLUDE_DIR AND CDD_LIBRARY AND CDDGMP_LIBRARY)
    message(STATUS "Found CDD and CDDGMP")
    set(CDD_LIBRARIES ${CDD_LIBRARY} ${CDDGMP_LIBRARY})
else()
    message(FATAL_ERROR "Could not find CDD and CDDGMP. Please set CDD_INCLUDE_DIR, CDD_LIBRARY, and CDDGMP_LIBRARY manually.")
endif()


set(TOPCOM_DEFINITIONS STL_SYMMETRIES STL_CONTAINERS STL_FLIPS STL_CHIROTOPE GMPRATIONAL PERMLIB_DOMAIN_INT USE_LEXORDER
PACKAGE="${PROJECT_NAME}" VERSION="${PROJECT_VERSION}")

add_subdirectory(lib-src)
add_subdirectory(lib-src-reg)

# Only build the executables if this is the main project
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  add_subdirectory(src)
  add_subdirectory(src-reg)
endif()
