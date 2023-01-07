#include "cardbar.h"

#include <iomanip>
#include <iostream>
#include <sstream>

#include "constant.h"
#include "student.h"


void Cardbar::Start()
{
	coffee_timer_.Start();
	coffee_timer_.last_action_ticks_ = 0;
	
	mouse_state_ = 0;
	for (int i = 0; i < 6; i++) {
		role_[i].cooldown_status = false;
	}
	role_[0].cooldown_time = kNormalstudentCD;
	role_[1].cooldown_time = kStarstudentCD;
	role_[2].cooldown_time = kLousystudentCD;
	role_[3].cooldown_time = kCoffeemachineCD;
	role_[4].cooldown_time = kPastexamCD;
	role_[5].cooldown_time = kObservationCD;
	
	role_[0].cost = kNormalstudentCost;
	role_[1].cost = kStarstudentCost;
	role_[2].cost = kLousystudentCost;
	role_[3].cost = kCoffeemachineCost;
	role_[4].cost = kPastexamCost;
	role_[5].cost = kObservationCost;
	
	for(int i = 0; i < 5; i++)
		for(int j = 0; j < 9; j++)
			is_occupied_[i][j] = false;
}

void Cardbar::CallObject (int a)
{
	if (mouse_state_ == 0)
	{
		a = (a - kBlockHeight) / kBlockWidth;
		if (!role_[a].cooldown_status && g_coffee_number >= role_[a].cost && mouse_state_ == 0) {
			mouse_state_ = a + 1;
		}
	}
	else
	{
		mouse_state_ = 0;
	}
}

void Cardbar::Render()
{
	if( coffee_timer_.GetTicks() >= kCoffeePlusCD * 1000 + coffee_timer_.last_action_ticks_)
	{
		g_coffee_number++;
		coffee_timer_.last_action_ticks_ = coffee_timer_.GetTicks();
	}
	
	std::stringstream CoffeeText;
	CoffeeText << (g_coffee_number) << std::setw(2) << std::setfill('0');
	coffee_number_.LoadFromRenderedText( g_font, CoffeeText.str().c_str(), {255, 255, 255, 255} );
	coffee_number_.Render(59, 102);
	
	if (mouse_state_ != 0)
	{
		int x, y;
    	SDL_GetMouseState( &x, &y );
		g_student_sprites[mouse_state_ - 1].Render(x - kBlockWidth/2, y - kBlockHeight/2);
	}
	
	for (int i = 0; i < 6; i++)
	{
		std::stringstream TimeText;
		if (role_[i].cooldown_status)
		{
			if (role_[i].cooldown_timer.GetTicks() - role_[i].cooldown_start > role_[i].cooldown_time * 1000) {
				role_[i].cooldown_status = false;
				continue;
			}
			int c;
			c = (role_[i].cooldown_timer.GetTicks() - role_[i].cooldown_start) / 1000;
			TimeText.str( "" );
			TimeText << (role_[i].cooldown_time-c);
			cooldown_text_[i].LoadFromRenderedText( g_font, TimeText.str().c_str(), {255, 255, 0, 255} );
			cooldown_text_[i].Render(kBlockWidth * (i+1) + 90, 40);
		}
	}
}

void Cardbar::ConstructObject ()
{
	if (mouse_state_ != 0)
	{
		int x, y, row, col;
	    SDL_GetMouseState( &x, &y );
	    if ( CanPlace(x, y) )
	    {
	    	row = (y - kMapOriginY) / kBlockHeight;
			col = (x - kMapOriginX) / kBlockWidth;
		    switch (mouse_state_) {
				case 1:
					g_students.emplace_back(new Normalstudent(row, col));
					break;
					
				case 2:
					g_students.emplace_back(new Starstudent(row, col));
					break;
					
				case 3:
					g_students.emplace_back(new Lousystudent(row, col));
					break;
					
				case 4:
					g_students.emplace_back(new Coffeemachine(row, col));
					break;

				case 5:
					g_students.emplace_back(new Pastexam(row, col));
					break;
					
				case 6:
					g_students.emplace_back(new Observation(row, col));
					break;
			}
			is_occupied_[row][col] = true;
			g_coffee_number -= role_[mouse_state_ - 1].cost;
			role_[mouse_state_ - 1].cooldown_status = true;
			role_[mouse_state_ - 1].cooldown_timer.Start();
			role_[mouse_state_ - 1].cooldown_start = role_[mouse_state_ - 1].cooldown_timer.GetTicks();
			mouse_state_ = 0;
		}
	}
}

bool Cardbar::CanPlace(int x, int y)
{
	if(x < kMapOriginX || x > kMapEndX || y < kMapOriginY || y > kMapEndY)
		return false;
	
	int row = (y - kMapOriginY) / kBlockHeight;
	int col = (x - kMapOriginX) / kBlockWidth;
	
	if(is_occupied_[row][col])
		return false;
		
	return true;
}
