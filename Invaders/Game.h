// Main Game loop control

#pragma once
//#include <vector>
#include "MyFiles.h"
#include "surface.h"
#include "Objects.h"
#include "Shooter.h"
#include "Input.h"
#include "Aliens.h"
#include "MyBullet.h"
#include "Shelter.h"
#include "TileFont.h"



#define SCRWIDTH 320
#define SCRHEIGHT 240

enum Directions
{
	Left,
	Right,
	Down

};

using namespace std;


class Game
{
public:
	
	Game();
	~Game();
	
	
	void Update(float DTime, MyFiles* FileHandler, Input* InputHandler,Surface* a_Screen);
	bool Init(MyFiles* FileHandler);
	TileFont Font;
	Objects* Bob;
	MyBullet* Bullet;
	Directions Direction;
	Directions SavedDirectionToChangeTo;
	int NumberOfDownSteps;
	int StepTime; 
	int AlienCount;
	int Multiplier = 1;
	Objects* Shelters[16];

	int Score;

private:
	
	 bool InitDone ;
	
	
	
	
	
};

