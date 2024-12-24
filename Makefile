CC = gcc
CFLAGS = -Wall -Wextra -I./include
SRC_DIR = src
BUILD_DIR = build
BIN = hyperdata

SRCS = $(wildcard $(SRC_DIR)/*.c) \
       $(wildcard $(SRC_DIR)/*/*.c)
OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)

$(BIN): $(OBJS)
	$(CC) $(OBJS) -o $@

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(BIN) 