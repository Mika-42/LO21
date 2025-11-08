PROJECT_NAME := lo21

CC := gcc
DEBUGGER := gdb

SOURCES_DIRECTORY := sources
INCLUDE_DIRECTORY := -I$(SOURCES_DIRECTORY)/queue -I$(SOURCES_DIRECTORY)/rule
BUILD_DIRECTORY := build
UNIT_TEST_DIRECTORY := unit-test
BUILD_UNIT_TEST_DIRECTORY := build-unit-test

UNIT_TEST_SOURCES_FILES := $(shell find $(UNIT_TEST_DIRECTORY) -type f -name "*.c")
SOURCES_FILES := $(shell find sources -type f -name "*.c")
HEADERS_FILES := $(shell find sources -type f -name "*.h")

SOURCES_WITH_HEADER := $(filter $(HEADERS_FILES), $(SOURCES_FILES:.c=.h))
C_FILES := $(SOURCES_WITH_HEADER:.h=.c)

DEBUG_FLAG := -g -Og
RELEASE_FLAG := -DNDEBUG -O3
FLAGS := -Wall -Wextra -Werror -Wpedantic


MAKEFLAGS += --no-print-directory

build-debug: create-build-directory 
	@$(MAKE) build-generic COMPILATION_FLAGS="$(DEBUG_FLAG)" SRCS_FILES="$(SOURCES_FILES)" OUTPUT_FILENAME="$(BUILD_DIRECTORY)/$(PROJECT_NAME)"
	
build-release: create-build-directory
	@$(MAKE) build-generic COMPILATION_FLAGS="$(RELEASE_FLAG)" SRCS_FILES="$(SOURCES_FILES)" OUTPUT_FILENAME="$(BUILD_DIRECTORY)/$(PROJECT_NAME)"

build-unit-test: create-build-unit-test-directory
	$(foreach FILE, $(shell find $(UNIT_TEST_DIRECTORY) -type f -name "*.c"), @$(MAKE) build-unit-test-generic FILES="$(FILE) $(C_FILES)" OUTPUT_FILE="$(notdir $(FILE:.c=))";)

run-debug:
	$(DEBUGGER) ./$(BUILD_DIRECTORY)/$(PROJECT_NAME)

run:
	./$(BUILD_DIRECTORY)/$(PROJECT_NAME)

run-unit-test:
	./$(BUILD_UNIT_TEST_DIRECTORY)/$(FILENAME)

run-all-unit-test:
	./$(BUILD_UNIT_TEST_DIRECTORY)/*

run-unit-test-debug:
	$(DEBUGGER) ./$(BUILD_UNIT_TEST_DIRECTORY)/$(FILENAME)
clean:
	rm -rf $(BUILD_DIRECTORY)

clean-unit-test:
	rm -rf $(BUILD_UNIT_TEST_DIRECTORY)

create-build-directory:
	mkdir -p $(BUILD_DIRECTORY)

create-build-unit-test-directory:
	mkdir -p $(BUILD_UNIT_TEST_DIRECTORY)

build-generic:
	 $(CC) $(COMPILATION_FLAGS) $(INCLUDE_DIRECTORY) $(SRCS_FILES) -o $(OUTPUT_FILENAME) $(FLAGS)

build-unit-test-generic: 
	@$(MAKE) build-generic COMPILATION_FLAGS="$(DEBUG_FLAG)" SRCS_FILES="$(FILES)" OUTPUT_FILENAME="$(BUILD_UNIT_TEST_DIRECTORY)/$(OUTPUT_FILE)"
