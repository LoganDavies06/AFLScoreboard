#include"LTexture.hpp"

/*
 * Image class adapted from Lazy Foo Productions
 * https://lazyfoo.net/tutorials/SDL3/index.php#Textures%20and%20Extension%20Libraries
*/

LTexture::LTexture():
    //Initialize texture variables
    mTexture{ nullptr },
    mWidth{ 0 },
    mHeight{ 0 },
    x{0},
    y{0}
{}

LTexture::LTexture(float pX, float pY) :
    //Initialize texture variables
    mTexture{ nullptr },
    mWidth{ 0 },
    mHeight{ 0 },
    x{ pX },
    y{ pY }
{
}

LTexture::LTexture(const LTexture& pTexture) :
    mTexture{ pTexture.mTexture },
    mHeight{ pTexture.mHeight },
    mWidth{ pTexture.mWidth },
    x{ pTexture.x },
    y{ pTexture.y }
{}

LTexture::~LTexture()
{
    //Clean up texture
    destroy();
}

//load without colour keying
bool LTexture::loadFromFile( std::string path, SDL_Renderer* gRenderer )
{
    //Clean up texture if it already exists
    destroy();

    //Load surface
    if( SDL_Surface* loadedSurface = IMG_Load( path.c_str() ); loadedSurface == nullptr )
    {
        SDL_Log( "Unable to load image %s! SDL_image error: %s\n", path.c_str(), SDL_GetError() );
    }
    else
    {
        //Create texture from surface
        if( mTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface ); mTexture == nullptr )
        {
            SDL_Log( "Unable to create texture from loaded pixels! SDL error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        //Clean up loaded surface
        SDL_DestroySurface( loadedSurface );
    }

    //Return success if texture loaded
    return mTexture != nullptr;
}
//load with colour keying
bool LTexture::loadFromFile( std::string path, SDL_Renderer* gRenderer, int keyR, int keyG, int keyB )
{
    //Clean up texture if it already exists
    destroy();

    //Load surface
    if( SDL_Surface* loadedSurface = IMG_Load( path.c_str() ); loadedSurface == nullptr )
    {
        SDL_Log( "Unable to load image %s. SDL_image error: %s\n", path.c_str(), SDL_GetError() );
    }
    else
    {
        if ( !SDL_SetSurfaceColorKey( loadedSurface, true, SDL_MapSurfaceRGB(loadedSurface, keyR, keyG, keyB ) ) )
        {
            SDL_Log( "Unable to key image %s. Error: %s", path.c_str(), SDL_GetError() );
        } else
        {    
            //Create texture from surface
            if( mTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface ); mTexture == nullptr )
            {
                SDL_Log( "Unable to create texture from loaded pixels! SDL error: %s\n", SDL_GetError() );
            }
            else
            {
                //Get image dimensions
                mWidth = loadedSurface->w;
                mHeight = loadedSurface->h;
            }

            //Clean up loaded surface
            SDL_DestroySurface( loadedSurface );
        }
    }

    //Return success if texture loaded
    return mTexture != nullptr;
}

void LTexture::destroy()
{
    //Clean up texture
    SDL_DestroyTexture( mTexture );
    mTexture = nullptr;
    mWidth = 0;
    mHeight = 0;
}

void LTexture::setPosition(float pX, float pY) {
    x = pX;
    y = pY;
}

void LTexture::setCentre(float pX, float pY) {
    x = pX - (float) mWidth/2;
    y = pY - (float) mHeight/2;
}

void LTexture::setColor( Uint8 r, Uint8 g, Uint8 b){
    SDL_SetTextureColorMod( mTexture, r, g, b );
}

void LTexture::setAlpha( Uint8 alpha ){
    SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::setBlending( SDL_BlendMode blendMode ){
    SDL_SetTextureBlendMode( mTexture, blendMode );
}

void LTexture::render( SDL_Renderer* gRenderer, SDL_FRect* clip, float width, float height, double degrees, SDL_FPoint* center, SDL_FlipMode flipMode )
{
    //Set texture position
    SDL_FRect dstRect{ x, y, static_cast<float>( mWidth ), static_cast<float>( mHeight ) };

    if (clip != nullptr){
        dstRect.w = clip->w;
        dstRect.h = clip->h;
    }

    if (width > 0){
        dstRect.w = width;
    }
    if (height > 0){
        dstRect.h = height;
    }

    //Render texture
    SDL_RenderTextureRotated( gRenderer, mTexture, clip, &dstRect, degrees, center, flipMode );
}

SDL_Texture* LTexture::getTexture() {
    return mTexture;
}

int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}

bool LTexture::isLoaded()
{
    return mTexture != nullptr;
}

float LTexture::getX() {
    return x;
}
float LTexture::getY() {
    return y;
}
