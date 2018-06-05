#include "MyBullet.h"


MyBullet::MyBullet()
{
}



MyBullet::~MyBullet()
{
}

MyBullet::MyBullet(char* f, MyFiles* fh) :Objects(f, fh)
{
	// just let the base constructor work
	Type = Bullet;
}


bool MyBullet::Update(Surface* a_Screen, Input* a_Input)
{
	bool returnValue = false;

// I'm a bullet I move up the screen, the only reason I stop is if I go off the end, or if I find that I hit something

	Ypos += Yspeed;
	if (Ypos < 0) 
		MarkForRemoval = true;

	Objects::Update(a_Screen, a_Input);

	return returnValue;
}


bool MyBullet::TestForHit(Objects* TheObject)
{
	int My_Height = this->Image->GetHeight()/2;
	int My_Width = this->Image->GetWidth()/2;

	int Ob_Height = TheObject->Image->GetHeight()/2;
	int Ob_Width = TheObject->Image->GetWidth()/2;
	
	// do a simple circle/circle test
	float R1 = sqrtf((My_Height*My_Height) + (My_Width*My_Width));
	float R2 = sqrtf((Ob_Height*Ob_Height) + (Ob_Width*Ob_Width));

	// move to the centre
	int diffx = ((Xpos + My_Width) - (TheObject->Xpos + Ob_Width));
	int diffy = ((Ypos+My_Height) - (TheObject->Ypos+Ob_Height));

	float Dist = sqrtf((diffx*diffx) + (diffy*diffy));
	if (Dist < (R1 + R2)) return true; 

	return false;


}


