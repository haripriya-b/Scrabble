#include<iostream>
#include<iomanip>
#include<string>
#include<cassert>
#include<fstream>
#include<cstring>
#include<vector>
#include "Bag.h"
#include "Board.h"
#include "Player.h"
#include "Rack.h"
#include "Tile.h"
#include "errorcodes.h"

Player :: Player(string playerName, Bag *b, Board *bd) : name(playerName), bag(b), board(bd), points(0)
	{
	rack = new Rack(bag);
	rack-> selfTest();
	selfTest();
	}

Player :: ~Player() 
	{
	delete rack;
	}

int Player :: getPoints() {
	return points;
	}

void Player :: show() 
	{
	rack->show();
	cout << "Name: " << name << std::setw(10);	
	cout << "Points: " << points << endl;
	selfTest();
	}


bool Player :: getInput(string& word, int& x, int& y,char& orientation, int& myturn, int num, int numOfTiles, ofstream& output ) {
	do {
	x = num/15;
	y = num%15;
	int ct = numOfTiles;
	if (num<0 || num > 224) {output << ERR02 << endl;return false;}
	if (orientation != 'H' && orientation != 'V') {output << ERR07 << endl;return false;}





	int k = 0;
	while (numOfTiles > 0)
		{
		int c = 0;
		if (rack->getTileCount() == 0) {output << ERR05 << endl; return false;}
		while (rack->getTile(k) == nullptr)
			{ 
			k++;
			if (k >=7) {c=1; break;} 
			}
			if (c == 1) {output << ERR06 << endl;return false;} 
			word = word + rack->getTile(k)->getLetter();
			k++;
		numOfTiles --;	
		}	


	for (int l=0;l<word.size();l++)
		{
		word[l] = toupper(word[l]);
		}









	bool onBd = board->onBoard(word, tolower(orientation), x, y);
	if (onBd == false ) {cout << "FALSE!!!" << endl; output << ERR03 << endl; return false;}
	//if (numOfTiles > 7) {output << ERR06 << endl; return false;}
		if (myturn == 1)
		{
		if (orientation == 'H')
			{
			if (x != 7) {output << ERR01 << endl; return false;}
			else if (y+ct <= 7 || y > 7)  {output << ERR01 << endl;return false;}
			
			}
		else if (orientation == 'V')
			{
			if (y != 7) {output << ERR01 << endl;return false;}
			else if (x+ct <=7 || x > 7) {output<< ERR01 << endl;return false;}
			}

		
		}

	}while(x < 0 || x > 14 || y < 0 || y > 14 || (orientation != 'H' && orientation != 'V' ));	

	selfTest();
	orientation = tolower(orientation);
	return true;
	}

bool Player :: checkBoard(string& word, int&x, int& y, char& orientation, int &myturn) {

	bool status = false;
	if (myturn == 1) {status = true;}
	else if (orientation == 'h' )
		{
		int size = word.size();
		for (int i= y-1; i <= y+size; i++)
			{
			if (i < 0) {i++;}
			if(board->chkBoard(x,i) == true)
				{status = true;
				break;}
			if( i>=y && i < y+size && x-1 >=0 && board->chkBoard(x-1,i) == true)
				{status = true;
				break;}

			if( i>=y && i < y+size && x+1 < ROWSIZE && board->chkBoard(x+1,i) == true)
				{status = true;
				break;}			
			}
		}

	else if (orientation == 'v' )
		{
		int size = word.size();
		for (int i = x-1; i<=x+size; i++)
			{
			if (i < 0) {i++;}
			if (board->chkBoard(i,y) == true)
				{status = true;
				break;}

			if (i >=x && i < x+size && y-1 >=0 && board->chkBoard(i,y-1) == true)
				{status = true;
				break;}
			
			if (i>=x && i< x+size && y+1 < ROWSIZE && board->chkBoard(i,y+1) == true)
				{status = true;
				break;}			
			}
		}
	return status;
}

bool Player :: searchRack(string& word, ofstream& output)
	{	
	bool status = false;
	int array[8] = {0,0,0,0,0,0,0,0};
	for (char c : word)
		{
		int count = 0;
		for (int i=0;i< RACKTILECOUNT;i++)
			{
			if (array[i] == 1) {i++;}
			if (rack->getTile(i) != nullptr && rack->getTile(i)->getLetter() == c)
				{count++; array[i] = 1;break;}
			}
		if (count == 0)
			{if (rack->getTileCount() == 0) {output << ERR05 << endl;} 
			else {output << ERR06 << endl;}
			status = true;
			break;}
		}
	selfTest();
	return status;
	}


void Player :: playTurn(string& word, int&x, int& y, char& orientation, int& myturn, ofstream& output)
	{
	bool a,b;
	int final = 0;
	a = searchRack(word, output);
	b = checkBoard(word, x, y, orientation, myturn);
	if (b == false) {output << ERR01 << endl;}
	else if (a == false && b == true)
		{
		vector<string> words;
		int final = 0;		
		bool abc = board->placeTiles(word, orientation , x , y, words, rack, final, output);
		if (abc == true)
		{
		myturn = 0;
		}
		points = points+final;				
		if (words.size() > 0)
			{output << words.size() << " ";}
		if (final > 0)
			{output << final << endl;}
		if (bag->getTileCount() > 0)
			{rack->refillRack();}
		}
	}	


void Player::selfTest() const
{
	assert(rack != nullptr);
	assert(points >= 0);
	assert(rack->getTileCount() >= 0 && rack->getTileCount() <= 7);
}
