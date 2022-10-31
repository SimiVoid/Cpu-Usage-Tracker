#include "cpu_usage.h"

#include <stddef.h>

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