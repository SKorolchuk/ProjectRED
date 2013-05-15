#include "main.hpp"

int main()
{
	Initializer initObject("Project");

	
	initObject.InitializeDrawData();

	return initObject.MainLoop();
}