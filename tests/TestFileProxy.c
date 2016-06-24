#include "unity.h"
#include "unity_fixture.h"
#include "fileproxy.h"

TEST_GROUP( TestFileProxy );

TEST_SETUP(TestFileProxy)
{

}

TEST_TEAR_DOWN(TestFileProxy)
{
  remove(( char* )"Full.Write.Name");
  remove(( char* )"Simple.Write");  
}

TEST( TestFileProxy, SimpleVersion )
{
  char verstr[128]  = { 0 };
  char *verstrwrite = ( char* )"7.8.9";

  FileProxy_WriteVersionSimple( ( char* )"Simple.Write", ( char* )verstrwrite );
  FileProxy_ReadVersionSimple( ( char* )"Simple.Write", ( char* )verstr );

  TEST_ASSERT_EQUAL_STRING( verstrwrite, verstr );
}

TEST( TestFileProxy, FullVersionName )
{
  char verstr[128]  = { 0 };
  char *verstrwrite = ( char* )"4.5.6";

  FileProxy_WriteVersion( ( char* )"Full.Write.Name", ( char* )verstrwrite, ( char* )"TESTVERSION" );
  FileProxy_ReadVersion( ( char* )"Full.Write.Name", ( char* )verstr, ( char* )"TESTVERSION" );

  TEST_ASSERT_EQUAL_STRING( verstrwrite, verstr );
}
