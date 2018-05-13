#include "Sudoku.h"

Sudoku::Sudoku(const std::string& file_name)
	: grid(SQUARES, '0'){

	init(file_name);
}

void Sudoku::init(const std::string& file_name){
	std::ifstream infile(file_name);
	
	if(infile.is_open()){
		int i = 0, c;
		while((c = infile.get()) != EOF && i < SQUARES){
			if(c >= '0' && c <= '9'){
				grid[i] = c;
				i++;
			}
		}		
	}
	
	init_units();	
	init_peers();	
}

void Sudoku::create_unit_list(hash_sets<int>& unit_list){

	unit_list.resize(DIGITS * 3);
	int idx = 0;
	for(int i = 0; i < DIGITS; i++, idx++){
		for(int j = 0; j < DIGITS; j++){
			int s = DIGITS * i + j;
			unit_list[idx].insert(s);
		}
	}
	
	for(int i = 0; i < DIGITS; i++, idx++){
		for(int j = 0; j < DIGITS; j++){
			int s = DIGITS * j + i;
			unit_list[idx].insert(s);
		}
	}

	for(int i = 0; i < DIGITS; i += 3){
		for(int j = 0; j < DIGITS; j += 3, idx++){
			for(int r = i; r < i + 3; r++){
				for(int c = j; c < j + 3; c++){
					int s = DIGITS * r + c;
					unit_list[idx].insert(s);
				}
			}
		}
	}	
}

void Sudoku::init_units(){

	hash_sets<int> unit_list;
	create_unit_list(unit_list);

	for(int i = 0; i < SQUARES; i++){
		for(const hash_set<int>& u: unit_list){
			if(u.find(i) != u.end())
				units[i].push_back(u);
		}
	}
}

void Sudoku::init_peers(){

	for(int i = 0; i < SQUARES; i++){
		for(const hash_set<int>& u: units[i]){
			for(const int& s: u){
				if(s != i)
					peers[i].insert(s);
			}
		}
	}
}

void Sudoku::print(){

	for(int i = 0; i < DIGITS; i++){
		for(int j = 0; j < DIGITS; j++){
			int idx = DIGITS * i + j;
			if(grid[idx] != '0')
				std::cout << grid[idx] << ' ';
			else
				std::cout << "- ";
		}
		std::cout << '\n';
	}
}

std::vector<Entry> Sudoku::search_report(){
	return report;
}

bool Sudoku::solved(const hash_sets<char>& vals){
	
	for(int i = 0; i < SQUARES; i++){
		if(vals[i].size() != 1)
			return false;	
	}
	return true;
}

int Sudoku::min_sqr(const hash_sets<char>& vals){

	int sqr = -1, size = DIGITS;
	for(int i = 0; i < SQUARES; i++){
		if(vals[i].size() > 1 && vals[i].size() <= size){
			sqr = i; 
			size = vals[i].size();
		}		
	}
	return sqr;
}

bool Sudoku::assign(hash_sets<char>& vals, int sqr, char digit){
	
	if(report.size() > 0){
		Entry last = report.back();
		if(last.sqr != sqr || last.digit != digit)
			report.emplace_back(sqr, digit);
	}
	else{
		report.emplace_back(sqr, digit);	
	}
	
	hash_set<char> values = vals[sqr];	
	for(const char& d: values){
		if(d != digit){
			if(!eliminate(vals, sqr, d))
				return false;
		}
	}
	return true;
}

bool Sudoku::eliminate(hash_sets<char>& vals, int sqr, char d){
	
	if(vals[sqr].find(d) == vals[sqr].end())
		return true;

	vals[sqr].erase(d);

	if(vals[sqr].size() == 0)
		return false;
	else if(vals[sqr].size() == 1){
		char d = *vals[sqr].begin();

		for(const int& s: peers[sqr]){
			if(!eliminate(vals, s, d))
				return false;
		}	
	}

	for(const hash_set<int>& u: units[sqr]){
		std::vector<int> sqrs;

		for(const int& s: u){
			if(vals[s].find(d) != vals[s].end())
				sqrs.push_back(s);	
		}

		if(sqrs.size() == 0)
			return false;
		else if(sqrs.size() == 1){
			if(!assign(vals, sqrs[0], d))
				return false;
		}	
	}
	return true;
}

bool Sudoku::search(hash_sets<char>& vals){
	
	if(solved(vals)){
		for(int i = 0; i < SQUARES; i++){
			char d = *vals[i].begin();
			solution.push_back(d);
		}
		return true;
	}

	int sqr = min_sqr(vals);	
	for(const char& d: vals[sqr]){	
		hash_sets<char> vals_cp(vals);

		if(assign(vals_cp, sqr, d)){
			if(search(vals_cp)){
				return true;
			}
		}
	}
	return false;
}

std::string Sudoku::solve(){		
	
	if(solution.size() == SQUARES)
		return solution;	

	hash_sets<char> vals(SQUARES);
	for(int i = 0; i < SQUARES; i++){
		for(char c = '1'; c <= '9'; c++)
			vals[i].insert(c);
	}
	
	for(int i = 0; i < SQUARES; i++){
		if(grid[i] != '0'){
			if(!assign(vals, i, grid[i]))
				return solution;
		}
	}	

	search(vals);
	return solution;
}

