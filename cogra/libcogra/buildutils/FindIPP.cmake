# - Find Intel IPP
# Find the IPP libraries
# Options:
#
#   IPP_STATIC: true if using static linking
#   IPP_MULTI_THREADED: true if using multi-threaded static linking
#
# This module defines the following variables:
#
#   IPP_FOUND       : True if IPP_INCLUDE_DIR are found
#   IPP_INCLUDE_DIR : where to find ipp.h, etc.
#   IPP_INCLUDE_DIRS: set when IPP_INCLUDE_DIR found
#   IPP_LIBRARIES   : the library to link against.
#
# taken from https://github.com/hanjianwei/cmake-modules by Jianwei Han, https://hanjianwei.com/


if(WIN32)
  set(IPP_ROOT "C:/Program Files (x86)/IntelSWTools/compilers_and_libraries/windows/ipp" CACHE PATH "Folder contains IPP")
else()
  set(IPP_ROOT /opt/intel/ipp CACHE PATH "Folder contains IPP")
endif()

# Find header file dir
find_path(IPP_INCLUDE_DIR ipp.h PATHS ${IPP_ROOT}/include)

# Find libraries

# Handle suffix
set(_IPP_ORIG_CMAKE_FIND_LIBRARY_SUFFIXES ${CMAKE_FIND_LIBRARY_SUFFIXES})

if(WIN32)
    set(CMAKE_FIND_LIBRARY_SUFFIXES .lib)
else()
    if(IPP_STATIC)
        set(CMAKE_FIND_LIBRARY_SUFFIXES .a)
    else()
        set(CMAKE_FIND_LIBRARY_SUFFIXES .so)
    endif()
endif()

if(IPP_STATIC)
    if(IPP_MULTI_THREADED)
        set(IPP_LIBNAME_SUFFIX _t)
    else()
        set(IPP_LIBNAME_SUFFIX _l)
    endif()
else()
    set(IPP_LIBNAME_SUFFIX "")
endif()

macro(find_ipp_library IPP_COMPONENT)
  string(TOLOWER ${IPP_COMPONENT} IPP_COMPONENT_LOWER)
  find_library(IPP_LIB_${IPP_COMPONENT} ipp${IPP_COMPONENT_LOWER}mt${IPP_LIBNAME_SUFFIX}
               PATHS ${IPP_ROOT}/lib/intel64/)
endmacro()

macro(find_ipp_library2 IPP_COMPONENT)
  string(TOLOWER ${IPP_COMPONENT} IPP_COMPONENT_LOWER)
  find_library(IPP_LIB_${IPP_COMPONENT} ipp${IPP_COMPONENT_LOWER}${IPP_LIBNAME_SUFFIX}
               PATHS ${IPP_ROOT}/lib/intel64/)
endmacro()


# IPP components
# Core
find_ipp_library(CORE)
# Color Conversion
find_ipp_library(CC)
# String Processing
find_ipp_library(CH)
# Computer Vision
find_ipp_library(CV)
# Data Compression
find_ipp_library(DC)
# Image Processing
find_ipp_library(I)
# Signal Processing
find_ipp_library(S)
# Vector Math
find_ipp_library(VM)
# Integrated Wrappers
find_ipp_library2(_IW)
set(IPP_LIBRARY
    ${IPP_LIB_CORE}
	${IPP_LIB_CC}
	${IPP_LIB_CH}
	${IPP_LIB_CV}
	${IPP_LIB_DC}
	${IPP_LIB_I}
	${IPP_LIB_S}
	${IPP_LIB_VM}
	${IPP_LIB__IW}
   )   

set(CMAKE_FIND_LIBRARY_SUFFIXES ${_IPP_ORIG_CMAKE_FIND_LIBRARY_SUFFIXES})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(IPP DEFAULT_MSG IPP_INCLUDE_DIR IPP_LIBRARY)

if (IPP_FOUND)
    set(IPP_INCLUDE_DIRS ${IPP_INCLUDE_DIR} PARENT_SCOPE)
    set(IPP_LIBRARIES ${IPP_LIBRARY} PARENT_SCOPE)
endif()

#mark_as_advanced(PART4_ROOT_DIR PART4_INCLUDE_DIR PART4_LIBRARY)