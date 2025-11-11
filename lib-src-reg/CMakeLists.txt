file(GLOB CHECKREG_SOURCES "*.cc")

add_library(checkreg STATIC ${CHECKREG_SOURCES})

target_include_directories(checkreg PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../lib-src ${CMAKE_CURRENT_SOURCE_DIR}/../wrap-gmp-gmpxx ${GMP_INCLUDE_DIRECTORIES} ${CDD_INCLUDE_DIR})

target_compile_features(checkreg PUBLIC cxx_std_17)

target_compile_definitions(checkreg PUBLIC ${TOPCOM_DEFINITIONS})
