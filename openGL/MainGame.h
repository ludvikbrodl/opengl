#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>
#include "GLSLProgram.h"

#include <Sprite.h>

enum class GameState {PLAY, EXIT};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();


private:
	void initShaders();
	void initSystems();
	void gameLoop();
	void processInput();
	void drawGame();

	SDL_Window* _window;
	int _screenWidth;
	int _screenHeight;
	GameState _gameState;

	Sprite _sprite;

	GLSLProgram _colorProgram;

	float _time;
};

