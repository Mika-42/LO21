
#===Makefile==================================================================#
PROJECT_NAME=lo21
#=============================================================================#
CC = gcc
DEBUGGER = gdb
SOURCES_DIRECTORY = sources
SOURCES_FILES = $(shell find sources -type f -name "*.c")
FLAGS = -Wall -Wextra -Werror -Wpedantic
INCLUDE_DIRECTORY = -I$(SOURCES_DIRECTORY)/queue -I$(SOURCES_DIRECTORY)/rule
#=============================================================================#
BUILD_DIRECTORY=build
#=============================================================================#

build-debug: create-build-directory
	$(CC) -g  -Og $(INCLUDE_DIRECTORY) $(SOURCES_FILES) -o $(BUILD_DIRECTORY)/$(PROJECT_NAME) $(FLAGS)

build-release: create-build-directory
	 $(CC) -DNDEBUG -O3 $(INCLUDE_DIRECTORY) $(SOURCES_FILES) -o $(BUILD_DIRECTORY)/$(PROJECT_NAME) $(FLAGS)

debug-run:
	$(DEBUGGER) ./$(BUILD_DIRECTORY)/$(PROJECT_NAME)
run:
	./$(BUILD_DIRECTORY)/$(PROJECT_NAME)

clean:
	rm -rf $(BUILD_DIRECTORY)

create-build-directory:
	mkdir -p $(BUILD_DIRECTORY)

