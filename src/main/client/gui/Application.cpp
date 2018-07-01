/*============================================================================*/
/*
 *                     XIOS - http://metasophia.org/xios
 *
 *  This file is part of the XIOS, distributed under the ISC License.
 *  Please see the LICENSE.txt file for details on copyright and licensing.
 *
 *============================================================================*/

#include "Application.hpp"
#include "xios/Config.h"

using namespace xios;

/*----------------------------------------------------------------------------*/
Application::Application( int& argc, char** argv ): QApplication( argc, argv )
{
  setApplicationName( XIOS_CLIENT_GUI_OUTPUT_NAME );
  setApplicationDisplayName( applicationName() );

  _mainWindow.setWindowTitle( applicationDisplayName() );
}

/*----------------------------------------------------------------------------*/
Application::~Application()
{
}

/*----------------------------------------------------------------------------*/
void Application::showMainWindow()
{
  _mainWindow.show();
}

/*----------------------------------------------------------------------------*/
void Application::hideMainWindow()
{
  _mainWindow.hide();
}
