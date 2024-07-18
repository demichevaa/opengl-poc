#ifndef OPENGL_POC_STATE_H
#define OPENGL_POC_REGISTER_H


#include <stddef.h>
#include <stdlib.h>

int register_add(size_t key, void *value);
void * register_get(size_t key);

size_t sequence_get_next();

#endif //OPENGL_POC_STATE_H
