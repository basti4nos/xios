/*============================================================================*/
/*
 *                     XIOS - http://metasophia.org/xios
 *
 *  This file is part of the XIOS, distributed under the ISC License.
 *  Please see the LICENSE.txt file for details on copyright and licensing.
 *
 *============================================================================*/

#ifndef XIOS__CONFIG_H__INCLUDED
#define XIOS__CONFIG_H__INCLUDED

/*----------------------------------------------------------------------------*
 * XIOS Project Definitions
 *----------------------------------------------------------------------------*/

/*! */
#define PROJECT_NAME "@PROJECT_NAME@"
/*! */
#define XIOS_VERSION "@XIOS_VERSION@"
/*! */
#define XIOS_VERSION_MAJOR @XIOS_VERSION_MAJOR@
/*! */
#define XIOS_VERSION_MINOR @XIOS_VERSION_MINOR@
/*! */
#define XIOS_VERSION_PATCH @XIOS_VERSION_PATCH@

/*----------------------------------------------------------------------------*
 * XIOS Module Definitions
 *----------------------------------------------------------------------------*/

/*! */
#define XIOS_NAME "@XIOS_NAME@"
/*! */
#define XIOS_OUTPUT_NAME "@XIOS_OUTPUT_NAME@"
/*! */
#define XIOS_CLIENT_CLI_NAME "@XIOS_CLIENT_CLI_NAME@"
/*! */
#define XIOS_CLIENT_CLI_OUTPUT_NAME "@XIOS_CLIENT_CLI_OUTPUT_NAME@"
/*! */
#define XIOS_CLIENT_GUI_NAME "@XIOS_CLIENT_GUI_NAME@"
/*! */
#define XIOS_CLIENT_GUI_OUTPUT_NAME "@XIOS_CLIENT_GUI_OUTPUT_NAME@"
/*! */
#define XIOS_MASTER_NAME "@XIOS_MASTER_NAME@"
/*! */
#define XIOS_MASTER_OUTPUT_NAME "@XIOS_MASTER_OUTPUT_NAME@"

/*----------------------------------------------------------------------------*
 * Check Function Exists
 *----------------------------------------------------------------------------*/

#cmakedefine HAVE_SYSCONF_FUNCTION 1
#cmakedefine HAVE_GETGRNAM_R_FUNCTION 1
#cmakedefine HAVE_GETPWNAM_R_FUNCTION 1
#cmakedefine HAVE_SETGID_FUNCTION 1
#cmakedefine HAVE_SETUID_FUNCTION 1

/*----------------------------------------------------------------------------*
 * Common Macros
 *----------------------------------------------------------------------------*/

#ifdef _MSC_VER
  #ifdef xios_EXPORTS
    #define XIOS_API __declspec( dllexport )
  #else
    #define XIOS_API __declspec( dllimport )
  #endif
#else
  #define XIOS_API
#endif

#endif/*XIOS__CONFIG_H__INCLUDED*/
