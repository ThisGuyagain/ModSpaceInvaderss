// very basic tile font display system
#include "TileFont.h"


TileFont::TileFont()
{
	MyFiles* FileHandler = new MyFiles();
 	this->TheImage = new Surface("..//Assets//fontwhite.png", FileHandler);
	delete FileHandler; // we opened some memory, make sure it is reclaimed
}
void TileFont::SetPrintPosition(int PrintX, int PrintY)
{
	this->Xpos = PrintX;
	this->Ypos = PrintY;

}

void TileFont::SetColour(Pixel Col)
{
	TextColour = Col;
}


TileFont::~TileFont()
{

	delete this->TheImage; // we don't need this now

}




void TileFont::FontPrint(char* Text, Surface* mScreen)
{
	// parse the string till you find the terminating 0
	char* TheString = Text;

	while (*Text != 0)
	{
		char Ch = *Text;
		int index = (Ch - 32);
		// now convert index to an offset		
		int X = index % 8;
		int Y = index / 8;
		//	void CopyBox(Surface* Src, int Width, int Height, int srcPitch, int DestX, int DestY);

		TheImage->CopyBox(mScreen, X, Y, 8, 8, mScreen->GetPitch(), Xpos * 8, Ypos * 8, TextColour);
		Xpos++;

		Text++;
	}
	return;
}
void TileFont::SetScreenSizes(int height, int width)
{
	this->CharHeight = height;
	this->CharWidth = width;

}

