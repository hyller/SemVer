#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include "unity_fixture.h"
#include "run.h"
#include "FormatOutputSpy.h"
#include "fileproxy.h"
#include "version.h"

#define RUN_TEST_FILENAME "version.h"

static const char *expectedOutput;
static const char *actualOutput;
static const char *expectedbuf;

TEST_GROUP( TestRun );

TEST_SETUP( TestRun )
{
  Run_SetFormatOutput( FormatOutputSpy );
  actualOutput = FormatOutputSpy_GetOutput( );
  FormatOutputSpy_Clear( );

  optind = 1;
}

TEST_TEAR_DOWN( TestRun )
{
  Run_SetFormatOutput( printf );
  FileProxy_RemoveFile( RUN_TEST_FILENAME );
}

TEST( TestRun, TestPrintVersion )
{
  char expected[128] = { 0 };
  char *testargv[]   = {
    "semver.exe",
    "-v"
  };
  int  testargc = sizeof( testargv ) / sizeof( testargv[0] );

  Run_SemVer( testargc, testargv );

  snprintf( expected,
            128,
            "\nsemver increases version number in a file %s\n\n",
            VERSION );
  TEST_ASSERT_EQUAL_STRING( expected, actualOutput );
}

TEST( TestRun, TestPrintUsage )
{
  expectedOutput = "\n"
                   "Usage: semver [option] [FILE]\n"
                   "\n"
                   "Options:\n"
                   "-x,  Change major version number.\n"
                   "-y,  Change minor version number.\n"
                   "-z,  Change patch version number.\n"
                   "-l,  Specify version number digits.\n"
                   "-v,  Print program version.\n"
                   "-h,  Print this help screen.\n"
                   "-s,  Process simple version string.\n"
                   "-g,  Get version string.\n"
                   "-a,  Append version string to a file name.\n"
                   "-i,  Initialize version.\n"
                   "-n,  Specify version definition name.\n"
                   "-d,  Include modify date in version header file.\n"
                   "\n";

  char *testargv[] = {
    "semver.exe",
    "-h"
  };
  int  testargc = sizeof( testargv ) / sizeof( testargv[0] );

  Run_SemVer( testargc, testargv );

  TEST_ASSERT_EQUAL_STRING( expectedOutput, actualOutput );
}

TEST( TestRun, InitVersion )
{
  expectedOutput = "Input  version: 0.1.0\n"
                   "Output version: 0.1.0\n";
  expectedbuf = "/* This file is managed by semver, Don't modify manually */\n"
                "/* Visit https://github.com/hyller/SemVer for more information */\n"
                "#ifndef VERSION_H\n"
                "#define VERSION_H\n"
                "\n"
                "#define  VERSION             \"0.1.0\"\n"
                "#define  VERSION_MAJOR       0U\n"
                "#define  VERSION_MINOR       1U\n"
                "#define  VERSION_PATCH       0U\n"
                "\n"
                "#endif\n";
  char actualbuf[FILEPROXY_FILE_BUF_SIZE] = { 0 };

  char *testargv[] = {
    "semver.exe",
    "-i0.1.0",
    RUN_TEST_FILENAME
  };
  int  testargc = sizeof( testargv ) / sizeof( testargv[0] );

  Run_SemVer( testargc, testargv );

  FileProxy_ReadFile( RUN_TEST_FILENAME, actualbuf, FILEPROXY_FILE_BUF_SIZE );

  TEST_ASSERT_EQUAL_STRING( expectedOutput, actualOutput );
  TEST_ASSERT_EQUAL_STRING( expectedbuf, actualbuf );
}

TEST( TestRun, GetVersion )
{
  expectedOutput = "Input  version: 0.1.0\n";

  char *testargv[] = {
    "semver.exe",
    "-g",
    RUN_TEST_FILENAME
  };
  int  testargc = sizeof( testargv ) / sizeof( testargv[0] );

  /// Create version.h and initial version is 0.1.0
  FileProxy_WriteVersion( RUN_TEST_FILENAME, "0.1.0", 0, 0 );

  /// Get version
  Run_SemVer( testargc, testargv );

  TEST_ASSERT_EQUAL_STRING( expectedOutput, actualOutput );
}

TEST( TestRun, AppendFile )
{
  expectedOutput = "Input  version: 0.1.0\n"
                   "New   filename: version_0.1.0.h\n";

  char *testargv[] = {
    "semver.exe",
    "-aversion.h",
    RUN_TEST_FILENAME
  };
  int  testargc = sizeof( testargv ) / sizeof( testargv[0] );

  /// Create version.h and initial version is 0.1.0
  FileProxy_WriteVersion( RUN_TEST_FILENAME, "0.1.0", 0, 0 );

  /// Get version
  Run_SemVer( testargc, testargv );

  TEST_ASSERT_EQUAL_STRING( expectedOutput, actualOutput );
  TEST_ASSERT_TRUE( 0 == FileProxy_AccessFile( "version_0.1.0.h" ) );

  FileProxy_RemoveFile( "version_0.1.0.h" );
}

TEST( TestRun, IncreaseMinor )
{
  expectedOutput = "Input  version: 0.1.0\n"
                   "Output version: 0.2.0\n";
  expectedbuf = "/* This file is managed by semver, Don't modify manually */\n"
                "/* Visit https://github.com/hyller/SemVer for more information */\n"
                "#ifndef VERSION_H\n"
                "#define VERSION_H\n"
                "\n"
                "#define  VERSION             \"0.2.0\"\n"
                "#define  VERSION_MAJOR       0U\n"
                "#define  VERSION_MINOR       2U\n"
                "#define  VERSION_PATCH       0U\n"
                "\n"
                "#endif\n";
  char actualbuf[FILEPROXY_FILE_BUF_SIZE] = { 0 };

  char *testargv[] = {
    "semver.exe",
    "-y",
    RUN_TEST_FILENAME
  };
  int  testargc = sizeof( testargv ) / sizeof( testargv[0] );

  /// Create version.h and initial version is 0.1.0
  FileProxy_WriteVersion( RUN_TEST_FILENAME, "0.1.0", 0, 0 );

  /// Increase version to 0.2.0
  Run_SemVer( testargc, testargv );

  FileProxy_ReadFile( RUN_TEST_FILENAME, actualbuf, FILEPROXY_FILE_BUF_SIZE );

  TEST_ASSERT_EQUAL_STRING( expectedOutput, actualOutput );
  TEST_ASSERT_EQUAL_STRING( expectedbuf, actualbuf );
}

TEST( TestRun, IncreaseMajor )
{
  expectedOutput = "Input  version: 0.1.0\n"
                   "Output version: 1.0.0\n";
  expectedbuf = "/* This file is managed by semver, Don't modify manually */\n"
                "/* Visit https://github.com/hyller/SemVer for more information */\n"
                "#ifndef VERSION_H\n"
                "#define VERSION_H\n"
                "\n"
                "#define  VERSION             \"1.0.0\"\n"
                "#define  VERSION_MAJOR       1U\n"
                "#define  VERSION_MINOR       0U\n"
                "#define  VERSION_PATCH       0U\n"
                "\n"
                "#endif\n";
  char actualbuf[FILEPROXY_FILE_BUF_SIZE] = { 0 };
  char *testargv[]                        = {
    "semver.exe",
    "-x",
    RUN_TEST_FILENAME
  };
  int  testargc = sizeof( testargv ) / sizeof( testargv[0] );

  /// Create version.h and initial version is 0.1.0
  FileProxy_WriteVersion( RUN_TEST_FILENAME, "0.1.0", 0, 0 );

  /// Increase version to 1.0.0
  Run_SemVer( testargc, testargv );

  /// Get file buffer
  FileProxy_ReadFile( RUN_TEST_FILENAME, actualbuf, FILEPROXY_FILE_BUF_SIZE );

  TEST_ASSERT_EQUAL_STRING( expectedOutput, actualOutput );
  TEST_ASSERT_EQUAL_STRING( expectedbuf, actualbuf );
}

TEST( TestRun, IncreasePatch )
{
  expectedOutput = "Input  version: 0.1.0\n"
                   "Output version: 0.1.1\n";
  expectedbuf = "/* This file is managed by semver, Don't modify manually */\n"
                "/* Visit https://github.com/hyller/SemVer for more information */\n"
                "#ifndef VERSION_H\n"
                "#define VERSION_H\n"
                "\n"
                "#define  VERSION             \"0.1.1\"\n"
                "#define  VERSION_MAJOR       0U\n"
                "#define  VERSION_MINOR       1U\n"
                "#define  VERSION_PATCH       1U\n"
                "\n"
                "#endif\n";
  char actualbuf[FILEPROXY_FILE_BUF_SIZE] = { 0 };
  char *testargv[]                        = {
    "semver.exe",
    "-z",
    RUN_TEST_FILENAME
  };
  int  testargc = sizeof( testargv ) / sizeof( testargv[0] );

  /// Create version.h and initial version is 0.1.0
  FileProxy_WriteVersion( RUN_TEST_FILENAME, "0.1.0", 0, 0 );

  /// Increase version to 1.0.0
  Run_SemVer( testargc, testargv );

  /// Get file buffer
  FileProxy_ReadFile( RUN_TEST_FILENAME, actualbuf, FILEPROXY_FILE_BUF_SIZE );

  TEST_ASSERT_EQUAL_STRING( expectedOutput, actualOutput );
  TEST_ASSERT_EQUAL_STRING( expectedbuf, actualbuf );
}

TEST( TestRun, IncreaseMinorSimple )
{
  expectedOutput = "Input  version: 0.1.0\n"
                   "Output version: 0.2.0\n";
  expectedbuf = "0.2.0";
  char actualbuf[FILEPROXY_FILE_BUF_SIZE] = { 0 };
  char *testargv[]                        = {
    "semver.exe",
    "-y",
    "-s",
    RUN_TEST_FILENAME
  };
  int  testargc = sizeof( testargv ) / sizeof( testargv[0] );

  /// Create version.h and initial version is 0.1.0
  FileProxy_WriteVersionSimple( RUN_TEST_FILENAME, "0.1.0", 0 );

  /// Increase version to 0.2.0
  Run_SemVer( testargc, testargv );

  /// Get file buffer
  FileProxy_ReadFile( RUN_TEST_FILENAME, actualbuf, FILEPROXY_FILE_BUF_SIZE );

  TEST_ASSERT_EQUAL_STRING( expectedOutput, actualOutput );
  TEST_ASSERT_EQUAL_STRING( expectedbuf, actualbuf );
}

TEST( TestRun, IncreaseMinorSimpleDate )
{
  expectedOutput = "Input  version: 0.1.0\n"
                   "Output version: 0.2.0\n";
  char *testargv[] = {
    "semver.exe",
    "-y",
    "-s",
    "-d",
    RUN_TEST_FILENAME
  };
  int  testargc = sizeof( testargv ) / sizeof( testargv[0] );

  /// Create version.h and initial version is 0.1.0
  FileProxy_WriteVersionSimple( RUN_TEST_FILENAME, "0.1.0", 1 );

  /// Increase version to 0.2.0
  Run_SemVer( testargc, testargv );

  TEST_ASSERT_EQUAL_STRING( expectedOutput, actualOutput );
}

TEST( TestRun, IncreaseMajorDate )
{
  expectedOutput = "Input  version: 0.1.0\n"
                   "Output version: 1.0.0\n";
  char *testargv[] = {
    "semver.exe",
    "-x",
    "-d",
    RUN_TEST_FILENAME
  };
  int  testargc = sizeof( testargv ) / sizeof( testargv[0] );

  /// Create version.h and initial version is 0.1.0
  FileProxy_WriteVersion( RUN_TEST_FILENAME, "0.1.0", 0, 1 );

  /// Increase version to 1.0.0
  Run_SemVer( testargc, testargv );

  TEST_ASSERT_EQUAL_STRING( expectedOutput, actualOutput );
}

TEST( TestRun, FieldLen2 )
{
  expectedOutput = "Input  version: 00.01.00\n"
                   "Output version: 01.00.00\n";
  expectedbuf = "/* This file is managed by semver, Don't modify manually */\n"
                "/* Visit https://github.com/hyller/SemVer for more information */\n"
                "#ifndef VERSION_H\n"
                "#define VERSION_H\n"
                "\n"
                "#define  VERSION             \"01.00.00\"\n"
                "#define  VERSION_MAJOR       1U\n"
                "#define  VERSION_MINOR       0U\n"
                "#define  VERSION_PATCH       0U\n"
                "\n"
                "#endif\n";
  char actualbuf[FILEPROXY_FILE_BUF_SIZE] = { 0 };
  char *testargv[]                        = {
    "semver.exe",
    "-x",
    "-l2",
    RUN_TEST_FILENAME
  };
  int  testargc = sizeof( testargv ) / sizeof( testargv[0] );

  /// Create version.h and initial version is 00.01.00
  FileProxy_WriteVersion( RUN_TEST_FILENAME, "00.01.00", 0, 0 );

  /// Increase version to 01.00.00
  Run_SemVer( testargc, testargv );

  /// Get file buffer
  FileProxy_ReadFile( RUN_TEST_FILENAME, actualbuf, FILEPROXY_FILE_BUF_SIZE );

  TEST_ASSERT_EQUAL_STRING( expectedOutput, actualOutput );
  TEST_ASSERT_EQUAL_STRING( expectedbuf, actualbuf );
}

TEST( TestRun, FieldLen3 )
{
  expectedOutput = "Input  version: 000.001.000\n"
                   "Output version: 001.000.000\n";
  expectedbuf = "/* This file is managed by semver, Don't modify manually */\n"
                "/* Visit https://github.com/hyller/SemVer for more information */\n"
                "#ifndef VERSION_H\n"
                "#define VERSION_H\n"
                "\n"
                "#define  VERSION             \"001.000.000\"\n"
                "#define  VERSION_MAJOR       1U\n"
                "#define  VERSION_MINOR       0U\n"
                "#define  VERSION_PATCH       0U\n"
                "\n"
                "#endif\n";
  char actualbuf[FILEPROXY_FILE_BUF_SIZE] = { 0 };
  char *testargv[]                        = {
    "semver.exe",
    "-x",
    "-l3",
    RUN_TEST_FILENAME
  };
  int  testargc = sizeof( testargv ) / sizeof( testargv[0] );

  /// Create version.h and initial version is 000.001.000
  FileProxy_WriteVersion( RUN_TEST_FILENAME, "000.001.000", 0, 0 );

  /// Increase version to 001.000.000
  Run_SemVer( testargc, testargv );

  /// Get file buffer
  FileProxy_ReadFile( RUN_TEST_FILENAME, actualbuf, FILEPROXY_FILE_BUF_SIZE );

  TEST_ASSERT_EQUAL_STRING( expectedOutput, actualOutput );
  TEST_ASSERT_EQUAL_STRING( expectedbuf, actualbuf );
}
