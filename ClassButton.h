#pragma once
#ifndef CLASS_BUTTON
#define CLASS_BUTTON
//#include <cstdlib>
//#include <cstdio>
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>


using namespace std;

class Button {
private:

public:
	int x, y, w, h, r, g, b;
	string str;
	Button() {
		x = y = 100;
		w = 100;
		h = 50;
		str = "Button";
		r = 255;
		g = 0;
		b = 0;
	}
	Button(int X, int Y, int W, int H, string name, int R, int G, int B) {
		x = X;
		y = Y;
		w = W;
		h = H;
		str = name;
		r = R;
		g = G;
		b = B;
	}
	~Button() {

	};
	bool Click(int x, int y);
	void init(SDL_Renderer* ren);
	void drawing(SDL_Renderer* ren);
	void dimensions(int X, int Y, int W, int H, string name) {

	}
};
#endif