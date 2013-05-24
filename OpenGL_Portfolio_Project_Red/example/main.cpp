#include "main.hpp"
#include "al.h"

int main() {
	ExtendedWorld world;

	world.SetWindowAttributes("Example", GLFW_WINDOW, 3, 3, 4, 320, 240);
	world.Run();
	return 0;
}