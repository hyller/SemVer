#include "unity_fixture.h"

TEST_GROUP_RUNNER( TestSemVer )
{
  RUN_TEST_CASE( TestSemVer, InitByStrInvalid );
  RUN_TEST_CASE( TestSemVer, InitByStrInvalid2 );
  RUN_TEST_CASE( TestSemVer, InitByStrInvalid3 );
  RUN_TEST_CASE( TestSemVer, InitByStr );
  RUN_TEST_CASE( TestSemVer, InitByStr2 );
  RUN_TEST_CASE( TestSemVer, InitByStr3 );
  RUN_TEST_CASE( TestSemVer, SemVerInit );
  RUN_TEST_CASE( TestSemVer, SemVerBumpMajor );
  RUN_TEST_CASE( TestSemVer, SemVerBumpMinor );
  RUN_TEST_CASE( TestSemVer, SemVerBumpPatch );
  RUN_TEST_CASE( TestSemVer, SemVerBumpPatch255 );
}
