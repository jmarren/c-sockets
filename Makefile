TARGET = build/main

CC=clang

BUILD_DIR = build

SRCS = $(wildcard *.c)

OBJS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRCS))


all: $(TARGET)

main: main.c
	$(CC) -o main main.c

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -f $(TARGET) $(OBJS)
	rm -rf $(BUILD_DIR)


.PHONY: all clean
