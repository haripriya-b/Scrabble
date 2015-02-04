#include<cassert>
#include<iostream>
#include<iomanip>
#include "Tile.h"
#include "Square.h"

using std::cout;
using std::endl;

Tile::Tile(char l, int p) : letter(l), points(p), square(nullptr), isOnBoard(false)
{
}

char Tile::getLetter() const
{
	return letter;
}

int Tile::getPoints() const
{
	return points;
}
bool Tile :: getOnBoard()
	{
	return isOnBoard;
	}

void Tile :: onBoard(bool val)
	{
	isOnBoard = val;
	}

void Tile::placeInSquare( Square *s )
{
	square = s;
	if( s!=nullptr && s->getTile() != this )
		s->placeTile( this );
}

Square * Tile::getSquare() const
{
	return square;
}

void Tile::show() const
{
	cout << " " << letter << ":" << std::setw(2) << points;
}

void Tile::selfTest() const
{
	assert( square == nullptr || this == square->getTile() );
}
