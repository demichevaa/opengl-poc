#include <stdio.h>
#include "register.h"

static void **OBJECT_INDEX[200];
static size_t sequence = 0;

size_t sequence_get_next() {
        return sequence++;
}

void * register_get(size_t key) {
        return OBJECT_INDEX[key];
}

int register_add(size_t key, void *value) {
        OBJECT_INDEX[key] = value;
        printf("[INDEX:ADD] -> Object(%zu) registered in index\n", key);

        return EXIT_SUCCESS;
}
