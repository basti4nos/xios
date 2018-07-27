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
#include <Poco/Process.h>
#include "xios/Config.h"

namespace xios{ namespace sys{

using Poco::ProcessHandle;

class XIOS_API Process: public Poco::Process{
public:
  static bool changeGroup( const std::string& name );
  static bool changeUser( const std::string& name );
};

}} // namespace xios::sys
