CC = g++

DEBUG = -g

CFLAGS = -c -std=c++11

OBJS = polynomial.o source.o timer.o

FFT: $(OBJS)
	$(CC) $(OBJS) $(DEBUG) -o FFT
	
polynomial.o : polynomial.cpp polynomial.h
	$(CC) $(CFLAGS) $(DEBUG) polynomial.cpp

source.o : source.cpp
	$(CC) $(CFLAGS) $(DEBUG) source.cpp

timer.o : timer.cpp timer.h
	$(CC) $(CFLAGS) $(DEBUG) timer.cpp

clean:
	rm -f *.o
