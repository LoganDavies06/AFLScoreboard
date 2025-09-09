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

    int getTimePassed();
    int getTimeLeft();
    float getQuarter();
    bool isPaused();
    timeMode getTimeMode();

    void update(SDL_Renderer* renderer);
    void nextQuarter(SDL_Renderer* renderer, Font font);
    void pause(SDL_Renderer* renderer, Font font);

    void renderTime(SDL_Renderer* renderer, screenDimensions dim, screenDimensions size);
    void setTimeMode(timeMode mode);

private:
    int timePassed;
    int timeLeft;
    Uint64 startTicksDown;
    Uint64 startTicksUp;
    int pausedTicks;
    timeMode currentTimeMode;

    //if this is an integer, it's that quarter, other wise a x.5 means between two quarters
    float quarter;
    int timeInQtr;

    std::pair<int, int> lastTickUp;
    std::pair<int, int> lastTickDown;

    bool paused;

    CText timeTextUp;
    CText timeTextDown;
    CText qtrTextLine1;
    CText qtrTextLine2;

    std::pair<int, int> getTime(int ticks);
    std::string timeToString(std::pair<int, int> time);
    bool inQtr();
};