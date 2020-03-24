cmake_minimum_required (VERSION 3.12)
Project(Example2)

#------ set c++ standart ------------------------------------------------------
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
# set max warning level
if(MSVC)
  # Force to always compile with W4
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
  if(CMAKE_C_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
  else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  # Update if necessary
  if(NOT CMAKE_CXX_FLAGS MATCHES "-Wall")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
  endif()
  if(NOT CMAKE_C_FLAGS MATCHES "-Wall")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wno-long-long -pedantic")
  endif()
endif()
message("CMAKE_CXX_FLAGS: " ${CMAKE_CXX_FLAGS})
message("CMAKE_C_FLAGS: " ${CMAKE_C_FLAGS})
#------------------------------------------------------------------------------

#-----------------------------------------------------------------------------
# build configuration options.
option(BUILD_SHARED_LIBS "Global flag to cause add_library() to create shared libraries if on" OFF)
message("BUILD_SHARED_LIBS: " ${BUILD_SHARED_LIBS})

set (EXECUTABLE_OUTPUT_PATH ${Example2_BINARY_DIR}/bin CACHE PATH "Single output directory for building all executables.")
set (LIBRARY_OUTPUT_PATH ${Example2_BINARY_DIR}/bin CACHE PATH "Single output directory for building all libraries.")
mark_as_advanced(LIBRARY_OUTPUT_PATH EXECUTABLE_OUTPUT_PATH)

message("EXECUTABLE_OUTPUT_PATH: " ${EXECUTABLE_OUTPUT_PATH})
message("RUNTIME_OUTPUT_DIRECTORY_Debug: " ${RUNTIME_OUTPUT_DIRECTORY_Debug})
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
# declare BUILD_TESTING by default ON
# if don't want call test use: -DBUILD_TESTING=OFF 
include(CTest)
if(BUILD_TESTING) 
    message ("BUILD_TESTING ON")
else(BUILD_TESTING)
    message ("BUILD_TESTING OFF")
endif(BUILD_TESTING)
#-----------------------------------------------------------------------------

#----include sub directory of project ----------------------------------------

add_subdirectory(rank)
add_subdirectory(sample)

