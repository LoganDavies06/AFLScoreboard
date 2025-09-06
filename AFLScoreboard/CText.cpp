#include"CText.hpp"

#if defined(SDL_TTF_MAJOR_VERSION)
CText::CText() :
    text{ "" },
    textCol{},
    font{ nullptr }
{ }

CText::CText(CText& pText) :
    text{ pText.getMessage() },
    textCol{ pText.getCol() },
    font{ pText.getFont() }
{}

CText& CText::operator=(const CText& other) {
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

CText::CText(std::string& pText, const SDL_Color& pTextCol, TTF_Font* pFont, float pX, float pY) :
    CTexture{pX, pY},
    text{ pText },
    textCol{ pTextCol },
    font{ pFont }
{ }

CText::CText(std::string& pText, const SDL_Color& pTextCol, TTF_Font* pFont, SDL_Renderer* gRenderer, float pX, float pY) :
    CTexture{ pX, pY },
    text{ pText },
    textCol{ pTextCol },
    font{ pFont }
{
    RenderText( gRenderer );
}

void CText::setMessage(std::string& pText) {
    text = pText;
}

void CText::setMessage(std::string& pText, SDL_Renderer* renderer) {
    text = pText;
    this->RenderText(renderer);
}

void CText::setCol(SDL_Color& pTextCol) {
    textCol = pTextCol;
}

void CText::setCol(SDL_Color& pTextCol, SDL_Renderer* renderer) {
    textCol = pTextCol;
    this->RenderText(renderer);
}

void CText::setFont(TTF_Font* pFont) {
    font = pFont;
}

void CText::setFont(TTF_Font* pFont, SDL_Renderer* renderer) {
    font = pFont;
    this->RenderText(renderer);
}

std::string CText::getMessage() {
    return text;
}

SDL_Color CText::getCol() {
    return textCol;
}

TTF_Font* CText::getFont() {
    return font;
}

bool CText::RenderText( SDL_Renderer* gRenderer ){
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