#include"LText.hpp"

#if defined(SDL_TTF_MAJOR_VERSION)
LText::LText() :
    text{ "" },
    textCol{},
    font{ nullptr }
{ }

LText::LText(LText& pText) :
    text{ pText.getMessage() },
    textCol{ pText.getCol() },
    font{ pText.getFont() }
{}

LText& LText::operator=(const LText& other) {
    if (this != &other) {
        mTexture = other.mTexture;
        mWidth = other.mWidth;
        mHeight = other.mHeight;
        text = other.text;
        textCol = other.textCol;
        font = other.font;
    }

    return *this;
}

LText::LText(std::string& pText, SDL_Color& pTextCol, TTF_Font* pFont, float pX, float pY) :
    LTexture{pX, pY},
    text{ pText },
    textCol{ pTextCol },
    font{ pFont }
{ }

LText::LText(std::string& pText, SDL_Color& pTextCol, TTF_Font* pFont, SDL_Renderer* gRenderer, float pX, float pY) :
    LTexture{ pX, pY },
    text{ pText },
    textCol{ pTextCol },
    font{ pFont }
{
    RenderText( gRenderer );
}

void LText::setMessage(std::string& pText) {
    text = pText;
}

void LText::setCol(SDL_Color& pTextCol) {
    textCol = pTextCol;
}

void LText::setFont(TTF_Font* pFont) {
    font = pFont;
}

std::string LText::getMessage() {
    return text;
}

SDL_Color LText::getCol() {
    return textCol;
}

TTF_Font* LText::getFont() {
    return font;
}

bool LText::RenderText( SDL_Renderer* gRenderer ){
    destroy();

    if ( SDL_Surface * textSurface = TTF_RenderText_Blended( font, text.c_str(), 0, textCol ); textSurface == nullptr ){
        SDL_Log( "Unable to render text surface. SDL_ttf Error: %s\n", SDL_GetError() );
    } else {
        if ( mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface ); mTexture == nullptr ){
            SDL_Log( "Unable to create texture from rendered text. SDL Error: %s\n", SDL_GetError() );
        } else {
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        SDL_DestroySurface(textSurface);
    }

    return mTexture != nullptr;
}
#endif