cmake_minimum_required(VERSION 3.5)
project(se)

set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

add_compile_options(-std=c++11)

include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)

aux_source_directory(${PROJECT_SOURCE_DIR}/src/base SE_BASE_FILES)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/network/http SE_HTTP_FILES)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/network/tcp SE_TCP_FILES)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/facepp SE_FACEPP_FILES)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/thread SE_THREAD_FILES)

add_library(se_base SHARED ${SE_BASE_FILES})
add_library(se_base_static STATIC ${SE_BASE_FILES})
set_target_properties(se_base_static PROPERTIES OUTPUT_NAME "se_base")

add_library(se_http SHARED ${SE_HTTP_FILES})
add_library(se_http_static STATIC ${SE_HTTP_FILES})
set_target_properties(se_http_static PROPERTIES OUTPUT_NAME "se_http")

target_link_libraries(se_http se_base curl)

add_library(se_facepp SHARED ${SE_FACEPP_FILES})
add_library(se_facepp_static STATIC ${SE_FACEPP_FILES})
set_target_properties(se_facepp_static PROPERTIES OUTPUT_NAME "se_facepp")
target_link_libraries(se_facepp se_base se_http jsoncpp)


add_library(se_tcp SHARED ${SE_TCP_FILES})
add_library(se_tcp_static STATIC ${SE_TCP_FILES})
set_target_properties(se_tcp_static PROPERTIES OUTPUT_NAME "se_tcp")
target_link_libraries(se_tcp se_base)


add_library(se_thread SHARED ${SE_THREAD_FILES})
add_library(se_thread_static STATIC ${SE_THREAD_FILES})
set_target_properties(se_thread_static PROPERTIES OUTPUT_NAME "se_thread")
target_link_libraries(se_thread pthread)


add_library(se SHARED ${SE_BASE_FILES} ${SE_THREAD_FILES} ${SE_HTTP_FILES} ${SE_FACEPP_FILES} ${SE_TCP_FILES})
add_library(se_static STATIC ${SE_BASE_FILES} ${SE_THREAD_FILES} ${SE_HTTP_FILES} ${SE_FACEPP_FILES} ${SE_TCP_FILES})
set_target_properties(se_static PROPERTIES OUTPUT_NAME "se")
target_link_libraries(se curl jsoncpp pthread)


add_executable(se_test main.cpp)
target_link_libraries(se_test se )

install(TARGETS se se_static se_base se_base_static se_http se_http_static se_facepp se_facepp_static se_tcp se_tcp_static se_thread se_thread_static
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
install(DIRECTORY ./include/se DESTINATION include)

