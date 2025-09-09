#pragma once
#include<SDL3/SDL.h>
#include"Structs.h"
#include"CTime.h"

void scoreboard(SDL_Renderer* renderer, struct screenDimensions dim, struct screenDimensions size, struct Font apotek, struct Team* home, struct Team* away, CTime* time, bool clash);