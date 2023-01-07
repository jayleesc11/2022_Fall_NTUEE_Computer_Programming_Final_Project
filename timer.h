#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>


//The application time based timer
class Timer
{
    public:
    	
		//Initializes variables
		Timer();

		//The various clock actions
		void Start();
		void Stop();
		void Pause();
		void Unpause();

		//Gets the timer's time
		Uint32 GetTicks();

		//Checks the status of the timer
		bool started();
		bool paused();
		
		Uint32 last_action_ticks_;

    private:
		//The clock time when the timer started
		Uint32 start_ticks_;

		//The ticks stored when the timer was paused
		Uint32 paused_ticks_;

		//The timer status
		bool paused_;
		bool started_;
};

#endif
