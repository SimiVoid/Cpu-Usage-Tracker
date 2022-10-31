#ifndef __CPU_USAGE_H__
#define __CPU_USAGE_H__

#include <stdint.h>

typedef struct {
    char* name;
    uint32_t* data;
    uint32_t data_len;
} cpu_usage_raw_t;

extern cpu_usage_raw_t* cpu_usage;
extern uint32_t cpu_usage_len;

#endif