#include "stdio.h"
#include "version.h"

int main( int argc, char **argv )
{
  printf("%s\n",VERSION);
  printf("%d\n",VERSION_MAJOR);
  printf("%d\n",VERSION_MINOR);
  printf("%d\n",VERSION_PATCH);
  
  return( 0 );
}
