#include <iostream>
#include <string>
#include <iostream>
#include "Sudoku.h"

int main(){
	

	Sudoku sudoku("easy.txt");
	sudoku.print();
	std::cout << '\n';
	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 9; j++){
			std::cout << 9 * i + j << ' ';
		}
		std::cout << '\n';
	}

	std::cout << "------------------------units-----------------------\n";
	sudoku.print_units();
	std::cout << "------------------------peers-----------------------\n";
	sudoku.print_peers();	
	std::string sol = sudoku.solve();
	std::cout << "size: " << sol.size() << '\n';
	if(sol.size() == 81){

		for(int i = 0; i < 9; i++){
			for(int j = 0; j < 9; j++){
				int idx = 9 * i + j;
				std::cout << sol[idx] << ' ';
			}
			std::cout << '\n';
		}

	}	

	return 0;
}
