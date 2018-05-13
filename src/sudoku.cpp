#include <iostream>
#include <string>
#include "Sudoku.h"

int main(){
	
	Sudoku sudoku("hardest-sudoku.txt");
	sudoku.print();
	
	std::cout << "\n\n";

	std::string sol = sudoku.solve();
	if(sol.size() == SQUARES){

		for(int i = 0; i < DIGITS; i++){
			for(int j = 0; j < DIGITS; j++){
				int idx = DIGITS * i + j;
				std::cout << sol[idx] << ' ';
			}
			std::cout << '\n';
		}
	}	

	return 0;
}
