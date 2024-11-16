file(GLOB TOPCOM_SOURCES "*.cc")

add_library(topcom STATIC ${TOPCOM_SOURCES})

target_include_directories(topcom PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ../lib-src-reg ../wrap-gmp-gmpxx ${EXTERNAL_INCLUDES})

target_compile_features(topcom PUBLIC cxx_std_17)

target_compile_definitions(topcom PUBLIC ${TOPCOM_DEFINITIONS})

target_link_libraries(topcom PUBLIC ${GMP_PATH} ${GMPXX_PATH} ${CDD_PATH} ${CDDGMP_PATH} ${QSOPT_EX_PATH})
