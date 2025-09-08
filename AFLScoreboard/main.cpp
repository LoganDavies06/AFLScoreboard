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
#include<algorithm>

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
void close(struct Window* wn, struct Font* font, struct Team* home, struct Team* away);
void myLog(void* userdata, int category, SDL_LogPriority priority, const char* message);
float getFrameRate(SDL_Window* window);
std::map<int, TTF_Font*> loadFont(std::string fontPath, int* exitCode);
std::map<std::string, struct TeamData> loadTeamFile();
void getTeamData(std::map<std::string, struct TeamData> teamsData, std::string teamAbr, struct Team* team, SDL_Renderer* renderer, Font font);
bool clashTest(struct Team* team1, struct Team* team2);
float colourComparison(SDL_Color col1, SDL_Color col2);

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
void close(struct Window* wn, struct Font* fontStruct, struct Team* home, struct Team* away) {
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

    //destroys textures associated with home team
    home->texture.destroy();
    home->score.destroyText();

    //destroys textures associated with away team
    away->texture.destroy();
    away->score.destroyText();
    
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

//loads the fonts
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

//reads team data from the file
std::map<std::string, struct TeamData> loadTeamFile() {
    std::map<std::string, struct TeamData> dataMap;
    std::ifstream file("assets/data/teams.csv");
    std::string num1, num2, num3;

    if (!file.is_open()) {
        SDL_Log("Unable to open teams file");
    }
    else {
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            struct TeamData currentTeam;

            getline(ss, currentTeam.abr, ','); //gets team abbreviation
            getline(ss, currentTeam.name, ','); //gets team name

            //gets colours
            for (int i = 0; i < 4; i++) {
                getline(ss, num1, ',');
                getline(ss, num2, ',');
                getline(ss, num3, ',');

                //if colour is invalid
                if (std::stoi(num1) > 255 || std::stoi(num2) > 255 || std::stoi(num3) > 255)
                {
                    SDL_Log("Invalid color: %s colour %d\n", currentTeam.abr.c_str(), i);
                }

                currentTeam.cols[i] = SDL_Color{ (Uint8) std::stoi(num1), (Uint8) std::stoi(num2), (Uint8) std::stoi(num3), 255 };
            }

            getline(ss, currentTeam.moniker, ','); //gets team moniker
            ss.clear();

            //adds team to vector
            dataMap[currentTeam.abr] = currentTeam;
        }
    }

    return dataMap;
}

void getTeamData(std::map<std::string, struct TeamData> teamsData, std::string teamAbr, struct Team* team, SDL_Renderer* renderer, Font font) {
    bool teamFound = false;
    int index = 0;
    for (const auto& pair : teamsData) {
        if (pair.first == teamAbr) {
            teamFound = true;
        }
    }

    if (!teamFound) {
        SDL_Log("No team %s found", teamAbr.c_str());
    }
    else {
        //set name
        team->abr = teamAbr;
        team->name = teamsData.at(teamAbr).name;
        team->moniker = teamsData.at(teamAbr).moniker;

        //assigns colours
        for (int i = 0; i < 4; i++) {
            team->cols[i] = teamsData.at(teamAbr).cols[i];
        }

        //set the text for scoreboard
        team->nameText.setMessage(teamAbr);
        team->nameText.setCol(getCol(colName::WHITE));
        team->nameText.setFont(font.comp.at(68));
        team->nameText.RenderText(renderer);

        //set the score texts
        team->score.setUpText(font, renderer);

        //set the texture
        std::string filePath = "assets/images/teamCircles/" + teamAbr + ".png";
        team->texture.loadFromFile(filePath, renderer);
    }
}

bool clashTest(struct Team* team1, struct Team* team2) {
    bool clash = false;

    //gets the number that compares the colours
    float comparisonNum = colourComparison(team1->cols[0], team2->cols[0]);

    //sum of colour values (brightness measure)
    int col1Sum = team1->cols[0].r + team1->cols[0].g + team1->cols[0].b;
    int col2Sum = team2->cols[0].r + team2->cols[0].g + team2->cols[0].b;

    //if comparison num is less than 100 or if comparison num is less than 250 for two dark colours
    if (comparisonNum < 100 || (col1Sum < 200 && col2Sum < 200 && comparisonNum < 250)) {
        clash = true;
    }

    return clash;
}

float colourComparison(SDL_Color col1, SDL_Color col2) {
    float r1, g1, b1, r2, b2, g2;

    //gets the how bright as a % the brighest rgb value is for each colour
    float const1 = 255.f / std::max({ (int)col1.r, (int)col1.g, (int)col1.b, 1 });
    float const2 = 255.f / std::max({ (int)col2.r, (int)col2.g, (int)col2.b, 1 });

    //set colours to max brightness
    r1 = col1.r * const1;
    g1 = col1.g * const1;
    b1 = col1.b * const1;

    r2 = col2.r * const2;
    g2 = col2.g * const2;
    b2 = col2.b * const2;

    //return the sum of the root of the squares of each colour value for the two colours
    //sqrt(|r2 - r1|^2) + sqrt(|g2 - g1|^2) + sqrt(|b2 - b1|^2)
    return std::sqrt(std::pow(std::abs(r2 - r1), 2)) + std::sqrt(std::pow(std::abs(g2 - g1), 2)) + std::sqrt(std::pow(std::abs(b2 - b1), 2));
}

int main(int argc, char* args[]) {
    int exitCode{ 0 };

    //sets up screen dimensions
    screenDimensions screenDim{ 1240, 290 };
    constexpr screenDimensions scoreboardSize{ 1240, 290 };

    //make it so that logs are outputted to log.txt
    std::ofstream logFile("log.txt", std::ios::out);
    SDL_SetLogOutputFunction(myLog, &logFile);

    //team structs
    struct Team home;
    struct Team away;

    //initialize window
    Window window;
    if (!init(screenDim, &window)) {
        SDL_Log("Unable to initialize program");
        exitCode = 1;
    }

    //makes fonts
    struct Font apotek;
    apotek.reg = loadFont("assets/fonts/Apotek_Wide.otf", &exitCode);
    apotek.bold = loadFont("assets/fonts/Apotek_Wide_Black.otf", &exitCode);
    apotek.narrow = loadFont("assets/fonts/Apotek_Narrow.otf", &exitCode);
    apotek.comp = loadFont("assets/fonts/Apotek_Comp.otf", &exitCode);

    if (exitCode == 0) {
        bool quit{ false };

        std::map<std::string, struct TeamData> teamsData = loadTeamFile();

        //initialise events
        SDL_Event e;
        SDL_zero(e);

        //gets background colour
        SDL_Color bgCol = getCol(colName::DARK_GREY);

        //sets up teams
        getTeamData(teamsData, "KLA", &home, window.renderer, apotek);
        getTeamData(teamsData, "XAN", &away, window.renderer, apotek);

        bool clash = clashTest(&home, &away);

        if (clash) {
            std::string filePath = "assets/images/teamCircles/" + away.abr + " Clash.png";
            away.texture.loadFromFile(filePath, window.renderer);
        }

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
                else if (e.type == SDL_EVENT_WINDOW_MOVED) {
                    //gets the framerate of window if it is moved (in case it's move to another monitor with a different frame rate)
                    FPS = getFrameRate(window.window);
                }
            }
            //set window background colour
            SDL_SetRenderDrawColor(window.renderer, bgCol.r, bgCol.g, bgCol.b, bgCol.a);
            SDL_RenderClear(window.renderer);

            //renders active menu
            scoreboard(window.renderer, screenDim, scoreboardSize, apotek, &home, &away, time, clash);

            //refresh screen
            SDL_RenderPresent(window.renderer);
        }
    }

    close(&window, &apotek, &home, &away);
    return exitCode;
}