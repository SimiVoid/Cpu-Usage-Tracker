#include "analyzer.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <unistd.h>

#define ANALYZER_SLEEP 100000

cpu_usage_t* cpu_usage;
uint32_t cpu_usage_len;

static cpu_usage_raw_t* prev_cpu_usage_raw;

bool raw_data_is_changed(void);
float calculate_cpu_usage_percent(const cpu_usage_raw_t* prev, const cpu_usage_raw_t* curr);

int analyzer_main(void) {
    extern bool sig_stop;

    while(!sig_stop) {
        if(raw_data_is_changed()) {
            if(cpu_usage == NULL) {
                cpu_usage = (cpu_usage_t*)malloc(sizeof(cpu_usage_t) * cpu_usage_raw_len);
            }

            for(uint32_t i = 0; i < cpu_usage_raw_len; ++i) {
                cpu_usage[i].name = cpu_usage_raw[i].name;
                cpu_usage[i].usage = calculate_cpu_usage_percent(&prev_cpu_usage_raw[i], &cpu_usage_raw[i]);
            }

            prev_cpu_usage_raw = cpu_usage_raw;
        }

        usleep(ANALYZER_SLEEP);
    }

    free(cpu_usage);

    return 0;
}

float calculate_cpu_usage_percent(const cpu_usage_raw_t* prev, const cpu_usage_raw_t* curr) {
    if(prev == NULL || curr == NULL) {
        return 0.0f;
    }

    uint32_t prev_idle = prev->data[3] + prev->data[4];
    uint32_t curr_idle = curr->data[3] + curr->data[4];

    uint32_t prev_non_idle = prev->data[0] + prev->data[1] + prev->data[2] + prev->data[5] + prev->data[6] + prev->data[7];
    uint32_t curr_non_idle = curr->data[0] + curr->data[1] + curr->data[2] + curr->data[5] + curr->data[6] + curr->data[7];

    uint32_t prev_total = prev_idle + prev_non_idle;
    uint32_t curr_total = curr_idle + curr_non_idle;

    uint32_t total_delta = curr_total - prev_total;
    uint32_t idle_delta = curr_idle - prev_idle;

    return (float)(total_delta - idle_delta) / (float)total_delta * 100.f;
}

bool raw_data_is_changed(void) {
    if(pthread_mutex_trylock(&cpu_usage_raw_mutex) != 0) {
        return false;
    }

    if(prev_cpu_usage_raw == NULL && cpu_usage_raw != NULL) {
        prev_cpu_usage_raw = cpu_usage_raw;
        return true;
    }

    bool changed = false;

    for(uint32_t i = 0; i < cpu_usage_raw_len; ++i) {
        if(!cpu_usage_raw_equ(&prev_cpu_usage_raw[i], &cpu_usage_raw[i])) {
            changed = true;
            break;
        }
    }

    pthread_mutex_unlock(&cpu_usage_raw_mutex);

    return changed;
}
