#include "unity_fixture.h"

TEST_GROUP_RUNNER( TestRun )
{
  RUN_TEST_CASE( TestRun, TestPrintVersion );
  RUN_TEST_CASE( TestRun, TestPrintUsage );
  RUN_TEST_CASE( TestRun, InitVersion );
  RUN_TEST_CASE( TestRun, GetVersion );
  RUN_TEST_CASE( TestRun, GetVersion2 );  
  RUN_TEST_CASE( TestRun, AppendFile );
  RUN_TEST_CASE( TestRun, IncreaseMinor );
  RUN_TEST_CASE( TestRun, IncreaseMinorJava );
  RUN_TEST_CASE( TestRun, IncreaseMajor );
  RUN_TEST_CASE( TestRun, IncreasePatch );
  RUN_TEST_CASE( TestRun, IncreaseMinorSimple );
  RUN_TEST_CASE( TestRun, IncreaseMinorSimpleDate );
  RUN_TEST_CASE( TestRun, IncreaseMajorDate );
  RUN_TEST_CASE( TestRun, FieldLen2 );
  RUN_TEST_CASE( TestRun, FieldLen3 );
}
