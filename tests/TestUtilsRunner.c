#include "unity_fixture.h"

TEST_GROUP_RUNNER(TestUtils)
{
  RUN_TEST_CASE(TestUtils, ChangeFileName);
  RUN_TEST_CASE(TestUtils, NoSuffix);
  RUN_TEST_CASE(TestUtils, TestStrFind);  
  RUN_TEST_CASE(TestUtils, TestStrChr);  
  RUN_TEST_CASE(TestUtils, TestStrRchr);  
}