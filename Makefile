CC ?= cc
C_FLAGS := -std=c99 $\
					 -Wall -Wextra -Wpedantic $\
					 -O2 -march=native -pipe $\
					 -Iinclude

PROCESSED_HEADER_FILES := $(subst .h,$\
														$(if $(findstring clang,${CC}),$\
															.h.pch,$\
															.h.gch),$\
														$(shell find include -name '*.h'))

OBJECT_FILES := $(patsubst src/%.c,$\
										build/%.o,$\
										$(shell find src -name '*.c' -not -path './src/tests/*'))
TEST_OBJECT_FILES := $(patsubst src/%.c,$\
											 build/%.o,$\
											 $(shell find src/tests -name '*.c'))

define REMOVE_LIST
	$(foreach ITEM,$\
		$(1),$\
		$(if $(wildcard ${ITEM}),$\
			$(shell rm ${ITEM})))

endef

all: liborchestra.a

build/%.o: src/%.c
	${CC} -c $< ${C_FLAGS} -o $@

%.gch: %
	${CC} -c $< ${C_FLAGS}

%.pch: %
	${CC} -c $< ${C_FLAGS}

liborchestra.a: ${PROCESSED_HEADER_FILES} ${OBJECT_FILES}
	ar rcs liborchestra.a ${OBJECT_FILES}

test: liborchestra.a ${TEST_OBJECT_FILES}
	${CC} ${TEST_OBJECT_FILES} -L. -lorchestra -o test

clean:
	$(call REMOVE_LIST,$\
		${PROCESSED_HEADER_FILES})
	$(call REMOVE_LIST,$\
		${TEST_OBJECT_FILES})
	$(call REMOVE_LIST,$\
		${OBJECT_FILES})
ifneq (, $(wildcard test))
	rm test
endif
ifneq (, $(wildcard liborchestra.a))
	rm liborchestra.a
endif

.PHONY: all clean
