// Author: Neeraj Sharma <neerajsharma.9@outlook.com>
// License MIT

#pragma once

#define NO_BOOTSTRAP_ALLOCATOR
#define SNMALLOC_STATIC_LIBRARY_PREFIX sn_
#define MALLOC_USABLE_SIZE_QUALIFIER const

#ifdef SNMALLOC_STATIC_LIBRARY_PREFIX
#  define __SN_CONCAT(a, b) a##b
#  define __SN_EVALUATE(a, b) __SN_CONCAT(a, b)
#  define SNMALLOC_NAME_MANGLE(a) \
    __SN_EVALUATE(SNMALLOC_STATIC_LIBRARY_PREFIX, a)
#elif !defined(SNMALLOC_NAME_MANGLE)
#  define SNMALLOC_NAME_MANGLE(a) a
#endif

extern "C" {
    extern void* SNMALLOC_NAME_MANGLE(malloc)(size_t size);
    extern void SNMALLOC_NAME_MANGLE(free)(void* ptr);
    extern void SNMALLOC_NAME_MANGLE(cfree)(void* ptr);
    extern void* SNMALLOC_NAME_MANGLE(calloc)(size_t nmemb, size_t size);
    extern size_t SNMALLOC_NAME_MANGLE(malloc_usable_size)(MALLOC_USABLE_SIZE_QUALIFIER void* ptr);
    extern void* SNMALLOC_NAME_MANGLE(realloc)(void* ptr, size_t size);
}