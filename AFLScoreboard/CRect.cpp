#include"CRect.hpp"

CRect::CRect() :
	rect{ 0.0f, 0.0f, 0.0f, 0.0f },
	fillCol{ 0, 0, 0, 255 }
{}

CRect::CRect(CRect& pRect) :
	rect{ pRect.getRect() },
	fillCol{ pRect.getColour() }
{ }

CRect::CRect(float px, float py, float pw, float ph, const SDL_Color& pFillCol) :
	rect{px, py, pw, ph},
	fillCol{ pFillCol }
{}

void CRect::setPosition(float px, float py, float pw, float ph) {
	rect.x = px;
	rect.y = py;
	rect.w = pw;
	rect.h = ph;
}

void CRect::setColour(SDL_Color& pFillCol) {
	fillCol = pFillCol;
}

void CRect::setDimension(float pw, float ph) {
	rect.w = pw;
	rect.h = ph;
}

void CRect::setCentre(float px, float py) {
	rect.x = (px - (rect.w / 2));
	rect.y = (py - (rect.h / 2));
}

SDL_FRect CRect::getRect() const {
	return rect;
}

SDL_Color CRect::getColour() const {
	return fillCol;
}

float CRect::getCentreX() const {
	return rect.x + (rect.w / 2);
}

float CRect::getCentreY() const {
	return rect.y + (rect.h / 2);
}

bool CRect::inRect(float x, float y) const{
	bool isIn = true;
	if (x < rect.x || x >(rect.x + rect.w)) {
		isIn = false;
	}
	else if (y < rect.y || y >(rect.y + rect.h)) {
		isIn = false;
	}

	return isIn;
}

void CRect::render(SDL_Renderer * renderer) const{
	if (SDL_SetRenderDrawColor(renderer, fillCol.r, fillCol.g, fillCol.b, fillCol.a) != 0) {
		if (SDL_RenderFillRect(renderer, &rect) == 0) {
			SDL_Log("Failed to render rectangle. Error %s\n", SDL_GetError());
		}
	}
	else {
		SDL_Log("Failed to set draw colour. Error %s\n",SDL_GetError());
	}
}

void CRect::drawRect(SDL_Renderer* renderer, int pX, int pY, int pW, int pH, const SDL_Color& pFillCol) {
	SDL_FRect pRect{ (float) pX, (float) pY, (float) pW, (float) pH };

	if (SDL_SetRenderDrawColor(renderer, pFillCol.r, pFillCol.g, pFillCol.b, pFillCol.a) != 0) {
		if (SDL_RenderFillRect(renderer, &pRect) == 0) {
			SDL_Log("Failed to render rectangle. Error %s\n", SDL_GetError());
		}
	}
	else {
		SDL_Log("Failed to set draw colour. Error %s\n", SDL_GetError());
	}
}

void CRect::drawRect(SDL_Renderer* renderer, SDL_FRect pRect, const SDL_Color& pFillCol) {
	if (SDL_SetRenderDrawColor(renderer, pFillCol.r, pFillCol.g, pFillCol.b, pFillCol.a) != 0) {
		if (SDL_RenderFillRect(renderer, &pRect) == 0) {
			SDL_Log("Failed to render rectangle. Error %s\n", SDL_GetError());
		}
	}
	else {
		SDL_Log("Failed to set draw colour. Error %s\n", SDL_GetError());
	}
}