#include "reader.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

#define READER_SLEEP 500000

cpu_usage_t* cpu_usage;
static uint32_t cpu_usage_len = 0;

static FILE* open_stat_file();
static uint32_t cpu_usage_find_idx(const char* name);
static cpu_usage_t cpu_usage_get_from_line(char* line);

int reader_main() {
    extern bool sig_stop;
    FILE* stat_file = open_stat_file();

    if (stat_file == NULL) {
        return 1;
    }

    while (!sig_stop) {
        fseek(stat_file, 0, SEEK_SET);
        char line[1024];

        while (fgets(line, sizeof(line), stat_file) != NULL) {
            if(strncmp(line, "cpu", 3) != 0) {
                break;
            }

            cpu_usage_t cpu = cpu_usage_get_from_line(line);

            if(cpu_usage_len == 0 || cpu_usage == NULL) {
                cpu_usage = (cpu_usage_t*)malloc(sizeof(cpu_usage_t));
                cpu_usage[cpu_usage_len++] = cpu;
            }
            else {
                uint32_t idx = cpu_usage_find_idx(cpu.name);
                if(idx == cpu_usage_len) {
                    cpu_usage = (cpu_usage_t*)realloc(cpu_usage, sizeof(cpu_usage_t) * (cpu_usage_len + 1));
                    cpu_usage[cpu_usage_len++] = cpu;
                }
                else {
                    cpu_usage_t* old_cpu = &cpu_usage[idx];
                    free(old_cpu->name);
                    free(old_cpu->data);
                    cpu_usage[idx] = cpu;
                }
            }
        }

        usleep(READER_SLEEP);
    }

    fclose(stat_file);

    return 0;
}

static FILE* open_stat_file() {
    FILE* file_handle = fopen("/proc/stat", "r");

    if (file_handle == NULL) {
        perror("Cannot open /proc/stat");
        return NULL;
    }

    return file_handle;
}

static uint32_t cpu_usage_find_idx(const char* name) {
    uint32_t i = 0;

    for(; i < cpu_usage_len;) {
        if(strcmp(cpu_usage[i++].name, name) == 0) {
            return i;
        }
    }

    return i;
}

static cpu_usage_t cpu_usage_get_from_line(char* line) {
    cpu_usage_t cpu;
    cpu.name = (char*)malloc(sizeof(char) * 4);
    memcpy(cpu.name, line, 4);

    cpu.data_len = 0;
    uint32_t data_val;
    memcpy(line, line + 5, 1020);
    while(sscanf(line, "%u", &data_val)) {
        if(cpu.data_len == 0 || cpu.data == NULL) {
            cpu.data = (uint32_t*)malloc(sizeof(uint32_t));
        } else {
            cpu.data = (uint32_t*)realloc(cpu.data, sizeof(uint32_t) * (cpu.data_len + 1));
        }
        cpu.data[cpu.data_len++] = data_val;

        char* space = strchr(line, ' ');
        if(space == NULL) {
            break;
        }
        memcpy(line, space + 1, strlen(space));
    }

    return cpu;
}
