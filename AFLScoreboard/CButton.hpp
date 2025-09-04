#pragma once

#include<SDL3/SDL.h>
#include<String>
#include"Structs.h"
#include"CRect.hpp"
#include"CText.hpp"

class CButton {
public:
	//constructors
	CButton();
	CButton(CRect& pRectangle, float pOutlineWidth, CText& pText);
	CButton(float x, float y, float w, float h, SDL_Color& pMainCol, SDL_Color& pHoverCol, SDL_Color& pOutlineCol, float pOutlineWidth, std::string& pMessage, SDL_Color& pTextColour, TTF_Font* pFont);
	CButton(float x, float y, float w, float h, SDL_Color& pMainCol, SDL_Color& pHoverCol, SDL_Color& pOutlineCol, float pOutlineWidth, CText& pText);

	//mutators
	void setPosition(float x, float y, float w, float h);
	void setRect(CRect& pRectangle);
	void setCentre(float x, float y);

	void setMainCol(SDL_Color& pMainCol);
	void setHoverCol(SDL_Color& pHoverCol);
	void setOutlineCol(SDL_Color& pOutlineCol);
	void setOutlineWidth(float pOutlineWidth);

	void setText(CRext& pText);
	void setMessage(std::string pMessage);
	void setTextCol(SDL_Color& pCol);
	void setFont(TTF_Font* pFont);

	void loadOutlineRect();
	bool isClick();
	void render(SDL_Renderer* renderer);
	
private:
	CRect buttonRect, outlineRect;
	SDL_Color mainCol, hoverCol, outlineCol;
	float outlineWidth;

	CText text;
};