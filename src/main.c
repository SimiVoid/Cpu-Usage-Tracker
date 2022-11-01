#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>

#include "reader.h"
#include "analyzer.h"
#include "printer.h"

#define THREAD_COUNT 3

bool sig_stop = false;

void sig_handler(int sig);

int start_thread(pthread_t* thread, void* (*func)(void*), int* ret);
int wait_for_thread_stop(pthread_t* thread);

int main(void) {
    if(signal(SIGTERM, sig_handler) == SIG_ERR) {
        return 1;
    }

    pthread_t* threads = (pthread_t*)malloc(sizeof(pthread_t) * THREAD_COUNT);

    int ret = 0;

    // Start reader thread
    if(start_thread(&threads[0], (void* (*)(void*))reader_main, &ret) != 0) {
        return 1;
    }

    // Start analyzer thread
    if(start_thread(&threads[1], (void* (*)(void*))analyzer_main, &ret) != 0) {
        return 1;
    }

    // Start printer thread
    if(start_thread(&threads[2], (void* (*)(void*))printer_main, &ret) != 0) {
        return 1;
    }

    while(!sig_stop) {
        if(ret != 0) {
            sig_stop = true;
            break;
        }

        usleep(100);
    }

    for(int i = 0; i < THREAD_COUNT; ++i) {
        wait_for_thread_stop(&threads[i]);
    }

    free(threads);

    return ret;
}

void sig_handler(int sig) {
    if(sig == SIGTERM) {
        sig_stop = true;
    }
}

int start_thread(pthread_t* thread, void* (*func)(void*), int* ret) {
    if(pthread_create(thread, NULL, func, ret) != 0) {
        sig_stop = true;
        return 1;
    }

    return 0;
}

int wait_for_thread_stop(pthread_t* thread) {
    if(thread == NULL) {
        return 0;
    }

    if(pthread_join(*thread, NULL) != 0) {
        return 1;
    }

    return 0;
}
