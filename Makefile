CC = g++
CFLAGS = -Wall -std=c++11

all: src/main.cpp
	$(CC) $(CFLAGS) src/main.cpp -o Pokemon

clean:
	rm -rf Pokemon