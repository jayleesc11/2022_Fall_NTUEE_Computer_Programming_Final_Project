#ifndef STATE_H
#define STATE_H

#include <vector>
using std::vector;

#include "battlecontrol.h"
#include "cardbar.h"

extern Battlecontrol g_battlecontrol;
extern Cardbar g_cardbar;
extern vector<NTU*> g_ntus;

class State
{
	public:
		State();
		
		int state_;
		
		void GetBattlecontrolState();
		
		void StartGame();
		
		void GenerateFinals();
		
	private:
		Timer render_timer_;
		double interval_;
};

#endif
