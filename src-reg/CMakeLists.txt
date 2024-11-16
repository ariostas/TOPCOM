file(GLOB SOURCES "./*.cc")

foreach(SOURCE_FILE ${SOURCES})
    get_filename_component(EXEC_NAME ${SOURCE_FILE} NAME_WE)

    add_executable(${EXEC_NAME} ${SOURCE_FILE})

    target_include_directories(${EXEC_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ../lib-src ../wrap-gmp-gmpxx ${EXTERNAL_INCLUDES})

    target_compile_features(${EXEC_NAME} PRIVATE cxx_std_17)

    target_compile_definitions(${EXEC_NAME} PRIVATE ${TOPCOM_DEFINITIONS})

    target_link_libraries(${EXEC_NAME} PRIVATE ${GMP_PATH} ${GMPXX_PATH} ${CDD_PATH} ${CDDGMP_PATH} ${QSOPT_EX_PATH} topcom checkreg)
endforeach()
