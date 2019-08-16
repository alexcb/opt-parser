CC=gcc
CCFLAGS=-std=gnu11 -Wuninitialized -Wall -Werror -Wno-unused-label
LDFLAGS=-lpthread -lm -lmicrohttpd

GIT_COMMIT ?= "unknown"
BUILD_TIME := $(shell date +%s)
CCFLAGS += -DGIT_COMMIT=\"$(GIT_COMMIT)\" -DBUILD_TIME=\"$(BUILD_TIME)\"

EXAMPLESRC=$(wildcard src/common/*.c src/example/*.c)
EXAMPLEOBJ=$(EXAMPLESRC:%.c=%.o)

debug: CCFLAGS += -DDEBUG_BUILD -g
debug: all

release: CCFLAGS += -O3
release: all

all: example

example: $(EXAMPLEOBJ)
	$(CC) $(CCFLAGS) -o example $(EXAMPLEOBJ) $(LDFLAGS)


.PHONY: reformat
reformat:
	find -regex '.*/.*\.\(c\|h\)$$' -exec clang-format-7 -i {} \;

# To obtain object files
%.o: %.c
	$(CC) -I./src/client -I./src/common -I./src/test_common -c $(CCFLAGS) $< -o $@

clean:
	rm -f example $(EXAMPLEOBJ)

