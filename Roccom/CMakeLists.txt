cmake_minimum_required (VERSION 2.8)
project(Roccom)
ENABLE_LANGUAGE( CXX Fortran )
IF(NOT ENABLE_MPI)
  add_definitions( -DDUMMY_MPI )
ELSE()
  FIND_PACKAGE(MPI REQUIRED)
  add_definitions( -DMPICH_IGNORE_CXX_SEEK )
#  IF(MPI_CXX_COMPILER)
#    set (CMAKE_CXX_COMPILER ${MPI_CXX_COMPILER})
#  ENDIF(MPI_CXX_COMPILER)
ENDIF()
include(FortranCInterface)
FortranCInterface_HEADER(${PROJECT_SOURCE_DIR}/include/FC.h MACRO_NAMESPACE "FC_")
FortranCInterface_VERIFY(CXX QUIET)
set (BUILD_STATIC FALSE CACHE BOOL "Build static COM library")
set (ENABLE_MPI TRUE CACHE BOOL "Build with MPI Support")
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin CACHE PATH "Single directory for all executables.")
set (LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib CACHE PATH "Single directory for all libraries and archives.")
mark_as_advanced (LIBRARY_OUTPUT_PATH EXECUTABLE_OUTPUT_PATH)

#INCLUDE(CTest)

find_library(DL_LIB dl)
set (LIB_SRCS src/roccom_c.C src/assertion.C src/roccom_exception.C src/commpi.C src/Roccom_base.C src/Attribute.C src/Connectivity.C src/Window.C src/Pane.C src/Element_accessors.C)
set (FLIB_SRCS src/roccom_f.C src/m_pointers.f90 src/utilities.f90)
set (ALL_SRCS "${LIB_SRCS} ${FLIB_SRCS}")
set_source_files_properties(${ALL_SRCS} PROPERTIES COMPILE_FLAGS "-fPIC" )
#set(TEST_SRCS src/COMTest.C)

# rpath settings
SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

include_directories(include)

add_library(Roccomf STATIC ${FLIB_SRCS})

IF(NOT BUILD_STATIC)
  add_library(Roccom SHARED ${LIB_SRCS})
ELSE()
  add_library(Roccomf STATIC ${LIB_SRCS})
  add_definitions( -DSTATIC_LINK )
ENDIF()
target_link_libraries(Roccom ${DL_LIB})

add_subdirectory(Rocblas)
add_subdirectory(Rocin)
add_subdirectory(Rocout)
add_subdirectory(Rocmap)
add_subdirectory(Rocsurf)



#add_executable(testx ${TEST_SRCS})
#target_link_libraries(testx COM ${APPUTIL_LIB})

#ADD_TEST(RunAllTests ${EXECUTABLE_OUTPUT_PATH}/testx testresults.txt)
#ADD_TEST(TestObject:ValidHandle ${TEST_RESULTS} TestObject:ValidHandle testresults.txt)
#ADD_TEST(TestObject:Exists ${TEST_RESULTS} TestObject:Exists testresults.txt)

INSTALL(TARGETS Roccom Roccomf RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
