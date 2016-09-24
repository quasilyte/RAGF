#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define byte uint8_t

int8_t run_int8(void* data, const byte* code);
int16_t run_int16(void* data, const byte* code);
int32_t run_int32(void* data, const byte* code);
int64_t run_int64(void* data, const byte* code);

uint8_t run_uint8(void* data, const byte* code);
uint16_t run_uint16(void* data, const byte* code);
uint32_t run_uint32(void* data, const byte* code);
uint64_t run_uint64(void* data, const byte* code);

#undef byte

#ifdef __cplusplus
}
#endif



