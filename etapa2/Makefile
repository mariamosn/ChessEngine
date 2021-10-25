CC := g++ -std=c++17

build: board.o moves.o main.o
	$(CC) board.o main.o moves.o -o engine

run: build
	./engine

board.o: board.cpp board.h
	$(CC) -c board.cpp

moves.o: moves.cpp moves.h
	$(CC) -c moves.cpp

main.o: main.cpp
	$(CC) -c main.cpp

clean:
	rm -f *.o engine 
