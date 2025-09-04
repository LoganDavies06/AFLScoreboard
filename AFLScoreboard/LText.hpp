#pragma once

#include<SDL3/SDL.h>
#include<SDL3_image/SDL_image.h>
#include<SDL3_ttf/SDL_ttf.h>
#include<string>
#include"LTexture.hpp"

class LText : public LTexture{
public:
    #if defined(SDL_TTF_MAJOR_VERSION)
    LText();
    LText(LText& pText);
    LText& operator=(const LText&);
    LText(std::string& pText, SDL_Color& pTextCol, TTF_Font* pFont, float pX = 0.f, float pY = 0.f);
    LText(std::string& textureText, SDL_Color& textColour, TTF_Font* gFont, SDL_Renderer* gRenderer, float pX = 0.f, float pY = 0.f);

    //mutators
    void setMessage(std::string& pText);
    void setCol(SDL_Color& pTextCol);
    void setFont(TTF_Font* pFont);

    //accessors
    std::string getMessage();
    SDL_Color getCol();
    TTF_Font* getFont();

    //Creates texture from text
    bool RenderText( SDL_Renderer* gRenderer );
    #endif
private:
    std::string text;
    SDL_Color textCol;
    TTF_Font* font;
};