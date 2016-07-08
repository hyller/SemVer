#include "unity_fixture.h"

TEST_GROUP_RUNNER( TestSetting )
{
  RUN_TEST_CASE( TestSetting, ParseAll );
  RUN_TEST_CASE( TestSetting, ParseAll2 );
  RUN_TEST_CASE( TestSetting, ParseAll3 )
  RUN_TEST_CASE( TestSetting, NoArgv );
}
