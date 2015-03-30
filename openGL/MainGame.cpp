#include "MainGame.h"
#include <iostream>
#include <string>

void fatalError(std::string errorString) {
	std::cout << errorString << std::endl;
	std::cout << "Enter any key to quit...";
	int tmp;
	std::cin >> tmp;
	SDL_Quit();
	exit(1);
}


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

	//open a opengl window.
	_window = SDL_CreateWindow("SUPER Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight
		, SDL_WINDOW_OPENGL);
	//error control
	if (_window == nullptr) {
		fatalError("SDL Window failed to create!");
	}

	//start GL context.
	SDL_GLContext glContex = SDL_GL_CreateContext(_window);
	//error control
	if (glContex == nullptr) {
		fatalError("SDL_GL context could not be created!");
	}

	GLenum error = glewInit();
	if (error != GLEW_OK) {
		fatalError("Could not initialize glew!");
	}

	//double buffer=one drawing buffer, one clearing buffer -> to avoid flickering.
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//set background color
	glClearColor(0.2f, 0.5f, 0.7f, 1.0f);

}

void MainGame::gameLoop() {
	while (_gameState != GameState::EXIT) {
		processInput();
		drawGame();
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

void MainGame::drawGame() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	SDL_GL_SwapWindow(_window);

}