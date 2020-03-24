Project(Sample)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#-----------------------------------------------------------------------------
set ( SRC_main 
    ${CMAKE_CURRENT_SOURCE_DIR}/sample.cpp
)
#include_directories(${CMAKE_SOURCE_DIR}/rank)
add_executable(Sample ${SRC_main})
target_include_directories(Sample PUBLIC ${CMAKE_SOURCE_DIR}/rank)
target_link_libraries(Sample rank)

install (TARGETS Sample DESTINATION bin)