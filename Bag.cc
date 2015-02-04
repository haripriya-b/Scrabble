#include<iostream>
#include<vector>
#include<random>
#include<cassert>
#include<time.h>
#include "Bag.h"
#include "Tile.h"

using namespace std;

Bag:: Bag()
{
	//int score[27] = {1,3,3,2,1,4,2,4,1,8,5,1,2,1,1,2,10,1,1,1,1,4,4,8,4,10,0};
	int score[27] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	int noTiles[27]= {9,2,2,4,12,2,3,2,9,1,1,4,2,6,8,2,1,6,4,6,4,2,2,1,2,1,2};
	//int noTiles[27]= {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0};
	int a = 65;		
	for (int i=0; i<26;i++)
		{
		int no = noTiles[i];
		while(no>0)
			{
			Tile *k = new Tile((char) a , score[i]);
			tiles.push_back(k);
			tileCount ++;
			no--;
			}
		a = a+1;
		}
	for (int j=0;j<2;j++)
	{
		tiles.push_back(new Tile('.', 1));
		tileCount ++;			
	}	
}	

Bag :: ~Bag()
{
}

void Bag :: show() {
	for(int l=0; l<tiles.size(); l++)
	{
		tiles[l]->show();
	}
}

void Bag::selfTest() const
{
	assert(tileCount >= 0 && tileCount <= 100);
	int count = 0;
	for( count=0; count < MAXTILES && tiles[count] != nullptr; count++ )	// makes sure that the size of vector tiles is same as the tileCount.
		;
	assert(count == tileCount);
}

int Bag :: getTileCount() const
	{
	return tileCount;
	} 


Tile *Bag :: addToRack()
	{
	srand (time (NULL));
	int k = tiles.size();
	int v = rand() % k;
	Tile *q;
	q = tiles[v];
	tiles.erase(tiles.begin() + v);
	tileCount --;
	return q;
	}
