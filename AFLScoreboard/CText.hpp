#pragma once

#include<SDL3/SDL.h>
#include<SDL3_image/SDL_image.h>
#include<SDL3_ttf/SDL_ttf.h>
#include<string>
#include"CTexture.hpp"

class CText : public CTexture{
public:
    #if defined(SDL_TTF_MAJOR_VERSION)
    CText();
    CText(CText& pText);
    CText& operator=(const CText&);
    CText(std::string& pText, const SDL_Color& pTextCol, TTF_Font* pFont, float pX = 0.f, float pY = 0.f);
    CText(std::string& textureText, const SDL_Color& textColour, TTF_Font* gFont, SDL_Renderer* gRenderer, float pX = 0.f, float pY = 0.f);

    //mutators
    void setMessage(std::string& pText);
    void setMessage(std::string& pText, SDL_Renderer* renderer);
    void setCol(SDL_Color& pTextCol);
    void setFont(TTF_Font* pFont);
    void setCol(SDL_Color& pTextCol, SDL_Renderer* renderer);
    void setFont(TTF_Font* pFont, SDL_Renderer* renderer);


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