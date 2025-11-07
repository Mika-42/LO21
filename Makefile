
#===Makefile==================================================================#
PROJECT_NAME=lo21
#=============================================================================#
CC = gcc
SOURCES = sources/*.c
FLAGS = -Wall -Wextra -Werror -Wpedantic
INCLUDE_DIRECTORY = -Isources
#=============================================================================#
BUILD_DIRECTORY=build
#=============================================================================#

build: create-build-directory
	$(CC) $(INCLUDE_DIRECTORY) $(SOURCES) -o $(BUILD_DIRECTORY)/$(PROJECT_NAME) $(FLAGS)
run:
	./$(BUILD_DIRECTORY)/$(PROJECT_NAME)

clean:
	rm -rf $(BUILD_DIRECTORY)

create-build-directory:
	mkdir -p $(BUILD_DIRECTORY)

