//==========================================
// LIBCTINY - Matt Pietrek 2001
// MSDN Magazine, January 2001
//==========================================
#include "libctiny.h"
#include <ctype.h>

// add this extern type - compile with VS2017
// needs ctype.c 
_CRTIMP extern const unsigned short *_pctype;

extern "C" int __cdecl _isctype( int c , int mask ) {
    /* c valid between -1 and 255 */
    if (((unsigned)(c + 1)) <= 256)
    {
        return ( _pctype[c] & mask );
    }
    else
        return 0;
}
