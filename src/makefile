sudoku-solver: sudoku.o Sudoku.o
	g++ -o sudoku-solver sudoku.o Sudoku.o

sudoku.o: sudoku.cpp
	g++ -std=c++11 -c sudoku.cpp
Sudoku.o: Sudoku.cpp
	g++ -std=c++11 -c Sudoku.cpp

clean:
	rm sudoku-solver sudoku.o Sudoku.o
