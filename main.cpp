#include <stdio.h>

#include <ctime>
using std::time;
#include <vector>
using std::vector;

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "battlecontrol.h"
#include "cardbar.h"
#include "constant.h"
#include "ntu.h"
#include "state.h"
#include "student.h"
#include "texture.h"
#include "timer.h"


// Starts up SDL and creates window
bool Init();
bool LoadMedia();
void Close();

SDL_Window* g_window = NULL;
SDL_Renderer* g_renderer = NULL;
Texture g_backgrounds[6];
Texture g_bullet_sprite;
Texture g_student_sprites[7];
Texture g_student_red_sprites[7];
Texture g_explode_sprites;
SDL_Rect g_explode_clips[20];
Texture g_ntu_sprites[8];
Texture g_ntu_red_sprites[8];

// Fonts
TTF_Font *g_font = NULL;

// Elements
vector<Bullet*> g_bullets;
vector<Student*> g_students;
vector<NTU*> g_ntus;

// Game state
State g_state;

// Game battlecontrol
Battlecontrol g_battlecontrol;

// Game cardbar
Cardbar g_cardbar;

// Game coffee number
int g_coffee_number = kInitCoffeeNumber;

bool Init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		g_window = SDL_CreateWindow( "Student vs NTU", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, kScreenWidth, kScreenHeight, SDL_WINDOW_SHOWN );
		if( g_window == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			g_renderer = SDL_CreateRenderer( g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( g_renderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( g_renderer, 0xff, 0xff, 0xff, 0xff );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
				
				//Initialize font loading
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool LoadMedia()
{
	//Loading success flag
	bool success = true;

	//Load texture
	if( !g_backgrounds[0].LoadFromFile( "image/InitBackground.png" ) )
	{
		printf( "Failed to load texture!\n" );
		success = false;
	}
	g_backgrounds[1].LoadFromFile( "image/StudentBackground.png" );
	g_backgrounds[2].LoadFromFile( "image/NTUBackground.png" );
	g_backgrounds[3].LoadFromFile( "image/GameBackground.png" );
	g_backgrounds[4].LoadFromFile( "image/WinBackground.png" );
	g_backgrounds[5].LoadFromFile( "image/LoseBackground.png" );
	
	g_bullet_sprite.LoadFromFile( "image/Bullet.png" );
	g_student_sprites[0].LoadFromFile( "image/Normalstudent.png" );
	g_student_sprites[1].LoadFromFile( "image/Starstudent.png" );
	g_student_sprites[2].LoadFromFile( "image/Lousystudent.png" );
	g_student_sprites[3].LoadFromFile( "image/Coffeemachine.png" );
	g_student_sprites[4].LoadFromFile( "image/Pastexam.png" );
	g_student_sprites[5].LoadFromFile( "image/Observation_Prepare.png" );
	g_student_sprites[6].LoadFromFile( "image/Observation_Set.png" );
	g_student_red_sprites[0].LoadFromFile( "image/RedNormalstudent.png" );
	g_student_red_sprites[1].LoadFromFile( "image/RedStarstudent.png" );
	g_student_red_sprites[2].LoadFromFile( "image/RedLousystudent.png" );
	g_student_red_sprites[3].LoadFromFile( "image/RedCoffeemachine.png" );
	g_student_red_sprites[4].LoadFromFile( "image/RedPastexam.png" );
	g_student_red_sprites[5].LoadFromFile( "image/RedObservation_Prepare.png" );
	g_student_red_sprites[6].LoadFromFile( "image/RedObservation_Set.png" );
	g_explode_sprites.LoadFromFile( "image/ExplodeFrames.png" );
	g_ntu_sprites[0].LoadFromFile( "image/Homework.png" );
	g_ntu_sprites[1].LoadFromFile( "image/Video.png" );
	g_ntu_sprites[2].LoadFromFile( "image/Deadlinehomework.png" );
	g_ntu_sprites[3].LoadFromFile( "image/Quiz.png" );
	g_ntu_sprites[4].LoadFromFile( "image/Project.png" );
	g_ntu_sprites[5].LoadFromFile( "image/Midterm.png" );
	g_ntu_sprites[6].LoadFromFile( "image/Final.png" );
	g_ntu_sprites[7].LoadFromFile( "image/Shuiyuan.png" );
	g_ntu_red_sprites[0].LoadFromFile( "image/RedHomework.png" );
	g_ntu_red_sprites[1].LoadFromFile( "image/RedVideo.png" );
	g_ntu_red_sprites[2].LoadFromFile( "image/RedDeadlinehomework.png" );
	g_ntu_red_sprites[3].LoadFromFile( "image/RedQuiz.png" );
	g_ntu_red_sprites[4].LoadFromFile( "image/RedProject.png" );
	g_ntu_red_sprites[5].LoadFromFile( "image/RedMidterm.png" );
	g_ntu_red_sprites[6].LoadFromFile( "image/RedFinal.png" );
	g_ntu_red_sprites[7].LoadFromFile( "image/RedShuiyuan.png" );
	
	for(int i = 0; i < 2; i++)
		for(int j = 0; j < 8; j++)
		{
			g_explode_clips[8*i + j].x = j*200;
			g_explode_clips[8*i + j].y = i*200;
			g_explode_clips[8*i + j].w = 200;
			g_explode_clips[8*i + j].h = 200;
		}
	
	for(int i = 16; i < 20; i++)
	{
		g_explode_clips[i].x = i*200;
		g_explode_clips[i].y = 2*200;
		g_explode_clips[i].w = 200;
		g_explode_clips[i].h = 200;
	}
	
	//Open the font
	g_font = TTF_OpenFont(Font, 40);
	if( g_font == NULL )
	{
		printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	
	return success;
}

void Close()
{
	// Free loaded images
	g_bullet_sprite.Free();
	for(int i = 0; i < 6; i++)
		g_backgrounds[i].Free();
	for(int i = 0; i < 7; i++)
	{
		g_student_sprites[i].Free();
		g_student_red_sprites[i].Free();
	}
	for(int i = 0; i < 8; i++)
	{
		g_ntu_sprites[i].Free();
		g_ntu_red_sprites[i].Free();
	}
	
	// Free elements
	for(int i = 0; i < g_bullets.size(); i++)
		delete g_bullets[i];
	
	for(int i = 0; i < g_students.size(); i++)
		delete g_students[i];
	
	for(int i = 0; i < g_ntus.size(); i++)
		delete g_ntus[i];

	// Destroy window	
	SDL_DestroyRenderer( g_renderer );
	SDL_DestroyWindow( g_window );
	g_window = NULL;
	g_renderer = NULL;
	g_font = NULL;
	
	//Quit SDL subsystems
	IMG_Quit();
	TTF_Quit(); 
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !Init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !LoadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;
			
			//The frames per second cap timer
			Timer capTimer;
			srand(time(0));
			
			//While application is running
			while( !quit )
			{
				// Start cap timer
				capTimer.Start();
				
				// User Events handle
				while( SDL_PollEvent( &e ) != 0 )
				{
					// User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					// User clicks on screen
					if ( e.type == SDL_MOUSEBUTTONDOWN )
					{
						int x, y;
						SDL_GetMouseState( &x, &y );
						
						if(g_state.state_ == kInitial)
						{
							if(x > 300 && x < 800 && y > 450 && y < 600)
							{
								g_state.StartGame();
								SDL_Delay(100);
							}
							
							if(x > 100 && x < 500 && y > 650 && y < 900)
							{
								g_state.state_ = kInitStudent;
								SDL_Delay(100);
							}
							
							if(x > 600 && x < 1000 && y > 650 && y < 900)
							{
								g_state.state_ = kInitNTU;
								SDL_Delay(100);
							}
						}
						
						if(g_state.state_ == kInitStudent)
						{
							if(x > 48 && x < 1050 && y > 880 && y < 936)
							{
								g_state.state_ = kInitial;
								SDL_Delay(100);
							}
						}
						
						if(g_state.state_ == kInitNTU)
						{
							if(x > 48 && x < 1050 && y > 880 && y < 936)
							{
								g_state.state_ = kInitial;
								SDL_Delay(100);
							}
						}
						
						if(g_state.state_ == kGame)
						{
							//User clicks on cardbar
							if ( x > 150 && x < 750 && y <= 150 )
							{
								g_cardbar.CallObject (x);
							}
							else if ( y > 150 )
							{
								g_cardbar.ConstructObject ();
							}
						}
					}
				}
				
				if(g_state.state_ == kGame)
				{
					// Calculation handle
					g_battlecontrol.HandleAllBattleCalculation();
					g_state.GetBattlecontrolState();
					
					// Clear renderer
					SDL_RenderClear( g_renderer );
					
					// Render handle
					g_backgrounds[g_state.state_].Render(0, 0);
					g_battlecontrol.HandleAllRender();
					g_cardbar.Render();
				}
				else if(g_state.state_ == kLose)
				{
					// Clear renderer
					SDL_RenderClear( g_renderer );
					
					// Render handle
					g_backgrounds[g_state.state_].Render(0, 0);
					g_state.GenerateFinals();
				}
				else
				{
					g_backgrounds[g_state.state_].Render(0, 0);
				}
				
				// Update renderer handle
				SDL_RenderPresent( g_renderer );
				
				//If frame finished early
				int frameTicks = capTimer.GetTicks();
				if( frameTicks < kScreenTickPerFrame )
				{
					//Wait remaining time
					SDL_Delay( kScreenTickPerFrame - frameTicks );
				}
			}
		}
	}

	//Free resources and Close SDL
	Close();

	return 0;
}
