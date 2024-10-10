# Documentation

## Preprocessor flags
Preprocessor flags are found in [orchestra.h](include/orchestra.h)
| Name               | Description                                                                        | Type | Required                              |
| ------------------ | ---------------------------------------------------------------------------------- | ---- | ------------------------------------- |
| O_CHECK_NULL_ARGS  | When defined, makes all functions check for arguments being NULL                   | any  | no                                    |
| O_FAILURE_NULL_ARG | Exit code for when a inputed function argument is NULL, requires O_CHECK_NULL_ARGS | int  | yes (if O_CHECK_NULL_ARGS is defined) |
| O_FAILURE_MALLOC   | Exit code for when malloc fails                                                    | int  | yes                                   |
| O_FAILURE_REALLOC  | Exit code for when realloc fails                                                   | int  | yes                                   |
| O_SUCCESS          | Exit code for a successful function call                                           | int  | yes                                   |

## o_string
~~~c
typedef struct {
    char* contents;
    size_t reserved;
    size_t size;
} o_string;
~~~
| Name     | Description                                                              |
| -------- | ------------------------------------------------------------------------ |
| contents | Contents of the string                                                   |
| reserved | Minimum size is allowed to be                                            |
| size     | Amount of chars allocated to the o_string, not including NULL terminator |

## Functions

~~~c
int o_string_init(o_string* o_string_p);
~~~
| Description                                    | Header                             | Implementation           |
| ---------------------------------------------- | ---------------------------------- | ------------------------ |
| Initiates o_string_p to size 0 and reserved 0. | [orchestra.h](include/orchestra.h) | [memory.c](src/memory.c) |

---
~~~c
int o_string_reserve(o_string* o_string_p, size_t reservation);
~~~
| Description                                              | Header                             | Implementation           |
| -------------------------------------------------------- | ---------------------------------- | ------------------------ |
| Reserves reservation amount of characters in o_string_p. | [orchestra.h](include/orchestra.h) | [memory.c](src/memory.c) |

---
~~~c
int o_string_uninit(o_string* o_string_p);
~~~
| Description            | Header                             | Implementation            |
| ---------------------- | ---------------------------------- | ------------------------- |
| Uninitates o_string_p. | [orchestra.h](include/orchestra.h) | [memory.c](src/memory.c)) |

---
~~~c
int o_string_cat(o_string* o_string_p, const char* new_contents);
~~~
| Description                                          | Header                             | Implementation                       |
| ---------------------------------------------------- | ---------------------------------- | ------------------------------------ |
| Concatenates new_contents into o_string_p->contents. | [orchestra.h](include/orchestra.h) | [manipulation.c](src/manipulation.c) |

---
~~~c
int o_string_delete(o_string* o_string_p, size_t index, size_t length);
~~~
| Description                                                            | Header                             | Implementation                       |
| ---------------------------------------------------------------------- | ---------------------------------- | ------------------------------------ |
| Deletes length amount of characters at index from o_string_p->contents | [orchestra.h](include/orchestra.h) | [manipulation.c](src/manipulation.c) |

---
~~~c
int o_string_insert(o_string* o_string_p, size_t index, const char* insert);
~~~
| Description                              | Header                             | Implementation
| ---------------------------------------- | ---------------------------------- | ------------------------------------ |
| Inserts insert into o_string_p at index. | [orchestra.h](include/orchestra.h) | [manipulation.c](src/manipulation.c) |

---
~~~c
int o_string_set(o_string* o_string_p, const char* new_contents);
~~~
| Description                                         | Header                             | Implementation                       |
| --------------------------------------------------- | ---------------------------------- | ------------------------------------ |
| Changes the contents of o_string_p to new_contents. | [orchestra.h](include/orchestra.h) | [manipulation.c](src/manipulation.c) |

---
~~~c
int o_string_realloc(o_string* o_string_p, size_t new_size);
~~~
| Description                                                            | Header                                               | Implementation               |
| ---------------------------------------------------------------------- | ---------------------------------------------------- | ---------------------------- |
| Reallocates new_size amount of characters into o_string_p if required. | [orchestra_internal.h](include/orchestra_internal.h) | [internal.c](src/internal.c) |
