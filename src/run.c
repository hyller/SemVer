#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stddef.h>
#include <ctype.h>
#include <unistd.h>

#include "utils.h"
#include "version.h"
#include "semver.h"
#include "setting.h"
#include "fileproxy.h"

#define  RUN_BUF_SIZE ( 128U )

static int ( *FormatOutput )( const char *format, ... ) = printf;

static void Run_PrintVersion( void )
{
  FormatOutput( "\n" );
  FormatOutput( "semver increases version number in a file %s\n", VERSION );
  FormatOutput( "\n" );
}

static void Run_PrintUsage( void )
{
  FormatOutput( "\n" );
  FormatOutput( "Usage: semver [option] [FILE]\n" );
  FormatOutput( "\n" );
  FormatOutput( "Options:\n" );
  FormatOutput( "-x,  Change major version number.\n" );
  FormatOutput( "-y,  Change minor version number.\n" );
  FormatOutput( "-z,  Change patch version number.\n" );
  FormatOutput( "-l,  Specify version number digits.\n" );
  FormatOutput( "-v,  Print program version.\n" );
  FormatOutput( "-h,  Print this help screen.\n" );
  FormatOutput( "-g,  Get version string.\n" );
  FormatOutput( "-a,  Append version string to a file name.\n" );
  FormatOutput( "-i,  Initialize version.\n" );
  FormatOutput( "-n,  Specify version definition name.\n" );
  FormatOutput( "\n" );
}

static void Run_GetVersion( tSetting *as, tSemver *vd )
{
  char verstr[RUN_BUF_SIZE] = { 0 };

  if ( as->init == 1 )
  {
    strcpy( verstr, as->initarg );
  }
  else
  {
    FileProxy_ReadVersion( as->filename,
                           verstr,
                           as->vername );
  }

  SemVer_InitByStrFieldlen( vd, verstr, as->length );

  FormatOutput( "Input  version: %s\n", verstr );
}

static int Run_BumpVersion( tSetting *as, tSemver *versionData )
{
  int index = as->index;
  int ret   = 1;

  switch ( index )
  {
    case 0:
      SemVer_BumpPatch( versionData );
      ret = 0;
      break;

    case 1:
      SemVer_BumpMinor( versionData );
      ret = 0;
      break;

    case 2:
      SemVer_BumpMajor( versionData );
      ret = 0;
      break;
  }

  return( ret );
}

static void Run_OutputVersion( tSetting *as, tSemver *vd )
{
  FileProxy_WriteVersion( as->filename,
                          vd->str,
                          as->vername );

  FormatOutput( "Output version: %s\n", vd->str );
}

static void Run_CopyFile( tSetting *as, tSemver *vd )
{
  char filename[RUN_BUF_SIZE] = { 0 };

  Utils_StrAppend( as->appendarg, vd->str, filename );

  FileProxy_CopyFile( as->appendarg, filename );

  FormatOutput( "New   filename: %s\n", filename );
}

void Run_SetFormatOutput( int ( *p )( const char *format, ... ) )
{
  FormatOutput = p;
}

int Run_SemVer( int argc, char **argv )
{
  tSetting as;
  tSemver  vd;

  SemVer_Init( &vd );
  Setting_Init( &as );
  Setting_Parse( &as, argc, argv );

  if ( ( as.help == 1 ) || ( as.error == 1 ) )
  {
    Run_PrintUsage( );
  }
  else if ( as.version == 1 )
  {
    Run_PrintVersion( );
  }
  else if ( as.append == 1 )
  {
    Run_GetVersion( &as, &vd );
    Run_CopyFile( &as, &vd );
  }
  else if ( as.init == 1 )
  {
    Run_GetVersion( &as, &vd );
    Run_OutputVersion( &as, &vd );
  }
  else if ( as.get == 1 )
  {
    Run_GetVersion( &as, &vd );
  }
  else if ( 0 == FileProxy_AccessFile( as.filename ) )
  {
    Run_GetVersion( &as, &vd );
    Run_BumpVersion( &as, &vd );
    Run_OutputVersion( &as, &vd );
  }

  return( 0 );
}
