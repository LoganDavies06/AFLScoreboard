#pragma once
#include<SDL3/SDL.h>
#include<SDL3_ttf/SDL_ttf.h>
#include<map>
#include<string>
#include"CTexture.hpp"

//screen dimensions
struct screenDimensions {
    int w;
    int h;

    constexpr screenDimensions(int pWidth, int pHeight) : w(pWidth), h(pHeight) {}
};

struct Font {
    std::map<int, TTF_Font*> reg;
    std::map<int, TTF_Font*> bold;
    std::map<int, TTF_Font*> narrow;
    std::map<int, TTF_Font*> comp;
};

struct Time {
    int seconds{ 0 };
    float quarter{ 0.5 };
};

class Score {
public:
    Score();

    void goalScored();
    void behindScored();
    void removeLastScore();
    void removeLastGoal();
    void removeLastBehind();

    int getGoals();
    int getBehinds();
    int getScore();

private:
    int goals;
    int behinds;
    int lastScore = -1;
};

enum class colName {
    BLACK,
    WHITE,
    DARK_GREY,
    GREY
};

enum class menuID {
    SCOREBOARD
};

SDL_Color getCol(colName c);

struct Team {
    std::string name;
    std::string moniker;
    std::string abr;
    Score score{ };
    CTexture texture;
};