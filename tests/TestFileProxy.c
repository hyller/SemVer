#include "unity_fixture.h"
#include "fileproxy.h"

#define FILEPROXY_TEST_FILENAME "version.h"

TEST_GROUP( TestFileProxy );

TEST_SETUP( TestFileProxy )
{
}

TEST_TEAR_DOWN( TestFileProxy )
{   
  FileProxy_RemoveFile( FILEPROXY_TEST_FILENAME );
}

TEST( TestFileProxy, SimpleVersion )
{
  char verstr[128]  = { 0 };
  char *verstrwrite = "7.8.9";

  FileProxy_WriteVersionSimple( FILEPROXY_TEST_FILENAME, verstrwrite, 0 );
  FileProxy_ReadVersionSimple( FILEPROXY_TEST_FILENAME, verstr );

  TEST_ASSERT_EQUAL_STRING( verstrwrite, verstr );
}

TEST( TestFileProxy, FullVersionName )
{
  char verstr[128]  = { 0 };
  char *verstrwrite = "4.5.6";

  FileProxy_WriteVersion( FILEPROXY_TEST_FILENAME, verstrwrite, "TESTVERSION", 0 );
  FileProxy_ReadVersion( FILEPROXY_TEST_FILENAME, verstr, "TESTVERSION" );

  TEST_ASSERT_EQUAL_STRING( verstrwrite, verstr );
}

TEST( TestFileProxy, ReadFileNull )
{
  char buf[FILEPROXY_FILE_BUF_SIZE]  = { 0 };
  int ret;

  ret = FileProxy_ReadFile( NULL, buf, FILEPROXY_FILE_BUF_SIZE );

  TEST_ASSERT_EQUAL_INT( 1, ret );
}

TEST( TestFileProxy, WriteFileNull )
{
  char buf[FILEPROXY_FILE_BUF_SIZE]  = { 0 };
  int ret;

  ret = FileProxy_WriteFile( NULL, buf, FILEPROXY_FILE_BUF_SIZE );

  TEST_ASSERT_EQUAL_INT( 1, ret );
}

TEST( TestFileProxy, CopyFileNull )
{
  int ret;
  
  ret = FileProxy_CopyFile( NULL, NULL );

  TEST_ASSERT_EQUAL_INT( 1, ret );
}

