#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

#include "fileproxy.h"
#include "version.h"
#include "utils.h"
#include "semver.h"

#define FILEPROXY_DEFAULT_VERSION_NAME ( "VERSION" )

int FileProxy_ReadFile( char *filename, char *buf, int size )
{
  FILE *ifp;
  int  ch;
  int  count = 0;

  if ( ( ifp = fopen( filename, "r" ) ) == NULL )
  {
    return( 1 );
  }

  while ( ( ch = fgetc( ifp ) ) != EOF )
  {
    if ( count < size )
    {
      buf[count] = ch;
      count++;
    }
  }

  fclose( ifp );

  return( 0 );
}

int FileProxy_WriteFile( char *filename, char *buf, int size )
{
  FILE *ifp;

  if ( ( ifp = fopen( filename, "w" ) ) == NULL )
  {
    return( 1 );
  }

  fprintf( ifp, "%s", buf );

  fclose( ifp );

  return( 0 );
}

static char * FileProxy_GetDay( void )
{
  static char DayBuffer[80];
  struct tm   *tmt;
  time_t      timet;

  timet = time( 0 );
  tmt   = gmtime( &timet );
  strftime( DayBuffer, 80, "%Y-%m-%d", tmt );

  return( DayBuffer );
}

tFileProxyFileType FileProxy_GetFileType( char *filename )
{
  tFileProxyFileType ret             = eFileProxyFileType_Txt;
  char               filesuffix[128] = { 0 };
  int                len;
  int                rpos;
  int                i;

  len = strlen( filename );

  rpos = Utils_StrRchr( filename, 1, len + 1, '.' );

  if ( rpos != 0 )
  {
    for ( i = 0; i < len; i++ )
    {
      filesuffix[i] = tolower( filename[rpos + i] );
    }

    if ( strcmp( filesuffix, "h" ) == 0 )
    {
      ret = eFileProxyFileType_CHeader;
    }
    else if ( strcmp( filesuffix, "java" ) == 0 )
    {
      ret = eFileProxyFileType_Java;
    }
  }

  return( ret );
}

int FileProxy_AccessFile( char *filename )
{
  return( access( filename, 0 ) );
}

static int FileProxy_ReadVersionCHeader( char *filename,
                                         char *verstr,
                                         char *vername )
{
  char buf[FILEPROXY_FILE_BUF_SIZE] = { 0 };
  int  lpos;
  int  rpos;
  int  len;
  char defstr[100] = { 0 };

  if ( ( vername == NULL ) || ( *vername == 0 ) )
  {
    vername = FILEPROXY_DEFAULT_VERSION_NAME;
  }

  sprintf( &defstr[0], "#define  %s", vername );

  FileProxy_ReadFile( filename, buf, FILEPROXY_FILE_BUF_SIZE );

  len = strlen( buf ) + 1;

  lpos = Utils_StrFind( buf, 1, len, defstr );
  lpos = Utils_StrChr( buf, lpos + 1, len, '"' );
  rpos = Utils_StrChr( buf, lpos + 1, len, '"' );

  memcpy( verstr, &buf[lpos], ( size_t )( rpos - lpos - 1 ) );

  return( 0 );
}

static int FileProxy_WriteVersionCHeader( char *filename,
                                          char *verstr,
                                          char *vername,
                                          int  needdate )
{
  char    buf[FILEPROXY_FILE_BUF_SIZE] = { 0 };
  int     len                          = 0;
  char    *timestr                     = 0;
  tSemver vernum                       = { 0 };

  if ( ( vername == NULL ) || ( *vername == 0 ) )
  {
    vername = FILEPROXY_DEFAULT_VERSION_NAME;
  }

  SemVer_InitByStr( &vernum, verstr );

  timestr = FileProxy_GetDay( );

  len += sprintf( &buf[len], "/* This file is managed by semver, Don't modify manually */\n" );
  len += sprintf( &buf[len], "/* Visit https://github.com/hyller/SemVer for more information */\n" );
  len += sprintf( &buf[len], "#ifndef %s_H\n", vername );
  len += sprintf( &buf[len], "#define %s_H\n", vername );
  len += sprintf( &buf[len], "\n" );
  len += sprintf( &buf[len], "#define  %s             \"%s\"\n", vername, verstr );
  len += sprintf( &buf[len], "#define  %s_MAJOR       %uU\n", vername, vernum.major );
  len += sprintf( &buf[len], "#define  %s_MINOR       %uU\n", vername, vernum.minor );
  len += sprintf( &buf[len], "#define  %s_PATCH       %uU\n", vername, vernum.patch );
  if ( needdate )
  {
    len += sprintf( &buf[len], "#define  %s_MODIFY_DATE \"%s\"\n", vername, timestr );
  }
  len += sprintf( &buf[len], "\n" );
  len += sprintf( &buf[len], "#endif\n" );

  FileProxy_WriteFile( filename, buf, strlen( buf ) );

  return( 0 );
}

static int FileProxy_ReadVersionJava( char *filename,
                                      char *verstr,
                                      char *vername )
{
  char buf[FILEPROXY_FILE_BUF_SIZE] = { 0 };
  int  lpos;
  int  rpos;
  int  len;
  char defstr[100] = { 0 };

  if ( ( vername == NULL ) || ( *vername == 0 ) )
  {
    vername = FILEPROXY_DEFAULT_VERSION_NAME;
  }

  sprintf( &defstr[0], "static final String %s", vername );

  FileProxy_ReadFile( filename, buf, FILEPROXY_FILE_BUF_SIZE );

  len = strlen( buf ) + 1;

  lpos = Utils_StrFind( buf, 1, len, defstr );
  lpos = Utils_StrChr( buf, lpos + 1, len, '"' );
  rpos = Utils_StrChr( buf, lpos + 1, len, '"' );

  memcpy( verstr, &buf[lpos], ( size_t )( rpos - lpos - 1 ) );

  return( 0 );
}

static int FileProxy_WriteVersionJava( char *filename,
                                       char *verstr,
                                       char *vername,
                                       int  needdate )
{
  char    buf[FILEPROXY_FILE_BUF_SIZE] = { 0 };
  int     len                          = 0;
  tSemver vernum                       = { 0 };
  char    preffix[128]                 = { 0 };
  int     rpos;

  if ( ( vername == NULL ) || ( *vername == 0 ) )
  {
    vername = FILEPROXY_DEFAULT_VERSION_NAME;
  }

  strcpy( preffix, filename );
  rpos              = Utils_StrChr( preffix, 1, 128, '.' );
  preffix[rpos - 1] = 0;

  SemVer_InitByStr( &vernum, verstr );

  len += sprintf( &buf[len], "// This file is managed by semver, Don't modify manually\n" );
  len += sprintf( &buf[len], "// Visit https://github.com/hyller/SemVer for more information\n" );
  len += sprintf( &buf[len], "public class %s\n", preffix );
  len += sprintf( &buf[len], "{\n" );
  len += sprintf( &buf[len], "    static final String %s       = \"%s\";\n", vername, verstr );
  len += sprintf( &buf[len], "    static final int    %s_MAJOR = %d;\n", vername, vernum.major );
  len += sprintf( &buf[len], "    static final int    %s_MINOR = %d;\n", vername, vernum.minor );
  len += sprintf( &buf[len], "    static final int    %s_PATCH = %d;\n", vername, vernum.patch );
  len += sprintf( &buf[len], "}\n" );

  FileProxy_WriteFile( filename, buf, strlen( buf ) );

  return( 0 );
}

static int FileProxy_ReadVersionTxt( char *filename,
                                     char *verstr,
                                     char *vername )
{
  char buf[FILEPROXY_FILE_BUF_SIZE] = { 0 };
  int  len;

  FileProxy_ReadFile( filename, buf, FILEPROXY_FILE_BUF_SIZE );

  for ( len = 0; len < FILEPROXY_FILE_BUF_SIZE; len++ )
  {
    if ( ( buf[len] == ' ' ) || ( buf[len] == 0 ) )
    {
      buf[len] = 0;
      break;
    }
  }

  strcpy( verstr, buf );

  return( 0 );
}

static int FileProxy_WriteVersionTxt( char *filename,
                                      char *verstr,
                                      char *vername,
                                      int  needdate )
{
  char buf[FILEPROXY_FILE_BUF_SIZE] = { 0 };
  char *timestr                     = 0;

  if ( needdate )
  {
    timestr = FileProxy_GetDay( );

    sprintf( buf, "%s    %s", verstr, timestr );
  }
  else
  {
    sprintf( buf, "%s", verstr );
  }

  FileProxy_WriteFile( filename, buf, strlen( buf ) );

  return( 0 );
}

int FileProxy_ReadVersion( char *filename,
                           char *verstr,
                           char *vername )
{
  int ret;

  switch ( FileProxy_GetFileType( filename ) )
  {
    case eFileProxyFileType_CHeader:
      ret = FileProxy_ReadVersionCHeader( filename, verstr, vername );
      break;

    case eFileProxyFileType_Java:
      ret = FileProxy_ReadVersionJava( filename, verstr, vername );
      break;

    default:
      ret = FileProxy_ReadVersionTxt( filename, verstr, vername );
      break;
  }

  return( ret );
}

int FileProxy_WriteVersion( char *filename,
                            char *verstr,
                            char *vername,
                            int  needdate )
{
  int ret;

  switch ( FileProxy_GetFileType( filename ) )
  {
    case eFileProxyFileType_CHeader:
      ret = FileProxy_WriteVersionCHeader( filename, verstr, vername, needdate );
      break;

    case eFileProxyFileType_Java:
      ret = FileProxy_WriteVersionJava( filename, verstr, vername, needdate );
      break;

    default:
      ret = FileProxy_WriteVersionTxt( filename, verstr, vername, needdate );
      break;
  }

  return( ret );
}

int FileProxy_CopyFile( char *filename, char *newname )
{
  FILE *fpSrc = NULL;
  FILE *fpDst = NULL;
  int  ret    = 1;
  char ch;

  fpSrc = fopen( filename, "rb" );
  fpDst = fopen( newname, "wb" );

  if ( ( fpSrc != NULL ) && ( fpDst != NULL ) )
  {
    while ( !feof( fpSrc ) )
    {
      fread( &ch, sizeof( char ), 1, fpSrc );
      fwrite( &ch, sizeof( char ), 1, fpDst );
    }
    fflush( fpDst );
    fclose( fpSrc );
    fclose( fpDst );
    ret = 0;
  }
  else
  {
    ret = 1;
  }

  return( ret );
}

int FileProxy_RemoveFile( char *filename )
{
  int ret = 1;

  if ( 0 == FileProxy_AccessFile( filename ) )
  {
    ret = remove( filename );
  }

  return( ret );
}
