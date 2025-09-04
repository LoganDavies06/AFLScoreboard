#include"LButton.hpp"

LButton::LButton() :
	buttonRect{},
	mainCol{ 0, 0, 0, 0 },
	outlineCol{ 0, 0, 0, 0 },
	hoverCol{ 0, 0, 0, 0 },
	text{},
	outlineWidth{ 0 }
{
	loadOutlineRect();
}

LButton::LButton(LRect& pRectangle, float pOutlineWidth, LText& pText):
	buttonRect{ pRectangle },
	mainCol{ pRectangle.getColour() },
	outlineCol{ pRectangle.getColour() },
	hoverCol{ pRectangle.getColour() },
	text{ pText },
	outlineWidth{ pOutlineWidth }
{
	loadOutlineRect();
}

LButton::LButton(float x, float y, float w, float h, SDL_Color& pMainCol, SDL_Color& pHoverCol, SDL_Color& pOutlineCol, float pOutlineWidth, std::string& pMessage, SDL_Color& pTextColour, TTF_Font* pFont) :
	buttonRect{ x, y, w, h, pMainCol },
	mainCol{ pMainCol },
	outlineCol{ pOutlineCol },
	hoverCol{ pHoverCol },
	text{ pMessage, pTextColour, pFont },
	outlineWidth{ pOutlineWidth }
{
	loadOutlineRect();
}

LButton::LButton(float x, float y, float w, float h, SDL_Color& pMainCol, SDL_Color& pHoverCol, SDL_Color& pOutlineCol, float pOutlineWidth, LText& pText) :
	buttonRect{ x, y, w, h, pMainCol },
	mainCol{ pMainCol },
	outlineCol{ pOutlineCol },
	hoverCol{ pHoverCol },
	text{ pText },
	outlineWidth{ pOutlineWidth }
{
	loadOutlineRect();
}

void LButton::setPosition(float x, float y, float w, float h) {
	buttonRect.setPosition(x, y, w, h);
	loadOutlineRect();
}

void LButton::setRect(LRect& pRectangle) {
	buttonRect = pRectangle;
	loadOutlineRect();
}

void LButton::setCentre(float x, float y) {
	buttonRect.setCentre(x, y);
	loadOutlineRect();
}

void LButton::setMainCol(SDL_Color& pMainCol) {
	mainCol = pMainCol;
}

void LButton::setHoverCol(SDL_Color& pHoverCol){
	hoverCol = pHoverCol;
}

void LButton::setOutlineCol(SDL_Color& pOutlineCol){
	outlineCol = pOutlineCol;
	loadOutlineRect();
}

void LButton::setOutlineWidth(float pOutlineWidth){
	outlineWidth = pOutlineWidth;
	loadOutlineRect();
}

void LButton::setText(LText& pText){
	text = pText;
}

void LButton::setMessage(std::string pMessage){
	text.setMessage(pMessage);
}

void LButton::setTextCol(SDL_Color& pCol){
	text.setCol(pCol);
}

void LButton::setFont(TTF_Font* pFont){
	text.setFont(pFont);
}

void LButton::loadOutlineRect() {
	//defines rectangle for outline
	SDL_FRect buttonDim{ buttonRect.getRect() };
	outlineRect.setPosition(buttonDim.x - (outlineWidth / 2), (buttonDim.y - (outlineWidth / 2)), (buttonDim.w + outlineWidth), (buttonDim.h + outlineWidth));
	outlineRect.setColour(outlineCol);
}

bool LButton::isClick() {
	bool mouseIn = false;
	float x = -1.f, y = -1.f;
	SDL_GetMouseState(&x, &y);
	if (buttonRect.inRect(x, y)) {
		mouseIn = true;
	}
	return mouseIn;
}

void LButton::render(SDL_Renderer* renderer) {
	text.RenderText(renderer);
	text.setCentre(buttonRect.getCentreX(), buttonRect.getCentreY());

	float x = -1.f, y = -1.f;
	SDL_GetMouseState(&x, &y);
	if (buttonRect.inRect(x, y)) {
		buttonRect.setColour(hoverCol);
	}
	else {
		buttonRect.setColour(mainCol);
	}

	outlineRect.render(renderer);
	buttonRect.render(renderer);
	text.render(renderer);
}