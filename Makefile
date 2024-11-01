CC ?= cc
C_FLAGS := -std=c99 $\
					 -Wall -Wextra -Wpedantic $\
					 -O2 -march=native -pipe $\
					 -Iinclude

OBJECT_FILES := build/internal.o build/manipulation.o build/memory.o
TEST_OBJECT_FILES := build/tests/main.o

all: liborchestra.a test

build/%.o: src/%.c
	${CC} -c $< ${C_FLAGS} -o $@

liborchestra.a: ${OBJECT_FILES}
	ar rcs liborchestra.a ${OBJECT_FILES}

test: liborchestra.a ${TEST_OBJECT_FILES}
	${CC} ${TEST_OBJECT_FILES} -L. -lorchestra -o test

clean:
ifneq (, $(wildcard liborchestra.a))
	rm -f liborchestra.a
endif

.PHONY: all clean
