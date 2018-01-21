#==============================================================================#
#
#                      XIOS - http://metasophia.org/xios
#
#   This file is part of the XIOS, distributed under the ISC License.
#   Please see the LICENSE.txt file for details on copyright and licensing.
#
#==============================================================================#

SET( NAME ${XIOS_MASTER_NAME} )

FILE( GLOB SRCS "*.[ch]pp" )

ADD_EXECUTABLE( ${NAME} ${SRCS} )

TARGET_LINK_LIBRARIES( ${NAME} ${POCO_LIBRARIES} )

SET_TARGET_PROPERTIES( ${NAME} PROPERTIES OUTPUT_NAME ${XIOS_MASTER_OUTPUT_NAME} )
