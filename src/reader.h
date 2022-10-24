#ifndef __READER_H__
#define __READER_H__

#include <stdint.h>

typedef struct {
    char* name;
    uint32_t* data;
    uint32_t data_len;
} cpu_usage_t;

int reader_main();

extern cpu_usage_t* cpu_usage;

#endif