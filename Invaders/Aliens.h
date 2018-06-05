


#pragma once

#include "MyFiles.h"
#include "surface.h"
#include "Objects.h"

#define TICKCOUNT 15

class Aliens :public Objects
{
public:
	Aliens();
	Aliens( int Type, MyFiles* fh);
	Aliens(char* fName, MyFiles* fh);
	Aliens(Surface* S1, Surface* S2);
	~Aliens();

	int TickForAnim; 
	int CurrentAnim; //0 or 1


	bool Update(Surface*, Input*); // the update we override needs both params even if we don't use Input

	Surface* Image1;
	Surface* Image2;

};