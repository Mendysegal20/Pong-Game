#include "Game.h"
#define WINNING_SCORE 1


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





void Game::checkForCollisions()
{
    if (CheckCollisionCircleRec(Vector2{ ball.getX(), ball.getY() },
        ball.getRadius(), Rectangle{ player.getX(), player.getY(), (float)player.getWidth(), (float)player.getHeight() }))
        ball.speedX *= -1;


    if (CheckCollisionCircleRec(Vector2{ ball.getX(), ball.getY() },
        ball.getRadius(), Rectangle{ cpuPaddle.getX(), cpuPaddle.getY(), (float)cpuPaddle.getWidth(), (float)cpuPaddle.getHeight() }))
        ball.speedX *= -1;
}





void Game::update()
{
    ball.update();
    player.update();
    cpuPaddle.update(ball.speedX, ball.getX(), ball.getY());
    updateScore();
}




void Game::updateScore()
{
    if (ball.getX() + ball.getRadius() / 2 >= windowWidth) // cpu wins
    {
        cpuScore++;
        ball.resetBall();
    }
        
    else if (ball.getX() - ball.getRadius() / 2 <= 0) // player wins
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


