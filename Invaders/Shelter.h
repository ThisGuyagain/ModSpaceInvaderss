#pragma once
#include "Objects.h"

using namespace std;
class Shelter :
	public Objects
{
public:
	Shelter();
	~Shelter();

	bool Update(Surface*, Input*);
	bool TestForHit(Objects*);

};