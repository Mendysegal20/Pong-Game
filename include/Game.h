#pragma once
#include "Constants.h"
#include "SoundManager.h"
#include "GameEvents.h"
#include "Renderer.h"
#include "GameRenderData.h"
//#include <vector>



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
	/*Font iconsFont;*/
	GameStates gameState;
	SoundManager soundManager;
	Renderer renderer;

	int playerScore = 0;
	int cpuScore = 0;
	bool exitBtnClicked = false;
	float waitTime = 0;

	void checkForWinner();
	void checkIfRoundEnded();
	void EventHandler(const GameEvents& renderAction);
	void loadAssets();
	void update();
	void checkForCollisions();
	float calculateAngleCollision(const Paddle& paddle);
	void calculateBallVelocity(const Paddle& paddle);
	void playEndGameSound();
	void restartGame();
	void startGame();
	void startNewRound();
	void increasePaddleBallSpeed();
};


