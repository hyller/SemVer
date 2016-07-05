#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include "unity_fixture.h"
#include "run.h"
#include "FormatOutputSpy.h"
#include "fileproxy.h"

static const char *expectedOutput;
static const char *actualOutput;

TEST_GROUP( TestRun );

TEST_SETUP( TestRun )
{
  Run_SetFormatOutput( FormatOutputSpy );
  actualOutput = FormatOutputSpy_GetOutput( );
  FormatOutputSpy_Clear( );

  /// Reset to 1 so that getopt can work again
  optind = 1; 
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

  Run_SemVer(testargc, testargv);

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

  Run_SemVer(testargc, testargv);

  TEST_ASSERT_EQUAL_STRING( expectedOutput, actualOutput );
}

TEST( TestRun, TestRun3 )
{
  expectedOutput = "Input  version: 0.1.0\n"
                   "Output version: 0.1.0\n";

  char *testargv[] = {
    "semver.exe",
    "-i0.1.0",
    "version.h"
  };
  int  testargc = sizeof( testargv ) / sizeof( testargv[0] );

  Run_SemVer(testargc, testargv);

  /// Clear generated file
  remove( "version.h" ); 

  TEST_ASSERT_EQUAL_STRING( expectedOutput, actualOutput );  
}

TEST( TestRun, TestRun4 )
{
  expectedOutput = "Input  version: 0.1.0\n"
                   "Output version: 0.2.0\n";

  char *testargv[] = {
    "semver.exe",
    "version.h"
  };
  int  testargc = sizeof( testargv ) / sizeof( testargv[0] );

  /// Create version.h and initial version is 0.1.0
  FileProxy_WriteVersion("version.h", "0.1.0", 0, 0); 

  /// Increase version to 0.2.0
  Run_SemVer(testargc, testargv);

  /// Clear generated file
  remove( "version.h" );
  
  TEST_ASSERT_EQUAL_STRING( expectedOutput, actualOutput ); 
}

TEST( TestRun, TestRun5 )
{
  TEST_ASSERT_TRUE( 1 ); 
}
