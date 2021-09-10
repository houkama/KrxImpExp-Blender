#############################################################################
# Name:        CMakeLists.txt
# Purpose:     Primary CMake for KrxImpExp's wxImpExpUI
# Author:      houkama
# Created:     2021-09-10
# Copyright:   houkama
# Licence:     GNU GPL 3
#############################################################################

cmake_minimum_required(VERSION 2.8.12)

MESSAGE("Cmake Generator: ${CMAKE_GENERATOR}")

# Create directories to build and install wxWidgets
execute_process(COMMAND mkdir external
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
execute_process(COMMAND mkdir wxWidgets-build
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/external)
execute_process(COMMAND mkdir wxWidgets-install
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/external)

# create makefiles for wxWidgets
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" -A x64 ${CMAKE_BINARY_DIR}/../external/wxWidgets -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_BINARY_DIR}/external/wxWidgets-install -DwxBUILD_MONOLITHIC:BOOL=1 -DwxBUILD_SHARED:BOOL=0
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/external/wxWidgets-build)

# make and install wxWidgets
execute_process(COMMAND ${CMAKE_COMMAND} --build . --target install --config release
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/external/wxWidgets-build)

project(wxImpExpUI)

# https://blog.kitware.com/cmake-and-the-default-build-type/
# Set a default build type if none was specified
set(default_build_type "Release")
#if(EXISTS "${CMAKE_SOURCE_DIR}/.git")
#  set(default_build_type "Debug")
#endif()
 
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
      STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

include_directories(${CMAKE_BINARY_DIR}/external/wxWidgets-install/include)
include_directories(${CMAKE_BINARY_DIR}/external/wxWidgets-install/lib/vc_x64_lib/mswu)

set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

include_directories(${SOURCE_DIR}/MetaCpp)
include_directories(${SOURCE_DIR}/tstl)
include_directories(${SOURCE_DIR}/gfx)
include_directories(${SOURCE_DIR}/Meta)

FILE(GLOB CPP_FILES ${SOURCE_DIR}/wxImpExpUI/*.cpp)
FILE(GLOB HEADER ${SOURCE_DIR}/wxImpExpUI/*.h)
FILE(GLOB METAHEADER ${SOURCE_DIR}/MetaCpp/*.h)

ADD_EXECUTABLE(wxImpExpUI WIN32
                ${HEADER}
                ${METAHEADER}
                ${CPP_FILES}
                ${SOURCE_DIR}/wxImpExpUI/ImpExpUIApp.rc
                ${SOURCE_DIR}/Meta/3dsExporterDlgInput.meta
                ${SOURCE_DIR}/Meta/3dsExporterDlgOutput.meta
                ${SOURCE_DIR}/Meta/3dsImporterDefs.meta
                ${SOURCE_DIR}/Meta/3dsImporterDlgInput.meta
                ${SOURCE_DIR}/Meta/3dsImporterDlgOutput.meta
                ${SOURCE_DIR}/Meta/AscExporterDlgInput.meta
                ${SOURCE_DIR}/Meta/AscExporterDlgOutput.meta
                ${SOURCE_DIR}/Meta/AscImporterDefs.meta
                ${SOURCE_DIR}/Meta/AscImporterDlgInput.meta
                ${SOURCE_DIR}/Meta/AscImporterDlgOutput.meta
                ${SOURCE_DIR}/Meta/File.meta
                ${SOURCE_DIR}/Meta/FormatMsg.meta
                ${SOURCE_DIR}/Meta/MeshInfoDlgInput.meta
                ${SOURCE_DIR}/Meta/ModelHierarchy.meta
                ${SOURCE_DIR}/Meta/ObjectStats.meta
)

target_link_directories(wxImpExpUI PUBLIC ${CMAKE_BINARY_DIR}/external/wxWidgets-install/lib/vc_x64_lib)

target_link_libraries(wxImpExpUI comctl32.lib
                                rpcrt4.lib
                                wxexpat.lib
                                wxjpeg.lib
                                wxmsw31u.lib
                                wxpng.lib
                                wxregexu.lib
                                wxscintilla.lib
                                wxtiff.lib
                                wxzlib.lib)