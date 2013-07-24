default: all

all: correct tests

correct: correct.o main.cpp
	g++ -Wall -g -o correct correct.o main.cpp

correct.o: correct.cpp correct.h
	g++ -c -Wall -g correct.cpp

tests: tests.cpp correct.o
	g++ -g -Wall -o tests tests.cpp correct.o

clean:
	rm -f *.o correct tests