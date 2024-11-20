CC ?= cc
CFLAGS ?= -O2 -march=native -pipe
COMMONFLAGS := -Wall -Wextra -Wpedantic $\
							 -O2 -march=native -pipe $\
							 -Iinclude

# comment/uncomment to disable/enable
# PROCESS_HEADER_FILES := yes
PROCESSED_HEADER_FILES := $(if ${PROCESS_HEADER_FILES},$\
														$(subst .h,$\
															$(if $(findstring clang,${CC}),$\
																.h.pch,$\
																.h.gch),$\
															$(shell find include -name '*.h')))

OBJECT_FILES := $(patsubst src/%.c,$\
										build/%.o,$\
										$(shell find src -name '*.c' -not -path './src/tests/*'))

# uncomment/comment to enable/disable
# BUILD_TEST := yes
TEST_OBJECT_FILES := $(patsubst src/%.c,$\
											 build/%.o,$\
											 $(shell find src/tests -name '*.c'))

LIBORCHESTRA_REQUIREMENTS := ${PROCESSED_HEADER_FILES} ${OBJECT_FILES}
TEST_REQUIREMENTS := liborchestra.a ${TEST_OBJECT_FILES}

define COMPILE
${CC} -c $(1) ${CFLAGS} ${COMMONFLAGS} -o $(2)
endef
define REMOVE
$(if $(wildcard $(1)),$\
	$(info rm $(1))
	$(shell rm $(1)))

endef
define REMOVE_LIST
	$(foreach ITEM,$\
		$(1),$\
		$(call REMOVE,${ITEM}))

endef

all: liborchestra.a $(if ${BUILD_TEST},test)

build/%.o: src/%.c
	$(call COMPILE,$<,$@)

%.gch: %
	$(call COMPILE,$<,$@)

%.pch: %
	$(call COMPILE,$<,$@)

liborchestra.a: ${LIBORCHESTRA_REQUIREMENTS}
	ar rcs liborchestra.a ${OBJECT_FILES}

test: ${TEST_REQUIREMENTS}
	${CC} ${TEST_OBJECT_FILES} -L. -lorchestra -o test

clean:
	$(call REMOVE_LIST,${LIBORCHESTRA_REQUIREMENTS})
	$(call REMOVE_LIST,${TEST_REQUIREMENTS})
	$(call REMOVE,test)
	$(call REMOVE,liborchestra.a)

.PHONY: all clean
