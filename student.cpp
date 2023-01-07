#include "student.h"

#include <vector>
using std::vector;

#include <SDL.h>

#include "constant.h"
#include "ntu.h"
#include "texture.h"
#include "timer.h"


Bullet::Bullet(int r, int c): initial_x_(GetXFromCol(c) + kBlockWidth/2 - 40), pos_x_(GetXFromCol(c) + kBlockWidth/2 - 40), maprow_(r), pos_y_(GetYFromRow(r) + kBlockHeight/2 - 40)
{
    exist_ = true;
}

void Bullet::Move()
{
	pos_x_ += kBulletVelocity * kBlockWidth * kFrameInterval;
	
	if( pos_x_ >= kScreenWidth && exist_)
		exist_ = false;
}

void Bullet::Render()
{
	g_bullet_sprite.Render(pos_x_, pos_y_);
}

double Bullet::pos_x() { return pos_x_; }

Student::Student(int id, int hp, int r, int c): id_(id), hp_(hp), maprow_(r), mapcol_(c)
{
	alive_ = true;
	hurt_ = false;
	red_image_ = false;
	hurt_timer_.Start();
	hurt_timer_.last_action_ticks_ = 0;
}

void Student::Hurt(int damage)
{
	hp_ -= damage * kFrameInterval;
	
	hurt_ = true;
	
	if(hp_ <= 0 && alive_)
	{
		alive_ = false;
	}
}

void Student::Render()
{
	if(hurt_)
	{
		red_image_ = true;
		g_student_red_sprites[id_].Render(GetXFromCol(mapcol_), GetYFromRow(maprow_));
		
		if( hurt_timer_.GetTicks() >= kStudentChangeColorCD * 1000 + hurt_timer_.last_action_ticks_)
		{
			if(!red_image_)
			{
				g_student_red_sprites[id_].Render(GetXFromCol(mapcol_), GetYFromRow(maprow_));
				red_image_ = true;
			}
			else
			{
				hurt_ = false;
				red_image_ = false;
				g_student_sprites[id_].Render(GetXFromCol(mapcol_), GetYFromRow(maprow_));
			}
			
			hurt_timer_.last_action_ticks_ = hurt_timer_.GetTicks();
		}
		
		return;
	}
	
	g_student_sprites[id_].Render(GetXFromCol(mapcol_), GetYFromRow(maprow_));
}

int Student::id() { return id_; }

Normalstudent::Normalstudent(int row, int col): Student(kNormalstudentID, kNormalstudentHP, row, col)
{
	shoot_timer_.Start();
	shoot_timer_.last_action_ticks_ = 0;
}

void Normalstudent::Shoot()
{
	if( shoot_timer_.GetTicks() >= kNormalstudentAttackCD * 1000 + shoot_timer_.last_action_ticks_)
	{
		g_bullets.emplace_back(new Bullet(maprow_, mapcol_));
		shoot_timer_.last_action_ticks_ = shoot_timer_.GetTicks();
	}
}

Starstudent::Starstudent(int row, int col): Student(kStarstudentID, kStarstudentHP, row, col)
{
	shoot_timer1_.Start();
	shoot_timer2_.Start();
	shoot_timer1_.last_action_ticks_ = 0;
	shoot_timer2_.last_action_ticks_ = kStarstudentAttackInterval * 1000;
}

void Starstudent::Shoot()
{
	if( shoot_timer1_.GetTicks() >= kStarstudentAttackCD * 1000 + shoot_timer1_.last_action_ticks_)
	{
		g_bullets.emplace_back(new Bullet(maprow_, mapcol_));
		shoot_timer1_.last_action_ticks_ = shoot_timer1_.GetTicks();
	}
	
	if( shoot_timer2_.GetTicks() >= kStarstudentAttackCD * 1000 + shoot_timer2_.last_action_ticks_)
	{
		g_bullets.emplace_back(new Bullet(maprow_, mapcol_));
		shoot_timer2_.last_action_ticks_ = shoot_timer2_.GetTicks();
	}
}

Lousystudent::Lousystudent(int row, int col): Student(kLousystudentID, kLousystudentHP, row, col) {}

Coffeemachine::Coffeemachine(int row, int col): Student(kCoffeemachineID, kCoffeemachineHP, row, col)
{
	yield_timer_.Start();
	yield_timer_.last_action_ticks_ = 0;
}

void Coffeemachine::Yield()
{
	if( yield_timer_.GetTicks() >= kCoffeemachineYieldCD * 1000 + yield_timer_.last_action_ticks_)
	{
		g_coffee_number++;
		yield_timer_.last_action_ticks_ = yield_timer_.GetTicks();
	}
}

Pastexam::Pastexam(int row, int col): Student(kPastexamID, kPastexamHP, row, col)
{
	explode_ = false;
	frame_index_ = 0;
	
	damage_ = kPastexamDamageMin + rand() % (kPastexamDamageMax - kPastexamDamageMin);
}

void Pastexam::Render()
{
	if(explode_)
	{
		SDL_Rect* current_clip_ = &g_explode_clips[ frame_index_ ];
		g_explode_sprites.Render( GetXFromCol(mapcol_) - 50, GetYFromRow(maprow_) - 25, current_clip_ );
		frame_index_++;
		
		if(frame_index_ == 21)
		{
			hp_ = 0;
			alive_ = false;
		}
	}
	else
		g_student_sprites[id_].Render(GetXFromCol(mapcol_), GetYFromRow(maprow_));
}

int Pastexam::damage() { return damage_; }

Observation::Observation(int row, int col): Pastexam(row, col)
{
	set_timer_.Start();
	id_ = kObservationPrepareID;
	hp_ = kObservationHP;
	damage_ = kObservationDamage;
}

void Observation::Render()
{
	if(set_timer_.GetTicks() >= kObservationSetCD * 1000)
		id_ = kObservationSetID;
	
	if(id_ == kObservationSetID && explode_)
	{
		SDL_Rect* current_clip_ = &g_explode_clips[ frame_index_ ];
		g_explode_sprites.Render( GetXFromCol(mapcol_) - 50, GetYFromRow(maprow_) - 25, current_clip_ );
		frame_index_++;
		
		if(frame_index_ == 21)
		{
			hp_ = 0;
			alive_ = false;
		}
	}
	else
	{
		if(hurt_)
		{
			red_image_ = true;
			g_student_red_sprites[id_].Render(GetXFromCol(mapcol_), GetYFromRow(maprow_));
			
			if( hurt_timer_.GetTicks() >= kStudentChangeColorCD * 1000 + hurt_timer_.last_action_ticks_)
			{
				if(!red_image_)
				{
					g_student_red_sprites[id_].Render(GetXFromCol(mapcol_), GetYFromRow(maprow_));
					red_image_ = true;
				}
				else
				{
					hurt_ = false;
					red_image_ = false;
					g_student_sprites[id_].Render(GetXFromCol(mapcol_), GetYFromRow(maprow_));
				}
				
				hurt_timer_.last_action_ticks_ = hurt_timer_.GetTicks();
			}
			
			return;
		}
		
		g_student_sprites[id_].Render(GetXFromCol(mapcol_), GetYFromRow(maprow_));
	}
}
