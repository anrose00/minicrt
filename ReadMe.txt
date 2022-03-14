//==========================================
// LIBCTINY - Matt Pietrek 2001
// MSDN Magazine, January 2001
//==========================================

libctiny plus some additions

obj files from:

C:\Program Files\Microsoft Visual Studio .NET 2003\Vc7\crt\src\intel\dll_lib

-----

Additional by leepa

I took this from Google's Omaha project and then made it work for my own
purposes. Figured others might find this useful so wanted to share it. 

This version is built as a Visual Studio 2008 project for your usage anywhere 
you like. There was a couple of problems with making this work but it does work 
now. 

The main issue is around intrinsic functions and castings. I have fixed up the
relevant parts and forced VC++ to use the functions provided here instead
of intrinsic ones. This loses some optimisation, yes. But overall it keeps
within the spirit of the library.

Enjoy.

-----

Additional by Chris Benshoof

I took this from leepa and made a Visual Studio 2005 project in addition to the
Visual Studio 2008 one. I then added a number of crt functions on an as-needed basis, 
each in a new source file. No changes were made to the existing source files. 
Oh, and I brought back printf() from the original libctiny.

To reduce confusion I removed unused files from the project, including string.cc.
string.cc is virtually identical to string.c, and Google's Omaha build script
doesn't even use string.cc. It should probably be removed from their subversion
repo. string.c is where leepa added a few lines to address the intrinsic issue.

I also changed the project settings for Release mode to Minimize Size (/O1)
and to disable Debug Information Format to drop the Release minicrt.lib to
~100k.

------
Additions by A.Rosenberg (2019-2022)

Made some changes to make it compile with VS2017/VS2019. 
MS did major changes to make _isctype locale aware, which causes linker issues
with the previous minicrt implementation. For many small project these locale
specific changes are not relevant, so I added a previous implementation of 
ctype to the project.
See comments in the  various files. Added basic file IO functions.

Details regarding MS VC changes:

https://docs.microsoft.com/en-us/cpp/porting/visual-cpp-change-history-2003-2015

------

Building minicrt:
- install VS MSC (console tools are sufficient)
- open developer console for x86 and switch to source dir
- do "nmake"
- if you need a version with debug symbols do "nmake -D Debug=1"

To use minicrt in your project, just link to minicrt.lib and use /NODEFAULTLIB 
to reject all default libraries. If your project can't compile because it
uses functions that aren't in minicrt, you need to add those functions to minicrt,
find and use an alternative function, or not use minicrt. If you don't know
what you're doing, then that last option is the way to go. If you do know
what you're doing, then that last option is the way to go most of the time.