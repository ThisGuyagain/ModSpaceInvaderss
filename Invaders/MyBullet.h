#pragma once
#include "Objects.h"
class MyBullet :
	public Objects
{
public:
	MyBullet();
	~MyBullet();

	MyBullet(char* f, MyFiles* fh);
	bool Update(Surface*, Input*);
	bool TestForHit(Objects* );

};

