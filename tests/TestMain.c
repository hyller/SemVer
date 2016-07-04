#include "unity_fixture.h"

static void RunAllTests( void )
{
  RUN_TEST_GROUP( TestFileProxy );
  RUN_TEST_GROUP( TestParse );
  RUN_TEST_GROUP( TestSemVer );
  RUN_TEST_GROUP( TestUtils );
  RUN_TEST_GROUP( TestRun );
}

int main( int argc, const char *argv[] )
{
  return( UnityMain( argc, argv, RunAllTests ) );
}
