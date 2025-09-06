#include<SDL3/SDL.h>
#include<SDL3_image/SDL_image.h>
#include<SDL3_ttf/SDL_ttf.h>
#include<SDL3/SDL_main.h>
#include<string>
#include<sstream>
#include<iostream>
#include<fstream>
#include<cmath>
#include<map>
#include<vector>

#include"CTexture.hpp"
#include"CText.hpp"
#include"Structs.h"
#include"CRect.hpp"
#include"CButton.hpp"
#include"Menus.h"

//structure containing window and renderer
struct Window {
    SDL_Window* window{ nullptr };
    SDL_Renderer* renderer{ nullptr };
};

//function definitions
bool init(struct screenDimensions dim, struct Window* wn);
void close(struct Window* wn, struct Font* font);
void myLog(void* userdata, int category, SDL_LogPriority priority, const char* message);
float getFrameRate(SDL_Window* window);
std::map<int, TTF_Font*> loadFont(std::string fontPath, int* exitCode);

//sets up the window and renderer
bool init(struct screenDimensions dim, struct Window* wn) {
    bool success{ true };

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL initilaisation was unsuccesful. Error: %s\n", SDL_GetError());
        success = false;
    }
    else {
        if (!SDL_CreateWindowAndRenderer("Scoreboard", dim.w, dim.h, SDL_WINDOW_RESIZABLE, &wn->window, &wn->renderer)) {
            SDL_Log("Unable to create window. Error: %s\n", SDL_GetError());
            success = false;
        }
        else {
            SDL_SetWindowMinimumSize(wn->window, dim.w, dim.h);

            if (!SDL_SetRenderVSync(wn->renderer, 1)) {
                SDL_Log("Could not enable VSync. Error: %s\n", SDL_GetError());
                success = false;
            }

            if (!TTF_Init()) {
                SDL_Log("SDL font rendering failed to load. Error: %s\n", SDL_GetError());
                success = false;
            }
        }
    }

    return success;
}

//cleans up memory after program finishes
void close(struct Window* wn, struct Font* fontStruct) {
    //cleans up fonts
    for (const auto& [size, font] : fontStruct->reg) {
        TTF_CloseFont(font);
    }
    fontStruct->reg.clear();

    for (const auto& [size, font] : fontStruct->bold) {
        TTF_CloseFont(font);
    }
    fontStruct->bold.clear();

    for (const auto& [size, font] : fontStruct->narrow) {
        TTF_CloseFont(font);
    }
    fontStruct->narrow.clear();

    for (const auto& [size, font] : fontStruct->comp) {
        TTF_CloseFont(font);
    }
    fontStruct->comp.clear();
    
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

//gets the frame rate of the monitor the window is on
float getFrameRate(SDL_Window* window) {
    float refreshRate;
    Uint32 displayID = SDL_GetDisplayForWindow(window);
    const SDL_DisplayMode* dm = SDL_GetCurrentDisplayMode(displayID);
    if (dm) {
        refreshRate = dm->refresh_rate;
    }
    else {
        refreshRate = 0;
        SDL_Log("Error in retrieving display state: Error %s\n", SDL_GetError());
    }

    return refreshRate;
}

std::map<int, TTF_Font*> loadFont(std::string fontPath, int* exitCode) {
    std::map<int, TTF_Font*> fontMap;
    int sizes[] { 8, 10, 12, 20, 24, 30, 34, 36, 48, 50, 52, 54, 66, 68, 80, 120, 130, 140, 150, 160 };

    for (int i: sizes) {
        if (fontMap[i] = TTF_OpenFont(fontPath.c_str(), i * 2); fontMap.at(i) == nullptr) {
            SDL_Log("Could not load font %s. Error: %s\n", fontPath.c_str(), SDL_GetError());
            *exitCode = 2;
        }
    }

    return fontMap;
}

int main(int argc, char* args[]) {
    int exitCode{ 0 };

    //sets up screen dimensions
    screenDimensions screenDim{ 1240, 290 };
    constexpr screenDimensions scoreboardSize{ 1240, 290 };

    //make it so that logs are outputted to log.txt
    std::ofstream logFile("log.txt", std::ios::out);
    SDL_SetLogOutputFunction(myLog, &logFile);

    //initialize window
    Window window;
    if (!init(screenDim, &window)) {
        SDL_Log("Unable to initialize program");
        exitCode = 1;
    }

    //makes fonts
    struct Font apotek;
    apotek.reg = loadFont("media/fonts/Apotek_Wide.otf", &exitCode);
    apotek.bold = loadFont("media/fonts/Apotek_Wide_Black.otf", &exitCode);
    apotek.narrow = loadFont("media/fonts/Apotek_Narrow.otf", &exitCode);
    apotek.comp = loadFont("media/fonts/Apotek_Comp.otf", &exitCode);

    if (exitCode == 0) {
        bool quit{ false };

        //initialise events
        SDL_Event e;
        SDL_zero(e);

        //gets background colour
        SDL_Color bgCol = getCol(colName::DARK_GREY);

        //sets up teams
        struct Team home;
        struct Team away;

        //sets up time
        struct Time time;

        //gets frame rate
        float FPS = getFrameRate(window.window);

        //main loop
        while (!quit) {

            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_EVENT_QUIT) {
                    quit = true;
                }
                else if (e.type == SDL_EVENT_WINDOW_RESIZED) {
                    //changes window dimensions if window is resized
                    SDL_GetWindowSize(window.window, &screenDim.w, &screenDim.h);
                }
                else if (e.type = SDL_EVENT_WINDOW_MOVED) {
                    //gets the framerate of window if it is moved (in case it's move to another monitor with a different frame rate)
                    FPS = getFrameRate(window.window);
                }
            }
            //set window background colour
            SDL_SetRenderDrawColor(window.renderer, bgCol.r, bgCol.g, bgCol.b, bgCol.a);
            SDL_RenderClear(window.renderer);

            //renders active menu
            scoreboard(window.renderer, screenDim, scoreboardSize, apotek, home, away, time);

            //refresh screen
            SDL_RenderPresent(window.renderer);
        }
    }

    close(&window, &apotek);
    return exitCode;
}