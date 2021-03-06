#include "OpenGLESCode.h"








///
// Create a shader object, load the shader source, and
// compile the shader.
//
GLuint LoadShader(GLenum type, const char *shaderSrc)
{
	GLuint shader;
	GLint compiled;
	// Create the shader object
	shader = glCreateShader(type);
	if (shader == 0)
		return 0;
		// Load the shader source
	glShaderSource(shader, 1, &shaderSrc, NULL);
	// Compile the shader
	glCompileShader(shader);
	// Check the compile status
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		GLint infoLen = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
		if (infoLen > 1)
		{
			char* infoLog = (char*) malloc(sizeof(char) * infoLen);
			glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
			fprintf(stderr, "Error compiling shader:\n%s\n", infoLog);
			free(infoLog);
		}
		glDeleteShader(shader);
		return 0;
	}
	return shader;
}


GLuint LoadProgram(char *vertShaderSrc, char *fragShaderSrc)
{
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint programObject;
	GLint linked;

	// Load the vertex/fragment shaders
	vertexShader = LoadShader(GL_VERTEX_SHADER, vertShaderSrc);
	if (vertexShader == 0)
		return 0;

	fragmentShader = LoadShader(GL_FRAGMENT_SHADER, fragShaderSrc);
	if (fragmentShader == 0)
	{
		glDeleteShader(vertexShader);
		return 0;
	}

	// Create the program object
	programObject = glCreateProgram();

	if (programObject == 0)
		return 0;

	glAttachShader(programObject, vertexShader);
	glAttachShader(programObject, fragmentShader);

	// Link the program
	glLinkProgram(programObject);

	// Check the link status
	glGetProgramiv(programObject, GL_LINK_STATUS, &linked);

	if (!linked)
	{
		GLint infoLen = 0;
		glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);

		if (infoLen > 1)
		{
			GLchar* infoLog = (GLchar*)malloc(sizeof(char) * infoLen);

			glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);
			fprintf(stderr, "Error linking program:\n%s\n", infoLog);

			free(infoLog);
		}

		glDeleteProgram(programObject);
		return 0;
	}

	// Free up no longer needed shader resources
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return programObject;
}

///
// Create a simple width x height texture image with four different colors
//
GLuint CreateSimpleTexture2D(int width, int height, char* TheData)
{
	// Texture object handle
	GLuint textureId;

	// Use tightly packed data
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Generate a texture object
	glGenTextures(1, &textureId);

	// Bind the texture object
	glBindTexture(GL_TEXTURE_2D, textureId);

	// Load the texture


	glTexImage2D(GL_TEXTURE_2D,
		0,
		GL_RGBA,
		width,
		height,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		TheData);
	
	if (glGetError() != GL_NO_ERROR) printf("Oh bugger");

	// Set the filtering mode
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


	if (glGetError() == GL_NO_ERROR)	return textureId;
	printf("Oh bugger");

	return textureId;
}


///
// Initialize the shader and program object
//
int Init(CUBE_STATE_T *p_state)
{

	p_state->user_data = malloc(sizeof(UserData));
	UserData *userData = (UserData *)p_state->user_data;
	GLbyte vShaderStr[] =
		"attribute vec4 a_position;   \n"
		"attribute vec2 a_texCoord;   \n"
		"varying vec2 v_texCoord;     \n"
		"void main()                  \n"
		"{                            \n"
		"   gl_Position = a_position; \n"
		"   v_texCoord = a_texCoord;  \n"
		"}                            \n";

	GLbyte fShaderStr[] =
		"precision mediump float;                            \n"
		"varying vec2 v_texCoord;                            \n"
		"uniform sampler2D s_texture;                        \n"
		"void main()                                         \n"
		"{                                                   \n"
		"  gl_FragColor = texture2D( s_texture, v_texCoord );\n"
		"}                                                   \n";

	// Load the shaders and get a linked program object
	userData->programObject = LoadProgram((char*)vShaderStr, (char*)fShaderStr);

	// Get the attribute locations
	userData->positionLoc = glGetAttribLocation(userData->programObject, "a_position");
	userData->texCoordLoc = glGetAttribLocation(userData->programObject, "a_texCoord");

	// Get the sampler location
	userData->samplerLoc = glGetUniformLocation(userData->programObject, "s_texture");

	
	glClearColor(0.0f, 1.0f, 0.0f, 0.5f);
	return GL_TRUE;
}
//
// Draw triangles using the shader pair created in Init()
//

extern void swap();

void Draw(CUBE_STATE_T *p_state)
{

	swap(); // ok move the obuffers



	UserData *userData = (UserData*)p_state->user_data;

	GLfloat vVertices[] = {
		-1.0f,
		1.0f,
		0.0f,  // Position 0
		0.0f,
		0.0f,        // TexCoord 0 
		-1.0f,
		-1.0f,
		0.0f,  // Position 1
		0.0f,
		1.0f,        // TexCoord 1
		1.0f,
		-1.0f,
		0.0f,  // Position 2
		1.0f,
		1.0f,        // TexCoord 2
		1.0f,
		1.0f,
		0.0f,  // Position 3
		1.0f,
		0.0f         // TexCoord 3
	};

	GLushort indices[] = { 0, 1, 2, 0, 2, 3 };

	// Set the viewport
	glViewport(0, 0, p_state->width, p_state->height);

	// Use the program object
	glUseProgram(userData->programObject);

	// Load the vertex position
	glVertexAttribPointer(userData->positionLoc,
		3,
		GL_FLOAT,
		GL_FALSE,
		5 * sizeof(GLfloat),
		vVertices);
	// Load the texture coordinate
	glVertexAttribPointer(userData->texCoordLoc,
		2,
		GL_FLOAT,
		GL_FALSE,
		5 * sizeof(GLfloat),
		&vVertices[3]);

	glEnableVertexAttribArray(userData->positionLoc);
	glEnableVertexAttribArray(userData->texCoordLoc);

	extern int framebufferTexID[2];
	extern int bufferIndex;

	glBindTexture(GL_TEXTURE_2D, framebufferTexID[bufferIndex]);

	// Set the sampler texture unit to 0
	glUniform1i(userData->samplerLoc, 0);
	
	
	glBindTexture(GL_TEXTURE_2D, framebufferTexID[bufferIndex]);

	userData->textureId = framebufferTexID[bufferIndex];
	
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
	//glDrawElements ( GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_SHORT, indices );
	if (glGetError() != GL_NO_ERROR) printf("Oh bugger");
}





void init_ogl(CUBE_STATE_T *state, int width, int height)
{
	
	std::cout << "init openGLES\n";
	int32_t success = 0;
	EGLBoolean result;
	EGLint num_config;



	DISPMANX_ELEMENT_HANDLE_T dispman_element;
	DISPMANX_DISPLAY_HANDLE_T dispman_display;
	DISPMANX_UPDATE_HANDLE_T dispman_update;
	VC_RECT_T dst_rect;
	VC_RECT_T src_rect;

	static const EGLint attribute_list[] =
	{
		EGL_RED_SIZE,
		8,
		EGL_GREEN_SIZE,
		8,
		EGL_BLUE_SIZE,
		8,
		EGL_ALPHA_SIZE,
		8,
		EGL_SURFACE_TYPE,
		EGL_WINDOW_BIT,
		EGL_NONE
	};

	static const EGLint context_attributes[] =
	{
		EGL_CONTEXT_CLIENT_VERSION,
		2,
		EGL_NONE
	};

	EGLConfig config;

	    // get an EGL display connection
	state->display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

	    // initialize the EGL display connection
	result = eglInitialize(state->display, NULL, NULL);

	    // get an appropriate EGL frame buffer configuration
	result = eglChooseConfig(state->display, attribute_list, &config, 1, &num_config);
	assert(EGL_FALSE != result);

	    // get an appropriate EGL frame buffer configuration
	result = eglBindAPI(EGL_OPENGL_ES_API);
	assert(EGL_FALSE != result);


	    // create an EGL rendering context
	state->context = eglCreateContext(state->display, config, EGL_NO_CONTEXT, context_attributes);
	assert(state->context != EGL_NO_CONTEXT);

	    // create an EGL window surface
	success = graphics_get_display_size(0 /* LCD */, &state->width, &state->height);
	assert(success >= 0);

//	state->width = width;
//	state->height = height;

	dst_rect.x = 16;
	dst_rect.y = 16;
	dst_rect.width = state->width;
	dst_rect.height = state->height;

	src_rect.x = 16;
	src_rect.y = 16;
	src_rect.width = state->width << 16;
	src_rect.height = state->height << 16;        

	dispman_display = vc_dispmanx_display_open(0 /* LCD */);
	dispman_update = vc_dispmanx_update_start(0);

	dispman_element = 
	vc_dispmanx_element_add(dispman_update,
		dispman_display,
		0/*layer*/,
		&dst_rect,
		0/*src*/,
		&src_rect,
		DISPMANX_PROTECTION_NONE, 
		0 /*alpha*/,
		0/*clamp*/,
		(DISPMANX_TRANSFORM_T) 0/*transform*/);

	state->nativewindow.element = dispman_element;
	state->nativewindow.width = state->width;
	state->nativewindow.height = state->height;
	vc_dispmanx_update_submit_sync(dispman_update);

	state->surface = eglCreateWindowSurface(state->display, config, &(state->nativewindow), NULL);
	assert(state->surface != EGL_NO_SURFACE);

	    // connect the context to the surface
	result = eglMakeCurrent(state->display, state->surface, state->surface, state->context);
	assert(EGL_FALSE != result);
	

}

void esInitContext(CUBE_STATE_T *p_state)
{
	if (p_state != NULL)
	{
		memset(p_state, 0, sizeof(CUBE_STATE_T));
	}
}

void esRegisterDrawFunc(CUBE_STATE_T *p_state, void(*draw_func)(CUBE_STATE_T*))
{
	p_state->draw_func = draw_func;
}



