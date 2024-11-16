file(GLOB libTOPCOM_SOURCES "*.cc")

add_library(libTOPCOM STATIC ${libTOPCOM_SOURCES})

target_include_directories(libTOPCOM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ../lib-src-reg ../wrap-gmp-gmpxx ../external/gmpxx-patch )

target_compile_features(libTOPCOM PUBLIC cxx_std_17)

target_compile_definitions(libTOPCOM PUBLIC STL_SYMMETRIES STL_CONTAINERS STL_FLIPS STL_CHIROTOPE GMPRATIONAL PERMLIB_DOMAIN_INT USE_LEXORDER
PACKAGE="${PROJECT_NAME}" VERSION="${PROJECT_VERSION}")
