#include "unity_fixture.h"

TEST_GROUP_RUNNER( TestRun )
{
  RUN_TEST_CASE( TestRun, TestPrintVersion );
  RUN_TEST_CASE( TestRun, TestPrintUsage );
  RUN_TEST_CASE( TestRun, InitVersion );
  RUN_TEST_CASE( TestRun, GetVersion );
  RUN_TEST_CASE( TestRun, AppendFile );
  RUN_TEST_CASE( TestRun, IncreaseMinor );
  RUN_TEST_CASE( TestRun, IncreaseMajor );
}
