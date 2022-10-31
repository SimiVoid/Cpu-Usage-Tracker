#ifndef __CPU_USAGE_H__
#define __CPU_USAGE_H__

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    char* name;
    uint32_t* data;
    uint32_t data_len;
} cpu_usage_raw_t;

extern cpu_usage_raw_t* cpu_usage_raw;
extern uint32_t cpu_usage_raw_len;

typedef struct {
    char* name;
    float usage;
} cpu_usage_t;

extern cpu_usage_t* cpu_usage;
extern uint32_t cpu_usage_len;

bool cpu_usage_raw_equ(const cpu_usage_raw_t* left, const cpu_usage_raw_t* right);

#endif