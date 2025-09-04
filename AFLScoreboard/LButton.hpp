#pragma once

#include<SDL3/SDL.h>
#include<String>
#include"Structs.h"
#include"LRect.hpp"
#include"LText.hpp"

class LButton {
public:
	//constructors
	LButton();
	LButton(LRect& pRectangle, float pOutlineWidth, LText& pText);
	LButton(float x, float y, float w, float h, SDL_Color& pMainCol, SDL_Color& pHoverCol, SDL_Color& pOutlineCol, float pOutlineWidth, std::string& pMessage, SDL_Color& pTextColour, TTF_Font* pFont);
	LButton(float x, float y, float w, float h, SDL_Color& pMainCol, SDL_Color& pHoverCol, SDL_Color& pOutlineCol, float pOutlineWidth, LText& pText);

	//mutators
	void setPosition(float x, float y, float w, float h);
	void setRect(LRect& pRectangle);
	void setCentre(float x, float y);

	void setMainCol(SDL_Color& pMainCol);
	void setHoverCol(SDL_Color& pHoverCol);
	void setOutlineCol(SDL_Color& pOutlineCol);
	void setOutlineWidth(float pOutlineWidth);

	void setText(LText& pText);
	void setMessage(std::string pMessage);
	void setTextCol(SDL_Color& pCol);
	void setFont(TTF_Font* pFont);

	void loadOutlineRect();
	bool isClick();
	void render(SDL_Renderer* renderer);
	
private:
	LRect buttonRect, outlineRect;
	SDL_Color mainCol, hoverCol, outlineCol;
	float outlineWidth;

	LText text;
};