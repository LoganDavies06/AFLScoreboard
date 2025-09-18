#pragma once

/*
 * Image class adapted from Lazy Foo Productions
 * https://lazyfoo.net/tutorials/SDL3/index.php#Textures%20and%20Extension%20Libraries
*/

#include<SDL3/SDL.h>
#include<SDL3_image/SDL_image.h>
#include<string>

class CTexture{
public:
    static constexpr float kDefaultSize = -1.f;

    //Initializes texture variables
    CTexture();
    CTexture(float pX, float pY);

    //Cleans up texture variables
    ~CTexture();

    //Remove copy constructor
    CTexture( const CTexture& );

    //Remove copy assignment
    CTexture& operator=( const CTexture& ) = delete;

    //Remove move constructor
    CTexture( CTexture&& ) = delete;

    //Remove move assignment
    CTexture& operator=( CTexture&& ) = delete;

    //Cleans up texture
    void destroy();

    void setPosition(float pX, float pY);
    void setCentre(float pX, float pY);

    //Draws texture
    void render( SDL_Renderer* gRenderer, SDL_FRect* clip = nullptr, float width = kDefaultSize, float height = kDefaultSize, double degrees = 0.0, SDL_FPoint* center = nullptr, SDL_FlipMode flipMode = SDL_FLIP_NONE );

    //Gets texture attributes
    SDL_Texture* getTexture();
    int getWidth();
    int getHeight();
    bool isLoaded();
    float getX();
    float getY();

protected:
    //Contains texture data
    SDL_Texture* mTexture;

    float x, y;

    //Texture dimensions
    int mWidth;
    int mHeight;
};

class CImage : public CTexture {
public:
    //Loads texture from disk
    bool loadFromFile(std::string path, SDL_Renderer* gRenderer);
    bool loadFromFile(std::string path, SDL_Renderer* gRenderer, int maskR, int maskG, int maskB);

    //Sets color modulation
    void setColor(Uint8 r, Uint8 g, Uint8 b);

    //Sets opacity
    void setAlpha(Uint8 alpha);

    //Sets blend mode
    void setBlending(SDL_BlendMode blendMode);
};