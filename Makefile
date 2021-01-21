CC=g++
SRC= main.cpp
CFLAGS=-pedantic -Wall -Wextra -std=c++2a
EXE=maze

.PHONY: all clean

all:
	$(CC) $(CFLAGS) lib/main.cpp -o $(EXE)

clean:
	rm $(EXE)
