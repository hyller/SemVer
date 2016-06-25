#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

#define Utils_Idx( i, len )      ( ( i ) <= 0 ? ( i ) + ( len ) : ( i ) - 1 )
#define Utils_Convert( s, i, j ) do {\
    int len;\
    len = ( int )strlen( s );\
    i   = Utils_Idx( i, len );\
    j   = Utils_Idx( j, len );\
    if ( i > j ) { int t = i; i = j; j = t; }\
} while ( 0 )

void Utils_StrAppend( char *oldname, char *append, char *newname )
{
  char prefix[128] = { 0 };
  char sufix[128]  = { 0 };
  int  pos;
  int  len;

  len = ( int )strlen( oldname );
  pos = Utils_StrChr( oldname, 1, len + 1, '.' );

  if ( pos != 0 )
  {
    memcpy( prefix, oldname, ( unsigned int )pos - 1 );
    memcpy( sufix, &oldname[pos], ( unsigned int )( ( int )len - pos ) );

    sprintf( newname, "%s_%s.%s", prefix, ( char* )append, sufix );
  }
  else
  {
    sprintf( newname, "%s_%s", oldname, ( char* )append );
  }
}

int Utils_StrChr( const char *s, int i, int j, int c )
{
  Utils_Convert( s, i, j );
  for (; i < j; i++ )
  {
    if ( s[i] == c )
    {
      return( i + 1 );
    }
  }
  return( 0 );
}

int Utils_StrRchr( const char *s, int i, int j, int c )
{
  Utils_Convert( s, i, j );
  while ( j > i )
  {
    if ( s[--j] == c )
    {
      return( j + 1 );
    }
  }
  return( 0 );
}

int Utils_StrFind( const char *s, int i, int j, const char *str )
{
  int len2;

  Utils_Convert( s, i, j );
  len2 = ( int )strlen( str );
  if ( len2 == 0 )
  {
    return( i + 1 );
  }
  else if ( len2 == 1 )
  {
    for (; i < j; i++ )
    {
      if ( s[i] == *str )
      {
        return( i + 1 );
      }
    }
  }
  else
  {
    for (; i + len2 <= j; i++ )
    {
      if ( ( strncmp( &s[i], str, ( size_t )len2 ) == 0 ) )
      {
        return( i + 1 );
      }
    }
  }
  return( 0 );
}
