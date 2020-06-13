# MOVE THIS OUTSIDE THE SOURCE DIRECTORY (THE DIRECTORY THIS FILE IS CURRENTLY SITTING IN IS THE SOURCE DIRECTORY)
CC        := gcc
SRC_DIR   := ccalc
BUILD_DIR := build
SUB_DIR   := build/utils build/parsing build/features
BINARY    := a
LIBS      := -lm
PREPROC   := -D DEBUG_ON
CFLAGS    := -g

SOURCES := $(shell find $(SRC_DIR) -name '*.c' | sort -k 1nr | cut -f2-)
OBJECTS := $(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS    := $(OBJECTS:.o=.d)

$(BINARY) : $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBS) -o $@

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(PREPROC) -MMD -MP -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) && mkdir $(BUILD_DIR) && mkdir $(SUB_DIR)

-include $(DEPS)