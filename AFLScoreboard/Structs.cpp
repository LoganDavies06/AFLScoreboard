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

//Score class function definitions
Score::Score() :
	goals{0},
	behinds{0}
{}

void Score::goalScored() {
	goals++;
	lastScore = 1;
}

void Score::behindScored() {
	behinds++;
	lastScore = 0;
}

void Score::removeLastScore() {
	if (lastScore == 1) {
		removeLastGoal();
	}
	else if (lastScore == 0) {
		removeLastBehind();
	}
	else {
		SDL_Log("No score to remove");
	}
}

void Score::removeLastGoal() {
	goals--;
}

void Score::removeLastBehind() {
	behinds--;
}

int Score::getGoals() {
	return goals;
}

int Score::getBehinds() {
	return behinds;
}

int Score::getScore() {
	return (6 * goals) + behinds;
}
