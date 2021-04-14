#pragma once
#ifndef CLASS_GAME
#define CLASS_GAME
#include "ClassWell.h"
#include "ClassTetromino.h"
#include "ClassButton.h"
#include <iostream>
#include <fstream>
#define size1 640

using namespace std;

class Game{
	public:
		Game();
		~Game();
		bool tick();
		void close();
		string FromIntToString(int val);
		Button but{ size1 / 2 + 10, 100, 80, 30, "name", 0, 0, 255 };
		Button but2{ size1 / 2 + 10, 150, 80, 30, "name", 0, 255, 0 };
		//Button but3{ size1 / 2 + 10, 200, 80, 30, "name", 0, 255, 0 };
		void write();
		bool flag = true;
		bool flag2 = true;
	private:
		Game(const Game&);
		Game& operator=(const Game&);
		SDL_Window* window;
		
		SDL_Renderer* renderer;
		SDL_Texture* texture;
		TTF_Font* font = nullptr;
		//SDL_Surface* screen;
		Well well;
		Tetromino tetromino;
		uint32_t moveTime;

		void check(const Tetromino& t);
		void WriteText(int xPos, int yPos, string value);
		void WriteText1(int xPos, int yPos, string value);

};
#endif
