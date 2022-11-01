#include "watchdog.h"

#include <unistd.h>
#include <stdbool.h>

#define WATCHDOG_SLEEP 100000

clock_t last_reader_time;
clock_t last_analyzer_time;
clock_t last_printer_time;

pthread_mutex_t last_reader_time_mutex;
pthread_mutex_t last_analyzer_time_mutex;
pthread_mutex_t last_printer_time_mutex;

int watchdog_main(void) {
    extern bool sig_stop;

    if(pthread_mutex_init(&last_reader_time_mutex, NULL) != 0) {
        return 1;
    }

    if(pthread_mutex_init(&last_analyzer_time_mutex, NULL) != 0) {
        return 1;
    }

    if(pthread_mutex_init(&last_printer_time_mutex, NULL) != 0) {
        return 1;
    }

    while(!sig_stop) {
        clock_t now = clock();

        if(pthread_mutex_trylock(&last_reader_time_mutex) == 0) {
            if((float)(now - last_reader_time) / CLOCKS_PER_SEC > 2.f) {
                return 1;
            }

            pthread_mutex_unlock(&last_reader_time_mutex);
        }

        if(pthread_mutex_trylock(&last_analyzer_time_mutex) == 0) {
            if((float)(now - last_analyzer_time) / CLOCKS_PER_SEC > 2.f) {
                return 2;
            }

            pthread_mutex_unlock(&last_analyzer_time_mutex);
        }

        if(pthread_mutex_trylock(&last_printer_time_mutex) == 0) {
            if((float)(now - last_printer_time) / CLOCKS_PER_SEC > 2.f) {
                return 3;
            }

            pthread_mutex_unlock(&last_printer_time_mutex);
        }

        usleep(WATCHDOG_SLEEP);
    }

    pthread_mutex_destroy(&last_reader_time_mutex);
    pthread_mutex_destroy(&last_analyzer_time_mutex);
    pthread_mutex_destroy(&last_printer_time_mutex);

    return 0;
}