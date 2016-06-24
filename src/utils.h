#ifndef _UTILS_H_
#define _UTILS_H_

#ifdef __cplusplus
  extern "C"
  {
#endif

int Utils_StrChr( const char *s,
                    int        i,
                    int        j,
                    int        c );

 int Utils_StrRchr( const char *s,
                     int        i,
                     int        j,
                     int        c );

 int Utils_StrFind( const char *s,
                     int        i,
                     int        j,
                     const char *str );

void Utils_StrAppend( char *oldname,
                    char *append,
                    char *newname );

#ifdef __cplusplus
  }
#endif
#endif
