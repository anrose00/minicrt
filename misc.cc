#include "libctiny.h"
#include <windows.h>

//  extern "C" int __cdecl abs (
//          int number
//          )
//  {
//          return( number>=0 ? number : -number );
//  }
//  extern "C" __int64 __cdecl _abs64(
//          __int64 num
//          )
//  {
//          return (num >=0 ? num : -num);
//  }


#ifdef __cplusplus
extern "C" {
#endif
int _fltused=0; // it should be a single underscore since the double one is the mangled name
#ifdef __cplusplus
}
#endif

