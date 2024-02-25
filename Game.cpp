#include "Game.h"
#include "Player.h"
#include "Vec2.h"
#include "RigidBody.h"
#include <vector>

using std::vector;


SDL_Texture* playerTx;
SDL_Rect srcR, dstR;
int r = 50;
const float PI = 3.1415f;

vector<RigidBody*> rbs;
RigidBody* rb = new RigidBody(new Vec2(400.0f, 200.0f), 10.0f, &rbs);
RigidBody* rb1 = new RigidBody(new Vec2(200.0f, 50.0f), 15.0f, &rbs);

Game::Game()
{}
Game::~Game()
{}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = fullscreen*SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVENTS) == 0)
	{
		std::cout << "SDL initialized" << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_SHOWN);
		if (!window)
		{
			std::cout << "Error while creating window: " << SDL_GetError() << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, flags);
		if (!renderer)
		{
			std::cout << "Error while creating renderer: " << SDL_GetError() << std::endl;
		}
		else {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;
	}
	else {
		isRunning = false;
	}

	SDL_Surface* tempSurface = IMG_Load("assets/guy.png");
	playerTx = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (event.button.button == SDL_BUTTON_LEFT)
			new RigidBody(new Vec2(event.button.x, event.button.y), (rand()%10)*3, &rbs);

	default:
		break;
	}
}

void Game::update()
{
	cnt+= deltaTime/1000;
	//std::cout << cnt << std::endl;

	SDL_SetRenderDrawColor(renderer, 255 * (1.0f - sin((float)cnt / 10000)) / 2, 255 * (1.0f - sin((float)cnt / 3333)) / 2, 255 * (1.0f - sin((float)cnt / 5000)) / 2, 255);
	//std::cout << (1.0f-sin((float)cnt / 10000))/2 << std::endl;
	dstR.x = 128;//(1.0f - cos((float)cnt / 1000)) / 2 * 400;
	dstR.y = 128;//(1.0f - sin((float)cnt / 1000)) / 2 * 400;
	dstR.w = 64;
	dstR.h = 64;

	for (int i = 0; i < simulationSubsteps; i++)
	{
		float dt = deltaTime / 1000 / simulationSubsteps;
		for (int r = 0; r < rbs.size(); r++)
		{
			rbs[r]->update(dt);
		}
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);
	// stuff to render
	//SDL_RenderCopy(renderer, playerTx, NULL, &dstR);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	// Draw constraint circle
	circle(rb->constraintCoord->x, rb->constraintCoord->y, rb->constraintR);

	// Draw all RigidBodies
	for (int i = 0; i < rbs.size(); i++)
	{
		circle(rbs[i]->m_pos->x, rbs[i]->m_pos->y, rbs[i]->m_radius);
	}

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned" << std::endl;
}

void Game::circle(int32_t centreX, int32_t centreY, int32_t radius)
{
	const int32_t diameter = (radius * 2);

	int32_t x = (radius - 1);
	int32_t y = 0;
	int32_t tx = 1;
	int32_t ty = 1;
	int32_t error = (tx - diameter);

	while (x >= y)
	{
		//  Each of the following renders an octant of the circle
		SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
		SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
		SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
		SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
		SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
		SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
		SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
		SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

		if (error <= 0)
		{
			++y;
			error += ty;
			ty += 2;
		}

		if (error > 0)
		{
			--x;
			tx += 2;
			error += (tx - diameter);
		}
	}
}

void Game::play()
{
	dtA = SDL_GetTicks();
	deltaTime += dtA - dtB;

	if (deltaTime > 1000 / 60.0f)
	{
		handleEvents();
		update();
		render();

		std::cout << "FPS: " << 1000 / deltaTime << std::endl;

		deltaTime = 0.0f;
	}
	dtB = dtA;
}

