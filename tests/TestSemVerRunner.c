#include "unity_fixture.h"

TEST_GROUP_RUNNER(TestSemVer)
{
  RUN_TEST_CASE(TestSemVer, ConvertFromStr);
  RUN_TEST_CASE(TestSemVer, ConvertToStr);
  RUN_TEST_CASE(TestSemVer, ConvertToStr2);
  RUN_TEST_CASE(TestSemVer, ConvertToStr3);
  RUN_TEST_CASE(TestSemVer, Increase255);
}