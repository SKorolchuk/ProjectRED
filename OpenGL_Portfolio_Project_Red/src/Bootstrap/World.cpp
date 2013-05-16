#include "World.hpp"

World::World() {
	this->internalTime = new GameTime();
	this->isTerminated = false;
}

World::World(const World& copyObj) {
}

void World::Release() {
	// Close OpenGL window and terminate GLFW
	glfwTerminate();
}

void World::UnloadContent() {
	// Cleanup VBO
	glDeleteBuffers(1, &(this->vertexbuffer));
	glDeleteVertexArrays(1, &(this->vertexArrayID));
}

World::~World() {
	this->Release();
	this->UnloadContent();
}

void World::SetWindowAttributes(
	std::string _title,
	int _windowMode,
	int _majorOpenGlVersion,
	int _minorOpenGlVersion,
	int _fsaa,
	int _width,
	int _height,
	int _redInitBits,
	int _greenInitBits,
	int _blueInitBits,
	int _alphaInitBits,
	int _depthInitBits,
	int _stencilInitBits
	) {
		this->majorOpenGlVersion = _majorOpenGlVersion;
		this->fsaa = _fsaa;
		this->minorOpenGlVersion = _minorOpenGlVersion;
		this->width = _width;
		this->height = height;
		this->redInitBits = _redInitBits;
		this->greenInitBits = _greenInitBits;
		this->blueInitBits = _blueInitBits;
		this->alphaInitBits = _alphaInitBits;
		this->depthInitBits = _depthInitBits;
		this->stencilInitBits = _stencilInitBits;
		this->windowMode = _windowMode;
		this->title = _title;
}

void World::Initialize() {
	if( !glfwInit() )
	{
		throw std::exception("Failed to initialize GLFW\n");
	}

	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, this->fsaa);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, this->majorOpenGlVersion);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, this->minorOpenGlVersion);
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	if( !glfwOpenWindow( this->width,
							this->height,
							this->redInitBits,
							this->greenInitBits,
							this->blueInitBits,
							this->alphaInitBits, 
							this->depthInitBits, 
							this->stencilInitBits,
							this->windowMode) )
	{
		glfwTerminate();
		throw std::exception("Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
	}

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		throw std::exception("Failed to initialize GLEW\n");
	}

	glfwSetWindowTitle( this->title.data() );

	// Ensure we can capture the escape key being pressed below
	glfwEnable( GLFW_STICKY_KEYS );

	// Dark background
	glClearColor(
			(float)this->redInitBits / 255,
			(float)this->greenInitBits / 255,
			(float)this->blueInitBits / 255,
			(float)this->alphaInitBits / 255
		);
}

void World::LoadContent() {
	glGenVertexArrays(1, &(this->vertexArrayID));
	glBindVertexArray(this->vertexArrayID);

	// Create and compile our GLSL program from the shaders
	this->programID  = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );

	GLfloat g_vertex_buffer_data[] = { 
		-0.3f, -1.0f, 0.0f,
		 1.0f, -1.2f, 0.0f,
		 0.0f,  1.0f, 0.0f,
	};

	glGenBuffers(1, &(this->vertexbuffer));
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_DYNAMIC_DRAW);
}

void World::Update(GameTime *time) {
}

void World::Draw(GameTime *time) {
	// Clear the screen
		glClear( GL_COLOR_BUFFER_BIT );

		// Use our shader
		glUseProgram(this->programID);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle

		glDisableVertexAttribArray(0);

		// Swap buffers
		glfwSwapBuffers();
}

void World::Exit() {
	this->isTerminated = true;
}

void World::ResetTime() {
	this->internalTime->Start();
}

void World::Tick() {
	this->Update(this->internalTime);
	this->Draw(this->internalTime);
}

void World::Run() {
	this->Initialize();
	this->LoadContent();
	this->ResetTime();
	do {
		this->Tick();
	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
			glfwGetWindowParam( GLFW_OPENED ) && !this->isTerminated );
	this->UnloadContent();
	this->Release();
}