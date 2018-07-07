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
#include <Poco/Util/Application.h>
#include <Poco/Util/OptionSet.h>

namespace xios{

using Poco::Util::Application;
using Poco::Util::OptionSet;

class InstanceServer: public Application{
public:
  InstanceServer();
protected:
  void initialize( Application& self );
  void uninitialize();
  void defineOptions( OptionSet& opts );
  void handleOption( const std::string& name, const std::string& value );
  int main( const std::vector< std::string >& args );
};

} // namespace xios
