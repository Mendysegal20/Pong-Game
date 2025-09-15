#include "Game.h"
#include <cmath>
#define WINNING_SCORE 3


Game::Game() :
    ball(middleScreenX, middleScreenY, ballSpeedX, ballSpeedY, radius),
    player(paddlePosX, paddlePosY, paddleWidth, paddleHeight, paddleSpeed),
    cpuPaddle(cpuPaddlePosX, paddlePosY, paddleWidth, paddleHeight, paddleSpeed),
    background({ 0 }),
    font({ 0 }),
    playerScore(0),
    cpuScore(0),
    gameState(GameStates::HomeScreen) {}



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
    
    // DataFrame{...} replaces the need to call the constructor.
    // it creates a temporary object that is passed to the function
    GameRenderData renderData{ background, font, ball, player,
                           cpuPaddle, playerScore, cpuScore, gameState };

    
    while (!(WindowShouldClose() || exitBtnClicked))
    {

		dt = GetFrameTime();

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(background, 0, 0, WHITE);
        
        switch (gameState)
        {

            case displayCredits:
                renderer.renderCreditsScreen(renderData);
				break;

            case Pause:
                renderer.renderPlayScreen(renderData);
                break;


            case HomeScreen:
				soundManager.playHomeScreenSound();
                renderer.renderHomeScreen(renderData);    
				break;

            
            case NoWinner:
                update(dt);
                checkForCollisions();
                checkForWinner();
                renderer.renderPlayScreen(renderData);
                break;
            
            
            case PlayerWon:
            case CpuWon:
                playEndGameSound();
                renderer.renderEndScreen(renderData);
                break;

			
            case Exit:
				exitBtnClicked = true;
				break;
        }
                            
        EventHandler(renderer.checkForEvents());
        
        EndDrawing();
    }

    CloseWindow();
}




void Game::EventHandler(const GameEvents& renderEvent)
{
    
    switch (renderEvent)
    {
        case GameEvents::None:
            break;
        
        case GameEvents::homeScreenPlayBtnClicked:
            if (gameState == GameStates::HomeScreen)
                startGame();
			break;
        
        case GameEvents::homeScreenExitBtnClicked:
            if (gameState == GameStates::HomeScreen)
				gameState = GameStates::Exit;
            break;


        case GameEvents::homeScreenCreditsBtnClicked:
            if (gameState == GameStates::HomeScreen)
                gameState = GameStates::displayCredits;
			break;

        
        case GameEvents::CreditsScreenBackBtnClicked:
            if (gameState == GameStates::displayCredits)
				gameState = GameStates::HomeScreen;
            break;

        
        case GameEvents::playScreenPauseBtnClicked:
            if (gameState == GameStates::Pause || gameState == GameStates::NoWinner)
            {
                if (gameState == GameStates::Pause)
                    gameState = GameStates::NoWinner;

                else if (gameState == GameStates::NoWinner)
                    gameState = GameStates::Pause;

                renderer.changePauseBtnText();
            }
			break;


        case GameEvents::endScreenExitBtnClicked:
            if (gameState == GameStates::PlayerWon || gameState == GameStates::CpuWon)
				gameState = GameStates::Exit;
			break;


        case GameEvents::endScreenPlayBtnClicked:
            if (gameState == GameStates::PlayerWon || gameState == GameStates::CpuWon)
                restartGame();
    }
}



void Game::update(const float dt)
{
    if(GetTime() - waitTime >= 1.2f) // wait for 1.2 seconds before the next round starts
        ball.update(dt);
    
    player.update(dt);
    cpuPaddle.update(ball.velocity.x, ball.getX(), ball.getY(), dt);
    checkIfRoundEnded();
}




void Game::checkIfRoundEnded()
{
    if (ball.getX() >= windowWidth) // cpu wins
    {
		cpuScore++;
		soundManager.playLosingRoundSound();
        startNewRound();
    }
        
    else if (ball.getX() <= 0) // player wins
    {
		playerScore++;
        soundManager.playWinningRoundSound();
        startNewRound();
    }
}



void Game::checkForCollisions()
{

    if (ball.isBallCollide(player))
    {
		soundManager.playBallHitPaddleSound();
        increasePaddleBallSpeed();
        calculateBallVelocity(player);
    }
        


    else if (ball.isBallCollide(cpuPaddle))
    {
        soundManager.playBallHitPaddleSound();
        increasePaddleBallSpeed();
        calculateBallVelocity(cpuPaddle);
    }
        

    if (ball.getY() + ball.getRadius() >= windowHeight ||
        ball.getY() - ball.getRadius() <= 0)
    {
        soundManager.playBallHitBoundsSound();
    }
}


void Game::increasePaddleBallSpeed()
{
	ball.speedUp(dt);
	player.speedUp(dt);
	cpuPaddle.speedUp(dt);  
}




void Game::calculateBallVelocity(const Paddle& paddle)
{
    // calculate the angle of the ball's hit
    float angle = calculateAngleCollision(paddle);

    // calculate the overall speed. A combination of x velocity and y velocity
    float speed = sqrt(pow(ball.velocity.x, 2) + pow(ball.velocity.y, 2));

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
	/* if the ball collides with for example the top side of the paddle, 
	   then, we take the middle of the paddle and subtract the ball's position from it
	   then we get 1. if the ball was to hit the middle of the paddle, then the value will be 0
	   and if the ball was to hit the bottom of the paddle, then the value will be -1
	   any value in between will be a value between -1 and 1, which we can use to calculate the bounce angle */
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



void Game::startGame()
{
    soundManager.stopHomeScreenSound();
    startNewRound();
}



void Game::restartGame()
{
    soundManager.stopEndGameSounds();
    playerScore = 0;
    cpuScore = 0;
    startNewRound();
    
}


void Game::startNewRound()
{  
    gameState = GameStates::NoWinner;
    player.resetSpeed(paddleSpeed);
	cpuPaddle.resetSpeed(paddleSpeed);
    ball.resetBall(ballSpeedX, ballSpeedY);
    waitTime = GetTime();
}

