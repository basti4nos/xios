/*============================================================================*/
/*
 *                     XIOS - http://metasophia.org/xios
 *
 *  This file is part of the XIOS, distributed under the ISC License.
 *  Please see the LICENSE.txt file for details on copyright and licensing.
 *
 *============================================================================*/

#include "Command.hpp"

using namespace xios::sys;

/*----------------------------------------------------------------------------*/
Command::Command( const std::string& name ):
  _name( name )
{
}

/*----------------------------------------------------------------------------*/
Command::Command( const std::string& name, const Arguments& args ):
  _name( name ), _args( args )
{
}

/*----------------------------------------------------------------------------*/
const std::string& Command::name() const
{
  return _name;
}

/*----------------------------------------------------------------------------*/
const Command::Arguments& Command::args() const
{
  return _args;
}
