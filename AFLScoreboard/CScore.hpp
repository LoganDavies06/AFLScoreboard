#pragma once

#include"CText.hpp"

class Score {
public:
    Score();

    void setUpText(struct Font font, SDL_Renderer* renderer);
    void refreshText(SDL_Renderer* renderer);
    void setTextPositions(float xGoal, float xBehind, float xTotal, float y);
    void renderTexts(SDL_Renderer* renderer);

    void goalScored();
    void behindScored();
    void removeLastScore();
    void removeLastGoal();
    void removeLastBehind();

    int getGoals();
    int getBehinds();
    int getScore();

    void destroyText();

private:
    int goals;
    int behinds;
    int lastScore = -1;

    CText goalText;
    CText behindText;
    CText totalText;
};