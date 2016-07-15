#include "unity_fixture.h"
#include "semver.h"

TEST_GROUP( TestSemVer );

TEST_SETUP( TestSemVer )
{
}

TEST_TEAR_DOWN( TestSemVer )
{
}

TEST( TestSemVer, InitByStrInvalid )
{
  tSemver ver;
  char    str[10] = "1.2";
  int     ret;

  ver.major = 0;
  ver.minor = 0;
  ver.patch = 0;

  ret = SemVer_InitByStr( &ver, str );

  TEST_ASSERT_EQUAL_INT( 0, ver.major );
  TEST_ASSERT_EQUAL_INT( 1, ver.minor );
  TEST_ASSERT_EQUAL_INT( 0, ver.patch );
  TEST_ASSERT_EQUAL_INT( 1, ret );
}

TEST( TestSemVer, InitByStrInvalid2 )
{
  tSemver ver;
  char    str[10] = ".1.2.3.";
  int     ret;

  ver.major = 0;
  ver.minor = 0;
  ver.patch = 0;

  ret = SemVer_InitByStr( &ver, str );

  TEST_ASSERT_EQUAL_INT( 0, ver.major );
  TEST_ASSERT_EQUAL_INT( 1, ver.minor );
  TEST_ASSERT_EQUAL_INT( 0, ver.patch );
  TEST_ASSERT_EQUAL_INT( 1, ret );
}

TEST( TestSemVer, InitByStrInvalid3 )
{
  tSemver ver;
  char    str[10] = "123";
  int     ret;

  ver.major = 0;
  ver.minor = 0;
  ver.patch = 0;

  ret = SemVer_InitByStr( &ver, str );

  TEST_ASSERT_EQUAL_INT( 0, ver.major );
  TEST_ASSERT_EQUAL_INT( 1, ver.minor );
  TEST_ASSERT_EQUAL_INT( 0, ver.patch );
  TEST_ASSERT_EQUAL_INT( 1, ret );
}

TEST( TestSemVer, InitByStr )
{
  tSemver ver;

  ver.major = 1;
  ver.minor = 2;
  ver.patch = 3;

  SemVer_InitByStrFieldlen( &ver, "1.2.3", 0 );

  TEST_ASSERT_EQUAL_STRING( "1.2.3", ver.str );
}

TEST( TestSemVer, InitByStr2 )
{
  tSemver ver;

  ver.major = 1;
  ver.minor = 2;
  ver.patch = 3;

  SemVer_InitByStrFieldlen( &ver, "1.2.3", 2 );

  TEST_ASSERT_EQUAL_STRING( "01.02.03", ver.str );
}

TEST( TestSemVer, InitByStr3 )
{
  tSemver ver;

  ver.major = 1;
  ver.minor = 2;
  ver.patch = 3;

  SemVer_InitByStrFieldlen( &ver, "1.2.3", 3 );

  TEST_ASSERT_EQUAL_STRING( "001.002.003", ver.str );
}

TEST( TestSemVer, SemVerInit )
{
  tSemver ver;

  ver.major = 0;
  ver.minor = 0;
  ver.patch = 0;

  SemVer_Init( &ver );

  TEST_ASSERT_EQUAL_INT( 0, ver.major );
  TEST_ASSERT_EQUAL_INT( 1, ver.minor );
  TEST_ASSERT_EQUAL_INT( 0, ver.patch );
}

TEST( TestSemVer, SemVerBumpMajor )
{
  tSemver ver;

  ver.major = 0;
  ver.minor = 0;
  ver.patch = 0;

  SemVer_BumpMajor( &ver );

  TEST_ASSERT_EQUAL_INT( 1, ver.major );
  TEST_ASSERT_EQUAL_INT( 0, ver.minor );
  TEST_ASSERT_EQUAL_INT( 0, ver.patch );
}

TEST( TestSemVer, SemVerBumpMinor )
{
  tSemver ver;

  ver.major = 0;
  ver.minor = 0;
  ver.patch = 0;

  SemVer_BumpMinor( &ver );

  TEST_ASSERT_EQUAL_INT( 0, ver.major );
  TEST_ASSERT_EQUAL_INT( 1, ver.minor );
  TEST_ASSERT_EQUAL_INT( 0, ver.patch );
}

TEST( TestSemVer, SemVerBumpPatch )
{
  tSemver ver;

  ver.major = 0;
  ver.minor = 0;
  ver.patch = 0;

  SemVer_BumpPatch( &ver );

  TEST_ASSERT_EQUAL_INT( 0, ver.major );
  TEST_ASSERT_EQUAL_INT( 0, ver.minor );
  TEST_ASSERT_EQUAL_INT( 1, ver.patch );
}

TEST( TestSemVer, SemVerBumpPatch255 )
{
  tSemver ver;

  ver.major = 0;
  ver.minor = 255;
  ver.patch = 255;

  SemVer_BumpPatch( &ver );

  TEST_ASSERT_EQUAL_INT( 0, ver.major );
  TEST_ASSERT_EQUAL_INT( 255, ver.minor );
  TEST_ASSERT_EQUAL_INT( 256, ver.patch );
}