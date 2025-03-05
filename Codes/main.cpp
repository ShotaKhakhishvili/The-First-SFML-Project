#include "Game.h"
#include <Windows.h>

void logMessage(const std::string& msg)
{
	static std::ofstream log("log.txt", std::ios::app);
	log << msg << std::endl;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Game game("properties.txt");

	game.run();
}