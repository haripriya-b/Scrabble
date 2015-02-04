#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include "Board.h"
#include "Square.h"
#include "Tile.h"
#include "Bag.h"
#include "Rack.h"
#include "Player.h"
#include "errorcodes.h"


using namespace std;

main(int argc, char* argv[])
{
	Board *board;
	board = new Board;
	board->selfTest();
	Bag *g;
	g = new Bag;
	//g->show();
	g->selfTest();
	board->selfTest();
	//board->show();
	ifstream input;
	ofstream output;
	input.open(argv[1]);
	output.open(argv[2]);
	Player p1("hari", g, board);
	
	int x,y;
	
	int turn;
	int myturn = 1;
	int numOfTiles;
	char ori;
	int num;

	while (!input.eof())
	{
	input >> turn;
	if(input.eof()) {break;}
	output << turn << " ";
	input >> num;
	input >> numOfTiles;
	input >> ori;
	
	string w = "";
	
	bool a1 = p1.getInput(w, x, y, ori, myturn, num, numOfTiles, output);
	if(a1 == true)
	{
	p1.playTurn(w,x,y,ori, myturn, output);
	}
	else {}
	cout << turn << endl;
	board->show();
	p1.show();
	cout << "tiles-left " << g->getTileCount() << endl; 
	}
	input.close();
	output << "tiles_left=" << g->getTileCount() << endl;
	output << "total_points=" << p1.getPoints() << endl;
	output.close();
	
}
