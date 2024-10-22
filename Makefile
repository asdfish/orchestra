CC ?= cc
C_FLAGS := -std=c99 $\
					 -Wall -Wextra -Wpedantic $\
					 -O2 -march=native -pipe $\
					 -Iinclude

DIRECTORIES := build

OBJECT_FILES := build/internal.o build/manipulation.o build/memory.o

all: ${DIRECTORIES} liborchestra.a

${DIRECTORIES}:
	-mkdir ${DIRECTORIES}

${OBJECT_FILES}: build/%.o :src/%.c
	${CC} -c $< ${C_FLAGS} -o $@

liborchestra.a: ${OBJECT_FILES}
	ar rcs liborchestra.a ${OBJECT_FILES}

clean:
	-rm -rf ${DIRECTORIES}
	-rm -f liborchestra.a
