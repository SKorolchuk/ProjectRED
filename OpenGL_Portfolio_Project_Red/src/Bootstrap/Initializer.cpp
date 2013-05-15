#include "Initializer.hpp"

Initializer::Initializer(std::string _title,
							int _windowMode,
							int _majorOpenGlVersion,
							int _minorOpenGlVersion,
							int _FSAA,
							int _width,
							int _height,
							int _redInitBits,
							int _greenInitBits,
							int _blueInitBits,
							int _alphaInitBits,
							int _depthInitBits,
							int _stencilInitBits):
		OPENGL_MAJOR_VERSION(_majorOpenGlVersion),
		FSAA(_FSAA),
		OPENGL_MINOR_VERSION(_minorOpenGlVersion),
		width(_width),
		height(height),
		redInitBits(_redInitBits),
		greenInitBits(_greenInitBits),
		blueInitBits(_blueInitBits),
		alphaInitBits(_alphaInitBits),
		depthInitBits(_depthInitBits),
		stencilInitBits(_stencilInitBits),
		windowMode(_windowMode),
		title(_title)
		{
			this->InitializeWindow();
}

Initializer::~Initializer() {
	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	// Cleanup VBO
	glDeleteBuffers(1, &(this->vertexbuffer));
	glDeleteVertexArrays(1, &(this->VertexArrayID));
}

void Initializer::BoostTest()
	const {
	std::string greetings("Hello World!");

	BOOST_FOREACH( char character, greetings)
	{
		std::cout << character << std::endl;
	}
}

void Initializer::InitializeWindow() const {
	if( !glfwInit() )
	{
		throw std::exception("Failed to initialize GLFW\n");
	}

	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, this->FSAA);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, this->OPENGL_MAJOR_VERSION);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, this->OPENGL_MINOR_VERSION);
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
		fprintf(stderr, "Failed to initialize GLEW\n");
		throw std::exception("Failed to initialize GLEW\n");
	}

	glfwSetWindowTitle( this->title.data() );

	// Ensure we can capture the escape key being pressed below
	glfwEnable( GLFW_STICKY_KEYS );

	// Dark blue background
	glClearColor(0.1f, 0.2f, 0.4f, 0.4f);

}

void Initializer::InitializeDrawData() {
	glGenVertexArrays(1, &(this->VertexArrayID));
	glBindVertexArray(this->VertexArrayID);

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

int Initializer::MainLoop() const {
	do{

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

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
		   glfwGetWindowParam( GLFW_OPENED ) );

	return 0;
}