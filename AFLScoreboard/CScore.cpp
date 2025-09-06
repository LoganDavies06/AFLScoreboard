#include"CScore.hpp"
#include"Structs.h"
#include<SDL3/SDL.h>

//Score class function definitions
Score::Score() :
	goals{ 0 },
	behinds{ 0 },
	goalText{  },
	behindText{  },
	totalText{  }
{
}

void Score::setUpText(struct Font font, SDL_Renderer* renderer) {
	goalText.setCol(getCol(colName::WHITE));
	goalText.setFont(font.reg.at(54));
	goalText.setMessage("0", renderer);
	
	behindText.setCol(getCol(colName::WHITE));
	behindText.setFont(font.reg.at(54));
	behindText.setMessage("0", renderer);
	
	totalText.setCol(getCol(colName::WHITE));
	totalText.setFont(font.bold.at(66));
	totalText.setMessage("0", renderer);
}

void Score::renderTexts(SDL_Renderer* renderer) {
	goalText.render(renderer);
	behindText.render(renderer);
	totalText.render(renderer);

	if (!goalText.isLoaded()) {
		SDL_Log("Home score text not loaded!");
	}
}

void Score::setTextPositions(float xGoal, float xBehind, float xTotal, float y) {
	goalText.setCentre(xGoal, y);
	behindText.setCentre(xBehind, y);
	totalText.setCentre(xTotal, y);
}

void Score::refreshText(SDL_Renderer* renderer) {
	goalText.setMessage(std::to_string(goals), renderer);
	behindText.setMessage(std::to_string(behinds), renderer);
	totalText.setMessage(std::to_string(6 * goals + behinds), renderer);
}

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

void Score::destroyText() {
	goalText.destroy();
	behindText.destroy();
	totalText.destroy();
}