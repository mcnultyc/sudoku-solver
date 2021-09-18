sudoku-solver: main.o Sudoku.o
	g++ -o sudoku-solver main.o Sudoku.o

main.o: main.cpp
	g++ -std=c++11 -c main.cpp
Sudoku.o: Sudoku.cpp
	g++ -std=c++11 -c Sudoku.cpp

clean:
	rm sudoku-solver main.o Sudoku.o
