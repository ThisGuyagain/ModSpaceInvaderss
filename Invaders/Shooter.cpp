
#include "Shooter.h"
#include "Game.h"


Shooter::Shooter()
{

}


Shooter::Shooter(char* f, MyFiles* fh) :Objects(f, fh)
{
	// just let the base constructor work
	MarkForRemoval = false;
	Type = AShooter;
}


bool Shooter::Update(Surface* a_Screen, Input* a_Input)
{

	bool fire = false;

	if (a_Input->TestKey(KEY_LEFT))
	{
		Xpos--;
		if (Xpos < 0) Xpos = 0;
	}
	if (a_Input->TestKey(KEY_RIGHT))
	{
		Xpos++;
		if (Xpos > SCRWIDTH - Image->GetWidth()) Xpos = SCRWIDTH - Image->GetWidth();

	}

	if (a_Input->TestKey(KEY_SPACE))
	{
		// fire
		fire = true;

	}

	Image->CopyAlphaPlot(a_Screen, (int)Xpos, (int)Ypos);

	return fire;
}