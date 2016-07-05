#include "unity_fixture.h"
#include "fileproxy.h"

TEST_GROUP( TestFileProxy );

TEST_SETUP( TestFileProxy )
{
}

TEST_TEAR_DOWN( TestFileProxy )
{   
}

TEST( TestFileProxy, SimpleVersion )
{
  char verstr[128]  = { 0 };
  char *verstrwrite = ( char* )"7.8.9";

  FileProxy_WriteVersionSimple( "Simple.Write", verstrwrite, 0 );
  FileProxy_ReadVersionSimple( "Simple.Write", verstr );

  TEST_ASSERT_EQUAL_STRING( verstrwrite, verstr );

  remove( "Simple.Write" ); ///< Clear generated file
}

TEST( TestFileProxy, FullVersionName )
{
  char verstr[128]  = { 0 };
  char *verstrwrite = ( char* )"4.5.6";

  FileProxy_WriteVersion( "Full.Write.Name", verstrwrite, "TESTVERSION", 0 );
  FileProxy_ReadVersion( "Full.Write.Name", verstr, "TESTVERSION" );

  TEST_ASSERT_EQUAL_STRING( verstrwrite, verstr );

  remove( "Full.Write.Name" ); ///< Clear generated file
}
