cmake_minimum_required(VERSION 3.14...3.30)

project(TOPCOM
  VERSION
    1.1.2
  DESCRIPTION
    "Triangulations Of Point Configurations and Oriented Matroids"
  LANGUAGES
    CXX
)

execute_process(COMMAND make -C external)

add_subdirectory(lib-src)