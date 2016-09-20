#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define byte uint8_t

int8_t run_int8(const byte*);
int16_t run_int16(const byte*);
int32_t run_int32(const byte*);
int64_t run_int64(const byte*);

uint8_t run_uint8(const byte*);
uint16_t run_uint16(const byte*);
uint32_t run_uint32(const byte*);
uint64_t run_uint64(const byte*);

#undef byte

#ifdef __cplusplus
}
#endif



