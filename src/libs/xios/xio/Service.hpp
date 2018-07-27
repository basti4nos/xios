/*============================================================================*/
/*
 *                     XIOS - http://metasophia.org/xios
 *
 *  This file is part of the XIOS, distributed under the ISC License.
 *  Please see the LICENSE.txt file for details on copyright and licensing.
 *
 *============================================================================*/

#pragma once

#include "xios/Config.h"

namespace xios{ namespace xio{

class XIOS_API Service{
public:
  virtual void setup() = 0;
  virtual void start() = 0;
  virtual void stop() = 0;
};

}} // namespace xios::xio
