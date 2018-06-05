#pragma once

#include "math.h"
#include "stdlib.h"
#include "MyFiles.h"
#include <vector>
#include "surface.h"
#include "Input.h"

inline float Rand(float a_Range) { return ((float)rand() / RAND_MAX) * a_Range; }
enum Types {
	Bullet,
	Missile1,
	Missile2,
	Alien,
	AShooter,
	AShelter
};

class Objects
{


public:
	Objects();
	Objects(char*, MyFiles*);
	Objects(Surface* a_Image);
	~Objects();

	static std::vector<Surface*> AnimFrames;

	std::vector<int> FrameIndexes;

	static  int NumberOfObjectsCreated;

	int OBJID;
	int AnimationCount;
	Types Type;
	float Xpos, Ypos;
	float Xspeed, Yspeed;

	bool MarkForRemoval;
	virtual bool Update(Surface* s,Input* InputHandler);

	static int AddToList(Surface* Image);

	Surface* Image;



};

