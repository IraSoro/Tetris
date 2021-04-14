#include "ClassGame.h"
#include <stdexcept>

int ff = 20;

Game::Game(): tetromino {static_cast<Tetromino::Type>((int)round((float)rand() / (float)RAND_MAX * 6.0f))}, moveTime(SDL_GetTicks()){
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		runtime_error("SDL_Init(SDL_INIT_VIDEO)");
	SDL_CreateWindowAndRenderer((size1+200) / 2, size1, SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS, &window, &renderer);
	SDL_SetWindowPosition(window, size1/2, 10);
}

Game::~Game(){
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

bool Game::tick(){
	if (!flag2) return false;
	if (flag) {
		SDL_Event e;
		if (SDL_WaitEventTimeout(&e, 250)) {
			switch (e.type) {
			case SDL_MOUSEBUTTONDOWN:
				SDL_Log("Mouse Button Down %u", e.button.button);
				if (but.Click(e.motion.x, e.motion.y)) {					
					SDL_DestroyRenderer(renderer);
					SDL_DestroyWindow(window);
					//SDL_Quit();
					Game g;
					while (g.tick());
					//Game();
					//tick();
				}

				if (but2.Click(e.motion.x, e.motion.y)) return false;
				break;

			case SDL_KEYDOWN: {
				switch (e.key.keysym.sym) {
					case SDLK_DOWN: {
						Tetromino t = tetromino;
						t.move(0, 1);
						if (!well.isCollision(t))
							tetromino = t;
					}
					break;
					case SDLK_RIGHT: {
						Tetromino t = tetromino;
						t.move(1, 0);
						if (!well.isCollision(t))
							tetromino = t;
					}
					break;
					case SDLK_LEFT: {
						Tetromino t = tetromino;
						t.move(-1, 0);
						if (!well.isCollision(t))
							tetromino = t;
					}
					break;


					case SDLK_UP: {
						Tetromino t = tetromino;
						t.rotate();
						if (!well.isCollision(t))
							tetromino = t;
					}
					break;


					case SDLK_ESCAPE: {
						SDL_Quit();
					}
					break;
					}
			}
			break;

			case SDL_QUIT:
				SDL_Quit();
			}
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xff);
		SDL_RenderClear(renderer);
		well.draw(renderer);
		tetromino.draw(renderer);
		but.init(renderer);
		WriteText1(but.x+40 , but.y+11 , "again");
		but2.init(renderer);
		WriteText1(but2.x +40, but2.y + 11, "exit");
		/*Tetromino I(Tetromino::I);
		I.draw(renderer);
		Tetromino J(Tetromino::J);
		J.move(0, 4);
		J.draw(renderer);
		Tetromino L(Tetromino::L);
		L.move(0, 8);
		L.draw(renderer);
		Tetromino O(Tetromino::O);
		O.move(0, 12);
		O.draw(renderer);
		Tetromino S(Tetromino::S);
		S.move(0, 16);
		S.draw(renderer);
		Tetromino T(Tetromino::T);
		T.move(4, 16);
		T.draw(renderer);
		Tetromino Z(Tetromino::Z);
		Z.move(-4, 16);
		Z.draw(renderer);*/
		int x = 1;
		if (well.ch >= 100) {
			x = well.ch / 100;
		}
		if (SDL_GetTicks() > moveTime) {
			moveTime += 1000 / x;
			Tetromino t = tetromino;
			t.move(0, 1);
			check(t);
		}
		SDL_RenderPresent(renderer);
	}
	return true;
};

void Game::WriteText1(int xPos, int yPos, string value) {

	SDL_Color fontColor; fontColor.r = 0; fontColor.g = 0; fontColor.b = 0;
	SDL_Surface* surface = NULL;

	SDL_DestroyTexture(texture);

	font = TTF_OpenFont("ClearSans-Thin.ttf", 20);
	surface = TTF_RenderUTF8_Blended(font, value.c_str(), fontColor);
	texture = SDL_CreateTextureFromSurface(renderer, surface);

	int fontWidth = 0, fontHeight = 0;
	SDL_QueryTexture(texture, NULL, NULL, &fontWidth, &fontHeight);
	SDL_Rect textRect;

	textRect = { xPos, yPos, fontWidth, fontHeight };
	textRect.x -= int(textRect.w / 2);
	textRect.y -= int(textRect.h / 2);

	SDL_RenderCopy(renderer, texture, NULL, &textRect);
	SDL_FreeSurface(surface);

}



void Game::check(const Tetromino& t){
	if (well.isCollision(t)){
			well.unite(tetromino);
			int randomNum = (int)((float)rand() / (float)RAND_MAX * 7.0f);
			if (randomNum > 6)
				randomNum = 6;
			cout << randomNum << endl;
			tetromino = Tetromino{ static_cast<Tetromino::Type>(randomNum) };
			if (well.isCollision(tetromino)){
				//well = Well();
				flag = 0;
				cout << "FINISH" << endl;
				SDL_RenderClear(renderer);

				ff = 20;
				WriteText(60, 10, "The game over!");
				cout << "The game over!" << endl;
				//ff = 35;
				WriteText(40, 50, "Number of points:");
				string st = FromIntToString(well.ch);
				ff = 30;
				WriteText(180, 90, st);
				ff = 20;
				WriteText(20, 130, "NAME: ");
				write();				
			}
	}
	else{
		tetromino = t;
	}
}

void Game::write() {
	SDL_Event event;
	
	SDL_Color text_color = { 255, 255, 0 };

	char buf[20];
	memset(buf, 0, 20 * sizeof(char));
	int i = -1;

	bool shift = false;
	bool inputEnd = false;
	
	bool quit = true;
	while (quit) {
		while (SDL_PollEvent(&event)) {
			if (event.key.keysym.sym == SDLK_LSHIFT) shift = !shift;
			if (event.key.state == SDL_PRESSED && ((event.key.keysym.sym >= SDLK_a && event.key.keysym.sym <= SDLK_z) || (event.key.keysym.sym >= SDLK_0 && event.key.keysym.sym <= SDLK_9))) {
				if (i > 14) continue;

				event.key.state = SDL_RELEASED;
				char sym = (char)event.key.keysym.sym;
				if (shift && sym >= 'a' && sym <= 'z') sym -= 32;
				buf[++i] = sym;
				buf[i + 1] = '\0';
				cout << buf << endl;
				SDL_RenderClear(renderer);

				//ff = 20;
				WriteText(60, 10, "The game over!");
				cout << "The game over!" << endl;
				//ff = 20;
				WriteText(40, 50, "Number of points:");
				string st = FromIntToString(well.ch);
				ff = 30;
				WriteText(180, 90, st);
				ff = 20;
				WriteText(20, 130, "NAME: ");
				//ff = 20;
				WriteText(130, 130, buf);
				WriteText(70, 170, "Click ENTER");


			}
			else if (event.key.state == SDL_PRESSED && event.key.keysym.sym == SDLK_BACKSPACE) {
				if (i < 0)continue;
				buf[i--] = '\0';
				event.key.state = SDL_RELEASED;
				cout << buf << endl;
				SDL_RenderClear(renderer);
				//ff = 20;
				WriteText(60, 10, "The game over!");
				cout << "The game over!" << endl;
				//ff = 20;
				WriteText(40, 50, "Number of points:");
				string st = FromIntToString(well.ch);
				ff = 30;
				WriteText(180, 90, st);
				ff = 20;
				WriteText(20, 130, "NAME: ");
				//ff = 30;
				WriteText(150, 110, buf);
				WriteText(70, 170, "Click ENTER");
			}
			else if (event.key.keysym.sym == SDLK_RETURN) {
				if (!inputEnd) inputEnd = true;
				else continue;
				quit = false;
				ofstream out("1.txt", ios_base::app);
				out.seekp(0, ios::end);
				if (out.is_open()) {
					string name = buf;
					if (name.size() == 0)
						name = "Anonymous";
					out << name << '\t' <<FromIntToString(well.ch)<< endl;
				}
				out.close();
				cout << "ending" << endl;
				flag2 = false;

				close();
				tick();
			}
		}
	}
	
	return;
}




string Game::FromIntToString(int val) {
	stringstream a1;
	string str;
	a1 << val;
	a1 >> str;
	return str;
}

void Game::WriteText(int xPos, int yPos, string value) {
	TTF_Init();
	font = TTF_OpenFont("ClearSans-Thin.ttf", ff);


	if (!font) {
		cout << "Font create error. " << TTF_GetError() << endl;
		return;
	}
	else {
		cout << "All right" << endl;
	}

	SDL_Color color = { 255, 255, 0 };
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, value.c_str(), color);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_Rect Message_rect;

	int x = strlen(value.c_str());
	Message_rect.x = xPos;
	Message_rect.y = yPos;
	Message_rect.w = 20 * x;
	Message_rect.h = 35;


	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
	SDL_RenderPresent(renderer);

}

void Game::close() {
	//SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	//SDL_Quit();
}
