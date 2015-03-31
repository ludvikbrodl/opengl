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

	_sprite.init(-1, -1, 1, 1);

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
				std::cout << event.motion.x << " " << event.motion.y << std::endl;
				break;
			default:
				break;
		}
	}

}

//Draw the game scene with OpenGL
void MainGame::drawGame() {
	//Base depth to 
	glClearDepth(1.0);
	//Clear color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//draw triangle the retarded way
	//glEnableClientState(GL_COLOR_ARRAY);
	/*
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(0, 0);
	glVertex2f(0, 1);
	glVertex2f(1, 1);
	glEnd();
	*/
	

	_sprite.draw();

	SDL_GL_SwapWindow(_window);

}