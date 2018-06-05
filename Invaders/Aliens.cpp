
#include "Aliens.h"


// our default constructors effectivly do nothing as we will always construct with an image. 
Aliens::Aliens(){}

Aliens::~Aliens(){}

Aliens::Aliens(char* fName, MyFiles* fh)
{
	
	Image = new Surface(fName, fh);
	CurrentAnim = 0;
	TickForAnim = TICKCOUNT;
	MarkForRemoval = false;
	this->Type = Alien;

}


Aliens::Aliens(Surface* S1, Surface* S2)
{

	
	CurrentAnim = 0;
	TickForAnim = TICKCOUNT;
	MarkForRemoval = false;
	this->Type = Alien;
	this->Image = this->Image1 = S1;
	this->Image2 = S2;
	
}



Aliens::Aliens(int Type, MyFiles* fh)
{
	 static char* Names1[] =
	{
		(char*)"..//Assets//invaders8x8//InvaderA-1.png",
		(char*)"..//Assets//invaders8x8//InvaderB-1.png",
		(char*)"..//Assets//invaders8x8//InvaderB-1.png",
		(char*)"..//Assets//invaders8x8//InvaderC-1.png",
		(char*)"..//Assets//invaders8x8//InvaderC-1.png"
	};

	  static char* Names2[] =
	{
		(char*)"..//Assets//invaders8x8//InvaderA-2.png",
		(char*)"..//Assets//invaders8x8//InvaderB-2.png",
		(char*)"..//Assets//invaders8x8//InvaderB-2.png",
		(char*)"..//Assets//invaders8x8//InvaderC-2.png",
		(char*)"..//Assets//invaders8x8//InvaderC-2.png"
	};

	Image1 = new Surface(Names1[Type], fh);
	Image2 = new Surface(Names2[Type], fh);

	Image = Image1;		// Let the Objects Drawnsurface have something to work with.
	CurrentAnim = 0;
	TickForAnim = TICKCOUNT;
	MarkForRemoval = false;
	this->Type = Alien;

}


bool Aliens::Update(Surface* S, Input* In)
{
	bool ReturnValue = false;
	if (--TickForAnim == 0)
	{
		TickForAnim = TICKCOUNT;
		CurrentAnim++;
		CurrentAnim  %= 2;
		Image = (CurrentAnim == 0) ? Image1 : Image2;
	}
	Objects::Update(S, In);
// now do we want to drop bombs?
	if (Rand(10000) < 5)
	{
		ReturnValue = true; // yeah we want to fire
		printf("Firing missile\n");
	}

	return ReturnValue;
}






