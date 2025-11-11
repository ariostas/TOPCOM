file(GLOB SOURCES "./*.cc")

foreach(SOURCE_FILE ${SOURCES})
    get_filename_component(EXEC_NAME ${SOURCE_FILE} NAME_WE)

    add_executable(${EXEC_NAME} ${SOURCE_FILE})

    target_compile_features(${EXEC_NAME} PRIVATE cxx_std_17)

    target_link_libraries(${EXEC_NAME} PRIVATE topcom checkreg)
endforeach()
