CFLAGS=-g -Wall -static-libgcc -std=c99
CC=gcc
PROGRAM=build/program.exe
MAIN=src/test.c
MAIN_TARGET=$(patsubst %.c,%.o,build/$(notdir $(MAIN)))
OBJS=$(MAIN_TARGET) build/nstr.o build/queue.o 
#build/wordcnt.o

.PHONY:
	clean

$(PROGRAM):$(OBJS)
	$(CC) $(OBJS) -o $@

$(MAIN_TARGET): $(MAIN) 
	$(CC) $(CFLAGS) -c $(MAIN) -o $@

build/nstr.o:src/nstr.c src/nstr.h src/testhelper.h
	$(CC) $(CFLAGS) -c src/nstr.c -o $@
	
build/queue.o:src/queue.c src/queue.h src/testhelper.h
	$(CC) $(CFLAGS) -c src/queue.c -o $@

# build/wordcnt.o:src/wordcnt.c $(INCLUDES)
# 	$(CC) $(CFLAGS) -c src/wordcnt.c -o $@

test_nstr:
	$(CC) $(CFLAGS) src/nstr.c -o build/nstr.exe

clean:
	rm -rf build/*
	# del build\\* /q