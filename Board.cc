#include<iostream>
#include<cassert>
#include<vector>
#include<string>
#include<fstream>
#include "Board.h"
#include "Square.h"
#include "Tile.h"
#include "Rack.h"
#include "errorcodes.h"

using std::cout;
using std::endl;

Board::Board()
{
	for(int rndx=0; rndx < ROWSIZE; rndx++){
		for(int cndx=0; cndx < ROWSIZE; cndx++){
			Square *s = new Square(rndx,cndx);
			squares[rndx][cndx] = s;
		}
	}
	selfTest();
}

bool Board :: chkBoard(int row, int col)
	{
	bool status = false;
	if(squares[row][col]->getTile() != nullptr)
		{
		status = true;
		}
	return status;
}


string Board :: extractWord(int x, int y, char direction ,int& score) {
	string eword = "";
	score = 0;
	while (x <ROWSIZE && y<ROWSIZE && squares[x][y]->getTile() != nullptr )
		{
		char c = squares[x][y]->getTile()->getLetter();
		if (squares[x][y]->getType() == 0)
			score = score + squares[x][y]->getTile()-> getPoints(); 
		else if (squares[x][y]->getType() == 1 && squares[x][y]->getTile()->getOnBoard() == false)
			score = score + 2*(squares[x][y]->getTile()-> getPoints()); 
		else if (squares[x][y]->getType() == 2 && squares[x][y]->getTile()->getOnBoard() == false)
			score = score + 3*(squares[x][y]->getTile()-> getPoints()); 
		
		else
			score = score + squares[x][y]->getTile()-> getPoints();





		eword = eword + c;
		(direction == 'h') ? ++y : ++x;		
		}
	selfTest();
	return eword;
}


string Board :: extractWord(Tile *t, char direction ,int& score )
	{
	int x, y;
	string eword = "";
	Square *s = t->getSquare();
	x = s->getRow();
	y = s->getCol();
		while (squares[x][y]->getTile() != nullptr){
		(direction == 'h') ? --x : --y;
		if (y<0 || x<0) {break;}		
		}

	(direction == 'h') ? x = x+1 : y = y+1;
	if (x== s->getCol() || y == s->getRow())
		{
		if(x+1 < ROWSIZE && y+1 < ROWSIZE)
			{(direction == 'h') ? x = x+1 : y = y+1;
		if (squares[x][y]->getTile() != nullptr)
			{
			(direction == 'h') ? x = x-1 : y = y-1;	
			(direction == 'h') ? direction = 'v' : direction = 'h';	
			eword = extractWord(x,y,direction,score);
			}	}
		else {
			if (squares[x][y]->getTile() != nullptr)
			{
			(direction == 'h') ? direction = 'v' : direction = 'h';	
			eword = extractWord(x,y,direction,score);
			}	}
		}
	else
		{
		(direction == 'h') ? direction = 'v' : direction = 'h';
		eword = extractWord(x,y,direction, score);
		}
	
	return eword;
}

string Board :: mainWord (int x, int y, char direction, int& score)
	{
	while (squares[x][y]->getTile() != nullptr)
		{
		(direction == 'h') ? y-- : x--;
		if (y<0 || x<0) {break;}
		}
	
	(direction == 'h') ? y = y+1 : x = x+1;
	string eword = "";
	int a=x, b=y;
	eword = extractWord(x,y,direction,score);
	while (a<ROWSIZE && b<ROWSIZE && squares[a][b]->getTile() != nullptr)
		{
		squares[a][b]->getTile()->onBoard(true);
		(direction == 'h') ? b++ : a++;
		}
	return eword;

	}
bool Board :: placeTileOnBoard(int row, int col, Tile* t)  
{
	bool status = false;
	Square *sq;
	sq = squares[row][col];
	if (sq->getTile() == nullptr)
		{
		sq->placeTile(t);
		status = true;
		}
	return status;	
	selfTest();
}





bool Board :: onBoard(string w, char direction, int iniRow, int iniCol)
	{
	int noTiles = 0;
	int size = w.size();
	int i = iniRow, j = iniCol;
	 
	while (i<ROWSIZE && j<ROWSIZE)
		{
		if (squares[i][j]->getTile() == nullptr)
			{noTiles++;}
		(direction == 'h') ? j++ : i++;	
		}
	if (noTiles < size)
	{
		cout << "FALSE!! FALSE!!!" << endl;
	//output <<  ERR03 << endl;
		return false;
	}	
	else
	{
	cout << "TRUE!!" << endl;
	return true;
	}
}








bool Board :: placeTiles(string w, char direction , int iniRow, int iniCol, vector<string>& words, Rack *r, int& final, ofstream& output)
{
	bool status = false;
	int size = w.size();
	int count = 0;
	int noTiles = 0;
	int score,dw=0,tw=0;
	int x = iniRow, y = iniCol;
	int i = iniRow, j = iniCol;
	 
	while (i<ROWSIZE && j<ROWSIZE)
		{
		if (squares[i][j]->getTile() == nullptr)
			{noTiles++;}
		(direction == 'h') ? j++ : i++;	
		}
	if (noTiles < size)
	{
	output <<  ERR03 << endl;
		status = false;
	}	

	else {
	vector<Tile *> letters;
		for (char c : w)
			{
			Tile * letter = r->removeFromRack(c);
			letters.push_back(letter);
			}
		
		
	for (Tile *t : letters)
		{
		bool tstatus = false;
		while(tstatus == false)
			{
			tstatus = placeTileOnBoard(iniRow, iniCol, t);
			if (direction == 'h') {iniCol ++;}
			else {iniRow++;}
			}
		string word = extractWord(t, direction, score);
		int row = t->getSquare()->getRow();
		int col = t->getSquare()->getCol();

		if (squares[row][col]->getType() == 3 && squares[row][col]->getTile()->getOnBoard() == false)
			{
			score = 2*score; 
			dw++;
			}
		else if (squares[row][col]->getType() == 4 && squares[row][col]->getTile()->getOnBoard() == false)
			{
			score = 3*score; 
			tw++;
			}
		else
			{}
			
		if(word.size() >1)
			{
			words.push_back(word); 
			final = final+score;
			}				
		count++;
		}
	string main = mainWord(x, y, direction, score);
	while (dw > 0)
		{
		score = 2*score;
		dw--;
		}
	while (tw > 0)
		{
		score = 3*score;
		tw--;
		}
	if (main.size() > 1)
		{		
		words.push_back(main);
		final = final + score;
		}
	status = true;
	}
	selfTest();
	return status;
	
}


/*bool Board :: placeTiles(vector <Tile*> array , char direction , int iniRow, int iniCol)
{
	int size = array.size();
	int count = 0;
	if (iniRow+size-1 > ROWSIZE || iniCol+size-1 > ROWSIZE )
			{	
			cout << ERR03 << endl;
			}
		
	for (Tile *t : array)
		{
		bool tstatus = false;
		
		while(tstatus == false)
			{
			tstatus = placeTileOnBoard(iniRow, iniCol, t);
			if (direction == 'h') {iniCol ++;}
			else {iniRow++;}
			}				
		count++;
		}
	if (count == size)
		return true;
	else
		return false;
	selfTest();
	
}*/

void Board::selfTest() const
{
	for(int rndx=0; rndx < ROWSIZE; rndx++){
		for(int cndx=0; cndx < ROWSIZE; cndx++){
			assert(squares[rndx][cndx] != nullptr);
			squares[rndx][cndx]->selfTest();
		}
	}
}

void Board::show() const
{
	for(int rndx=0; rndx < ROWSIZE; rndx++){
		cout << endl << "-------------------------------------------------------------------------------------------" << endl;
		cout << "|";
		for(int cndx=0; cndx < ROWSIZE; cndx++){
			squares[rndx][cndx]->show();
		}
	}
	cout << endl << "-------------------------------------------------------------------------------------------" << endl << endl;
}
	
