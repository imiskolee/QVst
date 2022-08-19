cmake_minimum_required(VERSION 3.9.0)

#if(${CMAKE_MAJOR_VERSION} GREATER 2)
#    cmake_policy(SET CMP0042 OLD)
#    cmake_policy(SET CMP0043 OLD)
#    cmake_policy(SET CMP0054 OLD)
#endif()
#cmake_policy(SET CMP0020 OLD)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

project(QVst)

# Target directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/target/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/target/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# Installation destination
set(INSTALL_BIN_PATH ${CMAKE_INSTALL_PREFIX}/bin)
set(INSTALL_LIB_PATH ${CMAKE_INSTALL_PREFIX}/lib)
set(INSTALL_PATCHES_PATH ${CMAKE_INSTALL_PREFIX}/bin)

# CMake custom scripts
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

#set(CMAKE_VERBOSE_MAKEFILE on)

#add_definitions(-DUNICODE_OFF)
#add_definitions(-D_NATIVE_WCHAR_T_DEFINED)
#add_definitions(-D__wchar_t=wchar_t)
#add_definitions(-fpermissive)

# Process external libraries
add_subdirectory(externals)

# Process source code
add_subdirectory(source)
