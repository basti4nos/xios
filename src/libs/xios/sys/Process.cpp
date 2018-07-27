/*============================================================================*/
/*
 *                     XIOS - http://metasophia.org/xios
 *
 *  This file is part of the XIOS, distributed under the ISC License.
 *  Please see the LICENSE.txt file for details on copyright and licensing.
 *
 *============================================================================*/

#include "Process.hpp"
#include <Poco/Exception.h>

#ifdef _MSC_VER
#else
  #include <sys/types.h>
  #include <unistd.h>
  #include <grp.h>
  #include <pwd.h>
#endif

using namespace xios::sys;

/*----------------------------------------------------------------------------*/
bool Process::changeGroup( const std::string& name )
{
  bool result = false;

#if defined( HAVE_SYSCONF_FUNCTION ) && \
    defined( HAVE_GETGRNAM_R_FUNCTION ) && \
    defined( HAVE_SETGID_FUNCTION )

  size_t grps = sizeof( struct group );
  size_t grrs = sysconf( _SC_GETGR_R_SIZE_MAX ) * sizeof( char );

  void* buffer = ::calloc( 1, grps + grrs );
  if( !buffer )
    throw Poco::OutOfMemoryException( "xios::sys::Process::changeGroup" );
  else
  {
    struct group* grp = ( struct group* )buffer;
    char* grr = (char*)( grp + 1 );

    getgrnam_r( name.c_str(), grp, grr, grrs, &grp );
    if( grp )
      if( setgid( grp->gr_gid ) == 0 )
        result = true;

    ::free( buffer );
  }

#else
  throw Poco::NotImplementedException( "xios::sys::Process::changeGroup" );
#endif

  return result;
}

/*----------------------------------------------------------------------------*/
bool Process::changeUser( const std::string& name )
{
  bool result = false;

#if defined( HAVE_SYSCONF_FUNCTION ) && \
    defined( HAVE_GETPWNAM_R_FUNCTION ) && \
    defined( HAVE_SETUID_FUNCTION )

  size_t pwds = sizeof( struct passwd );
  size_t pwrs = sysconf( _SC_GETPW_R_SIZE_MAX ) * sizeof( char );

  void* buffer = ::calloc( 1, pwds + pwrs );
  if( !buffer )
    throw Poco::OutOfMemoryException( "xios::sys::Process::changeUser" );
  else
  {
    struct passwd* pwd = ( struct passwd* )buffer;
    char* pwr = (char*)( pwd + 1 );

    getpwnam_r( name.c_str(), pwd, pwr, pwrs, &pwd );
    if( pwd )
      if( setuid( pwd->pw_uid ) == 0 )
        result = true;

    ::free( buffer );
  }

#else
  throw Poco::NotImplementedException( "xios::sys::Process::changeUser" );
#endif

  return result;
}
