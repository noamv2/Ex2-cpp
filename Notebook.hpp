#pragma once
#include <vector>
#include <string>
#include "Direction.hpp"

using std::vector;


namespace ariel {
	class Page{

	vector<vector<char>> rows;
	
	public:

	void newLines(int);
	void writeRange(int, int, ariel::Direction,int len , std::string);
	void eraseData(int, int, ariel::Direction, int);

	std::string readRange(int, int,ariel::Direction, int);
	std::string readPage();

};

	class Notebook{
		
		std::unordered_map<int ,Page> notebook;

		public:

		void write(int page, int row, int col, Direction dir, std::string data);
		std::string read(int page, int row, int col, Direction dir, int len);
		void erase(int page, int row, int col, Direction dir, int len);

		void show(int page);
		bool isIn(int);

	};
	struct badInput : std::exception {
        const char* what() const noexcept {return "Bad input";}
    };


}