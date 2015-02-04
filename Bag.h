#ifndef BAG_H
#define BAG_H
#include<vector>

using namespace std;

const int MAXTILES = 100;


class Tile;


class Bag {
	vector<Tile*> tiles;
	int tileCount = 0;
	
	
public:
	Bag();
	~Bag();
	Tile *addToRack();
	int getTileCount() const;
	void show();
	void selfTest() const;
};
#endif
