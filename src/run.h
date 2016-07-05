//----------------------------------------------------------------------------//
/// \file   run.h
/// \brief  
//----------------------------------------------------------------------------//
#ifndef RUN_H
#define RUN_H

#ifdef __cplusplus
  extern "C" {
#endif

int Run_SemVer( int  argc, char **argv );
void Run_SetFormatOutput(int ( *p )( const char *format, ... ));

#ifdef __cplusplus
  }
#endif

#endif
