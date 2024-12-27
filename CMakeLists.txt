cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(COMPILE_FLAGS -O2 -ffast-math)

project(native)

add_library(${PROJECT_NAME}
    SHARED
        library/native.cpp
        library/fastmath.cpp
)

find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${JNI_LIBRARIES})
target_compile_options(${PROJECT_NAME}
    PRIVATE
        ${COMPILE_FLAGS}
)

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/out"
)

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:${PROJECT_NAME}>
        "${CMAKE_CURRENT_SOURCE_DIR}/out"
)