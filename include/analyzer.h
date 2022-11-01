#ifndef __ANALYZER_H__
#define __ANALYZER_H__

#include "cpu_usage.h"

float calculate_cpu_usage_percent(const cpu_usage_raw_t* prev, const cpu_usage_raw_t* curr);
int analyzer_main(void);

#endif