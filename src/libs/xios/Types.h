/*============================================================================*/
/*
 *                     XIOS - http://metasophia.org/xios
 *
 *  This file is part of the XIOS, distributed under the ISC License.
 *  Please see the LICENSE.txt file for details on copyright and licensing.
 *
 *============================================================================*/

#pragma once

/*! ASCII Codes */
enum xios_ascii
{
  XIOS_ASCII_NUL,         //!< 0x00 Null character
  XIOS_ASCII_SOH,         //!< 0x01 Start of heading
  XIOS_ASCII_STX,         //!< 0x02 Start of text
  XIOS_ASCII_ETX,         //!< 0x03 End of text
  XIOS_ASCII_EOT,         //!< 0x04 End of transmission
  XIOS_ASCII_ENQ,         //!< 0x05 Enquiry
  XIOS_ASCII_ACK,         //!< 0x06 Acknowledgment
  XIOS_ASCII_BEL,         //!< 0x07 Audible bell
  XIOS_ASCII_BS,          //!< 0x08 Backspace
  XIOS_ASCII_HT,          //!< 0x09 Horizontal tab
  XIOS_ASCII_LF,          //!< 0x0A Line feed
  XIOS_ASCII_VT,          //!< 0x0B Vertical tab
  XIOS_ASCII_FF,          //!< 0x0C Form feed
  XIOS_ASCII_CR,          //!< 0x0D Carriage return
  XIOS_ASCII_SO,          //!< 0x0E Shift out
  XIOS_ASCII_SI,          //!< 0x0F Shift in
  XIOS_ASCII_DLE,         //!< 0x10 Data link escape
  XIOS_ASCII_DC1,         //!< 0x11 Device control 1 / XON
  XIOS_ASCII_DC2,         //!< 0x12 Device control 2
  XIOS_ASCII_DC3,         //!< 0x13 Device control 3 / XOFF
  XIOS_ASCII_DC4,         //!< 0x14 Device control 4
  XIOS_ASCII_NAC,         //!< 0x15 Negative acknowledgment
  XIOS_ASCII_SYN,         //!< 0x16 Synchronous idle
  XIOS_ASCII_ETB,         //!< 0x17 End of transmission block
  XIOS_ASCII_CAN,         //!< 0x18 Cancel
  XIOS_ASCII_EM,          //!< 0x19 End of medium
  XIOS_ASCII_SUB,         //!< 0x1A Substitute character
  XIOS_ASCII_ESC,         //!< 0x1B Escape
  XIOS_ASCII_FS,          //!< 0x1C File separator
  XIOS_ASCII_GS,          //!< 0x1D Group separator
  XIOS_ASCII_RS,          //!< 0x1E Record separator
  XIOS_ASCII_US,          //!< 0x1F Unit separator
  XIOS_ASCII_SP  = 0x20,  //!< 0x20 White space
  XIOS_ASCII_DEL = 0x7F   //!< 0x7F Delete
};
