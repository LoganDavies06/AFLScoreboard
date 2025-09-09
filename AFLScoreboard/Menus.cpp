#include"Menus.h"
#include"CTexture.hpp"
#include"CText.hpp"
#include"CRect.hpp"

void scoreboard(SDL_Renderer* renderer, struct screenDimensions dim, struct screenDimensions size, struct Font apotek, struct Team* home, struct Team* away, CTime* time, bool clash) {
	int barPositions[]{ -250, -90, 69, 349 };

	if (time->inQtr()) {
		//horizontal bar
		CRect::drawRect(renderer, dim.w / 2.f - size.w / 2.f, dim.h / 2.f, static_cast<float>(size.w), 2.f, getCol(colName::GREY));
		//red box if paused
		if (time->isPaused()) {
			CRect::drawRect(renderer, dim.w / 2.f + 475, dim.h / 2.f - size.h / 2.f + 10, 20, 20, getCol(colName::RED));
		}
	}
	else {
		CRect::drawRect(renderer, dim.w / 2.f - size.w / 2.f, dim.h / 2.f, dim.w / 2.f + 349, 2, getCol(colName::GREY));
	}

	//draws vertical bars in menu
	for (int i : barPositions) {
		CRect::drawRect(renderer, dim.w / 2.f + i, dim.h / 2.f - size.h / 2.f, 2, static_cast<float>(size.h), getCol(colName::GREY));
	}

	//translucent team-colored rectangles
	CRect::drawRect(renderer, dim.w / 2.f - size.w / 2.f, dim.h / 2.f - size.h / 2.f, 969, 145, SDL_Color{ home->cols[0].r, home->cols[0].g , home->cols[0].b, 85 });
	if (clash) {
		CRect::drawRect(renderer, dim.w / 2.f - size.w / 2.f, dim.h / 2.f + 2, 969, 145, SDL_Color{ away->cols[2].r, away->cols[2].g , away->cols[2].b, 85 });
	}
	else {
		CRect::drawRect(renderer, dim.w / 2.f - size.w / 2.f, dim.h / 2.f + 2, 969, 145, SDL_Color{ away->cols[0].r, away->cols[0].g , away->cols[0].b, 85 });
	}

	//sets position of score texts
	home->score.setTextPositions(dim.w / 2.f - 170, dim.w / 2.f - 8, dim.w / 2.f + 210, dim.h / 2.f - size.h / 4.f);
	away->score.setTextPositions(dim.w / 2.f - 170, dim.w / 2.f - 8, dim.w / 2.f + 210, dim.h / 2.f + size.h / 4.f);

	//render text
	home->score.renderTexts(renderer);
	away->score.renderTexts(renderer);

	//render team texts
	home->nameText.setCentre(dim.w / 2.f - size.w / 2.f + 120, dim.h / 2.f - size.h / 4.f);
	away->nameText.setCentre(dim.w / 2.f - size.w / 2.f + 120, dim.h / 2.f + size.h / 4.f);

	home->nameText.render(renderer);
	away->nameText.render(renderer);

	//render team images
	home->texture.setPosition(dim.w / 2.f - 385, dim.h / 2.f - size.h / 4.f - 65);
	away->texture.setPosition(dim.w / 2.f - 385, dim.h / 2.f + size.h / 4.f - 65);

	home->texture.render(renderer, nullptr, 130.f, 130.f);
	away->texture.render(renderer, nullptr, 130.f, 130.f);

	time->renderTime(renderer, dim, size);
}