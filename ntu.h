#ifndef NTU_H
#define NTU_H

#include <vector>
using std::vector;

#include "texture.h"
#include "timer.h"


extern Texture g_ntu_sprites[8];
extern Texture g_ntu_red_sprites[8];

class NTU
{
	public:
		// Existence status
		bool alive_;

		// Hurt by Student
		void Hurt(int hurt);
		
		// Move
		void Move();
		
		// Render
		void Render();
		
		// Info & get info
		const int id_;
		const int maprow_;
		const int damage_;
        const double velocity_;
		double pos_x();
	
	protected:
		// Constructor
		NTU(int id, double velocity, int hp, int damage, int r);
		
		// Hurt 
		Timer hurt_timer_;
		bool red_image_;
		double hp_;
		
		// Pos
		double pos_x_;
        double pos_y_;
};

extern vector<NTU*> g_ntus;

class Homework: public NTU
{
	public:
		Homework(int row);
};

class Video: public NTU
{
	public:
		Video(int row);
};

class Deadlinehomework: public NTU
{
	public:
		Deadlinehomework(int row);
};

class Quiz: public NTU
{
	public:
		// Normal constructor
		Quiz(int row);
		
		// Constructor for Midterm and Final summon
		Quiz(int row, double x);
};

class Project: public NTU
{
	public:
		Project(int row);
};

class Midterm: public NTU
{
	public:
		Midterm(int row);
		
		void Summon();
	
	private:
		Timer summon_timer_;
};

class Final: public NTU
{
	public:
		// Normal Constructor
		Final(int row);
		
		// Constuctor for kLose animation
		Final(int x, int y);
		
		void Summon();
	
	private:
		Timer summon_timer_;
};

class Shuiyuan: public NTU
{
	public:
		Shuiyuan(int row);
};

#endif
