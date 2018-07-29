#==============================================================================#
#
#                      XIOS - http://metasophia.org/xios
#
#   This file is part of the XIOS, distributed under the ISC License.
#   Please see the LICENSE.txt file for details on copyright and licensing.
#
#==============================================================================#

SET( name ${XIOS_WORKER_NAME} )

FILE( GLOB srcs "*.[ch]pp" )

ADD_EXECUTABLE( ${name} ${srcs} )

IF( BUILD_POCO )
  ADD_DEPENDENCIES( ${name} ${EXT_POCO_NAME} )
ENDIF()

ADD_DEPENDENCIES( ${name} ${XIOS_NAME} )

TARGET_LINK_LIBRARIES( ${name} ${POCO_LIBRARIES} ${XIOS_NAME} )

SET_TARGET_PROPERTIES( ${name} PROPERTIES OUTPUT_NAME ${XIOS_WORKER_OUTPUT_NAME} )

# Add libs/* sub-directories
FILE( GLOB dirs RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "libs/*" )
FOREACH( dir ${dirs} )
  IF( IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${dir}" )
    ADD_SUBDIRECTORY( ${dir} )
  ENDIF()
ENDFOREACH()
