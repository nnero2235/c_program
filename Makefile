STANDARD=-g -Wall -static-libgcc -std=c99
WIN_FLAGS= -fexec-charset=gbk -finput-charset=UTF-8
CC=gcc
PROGRAM=build/program.exe
MAIN=src/pw.c
MAIN_TARGET=$(patsubst %.c,%.o,build/$(notdir $(MAIN)))
OBJS=$(MAIN_TARGET) build/nstr.o build/queue.o build/wordcnt.o build/debug.o

CFLAGS=$(STANDARD) $(WIN_FLAGS)

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

build/wordcnt.o:src/wordcnt.c src/wordcnt.h
	$(CC) $(CFLAGS) -c src/wordcnt.c -o $@

build/debug.o:src/debug.o src/debug.h
	$(CC) $(CFLAGS) -c src/debug.c -o $@

test_nstr:
	$(CC) $(CFLAGS) src/nstr.c src/debug.c -o build/program.exe

test_lklist:
	$(CC) $(CFLAGS) src/nstr.c src/lklist.c src/debug.c -o build/program.exe

clean:
	rm -rf build/*
	# del build\\* /q