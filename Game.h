#pragma once
#include "Constants.h"
#include "SoundManager.h"
#include "Renderer.h"
#include "GameRenderData.h"




class Game
{
public:

	Game();
	~Game();
	void init();
	void run();


private:

	Ball ball;
	Paddle player;
	CpuPaddle cpuPaddle;
	Texture2D background;
	Font font;
	GameStates gameState;
	SoundManager soundManager;
	Renderer renderer;

	int playerScore = 0;
	int cpuScore = 0;

	void checkForWinner();
	void checkIfRoundEnded();
	void checkForClickedButtons(const RendererActions& renderAction);
	void loadAssets();
	void update();
	void checkForCollisions();
	float calculateAngleCollision(const Paddle& paddle);
	void calculateBallVelocity(const Paddle& paddle);
	void playEndGameSound();
	void restartGame();
};


