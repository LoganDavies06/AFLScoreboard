#pragma once
#include<SDL3/SDL.h>

//screen dimensions
struct screenDimensions {
    int width;
    int height;

    constexpr screenDimensions(int pWidth, int pHeight) : width(pWidth), height(pHeight) {}
};

enum class colName {
    BLACK,
    WHITE,
    DARK_GREY,
    GREY
};

SDL_Color getCol(colName c);