#==============================================================================#
#
#                      XIOS - http://metasophia.org/xios
#
#   This file is part of the XIOS, distributed under the ISC License.
#   Please see the LICENSE.txt file for details on copyright and licensing.
#
#==============================================================================#

GET_FILENAME_COMPONENT( dir ${CMAKE_CURRENT_SOURCE_DIR} NAME )

FUNCTION( ADD_UNIT_TEST src libs )
  # Set name
  GET_FILENAME_COMPONENT( name_we ${src} NAME_WE )
  SET( target_name "${TEST_NAME}${dir}.${name_we}" )
  SET( output_name "${TEST_OUTPUT_NAME}${dir}.${name_we}" )
  # Add executable
  ADD_EXECUTABLE( ${target_name} ${src} )
  IF( BUILD_POCO )
    ADD_DEPENDENCIES( ${target_name} ${EXT_POCO_NAME} )
  ENDIF()
  TARGET_LINK_LIBRARIES( ${target_name} ${libs} )
  SET_TARGET_PROPERTIES( ${target_name} PROPERTIES OUTPUT_NAME ${output_name} )
  # Add test
  ADD_TEST( NAME ${target_name} COMMAND ${output_name} )
ENDFUNCTION()

# Add xiop* unit tests
FILE( GLOB srcs RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "xiop*.cpp" )
LIST( SORT srcs )
FOREACH( src ${srcs} )
  ADD_UNIT_TEST( ${src} "${XIOP_NAME};${POCO_LIBRARIES}" )
ENDFOREACH()

# Add xioc* unit tests
FILE( GLOB srcs RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "xioc*.cpp" )
LIST( SORT srcs )
FOREACH( src ${srcs} )
  ADD_UNIT_TEST( ${src} "${XIOC_NAME};${POCO_LIBRARIES}" )
ENDFOREACH()

# Add xios* unit tests
FILE( GLOB srcs RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "xios*.cpp" )
LIST( SORT srcs )
FOREACH( src ${srcs} )
  ADD_UNIT_TEST( ${src} "${XIOS_NAME};${POCO_LIBRARIES}" )
ENDFOREACH()
