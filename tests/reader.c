#include <stdlib.h>
#include <assert.h>

#include "reader.h"

bool sig_stop = false;

int main() {
    sig_stop = true;

    assert(reader_main() == 0);

    return 0;
}