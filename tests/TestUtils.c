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

  Utils_StrAppend( ( char* )"mytest.hex", ( char* )"0.1.0", name );

  TEST_ASSERT_EQUAL_STRING( "mytest_0.1.0.hex", name );
}

TEST( TestUtils, NoSuffix )
{
  char name[128];

  Utils_StrAppend( ( char* )"mytest", ( char* )"0.1.0", name );

  TEST_ASSERT_EQUAL_STRING( "mytest_0.1.0", name );
}

TEST( TestUtils, TestStrFind )
{
  char str[] = "hellostrfind";
  char find[] = "str";
  int  ret;
   
  ret = Utils_StrFind( str, 1, strlen(str), find );

  TEST_ASSERT_EQUAL_INT( 6, ret );
}

TEST( TestUtils, TestStrChr )
{
  char str[] = "hellostrfind";
  int  ret;
   
  ret = Utils_StrChr( str, 1, strlen(str), 'l' );

  TEST_ASSERT_EQUAL_INT( 3, ret );
}

TEST( TestUtils, TestStrRchr )
{
  char str[] = "hellostrfind";
  int  ret;
   
  ret = Utils_StrRchr( str, 1, strlen(str), 'l' );

  TEST_ASSERT_EQUAL_INT( 4, ret );
}

