#==============================================================================#
#
#                      XIOS - http://metasophia.org/xios
#
#   This file is part of the XIOS, distributed under the ISC License.
#   Please see the LICENSE.txt file for details on copyright and licensing.
#
#==============================================================================#

IF( BUILD_CLI_CLIENT )
  ADD_SUBDIRECTORY( "client/cli" )
ENDIF()
IF( BUILD_GUI_CLIENT )
  ADD_SUBDIRECTORY( "client/gui" )
ENDIF()

ADD_SUBDIRECTORY( "master" )
ADD_SUBDIRECTORY( "server" )
ADD_SUBDIRECTORY( "worker" )
