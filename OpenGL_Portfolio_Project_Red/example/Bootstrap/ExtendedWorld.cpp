#include "ExtendedWorld.hpp"

ExtendedWorld::ExtendedWorld() {
	World::World();
}

ExtendedWorld::ExtendedWorld(const ExtendedWorld& copyObj){
	World::World(copyObj);
}

ExtendedWorld::~ExtendedWorld(){
	World::~World();
}

void ExtendedWorld::LoadContent() {
	World::LoadContent();
	glGenVertexArrays(1, &(this->vertexArrayID));
	glBindVertexArray(this->vertexArrayID);

	// Create and compile our GLSL program from the shaders
	this->programID  = LoadShaders("D:\\GIT\\ProjectRED\\OpenGL_Portfolio_Project_Red\\example\\Shaders", "SimpleVertexShader.glsl", "SimpleFragmentShader.glsl" );

	GLfloat g_vertex_buffer_data[] = {
		 0.0f, 0.0f, 0.0f,
		 1.0f, 1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f,
		 -1.0f, -1.0f, 0.0f,
		 0.0f, 0.5f, 0.0f,
		 0.5f,  1.0f, 0.0f,
	};

	glGenBuffers(1, &(this->vertexbuffer));
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_DYNAMIC_DRAW);
}

void ExtendedWorld::UnloadContent() {
	World::UnloadContent();
	// Cleanup VBO
	glDeleteBuffers(1, &(this->vertexbuffer));
	glDeleteVertexArrays(1, &(this->vertexArrayID));
}

void ExtendedWorld::Update(GameTime *time) {
	World::Update(time);
}

void ExtendedWorld::Draw(GameTime *time) {
	World::Draw(time);
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
		glDrawArrays(GL_LINE_LOOP, 0, 6); // 3 indices starting at 0 -> 1 triangle
		 // 3 indices starting at 0 -> 1 triangle

		glDisableVertexAttribArray(0);

		// Swap buffers
		glfwSwapBuffers();
}