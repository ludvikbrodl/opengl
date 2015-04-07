#include "MainGame.h"
#include <iostream>
#include <string>
#include "Errors.h"





MainGame::MainGame() {
	_window = nullptr;
	_screenWidth = 1024;
	_screenHeight = 768;
	_gameState = GameState::PLAY;
	_time = 0.0f;
}


MainGame::~MainGame()
{
}


void MainGame::run() {
	initSystems();

	_sprite.init(-1, -1, 2, 2);

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

	initShaders();
}

void MainGame::initShaders() {
	_colorProgram.compileShaders("Shaders/colorShading.vert", "Shaders/ColorShading.frag");
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexColor");
	_colorProgram.linkShaders();
}


void MainGame::gameLoop() {
	while (_gameState != GameState::EXIT) {
		processInput();
		_time += 0.0005f;
		drawGame();
		//memory leak example, enable and watch your memory blow up (ctrl shift esc in windows and check proc memory)
		//char* str = new char[40000];
		
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

	_colorProgram.use();

	GLuint timeLocation = _colorProgram.getUniformLocation("time");
	glUniform1f(timeLocation, _time);



	_sprite.draw();



	_colorProgram.unuse();

	SDL_GL_SwapWindow(_window);

}