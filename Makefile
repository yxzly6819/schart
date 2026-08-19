SRCS = $(shell find . -name "*.c")
HEADERS = $(shell find . -name "*.h")
TARGET = ./build/test
CFLAGS = -Wall -Werror -g 

.PHONY: all test clean gdb

all: $(TARGET)

$(TARGET): $(SRCS) $(HEADERS)
	mkdir -p $(dir $@)
	gcc $(SRCS) $(CFLAGS) -o $@

test: $(TARGET)
	$(TARGET)

gdb: $(TARGET)
	gdb $(TARGET)

clean:
	rm -rf $(TARGET)