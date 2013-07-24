default: all

all: words tests

words: words.o main.cpp
	g++ -g -Wall -o words words.o main.cpp

words.o: words.cpp words.h
	g++ -g -Wall -c words.cpp

tests: words.o tests.cpp
	g++ -g -Wall -o tests words.o tests.cpp

clean:
	rm -f words tests *.o