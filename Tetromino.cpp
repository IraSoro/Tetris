#include "ClassTetromino.h"


Tetromino::Tetromino() {

}

Tetromino::Tetromino(Type type) :
	type(type),
	x1(10 / 2 - 4 / 2),
	y1(0),
	angle(0)
{}

void Tetromino::draw(SDL_Renderer* renderer){
	switch (type){
	case I:
		SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0xff);
		break;
	case J:
		SDL_SetRenderDrawColor(renderer, 0x80, 0x80, 0x80, 0xff);
		break;
	case L:
		SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0xff, 0xff);
		break;
	case O:
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x7f, 0xff);
		break;
	case S:
		SDL_SetRenderDrawColor(renderer, 0xff, 0x7f, 0x00, 0xff);
		break;
	case T:
		SDL_SetRenderDrawColor(renderer, 0x7f, 0x40, 0x00, 0xff);
		break;
	case Z:
		SDL_SetRenderDrawColor(renderer, 0x00, 0x7f, 0x7f, 0xff);
		break;
	}
	 

	for (int x = 0; x < 4; ++x)
		for (int y = 0; y < 4; ++y)
			if (isBlock(x, y)){
				SDL_Rect rect{ (x + x1) * size1/ 2 / 10 + 1, (y + y1) * size1 / 2 / 10 + 1, size1 / 2 / 10 - 2, size1 / 2 / 10 - 2 };
				SDL_RenderFillRect(renderer, &rect);
			}
}

void Tetromino::move(int dx, int dy) {	//���������

	x1 += dx;
	y1 += dy;
}

void Tetromino::rotate() {				//�������
	angle += 3;
	angle %= 4;
}


bool Tetromino::isBlock(int x, int y) const{
	static const char* Shapes[][4] = {
	  {
		" *  "
		" *  "
		" *  "
		" *  ",
		"    "
		"****"
		"    "
		"    ",
		" *  "
		" *  "
		" *  "
		" *  ",
		"    "
		"****"
		"    "
		"    ",
	  },
	  {
		"  * "
		"  * "
		" ** "
		"    ",
		"    "
		"*   "
		"*** "
		"    ",
		"**  "
		"*   "
		"*   "
		"    ",
		"    "
		"*** "
		"  * "
		"    ",
	  },
	  {
		" *  "
		" *  "
		" ** "
		"    ",
		"    "
		"*** "
		"*   "
		"    ",
		" ** "
		"  * "
		"  * "
		"    ",
		"  * "
		"*** "
		"    "
		"    ",
	  },
	  {
		"    "
		" ** "
		" ** "
		"    ",
		"    "
		" ** "
		" ** "
		"    ",
		"    "
		" ** "
		" ** "
		"    ",
		"    "
		" ** "
		" ** "
		"    ",
	  },
	  {
		"  * "
		" ** "
		" *  "
		"    ",
		"    "
		"**  "
		" ** "
		"    ",
		"  * "
		" ** "
		" *  "
		"    ",
		"    "
		"**  "
		" ** "
		"    ",
	  },
	  {
		" *  "
		" ** "
		" *  "
		"    ",
		"    "
		"*** "
		" *  "
		"    ",
		" *  "
		"**  "
		" *  "
		"    ",
		" *  "
		"*** "
		"    "
		"    ",
	  },
	  {
		" *  "
		" ** "
		"  * "
		"    ",
		"    "
		" ** "
		"**  "
		"    ",
		" *  "
		" ** "
		"  * "
		"    ",
		"    "
		" ** "
		"**  "
		"    ",
	  },
	};
	return Shapes[type][angle][x + y * 4] == '*';
}
