#include "state.h"

#include <vector>
using std::vector;

#include "battlecontrol.h"
#include "cardbar.h"
#include "constant.h"


State::State() 
{
	render_timer_.Start();
	render_timer_.last_action_ticks_ = 0;
	interval_ = 0.8;
	state_ = kInitial;
} 

void State::StartGame()
{
	state_ = kGame;
	g_battlecontrol.Start();
	g_cardbar.Start();
}

void State::GetBattlecontrolState()
{
	if(state_ == kGame && (g_battlecontrol.state_ == kWin || g_battlecontrol.state_ == kLose))
		state_ = g_battlecontrol.state_;
}

void State::GenerateFinals()
{
	if(render_timer_.last_action_ticks_ == 0)
	{
		for(int i = 0; i < g_ntus.size(); i++)
			delete g_ntus[i];
		g_ntus.clear();
	}
	
	if( render_timer_.GetTicks() >= interval_ * 1000 + render_timer_.last_action_ticks_)
	{
		g_ntus.emplace_back(new Final(rand() % (kScreenWidth - kBlockWidth), rand() % (kScreenHeight - kBlockHeight)));
		render_timer_.last_action_ticks_ = render_timer_.GetTicks();
	}
	
	for(int i = 0; i < g_ntus.size(); i++)
		g_ntus[i]->Render();
		
	if(g_ntus.size() >= 4)
		interval_ = 0.2;
		
	if(g_ntus.size() >= 15)
		interval_ = 0.01;
}
