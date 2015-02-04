#ifndef TILE_H
#define TILE_H

class Square;

class Tile{
	char letter;
	int points;
	Square *square;
	bool isOnBoard;
public:
	Tile(char letter, int points);
	void selfTest() const;
	void show() const;
	void onBoard(bool val);
	char getLetter() const;
	int getPoints() const;
	bool getOnBoard();
	void placeInSquare( Square *square );
	Square *getSquare() const;
};

#endif
