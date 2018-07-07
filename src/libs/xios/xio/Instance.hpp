/*============================================================================*/
/*
 *                     XIOS - http://metasophia.org/xios
 *
 *  This file is part of the XIOS, distributed under the ISC License.
 *  Please see the LICENSE.txt file for details on copyright and licensing.
 *
 *============================================================================*/

#pragma once

#include <string>
#include "xios/Config.h"

namespace xios{ namespace xio{

class XIOS_API Instance{
public:
  static void format( const std::string& path );
public:
  Instance( const std::string& path );
private:
  std::string _path;
};

}} // namespace xios::xio
