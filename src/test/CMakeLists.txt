#==============================================================================#
#
#                      XIOS - http://metasophia.org/xios
#
#   This file is part of the XIOS, distributed under the ISC License.
#   Please see the LICENSE.txt file for details on copyright and licensing.
#
#==============================================================================#

IF( ENABLE_MAKE_TEST )
  # Add sub-directories
  FILE( GLOB dirs RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*" )
  LIST( SORT dirs )
  FOREACH( dir ${dirs} )
    IF( IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${dir}" )
      ADD_SUBDIRECTORY( ${dir} )
    ENDIF()
  ENDFOREACH()
ENDIF()
