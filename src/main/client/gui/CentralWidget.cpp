/*============================================================================*/
/*
 *                     XIOS - http://metasophia.org/xios
 *
 *  This file is part of the XIOS, distributed under the ISC License.
 *  Please see the LICENSE.txt file for details on copyright and licensing.
 *
 *============================================================================*/

#include "CentralWidget.hpp"

using namespace xios;

/*----------------------------------------------------------------------------*/
CentralWidget::CentralWidget( QWidget* parent ):
  QTabWidget( parent )
{
  setTabsClosable( true );
}

/*----------------------------------------------------------------------------*/
CentralWidget::~CentralWidget()
{
}
