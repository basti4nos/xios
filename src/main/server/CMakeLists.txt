#==============================================================================#
#
#                      XIOS - http://metasophia.org/xios
#
#   This file is part of the XIOS, distributed under the ISC License.
#   Please see the LICENSE.txt file for details on copyright and licensing.
#
#==============================================================================#

SET( name ${XIOS_SERVER_NAME} )

FILE( GLOB srcs "*.[ch]pp" )

ADD_EXECUTABLE( ${name} ${srcs} )

TARGET_LINK_LIBRARIES( ${name} ${XIOS_NAME} ${POCO_LIBRARIES} )

SET_TARGET_PROPERTIES( ${name} PROPERTIES OUTPUT_NAME ${XIOS_SERVER_OUTPUT_NAME} )
