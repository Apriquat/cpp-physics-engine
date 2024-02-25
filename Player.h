#pragma once
#include "SDL.h"
#undef main
#include "SDL_image.h"

class Player
{

public:
	Player(float xpos, float ypos);
	~Player();

	void phys();
	void draw();

	void setTexture(SDL_Texture* tx) { texture = tx; }

private:
	float x, y;
	SDL_Texture* texture;
	int txW, txH;
};

