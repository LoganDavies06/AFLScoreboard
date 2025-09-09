#include"CTime.h"
#include<cmath>
#include<iostream>

CTime::CTime() :
	timePassed{ 0 },
	timeLeft{ 1200000 },
	startTicksDown{ SDL_GetTicks() },
	startTicksUp{ SDL_GetTicks() },
	pausedTicks{ 0 },
	quarter{ 0.5 },
	timeInQtr{ 1200 },
	lastTickUp{ 0, 0 },
	lastTickDown{ 20, 0 },
	paused{ true },
	timeTextDown{ },
	timeTextUp{ },
	qtrTextLine1{ },
	qtrTextLine2{ },
	currentTimeMode{ timeMode::BOTH }
{}

CTime::CTime(SDL_Renderer* renderer, struct Font font) :
	timePassed{ 0 },
	timeLeft{ 1200 },
	startTicksDown{ SDL_GetTicks() },
	startTicksUp{ SDL_GetTicks() },
	pausedTicks{ 0 },
	quarter{ 0.5 },
	timeInQtr{ 1200 },
	lastTickUp{ 0, 0 },
	lastTickDown{ 20, 0 },
	paused{ true },
	currentTimeMode{ timeMode::BOTH },
	timeTextUp{ "0:00", getCol(colName::GREY), font.reg.at(20), renderer },
	timeTextDown{ "20:00", getCol(colName::WHITE), font.reg.at(50), renderer },
	qtrTextLine1{ "STARTING", getCol(colName::WHITE), font.reg.at(30), renderer },
	qtrTextLine2{ "SOON", getCol(colName::WHITE), font.reg.at(30), renderer }
{}

int CTime::getTimePassed() { return timePassed; }
int CTime::getTimeLeft() { return timeLeft; }
float CTime::getQuarter() { return quarter ;}
bool CTime::isPaused() { return paused; }
CTime::timeMode CTime::getTimeMode() { return currentTimeMode; }

std::pair<int, int> CTime::getTime(int ticks) {
	int totalTime = ticks / 1000;
	return { totalTime / 60, totalTime % 60 };
}

std::string CTime::timeToString(std::pair<int, int> time) {
	std::string outString;

	if (time.second < 10) {
		outString = std::to_string(time.first) + ":0" + std::to_string(time.second);
	}
	else {
		outString = std::to_string(time.first) + ":" + std::to_string(time.second);
	}

	return outString;
}

void CTime::update(SDL_Renderer* renderer) {
	//only works if game is active
	if (inQtr())
	{
		timePassed = SDL_GetTicks() - startTicksUp;

		//updates texture for count up
		std::pair<int, int> timePassedPair = getTime(timePassed);
		if (timePassedPair.second != lastTickUp.second) {
			std::string timePassedStr = timeToString(timePassedPair);
			timeTextUp.setMessage(timePassedStr, renderer);
		}
		lastTickUp = timePassedPair;

		if (currentTimeMode != timeMode::UP) {
			if (paused) {
				timeLeft = (timeInQtr * 1000) - pausedTicks;
			}
			else {
				timeLeft = (timeInQtr * 1000) - (SDL_GetTicks() - startTicksDown);
			}

			if (timeLeft <= 0) {
				pause();
			}

			std::pair<int, int> timeLeftPair = getTime(timeLeft);
			if (timeLeftPair.second != lastTickDown.second) {
				std::string timeLeftStr = timeToString(timeLeftPair);
				timeTextDown.setMessage(timeLeftStr, renderer);
			}
			lastTickUp = timePassedPair;
		}
	}
}

void CTime::nextQuarter(SDL_Renderer* renderer, Font font) {
	quarter += 0.5;

	if (inQtr()) {
		startTicksDown = SDL_GetTicks();
		paused = true;
		qtrTextLine1.setFont(font.reg.at(54));
		qtrTextLine1.setMessage("Q" + std::to_string((int)quarter), renderer);
	}
	else {
		paused = true;

		//sets the text for the quarter
		if (quarter == 0.5) {
			qtrTextLine1.setFont(font.reg.at(30));
			qtrTextLine2.setFont(font.reg.at(30));

			qtrTextLine1.setMessage("STARTING", renderer);
			qtrTextLine2.setMessage("SOON" + std::to_string((int)quarter), renderer);
		}
		else {
			qtrTextLine1.setFont(font.reg.at(36));
			qtrTextLine2.setFont(font.reg.at(36));

			if (quarter == 1.5) {
				qtrTextLine1.setMessage("QUARTER", renderer);
				qtrTextLine2.setMessage("TIME" + std::to_string((int)quarter), renderer);
			}
			else if (quarter == 2.5) {
				qtrTextLine1.setMessage("HALF", renderer);
				qtrTextLine2.setMessage("TIME" + std::to_string((int)quarter), renderer);
			}
			else if (quarter == 3.5) {
				qtrTextLine1.setMessage("3 QUARTER", renderer);
				qtrTextLine2.setMessage("TIME" + std::to_string((int)quarter), renderer);
			}
			else if (quarter == 4.5) {
				qtrTextLine1.setMessage("FULL", renderer);
				qtrTextLine2.setMessage("TIME" + std::to_string((int)quarter), renderer);
			}
		}
	}
}

//called when the pause button is hit
void CTime::pause(SDL_Renderer* renderer, Font font) { 
	if (inQtr()) {
		//if time has run out or there is no count down
		if (timeLeft <= 0 || currentTimeMode == timeMode::UP) {
			nextQuarter(renderer, font);
		}

		//if it is paused
		else if (paused) {
			paused = false;
			startTicksDown = SDL_GetTicks() - pausedTicks;
		}

		//if it isn't paused
		else {
			paused = true;
			pausedTicks = SDL_GetTicks() - startTicksDown;
		}
	}
	else {
		nextQuarter();
	}
}

bool CTime::inQtr() {
	bool isInQtr = false;

	if (std::fmod(quarter, 1) == 0) {
		isInQtr = true;
	}

	return isInQtr;
}

void CTime::renderTime(SDL_Renderer* renderer, screenDimensions dim, screenDimensions size) {

	if (inQtr()) {
		switch (currentTimeMode)
		{
		case timeMode::UP:
			timeTextUp.setCentre(dim.w / 2.f + 485, dim.h / 2.f - size.h / 4.f);
			timeTextUp.render(renderer);
			break;
		case timeMode::BOTH:
			timeTextUp.setCentre(dim.w / 2.f + 485, dim.h / 2.f - 20);
			timeTextUp.render(renderer);
			[[fallthrough]];
		case timeMode::DOWN:
			timeTextDown.setCentre(dim.w / 2.f + 485, dim.h / 2.f - size.h / 4.f);
			timeTextDown.render(renderer);
			break;
		}

		qtrTextLine1.setCentre(dim.w / 2.f + 485, dim.h / 2.f + size.h / 4.f);
	}
	else {
		qtrTextLine2.render(renderer);
	}

	qtrTextLine1.render(renderer);
}

void CTime::setTimeMode(timeMode mode) {
	currentTimeMode = mode;
}