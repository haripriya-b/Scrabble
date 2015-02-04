#ifndef RACK_H
#define RACK_H
#include<vector>
#include "Bag.h"

using namespace std;

class Tile;
const int RACKTILECOUNT = 7;
class Rack {

Bag *bag;
vector<Tile*> rack;
int tileCount;

public:
	Rack(Bag *g);
	void show();
	Tile * removeFromRack(char letter);
	int getTileCount() const;
	void selfTest() const;
	Tile * getTile(int i);
	void refillRack();
};
#endif
