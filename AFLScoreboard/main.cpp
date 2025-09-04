#include<SDL3/SDL.h>
#include<SDL3_image/SDL_image.h>
#include<SDL3_ttf/SDL_ttf.h>
#include<SDL3/SDL_main.h>
#include<string>
#include<sstream>
#include<iostream>
#include<fstream>

#include"CTexture.hpp"
#include"CText.hpp"
#include"Structs.h"
#include"CRect.hpp"
#include"CButton.hpp"

//structure containing window and renderer
struct Window {
    SDL_Window* window{ nullptr };
    SDL_Renderer* renderer{ nullptr };
};

bool init(struct screenDimensions dim, struct Window* wn);
void close(struct Window* wn);
void myLog(void* userdata, int category, SDL_LogPriority priority, const char* message);

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

//cleans up memory after program finishes
void close(struct Window* wn) {

    //cleans up window and renderer
    SDL_DestroyRenderer(wn->renderer);
    SDL_DestroyWindow(wn->window);
    wn->renderer = nullptr;
    wn->window = nullptr;

    SDL_Quit();
}

//writes calls of SDL_Log() to a file instead of to the console
void myLog(void* userdata, int category, SDL_LogPriority priority, const char* message) {
    auto* logFile = static_cast<std::ofstream*>(userdata);
    if (logFile && *logFile) {
        *logFile << message << '\n';
        logFile->flush();
    }
}

int main(int argc, char* args[]) {
    int exitCode{ 0 };

    constexpr screenDimensions screenDim{ 1240, 290 };
    Window window;

    //make it so that logs are outputted to log.txt
    std::ofstream logFile("log.txt", std::ios::out);
    SDL_SetLogOutputFunction(myLog, &logFile);

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

        SDL_Color bgCol = getCol(colName::DARK_GREY);

        //main loop
        while (!quit) {
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_EVENT_QUIT) {
                    quit = true;
                }
            }

            //set window background colour
            SDL_SetRenderDrawColor(window.renderer, bgCol.r, bgCol.g, bgCol.b, bgCol.a);
            SDL_RenderClear(window.renderer);

            //refresh screen
            SDL_RenderPresent(window.renderer);
        }
    }

    close(&window);
    return exitCode;
}