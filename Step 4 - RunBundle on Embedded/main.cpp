#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MIMXRT1052.h"
#include "fsl_debug_console.h"
#include "timer.h"

// ----------------------------- Bundle API -----------------------------
// Bundle includes
#include "gesture.h"
#include "glow_bundle_utils.h"

// Statically allocate memory for constant weights (model weights) and initialize.
GLOW_ALIGN(GESTURE_MEM_ALIGN)
uint8_t constantWeight[GESTURE_CONSTANT_MEM_SIZE] = {
#include "gesture.inc"
};

// Statically allocate memory for mutable weights (model input/output data).
GLOW_ALIGN(GESTURE_MEM_ALIGN)
uint8_t mutableWeight[GESTURE_MUTABLE_MEM_SIZE];

// Statically allocate memory for activations (model intermediate results).
GLOW_ALIGN(GESTURE_MEM_ALIGN)
uint8_t activations[GESTURE_ACTIVATIONS_MEM_SIZE];

// Bundle input data absolute address.
uint8_t *inputAddr = GLOW_GET_ADDR(mutableWeight, GESTURE_input_1_01);

// Bundle output data absolute address.
uint8_t *outputAddr = GLOW_GET_ADDR(mutableWeight, GESTURE_save_output_1_Softmax_0);

// ---------------------------- Application -----------------------------
// Input data size
#define GESTURE_INPUT_SIZE    64

// Lenet Mnist model number of output classes.
#define GESTURE_OUTPUT_CLASS  7

// Allocate buffer for input data.
float inputData[GESTURE_INPUT_SIZE] = {
// your input test data here
};

/*
 * @brief   Application entry point.
 */
int main(void) {

  // Initialize hardware
  BOARD_InitBootPins();
  BOARD_InitBootClocks();
  BOARD_InitBootPeripherals();
  BOARD_InitDebugConsole();
  init_timer();

  // Timer variables
  uint32_t start_time, stop_time;
  uint32_t duration_ms;

  // Produce input data for bundle.
  start_time = get_time_in_us();
  memcpy(inputAddr, inputData, sizeof(inputData));

  // Perform inference and measure time
  start_time = get_time_in_us();
  gesture(constantWeight, mutableWeight, activations);
  stop_time = get_time_in_us();
  duration_ms = (stop_time - start_time) / 1000;

  // Get classification top1 result and confidence
  float *out_data = (float*)(outputAddr);
  float max_val = 0.0;
  uint32_t max_idx = 0;
  for(int i = 0; i < GESTURE_OUTPUT_CLASS; i++) {
    if (out_data[i] > max_val) {
      max_val = out_data[i];
      max_idx = i;
    }
  }

  // Print classification results
  PRINTF("Top1 class = %lu\r\n", max_idx, max_idx);
  PRINTF("Confidence = %f\r\n", max_val);
  PRINTF("Inference time = %lu (ms)\r\n", duration_ms);

  while(1) {}
  return 0 ;
}
