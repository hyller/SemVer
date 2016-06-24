#include "unity_fixture.h"

TEST_GROUP_RUNNER(TestFileProxy)
{
  RUN_TEST_CASE(TestFileProxy, SimpleVersion);
  RUN_TEST_CASE(TestFileProxy, FullVersionName);
}