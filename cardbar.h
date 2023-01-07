#ifndef CARDBAR_H
#define CARDBAR_H

#include <vector>
using std::vector;

#include <SDL.h>
#include <SDL_ttf.h>

#include "constant.h"
#include "student.h"
#include "texture.h"
#include "timer.h"


extern int g_coffee_number;
extern Texture g_student_sprites[7];
extern TTF_Font *g_font;

extern vector<Student*> g_students;


struct card
{
	int cost;
	int cooldown_time;
	bool cooldown_status;
	Uint32 cooldown_start;
	Timer cooldown_timer;
};

class Cardbar
{   
	private:
		card role_[6];
		Texture cooldown_text_[6];
		Texture coffee_number_;
		int mouse_state_;
		
	public:
		// Start
		void Start();
		
		void CallObject(int a);
		void Render();
		void ConstructObject();
		
		Timer coffee_timer_;
		// State of each block
		bool is_occupied_[5][9];
		
		// can place Student?
		bool CanPlace(int x, int y);
};

#endif

