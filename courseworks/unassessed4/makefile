default: braille

all: braille tests

braille: braille.o main.cpp
	g++ -g -Wall -o braille main.cpp braille.o

braille.o: braille.cpp braille.h
	g++ -g -Wall -c braille.cpp

tests: braille.o tests.cpp
	g++ -g -Wall -o tests tests.cpp braille.o

clean:
	rm -f *.o tests braille