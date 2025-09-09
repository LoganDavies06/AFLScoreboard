#pragma once
#include<SDL3/SDL.h>
#include<SDL3_ttf/SDL_ttf.h>

#include"CText.hpp"
#include"Structs.h"


class CTime {
public:
    CTime();
    CTime(SDL_Renderer* renderer, struct Font font);

    enum class timeMode {
        UP,
        DOWN,
        BOTH
    };

    Uint64 getTimePassed();
    Uint64 getTimeLeft();
    float getQuarter();
    bool isPaused();
    timeMode getTimeMode();

    bool inQtr();

    void update(SDL_Renderer* renderer);
    void nextQuarter(SDL_Renderer* renderer, Font font);
    void pause(SDL_Renderer* renderer, Font font);

    void renderTime(SDL_Renderer* renderer, screenDimensions dim, screenDimensions size);
    void setTimeMode(timeMode mode);

private:
    Uint64 timePassed;
    Uint64 timeLeft;
    Uint64 startTicksDown;
    Uint64 startTicksUp;
    Uint64 pausedTicks;
    timeMode currentTimeMode;

    //if this is an integer, it's that quarter, other wise a x.5 means between two quarters
    float quarter;
    int timeInQtr;

    std::pair<int, int> lastTickUp;
    std::pair<int, int> lastTickDown;

    bool paused;
    bool startCounting;

    CText timeTextUp;
    CText timeTextDown;
    CText qtrTextLine1;
    CText qtrTextLine2;

    std::pair<int, int> getTime(Uint64 ticks, bool doFloor = true);
    std::string timeToString(std::pair<int, int> time);
};