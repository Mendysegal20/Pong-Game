#include "Game.h"
#include <cmath>
#define WINNING_SCORE 2


Game::Game():
    ball(middleScreenX, middleScreenY, ballSpeedX, ballSpeedY, radius),
    player(paddlePosX, paddlePosY, paddleWidth, paddleHeight, paddleColor),
    cpuPaddle(cpuPaddlePosX, paddlePosY, paddleWidth, paddleHeight, paddleColor),
    backgroundTexture({ 0 }),
    font({ 0 }),
	playerScore(0),
	cpuScore(0),
    gameState(GameStates::NoWinner) {}



Game::~Game()
{
    UnloadFont(font);
	UnloadTexture(backgroundTexture);
}



void Game::init()
{
    InitWindow(windowWidth, windowHeight, "Pong Game");
    SetTargetFPS(60);
    loadAssets();
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
                render();
                break;
            
            case PlayerWon:
                drawWinner("You Won!");
                break;
            
            case CpuWon:
                drawWinner("Cpu Won!");
                break;
        }

        EndDrawing();
    }

    CloseWindow();
}





void Game::loadAssets()
{
    Image image = LoadImage(bgPath);
    backgroundTexture = LoadTextureFromImage(image);
    UnloadImage(image);
    font = LoadFontEx(fontPath, fontSize, 0, 0);
}



bool Game::isBallCollide(Paddle paddle)
{
    if (CheckCollisionCircleRec(Vector2{ ball.getX(), ball.getY() },
        ball.getRadius(), Rectangle{ paddle.getX(), paddle.getY(), (float)paddle.getWidth(), (float)paddle.getHeight()}))
		return true;
	
    return false;
}


void Game::calculateBallVelocity(Paddle paddle)
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


void Game::checkForCollisions()
{
    
	if (isBallCollide(player))
		calculateBallVelocity(player);
        

    else if (isBallCollide(cpuPaddle))
        calculateBallVelocity(cpuPaddle);
}





void Game::update()
{
    ball.update();
    player.update();
    cpuPaddle.update(ball.velocity.x, ball.getX(), ball.getY());
    updateScore();
}




void Game::updateScore()
{
    if (ball.getX() >= windowWidth) // cpu wins
    {
        cpuScore++;
        ball.resetBall();
    }
        
    else if (ball.getX() <= 0) // player wins
    {
        playerScore++;
        ball.resetBall();
    }
}


void Game::render()
{
    DrawTexture(backgroundTexture, 0, 0, WHITE);
    DrawTextEx(font, TextFormat("%i", playerScore), Vector2{ 3 * textPosX, textPosY }, fontSize, 0.0f, GREEN);
    DrawTextEx(font, TextFormat("%i", cpuScore), Vector2{textPosX, textPosY}, fontSize, 0.0f, GREEN);
    ball.drawBall();
    player.draw();
    cpuPaddle.draw();
}





void Game::drawWinner(const char* winner)
{
    DrawTexture(backgroundTexture, 0, 0, WHITE);
    DrawTextEx(font, winner, Vector2{ windowWidth / 4.5f, windowHeight / 3.5f }, fontSize * 2, 0.0f, GREEN);
}





void Game::checkForWinner()
{
    
    if (playerScore == WINNING_SCORE)
        gameState = GameStates::PlayerWon;
        
    else if (cpuScore == WINNING_SCORE)
        gameState = GameStates::CpuWon;
}



float Game::calculateAngleCollision(Paddle paddle)
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






