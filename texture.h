#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
using std::string;

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>


extern SDL_Renderer* g_renderer;

//Texture wrapper class
class Texture
{
	public:
		//Initializes variables
		Texture();

		//Deallocates memory
		~Texture();

		//Loads image at specified path
		bool LoadFromFile( string path );
		
		#if defined(SDL_TTF_MAJOR_VERSION)
		//Creates image from font string
		bool LoadFromRenderedText( TTF_Font *g_font, string textureText, SDL_Color textColor );
		#endif

		//Deallocates texture
		void Free();
		
		//Set color modulation
		void SetColor( Uint8 red, Uint8 green, Uint8 blue );
		
		//Renders texture at given point
		void Render( int x, int y, SDL_Rect* clip = NULL );

		//Gets image dimensions
		int Width();
		int Height();

	private:
		//The actual hardware texture
		SDL_Texture* texture_;

		//Image dimensions
		int width_;
		int height_;
};

#endif 
