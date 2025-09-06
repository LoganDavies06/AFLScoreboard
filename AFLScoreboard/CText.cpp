#include"CText.hpp"

#if defined(SDL_TTF_MAJOR_VERSION)
CText::CText() :
    text{ "" },
    textCol{},
    font{ nullptr }
{ }

CText::CText(const std::string& pText, const SDL_Color& pTextCol, TTF_Font* pFont, float pX, float pY) :
    CTexture{pX, pY},
    text{ pText },
    textCol{ pTextCol },
    font{ pFont }
{ }

CText::CText(const std::string& pText, const SDL_Color& pTextCol, TTF_Font* pFont, SDL_Renderer* gRenderer, float pX, float pY) :
    CTexture{ pX, pY },
    text{ pText },
    textCol{ pTextCol },
    font{ pFont }
{
    RenderText( gRenderer );
}

void CText::setMessage(const std::string& pText) {
    text = pText;
}

void CText::setMessage(const std::string& pText, SDL_Renderer* renderer) {
    text = pText;
    RenderText(renderer);
}

void CText::setCol(const SDL_Color& pTextCol) {
    textCol = pTextCol;
}

void CText::setCol(const SDL_Color& pTextCol, SDL_Renderer* renderer) {
    textCol = pTextCol;
    RenderText(renderer);
}

void CText::setFont(TTF_Font* pFont) {
    font = pFont;
}

void CText::setFont(TTF_Font* pFont, SDL_Renderer* renderer) {
    font = pFont;
    RenderText(renderer);
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