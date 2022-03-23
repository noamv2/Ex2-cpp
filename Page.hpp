#pragma once
#include <vector>
#include <string>
#include "Direction.hpp"



using std::vector;




class Page{

	vector<vector<char>> rows;
	
	public:

	void newLines(int);
	void writeRange(int, int, ariel::Direction,int len , std::string);
	void eraseData(int, int, ariel::Direction, int);

	std::string readRange(int, int,ariel::Direction, int);
	std::string readPage();

};
	
