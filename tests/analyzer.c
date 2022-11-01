#include <stdlib.h>
#include <assert.h>

#include "analyzer.h"

bool sig_stop = false;

int main() {
    assert(calculate_cpu_usage_percent(NULL, NULL) == 0);

    cpu_usage_raw_t prev_cpu_usage_raw, curr_cpu_usage_raw;
    assert(calculate_cpu_usage_percent(&prev_cpu_usage_raw, &curr_cpu_usage_raw) == 0);

    return 0;
}