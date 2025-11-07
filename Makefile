
#===Makefile==================================================================#
PROJECT_NAME=lo21
#=============================================================================#
CC=gcc
SOURCES=main.c
FLAGS= -Wall -Wextra -Werror -Wpedantic
#=============================================================================#
BUILD_DIRECTORY=build
#=============================================================================#

build:
	$(CC) $(SOURCES) -o $(BUILD_DIRECTORY)/$(PROJECT_NAME) $(FLAGS)
run:
	./$(BUILD_DIRECTORY)/$(PROJECT_NAME)

clean:
	rm -rf $(BUILD_DIRECTORY)

create-build-directory:
	mkdir -p $(BUILD_DIRECTORY)

