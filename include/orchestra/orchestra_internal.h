#ifndef ORCHESTRA_INTERNAL_H
#define ORCHESTRA_INTERNAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <orchestra/orchestra.h>

extern int o_string_realloc(o_string* o_string_p, size_t new_size);

#ifdef __cplusplus
}
#endif

#endif
