#pragma once
#ifndef CLASS_TETRO
#define CLASS_TETRO
#include <SDL.h>
#define size1 640

class Tetromino{
	private:

	public:
		int x1;
		int y1;
		int angle; // 0 - 0deg, 1 - 90deg, 2 - 180deg, 3 - 270deg
		Tetromino();

		enum Type { I = 0, J, L, O, S, T, Z };
		Tetromino(Type);
		
		Type type;
		void draw(SDL_Renderer* renderer);
		void move(int dx, int dy);
		void rotate();
		bool isBlock(int x, int y) const;


};
#endif