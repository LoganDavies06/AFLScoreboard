#include"Menus.h"
#include"CTexture.hpp"
#include"CText.hpp"
#include"CRect.hpp"

void scoreboard(SDL_Renderer* renderer, struct screenDimensions dim, struct screenDimensions size, struct Font apotek, struct Team home, struct Team away, struct Time time) {
	int barPositions[]{ -250, -90, 69, 349 };

	//horizontal bar
	CRect::drawRect(renderer, dim.w / 2 - size.w / 2, dim.h / 2, size.w, 2, getCol(colName::GREY));

	//draws vertical bars in menu
	for (int i : barPositions) {
		CRect::drawRect(renderer, dim.w / 2 + i, dim.h / 2 - size.h / 2, 2, size.h, getCol(colName::GREY));
	}
	
}