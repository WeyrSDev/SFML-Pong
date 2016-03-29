cmake_minimum_required(VERSION 3.2)

# Specify default build type if none provided (before project() command)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

project(Pong)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
  add_definitions(-D_DEBUG)
endif()
set(EXE_NAME "Pong-${CMAKE_BUILD_TYPE}")

# if MinGW is used, set a different binary output directory
# to manage different dll versions between VS and MinGW compiler
if(MINGW)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin-mingw)
else()
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
endif()

include_directories(src)
set(SOURCE_FILES src/Main.cpp)

# this adds the CMakeLists.txt from the specific subdirs to the project
add_subdirectory(src/engine)
add_subdirectory(src/game)
add_subdirectory(src/states)

add_executable(${EXE_NAME} ${SOURCE_FILES})

# add libpthread to link libraries if compiler is GCC
# this action requires cmake 3.2
if (CMAKE_COMPILER_IS_GNUCXX)
  set(THREADS_PREFER_PTHREAD_FLAG ON)
  find_package(Threads REQUIRED)
  target_link_libraries(${EXE_NAME} Threads::Threads)
endif ()

# find and add SFML to the project
# if cmake can't find your SFML installation make sure to set SFML_ROOT
find_package(SFML 2.3 REQUIRED graphics window system audio)
if (SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXE_NAME} ${SFML_LIBRARIES})
endif ()