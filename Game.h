#pragma once
#include "Constants.h"
#include "Ball.h"
#include "Paddle.h"
#include "CpuPaddle.h"

enum GameStates
{
	NoWinner,
	PlayerWon,
	CpuWon
};


class Game
{
	Ball ball;
	Paddle player;
	CpuPaddle cpuPaddle;
	Texture2D backgroundTexture;
	Font font;
	GameStates gameState;

	int playerScore;
	int cpuScore;

	void checkForWinner();
	void loadAssets();
	void draw();
	void update();
	void updateScore();
	void render();
	void drawWinner(const char* winner);
	void checkForCollisions();
	


public:
	
	Game();
	~Game();
	void init();
	void run();

};















