#include<SDL3/SDL.h>
#include<SDL3_image/SDL_image.h>
#include<SDL3_ttf/SDL_ttf.h>
#include<SDL3/SDL_main.h>
#include<string>
#include<sstream>
#include<iostream>

#include"LTexture.hpp"
#include"LText.hpp"
#include"Structs.h"
#include"LRect.hpp"
#include"LButton.hpp"

struct Window {
    SDL_Window* window{ nullptr };
    SDL_Renderer* renderer{ nullptr };
};

//sets up the window and renderer
bool init(struct screenDimensions dim, struct Window* wn) {
    bool success{ true };

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL initilaisation was unsuccesful. Error: %s\n", SDL_GetError());
        success = false;
    }
    else {
        //create window
        if (!SDL_CreateWindowAndRenderer("Scoreboard", dim.width, dim.height, 0, &wn->window, &wn->renderer)) {
            SDL_Log("Unable to create window. Error: %s\n", SDL_GetError());
            success = false;
        }
        else {
            if (!TTF_Init()) {
                SDL_Log("SDL font rendering failed to load. Error: %s\n", SDL_GetError());
                success = false;
            }
        }
    }

    return success;
}

int main(int argc, char* args[]) {
    int exitCode{ 0 };

    constexpr screenDimensions screenDim{ 640, 480 };
    Window window;

    //initialize window
    if (!init(screenDim, &window)) {
        SDL_Log("Unable to initialize program");
        exitCode = 1;
    }

    if (exitCode == 0) {
        bool quit{ false };

        //events
        SDL_Event e;
        SDL_zero(e);

        //main loop
        while (!quit) {
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_EVENT_QUIT) {
                    quit = true;
                }
            }

            //set window background colour
            SDL_SetRenderDrawColor(window.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(window.renderer);

            //refresh screen
            SDL_RenderPresent(window.renderer);
        }
    }

    return exitCode;
}