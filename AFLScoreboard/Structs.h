#pragma once
#include<SDL3/SDL.h>
#include<SDL3_ttf/SDL_ttf.h>
#include<map>
#include<string>
#include"CTexture.hpp"
#include"CText.hpp"
#include"CScore.hpp"

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

//teams that are loaded
struct Team {
    std::string name;
    std::string moniker;
    std::string abr;
    //colours:         home primary,       home secondary,     clash primary,      clash secondary
    SDL_Color cols[4]{ SDL_Color{0,0,0,0}, SDL_Color{0,0,0,0}, SDL_Color{0,0,0,0}, SDL_Color{0,0,0,0} };
    Score score{ };
    CTexture texture{ };
    CText nameText{ };
};

//all teams
struct TeamData {
    std::string abr;
    std::string name;
    std::string moniker;
    //colours:         home primary,       home secondary,     clash primary,      clash secondary
    SDL_Color cols[4]{ SDL_Color{0,0,0,0}, SDL_Color{0,0,0,0}, SDL_Color{0,0,0,0}, SDL_Color{0,0,0,0} };
};