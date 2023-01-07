#ifndef STUDENT_H
#define STUDENT_H

#include <vector>
using std::vector;

#include "ntu.h"
#include "texture.h"
#include "timer.h"


extern Texture g_bullet_sprite;
extern Texture g_student_sprites[7];
extern Texture g_student_red_sprites[7];
extern Texture g_explode_sprites;
extern SDL_Rect g_explode_clips[20];
extern int g_coffee_number;


class Bullet
{
	public:
		// Existence status
		bool exist_;
        
        // Constructor
		Bullet(int r, int c);
		
		// Move
		void Move();
		
		// Render
		void Render();
		
		// Info & get info
		const double initial_x_;
        const int maprow_;
        const double pos_y_;
		double pos_x();
        
	private:
        double pos_x_;
};

extern std::vector<Bullet*> g_bullets;

class Student
{
	public:
		// alive_ Status
		bool alive_;

		// Hurt by NTU
		void Hurt(int damage);
		
		// Render
		virtual void Render();
		
		// Info & get info
		const int maprow_;
        const int mapcol_;
        int id();
		
	protected:
		// Constructor
		Student(int id, int hp, int r, int c);
		
		int id_;
		
		// Hurt
		Timer hurt_timer_;
		bool red_image_;
		bool hurt_;
		double hp_;
};

class Normalstudent: public Student
{
	public:
		Normalstudent(int row, int col);
		
		void Shoot();
		
	private:
		Timer shoot_timer_;
};

class Starstudent: public Student
{
	public:
		Starstudent(int row, int col);
		
		void Shoot();
	
	private:
		Timer shoot_timer1_;
		Timer shoot_timer2_;
};

class Lousystudent: public Student
{
	public:
		Lousystudent(int row, int col);
};

class Coffeemachine: public Student
{
	public:
		Coffeemachine(int row, int col);
		
		void Yield();
		
	private:
		Timer yield_timer_;
};

class Pastexam: public Student
{
	public:
		bool explode_;
			
		Pastexam(int row, int col);
		
		void Render();
		
		int damage();
		
	protected:
		// Explode animation
		SDL_Rect* current_clip_;
		int frame_index_;
		
		int damage_;
};

class Observation: public Pastexam
{
	public:
		Observation(int row, int col);
		
		void Render();
		
	private:
		// Set time
		Timer set_timer_;
};

#endif
