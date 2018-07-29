#==============================================================================#
#
#                      XIOS - http://metasophia.org/xios
#
#   This file is part of the XIOS, distributed under the ISC License.
#   Please see the LICENSE.txt file for details on copyright and licensing.
#
#==============================================================================#

SET( name ${XIOS_MASTER_NAME} )

FILE( GLOB srcs "*.[ch]pp" )

ADD_EXECUTABLE( ${name} ${srcs} )

IF( BUILD_POCO )
  ADD_DEPENDENCIES( ${name} ${EXT_POCO_NAME} )
ENDIF()

ADD_DEPENDENCIES( ${name} ${XIOS_NAME} )

TARGET_LINK_LIBRARIES( ${name} ${POCO_LIBRARIES} ${XIOS_NAME} )

SET_TARGET_PROPERTIES( ${name} PROPERTIES OUTPUT_NAME ${XIOS_MASTER_OUTPUT_NAME} )
