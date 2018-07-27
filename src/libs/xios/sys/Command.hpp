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
#include "Process.hpp"

namespace xios{ namespace sys{

class XIOS_API Command{
public:
  typedef Process::Args Arguments;
public:
  Command( const std::string& name );
  Command( const std::string& name, const Arguments& args );
  const std::string& name() const;
  const Arguments& args() const;
private:
  std::string _name;
  Arguments _args;
};

}} // namespace xios::sys
