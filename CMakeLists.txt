cmake_minimum_required(VERSION 3.7)
project(se)

set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

add_compile_options(-std=c++11)

include_directories(./include)
link_directories(./lib)

aux_source_directory(./src/base SE_BASE_FILES)
aux_source_directory(./src/network/http SE_HTTP_FILES)

add_library(se_base ${SE_BASE_FILES})

add_library(se_http ${SE_HTTP_FILES})

target_link_libraries(se_http curl)


add_executable(se_test main.cpp)
target_link_libraries(se_test se_http)

