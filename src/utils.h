#ifndef _UTILS_H_
#define _UTILS_H_

#ifdef __cplusplus
  extern "C"
  {
#endif

extern int Str_chr( const char *s,
                    int        i,
                    int        j,
                    int        c );

extern int Str_rchr( const char *s,
                     int        i,
                     int        j,
                     int        c );

extern int Str_find( const char *s,
                     int        i,
                     int        j,
                     const char *str );

void ChangFileName( char *oldname,
                    char *append,
                    char *newname );

#ifdef __cplusplus
  }
#endif
#endif
