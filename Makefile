#compiles puzzleTest.cpp and Sudoku.cpp

CC = g++

default: test

test: puzzleTest.cpp Puzzle.h
	$(CC) -o test puzzleTest.cpp

sudoku: sudoku.cpp Puzzle.h
	$(CC) -o sudoku sudoku.cpp

clean:
	rm test *~ sudoku a.out
