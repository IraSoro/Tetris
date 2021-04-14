#include "ClassButton.h"

bool Button::Click(int ValX, int ValY) {
	if ((ValX > x) && (ValX < x + w) && (ValY > y) && (ValY < y + h)) {
		cout << "CLICK" << endl;
		return 1;
	}
	return 0;
}

void Button::init(SDL_Renderer* ren) {
	//SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0x00);
	//SDL_RenderClear(ren);

	SDL_SetRenderDrawColor(ren, r, g, b, 128);
	SDL_Rect rect1 = { x, y, w, h };
	SDL_RenderFillRect(ren, &rect1);
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
	SDL_Rect rect2 = { x + 1, y + 1, w - 2, h - 2 };
	SDL_RenderDrawRect(ren, &rect2);

	SDL_RenderPresent(ren);
}

void Button::drawing(SDL_Renderer* ren) {
	SDL_SetRenderDrawColor(ren, r, g, b, 128);
	SDL_Rect rect1 = { x, y, w, h };
	SDL_RenderFillRect(ren, &rect1);
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
	SDL_Rect rect2 = { x + 1, y + 1, w - 2, h - 2 };
	SDL_RenderDrawRect(ren, &rect2);
}
