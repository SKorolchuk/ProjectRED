// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GL/glfw.h>

// Include GLM
#include <glm/glm.hpp>
using namespace glm;

#include <src/Common/shader.hpp>

// Include Boost Libs
#include <boost\foreach.hpp>

class Initializer {
public:
	Initializer(std::string _title,
							int _windowMode = GLFW_WINDOW,
							int _majorOpenGlVersion = 3,
							int _minorOpenGlVersion = 3,
							int _FSAA = 4,
							int _width = 1024,
							int _height = 768,
							int _redInitBits = 0,
							int _greenInitBits = 0,
							int _blueInitBits = 0,
							int _alphaInitBits = 0,
							int _depthInitBits = 32,
							int _stencilInitBits = 0);
	~Initializer();
	void BoostTest() const;
	void InitializeWindow() const;
	void InitializeDrawData();
	int MainLoop() const;
private:
	int FSAA;
	int OPENGL_MAJOR_VERSION;
	int OPENGL_MINOR_VERSION;
	int width;
	int height;
	int redInitBits;
	int greenInitBits;
	int blueInitBits;
	int alphaInitBits;
	int depthInitBits;
	int stencilInitBits;
	int windowMode;
	GLuint VertexArrayID;
	GLuint programID;
	GLuint vertexbuffer;
	std::string title;
};