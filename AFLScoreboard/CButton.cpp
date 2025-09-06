#include"CButton.hpp"

CButton::CButton() :
	buttonRect{},
	mainCol{ 0, 0, 0, 0 },
	outlineCol{ 0, 0, 0, 0 },
	hoverCol{ 0, 0, 0, 0 },
	text{},
	outlineWidth{ 0 }
{
	loadOutlineRect();
}

CButton::CButton(CRect& pRectangle, float pOutlineWidth, CText& pText):
	buttonRect{ pRectangle },
	mainCol{ pRectangle.getColour() },
	outlineCol{ pRectangle.getColour() },
	hoverCol{ pRectangle.getColour() },
	text{ pText.getMessage(), pText.getCol(), pText.getFont() },
	outlineWidth{ pOutlineWidth }
{
	loadOutlineRect();
}

CButton::CButton(float x, float y, float w, float h, SDL_Color& pMainCol, SDL_Color& pHoverCol, SDL_Color& pOutlineCol, float pOutlineWidth, std::string& pMessage, SDL_Color& pTextColour, TTF_Font* pFont) :
	buttonRect{ x, y, w, h, pMainCol },
	mainCol{ pMainCol },
	outlineCol{ pOutlineCol },
	hoverCol{ pHoverCol },
	text{ pMessage, pTextColour, pFont },
	outlineWidth{ pOutlineWidth }
{
	loadOutlineRect();
}

CButton::CButton(float x, float y, float w, float h, SDL_Color& pMainCol, SDL_Color& pHoverCol, SDL_Color& pOutlineCol, float pOutlineWidth, CText& pText) :
	buttonRect{ x, y, w, h, pMainCol },
	mainCol{ pMainCol },
	outlineCol{ pOutlineCol },
	hoverCol{ pHoverCol },
	text{ pText.getMessage(), pText.getCol(), pText.getFont() },
	outlineWidth{ pOutlineWidth }
{
	loadOutlineRect();
}

void CButton::setPosition(float x, float y, float w, float h) {
	buttonRect.setPosition(x, y, w, h);
	loadOutlineRect();
}

void CButton::setRect(CRect& pRectangle) {
	buttonRect = pRectangle;
	loadOutlineRect();
}

void CButton::setCentre(float x, float y) {
	buttonRect.setCentre(x, y);
	loadOutlineRect();
}

void CButton::setMainCol(SDL_Color& pMainCol) {
	mainCol = pMainCol;
}

void CButton::setHoverCol(SDL_Color& pHoverCol){
	hoverCol = pHoverCol;
}

void CButton::setOutlineCol(SDL_Color& pOutlineCol){
	outlineCol = pOutlineCol;
	loadOutlineRect();
}

void CButton::setOutlineWidth(float pOutlineWidth){
	outlineWidth = pOutlineWidth;
	loadOutlineRect();
}

void CButton::setText(CText& pText){
	text.setMessage(pText.getMessage());
}

void CButton::setMessage(std::string pMessage){
	text.setMessage(pMessage);
}

void CButton::setTextCol(SDL_Color& pCol){
	text.setCol(pCol);
}

void CButton::setFont(TTF_Font* pFont){
	text.setFont(pFont);
}

void CButton::loadOutlineRect() {
	//defines rectangle for outline
	SDL_FRect buttonDim{ buttonRect.getRect() };
	outlineRect.setPosition(buttonDim.x - (outlineWidth / 2), (buttonDim.y - (outlineWidth / 2)), (buttonDim.w + outlineWidth), (buttonDim.h + outlineWidth));
	outlineRect.setColour(outlineCol);
}

bool CButton::isClick() {
	bool mouseIn = false;
	float x = -1.f, y = -1.f;
	SDL_GetMouseState(&x, &y);
	if (buttonRect.inRect(x, y)) {
		mouseIn = true;
	}
	return mouseIn;
}

void CButton::render(SDL_Renderer* renderer) {
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