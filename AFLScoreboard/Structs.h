#pragma once
#include<SDL3/SDL.h>
#include<SDL3_ttf/SDL_ttf.h>
#include<map>

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

enum class colName {
    BLACK,
    WHITE,
    DARK_GREY,
    GREY
};

SDL_Color getCol(colName c);