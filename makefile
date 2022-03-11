#==================================================
# LIBCTINY - Matt Pietrek 1996
# Microsoft Systems Journal, October 1996
# FILE: LIBCTINY.MAK - Makefile for Microsoft version
#==================================================
CC = CL
CC_OPTIONS = /GS- /c /W3 /DWIN32_LEAN_AND_MEAN /FS /GR- /EHsc /D _NO_CRT_STDIO_INLINE /D _CTYPE_DISABLE_MACROS 

S=.
!ifdef DEBUG
CC_OPTIONS = $(CC_OPTIONS) /Zi
O=Debug
!else
CC_OPTIONS = $(CC_OPTIONS) /Zi /O1
O=Release
!endif

PROJ = minicrt15

OBJS =  $O\CRT0TCON.OBJ $O\CRT0TWIN.OBJ $O\DLLCRT0.OBJ $O\ARGCARGV.OBJ $O\PRINTF.OBJ \
        $O\SPRINTF.OBJ $O\PUTS.OBJ $O\ALLOC.OBJ $O\ALLOC2.OBJ $O\ALLOCSUP.OBJ $O\STRUPLWR.OBJ \
        $O\ISCTYPE.OBJ $O\ATOI.OBJ $O\STRICMP.OBJ $O\NEWDEL.OBJ $O\INITTERM.OBJ \
		$O\bsearch.OBJ $O\charmax.OBJ $O\fullpath.OBJ $O\isalpha.OBJ $O\isdigit.OBJ \
		$O\memory.OBJ $O\misc.OBJ $O\pesect.OBJ $O\rand.OBJ $O\resetstk.OBJ \
		$O\security.OBJ $O\string.OBJ $O\strncpy.OBJ $O\strrchr.OBJ $O\strtok.OBJ \
		$O\tolower.OBJ $O\toupper.OBJ \
#add ctype for compilation with VS2017, because the original startup is using a different way now
      $O\ctype.OBJ $O\file.OBJ 
      

all: $O $O\$(PROJ).LIB

$O: ; mkdir $O

$O\$(PROJ).LIB: {$O}$(OBJS)
    LIB /OUT:$O\$(PROJ).LIB $(OBJS)

{$S}.CC{$O}.OBJ::
    $(CC) $(CC_OPTIONS) -Fo$O\ -Fd$O\ $<

{$S}.C{$O}.OBJ::
    $(CC) $(CC_OPTIONS) -Fo$O\ -Fd$O\ $<
    
{$O}$(OBJS):