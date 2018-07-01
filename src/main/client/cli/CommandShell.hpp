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
#include <vector>
#include <Poco/Util/OptionSet.h>
#include <Poco/Util/Application.h>

namespace xios{

using Poco::Util::OptionSet;
using Poco::Util::Application;

class CommandShell: public Application{
public:
  CommandShell();
protected:
  void defineOptions( OptionSet& opts );
  void handleOption( const std::string& name, const std::string& value );
  int main( const std::vector< std::string >& args );
};

} // namespace xios
