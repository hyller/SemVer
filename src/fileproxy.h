#ifndef _FILEPROXY_H_
#define _FILEPROXY_H_

#ifdef __cplusplus
  extern "C"
  {
#endif

#define FILEPROXY_FILE_BUF_SIZE ( 1024U )

int FileProxy_ReadFile( char *filename,
                        char *buf,
                        int size );

int FileProxy_WriteFile( char *filename,
                         char *buf,
                         int size );

int FileProxy_AccessFile( char *filename );

int FileProxy_ReadVersion( char *filename,
                           char *verstr,
                           char *vername );

int FileProxy_WriteVersion( char *filename,
                            char *verstr,
                            char *vername,
                            int needdate );

int FileProxy_ReadVersionSimple( char *filename,
                                 char *verstr );

int FileProxy_WriteVersionSimple( char *filename,
                                  char *verstr,
                                  int needdate );

int FileProxy_CopyFile( char *filename,
                        char *newname );
                        
int FileProxy_RemoveFile( char *filename );

#ifdef __cplusplus
  }
#endif
#endif
