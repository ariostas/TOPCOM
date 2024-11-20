cmake_minimum_required(VERSION 3.14...3.30)

project(TOPCOM
  VERSION
    1.1.2
  DESCRIPTION
    "Triangulations Of Point Configurations and Oriented Matroids"
  LANGUAGES
    CXX
)

# Set up external dependencies
execute_process(COMMAND make -C ${CMAKE_CURRENT_SOURCE_DIR}/external)
find_path(EXTERNAL_INCLUDES gmp.h cdd.h PATHS external/include NO_DEFAULT_PATH)
find_library(GMP_PATH gmp PATHS external/lib NO_DEFAULT_PATH)
find_library(GMPXX_PATH gmpxx PATHS external/lib NO_DEFAULT_PATH)
find_library(CDD_PATH cdd PATHS external/lib NO_DEFAULT_PATH)
find_library(CDDGMP_PATH cddgmp PATHS external/lib NO_DEFAULT_PATH)
find_library(QSOPT_EX_PATH qsopt_ex PATHS external/lib NO_DEFAULT_PATH)

set(TOPCOM_DEFINITIONS STL_SYMMETRIES STL_CONTAINERS STL_FLIPS STL_CHIROTOPE GMPRATIONAL PERMLIB_DOMAIN_INT USE_LEXORDER
PACKAGE="${PROJECT_NAME}" VERSION="${PROJECT_VERSION}")

add_subdirectory(lib-src)
add_subdirectory(lib-src-reg)

# Only build the executables if this is the main project
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  add_subdirectory(src)
  add_subdirectory(src-reg)
endif()
