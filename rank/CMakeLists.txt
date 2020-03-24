Project(rank)

#-----------------------------------------------------------------------------
# rank version number, useful for packaging and doxygen doc:
# [VERSION <major>[.<minor>[.<patch>[.<tweak>]]]]
set(rank_VERSION_MAJOR 3)
set(rank_VERSION_MINOR 4)
set(rank_VERSION_PATCH 1)
set(rank_VERSION_TWEAK 2)
set(rank_VERSION
  "${rank_VERSION_MAJOR}.${rank_VERSION_MINOR}.${rank_VERSION_PATCH}")
set(PACKAGE_VERSION
  "${rank_VERSION_MAJOR}.${rank_VERSION_MINOR}.${rank_VERSION_BUILD}")

# version | soversion (API)
#   3.4.1 |  3
# above is the recommendation. If you really need to override this default,
# you can specify your own <PROJECT-NAME>_SOVERSION at cmake configuration time:
# cmake -D<PROJECT-NAME>_SOVERSION:STRING=42 /path/to/<PROJECT>
if(NOT DEFINED rank_SOVERSION)
  set(rank_SOVERSION 3)
endif(NOT DEFINED rank_SOVERSION)
message(------- ${rank_SOVERSION})
set(rank_LIBRARY_PROPERTIES
  VERSION   "${rank_VERSION}"
  SOVERSION "${rank_SOVERSION}"
)
#-----------------------------------------------------------------------------

# --------- set C++ version --  defined in uper level
#set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)

#-----------------------------------------------------------------------------
set ( HDR  
    ${CMAKE_CURRENT_SOURCE_DIR}/rank.h
)

set ( SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/rank.cpp
)

if (BUILD_SHARED_LIBS)
message("------------")
#set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
if (DEFINED CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS AND CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS)
    message("CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS is ON")
    set (NOT_NEED_DLLEXPORT ON)
else(DEFINED CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS  AND CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS) 
    message("CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS is OFF")
    set (NOT_NEED_DLLEXPORT OFF)
endif(DEFINED CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS  AND CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS)
message("------------")

if(WIN32)
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/rank.rc.in
  ${CMAKE_CURRENT_BINARY_DIR}/rank.rc
  NEWLINE_STYLE WIN32
  @ONLY
)

ENABLE_LANGUAGE(RC)
set(WIN32Rc ${CMAKE_CURRENT_BINARY_DIR}/rank.rc)
set (RCHDR  ${CMAKE_CURRENT_SOURCE_DIR}/Resource.h
            ${CMAKE_CURRENT_SOURCE_DIR}/targetver.h)

endif(WIN32)
endif(BUILD_SHARED_LIBS)


add_library(rank ${SRC} ${HDR} ${WIN32Rc} ${RCHDR})
include_directories(rank PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# ------------ add defines (/D) ----------------------------------------------
if (BUILD_SHARED_LIBS)
    if (NOT_NEED_DLLEXPORT)
        target_compile_definitions(rank
            PUBLIC  rank_DLL_EXPORTALL)
    else(NOT_NEED_DLLEXPORT)
        target_compile_definitions(rank
            PUBLIC  rank_DLL
            PRIVATE rank_EXPORTS )
endif(NOT_NEED_DLLEXPORT)
else(BUILD_SHARED_LIBS)
    target_compile_definitions(rank
        PUBLIC rank_STATIC_DEFINE)
endif(BUILD_SHARED_LIBS)    
#-----------------------------------------------------------------------------

#--------------- set version, soversion --------------------------------------
set_property(TARGET rank PROPERTY VERSION ${rank_VERSION})
set_property(TARGET rank PROPERTY SOVERSION ${rank_SOVERSION})
set_property(TARGET rank PROPERTY
  INTERFACE_rank_MAJOR_VERSION ${rank_SOVERSION})
set_property(TARGET rank APPEND PROPERTY
  COMPATIBLE_INTERFACE_STRING INTERFACE_rank_MAJOR_VERSION
)
#-----------------------------------------------------------------------------

#---- helper for generate LIBNAME_EXPORT defines
#include(GenerateExportHeader)
#generate_export_header(rank)
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
#---- install part -----------------------------------------------------------

# ---- result of target---
if (WIN32)
    install (TARGETS rank EXPORT rankExports
            LIBRARY DESTINATION bin 
            ARCHIVE DESTINATION lib
            RUNTIME DESTINATION bin
            INCLUDES DESTINATION include
    )
else (WIN32)
    install (TARGETS rank EXPORT rankExports
            LIBRARY DESTINATION lib 
            ARCHIVE DESTINATION lib
            RUNTIME DESTINATION bin 
            INCLUDES DESTINATION include
    )
endif (WIN32)
# ---------------------------------------------------

# ---- install include ------------------------------
install (FILES ${HDR} DESTINATION include)

# ---- configuration for finde_package --------------
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/rankConfigVersion.cmake"
  VERSION ${rank_VERSION}
  COMPATIBILITY AnyNewerVersion
)

export(TARGETS rank
        FILE "${CMAKE_CURRENT_BINARY_DIR}/rankConfig.cmake")

set(ConfigPackageLocation lib/cmake/rank)  
install (EXPORT rankExports
        FILE rankConfig.cmake
        DESTINATION ${ConfigPackageLocation})

install (FILES "${CMAKE_CURRENT_BINARY_DIR}/rankConfigVersion.cmake"
        DESTINATION ${ConfigPackageLocation})
#-----------------------------------------------------------------------------


#-----------------------------------------------------------------------------
# --- TESTS -----
if(BUILD_TESTING)
    add_subdirectory(tests)
endif(BUILD_TESTING)
#-----------------------------------------------------------------------------
