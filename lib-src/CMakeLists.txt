file(GLOB TOPCOM_SOURCES "*.cc")

add_library(topcom STATIC ${TOPCOM_SOURCES})

target_include_directories(topcom PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../lib-src-reg ${CMAKE_CURRENT_SOURCE_DIR}/../wrap-gmp-gmpxx ${GMP_INCLUDE_DIRECTORIES} ${CDD_INCLUDE_DIR})

target_compile_features(topcom PUBLIC cxx_std_17)

target_compile_definitions(topcom PUBLIC ${TOPCOM_DEFINITIONS})

target_link_libraries(topcom PUBLIC ${GMP_LIBRARIES} ${CDD_LIBRARY} ${CDDGMP_LIBRARY})
