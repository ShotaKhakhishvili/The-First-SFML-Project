#include "Game.h"
#include <Windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Game game("properties.txt");

	game.run();
}

int main()
{
    Game game("properties.txt");

    game.run();
}