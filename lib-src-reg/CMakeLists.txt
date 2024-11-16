file(GLOB CHECKREG_SOURCES "*.cc")

add_library(checkreg STATIC ${CHECKREG_SOURCES})

target_include_directories(checkreg PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ../lib-src ../wrap-gmp-gmpxx ${EXTERNAL_INCLUDES})

target_compile_features(checkreg PUBLIC cxx_std_17)

target_compile_definitions(checkreg PUBLIC ${TOPCOM_DEFINITIONS})

target_link_libraries(checkreg PUBLIC ${GMP_PATH} ${GMPXX_PATH} ${CDD_PATH} ${CDDGMP_PATH} ${QSOPT_EX_PATH})
