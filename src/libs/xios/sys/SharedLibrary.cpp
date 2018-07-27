/*============================================================================*/
/*
 *                     XIOS - http://metasophia.org/xios
 *
 *  This file is part of the XIOS, distributed under the ISC License.
 *  Please see the LICENSE.txt file for details on copyright and licensing.
 *
 *============================================================================*/

#include "SharedLibrary.hpp"

using namespace xios::sys;

/*----------------------------------------------------------------------------*/
std::string SharedLibrary::prefix()
{
#ifdef _MSC_VER
  return "";
#else
  return "lib";
#endif
}

/*----------------------------------------------------------------------------*/
std::string SharedLibrary::suffix()
{
#ifdef _MSC_VER
  return ".dll";
#else
  return ".so";
#endif
}
