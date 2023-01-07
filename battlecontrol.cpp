#include "battlecontrol.h"

#include <vector>
using std::vector;

#include <SDL.h>

#include "cardbar.h"
#include "constant.h"
#include "ntu.h"
#include "student.h"


void Battlecontrol::Start()
{
	for(int i = 0; i < 8; i++)
	{
		ntu_generator_[i].Start();
		ntu_generator_[i].last_action_ticks_ = 0;
	}
	
	state_ = kGame;
}

// handle all battle calculation
void Battlecontrol::HandleAllBattleCalculation()
{
	HandleNTUGenerate();
	
	// g_bullets
	for (int i = 0; i < g_bullets.size(); i++)
	{
		// hit and move
		HandleBulletHitMove(g_bullets[i]);
		
		// die
		if(!g_bullets[i]->exist_)
		{
			delete g_bullets[i];
			g_bullets.erase(g_bullets.begin() + i);
		}
	}
	
	// g_students
    for (int i = 0; i < g_students.size(); i++)
	{
		// shooters
		HandleStudentShoot(g_students[i]);
		
		// Coffeemachines
		if(g_students[i]->id() == kCoffeemachineID)
			((Coffeemachine*)g_students[i])->Yield();
		
		HandleStudentBomberExplode(g_students[i]);
		
		// die
		if(!g_students[i]->alive_)
		{
			g_cardbar.is_occupied_[g_students[i]->maprow_][g_students[i]->mapcol_] = false;
			delete g_students[i];
			g_students.erase(g_students.begin() + i);
		}
	}
	
	// g_ntus
	for (int i = 0; i < g_ntus.size(); i++)
	{
		// summoners
		if(g_ntus[i]->id_ == kMidtermID)
			((Midterm*)g_ntus[i])->Summon();
			
		if(g_ntus[i]->id_ == kFinalID)
			((Final*)g_ntus[i])->Summon();
		
		// move and attack
		if(CanNTUMove(g_ntus[i]))
				g_ntus[i]->Move();
		
		// die
		if(!g_ntus[i]->alive_)
		{
			delete g_ntus[i];
			g_ntus.erase(g_ntus.begin() + i);
		}
	}	
}

int Battlecontrol::GetRandomMaprow()
{
	return (rand() % 5);
}

void Battlecontrol::HandleNTUGenerate()
{
	if( ntu_generator_[0].GetTicks() >= 30 * 1000 + ntu_generator_[0].last_action_ticks_)
	{
		g_ntus.emplace_back(new Homework(GetRandomMaprow()));
		
		ntu_generator_[0].last_action_ticks_ = ntu_generator_[0].GetTicks();
	}
	
	if( ntu_generator_[1].GetTicks() >= 40 * 1000 + ntu_generator_[1].last_action_ticks_)
	{
		g_ntus.emplace_back(new Video(GetRandomMaprow()));
		
		ntu_generator_[1].last_action_ticks_ = ntu_generator_[1].GetTicks();
	}
	
	if( ntu_generator_[2].GetTicks() >= 50 * 1000 + ntu_generator_[2].last_action_ticks_)
	{
		g_ntus.emplace_back(new Deadlinehomework(GetRandomMaprow()));
		
		ntu_generator_[2].last_action_ticks_ = ntu_generator_[2].GetTicks();
	}
	
	if( ntu_generator_[3].GetTicks() >= 55 * 1000 + ntu_generator_[3].last_action_ticks_)
	{
		g_ntus.emplace_back(new Quiz(GetRandomMaprow()));
		
		ntu_generator_[3].last_action_ticks_ = ntu_generator_[3].GetTicks();
	}
	
	if( ntu_generator_[7].GetTicks() >= (2*60) * 1000 + ntu_generator_[7].last_action_ticks_)
	{
		g_ntus.emplace_back(new Shuiyuan(GetRandomMaprow()));
		
		ntu_generator_[7].last_action_ticks_ = ntu_generator_[7].GetTicks();
	}
	
	if( ntu_generator_[5].GetTicks() >= (2*60 + 30) * 1000 + ntu_generator_[5].last_action_ticks_)
	{
		g_ntus.emplace_back(new Midterm(GetRandomMaprow()));
		
		ntu_generator_[5].last_action_ticks_ = 10000000;
	}
	
	if( ntu_generator_[4].GetTicks() >= (3*60 + 30) * 1000 + ntu_generator_[4].last_action_ticks_)
	{
		g_ntus.emplace_back(new Project(GetRandomMaprow()));
		
		ntu_generator_[4].last_action_ticks_ = 10000000;
	}	
	
	if( ntu_generator_[6].GetTicks() >= (4*60 + 30) * 1000 + ntu_generator_[6].last_action_ticks_)
	{
		g_ntus.emplace_back(new Final(GetRandomMaprow()));
		
		ntu_generator_[6].last_action_ticks_ = 10000000;
	}
	
	if(ntu_generator_[6].GetTicks() >= (4*60 + 30) * 1000)
	{
		if(g_ntus.size() == 0)
		{
			state_ = kWin;
			SDL_Delay(500);
		}
	}
}

// handle all Render (Done)
void Battlecontrol::HandleAllRender()
{
	// g_bullets
	for (int i = 0; i < g_bullets.size(); i++)
		g_bullets[i]->Render();
	
	// g_students
    for (int i = 0; i < g_students.size(); i++)
		g_students[i]->Render();
	
	// g_ntus
	for (int i = 0; i < g_ntus.size(); i++)
		g_ntus[i]->Render();
}

// handle NTU attack Student & shuiyuan skill (Done)
bool Battlecontrol::CanNTUMove(NTU* ntu)
{
	if(ntu->pos_x() - ntu->velocity_ * kBlockWidth * kFrameInterval <= kMapOriginX)
	{
		if(ntu->id_ != kShuiyuanID)
		{
			state_ = kLose;
			SDL_Delay(500);
			return false;
		}
		else
		{
			ntu->alive_ = false;
			return false;
		}
	}
	
	for(int i = 0; i < g_students.size(); i++)
		if(ntu->maprow_ == g_students[i]->maprow_ && 
		   ntu->pos_x() - ntu->velocity_ * kBlockWidth * kFrameInterval <= GetXFromCol(g_students[i]->mapcol_) + 0.85 * kBlockWidth && 
		   ntu->pos_x() - ntu->velocity_ * kBlockWidth * kFrameInterval >= GetXFromCol(g_students[i]->mapcol_) - 0.15 * kBlockWidth)
		{
			if(ntu->id_ != kShuiyuanID)
				g_students[i]->Hurt(ntu->damage_);
			else
				g_students[i]->alive_ = false;
			
			return false;
		}
	
	return true;
}

// handle Student shooter shoot (Done)
void Battlecontrol::HandleStudentShoot(Student* student)
{
	if(student->id() == kNormalstudentID || student->id() == kStarstudentID)
	{
		for (int j = 0; j < g_ntus.size(); j++)
			if(g_ntus[j]->maprow_ == student->maprow_ && g_ntus[j]->pos_x() <= kMapEndX)
			{
				if(student->id() == kNormalstudentID)
					((Normalstudent*)student)->Shoot();
				
				if(student->id() == kStarstudentID)
					((Starstudent*)student)->Shoot();
			}
	}
}

// handle bullet & NTU interaction (Done)
void Battlecontrol::HandleBulletHitMove(Bullet* bullet)
{
	for (int j = 0; j < g_ntus.size() && bullet->exist_; j++)
		if(bullet->maprow_ == g_ntus[j]->maprow_ && bullet->initial_x_ <= g_ntus[j]->pos_x() && bullet->pos_x() + 40 >= g_ntus[j]->pos_x())
		{
			g_ntus[j]->Hurt(kBulletDamage);
			bullet->exist_ = false;
		}
	
	if(bullet->exist_)
		bullet->Move();
}

// handle Student bomber explode_
bool Battlecontrol::CanStudentExplode(Student* student)
{	
	for (int i = 0; i < g_ntus.size(); i++)
		if(g_ntus[i]->id_ != kShuiyuanID && g_ntus[i]->alive_ && g_ntus[i]->maprow_ == student->maprow_ && g_ntus[i]->pos_x() <= GetXFromCol(student->mapcol_) + kBlockWidth)
			return true;
	
	return false;
}

void Battlecontrol::HandleStudentBomberExplode(Student* student)
{
	if(student->id() == kPastexamID || student->id() == kObservationSetID)
		if(CanStudentExplode(student))
		{
			for (int j = 0; j < g_ntus.size(); j++)
				if(g_ntus[j]->alive_ && 
				   g_ntus[j]->maprow_ <= student->maprow_ + 1 && g_ntus[j]->maprow_ >= student->maprow_ - 1 && 
				   g_ntus[j]->pos_x() <= GetXFromCol(student->mapcol_) + 1.5 * kBlockWidth && g_ntus[j]->pos_x() >= GetXFromCol(student->mapcol_) - 1.5  * kBlockWidth)	
				{
					g_ntus[j]->Hurt(((Pastexam*)student)->damage());
				}
			
			((Pastexam*)student)->explode_ = true;
		}
}
