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
#include <Poco/SharedLibrary.h>
#include "xios/Config.h"

namespace xios{ namespace sys{

class XIOS_API SharedLibrary: public Poco::SharedLibrary{
public:
  static std::string prefix();
  static std::string suffix();
};

}} // namespace xios::sys
