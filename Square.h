#ifndef SQUARE_H
#define SQUARE_H

class Tile;

class Square{
	int row;
	int col;
	Tile *tile;
	int type;
public:
	Square(int x, int y);
	void selfTest() const;
	void show() const;
	int getRow() const;
	int getCol() const;
	int getType() const;
	bool placeTile( Tile *tile );
	Tile *getTile() const;
};

#endif
