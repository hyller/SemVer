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

#define  BUF_SIZE 128

int (* FormatOutput)( const char* format, ... ) = printf;

void PrintVersion( void )
{
  FormatOutput( "\n" );
  FormatOutput( "semver increases version number in a file %s\n", VERSION );
  FormatOutput( "\n" );
}

void PrintUsage( void )
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
  FormatOutput( "-s,  Process simple version string.\n" );
  FormatOutput( "-g,  Get version string.\n" );
  FormatOutput( "-a,  Append version string to a file name.\n" );
  FormatOutput( "-i,  Initialize version.\n" );
  FormatOutput( "-n,  Specify version definition name.\n" );
  FormatOutput( "-d,  Include modify date in version header file.\n" );
  FormatOutput( "\n" );
}

void GetVersion( tSetting *as, tSemverVersion *vd )
{
  char verstr[BUF_SIZE] = { 0 };

  if ( as->init == 1 )
  {
    strcpy( verstr, as->initarg );
  }
  else
  {
    if ( as->simple == 1 )
    {
      FileProxy_ReadVersionSimple( as->filename, ( char* )verstr );
    }
    else
    {
      FileProxy_ReadVersion( as->filename,
                             ( char* )verstr,
                             ( char* )as->vername );
    }
  }

  SemVer_ConvertFromStr( vd, verstr );

  FormatOutput( "Input  version: %s\n", ( char* )verstr );
}

int IncreaseVersion( tSetting *as, tSemverVersion *versionData )
{
  int index = as->index;

  switch ( index )
  {
    case 0:
      SemVer_IncreasePatch( versionData );
      return( 0 );

    case 1:
      SemVer_IncreaseMinor( versionData );
      return( 0 );

    case 2:
      SemVer_IncreaseMajor( versionData );
      return( 0 );

    default:
      return( 1 );

      break;
  }
}

void OutputVersion( tSetting *as, tSemverVersion *vd )
{
  char verstr[BUF_SIZE] = { 0 };

  SemVer_ConvertToStr( vd, verstr, as->length );

  if ( as->simple == 1 )
  {
    FileProxy_WriteVersionSimple( ( char* )as->filename,
                                  ( char* )verstr,
                                  as->needdate );
  }
  else
  {
    FileProxy_WriteVersion( ( char* )as->filename,
                            ( char* )verstr,
                            ( char* )as->vername,
                            as->needdate );
  }

  FormatOutput( "Output version: %s\n", ( char* )verstr );
}

void AppendToFile( tSetting *as, tSemverVersion *vd )
{
  char verstr[BUF_SIZE]   = { 0 };
  char filename[BUF_SIZE] = { 0 };

  SemVer_ConvertToStr( vd, verstr, as->length );

  Utils_StrAppend( as->appendarg, ( char* )verstr, filename );

  FileProxy_CopyFile( as->appendarg, ( char* )filename );

  FormatOutput( "New   filename: %s\n", ( char* )filename );
}

int semverrun( int argc, char **argv )
{
  tSetting       as;
  tSemverVersion vd;

  SemVer_Init( &vd );
  Setting_Init( &as );
  Setting_Parse( &as, argc, argv );

  if ( ( as.help == 1 ) || ( as.error == 1 ) )
  {
    PrintUsage( );
  }
  else if ( as.version == 1 )
  {
    PrintVersion( );
  }
  else if ( as.append == 1 )
  {
    GetVersion( &as, &vd );
    AppendToFile( &as, &vd );
  }
  else if ( as.init == 1 )
  {
    GetVersion( &as, &vd );
    OutputVersion( &as, &vd );
  }
  else if ( as.get == 1 )
  {
    GetVersion( &as, &vd );
  }
  else if ( 0 == FileProxy_IsFileExist( as.filename ) )
  {
    GetVersion( &as, &vd );
    IncreaseVersion( &as, &vd );
    OutputVersion( &as, &vd );
  }
  else
  {
    OutputVersion( &as, &vd );
  }

  return( 0 );
}
