#include "cpu_usage.h"

#include <stddef.h>
#include <stdlib.h>

bool cpu_usage_raw_equ(const cpu_usage_raw_t* left, const cpu_usage_raw_t* right) {
    if(left == NULL || right == NULL) {
        return false;
    }

    if(left->name == NULL || right->name == NULL) {
        return false;
    }

    if(left->data == NULL || right->data == NULL) {
        return false;
    }

    if(left->data_len != right->data_len) {
        return false;
    }

    for(uint32_t i = 0; i < left->data_len; ++i) {
        if(left->data[i] != right->data[i]) {
            return false;
        }
    }

    return true;
}

cpu_usage_raw_t* copy_cpu_usage_raw_array(const cpu_usage_raw_t* src) {
    if(src == NULL) {
        return NULL;
    }

    cpu_usage_raw_t* dst = malloc(sizeof(cpu_usage_raw_t) * cpu_usage_raw_len);

    for(uint32_t i = 0; i < cpu_usage_raw_len; ++i) {
        dst[i].name = src[i].name;
        dst[i].data = malloc(sizeof(uint32_t) * src[i].data_len);
        dst[i].data_len = src[i].data_len;

        for(uint32_t j = 0; j < src[i].data_len; ++j) {
            dst[i].data[j] = src[i].data[j];
        }
    }

    return dst;
}
