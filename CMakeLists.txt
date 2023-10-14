cmake_minimum_required(VERSION 3.10)
project(phoenix-shared-interface LANGUAGES CXX VERSION 0.0.1)

include(support/BuildSupport.cmake)

set(CMAKE_CXX_STANDARD 17)

if (NOT MSVC)
    # Make sure everything is relocatable.
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
endif ()

option(PXC_ENABLE_ASAN "phoenix-shared: Enable sanitizers in debug builds." ON)

add_subdirectory(vendor/phoenix)

set(PXC_SOURCES
        src/Animation.cc
        src/BspTree.cc
        src/Buffer.cc
        src/Cutscene.cc
        src/DaedalusScript.cc
        src/Vm.cc
        src/Font.cc
        src/Logging.cc
        src/Material.cc
        src/Mesh.cc
        src/Model.cc
        src/ModelHierarchy.cc
        src/ModelMesh.cc
        src/ModelScript.cc
        src/MorphMesh.cc
        src/MultiResolutionMesh.cc
        src/Texture.cc
        src/Vfs.cc
        src/World.cc)

bs_select_cflags(${PXC_ENABLE_ASAN} PXC_COMPILE_FLAGS PXC_LINK_FLAGS)

add_library(phoenix-shared SHARED)
set_target_properties(phoenix-shared PROPERTIES CXX_VISIBILITY_PRESET hidden VISIBILITY_INLINES_HIDDEN 1)

target_sources(phoenix-shared PRIVATE ${PXC_SOURCES})
target_include_directories(phoenix-shared PUBLIC include)
target_compile_options(phoenix-shared PRIVATE ${PXC_COMPILE_FLAGS})
target_compile_definitions(phoenix-shared PRIVATE PXC_EXPORTS=1)
target_link_options(phoenix-shared PRIVATE ${PXC_LINK_FLAGS})
target_link_libraries(phoenix-shared phoenix)
set_target_properties(phoenix-shared PROPERTIES DEBUG_POSTFIX "d" VERSION ${PROJECT_VERSION})

if (MINGW)
    # We need to "bake" standard C/C++ libraries and windows pthread into DLL
    # Otherwise we need to distribute up to 3 dlls within the same folder.
    # If we don't do any of this, we'll get the following error (or a similar one):
    # -> The procedure entry point _ZNKSt7codecvtlwc9_MbstatetE10do_unshiftERS0_PcS3_RS3_ could not be located in the dynamic link library [...]\build\test_lib.exe
    # -> Dll couldn't be loaded as dependencies are missing.
    target_link_options(phoenix-shared PUBLIC "-static")
endif()

install(TARGETS phoenix-shared ARCHIVE LIBRARY RUNTIME)
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/phoenix" TYPE INCLUDE)
