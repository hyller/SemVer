#include "unity.h"
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

  ChangFileName( ( char* )"mytest.hex", ( char* )"0.1.0", name );

  TEST_ASSERT_EQUAL_STRING( "mytest_0.1.0.hex", name );
}

TEST( TestUtils, NoSuffix )
{
  char name[128];

  ChangFileName( ( char* )"mytest", ( char* )"0.1.0", name );

  TEST_ASSERT_EQUAL_STRING( "mytest_0.1.0", name );
}
