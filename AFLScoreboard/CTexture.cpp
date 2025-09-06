#include"CTexture.hpp"

/*
 * Image class adapted from Lazy Foo Productions
 * https://lazyfoo.net/tutorials/SDL3/index.php#Textures%20and%20Extension%20Libraries
*/

CTexture::CTexture():
    //Initialize texture variables
    mTexture{ nullptr },
    mWidth{ 0 },
    mHeight{ 0 },
    x{0},
    y{0}
{}

CTexture::CTexture(float pX, float pY) :
    //Initialize texture variables
    mTexture{ nullptr },
    mWidth{ 0 },
    mHeight{ 0 },
    x{ pX },
    y{ pY }
{
}

CTexture::CTexture(const CTexture& pTexture) :
    mTexture{ pTexture.mTexture },
    mHeight{ pTexture.mHeight },
    mWidth{ pTexture.mWidth },
    x{ pTexture.x },
    y{ pTexture.y }
{}

CTexture::~CTexture()
{
    //Clean up texture
    destroy();
}

//load without colour keying
bool CTexture::loadFromFile( std::string path, SDL_Renderer* gRenderer )
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
bool CTexture::loadFromFile( std::string path, SDL_Renderer* gRenderer, int keyR, int keyG, int keyB )
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

void CTexture::destroy()
{
    //Clean up texture
    SDL_DestroyTexture( mTexture );
    mTexture = nullptr;
    mWidth = 0;
    mHeight = 0;
}

void CTexture::setPosition(float pX, float pY) {
    x = pX;
    y = pY;
}

void CTexture::setCentre(float pX, float pY) {
    x = pX - mWidth/2.f;
    y = pY - mHeight/2.f;
}

void CTexture::setColor( Uint8 r, Uint8 g, Uint8 b){
    SDL_SetTextureColorMod( mTexture, r, g, b );
}

void CTexture::setAlpha( Uint8 alpha ){
    SDL_SetTextureAlphaMod( mTexture, alpha );
}

void CTexture::setBlending( SDL_BlendMode blendMode ){
    SDL_SetTextureBlendMode( mTexture, blendMode );
}

void CTexture::render( SDL_Renderer* gRenderer, SDL_FRect* clip, float width, float height, double degrees, SDL_FPoint* center, SDL_FlipMode flipMode )
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

SDL_Texture* CTexture::getTexture() {
    return mTexture;
}

int CTexture::getWidth()
{
    return mWidth;
}

int CTexture::getHeight()
{
    return mHeight;
}

bool CTexture::isLoaded()
{
    return mTexture != nullptr;
}

float CTexture::getX() {
    return x;
}
float CTexture::getY() {
    return y;
}
