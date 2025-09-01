#include "Game.h"
#include <cmath>
#define WINNING_SCORE 2


Game::Game() :
    ball(middleScreenX, middleScreenY, ballSpeedX, ballSpeedY, radius),
    player(paddlePosX, paddlePosY, paddleWidth, paddleHeight, paddleSpeed),
    cpuPaddle(cpuPaddlePosX, paddlePosY, paddleWidth, paddleHeight, paddleSpeed),
    background({ 0 }),
    font({ 0 }),
    playerScore(0),
    cpuScore(0),
    gameState(GameStates::NoWinner) {}



Game::~Game()
{
    UnloadFont(font);
	UnloadTexture(background);
}



void Game::init()
{   
    InitWindow(windowWidth, windowHeight, "Pongi pongo");
    SetTargetFPS(60);
    loadAssets();
}



void Game::loadAssets()
{
    Image image = LoadImage(bgPath);
    background = LoadTextureFromImage(image);
    UnloadImage(image);
    font = LoadFontEx(fontPath, fontSize, 0, 0);
}



void Game::run()
{
    
    while (!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        switch (gameState)
        {

            case NoWinner:
                update();
                checkForCollisions();
                checkForWinner();
                break;
            
            case PlayerWon:
            case CpuWon:
                playEndGameSound();
                break;
        }
        
		// DataFrame{...} replaces the need to call the constructor.
		// it creates a temporary object that is passed to the function
        renderer.renderFrame(DataFrame{ background, font, ball, player, 
                                        cpuPaddle, playerScore, 
                                        cpuScore, gameState });

        EndDrawing();
    }

    CloseWindow();
}




void Game::update()
{
    ball.update();
    player.update();
    cpuPaddle.update(ball.velocity.x, ball.getX(), ball.getY());
    checkIfRoundEnded();
}




void Game::checkIfRoundEnded()
{
    if (ball.getX() >= windowWidth) // cpu wins
    {
		cpuScore++;
		soundManager.playLosingRoundSound();
        ball.resetBall();
    }
        
    else if (ball.getX() <= 0) // player wins
    {
		playerScore++;
        soundManager.playWinningRoundSound();
        ball.resetBall();
    }
}




void Game::checkForCollisions()
{

    if (ball.isBallCollide(player))
    {
		soundManager.playBallHitPaddleSound();
        calculateBallVelocity(player);
    }
        


    else if (ball.isBallCollide(cpuPaddle))
    {
        soundManager.playBallHitPaddleSound();
        calculateBallVelocity(cpuPaddle);
    }
        

    if (ball.getY() + ball.getRadius() >= windowHeight ||
        ball.getY() - ball.getRadius() <= 0)
    {
        soundManager.playBallHitBoundsSound();
    }
}



void Game::calculateBallVelocity(const Paddle& paddle)
{
    // calculate the angle of the ball's hit
    float angle = calculateAngleCollision(paddle);

    // calculate the overall speed. A combination of x velocity and y velocity
    float speed = sqrt(pow(ball.velocity.x, 2) + pow(ball.velocity.y, 2));
    //speed *= 1.05f;

    // Determine the direction of the ball based on its position
    // we could have take the ball x but it is more stable to take the paddle x 
    // because the ball can pass the paddle by some pixels
    float direction = paddle.getX() < windowWidth / 2 ? 1.0f : -1.0f; // determine the direction of the ball based on its position

    // claculate the angle direction of x with cos, and angle direction of y with sin as in math
    ball.velocity.x = direction * speed * std::cos(angle); // multiply by -1 to change direction
    ball.velocity.y = -speed * std::sin(angle); // multiply by -1 because the Y system in raylib is the opposite from the math system
}



void Game::checkForWinner()
{
    
    if (playerScore == WINNING_SCORE)
        gameState = GameStates::PlayerWon;
        
    else if (cpuScore == WINNING_SCORE)
        gameState = GameStates::CpuWon;
}




float Game::calculateAngleCollision(const Paddle& paddle)
{
	// if the ball collides with for example the top side of the paddle, 
	// then, we take the middle of the paddle and subtract the ball's position from it
	// then we get 1. if the ball was to hit the middle of the paddle, then the value will be 0
	// and if the ball was to hit the bottom of the paddle, then the value will be -1
	// any value in between will be a value between -1 and 1, which we can use to calculate the bounce angle
    float relativeIntersectionY = (paddle.getY() + paddle.getHeight() / 2) - ball.getY();
                                      

	// Normalize the value to be between -1 and 1 so we get the 
    // relative position of the ball-paddle collision by presentege
    float normalizedRelativeIntersectionY = relativeIntersectionY / (paddle.getHeight() / 2);

	// We multiply the normalized value by 45 degrees in radians (3.14f / 4)
    return normalizedRelativeIntersectionY * (3.14f / 4); // 45 degrees in radians
}



void Game::playEndGameSound()
{  
    if (gameState == GameStates::PlayerWon)
        soundManager.playWinningSound();
    
    else
        soundManager.playLosingSound();
}

