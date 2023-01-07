#ifndef BATTLECONTROL_H
#define BATTLECONTROL_H

#include <vector>
using std::vector;

#include "cardbar.h"
#include "ntu.h"
#include "student.h"


extern Cardbar g_cardbar;

extern vector<Bullet*> g_bullets;
extern vector<Student*> g_students;
extern vector<NTU*> g_ntus;

class Battlecontrol
{
	public:
		int state_;
		
		// Start
		void Start();
		
		// handle all battle calculation
		void HandleAllBattleCalculation();
		
		// handle all render
		void HandleAllRender();
		
		// generate NTU
		int GetRandomMaprow();
		void HandleNTUGenerate();
		
		// can NTU attack Student & shuiyuan skill
		bool CanNTUMove(NTU* ntu);

		// handle Student shooter shoot
		void HandleStudentShoot(Student* student);

		// handle bullet & NTU interaction
		void HandleBulletHitMove(Bullet* bullet);
		
		// handle Student bomber explode
		bool CanStudentExplode(Student* student);
		void HandleStudentBomberExplode(Student* student);
	
	protected:
		Timer ntu_generator_[8];
};

#endif
