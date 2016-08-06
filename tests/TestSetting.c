#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include "unity_fixture.h"
#include "setting.h"

tSetting as;

TEST_GROUP( TestSetting );

TEST_SETUP( TestSetting )
{
  Setting_Init( &as );
  optind = 1; // Reset to 1 so that getopt can work again
  opterr = 1;
  optopt = '?';
}

TEST_TEAR_DOWN( TestSetting )
{
}

TEST( TestSetting, ParseAll )
{
  char *testargv[] = {
    "semver",
    "-y",
    "-v",
    "-h",
    "-g",
    "-l2",
    "-ahello",
    "-i2.3.4",
    "-nTESTVERSION",
    "version.h"
  };
  int  testargc = sizeof( testargv ) / sizeof( testargv[0] );

  Setting_Init( &as );
  Setting_Parse( &as, testargc, ( char** )testargv );

  TEST_ASSERT_EQUAL_INT( 1, as.version );
  TEST_ASSERT_EQUAL_INT( 1, as.help );
  TEST_ASSERT_EQUAL_INT( 1, as.index );
  TEST_ASSERT_EQUAL_INT( 1, as.append );
  TEST_ASSERT_EQUAL_INT( 1, as.init );
  TEST_ASSERT_EQUAL_INT( 2, as.length );
  TEST_ASSERT_EQUAL_INT( 1, as.get);
  TEST_ASSERT_EQUAL_STRING( "hello", as.appendarg );
  TEST_ASSERT_EQUAL_STRING( "version.h", as.filename );
  TEST_ASSERT_EQUAL_STRING( "2.3.4", as.initarg );
  TEST_ASSERT_EQUAL_STRING( "TESTVERSION", as.vername );
}

TEST( TestSetting, ParseAll2 )
{
  char *testargv[] = {
    "semver",
    "-x",
    "-v",
    "-?",
    "-ahello",
    "-i2.3.4",
    "-nTESTVERSION",
    "version.h"
  };
  int  testargc = sizeof( testargv ) / sizeof( testargv[0] );

  Setting_Init( &as );
  Setting_Parse( &as, testargc, ( char** )testargv );

  TEST_ASSERT_EQUAL_INT( 1, as.version );
  TEST_ASSERT_EQUAL_INT( 1, as.help );
  TEST_ASSERT_EQUAL_INT( 2, as.index );
  TEST_ASSERT_EQUAL_INT( 1, as.append );
  TEST_ASSERT_EQUAL_INT( 1, as.init );
  TEST_ASSERT_EQUAL_INT( 0, as.length );
  TEST_ASSERT_EQUAL_STRING( "hello", as.appendarg );
  TEST_ASSERT_EQUAL_STRING( "version.h", as.filename );
  TEST_ASSERT_EQUAL_STRING( "2.3.4", as.initarg );
  TEST_ASSERT_EQUAL_STRING( "TESTVERSION", as.vername );
}

TEST( TestSetting, ParseAll3 )
{
  char *testargv[] = {
    "semver",
    "-z",
    "-v",
    "-?",
    "-ahello",
    "-i2.3.4",
    "-nTESTVERSION",
    "version.h"
  };
  int  testargc = sizeof( testargv ) / sizeof( testargv[0] );

  Setting_Init( &as );
  Setting_Parse( &as, testargc, ( char** )testargv );

  TEST_ASSERT_EQUAL_INT( 1, as.version );
  TEST_ASSERT_EQUAL_INT( 1, as.help );
  TEST_ASSERT_EQUAL_INT( 0, as.index );
  TEST_ASSERT_EQUAL_INT( 1, as.append );
  TEST_ASSERT_EQUAL_INT( 1, as.init );
  TEST_ASSERT_EQUAL_INT( 0, as.length );
  TEST_ASSERT_EQUAL_STRING( "hello", as.appendarg );
  TEST_ASSERT_EQUAL_STRING( "version.h", as.filename );
  TEST_ASSERT_EQUAL_STRING( "2.3.4", as.initarg );
  TEST_ASSERT_EQUAL_STRING( "TESTVERSION", as.vername );
}

TEST( TestSetting, NoArgv )
{
  char *testargv[] = {
    "semver",
  };
  int  testargc = sizeof( testargv ) / sizeof( testargv[0] );

  Setting_Init( &as );
  Setting_Parse( &as, testargc, ( char** )testargv );

  TEST_ASSERT_EQUAL_INT( 1, as.error);
}

