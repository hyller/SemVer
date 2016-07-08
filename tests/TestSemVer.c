#include "unity_fixture.h"
#include "semver.h"

TEST_GROUP( TestSemVer );

TEST_SETUP( TestSemVer )
{
}

TEST_TEAR_DOWN( TestSemVer )
{
}

TEST( TestSemVer, ConvertFromStr )
{
  tSemverVersion ver;
  char           str[10] = "1.2.3";
  int ret;

  ver.major = 0;
  ver.minor = 0;
  ver.patch = 0;

  ret = SemVer_ConvertFromStr( &ver, str );

  TEST_ASSERT_EQUAL_INT( 1, ver.major );
  TEST_ASSERT_EQUAL_INT( 2, ver.minor );
  TEST_ASSERT_EQUAL_INT( 3, ver.patch );
  TEST_ASSERT_EQUAL_INT( 0, ret );
}

TEST( TestSemVer, ConvertFromStrInvalid )
{
  tSemverVersion ver;
  char           str[10] = "1.2";
  int ret;

  ver.major = 0;
  ver.minor = 0;
  ver.patch = 0;

  ret = SemVer_ConvertFromStr( &ver, str );

  TEST_ASSERT_EQUAL_INT( 0, ver.major );
  TEST_ASSERT_EQUAL_INT( 1, ver.minor );
  TEST_ASSERT_EQUAL_INT( 0, ver.patch );
  TEST_ASSERT_EQUAL_INT( 1, ret );
}

TEST( TestSemVer, ConvertFromStrInvalid2 )
{
  tSemverVersion ver;
  char           str[10] = ".1.2.3.";
  int ret;

  ver.major = 0;
  ver.minor = 0;
  ver.patch = 0;

  ret = SemVer_ConvertFromStr( &ver, str );

  TEST_ASSERT_EQUAL_INT( 0, ver.major );
  TEST_ASSERT_EQUAL_INT( 1, ver.minor );
  TEST_ASSERT_EQUAL_INT( 0, ver.patch );
  TEST_ASSERT_EQUAL_INT( 1, ret );
}

TEST( TestSemVer, ConvertFromStrInvalid3 )
{
  tSemverVersion ver;
  char           str[10] = "123";
  int ret;

  ver.major = 0;
  ver.minor = 0;
  ver.patch = 0;

  ret = SemVer_ConvertFromStr( &ver, str );

  TEST_ASSERT_EQUAL_INT( 0, ver.major );
  TEST_ASSERT_EQUAL_INT( 1, ver.minor );
  TEST_ASSERT_EQUAL_INT( 0, ver.patch );
  TEST_ASSERT_EQUAL_INT( 1, ret );
}


TEST( TestSemVer, ConvertToStr )
{
  tSemverVersion ver;
  char           str[10] = "0";

  ver.major = 1;
  ver.minor = 2;
  ver.patch = 3;

  SemVer_ConvertToStr( &ver, str, 0 );

  TEST_ASSERT_EQUAL_STRING( "1.2.3", str );
}

TEST( TestSemVer, ConvertToStr2 )
{
  tSemverVersion ver;
  char           str[10] = "0";

  ver.major = 1;
  ver.minor = 2;
  ver.patch = 3;

  SemVer_ConvertToStr( &ver, str, 2 );

  TEST_ASSERT_EQUAL_STRING( "01.02.03", str );
}

TEST( TestSemVer, ConvertToStr3 )
{
  tSemverVersion ver;
  char           str[10] = "0";

  ver.major = 1;
  ver.minor = 2;
  ver.patch = 3;

  SemVer_ConvertToStr( &ver, str, 3 );

  TEST_ASSERT_EQUAL_STRING( "001.002.003", str );
}

TEST( TestSemVer, Increase255 )
{
  tSemverVersion ver;

  ver.major = 0;
  ver.minor = 255;
  ver.patch = 255;

  SemVer_IncreasePatch( &ver );

  TEST_ASSERT_EQUAL_INT( 0, ver.major );
  TEST_ASSERT_EQUAL_INT( 255, ver.minor );
  TEST_ASSERT_EQUAL_INT( 256, ver.patch );
}

TEST( TestSemVer, SemVerInit )
{
  tSemverVersion ver;

  ver.major = 0;
  ver.minor = 0;
  ver.patch = 0;

  SemVer_Init( &ver );

  TEST_ASSERT_EQUAL_INT( 0, ver.major );
  TEST_ASSERT_EQUAL_INT( 1, ver.minor );
  TEST_ASSERT_EQUAL_INT( 0, ver.patch );
}

TEST( TestSemVer, SemVerIncreaseMajor )
{
  tSemverVersion ver;

  ver.major = 0;
  ver.minor = 0;
  ver.patch = 0;

  SemVer_IncreaseMajor( &ver );

  TEST_ASSERT_EQUAL_INT( 1, ver.major );
  TEST_ASSERT_EQUAL_INT( 0, ver.minor );
  TEST_ASSERT_EQUAL_INT( 0, ver.patch );
}

TEST( TestSemVer, SemVerIncreaseMinor )
{
  tSemverVersion ver;

  ver.major = 0;
  ver.minor = 0;
  ver.patch = 0;

  SemVer_IncreaseMinor( &ver );

  TEST_ASSERT_EQUAL_INT( 0, ver.major );
  TEST_ASSERT_EQUAL_INT( 1, ver.minor );
  TEST_ASSERT_EQUAL_INT( 0, ver.patch );
}

TEST( TestSemVer, SemVerIncreasePatch )
{
  tSemverVersion ver;

  ver.major = 0;
  ver.minor = 0;
  ver.patch = 0;

  SemVer_IncreasePatch( &ver );

  TEST_ASSERT_EQUAL_INT( 0, ver.major );
  TEST_ASSERT_EQUAL_INT( 0, ver.minor );
  TEST_ASSERT_EQUAL_INT( 1, ver.patch );
}

