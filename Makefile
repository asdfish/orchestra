CC ?= cc
C_FLAGS := -std=c99 $\
					 -Wall -Wextra -Wpedantic $\
					 -O2 -march=native -pipe $\
					 -Iinclude

DIRECTORIES := build build/tests

OBJECT_FILES := build/internal.o build/manipulation.o build/memory.o
TEST_OBJECT_FILES := build/tests/main.o

all: ${DIRECTORIES} liborchestra.a

${DIRECTORIES}:
	$(foreach DIRECTORY,$\
		${DIRECTORIES},$\
		$(if $(wildcard ${DIRECTORY}),,$\
			$(shell mkdir ${DIRECTORY})$\
		)$\
	)

build/%.o: src/%.c
	${CC} -c $< ${C_FLAGS} -o $@

liborchestra.a: ${OBJECT_FILES}
	ar rcs liborchestra.a ${OBJECT_FILES}

test: liborchestra.a ${TEST_OBJECT_FILES}
	${CC} ${TEST_OBJECT_FILES} -L. -lorchestra -o test

clean:
	$(foreach DIRECTORY,$\
		${DIRECTORIES},$\
		$(if $(wildcard ${DIRECTORY}),$\
			$(shell rm -rf ${DIRECTORY})$\
		)$\
	)
ifneq (, $(wildcard liborchestra.a))
	rm -f liborchestra.a
endif

.PHONY: all clean
