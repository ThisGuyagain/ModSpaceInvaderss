#pragma once

#include "MyFiles.h"
#include "surface.h"
#include "Objects.h"
#include "Input.h"

#define PRINT_AT 1
#define NEWLINE  13


class TileFont
{
public:
	TileFont();
	~TileFont();
	void FontPrint(char*, Surface* mScreen);
	void SetScreenSizes(int height, int width);
	void SetPrintPosition(int PrintX, int PrintY);
	void SetColour(Pixel Col);

private:
	Surface* TheImage;
	int Xpos, Ypos;
	int CharWidth, CharHeight;
	Pixel TextColour;
};

