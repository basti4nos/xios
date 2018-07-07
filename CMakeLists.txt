#==============================================================================#
#
#                      XIOS - http://metasophia.org/xios
#
#   This file is part of the XIOS, distributed under the ISC License.
#   Please see the LICENSE.txt file for details on copyright and licensing.
#
#==============================================================================#

CMAKE_MINIMUM_REQUIRED( VERSION 3.9.6 )

SET( CMAKE_DISABLE_SOURCE_CHANGES  ON )
SET( CMAKE_DISABLE_IN_SOURCE_BUILD ON )

PROJECT( XIOS VERSION 0.0.0 LANGUAGES C CXX )

#------------------------------------------------------------------------------#
#  Global Variables
#------------------------------------------------------------------------------#

SET( XIOS_ORGANIZATION "metasophia.org" )

STRING( TOLOWER ${PROJECT_NAME} PACKAGE_NAME )

SET( USE_POCO ON ) # Required

#------------------------------------------------------------------------------#
#  Project Options
#------------------------------------------------------------------------------#

OPTION( BUILD_POCO
  "Build The POCO C++ libraries." OFF )

OPTION( BUILD_XIOC
  "Build The XIOC library." ON )

OPTION( BUILD_CLI_CLIENT
  "Build The XIOS CLI client." ON )

OPTION( BUILD_GUI_CLIENT
  "Build The XIOS GUI client." OFF )

OPTION( ENABLE_MAKE_DOC
  "Enable generate documentation from source code with Doxygen." OFF )

OPTION( ENABLE_MAKE_TEST
  "Enable testing with CTest and dashboard submissions to CDash." OFF )

#------------------------------------------------------------------------------#
#  Project Modules
#------------------------------------------------------------------------------#

# libs/xioc
SET( XIOC_NAME "xioc" )
SET( XIOC_OUTPUT_NAME ${XIOC_NAME} )
# libs/xiop
SET( XIOP_NAME "xiop" )
SET( XIOP_OUTPUT_NAME ${XIOP_NAME} )
# libs/xios
SET( XIOS_NAME "xios" )
SET( XIOS_OUTPUT_NAME ${XIOS_NAME} )
# main/client/cli
SET( XIOS_CLIENT_CLI_NAME "${XIOS_NAME}-client.cli" )
SET( XIOS_CLIENT_CLI_OUTPUT_NAME "xiosh" )
# main/client/gui
SET( XIOS_CLIENT_GUI_NAME "${XIOS_NAME}-client.gui" )
SET( XIOS_CLIENT_GUI_OUTPUT_NAME "XIOS_Workbench" )
# main/master
SET( XIOS_MASTER_NAME "${XIOS_NAME}-master" )
SET( XIOS_MASTER_OUTPUT_NAME ${XIOS_MASTER_NAME} )
# main/server
SET( XIOS_SERVER_NAME "${XIOS_NAME}-server" )
SET( XIOS_SERVER_OUTPUT_NAME ${XIOS_SERVER_NAME} )
# main/worker
SET( XIOS_WORKER_NAME "${XIOS_NAME}-worker" )
SET( XIOS_WORKER_OUTPUT_NAME ${XIOS_WORKER_NAME} )
# test/tester
SET( XIOS_TESTER_NAME "${XIOS_NAME}-tester" )
SET( XIOS_TESTER_OUTPUT_NAME ${XIOS_TESTER_NAME} )

#------------------------------------------------------------------------------#
#  Check Environment
#------------------------------------------------------------------------------#

IF( NOT CMAKE_BUILD_TYPE )
  SET( CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose build type." FORCE )
ENDIF()

SET( CMAKE_C_STANDARD 11 )

SET( CMAKE_CXX_STANDARD 11 )
SET( CMAKE_CXX_STANDARD_REQUIRED ON )
SET( CMAKE_CXX_EXTENSIONS OFF )

INCLUDE( CheckFunctionExists )
CHECK_FUNCTION_EXISTS( "sysconf" HAVE_SYSCONF_FUNCTION )
CHECK_FUNCTION_EXISTS( "getgrnam_r" HAVE_GETGRNAM_R_FUNCTION )
CHECK_FUNCTION_EXISTS( "getpwnam_r" HAVE_GETPWNAM_R_FUNCTION )
CHECK_FUNCTION_EXISTS( "setgid" HAVE_SETGID_FUNCTION )
CHECK_FUNCTION_EXISTS( "setuid" HAVE_SETUID_FUNCTION )

#------------------------------------------------------------------------------#
#  External Projects
#------------------------------------------------------------------------------#

INCLUDE( ExternalProject )

SET( EXT_SOURCE_DIR "${CMAKE_SOURCE_DIR}/ext" )
SET( EXT_BINARY_DIR "${CMAKE_BINARY_DIR}/ext" )

# Poco
IF( USE_POCO )
  IF( BUILD_POCO )
    SET( EXT_POCO_NAME "ext-poco" )
    SET( EXT_POCO_PREFIX "${EXT_BINARY_DIR}/poco" )
    ExternalProject_Add(
      ${EXT_POCO_NAME}
      PREFIX ${EXT_POCO_PREFIX}
      URL "https://github.com/pocoproject/poco/archive/poco-1.8.1-release.zip"
      CMAKE_CACHE_ARGS
        "-DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>"
        "-DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}"
        "-DPOCO_STATIC:BOOL=OFF"
        "-DENABLE_XML:BOOL=ON"
        "-DENABLE_JSON:BOOL=ON"
        "-DENABLE_MONGODB:BOOL=OFF"
        "-DENABLE_REDIS:BOOL=OFF"
        "-DENABLE_PDF:BOOL=OFF"
        "-DENABLE_UTIL:BOOL=ON"
        "-DENABLE_NET:BOOL=ON"
        "-DENABLE_NETSSL:BOOL=OFF"
        "-DENABLE_NETSSL_WIN:BOOL=OFF"
        "-DENABLE_CRYPTO:BOOL=OFF"
        "-DENABLE_DATA:BOOL=OFF"
        "-DENABLE_DATA_SQLITE:BOOL=OFF"
        "-DENABLE_DATA_MYSQL:BOOL=OFF"
        "-DENABLE_DATA_ODBC:BOOL=OFF"
        "-DENABLE_SEVENZIP:BOOL=OFF"
        "-DENABLE_ZIP:BOOL=OFF"
        "-DENABLE_APACHECONNECTOR:BOOL=OFF"
        "-DENABLE_CPPPARSER:BOOL=OFF"
        "-DENABLE_POCODOC:BOOL=OFF"
        "-DENABLE_PAGECOMPILER:BOOL=OFF"
        "-DENABLE_PAGECOMPILER_FILE2PAGE:BOOL=OFF" )
    IF( WIN32 )
      IF( CMAKE_BUILD_TYPE STREQUAL "Debug" )
        SET( dlls
          "PocoFoundationd.dll"
          "PocoJSONd.dll"
          "PocoNetd.dll"
          "PocoUtild.dll"
          "PocoXMLd.dll" )
      ELSE()
        SET( dlls
          "PocoFoundation.dll"
          "PocoJSON.dll"
          "PocoNet.dll"
          "PocoUtil.dll"
          "PocoXML.dll" )
      ENDIF()
      ExternalProject_Add_Step(
        ext-poco post-install DEPENDEES install
        WORKING_DIRECTORY "${EXT_POCO_PREFIX}/bin"
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}"
        COMMAND ${CMAKE_COMMAND} -E copy ${dlls} "${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}" )
    ENDIF()
    INCLUDE_DIRECTORIES( "${EXT_POCO_PREFIX}/include" )
    LINK_DIRECTORIES( "${EXT_POCO_PREFIX}/lib" )
  ENDIF()
  IF( CMAKE_BUILD_TYPE STREQUAL "Debug" )
    SET( POCO_FOUNDATION_LIBRARY "PocoFoundationd" )
    SET( POCO_JSON_LIBRARY "PocoJSONd" )
    SET( POCO_NET_LIBRARY "PocoNetd" )
    SET( POCO_UTIL_LIBRARY "PocoUtild" )
    SET( POCO_XML_LIBRARY "PocoXMLd" )
  ELSE()
    SET( POCO_FOUNDATION_LIBRARY "PocoFoundation" )
    SET( POCO_JSON_LIBRARY "PocoJSON" )
    SET( POCO_NET_LIBRARY "PocoNet" )
    SET( POCO_UTIL_LIBRARY "PocoUtil" )
    SET( POCO_XML_LIBRARY "PocoXML" )
  ENDIF()
  SET( POCO_LIBRARIES
    ${POCO_FOUNDATION_LIBRARY}
    ${POCO_JSON_LIBRARY}
    ${POCO_NET_LIBRARY}
    ${POCO_UTIL_LIBRARY}
    ${POCO_XML_LIBRARY} )
ENDIF()

#------------------------------------------------------------------------------#
#  Subdirectories
#------------------------------------------------------------------------------#

FUNCTION( ADD_INCLUDE_DIRECTORY dir )
  INCLUDE_DIRECTORIES( BEFORE "${CMAKE_SOURCE_DIR}/${dir}" )
  INCLUDE_DIRECTORIES( BEFORE "${CMAKE_BINARY_DIR}/${dir}" )
ENDFUNCTION()

IF( WIN32 )
  SET( CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib" )
  SET( CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin" )
  SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin" )
ELSE()
  SET( CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib" )
  SET( CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib" )
  SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin" )
ENDIF()

# "make doc"
IF( ENABLE_MAKE_DOC )
  ADD_SUBDIRECTORY( "doc" )
ENDIF()

# "make test"
IF( ENABLE_MAKE_TEST )
  ENABLE_TESTING()
ENDIF()

# include directories
FOREACH( dir "include" "src/libs" )
  ADD_INCLUDE_DIRECTORY( ${dir} )
ENDFOREACH()

# all subdirectories
FOREACH( dir "include" "src/libs" "src/main" "src/test" "var" )
  ADD_SUBDIRECTORY( ${dir} )
ENDFOREACH()

#------------------------------------------------------------------------------#
#  Dependencies
#------------------------------------------------------------------------------#

IF( BUILD_POCO )
  IF( BUILD_CLI_CLIENT )
    ADD_DEPENDENCIES( ${XIOS_CLIENT_CLI_NAME} ${EXT_POCO_NAME} )
  ENDIF()
  ADD_DEPENDENCIES( ${XIOS_NAME} ${EXT_POCO_NAME} )
  ADD_DEPENDENCIES( ${XIOS_MASTER_NAME} ${EXT_POCO_NAME} )
  ADD_DEPENDENCIES( ${XIOS_SERVER_NAME} ${EXT_POCO_NAME} )
  ADD_DEPENDENCIES( ${XIOS_WORKER_NAME} ${EXT_POCO_NAME} )
  IF( ENABLE_MAKE_TEST )
    ADD_DEPENDENCIES( ${XIOS_TESTER_NAME} ${EXT_POCO_NAME} )
  ENDIF()
ENDIF()

IF( BUILD_XIOC )
  ADD_DEPENDENCIES( ${XIOC_NAME} ${XIOP_NAME} )
ENDIF()
IF( BUILD_CLI_CLIENT )
  ADD_DEPENDENCIES( ${XIOS_CLIENT_CLI_NAME} ${XIOC_NAME} )
ENDIF()
IF( BUILD_GUI_CLIENT )
  ADD_DEPENDENCIES( ${XIOS_CLIENT_GUI_NAME} ${XIOC_NAME} )
ENDIF()

IF( TRUE )
  ADD_DEPENDENCIES( ${XIOS_MASTER_NAME} ${XIOP_NAME} ${XIOS_NAME} )
  ADD_DEPENDENCIES( ${XIOS_SERVER_NAME} ${XIOP_NAME} ${XIOS_NAME} )
  ADD_DEPENDENCIES( ${XIOS_WORKER_NAME} ${XIOP_NAME} ${XIOS_NAME} )
ENDIF()
IF( ENABLE_MAKE_TEST )
  ADD_DEPENDENCIES( ${XIOS_TESTER_NAME} ${XIOP_NAME} ${XIOS_NAME} )
ENDIF()

#------------------------------------------------------------------------------#
#  CPack Package
#------------------------------------------------------------------------------#

SET( CPACK_PACKAGE_NAME ${PACKAGE_NAME} )
SET( CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR} )
SET( CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR} )
SET( CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH} )

INCLUDE( CPack )

#------------------------------------------------------------------------------#
#  Dump Variables
#------------------------------------------------------------------------------#

MESSAGE( STATUS "============================================================" )
MESSAGE( STATUS "PROJECT: ${PROJECT_NAME} ${PROJECT_VERSION}" )
MESSAGE( STATUS "BUILD_POCO: ${BUILD_POCO}" )
MESSAGE( STATUS "BUILD_XIOC: ${BUILD_XIOC}" )
MESSAGE( STATUS "BUILD_CLI_CLIENT: ${BUILD_CLI_CLIENT}" )
MESSAGE( STATUS "BUILD_GUI_CLIENT: ${BUILD_GUI_CLIENT}" )
MESSAGE( STATUS "ENABLE_MAKE_DOC: ${ENABLE_MAKE_DOC}" )
MESSAGE( STATUS "ENABLE_MAKE_TEST: ${ENABLE_MAKE_TEST}" )
MESSAGE( STATUS "------------------------------------------------------------" )
MESSAGE( STATUS "CMAKE_VERSION: ${CMAKE_VERSION}" )
MESSAGE( STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}" )
MESSAGE( STATUS "CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}" )
MESSAGE( STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}" )
MESSAGE( STATUS "CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}" )
MESSAGE( STATUS "CMAKE_C_FLAGS: ${CMAKE_C_FLAGS}" )
MESSAGE( STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}" )
MESSAGE( STATUS "CMAKE_EXE_LINKER_FLAGS: ${CMAKE_EXE_LINKER_FLAGS}" )
MESSAGE( STATUS "CMAKE_MODULE_LINKER_FLAGS: ${CMAKE_MODULE_LINKER_FLAGS}" )
MESSAGE( STATUS "CMAKE_SHARED_LINKER_FLAGS: ${CMAKE_SHARED_LINKER_FLAGS}" )
MESSAGE( STATUS "CMAKE_STATIC_LINKER_FLAGS: ${CMAKE_STATIC_LINKER_FLAGS}" )
MESSAGE( STATUS "INCLUDE_DIRECTORIES:" )
GET_PROPERTY( dirs DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES )
FOREACH( dir ${dirs} )
  MESSAGE( STATUS "  ${dir}" )
ENDFOREACH()
MESSAGE( STATUS "LINK_DIRECTORIES:" )
GET_PROPERTY( dirs DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY LINK_DIRECTORIES )
FOREACH( dir ${dirs} )
  MESSAGE( STATUS "  ${dir}" )
ENDFOREACH()
MESSAGE( STATUS "============================================================" )
