#include <string.h>
#include "unity_fixture.h"
#include "run.h"
#include "FormatOutputSpy.h"

extern int ( *FormatOutput )( const char *format, ... );
static const char *expectedOutput;
static const char *actualOutput;

TEST_GROUP( TestRun );

TEST_SETUP( TestRun )
{
  Run_SetFormatOutput( FormatOutputSpy );
  actualOutput = FormatOutputSpy_GetOutput( );
  FormatOutputSpy_Clear( );
}

TEST_TEAR_DOWN( TestRun )
{
}

TEST( TestRun, TestRun1 )
{
  expectedOutput = "\n"
                   "semver increases version number in a file 0.11.1\n"
                   "\n";

  Run_PrintVersion( );

  TEST_ASSERT_EQUAL_STRING( expectedOutput, actualOutput );
}

TEST( TestRun, TestRun2 )
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

  Run_PrintUsage( );

  TEST_ASSERT_EQUAL_STRING( expectedOutput, actualOutput );
}

TEST( TestRun, TestRun3 )
{
  TEST_ASSERT_TRUE( 1 );
}

TEST( TestRun, TestRun4 )
{
  TEST_ASSERT_TRUE( 1 );
}

TEST( TestRun, TestRun5 )
{
  TEST_ASSERT_TRUE( 1 );
}
