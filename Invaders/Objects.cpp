#include "Objects.h"





Objects::Objects()
{
	MarkForRemoval = false;
	
}


Objects::Objects(char* Filename, MyFiles* FileHandler)
{
	Image = new Surface(Filename, FileHandler);
	
	MarkForRemoval = false;


}

Objects::Objects(Surface* a_Image)
{
	Image = a_Image;

	MarkForRemoval = false;
}

Objects::~Objects()
{
//	delete Image;
	Image = 0;
}

bool Objects::Update(Surface* TheScreen, Input* InputHandeler)
{

	Image->CopyAlphaPlot(TheScreen, (int)Xpos, (int)Ypos);

}

 int Objects::AddToList(Surface* Image)
{
	

		
	return 0; // let any routine know the index

}
