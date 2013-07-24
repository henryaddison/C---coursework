substring: main.cpp substring.o
	g++ -Wall -g main.cpp substring.o -o substring

all: tests substring

tests: substring.o tests.cpp
	g++ -Wall -g substring.o tests.cpp -o tests

substring.o: substring.h substring.cpp
	g++ -Wall -g -c substring.cpp
