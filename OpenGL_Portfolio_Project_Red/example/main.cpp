#include "main.hpp"
#include "al.h"

int main() {
	ExtendedWorld world;

	world.SetWindowAttributes("Example", GLFW_WINDOW, 3, 3, 4, 1377, 768, 56, 128, 46);
	world.Run();
	return 0;
}