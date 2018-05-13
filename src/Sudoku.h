#ifndef SUDOKU_H
#define SUDOKU_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_set>

#define DIGITS 9
#define SQUARES 81
#define UNITS 3
#define PEERS 20


class Sudoku{	
	
	template<typename T>
	using hash_set = std::unordered_set<T>;

	template<typename T>
	using hash_sets = std::vector<hash_set<T>>;

	public:

	explicit Sudoku(const std::string& file_name);
	void print();
	std::string solve();

	private:

	void init(const std::string& file_name);
	void init_grid(const std::string& file_name);    	
	void init_peers();
	void init_units();
	void create_values(hash_sets<char>& vals);
	void create_unit_list(hash_sets<int>& unit_list);

	inline bool solved(const hash_sets<char>& vals);	
	inline int min_sqr(const hash_sets<char>& vals);

	bool assign(hash_sets<char>& vals, int sqr, char digit);
	bool eliminate(hash_sets<char>& vals, int sqr, char digit);	
	bool search(hash_sets<char>& vals);	

	std::string grid;	
	std::string solution;
	// units and peers for each square
	hash_set<int> peers[SQUARES];
	hash_sets<int> units[SQUARES];
};

#endif
