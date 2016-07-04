//----------------------------------------------------------------------------//
/// \file   FormatOutputSpy.h
/// \brief  
//----------------------------------------------------------------------------//
#ifndef FORMAT_OUTPUT_SPY_H
#define FORMAT_OUTPUT_SPY_H

#ifdef __cplusplus
  extern "C" {
#endif


int FormatOutputSpy( const char* format,
                     ... );
const char* FormatOutputSpy_GetOutput( void );
void FormatOutputSpy_Clear( void );

#ifdef __cplusplus
  }
#endif

#endif
