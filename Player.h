#ifndef PLAYER_H
#define PLAYER_H
#include<string>
#include "Bag.h"
#include "Board.h"
#include "Rack.h"

using namespace std;
class Bag;
class Board;
class Tile;
class Player {
	
	string name;
	Rack *rack;
	int points;
	Bag *bag;
	Board *board;

public:
	Player(string playerName, Bag *b, Board *bd);
	~Player();
	void show();
	void selfTest() const;
	int getPoints();
	bool getInput(string& word, int& x, int& y,char& orientation, int& myturn, int num, int numOfTiles, ofstream& output);
	bool checkBoard(string& word, int&x, int& y, char& orientation, int& myturn);
	bool searchRack(string& word, ofstream& output);
	void playTurn(string& word, int&x, int& y, char& orientation, int& myturn, ofstream& output);
	};

#endif
