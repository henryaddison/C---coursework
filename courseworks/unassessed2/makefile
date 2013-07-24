soundex: soundex.o main.cpp
	g++ -g -Wall -o soundex main.cpp soundex.o

all: soundex tests

tests: tests.cpp soundex.o
	g++ -g -Wall -o	tests tests.cpp	soundex.o

soundex.o: soundex.h soundex.cpp
	g++ -g -Wall -c soundex.cpp

clean:
	rm soundex tests *.o