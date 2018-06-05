#pragma once

#include "MyFiles.h"
#include "surface.h"
#include "Objects.h"
#include "Input.h"



class Shooter :public Objects
{
public:
	Shooter();
	Shooter(char* f, MyFiles* fh);
	

	~Shooter();


	bool Update(Surface*,Input*);


};