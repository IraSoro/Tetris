#include "ClassMenu.h"

struct less_than_ball {
	inline bool operator() (const Person& struct1, const Person& struct2) {
		return (struct1.ball > struct2.ball);
	}
};

void Menu::Table() {
	vector <Person> pers;
	ifstream in;
	in.open("1.txt");
	while (!in.eof()) {
		string name;
		in>>name;
		if (name.size() > 0) {
			int score;
			in >> score;
			pers.push_back(Person(score, name));
		}
		
	}
	in.close();

	int len = pers.size();
	sort(pers.begin(), pers.end(), less_than_ball());
	cout<<"SORT:"<<endl;
	/*for (int j = 0; j < len; j++) {
		cout << "name:"<<pers[j].name << endl;
		cout << "score:"<<pers[j].ball << endl;
	}*/
	
	SDL_RenderClear(mRenderer);
	//SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderPresent(mRenderer);

	int Oy = 10;
	int Ox = 0;

	if (len >= 3)
		for (int i = 0; i < 3; i++) {
			Ox = 0;
			Ox += 10;
			WriteText(Ox, Oy, FromIntToString(i+1));
			Ox += 30;
			WriteText(Ox, Oy, pers[i].name);
			string str = FromIntToString(pers[i].ball);
			Ox += 370;
			WriteText(Ox, Oy, str);
			Oy += 50;
		}
	else if (len == 2)
			for (int i = 0; i < 2; i++) {
				Ox = 0;
				Ox += 10;
				WriteText(Ox, Oy, FromIntToString(i + 1));
				Ox += 30;
				WriteText(Ox, Oy, pers[i].name);
				string str = FromIntToString(pers[i].ball);
				Ox += 370;
				WriteText(Ox, Oy, str);
				Oy += 50;
			}
			else if (len == 1) {
					Ox += 10;
					WriteText(Ox, Oy, "1.");
					Ox += 30;
					WriteText(Ox, Oy, pers[0].name);
					string str = FromIntToString(pers[0].ball);
					Ox += 370;
					WriteText(Ox, Oy, str);
				
				}

	
	b4.init(mRenderer);
	WriteTextButton(b4.x + 60, b4.y + 20, "RETURN");
	

	SDL_RenderPresent(mRenderer);
}

string Menu::FromIntToString(int val) {
	stringstream a1;
	string str;
	a1 << val;
	a1 >> str;
	return str;
}


void Menu::start() {
	Game game;
	if (go)
		while (game.tick());
	flag = false;
	return;
}


bool Menu::init() {
	
	mWindow = SDL_CreateWindow(name.c_str(), winX, winY, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (mWindow != NULL) {
		mWidth = SCREEN_WIDTH;
		mHeight = SCREEN_HEIGHT;

		//Create renderer for window
		mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (mRenderer == NULL) {
			printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			SDL_DestroyWindow(mWindow);
			mWindow = NULL;
		}
		else {
			SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		}
	}
	else {
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
	}
	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		cout << "SDL_AUDIO could not initialize! SDL Error: " << SDL_GetError() << endl;
		return false;
	}
	else Music();
	TTF_Init();
	font = TTF_OpenFont("ClearSans-Thin.ttf", fontSize);
	if (!font) {
		cout << "Font create error. " << TTF_GetError() << endl;
		return false;
	}
	else {
		cout << "All right" << endl;
	}
	
	

	b1.init(mRenderer);
	WriteTextButton(b1.x+100, b1.y+20, "START");
	b2.init(mRenderer);
	WriteTextButton(b2.x + 100, b2.y + 20, "TABLE");
	b3.init(mRenderer);
	WriteTextButton(b3.x + 100, b3.y + 20, "EXIT");
	
	SDL_RenderPresent(mRenderer);
	
	
	return mWindow != NULL && mRenderer != NULL;
}

void Menu::Drawing(int x, int y) {
	SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(mRenderer);
	SDL_DestroyTexture(texture);

	/*b1.drawing(mRenderer);
	WriteText(b1.x, b1.y, "START");
	b2.drawing(mRenderer);
	b3.drawing(mRenderer);*/

	SDL_RenderPresent(mRenderer);
}

void Menu::Music() {
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		return ;
	}
	music = Mix_LoadMUS("tetris2.mp3");

	//Если не получилось
	if (music == NULL){
		cout << "NO" << endl;
		return ;
	}

	if (Mix_PlayingMusic() == 0){
		//Запускаем проигрываение музыки
		if (Mix_PlayMusic(music, -1) == -1){
			return ;
		}
	}

}


void Menu::WriteTextButton(int xPos, int yPos, string value) {
	font = TTF_OpenFont("ClearSans-Thin.ttf", fontSize);
	SDL_Color fontColor; fontColor.r = 0; fontColor.g = 0; fontColor.b = 0;
	SDL_Surface* surface = NULL;

	SDL_DestroyTexture(texture);


	surface = TTF_RenderUTF8_Blended(font, value.c_str(), fontColor);
	texture = SDL_CreateTextureFromSurface(mRenderer, surface);

	int fontWidth = 0, fontHeight = 0;
	SDL_QueryTexture(texture, NULL, NULL, &fontWidth, &fontHeight);
	SDL_Rect textRect;

	textRect = { xPos, yPos, fontWidth, fontHeight };
	textRect.x -= int(textRect.w / 2);
	textRect.y -= int(textRect.h / 2);

	SDL_RenderCopy(mRenderer, texture, NULL, &textRect);
	SDL_FreeSurface(surface);

}

void Menu::WriteText(int xPos, int yPos, string value) {
	font = TTF_OpenFont("ClearSans-Thin.ttf", 20);
	SDL_Color color = { 255, 255, 0 };
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, value.c_str(), color);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(mRenderer, surfaceMessage);

	SDL_Rect Message_rect;

	int x = strlen(value.c_str());
	Message_rect.x = xPos;
	Message_rect.y = yPos;
	Message_rect.w = 20 * x;
	Message_rect.h = 35;


	SDL_RenderCopy(mRenderer, Message, NULL, &Message_rect);
	SDL_RenderPresent(mRenderer);
}

void Menu::begin() {

	if (!init()) {
		printf("Failed to initialize!\n");
	}
	else {
		bool quit = false;
		SDL_Event e;

		while (!quit) {
			if (!flag) return;
			while (SDL_WaitEvent(&e) != 0) {
				if (e.type == SDL_QUIT) 
					return;

				switch (e.type) {
				case SDL_MOUSEMOTION:
					SDL_Log("Mouse Move. X=%d, Y=%d, RelativeX=%d, RelativeY=%d", e.motion.x, e.motion.y, e.motion.xrel, e.motion.yrel);
					break;

				case SDL_MOUSEBUTTONDOWN:
					SDL_Log("Mouse Button Down %u", e.button.button);
					if (b1.Click(e.motion.x, e.motion.y)) { go = true; start(); }
					if (b2.Click(e.motion.x, e.motion.y)) { /*go = false; start();*/Table(); }
					if (b3.Click(e.motion.x, e.motion.y)) return;
					if (b4.Click(e.motion.x, e.motion.y)) {
																SDL_RenderClear(mRenderer);
																SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
																SDL_RenderPresent(mRenderer);
																b1.init(mRenderer);
																WriteTextButton(b1.x + 100, b1.y + 20, "START");
																b2.init(mRenderer);
																WriteTextButton(b2.x + 100, b2.y + 20, "TABLE");
																b3.init(mRenderer);
																WriteTextButton(b3.x + 100, b3.y + 20, "EXIT");

																SDL_RenderPresent(mRenderer);
															};

					break;

				case SDL_MOUSEBUTTONUP:
					SDL_Log("Mouse Button Up %u", e.button.button);
					break;
				}
			}
		}
	}
}
