#include "printer.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PRINTER_SLEEP 1000000

void print_cpu_usage_line(const uint32_t line);

int printer_main(void) {
    extern bool sig_stop;

    while(!sig_stop) {
        system("clear");

        printf("\033[0;32mCPU\tUSAGE\033[0;37m\n");

        if(pthread_mutex_trylock(&cpu_usage_mutex) == 0) {
            for(uint32_t i = 0; i < cpu_usage_len; ++i) {
                print_cpu_usage_line(i);
            }

            pthread_mutex_unlock(&cpu_usage_mutex);
        }

        usleep(PRINTER_SLEEP);
    }

    return 0;
}

void print_cpu_usage_line(const uint32_t line) {
    if(line >= cpu_usage_len) {
        return;
    }

    if(cpu_usage[line].name[3] == ' ') {
        printf("%s:\t%3.2f%%\n", "total", cpu_usage[line].usage);
    }
    else {
        printf("%s:\t%3.2f%%\n", cpu_usage[line].name, cpu_usage[line].usage);
    }
}