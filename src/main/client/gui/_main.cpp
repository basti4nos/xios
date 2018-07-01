/*============================================================================*/
/*
 *                     XIOS - http://metasophia.org/xios
 *
 *  This file is part of the XIOS, distributed under the ISC License.
 *  Please see the LICENSE.txt file for details on copyright and licensing.
 *
 *============================================================================*/

#include "Application.hpp"

using namespace xios;

/*----------------------------------------------------------------------------*/
int main( int argc, char* argv[] )
{
  Application app( argc, argv );

  app.showMainWindow();

  return app.exec();
}
