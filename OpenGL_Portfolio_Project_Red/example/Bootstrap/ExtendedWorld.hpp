#include "src\Bootstrap\World.hpp"
#include <vector>

class ExtendedWorld : public World {
public:
	ExtendedWorld();
	ExtendedWorld(const ExtendedWorld& copyObj);
	~ExtendedWorld();
protected:
	virtual void LoadContent();
	virtual void UnloadContent();
	virtual void Update(GameTime*);
	virtual void Draw(GameTime*);
private:
	GLuint vertexArrayID;
	GLuint programID;
	GLuint vertexbuffer;
	GLuint colorbuffer;
	GLuint MatrixId;
	glm::mat4 Projection;
	glm::mat4 View;
	glm::mat4 Model;
	glm::mat4 MVP;
};