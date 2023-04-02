cmake_minimum_required(VERSION 3.10)
project(phoenix-shared-interface LANGUAGES CXX VERSION 0.0.1)

include(support/BuildSupport.cmake)

set(CMAKE_CXX_STANDARD 17)

option(PXC_ENABLE_ASAN "phoenix-shared: Enable sanitizers in debug builds." ON)
option(PXC_BUILD_SHARED "phoenix-shared: Build as a shared libary." OFF)

add_subdirectory(vendor/phoenix)

set(PXC_SOURCES )

bs_select_cflags(${PXC_ENABLE_ASAN} PXC_COMPILE_FLAGS PXC_LINK_FLAGS)

add_library(phoenix-shared SHARED)
set_target_properties(phoenix-shared PROPERTIES CXX_VISIBILITY_PRESET hidden VISIBILITY_INLINES_HIDDEN 1)

target_sources(phoenix-shared PRIVATE ${PXC_SOURCES})
target_include_directories(phoenix-shared PUBLIC include)
target_compile_options(phoenix-shared PRIVATE ${PXC_COMPILE_FLAGS})
target_link_options(phoenix-shared PRIVATE ${PXC_LINK_FLAGS})
target_link_libraries(phoenix-shared phoenix)
set_target_properties(phoenix-shared PROPERTIES DEBUG_POSTFIX "d" VERSION ${PROJECT_VERSION})

install(TARGETS phoenix-shared ARCHIVE LIBRARY RUNTIME)
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/phoenix" TYPE INCLUDE)
