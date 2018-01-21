/*============================================================================*/
/*
 *                     XIOS - http://metasophia.org/xios
 *
 *  This file is part of the XIOS, distributed under the ISC License.
 *  Please see the LICENSE.txt file for details on copyright and licensing.
 *
 *============================================================================*/

#pragma once

#include <list>
#include <string>
#include <vector>
#include <Poco/SharedPtr.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Util/OptionSet.h>
#include <Poco/Util/ServerApplication.h>

namespace xios{

using Poco::SharedPtr;
using Poco::Net::HTTPServer;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;
using Poco::Util::OptionSet;
using Poco::Util::ServerApplication;

class InstanceMaster: public ServerApplication{
public:
  InstanceMaster();
protected:
  void initialize( Application& self );
  void reinitialize( Application& self );
  void uninitialize();
  void defineOptions( OptionSet& opts );
  void handleOption( const std::string& name, const std::string& value );
  int main( const std::vector< std::string >& args );
private:
  const std::string _initialCurrentPath;
  std::list< SharedPtr< HTTPServer > > _servers;
  void _loadConfiguration();
  void _prepare();
  void _startup();
  void _cleanup();
  bool _changeGroup( const std::string& name );
  bool _changeUser( const std::string& name );
};

class RequestHandlerFactory: public Poco::Net::HTTPRequestHandlerFactory{
public:
  RequestHandlerFactory( const std::string& name );
  Poco::Net::HTTPRequestHandler* createRequestHandler( const HTTPServerRequest& req );
private:
  const std::string _name;
  const std::string _path;
};

class RequestHandler: public Poco::Net::HTTPRequestHandler{
public:
  RequestHandler( const std::string& path );
  void handleRequest( HTTPServerRequest& req, HTTPServerResponse& res );
private:
  const std::string& _path;
  void _handleGET( HTTPServerRequest& req, HTTPServerResponse& res );
  void _handleHEAD( HTTPServerRequest& req, HTTPServerResponse& res );
  void _handlePUT( HTTPServerRequest& req, HTTPServerResponse& res );
  void _handlePOST( HTTPServerRequest& req, HTTPServerResponse& res );
  void _handleOPTIONS( HTTPServerRequest& req, HTTPServerResponse& res );
  void _handleDELETE( HTTPServerRequest& req, HTTPServerResponse& res );
  void _handleTRACE( HTTPServerRequest& req, HTTPServerResponse& res );
  void _handleCONNECT( HTTPServerRequest& req, HTTPServerResponse& res );
  void _handlePATCH( HTTPServerRequest& req, HTTPServerResponse& res );
};

} // namespace xios
