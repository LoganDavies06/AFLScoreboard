#include"Structs.h"

SDL_Color getCol(colName c) {
	SDL_Color curCol{ 0,0,0,0 };
	switch (c) {
	case colName::BLACK: curCol = SDL_Color{ 0, 0, 0, 255 }; break;
	case colName::WHITE: curCol = SDL_Color{ 255, 255, 255, 255 }; break;
	case colName::DARK_GREY: curCol = SDL_Color{ 27, 27, 27, 255 }; break;
	case colName::GREY: curCol = SDL_Color{ 45, 45, 45, 255 }; break;
	}

	return curCol;
}