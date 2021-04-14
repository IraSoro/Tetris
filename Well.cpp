#include "ClassWell.h"
#define fontsize 15

Well::Well() :
	data{ {false} }
{
	font1 = TTF_OpenFont("ClearSans-Thin.ttf", fontsize);
}

void Well::draw(SDL_Renderer* renderer){
	
	SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
	for (int x = 0; x < Width; ++x)
		for (int y = 0; y < Height; ++y){
			if (data[x][y]){
				SDL_Rect rect{ x * size1 / 2 / 10 + 1, y * size1 / 2 / 10 + 1, size1 / 2 / 10 - 2, size1 / 2 / 10 - 2 };
				SDL_RenderFillRect(renderer, &rect);
			}
			else
				SDL_RenderDrawPoint(renderer, x * size1 / 2 / 10 + size1 / 2 / 10 / 2,
												y * size1 / 2 / 10 + size1 / 2 / 10 / 2);
		}
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
	SDL_RenderDrawLine(renderer, 0, 1, size1/2 + 100 , 1);
	SDL_RenderDrawLine(renderer, 0, size1 - 1, size1 / 2 + 100, size1 - 1);
	SDL_RenderDrawLine(renderer, 0, 0, 0, size1);
	SDL_RenderDrawLine(renderer, size1/2, 1, size1 / 2 , size1 - 1);
	SDL_RenderDrawLine(renderer, size1 / 2 + 100 - 1, 1, size1 / 2 + 100 - 1, size1 - 1);
	string s = FromIntToString(ch);
	WriteText(size1/2 + 10, 50, s, renderer);
}

bool Well::isCollision(const Tetromino& t) {
	for (int x = 0; x < 4; ++x)
		for (int y = 0; y < 4; ++y)
			if (t.isBlock(x, y)){
				int wx = t.x1 + x;
				int wy = t.y1 + y;
				if (wx < 0 || wx >= Width || wy < 0 || wy >= Height)
					return true;
				if (data[wx][wy])
					return true;
			}
	
	
	return false;
}

void Well::unite(const Tetromino& t){
	for (int x = 0; x < 4; ++x)
		for (int y = 0; y < 4; ++y)
			if (t.isBlock(x, y)) {
				data[t.x1 + x][t.y1 + y] = true;		
			}
	ch += 4;
	
	for (int y = Height - 1; y >= 0; --y){
		bool solid = true;
		for (int x = 0; x < Width; ++x)
			if (!data[x][y]){
				solid = false;
				break;
			}
			if (solid){
				for (int yy = y - 1; yy >= 0; yy--)
					for (int x = 0; x < Width; ++x)
						data[x][yy + 1] = data[x][yy];
				ch += 10;
				//cout << "ch = " << ch << endl;
				y++;
			}
	}

}
void Well::WriteText(int xPos, int yPos, string value, SDL_Renderer* renderer) {
	
	SDL_Color color = { 255, 255, 0 };  
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font1, value.c_str(), color);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); 

	SDL_Rect Message_rect; 

	int x = strlen(value.c_str());
	Message_rect.x = xPos;  
	Message_rect.y = yPos; 
	Message_rect.w = 20 * x; 
	Message_rect.h = 35; 
	

	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

}



string Well::FromIntToString(int val) {
	stringstream a1;
	string str;
	a1 << val;
	a1 >> str;
	return str;
}
