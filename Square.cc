#include<iostream>
#include<iomanip>
#include <stdlib.h> 
#include<cassert>
#include "Square.h"
#include "Tile.h"
#define RESET_COLOR "\e[m"
#define MAKE_GREEN "\e[32m"
#define RED "\e[41m"   
#define BLUE "\e[44;1m"
#define DBLUE "\e[43m"
#define PINK "\e[45;1m"

using namespace std;

class Tile;

/*
type 0 normal
type 1 double letter     blue
type 2 triple letter	yellow
type 3 double word	violet
type 4 triple word	red
*/

Square::Square(int x, int y) : row(x), col(y)
{
		if ((x == 0 || x == 14) && (y == 0 || y == 7 || y == 14)) {type = 4;}else if ((x == 7) && (y == 0|| y == 14)) {type = 4;}	

		else if ((x==1 || x==2 || x==3 || x==4 || x==10 || x==11 || x==12 || x==13) && (y==x || y== (14-x))) {type = 3;} else if(x==7 && y ==7) {type = 3;}

		else if ((x==1 || x==13) && (y==5 || y==9)) {type = 2;}else if ((x==5 || x==9) && (y==1 || y==5 || y==9 || y==13)) {type = 2;}


		else if ((x==0 || x==14) && (y==3 || y==11)) {type = 1;}else if ((x==2 || x==12) && (y==6 || y==8)) {type = 1;}
		else if ((x==3 || x==11) && (y==0 || y==7 || y==14)) {type = 1;}else if ((x==6 || x==8) && (y==2 ||y==6 || y==8 || y==12)) {type = 1;}		
		else if ((x==7) && (y==3 || y==11)) {type = 1;}


		else {type = 0;}	
}

int Square::getRow() const
{
	return row;
}

int Square::getCol() const
{
	return col;
}

int Square::getType() const
{
	return type;
}


bool Square::placeTile( Tile *newtile )
{
	bool status=true;
	// Place the tile in square only if square is empty
	if( newtile != nullptr && tile == nullptr && newtile != tile ){
		tile = newtile;
		if( tile->getSquare() != this )
			tile->placeInSquare(this);
		status = true;
	}
	else
		// Cannot place new tile if square is already occupied
		status = false;

	selfTest();
	return status;
}


Tile * Square::getTile() const
{
	return tile;
}

void Square::show() const
{
	if(tile == nullptr)
	{
	if (type == 1)
	{
	std::cout<< BLUE << std::setw(4) << (row*15)+col
		<< std::setw(4) << RESET_COLOR<< "|" ;
	}
	else if (type == 2)
	{
	std::cout << DBLUE << std::setw(4) << (row*15)+col 
		<< std::setw(4) << RESET_COLOR << "|" ;
	}
	else if (type == 3)
	{
	std::cout << PINK << std::setw(4) << (row*15)+col 
		<< std::setw(4) << RESET_COLOR << "|" ;
	}
	else if (type == 4)
	{
	std::cout << RED << std::setw(4) << (row*15)+col  
		<< std::setw(4) << RESET_COLOR << "|" ;
	}
	else if (type == 0)
	{
	std::cout << MAKE_GREEN << std::setw(4) << (row*15)+col
		<< std::setw(4) << RESET_COLOR << "|" ;
	}	
	}
	else
	{
		char alpha = tile->getLetter();
		std :: cout << std::setw(3)<< alpha << std::setw(3) << "|" ;
	}
}

void Square::selfTest() const
{
	// Include all "invariants" here
	// Invariants are those conditions that can never be false
	// during the life time of an object

	// The tile's square must match with this square
	assert( tile == nullptr || this == tile->getSquare() );
}
