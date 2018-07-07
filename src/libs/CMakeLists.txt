#==============================================================================#
#
#                      XIOS - http://metasophia.org/xios
#
#   This file is part of the XIOS, distributed under the ISC License.
#   Please see the LICENSE.txt file for details on copyright and licensing.
#
#==============================================================================#

IF( BUILD_XIOC )
  ADD_SUBDIRECTORY( "xioc" )
ENDIF()

ADD_SUBDIRECTORY( "xiop" )
ADD_SUBDIRECTORY( "xios" )
