#ifndef ORCHESTRA_H
#define ORCHESTRA_H

#define O_CHECK_NULL_ARGS

#ifdef O_CHECK_NULL_ARGS
#define O_FAILURE_NULL_ARG -1
#define O_FAILURE_MALLOC -2
#define O_FAILURE_REALLOC -3
#else
#define O_FAILURE_MALLOC -1
#define O_FAILURE_REALLOC -2
#endif

#define O_SUCCESS 0

#include <stddef.h>

typedef struct {
  char* contents;
  size_t size;
} o_string;

extern int o_string_init(o_string*);
extern int o_string_uninit(o_string*);

extern int o_string_cat(o_string*, const char*);
extern int o_string_delete(o_string*, size_t, size_t);
extern int o_string_insert(o_string*, size_t, const char*);
extern int o_string_set(o_string*, const char*);

#endif
