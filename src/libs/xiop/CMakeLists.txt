#==============================================================================#
#
#                      XIOS - http://metasophia.org/xios
#
#   This file is part of the XIOS, distributed under the ISC License.
#   Please see the LICENSE.txt file for details on copyright and licensing.
#
#==============================================================================#

SET( name ${XIOP_NAME} )

FILE( GLOB srcs "*.[ch]" )

IF( MSVC )
  LIST( APPEND srcs "XIOP.def" )
ENDIF()

ADD_LIBRARY( ${name} STATIC ${srcs} )

SET_TARGET_PROPERTIES( ${name} PROPERTIES OUTPUT_NAME ${XIOP_OUTPUT_NAME} )
