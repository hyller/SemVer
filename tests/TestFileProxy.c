#include "unity_fixture.h"
#include "fileproxy.h"

#define FILEPROXY_TEST_FILENAME_CHEADER "version.h"
#define FILEPROXY_TEST_FILENAME_TXT     "version"
#define FILEPROXY_TEST_FILENAME_JAVA    "version.java"

TEST_GROUP( TestFileProxy );

TEST_SETUP( TestFileProxy )
{
}

TEST_TEAR_DOWN( TestFileProxy )
{   
  FileProxy_RemoveFile( FILEPROXY_TEST_FILENAME_CHEADER );
  FileProxy_RemoveFile( FILEPROXY_TEST_FILENAME_TXT );
  FileProxy_RemoveFile( FILEPROXY_TEST_FILENAME_JAVA );
}

TEST( TestFileProxy, TxtFile )
{
  char verstr[128]  = { 0 };
  char *verstrwrite = "7.8.9";

  FileProxy_WriteVersion( FILEPROXY_TEST_FILENAME_TXT, verstrwrite, "TESTVERSION", 0 );
  FileProxy_ReadVersion( FILEPROXY_TEST_FILENAME_TXT, verstr, "TESTVERSION" );

  TEST_ASSERT_EQUAL_STRING( verstrwrite, verstr );
}

TEST( TestFileProxy, CHeaderFile )
{
  char verstr[128]  = { 0 };
  char *verstrwrite = "4.5.6";

  FileProxy_WriteVersion( FILEPROXY_TEST_FILENAME_CHEADER, verstrwrite, "TESTVERSION", 0 );
  FileProxy_ReadVersion( FILEPROXY_TEST_FILENAME_CHEADER, verstr, "TESTVERSION" );

  TEST_ASSERT_EQUAL_STRING( verstrwrite, verstr );
}

TEST( TestFileProxy, JavaFile )
{
  char verstr[128]  = { 0 };
  char *verstrwrite = "4.5.6";

  FileProxy_WriteVersion( FILEPROXY_TEST_FILENAME_JAVA, verstrwrite, "TESTVERSION", 0 );
  FileProxy_ReadVersion( FILEPROXY_TEST_FILENAME_JAVA, verstr, "TESTVERSION" );

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

TEST( TestFileProxy, GetFileTypeCHeader )
{
  tFileProxyFileType ret;
  
  ret = FileProxy_GetFileType( "version.h" );

  TEST_ASSERT_EQUAL_INT( eFileProxyFileType_CHeader, ret );
}

TEST( TestFileProxy, GetFileTypeCHeader2 )
{
  tFileProxyFileType ret;
  
  ret = FileProxy_GetFileType( "version.H" );

  TEST_ASSERT_EQUAL_INT( eFileProxyFileType_CHeader, ret );
}

TEST( TestFileProxy, GetFileTypeTxt )
{
  tFileProxyFileType ret;
  
  ret = FileProxy_GetFileType( "version.txt" );

  TEST_ASSERT_EQUAL_INT( eFileProxyFileType_Txt, ret );
}

TEST( TestFileProxy, GetFileTypeTxt2 )
{
  tFileProxyFileType ret;
  
  ret = FileProxy_GetFileType( "version" );

  TEST_ASSERT_EQUAL_INT( eFileProxyFileType_Txt, ret );
}

TEST( TestFileProxy, GetFileTypeJava )
{
  tFileProxyFileType ret;
  
  ret = FileProxy_GetFileType( "version.java" );

  TEST_ASSERT_EQUAL_INT( eFileProxyFileType_Java, ret );
}
