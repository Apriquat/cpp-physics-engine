#pragma once

#include "SDL.h"
#undef main
#include "SDL_image.h"
#include <iostream>

class Game
{

public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	void render();
	void clean();

	void play();

	bool running() { return isRunning; }
	int getCnt() { return cnt; }

	double deltaTime;

private:
	float cnt = 0.0f;
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
	void circle(int32_t centreX, int32_t centreY, int32_t radius);

	double dtA, dtB = 0;

	static const int simulationSubsteps = 3;
};

