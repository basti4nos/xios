/*============================================================================*/
/*
 *                     XIOS - http://metasophia.org/xios
 *
 *  This file is part of the XIOS, distributed under the ISC License.
 *  Please see the LICENSE.txt file for details on copyright and licensing.
 *
 *============================================================================*/

#pragma once

#include <QApplication>
#include "MainWindow.hpp"

namespace xios{

class Application: public QApplication{
  Q_OBJECT
public:
  Application( int& argc, char** argv );
  ~Application();
	void showMainWindow();
	void hideMainWindow();
private:
	MainWindow _mainWindow;
};

} // namespace xios
