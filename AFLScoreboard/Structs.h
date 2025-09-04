#pragma once
#include<SDL3/SDL.h>

//screen dimensions
struct screenDimensions {
    int w;
    int h;

    constexpr screenDimensions(int pWidth, int pHeight) : w(pWidth), h(pHeight) {}
};

enum class colName {
    BLACK,
    WHITE,
    DARK_GREY,
    GREY
};

SDL_Color getCol(colName c);