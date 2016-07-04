//----------------------------------------------------------------------------//
/// \file   run.h
/// \brief  
//----------------------------------------------------------------------------//
#ifndef RUN_H
#define RUN_H

#ifdef __cplusplus
  extern "C" {
#endif

int semverrun( int  argc, char **argv );
void PrintVersion( void );
void PrintUsage( void );

#ifdef __cplusplus
  }
#endif

#endif
