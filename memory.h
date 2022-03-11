#ifndef TR_COMMON_MINICRT_MEMORY_H_
#define TR_COMMON_MINICRT_MEMORY_H_

// added definition for NULL - compile with VS2017
#ifndef NULL
    #ifdef __cplusplus
        #define NULL 0
    #else
        #define NULL ((void *)0)
    #endif
#endif

int __cdecl memcmp(const void * buf1, const void * buf2, size_t count);
void * __cdecl memcpy(void * dst, const void * src, size_t count);
void * __cdecl memset(void *dst, int val, size_t count);

#endif  // TR_COMMON_MINICRT_MEMORY_H_
