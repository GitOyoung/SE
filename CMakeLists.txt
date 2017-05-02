cmake_minimum_required(VERSION 3.6)
project(se)

set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

add_compile_options(-std=c++11)

include_directories(./include)
link_directories(./lib)

aux_source_directory(./src/base SE_BASE_FILES)
aux_source_directory(./src/network/http SE_HTTP_FILES)

add_library(se_base SHARED ${SE_BASE_FILES})
add_library(se_base_static STATIC ${SE_BASE_FILES})
set_target_properties(se_base_static PROPERTIES OUTPUT_NAME "se_base")

add_library(se_http SHARED ${SE_HTTP_FILES})
add_library(se_http_static STATIC ${SE_HTTP_FILES})
set_target_properties(se_http_static PROPERTIES OUTPUT_NAME "se_http")

target_link_libraries(se_http se_base curl)


add_executable(se_test main.cpp)
target_link_libraries(se_test se_base se_http)

install(TARGETS se_base se_http LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
install(DIRECTORY ./include/se DESTINATION include)

