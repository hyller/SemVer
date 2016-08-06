#ifndef _SEMVER_H_
#define _SEMVER_H_

#ifdef __cplusplus
  extern "C"
  {
#endif

#define SEMVER_STR_LEN ( 255u )

typedef struct
{
  int  major;
  int  minor;
  int  patch;
  char str[SEMVER_STR_LEN];
  int  fieldlen;
}tSemver;

int SemVer_Init( tSemver *me );

int SemVer_InitByStr( tSemver *me,
                      char    *str );

int SemVer_InitByStrFieldlen( tSemver *me,
                              char    *str,
                              int     len );

int SemVer_BumpMajor( tSemver *me );

int SemVer_BumpMinor( tSemver *me );

int SemVer_BumpPatch( tSemver *me );

#ifdef __cplusplus
  }
#endif
#endif
