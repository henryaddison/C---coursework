default: piglatin

all: piglatin tests

clean:
	rm -f tests piglatin *.o

piglatin: piglatin.o main.cpp
	g++ -Wall -g -o piglatin piglatin.o main.cpp

piglatin.o: piglatin.cpp piglatin.h
	g++ -Wall -g -c piglatin.cpp

tests: tests.cpp piglatin.o
	g++ -Wall -g -o tests tests.cpp piglatin.o