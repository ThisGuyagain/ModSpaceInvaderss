
#include "Game.h"
#include <string.h>

#define TIMEPERSTEP 10
#define SIZEOFSTEP 4

Game::Game()
{
	InitDone = false;
	
}
Game::~Game()
{
// make sure everything is cleared out	
}

extern std::vector<Objects*> MyObjects;

TileFont* Font;



void Game::Update(float DTime, MyFiles* a_FileHandler, Input* a_InputHandler,Surface* a_Screen)
{
	if (this->InitDone == false)
	{
		Init(a_FileHandler);

		Direction = Right;
	}


	char buffer[50];
	int n, a = 5, b = 3;
	n = sprintf(buffer, "Score %04d Kills %d", Score,this->AlienCount);
	buffer[n] = 0; //ensure we have a 0 in there


	// draw the text to screen
	Font.SetPrintPosition(12,1);
	Font.SetColour(GREENMASK + REDMASK + ALPHAMASK);
	Font.FontPrint(buffer, a_Screen);

	Directions ShallWeChange = Direction; // keep track of the current Direction
	if (--StepTime == 0) StepTime = TIMEPERSTEP;

	if (StepTime == TIMEPERSTEP)
	{
		for (int i = 0; i < MyObjects.size(); i++)
		{
			if (MyObjects[i]->Type == Alien)
			{
				float Xstep = 0;
				float Ystep = 0;

				switch (Direction)
				{
				case Left:
					Xstep = -SIZEOFSTEP;
					if (MyObjects[i]->Xpos < SIZEOFSTEP) ShallWeChange = Right;
					break;

				case Right:
					Xstep = SIZEOFSTEP;
					if (MyObjects[i]->Xpos > SCRWIDTH - MyObjects[i]->Image->GetWidth() - SIZEOFSTEP) ShallWeChange = Left;
					break;

				case Down:
					Ystep = 2;
					break;
				default:
					printf("Huston, we have a problem");
					break;
				}
				MyObjects[i]->Xpos += Xstep;
				MyObjects[i]->Ypos += Ystep;
			}
		}

		if (ShallWeChange != Direction)
		{

			Direction = Down;
			SavedDirectionToChangeTo = ShallWeChange;
			NumberOfDownSteps = 4;

		}
		else
			if (Direction == Down)
			{
				NumberOfDownSteps--;
				if (NumberOfDownSteps == 0)
				{
					ShallWeChange = SavedDirectionToChangeTo;
					Direction = SavedDirectionToChangeTo; // we've moved down, so give it the saved direction
				}
			}

	}

	for (int i = 0; i < MyObjects.size(); i++)
	{ // update loop
		bool WantToDropBombs = MyObjects[i]->Update(a_Screen, a_InputHandler);
		if (WantToDropBombs == true)
		{
			MyBullet* b = new MyBullet(Rand(100)>90 ? (char*)"..//Assets//invaders//vertical_line.png" : (char*)"..//Assets//invaders//wiggly-missile.png", a_FileHandler);
			b->Type = Missile1;
			b->Yspeed = 1; // give it a speed
			MyObjects.push_back(b);
			b->Xpos = MyObjects[i]->Xpos + 4;
			b->Ypos = MyObjects[i]->Ypos + 6;
		}

	// ok lets get the bombs to test if they hit the shooter?
		if (MyObjects[i]->Type == Missile1)
		{
			MyBullet* b = (MyBullet*)MyObjects[i];



			if (b->TestForHit(Bob))
			{
				printf("I'm hit\n");
			}

			
		}

// if we have a bullet check if it hit anything		
		if (Bullet && Bullet->MarkForRemoval == false)
			{
				if (MyObjects[i] != Bullet && MyObjects[i]->MarkForRemoval == false)
				{
					if (Bullet->TestForHit(MyObjects[i]))
					{
						MyObjects[i]->MarkForRemoval = true;
						Bullet->MarkForRemoval = true;

						if (MyObjects[i]->Type == Alien) Score += (10 + Multiplier) ; // only add for aliens
					}
				} // if !Bullet

	// did we hit a shelter
				for (int i = 0; i < 16; i++)
				{
					if (Shelters[i] != NULL && Bullet->TestForHit(Shelters[i]))
					{
						Shelters[i]->MarkForRemoval = true;
						Bullet->MarkForRemoval = true;
					}
					

				}

			} // if Bullet

	} // update loop
	

	// Update the Shelters looping 16 times
	for (int i = 0; i < 16; i++)
	{
		if (Shelters[i] != NULL) Shelters[i]->Update(a_Screen, a_InputHandler);
	}


 bool WantToFire =	Bob->Update(a_Screen, a_InputHandler);

 if (WantToFire)
 {
	 // do we have a bullet in flight?
	 if (Bullet == NULL)
	 {// ok lets make a new bullet

		 printf("We fired a bullet/n");
		 Bullet = new MyBullet((char*)"..//Assets//invaders8x8//bullet.png", a_FileHandler);
		 Bullet->Yspeed = -4; // give it a speed
		 MyObjects.push_back(Bullet); 
		 Bullet->Xpos = Bob->Xpos+4;
		 Bullet->Ypos = Bob->Ypos - 12;

	 }
 }



 // scan for a clear up
 for (int i = MyObjects.size()-1; i >= 0; i--)
 {
	 if (MyObjects[i]->MarkForRemoval)
	 {
		 printf("removed/n");
		 if (MyObjects[i] == Bullet) Bullet = NULL;

		 if (MyObjects[i]->Type == Alien)
		 {
			 AlienCount--;
			 if (AlienCount == 0)
			 {
				 Multiplier += 1;

				 InitDone = false; // force a new level
			 }
		 }
		 delete(MyObjects[i]);
		 MyObjects.erase(MyObjects.begin() + i);
		 i--;
	 }
 }

 // scan for a shelter clean up
 for (int i = 0; i < 16; i++)
 {
	 if (Shelters[i] != NULL && Shelters[i]->MarkForRemoval)
	 {
		 printf("removed Shelter/n");
		 delete Shelters[i]; // delete the instance of object
		 Shelters[i] = NULL;
	 }
 }





} // update 


bool Game::Init(MyFiles* a_FileHandler)
{
	int imageWidth, imageHeight;
	StepTime = TIMEPERSTEP;
	AlienCount = 0;

#define PRELOAD 

#ifdef PRELOAD
	char* Names1[] =
	{
		(char*)"..//Assets//invaders8x8//InvaderA-1.png",
		(char*)"..//Assets//invaders8x8//InvaderB-1.png",
		(char*)"..//Assets//invaders8x8//InvaderC-1.png",
	
	};

	char* Names2[] =
	{
		(char*)"..//Assets//invaders8x8//InvaderA-2.png",
		(char*)"..//Assets//invaders8x8//InvaderB-2.png",
		(char*)"..//Assets//invaders8x8//InvaderC-2.png"
	};

	Surface* Images1[5];
	Surface* Images2[5];
	for (int i = 0; i < 3; i++)
	{
		Surface* s = new Surface(Names1[i], a_FileHandler);
		Images1[i] = s;
		// reload s
		s = new Surface(Names2[i], a_FileHandler);
		Images2[i] = s;
	}
// rearrange things because we have 3 images to fill 5 rows.
	Images1[4] = Images1[2];
	Images1[3] = Images1[2];
	Images1[2] = Images1[1];

	Images2[4] = Images2[2];
	Images2[3] = Images2[2];
	Images2[2] = Images2[1];

	for (int i = 0; i < 5; i++)
	{
		for (int x = 0; x < 11; x++)
		{
			Aliens* T = new Aliens(Images1[i], Images2[i]);
			T->Xpos = (x * 11) + 5;
			T->Ypos = (i * 11) + 40;
			MyObjects.push_back(T);
			AlienCount++; // keep track of how many we create so we can tell when they are all dead
		}
	}

#else

	for (int i = 0; i < 5; i++)
	{
		for (int x = 0; x < 11; x++)
		{
			Aliens* T = new Aliens(i, a_FileHandler);
			T->Xpos = (x * 11) + 5;
			T->Ypos = (i * 11) + 40;
			MyObjects.push_back(T);
			AlienCount++; // keep track of how many we create so we can tell when they are all dead
		}
	}


#endif

	Bob = new Shooter((char*)"..//Assets//invaders8x8//shooter.png", a_FileHandler);
	Bob->Xpos = SCRWIDTH / 2 + 16;
	Bob->Ypos = SCRHEIGHT- 48;

	Bullet = NULL; // make sure it is nulled
	
// now lets make 4 barriers using 4 squares.. so thats a total of 16

// becuase these are not at equidistant points lets keep a simple table of x locations to place them
#define BARRIER1  32
#define BARRIER2  BARRIER1+64
#define BARRIER3  BARRIER2+64
#define BARRIER4  BARRIER3+64

	int BarrierPositions[] = {
		BARRIER1, BARRIER1 + 9, BARRIER1 + 18, BARRIER1 + 27,
		BARRIER2, BARRIER2 + 9, BARRIER2 + 18, BARRIER2 + 27,
		BARRIER3, BARRIER3 + 9, BARRIER3 + 18, BARRIER3 + 27,
		BARRIER4, BARRIER4 + 9, BARRIER4 + 18, BARRIER4 + 27
	};

	for (int i = 0; i < 16; i++)
	{
		Shelter* s = new Shelter();
		s->Xpos =  BarrierPositions[i]; // use the counter as an index
		s->Ypos = SCRHEIGHT - 48 - 16;
		s->Type = AShelter;
		s->MarkForRemoval = false;
		Shelters[i] = s;

	}

	Score = 0;


	InitDone = true;
	return true;
}
	
