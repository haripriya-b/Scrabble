#ifndef BOARD_H
#define BOARD_H
#include<vector>


using namespace std;
class Rack;
class Tile;
class Square;
const int NUMSQUARES = 225;
const int ROWSIZE = 15;

class Board{
	Square *squares[ROWSIZE][ROWSIZE];
public:
	Board();
	void selfTest() const;
	void show() const;
	bool chkBoard(int row, int col);
	bool onBoard(string w, char direction, int iniRow, int iniCol);
	bool placeTileOnBoard(int row, int col, Tile* t);
	bool placeTiles(string w , char direction , int iniRow , int iniCol, vector<string>& words, Rack *r, int& final, ofstream& output);
	bool placeTiles(vector <Tile*> , char direction , int iniRow , int iniCol);	
	string extractWord(int x, int y, char direction, int& score);
	string extractWord(Tile *t, char direction, int& score );
	string mainWord (int x, int y, char direction, int& score);
	};

#endif
