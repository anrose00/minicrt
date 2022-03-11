//==========================================
// minicrt - Chris Benshoof 2009
// sprintf()
//==========================================
#include "libctiny.h"
#include <windows.h>
#include <stdarg.h>

// Force the linker to include USER32.LIB
#pragma comment(linker, "/defaultlib:user32.lib")

extern "C" int __cdecl sprintf (char *string, const char *format, ...)
{
    int retValue;
    va_list argptr;

    va_start( argptr, format );
    retValue = wvsprintf( string, format, argptr );
    va_end( argptr );

    return retValue;
}

// Note - the wvsprintf located in user does not support floats 
// added to compile with VS2017
extern "C" int __cdecl __stdio_common_vsprintf (
   unsigned __int64 _Options,
   char*            _Buffer,
   size_t           _BufferCount,
   char const*      _Format,
   void*            _Locale,
   va_list          _ArgList)
{
    int retValue;

    retValue = wvsprintf( _Buffer, _Format, _ArgList );

    return retValue;
}