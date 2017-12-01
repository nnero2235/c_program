CFLAGS=-g -Wall -static-libgcc -std=c11
CC=gcc
INCLUDES=src/include
PROGRAM_ONE=build/program_one.exe
SRC=src/program_one.c
OBJS=build/program_one.o

.PHONY:
	clean

$(PROGRAM_ONE):$(OBJS)
	$(CC) $(OBJS) -o $@

$(OBJS):$(SRC)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del build\\* /q