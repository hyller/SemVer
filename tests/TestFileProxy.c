#include "unity_fixture.h"
#include "fileproxy.h"

#define FILEPROXY_TEST_FILENAME_CHEADER "version.h"
#define FILEPROXY_TEST_FILENAME_TXT     "version"
#define FILEPROXY_TEST_FILENAME_JAVA    "version.java"

static const char *expectedbuf;

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

  expectedbuf = "7.8.9";
  char actualbuf[FILEPROXY_FILE_BUF_SIZE] = { 0 };

  FileProxy_WriteVersion( FILEPROXY_TEST_FILENAME_TXT, verstrwrite, "TESTVERSION" );
  FileProxy_ReadVersion( FILEPROXY_TEST_FILENAME_TXT, verstr, "TESTVERSION" );
  FileProxy_ReadFile( FILEPROXY_TEST_FILENAME_TXT, actualbuf, FILEPROXY_FILE_BUF_SIZE );

  TEST_ASSERT_EQUAL_STRING( verstrwrite, verstr );
  TEST_ASSERT_EQUAL_STRING( expectedbuf, actualbuf );
}

TEST( TestFileProxy, CHeaderFile )
{
  char verstr[128]  = { 0 };
  char *verstrwrite = "4.5.6";

  expectedbuf = "/* This file is managed by semver, Don't modify manually */\n"
                "/* Visit https://github.com/hyller/SemVer for more information */\n"
                "#ifndef TESTVERSION_H\n"
                "#define TESTVERSION_H\n"
                "\n"
                "#define  TESTVERSION             \"4.5.6\"\n"
                "#define  TESTVERSION_MAJOR       4U\n"
                "#define  TESTVERSION_MINOR       5U\n"
                "#define  TESTVERSION_PATCH       6U\n"
                "\n"
                "#endif\n";
  char actualbuf[FILEPROXY_FILE_BUF_SIZE] = { 0 };

  FileProxy_WriteVersion( FILEPROXY_TEST_FILENAME_CHEADER, verstrwrite, "TESTVERSION" );
  FileProxy_ReadVersion( FILEPROXY_TEST_FILENAME_CHEADER, verstr, "TESTVERSION" );
  FileProxy_ReadFile( FILEPROXY_TEST_FILENAME_CHEADER, actualbuf, FILEPROXY_FILE_BUF_SIZE );

  TEST_ASSERT_EQUAL_STRING( verstrwrite, verstr );
  TEST_ASSERT_EQUAL_STRING( expectedbuf, actualbuf );
}

TEST( TestFileProxy, JavaFile )
{
  char verstr[128]  = { 0 };
  char *verstrwrite = "4.5.6";

  expectedbuf = "// This file is managed by semver, Don't modify manually\n"
                "// Visit https://github.com/hyller/SemVer for more information\n"
                "public class version\n"
                "{\n"
                "    public static final String TESTVERSION       = \"4.5.6\";\n"
                "    public static final int    TESTVERSION_MAJOR = 4;\n"
                "    public static final int    TESTVERSION_MINOR = 5;\n"
                "    public static final int    TESTVERSION_PATCH = 6;\n"
                "}\n";
  char actualbuf[FILEPROXY_FILE_BUF_SIZE] = { 0 };

  FileProxy_WriteVersion( FILEPROXY_TEST_FILENAME_JAVA, verstrwrite, "TESTVERSION" );
  FileProxy_ReadVersion( FILEPROXY_TEST_FILENAME_JAVA, verstr, "TESTVERSION" );
  FileProxy_ReadFile( FILEPROXY_TEST_FILENAME_JAVA, actualbuf, FILEPROXY_FILE_BUF_SIZE );

  TEST_ASSERT_EQUAL_STRING( verstrwrite, verstr );
  TEST_ASSERT_EQUAL_STRING( expectedbuf, actualbuf );
}

TEST( TestFileProxy, ReadFileNull )
{
  char buf[FILEPROXY_FILE_BUF_SIZE] = { 0 };
  int  ret;

  ret = FileProxy_ReadFile( NULL, buf, FILEPROXY_FILE_BUF_SIZE );

  TEST_ASSERT_EQUAL_INT( 1, ret );
}

TEST( TestFileProxy, WriteFileNull )
{
  char buf[FILEPROXY_FILE_BUF_SIZE] = { 0 };
  int  ret;

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
