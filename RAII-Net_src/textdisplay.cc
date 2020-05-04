#include "textdisplay.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;


TextDisplay::TextDisplay(){
	vector<string> border;
	for(int x = 0; x < 8; x++){
		border.emplace_back("=");
	}
	display.emplace_back(border);
	vector<string> row1;
	vector<string> row2;
	char curr = 'a';
	for(int x = 0; x < 8; x++){
		if(x == 3 || x == 4){
			row1.emplace_back("S");
			row2.emplace_back(string(1, curr));
		}
		else{
			row1.emplace_back(string(1,curr));
			row2.emplace_back(".");
		}
		curr++;
	}
	display.emplace_back(row1);
	display.emplace_back(row2);
	for(int y = 2; y < 6; y++){
		vector<string> row;
		for(int x = 0; x < 8; x++){
			row.emplace_back(".");
		}
		display.emplace_back(row);
	}
	row1.clear();
	row2.clear();
	curr = 'A';
	for(int x = 0; x < 8; x++){
		if(x == 3 || x == 4 ){
			row1.emplace_back(string(1, curr));
		row2.emplace_back("S");
		}
		else{
			row1.emplace_back(".");
			row2.emplace_back(string(1, curr));
		}
		curr++;;
	}
	display.emplace_back(row1);
	display.emplace_back(row2);
	display.emplace_back(border);
	row1.clear();
	row1.shrink_to_fit();
	row2.clear();
	row2.shrink_to_fit();
	border.clear();
	border.shrink_to_fit();
}


ostream &operator<<(ostream &out, const TextDisplay &td){
	// cycles through the rows
	for(auto &row: td.display){
		// prints each cell
		for(auto &cell: row){
			out << cell;
		}
		out << std::endl;
		
	}
	return out;
}

void TextDisplay::notify(int x, int y, string symbol){
	display.at(y).at(x) = symbol;
}

TextDisplay::~TextDisplay(){
	for(auto &row: display){
		vector<string>().swap(row);
	}
	vector<vector<string>>().swap(display);

}
