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
	Sound gameOverSound;
	Sound winningSound;
	GameStates gameState;

	int playerScore;
	int cpuScore;
	bool isGameOverSoundPlayed;

	void checkForWinner();
	void loadAssets();
	void update();
	void updateScore();
	void render();
	void drawWinner(const char* winner);
	bool isBallCollide(Paddle paddle);
	void checkForCollisions();
	float calculateAngleCollision(Paddle paddle);
	void calculateBallVelocity(Paddle paddle);
	void playEndGameSound();
	


public:
	
	Game();
	~Game();
	void init();
	void run();

};















