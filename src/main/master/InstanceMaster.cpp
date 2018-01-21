/*============================================================================*/
/*
 *                     XIOS - http://metasophia.org/xios
 *
 *  This file is part of the XIOS, distributed under the ISC License.
 *  Please see the LICENSE.txt file for details on copyright and licensing.
 *
 *============================================================================*/

#include "InstanceMaster.hpp"
#include <iostream>
#include <sstream>
#include <Poco/Environment.h>
#include <Poco/Exception.h>
#include <Poco/Logger.h>
#include <Poco/Message.h>
#include <Poco/Path.h>
#include <Poco/StringTokenizer.h>
#include <Poco/Util/AbstractConfiguration.h>
#include <Poco/Util/HelpFormatter.h>
#include <Poco/Util/LayeredConfiguration.h>
#include <Poco/Util/Option.h>
#include <Poco/Util/OptionCallback.h>
#include "xios/Config.h"

#ifdef _MSC_VER
#else
  #include <sys/types.h>
  #include <unistd.h>
  #include <grp.h>
  #include <pwd.h>
#endif

#define XIOS_INSTANCE "XIOS_INSTANCE"
#define XIOS_INSTANCE_FILE XIOS_NAME ".xml"

using namespace xios;
using Poco::Environment;
using Poco::Logger;
using Poco::Message;
using Poco::Path;
using Poco::StringTokenizer;
using Poco::Util::AbstractConfiguration;
using Poco::Util::HelpFormatter;
using Poco::Util::LayeredConfiguration;
using Poco::Util::Option;
using Poco::Util::OptionCallback;

static const std::string _CONFIG_KEY_GENERAL = "general";
static const std::string _CONFIG_KEY_SERVERS = "servers";
static const std::string _CONFIG_KEY_WORKERS = "workers";

static const std::string _CONFIG_KEY_GENERAL_INSTANCE_PATH  = _CONFIG_KEY_GENERAL + ".instance.path";
static const std::string _CONFIG_KEY_GENERAL_INSTANCE_USER  = _CONFIG_KEY_GENERAL + ".instance.user";
static const std::string _CONFIG_KEY_GENERAL_INSTANCE_GROUP = _CONFIG_KEY_GENERAL + ".instance.group";

static bool _dumpConfiguration( const LayeredConfiguration& config, std::stringstream& output, const std::string& key = "", const std::string& indent = "  " );

/*----------------------------------------------------------------------------*/
static inline LayeredConfiguration& _config()
{
  return ServerApplication::instance().config();
}

/*----------------------------------------------------------------------------*/
InstanceMaster::InstanceMaster(): _initialCurrentPath( Path::current() )
{
  setUnixOptions( true );
}

/*----------------------------------------------------------------------------*/
void InstanceMaster::initialize( Application& self )
{
  _loadConfiguration();

  ServerApplication::initialize( self );

  _prepare();
}

/*----------------------------------------------------------------------------*/
void InstanceMaster::reinitialize( Application& self )
{
  _cleanup();

  _loadConfiguration();

  ServerApplication::reinitialize( self );

  _prepare();
}

/*----------------------------------------------------------------------------*/
void InstanceMaster::uninitialize()
{
  _cleanup();

  ServerApplication::uninitialize();
}

/*----------------------------------------------------------------------------*/
void InstanceMaster::defineOptions( OptionSet& opts )
{
  ServerApplication::defineOptions( opts );

  opts.addOption(
    Option( "instance", "i", "Set the instance configuration file." )
    .argument( "<path>" )
    .callback( OptionCallback< InstanceMaster >( this, &InstanceMaster::handleOption ) ) );

  opts.addOption(
    Option( "help", "?", "Display this information and exit." )
    .callback( OptionCallback< InstanceMaster >( this, &InstanceMaster::handleOption ) ) );

  opts.addOption(
    Option( "version", "V", "Display version information and exit." )
    .callback( OptionCallback< InstanceMaster >( this, &InstanceMaster::handleOption ) ) );
}

/*----------------------------------------------------------------------------*/
void InstanceMaster::handleOption( const std::string& name, const std::string& value )
{
  if( name == "instance" )
  {
    Environment::set( XIOS_INSTANCE, value );
  }
  else if( name == "help" )
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
    ServerApplication::handleOption( name, value );
  }
}

/*----------------------------------------------------------------------------*/
int InstanceMaster::main( const std::vector< std::string >& args )
{
  try
  {
    _startup();

    waitForTerminationRequest();
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
    logger().fatal( "caught unknown exception" );
    return EXIT_SOFTWARE;
  }

  return EXIT_OK;
}

/*----------------------------------------------------------------------------*/
void InstanceMaster::_loadConfiguration()
{
  Path file( Environment::get( XIOS_INSTANCE, XIOS_INSTANCE_FILE ) );
  {
    if( !file.isAbsolute() )
    {
      file = _initialCurrentPath + Path::separator() + file.toString();
    }

    loadConfiguration( file.toString() );
  }

  Path path( config().getString( _CONFIG_KEY_GENERAL_INSTANCE_PATH, "." ) );
  {
    if( !path.isAbsolute() )
    {
      path = file.parent().append( path );
      config().setString( _CONFIG_KEY_GENERAL_INSTANCE_PATH, path.toString() );
    }
  }
}

/*----------------------------------------------------------------------------*/
void InstanceMaster::_prepare()
{
  logger().information( "preparing..." );

  if( logger().getLevel() >= Message::PRIO_DEBUG )
  {
    std::stringstream stream;
    stream << "dump configuration:";
    _dumpConfiguration( config(), stream );
    logger().debug( stream.str() );
  }

  {
    std::string p = config().getString( _CONFIG_KEY_GENERAL_INSTANCE_PATH );
    logger().information( "instance path is \"" + p + "\"" );

    std::string g = config().getString( _CONFIG_KEY_GENERAL_INSTANCE_GROUP, "" );
    if( !g.empty() )
    {
      logger().information( "change group to '" + g + "'" );
      if( !_changeGroup( g ) )
        throw Poco::Exception( "failed to change group '" + g + "'" );
    }

    std::string u = config().getString( _CONFIG_KEY_GENERAL_INSTANCE_USER, "" );
    if( !u.empty() )
    {
      logger().information( "change user to '" + u + "'" );
      if( !_changeUser( u ) )
        throw Poco::Exception( "failed to change user '" + u + "'" );
    }
  }

  {
    std::string e = config().getString( _CONFIG_KEY_SERVERS + ".enable", "" );
    logger().information( "enable servers '" + e + "'" );

    StringTokenizer tokens( e, ",", StringTokenizer::TOK_IGNORE_EMPTY|StringTokenizer::TOK_TRIM );
    for( auto s: tokens )
    {
      std::string type = config().getString( _CONFIG_KEY_SERVERS + "." + s + ".type" );
      if( type == "http" )
      {
        int port = config().getInt( _CONFIG_KEY_SERVERS + "." + s + ".port" );
        _servers.push_back( new HTTPServer( new RequestHandlerFactory( s ), port ) );
      }
      else
      {
        throw Poco::Exception( "unknown server type '" + type + "'" );
      }
    }
  }

  {
    std::string s = config().getString( _CONFIG_KEY_WORKERS + ".enable", "" );
    logger().information( "enable workers '" + s + "'" );

    StringTokenizer tokens( s, ",", StringTokenizer::TOK_IGNORE_EMPTY|StringTokenizer::TOK_TRIM );
    for( auto t: tokens )
    {
      throw Poco::Exception( "workers are not supported yet" );
    }
  }

  logger().information( "preparing... done" );
}

/*----------------------------------------------------------------------------*/
void InstanceMaster::_startup()
{
  logger().information( "starting up..." );

  for( auto i = _servers.begin(), end = _servers.end(); i != end; i++ )
  {
    (*i)->start();
  }

  logger().information( "starting up... done" );
}

/*----------------------------------------------------------------------------*/
void InstanceMaster::_cleanup()
{
  logger().information( "shutting down..." );

  for( auto i = _servers.rbegin(), end = _servers.rend(); i != end; i++ )
  {
    (*i)->stop();
  }

  _servers.clear();

  logger().information( "shutting down... done" );
}

/*----------------------------------------------------------------------------*/
bool InstanceMaster::_changeGroup( const std::string& name )
{
  bool result = false;

#if defined( HAVE_SYSCONF_FUNCTION ) && \
    defined( HAVE_GETGRNAM_R_FUNCTION ) && \
    defined( HAVE_SETGID_FUNCTION )

  size_t grpSize = sizeof( struct group );
  size_t grrSize = sysconf( _SC_GETGR_R_SIZE_MAX ) * sizeof( char );

  void* buffer = ::calloc( 1, grpSize + grrSize );
  if( buffer == NULL )
    throw Poco::OutOfMemoryException( "InstanceMaster::_changeGroup" );
  else
  {
    struct group* grp = ( struct group* )buffer;
    char* grr = (char*)( grp + 1 );

    getgrnam_r( name.c_str(), grp, grr, grrSize, &grp );
    if( grp != NULL )
      if( setgid( grp->gr_gid ) == 0 )
        result = true;

    ::free( buffer );
  }

#else
  throw Poco::NotImplementedException( "InstanceMaster::_changeGroup" );
#endif

  return result;
}

/*----------------------------------------------------------------------------*/
bool InstanceMaster::_changeUser( const std::string& name )
{
  bool result = false;

#if defined( HAVE_SYSCONF_FUNCTION ) && \
    defined( HAVE_GETPWNAM_R_FUNCTION ) && \
    defined( HAVE_SETUID_FUNCTION )

  size_t pwdSize = sizeof( struct passwd );
  size_t pwrSize = sysconf( _SC_GETPW_R_SIZE_MAX ) * sizeof( char );

  void* buffer = ::calloc( 1, pwdSize + pwrSize );
  if( buffer == NULL )
    throw Poco::OutOfMemoryException( "InstanceMaster::_changeUser" );
  else
  {
    struct passwd* pwd = ( struct passwd* )buffer;
    char* pwr = (char*)( pwd + 1 );

    getpwnam_r( name.c_str(), pwd, pwr, pwrSize, &pwd );
    if( pwd != NULL )
      if( setuid( pwd->pw_uid ) == 0 )
        result = true;

    ::free( buffer );
  }

#else
  throw Poco::NotImplementedException( "InstanceMaster::_changeUser" );
#endif

  return result;
}

/*----------------------------------------------------------------------------*/
RequestHandlerFactory::RequestHandlerFactory( const std::string& name ):
  _name( name ),
  _path( _config().getString( _CONFIG_KEY_SERVERS + "." + _name + ".path", "" ) )
{
}

/*----------------------------------------------------------------------------*/
Poco::Net::HTTPRequestHandler* RequestHandlerFactory::createRequestHandler( const HTTPServerRequest& req )
{
  return new RequestHandler( _path );
}

/*----------------------------------------------------------------------------*/
RequestHandler::RequestHandler( const std::string& path ):
  _path( path )
{
}

/*----------------------------------------------------------------------------*/
void RequestHandler::handleRequest( HTTPServerRequest& req, HTTPServerResponse& res )
{
  Logger& logger = ServerApplication::instance().logger();
  std::string method = req.getMethod();

  try
  {
    if( method == HTTPServerRequest::HTTP_GET )
      _handleGET( req, res );
    else if( method == HTTPServerRequest::HTTP_HEAD )
      _handleHEAD( req, res );
    else if( method == HTTPServerRequest::HTTP_PUT )
      _handlePUT( req, res );
    else if( method == HTTPServerRequest::HTTP_POST )
      _handlePOST( req, res );
    else if( method == HTTPServerRequest::HTTP_OPTIONS )
      _handleOPTIONS( req, res );
    else if( method == HTTPServerRequest::HTTP_DELETE )
      _handleDELETE( req, res );
    else if( method == HTTPServerRequest::HTTP_TRACE )
      _handleTRACE( req, res );
    else if( method == HTTPServerRequest::HTTP_CONNECT )
      _handleCONNECT( req, res );
    else if( method == HTTPServerRequest::HTTP_PATCH )
      _handlePATCH( req, res );
    else
    {
      logger.error( "bad request '" + method + "'" );
      res.setStatusAndReason( HTTPServerResponse::HTTP_BAD_REQUEST );
    }
  }
  catch( const Poco::FileNotFoundException& e )
  {
    logger.error( e.displayText() );
    res.setStatusAndReason( HTTPServerResponse::HTTP_NOT_FOUND );
  }

  logger.information( Poco::format(
    "%s \"%s %s %s\" - %?i \"%s\" %?i \"%s\"",
    req.clientAddress().toString(),
    method,
    req.getURI(),
    req.getVersion(),
    (int)res.getStatus(),
    res.getReason(),
    res.getContentLength64(),
    res.getContentType() ) );
}

/*----------------------------------------------------------------------------*/
void RequestHandler::_handleGET( HTTPServerRequest& req, HTTPServerResponse& res )
{
  const std::string& uri = req.getURI();

  if( uri.empty() || uri.at( 0 ) != '/' )
  {
    res.setStatusAndReason( HTTPServerResponse::HTTP_BAD_REQUEST );
    return;
  }

  res.sendFile( _path + req.getURI(), "text/html" );
}

/*----------------------------------------------------------------------------*/
void RequestHandler::_handleHEAD( HTTPServerRequest& req, HTTPServerResponse& res )
{
  throw Poco::NotImplementedException( "RequestHandler::_handleHEAD" );
}

/*----------------------------------------------------------------------------*/
void RequestHandler::_handlePUT( HTTPServerRequest& req, HTTPServerResponse& res )
{
  throw Poco::NotImplementedException( "RequestHandler::_handlePUT" );
}

/*----------------------------------------------------------------------------*/
void RequestHandler::_handlePOST( HTTPServerRequest& req, HTTPServerResponse& res )
{
  throw Poco::NotImplementedException( "RequestHandler::_handlePOST" );
}

/*----------------------------------------------------------------------------*/
void RequestHandler::_handleOPTIONS( HTTPServerRequest& req, HTTPServerResponse& res )
{
  throw Poco::NotImplementedException( "RequestHandler::_handleOPTIONS" );
}

/*----------------------------------------------------------------------------*/
void RequestHandler::_handleDELETE( HTTPServerRequest& req, HTTPServerResponse& res )
{
  throw Poco::NotImplementedException( "RequestHandler::_handleDELETE" );
}

/*----------------------------------------------------------------------------*/
void RequestHandler::_handleTRACE( HTTPServerRequest& req, HTTPServerResponse& res )
{
  throw Poco::NotImplementedException( "RequestHandler::_handleTRACE" );
}

/*----------------------------------------------------------------------------*/
void RequestHandler::_handleCONNECT( HTTPServerRequest& req, HTTPServerResponse& res )
{
  throw Poco::NotImplementedException( "RequestHandler::_handleCONNECT" );
}

/*----------------------------------------------------------------------------*/
void RequestHandler::_handlePATCH( HTTPServerRequest& req, HTTPServerResponse& res )
{
  throw Poco::NotImplementedException( "RequestHandler::_handlePATCH" );
}

/*----------------------------------------------------------------------------*/
static bool _dumpConfiguration( const LayeredConfiguration& config, std::stringstream& output, const std::string& key, const std::string& indent )
{
  AbstractConfiguration::Keys subKeys;
  config.keys( key, subKeys );

  for( auto k: subKeys )
  {
    std::string subKey = ( key.empty() ? "" : key + "." ) + k;

    if( !_dumpConfiguration( config, output, subKey ) )
      if( config.has( subKey ) )
        output << std::endl << indent << subKey << " = " << config.getString( subKey );
  }

  return !subKeys.empty();
}
