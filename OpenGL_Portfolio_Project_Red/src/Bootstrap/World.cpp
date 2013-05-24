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

void World::LoadContent() {
}

void World::UnloadContent() {
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

void World::Update(GameTime *time) {
}

void World::Draw(GameTime *time) {
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