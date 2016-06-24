#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(TestUtils)
{
  RUN_TEST_CASE(TestUtils, ChangeFileName);
  RUN_TEST_CASE(TestUtils, NoSuffix);
}