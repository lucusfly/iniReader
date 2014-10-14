CC=g++
CFLAG=-O2 -Wall

all:test

test:test.o ini.o
	$(CC) $(CFLAG) -o test test.o ini.o

test.o:test.cpp ini.h
	$(CC) $(CFLAG) -c test.cpp

ini.o:ini.cpp ini.h stringCommon.h
	$(CC) $(CFLAG) -c ini.cpp

clean:
	rm *.o test
