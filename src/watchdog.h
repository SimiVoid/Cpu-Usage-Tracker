#ifndef __WATCHDOG_H__
#define __WATCHDOG_H__

#include <pthread.h>
#include <time.h>

int watchdog_main(void);

extern clock_t last_reader_time;
extern clock_t last_analyzer_time;
extern clock_t last_printer_time;

extern pthread_mutex_t last_reader_time_mutex;
extern pthread_mutex_t last_analyzer_time_mutex;
extern pthread_mutex_t last_printer_time_mutex;

#endif