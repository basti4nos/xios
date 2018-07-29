#==============================================================================#
#
#                      XIOS - http://metasophia.org/xios
#
#   This file is part of the XIOS, distributed under the ISC License.
#   Please see the LICENSE.txt file for details on copyright and licensing.
#
#==============================================================================#

SET( name ${XIOS_CLIENT_GUI_NAME} )

FILE( GLOB srcs "*.[ch]pp" )

FIND_PACKAGE( Qt5Widgets REQUIRED )

IF( WIN32 )
  FIND_PACKAGE( Qt5WinExtras REQUIRED )
ENDIF()

SET( CMAKE_AUTOMOC ON )
SET( CMAKE_INCLUDE_CURRENT_DIR ON )

IF( WIN32 )
  ADD_EXECUTABLE( ${name} WIN32 ${srcs} )
  ADD_DEPENDENCIES( ${name} ${XIOC_NAME} )
  TARGET_LINK_LIBRARIES( ${name} ${XIOC_NAME} Qt5::Widgets Qt5::WinMain )
ELSE()
  ADD_EXECUTABLE( ${name} ${srcs} )
  ADD_DEPENDENCIES( ${name} ${XIOC_NAME} )
  TARGET_LINK_LIBRARIES( ${name} ${XIOC_NAME} Qt5::Widgets )
ENDIF()

SET_TARGET_PROPERTIES( ${name} PROPERTIES OUTPUT_NAME "${XIOS_CLIENT_GUI_OUTPUT_NAME}" )
