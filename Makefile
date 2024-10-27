CC ?= cc
C_FLAGS := -std=c99 $\
					 -Wall -Wextra -Wpedantic $\
					 -Og -g -march=native -pipe $\
					 -Iinclude

DIRECTORIES := build build/tests

OBJECT_FILES := build/internal.o build/manipulation.o build/memory.o
TEST_OBJECT_FILES := build/tests/main.o

all: ${DIRECTORIES} liborchestra.a test

${DIRECTORIES}:
	-mkdir ${DIRECTORIES}

build/%.o: src/%.c
	${CC} -c $< ${C_FLAGS} -o $@

liborchestra.a: ${OBJECT_FILES}
	ar rcs liborchestra.a ${OBJECT_FILES}

test: liborchestra.a ${TEST_OBJECT_FILES}
	${CC} ${TEST_OBJECT_FILES} -L. -lorchestra -o test

clean:
	-rm -rf ${DIRECTORIES}
	-rm -f liborchestra.a
