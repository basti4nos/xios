/*============================================================================*/
/*
 *                     XIOS - http://metasophia.org/xios
 *
 *  This file is part of the XIOS, distributed under the ISC License.
 *  Please see the LICENSE.txt file for details on copyright and licensing.
 *
 *============================================================================*/

#include <string>
#include <vector>
#include <iostream>
#include <Poco/Exception.h>
#include <Poco/Util/Application.h>
#include <Poco/Util/HelpFormatter.h>
#include <Poco/Util/Option.h>
#include <Poco/Util/OptionCallback.h>
#include <Poco/Util/OptionSet.h>
#include "xios/Config.h"

using Poco::Util::Application;
using Poco::Util::HelpFormatter;
using Poco::Util::Option;
using Poco::Util::OptionCallback;
using Poco::Util::OptionSet;

class xiop_Test: public Application{
public:
  xiop_Test(){ setUnixOptions( true ); }
protected:
  void defineOptions( OptionSet& opts );
  void handleOption( const std::string& name, const std::string& value );
  int main( const std::vector< std::string >& args );
};

/*----------------------------------------------------------------------------*/
POCO_APP_MAIN( xiop_Test )

/*----------------------------------------------------------------------------*/
void xiop_Test::defineOptions( OptionSet& opts )
{
  Application::defineOptions( opts );

  OptionCallback< xiop_Test > handler( this, &xiop_Test::handleOption );

  opts.addOption(
    Option( "help", "?", "Display this information and exit." )
    .callback( handler ) );

  opts.addOption(
    Option( "version", "V", "Display version information and exit." )
    .callback( handler ) );
}

/*----------------------------------------------------------------------------*/
void xiop_Test::handleOption( const std::string& name, const std::string& value )
{
  if( name == "help" )
  {
    HelpFormatter formatter( options() );
    formatter.setCommand( commandName() );
    formatter.setUsage( "[options...]" );
    formatter.format( std::cout );
    stopOptionsProcessing();
    ::exit( EXIT_OK );
  }
  else if( name == "version" )
  {
    std::cout << PROJECT_NAME " " XIOS_VERSION << std::endl;
    stopOptionsProcessing();
    ::exit( EXIT_OK );
  }
  else
  {
    Application::handleOption( name, value );
  }
}

/*----------------------------------------------------------------------------*/
int xiop_Test::main( const std::vector< std::string >& args )
{
  try
  {
  }
  catch( const Poco::Exception& e )
  {
    logger().fatal( e.displayText() );
    return EXIT_SOFTWARE;
  }
  catch( const std::exception& e )
  {
    logger().fatal( e.what() );
    return EXIT_SOFTWARE;
  }
  catch( ... )
  {
    logger().fatal( "Caught unknown exception" );
    return EXIT_SOFTWARE;
  }

  return EXIT_OK;
}
