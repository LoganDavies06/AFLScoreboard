#include"LRect.hpp"

LRect::LRect() :
	rect{ 0.0f, 0.0f, 0.0f, 0.0f },
	fillCol{ 0, 0, 0, 255 }
{}

LRect::LRect(LRect& pRect) :
	rect{ pRect.getRect() },
	fillCol{ pRect.getColour() }
{ }

LRect::LRect(float px, float py, float pw, float ph, SDL_Color& pFillCol) :
	rect{px, py, pw, ph},
	fillCol{ pFillCol }
{}

void LRect::setPosition(float px, float py, float pw, float ph) {
	rect.x = px;
	rect.y = py;
	rect.w = pw;
	rect.h = ph;
}

void LRect::setColour(SDL_Color& pFillCol) {
	fillCol = pFillCol;
}

void LRect::setDimension(float pw, float ph) {
	rect.w = pw;
	rect.h = ph;
}

void LRect::setCentre(float px, float py) {
	rect.x = (px - (rect.w / 2));
	rect.y = (py - (rect.h / 2));
}

SDL_FRect LRect::getRect() const {
	return rect;
}

SDL_Color LRect::getColour() const {
	return fillCol;
}

float LRect::getCentreX() const {
	return rect.x + (rect.w / 2);
}

float LRect::getCentreY() const {
	return rect.y + (rect.h / 2);
}

bool LRect::inRect(float x, float y) const{
	bool isIn = true;
	if (x < rect.x || x >(rect.x + rect.w)) {
		isIn = false;
	}
	else if (y < rect.y || y >(rect.y + rect.h)) {
		isIn = false;
	}

	return isIn;
}

void LRect::render(SDL_Renderer * renderer) const{
	if (SDL_SetRenderDrawColor(renderer, fillCol.r, fillCol.g, fillCol.b, fillCol.a) != 0) {
		if (SDL_RenderFillRect(renderer, &rect) == 0) {
			SDL_Log("Failed to render rectangle. Error %s\n", SDL_GetError());
		}
	}
	else {
		SDL_Log("Failed to set draw colour. Error %s\n",SDL_GetError());
	}
}