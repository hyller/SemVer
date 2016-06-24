#include <string.h>
#include "unity_fixture.h"
#include "setting.h"

tSetting as;

TEST_GROUP( TestParse );

TEST_SETUP( TestParse )
{
  Setting_Init( &as );
}

TEST_TEAR_DOWN( TestParse )
{
}

TEST( TestParse, ParseAll )
{
  char *testargv[] = {
    ( char* )"semver",
    ( char* )"-x",
    ( char* )"-v",
    ( char* )"-h",
    ( char* )"-s",
    ( char* )"-l2",
    ( char* )"-ahello",
    ( char* )"-i2.3.4",
    ( char* )"-nTESTVERSION",
    ( char* )"version.h"
  };
  int  testargc = sizeof( testargv ) / sizeof( testargv[0] );

  Setting_Init( &as );
  Setting_Parse( &as, testargc, ( char** )testargv );

  TEST_ASSERT_EQUAL_INT( 1, as.version );
  TEST_ASSERT_EQUAL_INT( 1, as.help );
  TEST_ASSERT_EQUAL_INT( 2, as.index );
  TEST_ASSERT_EQUAL_INT( 1, as.simple );
  TEST_ASSERT_EQUAL_INT( 1, as.append );
  TEST_ASSERT_EQUAL_INT( 1, as.init );
  TEST_ASSERT_EQUAL_INT( 2, as.length );
  TEST_ASSERT_EQUAL_STRING( "hello", as.appendarg );
  TEST_ASSERT_EQUAL_STRING( "version.h", as.filename );
  TEST_ASSERT_EQUAL_STRING( "2.3.4", as.initarg );
  TEST_ASSERT_EQUAL_STRING( "TESTVERSION", as.vername );
}
