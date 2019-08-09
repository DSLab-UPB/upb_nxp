// Bundle API header file
// Auto-generated file. Do not edit!

#ifndef _GLOW_BUNDLE_GESTURE_H
#define _GLOW_BUNDLE_GESTURE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// ---------------------------------------------------------------
// Model name: "gesture"
// Total data size: 149312 (bytes)
// Placeholders:
//  Name: "input_1_01"
//  Type: float
//  Size: 64 (elements)
//  Size: 256 (bytes)
//  Offset: 0 (bytes)
//
//  Name: "save_output_1_Softmax_0"
//  Type: float
//  Size: 7 (elements)
//  Size: 28 (bytes)
//  Offset: 256 (bytes)
//
// Note: Placeholders are allocated within the "mutableWeight"
// buffer and the location is identified with the offset which
// is relative to the base of the buffer.
// ---------------------------------------------------------------

// Address offset definitions for placeholders
#define GESTURE_input_1_01  0
#define GESTURE_save_output_1_Softmax_0  256

// Memory sizes (bytes)
#define GESTURE_CONSTANT_MEM_SIZE     146816
#define GESTURE_MUTABLE_MEM_SIZE      320
#define GESTURE_ACTIVATIONS_MEM_SIZE  2176

// Memory alignment (bytes)
#define GESTURE_MEM_ALIGN  64

// Bundle entry point (inference function)
void gesture(uint8_t *constantWeight, uint8_t *mutableWeight, uint8_t *activations);

#ifdef __cplusplus
}
#endif
#endif // _GLOW_BUNDLE_GESTURE_H
