/*============================================================================*/
/*
 *                     XIOS - http://metasophia.org/xios
 *
 *  This file is part of the XIOS, distributed under the ISC License.
 *  Please see the LICENSE.txt file for details on copyright and licensing.
 *
 *============================================================================*/

#include "MainWindow.hpp"
#include "xios/Config.h"

using namespace xios;

/*----------------------------------------------------------------------------*/
MainWindow::MainWindow( QWidget* parent, Qt::WindowFlags flags ):
  QMainWindow( parent, flags )
{
#ifdef Q_OS_MAC
  setUnifiedTitleAndToolBarOnMac( true );
#endif

  menuBar()->addMenu( _createFileMenu() );
  menuBar()->addMenu( _createHelpMenu() );

  addToolBar( _createNavigationBar() );

  _setupCentralWidget();
  _setupAroundWidgets();

  _loadSettings();

  statusBar()->showMessage( "Ready", 5000 );
}

/*----------------------------------------------------------------------------*/
MainWindow::~MainWindow()
{
}

/*----------------------------------------------------------------------------*/
void MainWindow::closeEvent( QCloseEvent* event )
{
  _saveSettings();

  event->accept();
}

/*----------------------------------------------------------------------------*/
QMenu* MainWindow::_createFileMenu()
{
  // File
  auto* menu = new QMenu( tr( "&File" ) );
  {
    // Separator
    menu->addSeparator();
    // Exit
    auto* exitAction = new QAction( tr( "E&xit" ), this );
    exitAction->setShortcuts( QKeySequence::Quit );
    exitAction->setStatusTip( tr( "Exit the application" ) );
    connect( exitAction, SIGNAL( triggered() ), this, SLOT( close() ) );
    menu->addAction( exitAction );
  }

  return menu;
}

/*----------------------------------------------------------------------------*/
QMenu* MainWindow::_createHelpMenu()
{
  // Help
  auto* menu = new QMenu( tr( "&Help" ) );
  {
    // About
    auto* aboutAction = new QAction( tr( "&About" ), this );
    aboutAction->setStatusTip( tr( "About this application" ) );
    connect( aboutAction, SIGNAL( triggered() ), this, SLOT( _onMenuHelpAbout() ) );
    menu->addAction( aboutAction );
  }

  return menu;
}

/*----------------------------------------------------------------------------*/
QToolBar* MainWindow::_createNavigationBar()
{
  auto* toolbar = new QToolBar( tr( "Navigation" ) );
  {
    toolbar->setObjectName( "NavigationBar" );
    toolbar->setAllowedAreas( Qt::TopToolBarArea | Qt::BottomToolBarArea );
    toolbar->addWidget( new QLineEdit( toolbar ) );
  }

  return toolbar;
}

/*----------------------------------------------------------------------------*/
void MainWindow::_setupCentralWidget()
{
  _centralWidget = new CentralWidget( this );

  setCentralWidget( _centralWidget );
}

/*----------------------------------------------------------------------------*/
void MainWindow::_setupAroundWidgets()
{
}

/*----------------------------------------------------------------------------*/
void MainWindow::_loadSettings()
{
  QSettings settings( QSettings::IniFormat, QSettings::UserScope,
                      PROJECT_NAME, XIOS_CLIENT_GUI_OUTPUT_NAME, this );

  settings.beginGroup( "MainWindow" );
  {
    restoreGeometry( settings.value( "geometry" ).toByteArray() );
    restoreState( settings.value( "state" ).toByteArray() );
  }
  settings.endGroup();
}

/*----------------------------------------------------------------------------*/
void MainWindow::_saveSettings()
{
  QSettings settings( QSettings::IniFormat, QSettings::UserScope,
                      PROJECT_NAME, XIOS_CLIENT_GUI_OUTPUT_NAME, this );

  settings.beginGroup( "MainWindow" );
  {
    settings.setValue( "geometry", saveGeometry() );
    settings.setValue( "state", saveState() );
  }
  settings.endGroup();
}

/*----------------------------------------------------------------------------*/
void MainWindow::_onMenuHelpAbout()
{
  QMessageBox::about( this, tr( "About" ),
    tr( XIOS_CLIENT_GUI_OUTPUT_NAME " " XIOS_VERSION " with Qt " QT_VERSION_STR ) );
}
