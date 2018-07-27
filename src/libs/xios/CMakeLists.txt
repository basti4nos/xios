#==============================================================================#
#
#                      XIOS - http://metasophia.org/xios
#
#   This file is part of the XIOS, distributed under the ISC License.
#   Please see the LICENSE.txt file for details on copyright and licensing.
#
#==============================================================================#

SET( name ${XIOS_NAME} )

CONFIGURE_FILE( "Config.h.cmake" "Config.h" @ONLY )

FILE( GLOB_RECURSE srcs "*.[ch]" "*.[ch]pp" )

IF( MSVC )
  LIST( APPEND srcs "XIOS.def" )
ENDIF()

ADD_LIBRARY( ${name} SHARED ${srcs} )

IF( BUILD_POCO )
  ADD_DEPENDENCIES( ${name} ${EXT_POCO_NAME} )
ENDIF()

TARGET_LINK_LIBRARIES( ${name} ${POCO_LIBRARIES} )

SET_TARGET_PROPERTIES( ${name} PROPERTIES OUTPUT_NAME ${XIOS_OUTPUT_NAME} )
