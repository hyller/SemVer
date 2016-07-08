#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "semver.h"
#include "utils.h"

#define SEMVER_FMT_STR_SIMPLE      ( "%d.%d.%d" )
#define SEMVER_FMT_STR_SIMPLE2     ( "%02d.%02d.%02d" )
#define SEMVER_FMT_STR_SIMPLE3     ( "%03d.%03d.%03d" )
#define SEMVER_INITIAL_VERSION_STR ( "0.1.0" )
#define SEMVER_BUF_SIZE            ( 128U )

static int SemVer_ValidPos( int len, int lpos, int rpos )
{
  if ( ( lpos == 0 ) || ( rpos == 0 ) )
  {
    return( 1 );
  }

  if ( ( lpos == 1 ) || ( rpos == len ) )
  {
    return( 1 );
  }

  if ( ( lpos == rpos ) || ( ( lpos + 1 ) == rpos ) )
  {
    return( 1 );
  }

  return( 0 );
}

int SemVer_Init( tSemverVersion *me )
{
  me->major = 0;
  me->minor = 1;
  me->patch = 0;

  return( 0 );
}

int SemVer_ConvertFromStr( tSemverVersion *me, char *str )
{
  int  lpos;
  int  rpos;
  int  len;
  char strtemp[SEMVER_BUF_SIZE] = { 0 };

  strcpy( strtemp, str );
  len = ( int )strlen( strtemp );

  lpos = Utils_StrChr( strtemp, 1, len, '.' );
  rpos = Utils_StrRchr( strtemp, 1, len, '.' );
  if ( 0 == SemVer_ValidPos( len, lpos, rpos ) )
  {
    strtemp[lpos - 1] = 0;
    strtemp[rpos - 1] = 0;
    me->major         = atoi( &strtemp[0] );
    me->minor         = atoi( &strtemp[lpos] );
    me->patch         = atoi( &strtemp[rpos] );

    return( 0 );
  }
  else
  {
    me->major = 0;
    me->minor = 1;
    me->patch = 0;
    return( 1 );
  }
}

int SemVer_ConvertToStr( tSemverVersion *me, char *str, int length )
{
  if ( length == 2 )
  {
    sprintf( str,
             ( char* )SEMVER_FMT_STR_SIMPLE2,
             me->major,
             me->minor,
             ( int )me->patch );
  }
  else if ( length == 3 )
  {
    sprintf( str,
             ( char* )SEMVER_FMT_STR_SIMPLE3,
             me->major,
             me->minor,
             ( int )me->patch );
  }
  else
  {
    sprintf( str,
             ( char* )SEMVER_FMT_STR_SIMPLE,
             me->major,
             me->minor,
             ( int )me->patch );
  }
  return( 0 );
}

int SemVer_IncreaseMajor( tSemverVersion *me )
{
  me->major = me->major + 1;
  me->minor = 0;
  me->patch = 0;

  return( 0 );
}

int SemVer_IncreaseMinor( tSemverVersion *me )
{
  me->minor = me->minor + 1;
  me->patch = 0;

  return( 0 );
}

int SemVer_IncreasePatch( tSemverVersion *me )
{
  me->patch = me->patch + 1;

  return( 0 );
}
