#include "unity_fixture.h"

TEST_GROUP_RUNNER( TestFileProxy )
{
  RUN_TEST_CASE( TestFileProxy, TxtFile );
  RUN_TEST_CASE( TestFileProxy, CHeaderFile );
  RUN_TEST_CASE( TestFileProxy, JavaFile );
  RUN_TEST_CASE( TestFileProxy, ReadFileNull );
  RUN_TEST_CASE( TestFileProxy, WriteFileNull );
  RUN_TEST_CASE( TestFileProxy, CopyFileNull );
  RUN_TEST_CASE( TestFileProxy, GetFileTypeCHeader );
  RUN_TEST_CASE( TestFileProxy, GetFileTypeCHeader2 );
  RUN_TEST_CASE( TestFileProxy, GetFileTypeTxt );
  RUN_TEST_CASE( TestFileProxy, GetFileTypeTxt2 );
  RUN_TEST_CASE( TestFileProxy, GetFileTypeJava );
}
