#pragma once
#include<SDL3/SDL.h>
#include"Structs.h"

void scoreboard(SDL_Renderer* renderer, struct screenDimensions dim, struct Font apotek, Score homeScore, Score awayScore, struct Time time);