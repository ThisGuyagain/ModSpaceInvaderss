/*
 * code based on standard OpenGL examples 
 * including OpenGL ES 2.0 Programming Guide
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <sys/time.h>
#include <vector>

#ifdef RASPBERRY
#include "bcm_host.h"
#endif

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include "MyFiles.h"
#include "surface.h"
#include "Objects.h"
#include "OpenGLESCode.h"
#include "Game.h"

typedef unsigned long Pixel;
	


Input TheInput;

vector<Surface*> AnimFrames;

// from esUtil.h
#define TRUE 1
#define FALSE 0


int imageWidth;
int imageHeight;



GLuint framebufferTexID[2];

Pixel* Locations[2];
void* framedata = 0;
int bufferIndex = 0; // this is the working buffer


uint32_t scr_width, scr_height;
Surface* m_Screen;
std::vector<Objects*> MyObjects; // all our game objects are held here for rendering.
Game* TheGame;
MyFiles* FileHandler;

// we're not really creating buffers
bool createFBtexture()
{
	Locations[0] = (Pixel*)malloc(SCRWIDTH * SCRHEIGHT * 4);
	Locations[1] = (Pixel*)malloc(SCRWIDTH * SCRHEIGHT * 4);
	//set it all to black
	memset(Locations[0], 255, SCRWIDTH * SCRHEIGHT * 4);
	memset(Locations[1], 123, SCRWIDTH * SCRHEIGHT * 4);

	m_Screen = new Surface(SCRWIDTH, SCRHEIGHT, Locations[0]); // make our target screen
	m_Screen->SetPitch(SCRWIDTH);

	// addition to the book, lets clear them with colour so we can seem them swapping
	m_Screen->ClearBuffer(REDMASK + ALPHAMASK); // we have to add the alpha mask so we don't get invisible
	m_Screen->SetBuffer(Locations[1]);
	m_Screen->ClearBuffer(BLUEMASK + ALPHAMASK);
	m_Screen->SetBuffer(Locations[0]);

	
}

bool swap()
{


	bufferIndex++;
	bufferIndex = bufferIndex % 2;
	glDeleteTextures(1, &framebufferTexID[bufferIndex]); //delete the old texture (displayed 1 frame ago)
	 
	framebufferTexID[bufferIndex] = CreateSimpleTexture2D(SCRWIDTH, SCRHEIGHT, (char*)m_Screen->GetBuffer());
	m_Screen->SetBuffer(Locations[bufferIndex]);	// forgot to re-add in the book though it won't actually make any difference since we have an OpenGLES back buffer

}

CUBE_STATE_T state, *p_state = &state;


void  esMainLoop(CUBE_STATE_T *esContext)
{
	struct timeval t1, t2;
	struct timezone tz;
	float deltatime;
	float totaltime = 0.0f;
	unsigned int frames = 0;

	gettimeofday(&t1, &tz);
	static int ycoord = 0;
	while (1)
	{

	

		gettimeofday(&t2, &tz);
		deltatime = (float)(t2.tv_sec - t1.tv_sec + (t2.tv_usec - t1.tv_usec) * 0.0000001f);
		t1 = t2;

		if (esContext->draw_func != NULL)
			esContext->draw_func(esContext);

	
		eglSwapBuffers(esContext->display, esContext->surface);

		m_Screen->ClearBuffer(0xff000000);
		TheGame->Update(deltatime, FileHandler, &TheInput, m_Screen);
	
		if (TheInput.TestKey(KEY_A) != FALSE)
			printf("WTF");

		totaltime += deltatime;
		frames++;
		if (totaltime >  1.0f)
		{
			printf("%4d frames rendered in %1.4f seconds -> FPS=%3.4f\n", frames, totaltime, frames / totaltime);
			totaltime -= 1.0f;
			frames = 0;
		}


	}
}



int main(int argc, char *argv[])
{
	UserData user_data;

	bcm_host_init();
	
	graphics_get_display_size(0,
			&scr_width,
			&scr_height);
	
	
	
	TheInput.Init();

	bool quitloop = false;





	FileHandler = new MyFiles();
	printf("filehandler set up\n");




	esInitContext(p_state);
	init_ogl(p_state, scr_width, scr_height);

	createFBtexture();

	TheGame = new Game();

	


	p_state->user_data = &user_data;

	if (!Init(p_state))
		return 0;
	esRegisterDrawFunc(p_state, Draw);
	eglSwapBuffers(p_state->display, p_state->surface);



	esMainLoop(p_state);
}
 