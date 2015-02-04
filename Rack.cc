#include<iostream>
#include<vector>
#include<cassert>
#include "Rack.h"
#include "Bag.h"
#include "Tile.h"

using namespace std;

Rack :: Rack(Bag *g) {
	tileCount = 0;
	
for (int i=0; i < RACKTILECOUNT ; i++)
	{
	bag = g;
	Tile *k;
	k = g->addToRack();
	rack.push_back(k);
	tileCount++;
	}
selfTest();    
} 

int Rack::getTileCount() const
{
	return tileCount;
}


void Rack :: show() {
	cout << "Rack: " << endl;
	for (Tile *t : rack)
		{
		if (t != nullptr)
			t->show();
		}
		cout << endl;

selfTest();
}

Tile *Rack :: getTile(int i) {

	return rack[i];
	}

void Rack :: refillRack()
	{
	for (int i=0; i < RACKTILECOUNT ;i++)
		{
		if(rack[i] == nullptr)
			{
			if (bag->getTileCount() > 0)
				{
				rack[i] = bag->addToRack();
				tileCount++;
				}
			}
		}
selfTest();
	}

void Rack::selfTest() const
{
	int count = 0;

	for( Tile *t : rack )
		if( t != nullptr )
			count++;

	assert( tileCount == count );

	for( Tile *t : rack )
		if( t != nullptr )
			t->selfTest();
}


Tile * Rack :: removeFromRack(char letter)
{
	Tile *t = nullptr;
	for (int i=0; i < RACKTILECOUNT ; i++)
		{
		if(rack[i]!= nullptr && rack[i]->getLetter() == letter)
			{
			t = rack[i];
			rack[i] = nullptr;
			tileCount--;
			break;
			}
		}
	selfTest();
	return t;				
}

