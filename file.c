/*
 * FILE.C
 *
 * Implementations for f* file library functions.
 *
 * Copyright (c) 2014 Malcolm J. Smith
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */


#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#ifndef FILE_SHARE_DELETE
#define FILE_SHARE_DELETE 4
#endif

typedef struct _file {
    HANDLE hFile;
} FILE;

FILE * fopen(char * filename, char * mode)
{
    FILE * RetVal;
    DWORD DesiredAccess;
    DWORD CreateDisposition;

    if (strcmp(mode,"r")==0 ||
        strcmp(mode,"rb")==0) {

        DesiredAccess = GENERIC_READ;
        CreateDisposition = OPEN_EXISTING;

    } else if (strcmp(mode,"w")==0 ||
               strcmp(mode,"wb")==0) {

        DesiredAccess = GENERIC_WRITE;
        CreateDisposition = CREATE_ALWAYS;

    } else {
        return NULL;
    }

    RetVal = malloc(sizeof(FILE));
    if (RetVal == NULL) {
        return NULL;
    }

    RetVal->hFile = CreateFile(filename,
                               DesiredAccess,
                               FILE_SHARE_READ|FILE_SHARE_DELETE,
                               NULL,
                               CreateDisposition,
                               FILE_ATTRIBUTE_NORMAL,
                               NULL);

    if (RetVal->hFile != INVALID_HANDLE_VALUE) {
        return RetVal;
    } else {
        free(RetVal);
    }

    return NULL;
}

char *fgets(char * str,int n,FILE * fp)
{
    int count = 0;
    char ch;
    DWORD bytesread;

    while ((count + 1) < n && ReadFile(fp->hFile,&ch,sizeof(ch),&bytesread,NULL) && bytesread == sizeof(ch)) {
        str[count] = ch;
        count++;
        if (ch == '\n' || ch == '\r') {
            break;
        }
    }
    str[count] = '\0';
    if (count == 0) {
        return NULL;
    }
    return str;
}

int fputs ( const char * str, FILE * fp )
{
   size_t stlen=strlen(str);
   DWORD byteswritten;
   BOOL result;
   
   result = WriteFile(fp->hFile,str, (DWORD)stlen, &byteswritten,NULL);
   if (result && stlen == byteswritten)
      return 0;
   else
      return -1;
}

int fputc ( int character, FILE * fp )
{
   BOOL result;
   DWORD byteswritten;
   
   result = WriteFile(fp->hFile,&character, 1, &byteswritten,NULL);
   if (result && byteswritten == 1)
      return 0;
   else
      return -1;
}

size_t fwrite ( const void * ptr, size_t size, size_t count, FILE * fp )
{
   size_t blen=size*count;
   DWORD byteswritten;
   BOOL result;
   
   result = WriteFile(fp->hFile,ptr, (DWORD)blen, &byteswritten,NULL);
   if (result && blen == byteswritten)
      return 0;
   else
      return -1;
}

size_t __cdecl __stdio_common_vfprintf (FILE * fp, char *fstring, const char *format, ...)
{
   int retValuep;
   size_t retValuef;
   va_list argptr;
   char *buffer;

   buffer = malloc(1024);
   if (!buffer) return ENOMEM;
   va_start( argptr, format );
   retValuep = wvsprintf( buffer, fstring, argptr );
   va_end( argptr );
   free(buffer);
   retValuef = fwrite (buffer,1, retValuep, fp );
   
   return retValuef;
}


int fclose(FILE * fp)
{
    if (fp==NULL) {
        return 0;
    }

    if (fp->hFile != NULL && fp->hFile != INVALID_HANDLE_VALUE) {
        CloseHandle(fp->hFile);
    }

    free(fp);
    return 0;
}
