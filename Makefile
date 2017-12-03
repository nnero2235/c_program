CFLAGS=-g -Wall -static-libgcc -std=c11
CC=gcc
INCLUDES=src/common.h
PROGRAM=build/program.exe
MAIN=src/program_fourth.c
MAIN_TARGET=$(patsubst %.c,%.o,build/$(notdir $(MAIN)))
OBJS=$(MAIN_TARGET) build/utils.o build/stack.o build/input.o

.PHONY:
	clean

$(PROGRAM):$(OBJS)
	$(CC) $(OBJS) -o $@

$(MAIN_TARGET): $(MAIN) $(INCLUDES)
	$(CC) $(CFLAGS) -c $(MAIN) -o $@

build/utils.o:src/utils.c $(INCLUDES)
	$(CC) $(CFLAGS) -c src/utils.c -o $@

build/stack.o:src/stack.c $(INCLUDES)
	$(CC) $(CFLAGS) -c src/stack.c -o $@

build/input.o:src/input.c $(INCLUDES)
	$(CC) $(CFLAGS) -c src/input.c -o $@

clean:
	rm -rf build/*
	# del build\\* /q