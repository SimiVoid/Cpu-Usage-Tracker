#ifndef __CPU_USAGE_H__
#define __CPU_USAGE_H__

#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>

#include "watchdog.h"

typedef struct {
    char* name;
    uint32_t* data;
    uint32_t data_len;
} cpu_usage_raw_t;

extern cpu_usage_raw_t* cpu_usage_raw;
extern pthread_mutex_t cpu_usage_raw_mutex;
extern uint32_t cpu_usage_raw_len;

typedef struct {
    char* name;
    float usage;
} cpu_usage_t;

extern cpu_usage_t* cpu_usage;
extern pthread_mutex_t cpu_usage_mutex;
extern uint32_t cpu_usage_len;

bool cpu_usage_raw_equ(const cpu_usage_raw_t* left, const cpu_usage_raw_t* right);
cpu_usage_raw_t* copy_cpu_usage_raw_array(const cpu_usage_raw_t* src);

#endif