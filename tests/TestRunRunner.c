#include "unity_fixture.h"

TEST_GROUP_RUNNER( TestRun )
{
  RUN_TEST_CASE( TestRun, TestPrintVersion );
  RUN_TEST_CASE( TestRun, TestPrintUsage );
  RUN_TEST_CASE( TestRun, TestRun3 );
  RUN_TEST_CASE( TestRun, TestRun4 );
  RUN_TEST_CASE( TestRun, TestRun5 );
}
