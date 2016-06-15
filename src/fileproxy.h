#ifndef _FILEPROXY_H_
#define _FILEPROXY_H_

#ifdef __cplusplus
  extern "C"
  {
#endif

int FileProxy_IsFileExist( char *filename );

int FileProxy_ReadVersion( char *filename,
                               char *verstr,
                               char *vername );

int FileProxy_WriteVersion( char *filename,
                                char *verstr,
                                char *vername );

int FileProxy_ReadVersionSimple( char *filename,
                                 char *verstr );

int FileProxy_WriteVersionSimple( char *filename,
                                  char *verstr );

int FileProxy_CopyFile( char *filename,
                        char *newname );

#ifdef __cplusplus
  }
#endif
#endif
