CC=g++
SRC= lib/main.cpp lib/fields.cpp lib/coordinate.cpp lib/iterator.cpp lib/maze_storage.cpp lib/utils.cpp lib/player.cpp lib/ia.cpp
CFLAGS=-pedantic -Wall -Wextra -std=c++2a
EXE=maze

.PHONY: all clean

all:
	$(CC) $(CFLAGS) $(SRC) -o $(EXE)

clean:
	rm $(EXE)
