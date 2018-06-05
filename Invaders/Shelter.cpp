#include "Shelter.h"


// Shelters are always set up here, there are no graphics to load

Shelter::Shelter()
{
	// create its image
	Image = new Surface(8, 8);
	Image->ClearBuffer(BLUEMASK+ALPHAMASK);
	this->MarkForRemoval = false;
	this->Type = AShelter;
};



Shelter::~Shelter()
{
	


};

bool Shelter::Update(Surface* a_Screen, Input* keys)
{
	Image->CopyTo(a_Screen, (int)Xpos, (int)Ypos);
	return false;

}

