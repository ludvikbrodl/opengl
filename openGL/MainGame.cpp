#include "MainGame.h"
#include <iostream>


MainGame::MainGame()
{
	_window = nullptr;
	_screenWidth = 1024;
	_screenHeight = 768;
	_gameState = GameState::PLAY;
}


MainGame::~MainGame()
{
}


void MainGame::run() {
	initSystems();
	gameLoop();

}

void MainGame::initSystems() {
	SDL_Init(SDL_INIT_EVERYTHING);

	_window = SDL_CreateWindow("SUPER Window, SDL_P", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight
		, SDL_WINDOW_OPENGL);

}

void MainGame::gameLoop() {
	while (_gameState != GameState::EXIT) {
		processInput();
	}

}

void MainGame::processInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {

			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
			case SDL_MOUSEMOTION:
				std::cout << event.motion.y << " " << event.motion.y << std::endl;
				break;
			default:
				break;
		}
	}

}