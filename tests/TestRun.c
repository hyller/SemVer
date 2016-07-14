#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include "unity_fixture.h"
#include "run.h"
#include "FormatOutputSpy.h"
#include "fileproxy.h"

static const char *expectedOutput;
static const char *actualOutput;
static const char *expectedbuf;

TEST_GROUP( TestRun );

TEST_SETUP( TestRun )
{
  Run_SetFormatOutput( FormatOutputSpy );
  actualOutput = FormatOutputSpy_GetOutput( );
  FormatOutputSpy_Clear( );

  optind = 1; // Reset to 1 so that getopt can work again
}

TEST_TEAR_DOWN( TestRun )
{
  Run_SetFormatOutput( printf );
}

TEST( TestRun, TestPrintVersion )
{
  expectedOutput = "\n"
                   "semver increases version number in a file 0.11.1\n"
                   "\n";
  char *testargv[] = {
    ( char* )"semver.exe",
    ( char* )"-v"
  };
  int  testargc = sizeof( testargv ) / sizeof( testargv[0] );

  Run_SemVer( testargc, testargv );

  TEST_ASSERT_EQUAL_STRING( expectedOutput, actualOutput );
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
    ( char* )"semver.exe",
    ( char* )"-h"
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
    "version.h"
  };
  int  testargc = sizeof( testargv ) / sizeof( testargv[0] );

  Run_SemVer( testargc, testargv );

  FileProxy_ReadFile( "version.h", actualbuf, FILEPROXY_FILE_BUF_SIZE );

  /// Clear generated file
  remove( "version.h" );

  TEST_ASSERT_EQUAL_STRING( expectedOutput, actualOutput );
  TEST_ASSERT_EQUAL_STRING( expectedbuf, actualbuf );
}

TEST( TestRun, GetVersion )
{
  expectedOutput = "Input  version: 0.1.0\n";

  char *testargv[] = {
    "semver.exe",
    "-g",
    "version.h"
  };
  int  testargc = sizeof( testargv ) / sizeof( testargv[0] );

  /// Create version.h and initial version is 0.1.0
  FileProxy_WriteVersion( "version.h", "0.1.0", 0, 0 );

  /// Get version
  Run_SemVer( testargc, testargv );

  /// Clear generated file
  remove( "version.h" );

  TEST_ASSERT_EQUAL_STRING( expectedOutput, actualOutput );
}

TEST( TestRun, AppendFile )
{
  expectedOutput = "Input  version: 0.1.0\n"
                   "New   filename: version_0.1.0.h\n";

  char *testargv[] = {
    "semver.exe",
    "-aversion.h",
    "version.h"
  };
  int  testargc = sizeof( testargv ) / sizeof( testargv[0] );

  /// Create version.h and initial version is 0.1.0
  FileProxy_WriteVersion( "version.h", "0.1.0", 0, 0 );

  /// Get version
  Run_SemVer( testargc, testargv );

  TEST_ASSERT_EQUAL_STRING( expectedOutput, actualOutput );
  TEST_ASSERT_TRUE( !FileProxy_IsFileExist( "version_0.1.0.h" ) );

  /// Clear generated file
  remove( "version.h" );
  remove( "version_0.1.0.h" );
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
    "version.h"
  };
  int  testargc = sizeof( testargv ) / sizeof( testargv[0] );

  /// Create version.h and initial version is 0.1.0
  FileProxy_WriteVersion( "version.h", "0.1.0", 0, 0 );

  /// Increase version to 0.2.0
  Run_SemVer( testargc, testargv );

  FileProxy_ReadFile( "version.h", actualbuf, FILEPROXY_FILE_BUF_SIZE );

  /// Clear generated file
  remove( "version.h" );

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
    "version.h"
  };
  int  testargc = sizeof( testargv ) / sizeof( testargv[0] );

  /// Create version.h and initial version is 0.1.0
  FileProxy_WriteVersion( "version.h", "0.1.0", 0, 0 );

  /// Increase version to 1.0.0
  Run_SemVer( testargc, testargv );

  /// Get file buffer
  FileProxy_ReadFile( "version.h", actualbuf, FILEPROXY_FILE_BUF_SIZE );

  /// Clear generated file
  remove( "version.h" );

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
    "version.h"
  };
  int  testargc = sizeof( testargv ) / sizeof( testargv[0] );

  /// Create version.h and initial version is 0.1.0
  FileProxy_WriteVersion( "version.h", "0.1.0", 0, 0 );

  /// Increase version to 1.0.0
  Run_SemVer( testargc, testargv );

  /// Get file buffer
  FileProxy_ReadFile( "version.h", actualbuf, FILEPROXY_FILE_BUF_SIZE );

  /// Clear generated file
  remove( "version.h" );

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
    "version.h"
  };
  int  testargc = sizeof( testargv ) / sizeof( testargv[0] );

  /// Create version.h and initial version is 0.1.0
  FileProxy_WriteVersionSimple( "version.h", "0.1.0", 0 );

  /// Increase version to 0.2.0
  Run_SemVer( testargc, testargv );

  /// Get file buffer
  FileProxy_ReadFile( "version.h", actualbuf, FILEPROXY_FILE_BUF_SIZE );

  /// Clear generated file
  remove( "version.h" );

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
    "version.h"
  };
  int  testargc = sizeof( testargv ) / sizeof( testargv[0] );

  /// Create version.h and initial version is 0.1.0
  FileProxy_WriteVersionSimple( "version.h", "0.1.0", 1 );

  /// Increase version to 0.2.0
  Run_SemVer( testargc, testargv );

  /// Clear generated file
  remove( "version.h" );

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
    "version.h"
  };
  int  testargc = sizeof( testargv ) / sizeof( testargv[0] );

  /// Create version.h and initial version is 0.1.0
  FileProxy_WriteVersion( "version.h", "0.1.0", 0, 1 );

  /// Increase version to 1.0.0
  Run_SemVer( testargc, testargv );

  /// Clear generated file
  remove( "version.h" );

  TEST_ASSERT_EQUAL_STRING( expectedOutput, actualOutput );
}
