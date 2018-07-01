/*============================================================================*/
/*
 *                     XIOS - http://metasophia.org/xios
 *
 *  This file is part of the XIOS, distributed under the ISC License.
 *  Please see the LICENSE.txt file for details on copyright and licensing.
 *
 *============================================================================*/

#pragma once

#include <QtWidgets>
#include "CentralWidget.hpp"

namespace xios{

class MainWindow: public QMainWindow{
  Q_OBJECT
public:
  MainWindow( QWidget* parent = 0, Qt::WindowFlags flags = 0 );
  ~MainWindow();
protected:
  virtual void closeEvent( QCloseEvent* event );
private:
  CentralWidget* _centralWidget;
  QMenu* _createFileMenu();
  QMenu* _createHelpMenu();
  QToolBar* _createNavigationBar();
  void _setupCentralWidget();
  void _setupAroundWidgets();
  void _loadSettings();
  void _saveSettings();
private slots:
  void _onMenuHelpAbout();
};

} // namespace xios
