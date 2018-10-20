cmake_minimum_required(VERSION 3.5)
project(pvr.mythtv)

set(APP_VERSION_MAJOR "19" CACHE STRING "Application version major")
set(APP_VERSION_MINOR "0" CACHE STRING "Application verison minor")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)

option(PACKAGE_ZIP "Package ZIP archive" ON)

# Make sure CORE_SYSTEM_NAME is set
if(NOT CORE_SYSTEM_NAME)
  if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(CORE_SYSTEM_NAME "osx")
  else()
    string(TOLOWER ${CMAKE_SYSTEM_NAME} CORE_SYSTEM_NAME)
  endif()
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_BINARY_DIR}/include
                    ${CMAKE_BINARY_DIR}/include/kodi
                    ${PROJECT_SOURCE_DIR}/lib/cppmyth/src)

add_definitions(-DUSE_DEMUX -D__STDC_FORMAT_MACROS -DBUILD_KODI_ADDON)
add_definitions(-DADDON_GLOBAL_VERSION_GUI_USED)
add_definitions(-DADDON_GLOBAL_VERSION_MAIN_USED)
add_definitions(-DADDON_INSTANCE_VERSION_PVR_USED)
add_definitions(-DBUILD_KODI_ADDON)

if(NOT WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wall")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -Wall")
else()
  add_definitions(-DTARGET_WINDOWS -D_WINSOCKAPI_
    -D_USE_32BIT_TIME_T -D_CRT_SECURE_NO_WARNINGS
    -D_SCL_SECURE_NO_WARNINGS -D__STDC_CONSTANT_MACROS)
  set(CMAKE_CXX_FLAGS_RELEASE "/MT /W3 /Od /RTC1 /EHsc")
  set(CMAKE_CXX_FLAGS_DEBUG "/MTd /W3 /Od /RTC1 /EHsc")
  set(CMAKE_C_FLAGS_RELEASE "/MT /W3")
  set(CMAKE_C_FLAGS_DEBUG "/MTd /W3")
endif()

file (GLOB MYTHTV_SOURCES
  src/demuxer/*.cpp
  src/cppmyth/*.cpp
  src/*.cpp)

file (GLOB MYTHTV_HEADERS
  src/demuxer/*.h
  src/cppmyth/*.h
  src/*.h)

include(addon-helpers)

add_subdirectory(lib/cppmyth)
add_subdirectory(lib/kodi)

set(DEPLIBS cppmyth)
if(WIN32)
  list(APPEND DEPLIBS ws2_32)
else()
  list(APPEND DEPLIBS m dl)
endif()

if(NOT WIN32 AND (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX))
  if(HAS_BUILTIN_SYNC_ADD_AND_FETCH)
    add_definitions("-DHAS_BUILTIN_SYNC_ADD_AND_FETCH")
  endif()
  if(HAS_BUILTIN_SYNC_SUB_AND_FETCH)
    add_definitions("-DHAS_BUILTIN_SYNC_SUB_AND_FETCH")
  endif()
endif()

set(BUILD_SHARED_LIBS ON)
build_addon(pvr.mythtv MYTHTV DEPLIBS)

include(CPack)
