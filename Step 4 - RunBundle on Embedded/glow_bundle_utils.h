#ifndef _GLOW_BUNDLE_UTILS_H
#define _GLOW_BUNDLE_UTILS_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Memory alignment definition with given alignment size
// for static allocation of memory.
#define GLOW_ALIGN(size) __attribute__((aligned(size)))

// Macro function to get the absolute address of a
// placeholder using the base address of the mutable
// weight buffer and placeholder offset definition.
#define GLOW_GET_ADDR(mutableWeightAddr, placeholderDef) (((uint8_t*)(mutableWeightAddr)) + placeholderDef)

// Alignment size definition.
// Valid alignment sizes are 1 ... 255.
typedef uint8_t align_t;

// Allocate memory dynamically with given alignment and size.
void* alignedAlloc(align_t alignment, size_t size);

// Free memory previously allocated with "alignedAlloc".
void alignedFree(void *ptr);

#ifdef __cplusplus
}
#endif

#endif // _GLOW_BUNDLE_UTILS_H
