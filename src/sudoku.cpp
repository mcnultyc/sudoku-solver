#include <iostream>
#include <string>
#include "Sudoku.h"

int main(){
		
	Sudoku sudoku("hardest-sudoku.txt");
	
	std::string sol(sudoku.solve());
	std::vector<Entry> search_report(sudoku.search_report());
	std::string search_sol(SQUARES, '0');
	
	std::cout << "solution:\n";	
	for(int i = 0; i < DIGITS; i++){
		for(int j = 0; j < DIGITS; j++){
			int idx = DIGITS * i + j;
			std::cout << sol[idx] << ' ';
		}
		std::cout << '\n';
	}	

	return 0;
}
