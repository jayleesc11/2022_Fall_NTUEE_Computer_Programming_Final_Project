#include "ntu.h"

#include <vector>
using std::vector;

#include "constant.h"
#include "texture.h"
#include "timer.h"


NTU::NTU(int id, double velocity, int hp, int damage, int r): id_(id), velocity_(velocity), hp_(hp), damage_(damage), maprow_(r), pos_y_(GetYFromRow(r))
{
	hurt_timer_.Start();
	alive_ = true;
	red_image_ = false;
	pos_x_ = kScreenWidth;
}

void NTU::Move()
{
	pos_x_ -= velocity_ * kBlockWidth * kFrameInterval;
}

void NTU::Hurt(int hurt)
{
	hp_ -= hurt;
	
	hurt_timer_.Start();
	hurt_timer_.last_action_ticks_ = hurt_timer_.GetTicks();
	red_image_ = true;
	
	if(hp_ <= 0)
	{
		alive_ = false;
	}
}

void NTU::Render()
{
	if(red_image_)
	{
		if( hurt_timer_.GetTicks() >= kNTUChangeColorCD * 1000 + hurt_timer_.last_action_ticks_)
		{
			g_ntu_sprites[id_].Render(pos_x_, pos_y_);
			red_image_ = false;
		}
		else
			g_ntu_red_sprites[id_].Render(pos_x_, pos_y_);
		
		return;
	}
	
	g_ntu_sprites[id_].Render(pos_x_, pos_y_);
}

double NTU::pos_x() { return pos_x_; }

Homework::Homework(int row): NTU(kHomeworkID, kHomeworkVelocity, kHomeworkHP, kHomeworkDamage, row) {}

Video::Video(int row): NTU(kVideoID, kVideoVelocity, kVideoHP, kVideoDamage, row) {}

Deadlinehomework::Deadlinehomework(int row): NTU(kDeadlinehomeworkID, kDeadlinehomeworkVelocity, kDeadlinehomeworkHP, kDeadlinehomeworkDamage, row) {}

Quiz::Quiz(int row): NTU(kQuizID, kQuizVelocity, kQuizHP, kQuizDamage, row) {}

Quiz::Quiz(int row, double x): NTU(3, kQuizVelocity, kQuizHP, kQuizDamage, row)
{
	pos_x_ = x;
}

Project::Project(int row): NTU(kProjectID, kProjectVelocity, kProjectHP, kProjectDamage, row) {}

Midterm::Midterm(int row): NTU(kMidtermID, kMidtermVelocity, kMidtermHP, kMidtermDamage, row)
{
	summon_timer_.Start();
	summon_timer_.last_action_ticks_ = 0;
}

void Midterm::Summon()
{
	if(summon_timer_.last_action_ticks_ == 0)
	{
		if(pos_x_ - kBlockWidth <= kMapOriginX)
			g_ntus.emplace_back(new Quiz(maprow_, pos_x_ - kBlockWidth));	// Front
		g_ntus.emplace_back(new Quiz(maprow_, pos_x_ + kBlockWidth));		// Back
		if(maprow_ - 1 >= 0)
			g_ntus.emplace_back(new Quiz(maprow_ - 1, pos_x_));			// Up
		if(maprow_ + 1 <= 4)
			g_ntus.emplace_back(new Quiz(maprow_ + 1, pos_x_));			// Down
			
		summon_timer_.last_action_ticks_ = summon_timer_.GetTicks();
	}
	
	if( summon_timer_.GetTicks() >= kMidtermSummonCD * 1000 + summon_timer_.last_action_ticks_)
	{
		if(pos_x_ - kBlockWidth <= kMapOriginX)
			g_ntus.emplace_back(new Quiz(maprow_, pos_x_ - kBlockWidth));	// Front
		g_ntus.emplace_back(new Quiz(maprow_, pos_x_ + kBlockWidth));		// Back
		if(maprow_ - 1 >= 0)
			g_ntus.emplace_back(new Quiz(maprow_ - 1, pos_x_));			// Up
		if(maprow_ + 1 <= 4)
			g_ntus.emplace_back(new Quiz(maprow_ + 1, pos_x_));			// Down
			
		summon_timer_.last_action_ticks_ = summon_timer_.GetTicks();
			
		summon_timer_.last_action_ticks_ = summon_timer_.GetTicks();
	}
}

Final::Final(int row): NTU(kFinalID, kFinalVelocity, kFinalHP, kFinalDamage, row)
{
	summon_timer_.Start();
	summon_timer_.last_action_ticks_ = 0;
}

Final::Final(int x, int y): NTU(kFinalID, kFinalVelocity, kFinalHP, kFinalDamage, 0)
{
	pos_x_ = x;
	pos_y_ = y;
}

void Final::Summon()
{
	if(summon_timer_.last_action_ticks_ == 0)
	{
		if(pos_x_ - kBlockWidth <= kMapOriginX)
			g_ntus.emplace_back(new Quiz(maprow_, pos_x_ - kBlockWidth));	// Front
		g_ntus.emplace_back(new Quiz(maprow_, pos_x_ + kBlockWidth));		// Back
		if(maprow_ - 1 >= 0)
			g_ntus.emplace_back(new Quiz(maprow_ - 1, pos_x_));			// Up
		if(maprow_ + 1 <= 4)
			g_ntus.emplace_back(new Quiz(maprow_ + 1, pos_x_));			// Down
			
		summon_timer_.last_action_ticks_ = summon_timer_.GetTicks();
	}
	
	if( summon_timer_.GetTicks() >= kMidtermSummonCD * 1000 + summon_timer_.last_action_ticks_)
	{
		if(pos_x_ - kBlockWidth <= kMapOriginX)
			g_ntus.emplace_back(new Quiz(maprow_, pos_x_ - kBlockWidth));	// Front
		g_ntus.emplace_back(new Quiz(maprow_, pos_x_ + kBlockWidth));		// Back
		if(maprow_ - 1 >= 0)
			g_ntus.emplace_back(new Quiz(maprow_ - 1, pos_x_));			// Up
		if(maprow_ + 1 <= 4)
			g_ntus.emplace_back(new Quiz(maprow_ + 1, pos_x_));			// Down
			
		summon_timer_.last_action_ticks_ = summon_timer_.GetTicks();
	}
}

Shuiyuan::Shuiyuan(int row): NTU(kShuiyuanID, kShuiyuanVelocity, kShuiyuanHP, 0, row) {}
