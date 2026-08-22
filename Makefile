SRCS = $(shell find . -name "*.c")
HEADERS = $(shell find . -name "*.h")
TARGET = ./build/test
CFLAGS = -Wall -Werror -g 

INPUT ?= 50

.PHONY: all test clean gdb

all: $(TARGET)

$(TARGET): $(SRCS) $(HEADERS)
	mkdir -p $(dir $@)
	gcc $(SRCS) $(CFLAGS) -o $@

test: $(TARGET)
	$(TARGET) $(INPUT)

gdb: $(TARGET)
	gdb $(TARGET)

clean:
	rm -rf ./build