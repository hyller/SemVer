#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

#define assert( x )

#define idx( i, len )      ( ( i ) <= 0 ? ( i ) + ( len ) : ( i ) - 1 )
#define convert( s, i, j ) do { int len;\
                                assert( s ); len = ( int )strlen( s );\
                                i                = idx( i, len ); j = idx( j, len );\
                                if ( i > j ) { int t = i; i = j; j = t; }\
                                assert( i >= 0 && j <= len ); } while ( 0 )

void ChangFileName( char *oldname, char *append, char *newname )
{
  char prefix[128] = { 0 };
  char sufix[128]  = { 0 };
  int  pos;
  int  len;

  len = ( int )strlen( oldname );
  pos = Str_chr( oldname, 1, len + 1, '.' );

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

int Str_chr( const char *s, int i, int j, int c )
{
  convert( s, i, j );
  for (; i < j; i++ )
  {
    if ( s[i] == c )
    {
      return i + 1;
    }
  }
  return 0;
}

int Str_rchr( const char *s, int i, int j, int c )
{
  convert( s, i, j );
  while ( j > i )
    if ( s[--j] == c )
    {
      return j + 1;
    }
  return 0;
}

int Str_find( const char *s, int i, int j, const char *str )
{
  int len2;

  convert( s, i, j );
  assert( str );
  len2 = ( int )strlen( str );
  if ( len2 == 0 )
  {
    return i + 1;
  }
  else if ( len2 == 1 )
  {
    for (; i < j; i++ )
    {
      if ( s[i] == *str )
      {
        return i + 1;
      }
    }
  }
  else
  {
    for (; i + len2 <= j; i++ )
    {
      if ( ( strncmp( &s[i], str, (size_t)len2 ) == 0 ) )
      {
        return i + 1;
      }
    }
  }
  return 0;
}
