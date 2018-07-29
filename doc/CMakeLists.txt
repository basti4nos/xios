#==============================================================================#
#
#                      XIOS - http://metasophia.org/xios
#
#   This file is part of the XIOS, distributed under the ISC License.
#   Please see the LICENSE.txt file for details on copyright and licensing.
#
#==============================================================================#

# Add custom target "make doc"
FIND_PACKAGE( Doxygen REQUIRED )
IF( DOXYGEN_FOUND )
  CONFIGURE_FILE( "Doxyfile.cmake" "Doxyfile" @ONLY )
  ADD_CUSTOM_TARGET( "doc"
    ${DOXYGEN_EXECUTABLE} "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} )
ENDIF()
