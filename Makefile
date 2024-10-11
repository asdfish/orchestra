CC ?= gcc
C_STANDARD := -std=c11

ORCHESTRA_OBJECT_FILES := build/internal.c.o build/manipulation.c.o build/memory.c.o
TEST_OBJECT_FILES := build/test.c.o

INCLUDE_FLAGS := -Iinclude

DEBUG_FLAGS := -Wall -Wextra -Wpedantic
OPTIMIZATION_FLAGS := -Og -g

# setup
define COMPILE
	${CC} ${C_STANDARD} -c $(1) ${INCLUDE_FLAGS} ${DEBUG_FLAGS} ${OPTIMIZATION_FLAGS} -o build/$(notdir $(1)).o

endef

all: build liborchestra.a

build:
	mkdir build

# liborchestra.a
build/internal.c.o: include/* src/internal.c
	$(call COMPILE,src/internal.c)

build/manipulation.c.o: include/* src/manipulation.c
	$(call COMPILE,src/manipulation.c)

build/memory.c.o: include/* src/memory.c
	$(call COMPILE,src/memory.c)

liborchestra.a: ${ORCHESTRA_OBJECT_FILES}
	ar rcs liborchestra.a ${ORCHESTRA_OBJECT_FILES}

# test
build/test.c.o: test.c
	$(call COMPILE,test.c)

test: liborchestra.a ${TEST_OBJECT_FILES}
	${CC} ${TEST_OBJECT_FILES} -L. -lorchestra -o test

# utils
clean:
ifneq (, $(wildcard build))
	rm -rf build
endif
ifneq (, $(wildcard liborchestra.a))
	rm -f liborchestra.a
endif
ifneq (, $(wildcard test))
	rm -f test
endif

run: all test
	valgrind --gen-suppressions=all ./test
