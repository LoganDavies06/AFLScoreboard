#pragma once
#include<SDL3/SDL.h>
#include"Structs.h"


class CRect {
public:
	//default constructor
	CRect();
	//copy constructor
	CRect(CRect& pRect);
	//constructor with parameters
	CRect(float px, float py, float pw, float ph, SDL_Color& pFillCol);

	//mutators
	void setPosition(float px, float py, float pw, float ph);
	void setColour(SDL_Color& pFillCol);
	void setCentre(float px, float py);
	void setDimension(float pw, float ph);

	//accessors
	SDL_FRect getRect() const;
	SDL_Color getColour() const;
	float getCentreX() const;
	float getCentreY() const;

	//renders rectangle
	bool inRect(float x, float y) const;
	void render(SDL_Renderer * gRenderer) const;

private:
	SDL_FRect rect; //rectange

	SDL_Color fillCol; //colour of rectangle
};