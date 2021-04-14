#pragma once
#ifndef CLASS_WELL
#define CLASS_WELL
#include <string>
#include <iostream>
#include <sstream>
#include <SDL_ttf.h>
#include "ClassTetromino.h"

using namespace std;

class Well{
public:
	Well();
	~Well() {
		TTF_CloseFont(font1);
	}
	void draw(SDL_Renderer*);
	enum { Width = 10, Height = 20 };
	bool isCollision(const Tetromino& t) ;
	void unite(const Tetromino&);
	string FromIntToString(int val);
	void WriteText(int xPos, int yPos, string value, SDL_Renderer* renderer);
	int ch = 0;
	TTF_Font* font1 = nullptr;
private:
	bool data[Width][Height];
	
};
#endif