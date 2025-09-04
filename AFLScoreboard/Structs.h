#pragma once

//screen dimensions
struct screenDimensions {
    int width;
    int height;

    constexpr screenDimensions(int pWidth, int pHeight) : width(pWidth), height(pHeight) {}
};