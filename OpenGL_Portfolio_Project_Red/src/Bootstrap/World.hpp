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

#include "IInitializable.hpp"

class World : IInitializable {
public:
	World();
	World(const World& copyObj);
	~World();
	virtual void Exit();
	virtual void ResetTime();
	virtual void Run();
	virtual void Tick();
	void SetWindowAttributes(
		std::string _title,
		int _windowMode = GLFW_WINDOW,
		int _majorOpenGlVersion = 3,
		int _minorOpenGlVersion = 3,
		int _fsaa = 4,
		int _width = 1024,
		int _height = 768,
		int _redInitBits = 0,
		int _greenInitBits = 0,
		int _blueInitBits = 0,
		int _alphaInitBits = 0,
		int _depthInitBits = 32,
		int _stencilInitBits = 0
		);
protected:
	virtual void Initialize();
	virtual void LoadContent();
	virtual void UnloadContent();
	virtual void Update(GameTime*);
	virtual void Draw(GameTime*);
	virtual void Release();
private:
	int fsaa;
	int majorOpenGlVersion;
	int minorOpenGlVersion;
	int width;
	int height;
	int redInitBits;
	int greenInitBits;
	int blueInitBits;
	int alphaInitBits;
	int depthInitBits;
	int stencilInitBits;
	int windowMode;
	bool isTerminated;
	GameTime* internalTime;
	GLuint vertexArrayID;
	GLuint programID;
	GLuint vertexbuffer;
	std::string title;
};