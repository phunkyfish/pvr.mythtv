project(pvr.mythtv)

cmake_minimum_required(VERSION 3.0.2)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR})

enable_language(CXX)
enable_language(C)

find_package(kodi REQUIRED)
find_package(kodiplatform REQUIRED)

include_directories(${kodiplatform_INCLUDE_DIRS}
                    ${KODI_INCLUDE_DIR}
                    ${CMAKE_BINARY_DIR}/include
                    ${PROJECT_SOURCE_DIR}/lib/cppmyth/src)

add_definitions(-DUSE_DEMUX -D__STDC_FORMAT_MACROS)

if(NOT WIN32)
  add_options(ALL_LANGUAGES ALL_BUILDS "-fPIC -Wall")
endif()

file (GLOB MYTHTV_SOURCES
  src/demuxer/*.cpp src/demuxer/*.h
  src/cppmyth/*.cpp src/cppmyth/*.h
  src/*.cpp src/*.h)

add_subdirectory(lib/cppmyth)
add_subdirectory(lib/p8-platform)

set(DEPLIBS ${p8-platform_LIBRARIES} cppmyth)
if(WIN32)
  list(APPEND DEPLIBS ws2_32)
else()
  list(APPEND DEPLIBS m)
endif()

if(NOT WIN32 AND (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX))
  if(HAS_BUILTIN_SYNC_ADD_AND_FETCH)
    add_options(ALL_LANGUAGES ALL_BUILDS "-DHAS_BUILTIN_SYNC_ADD_AND_FETCH")
  endif()
  if(HAS_BUILTIN_SYNC_SUB_AND_FETCH)
    add_options(ALL_LANGUAGES ALL_BUILDS "-DHAS_BUILTIN_SYNC_SUB_AND_FETCH")
  endif()
endif()

set(BUILD_SHARED_LIBS ON)
build_addon(pvr.mythtv MYTHTV DEPLIBS)

include(CPack)
