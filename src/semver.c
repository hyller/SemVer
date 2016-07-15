#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "semver.h"
#include "utils.h"

#define SEMVER_FMT_STR_SIMPLE      ( "%d.%d.%d" )
#define SEMVER_FMT_STR_SIMPLE2     ( "%02d.%02d.%02d" )
#define SEMVER_FMT_STR_SIMPLE3     ( "%03d.%03d.%03d" )
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

static int SemVer_ConvertFromStr( tSemver *me, char *str )
{
  int  lpos;
  int  rpos;
  int  len;
  char strtemp[SEMVER_BUF_SIZE] = { 0 };

  strcpy( strtemp, str );
  len = strlen( strtemp );

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

static int SemVer_UpdateStr( tSemver *me )
{
  if ( me->fieldlen == 2 )
  {
    sprintf( me->str,
             SEMVER_FMT_STR_SIMPLE2,
             me->major,
             me->minor,
             me->patch );
  }
  else if ( me->fieldlen == 3 )
  {
    sprintf( me->str,
             SEMVER_FMT_STR_SIMPLE3,
             me->major,
             me->minor,
             me->patch );
  }
  else
  {
    sprintf( me->str,
             SEMVER_FMT_STR_SIMPLE,
             me->major,
             me->minor,
             me->patch );
  }
  
  return( 0 );
}

int SemVer_Init( tSemver *me )
{
  me->major    = 0;
  me->minor    = 1;
  me->patch    = 0;
  me->fieldlen = 0;

  SemVer_UpdateStr( me );

  return( 0 );
}

int SemVer_InitByStr( tSemver *me, char *str )
{
  int ret;

  SemVer_Init( me );

  ret = SemVer_ConvertFromStr( me, str );

  if ( ret == 0 )
  {
    ret = SemVer_UpdateStr( me );
  }

  return( ret );
}

int SemVer_InitByStrFieldlen( tSemver *me, char *str, int len )
{
  int ret;

  SemVer_Init( me );

  ret = SemVer_ConvertFromStr( me, str );

  if ( ret == 0 )
  {
    me->fieldlen = len;

    ret = SemVer_UpdateStr( me );;
  }

  return( ret );
}

int SemVer_BumpMajor( tSemver *me )
{
  me->major = me->major + 1;
  me->minor = 0;
  me->patch = 0;

  SemVer_UpdateStr( me );

  return( 0 );
}

int SemVer_BumpMinor( tSemver *me )
{
  me->minor = me->minor + 1;
  me->patch = 0;

  SemVer_UpdateStr( me );

  return( 0 );
}

int SemVer_BumpPatch( tSemver *me )
{
  me->patch = me->patch + 1;

  SemVer_UpdateStr( me );

  return( 0 );
}
