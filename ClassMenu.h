#pragma once

#ifndef CLASS_MENU
#define CLASS_MENU
#include "ClassPerson.h"
#include "ClassGame.h"
#include <SDL_mixer.h>
#include <algorithm>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int fontSize = 30;

class Menu {
	private:
		SDL_Window* mWindow;
		SDL_Renderer* mRenderer;
		Mix_Music* music = NULL;
		TTF_Font* font;
		SDL_Texture* texture;
		string name;
		int winX, winY;
		int mWidth;
		int mHeight;
		//bool ComparePersons(const Person&, const Person&);
		bool go = false;
		bool flag = true;


	public:

		Button b1{ SCREEN_WIDTH/2 - 100, 100, 200, 50, "begin", 255, 0, 0 };
		Button b2{ SCREEN_WIDTH / 2 - 100, 200, 200, 50, "infor", 0, 0, 255 };
		Button b3{ SCREEN_WIDTH / 2 - 100, 300, 200, 50, "exit", 0, 255, 0 };
		Button b4{ SCREEN_WIDTH / 2 + 100, 400, 140, 50, "return", 255, 0, 0 };
		bool init();
		void start();
		void Drawing(int x, int y);
		void WriteTextButton(int xPos, int yPos, string value);
		void WriteText(int xPos, int yPos, string value);
		string FromIntToString(int val);
		void begin();
		void Music();
		void Table();
		void close() {
			mWindow = nullptr;
			mRenderer = nullptr;
			music = nullptr;
			font = nullptr;
			texture = nullptr;
			Mix_CloseAudio();
			TTF_Quit();
			SDL_Quit();
		}
	~Menu() {
		close();
	}
	Menu() {
		
		mWindow = nullptr;
		mRenderer = nullptr;
		TTF_Font* font = nullptr;

		name = "MENU";
		winX = SDL_WINDOWPOS_UNDEFINED;
		winY = SDL_WINDOWPOS_UNDEFINED;

		mWidth = 0;
		mHeight = 0;
		
	}


};
#endif
