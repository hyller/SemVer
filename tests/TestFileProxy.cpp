#include "CppUTest/TestHarness.h"
#include "FileProxy.h"

TEST_GROUP( TestFileProxy )
{
  void setup( )
  {
  }

  void teardown( )
  {
  }
};

TEST( TestFileProxy, SimpleVersion )
{
  char verstr[128]  = { 0 };
  char *verstrwrite = ( char* )"7.8.9";

  FileProxy_WriteVersionSimple( ( char* )"Simple.Write", ( char* )verstrwrite );
  FileProxy_ReadVersionSimple( ( char* )"Simple.Write", ( char* )verstr );

  STRCMP_EQUAL( verstrwrite, verstr );
}

TEST( TestFileProxy, FullVersionName )
{
  char verstr[128]  = { 0 };
  char *verstrwrite = ( char* )"4.5.6";

  FileProxy_WriteVersion( ( char* )"Full.Write.Name", ( char* )verstrwrite, ( char* )"TESTVERSION" );
  FileProxy_ReadVersion( ( char* )"Full.Write.Name", ( char* )verstr, ( char* )"TESTVERSION" );

  STRCMP_EQUAL( verstrwrite, verstr );
}
