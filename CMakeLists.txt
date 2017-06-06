cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Ofast")

set(CMAKE_CXX_STANDARD 11)

set(NO_QUADMATH FALSE CACHE BOOL "Prevent usage of libquadmath")
set(NO_OPENMP FALSE CACHE BOOL "Prevent usage of OpenMP")

if(NOT NO_OPENMP)
	find_package(OpenMP)
	if (OPENMP_FOUND)
		set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
		set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
		add_definitions(-DUSING_OPENMP)
	endif(OPENMP_FOUND)
endif(NOT NO_OPENMP)

include(CheckIncludeFiles)

########### FFTW
# - Find FFTW
# Find the native FFTW includes and library
#
#  FFTW_INCLUDES    - where to find fftw3.h
#  FFTW_LIBRARIES   - List of libraries when using FFTW.
#  FFTW_FOUND       - True if FFTW found.

if (FFTW_INCLUDES)
	# Already in cache, be silent
	set (FFTW_FIND_QUIETLY TRUE)
endif (FFTW_INCLUDES)

find_path (FFTW_INCLUDES fftw3.h)

find_library (FFTW_LIBRARIES NAMES fftw3)

# handle the QUIETLY and REQUIRED arguments and set FFTW_FOUND to TRUE if
# all listed variables are TRUE
include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (FFTW DEFAULT_MSG FFTW_LIBRARIES FFTW_INCLUDES)

mark_as_advanced (FFTW_LIBRARIES FFTW_INCLUDES)
########### End FFTW

########### libquadmath

if(NOT NO_QUADMATH)

	check_include_files(quadmath.h HAS_QUADMATH_H)
	if (HAS_QUADMATH_H)
		add_definitions(-DUSING_QUADMATH)
	endif (HAS_QUADMATH_H)

endif(NOT NO_QUADMATH)

########## End libquadmath

########## Argument handler

add_library(handle STATIC libs/handle.c)

########## End argument handler


add_library(complex STATIC complex.cpp)
if(HAS_QUADMATH_H)
	target_link_libraries(complex quadmath)
endif(HAS_QUADMATH_H)
add_library(state STATIC state.cpp)
add_library(lattice STATIC lattice.cpp)
target_link_libraries(lattice state)

add_executable(test-complex test-complex.cpp)
target_link_libraries(test-complex -lm complex state lattice)

add_executable(evolve evolve.cpp)
target_link_libraries(evolve -lm complex state lattice handle)
# TODO add back ${FFTW_LIBRARIES} to linked libraries when necessary

install(TARGETS evolve DESTINATION bin)
