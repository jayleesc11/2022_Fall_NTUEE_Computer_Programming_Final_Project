#include "texture.h"

#include <stdio.h>

#include <string>
using std::string;

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>


Texture::Texture()
{
	//Initialize
	texture_ = NULL;
	width_ = 0;
	height_ = 0;
}

Texture::~Texture()
{
	//Deallocate
	Free();
}

bool Texture::LoadFromFile( string path )
{
	//Get rid of preexisting texture
	Free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( g_renderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			width_ = loadedSurface->w;
			height_ = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	texture_ = newTexture;
	return texture_ != NULL;
}

#if defined(SDL_TTF_MAJOR_VERSION)
bool Texture::LoadFromRenderedText( TTF_Font* g_font, string textureText, SDL_Color textColor )
{
	//Get rid of preexisting texture
	Free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( g_font, textureText.c_str(), textColor );
	if( textSurface != NULL )
	{
		//Create texture from surface pixels
        texture_ = SDL_CreateTextureFromSurface( g_renderer, textSurface );
		if( texture_ == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			width_ = textSurface->w;
			height_ = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}
	else
	{
		printf( "Unable to Render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}

	//Return success
	return texture_ != NULL;
}
#endif

void Texture::Free()
{
	//Free texture if it exists
	if( texture_ != NULL )
	{
		SDL_DestroyTexture( texture_ );
		texture_ = NULL;
		width_ = 0;
		height_ = 0;
	}
}

void Texture::SetColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture
	SDL_SetTextureColorMod( texture_, red, green, blue );
}

void Texture::Render( int x, int y, SDL_Rect* clip )
{
	//Set rendering space and Render to screen
	SDL_Rect renderQuad = { x, y, width_, height_ };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopy( g_renderer, texture_, clip, &renderQuad );
}

int Texture::Width()
{
	return width_;
}

int Texture::Height()
{
	return height_;
}
