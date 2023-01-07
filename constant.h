#ifndef CONSTANT_H
#define CONSTANT_H

// Screen update rate
#define kScreenFPS 60
#define kScreenTickPerFrame (1000.0 / kScreenFPS)
#define kFrameInterval (1.0 / kScreenFPS)

// Screen dimension
#define kScreenWidth 1100
#define kScreenHeight 960

// State constant
#define kInitial 0
#define kInitStudent 1
#define kInitNTU 2
#define kGame 3
#define kWin 4
#define kLose 5

// Map dimension
#define kMapOriginX 100
#define kMapOriginY 150
#define kBlockWidth 100
#define kBlockHeight 150

// Map calculation
#define GetXFromCol(col) (kMapOriginX + ((col) * kBlockWidth))
#define GetYFromRow(row) (kMapOriginY + ((row) * kBlockHeight))
#define kMapEndX (kMapOriginX + 9 * kBlockWidth)
#define kMapEndY (kMapOriginY + 5 * kBlockHeight)

// Bullet info
#define kBulletVelocity 4
#define kBulletDamage 20

// Student ID
#define kNormalstudentID 0
#define kStarstudentID 1
#define kLousystudentID 2
#define kCoffeemachineID 3
#define kPastexamID 4
#define kObservationPrepareID 5
#define kObservationSetID 6

// Student HP 
#define kNormalstudentHP 300
#define kStarstudentHP 300
#define kLousystudentHP 2000
#define kCoffeemachineHP 300
#define kPastexamHP 300
#define kObservationHP 300

// Student CD
#define kNormalstudentCD 8
#define kStarstudentCD 8
#define kLousystudentCD 30
#define kCoffeemachineCD 8
#define kPastexamCD 30
#define kObservationCD 30

// Student Cost
#define kInitCoffeeNumber 20
#define kCoffeePlusCD 10
#define kNormalstudentCost 4
#define kStarstudentCost 8
#define kLousystudentCost 2
#define kCoffeemachineCost 2
#define kPastexamCost 6
#define kObservationCost 1

// Student Skill info
#define kNormalstudentAttackCD 1.4
#define kStarstudentAttackCD 1.4
#define kStarstudentAttackInterval 0.1
#define kCoffeemachineYieldCD 24
#define kPastexamDamageMax 1800
#define kPastexamDamageMin 180
#define kObservationSetCD 15
#define kObservationDamage 1200

// NTU ID
#define kHomeworkID 0
#define kVideoID 1
#define kDeadlinehomeworkID 2
#define kQuizID 3
#define kProjectID 4
#define kMidtermID 5
#define kFinalID 6
#define kShuiyuanID 7

// NTU HP
#define kHomeworkHP 200
#define kVideoHP 400
#define kDeadlinehomeworkHP 120
#define kQuizHP 400
#define kProjectHP 1300
#define kMidtermHP 1000
#define kFinalHP 1500
#define kShuiyuanHP 100

// NTU velocity
#define kHomeworkVelocity 0.25
#define kVideoVelocity 0.25
#define kProjectVelocity 0.25
#define kDeadlinehomeworkVelocity 1
#define kQuizVelocity 0.25
#define kMidtermVelocity 0.2
#define kFinalVelocity 0.2
#define kShuiyuanVelocity 2

// NTU damage
#define kHomeworkDamage 100
#define kVideoDamage 100
#define kProjectDamage 100
#define kDeadlinehomeworkDamage 200
#define kQuizDamage 100
#define kMidtermDamage 200
#define kFinalDamage 250

// NTU Skill info
#define kMidtermSummonCD 30
#define kFinalSummonCD 20

// Change color
#define kStudentChangeColorCD 0.5
#define kNTUChangeColorCD 0.4

// Fonts
#define Font "font/sylfaen.ttf"

#endif
