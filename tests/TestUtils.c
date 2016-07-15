#include <string.h>
#include "unity_fixture.h"
#include "utils.h"

TEST_GROUP( TestUtils );

TEST_SETUP( TestUtils )
{
}

TEST_TEAR_DOWN( TestUtils )
{
}

TEST( TestUtils, ChangeFileName )
{
  char name[128];

  Utils_StrAppend( "mytest.hex", "0.1.0", name );

  TEST_ASSERT_EQUAL_STRING( "mytest_0.1.0.hex", name );
}

TEST( TestUtils, NoSuffix )
{
  char name[128];

  Utils_StrAppend( "mytest", "0.1.0", name );

  TEST_ASSERT_EQUAL_STRING( "mytest_0.1.0", name );
}

TEST( TestUtils, TestStrFind )
{
  char str[]  = "hellostrfind";
  char find[] = "str";
  int  ret;

  ret = Utils_StrFind( str, 1, strlen( str ), find );

  TEST_ASSERT_EQUAL_INT( 6, ret );
}

TEST( TestUtils, TestStrFindStr0 )
{
  char str[]  = "hellostrfind";
  char find[] = "";
  int  ret;

  ret = Utils_StrFind( str, 1, strlen( str ), find );

  TEST_ASSERT_EQUAL_INT( 1, ret );
}

TEST( TestUtils, TestStrFindStr1 )
{
  char str[]  = "hellostrfind";
  char find[] = "s";
  int  ret;

  ret = Utils_StrFind( str, 1, strlen( str ), find );

  TEST_ASSERT_EQUAL_INT( 6, ret );
}

TEST( TestUtils, TestStrFindNoStr )
{
  char str[]  = "hellostrfind";
  char find[] = "xxx";
  int  ret;

  ret = Utils_StrFind( str, 1, strlen( str ), find );

  TEST_ASSERT_EQUAL_INT( 0, ret );
}

TEST( TestUtils, TestStrChr )
{
  char str[] = "hellostrfind";
  int  ret;

  ret = Utils_StrChr( str, 1, strlen( str ), 'l' );

  TEST_ASSERT_EQUAL_INT( 3, ret );
}

TEST( TestUtils, TestStrRchr )
{
  char str[] = "hellostrfind";
  int  ret;

  ret = Utils_StrRchr( str, 1, strlen( str ), 'l' );

  TEST_ASSERT_EQUAL_INT( 4, ret );
}
