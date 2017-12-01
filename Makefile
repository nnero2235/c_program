CFLAGS=-g -Wall -static-libgcc -std=c11
CC=gcc
INCLUDES=src/include
PROGRAM_ONE=build/program_third.exe
SRC=src/program_third.c
OBJS=build/program_third.o

.PHONY:
	clean

$(PROGRAM_ONE):$(OBJS)
	$(CC) $(OBJS) -o $@

$(OBJS):$(SRC)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build/*
	# del build\\* /q