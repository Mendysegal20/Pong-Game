#include "Renderer.h"


// This function draws the entire frame based on the game state, including the frame logic
void Renderer::renderFrame(const DataFrame& data) const
{ 
    DrawTexture(data.background, 0, 0, WHITE);

    if(data.gameState == GameStates::NoWinner)
    {
        DrawTextEx(data.font, TextFormat("%i", data.playerScore), Vector2{ 3 * textPosX, textPosY }, fontSize, 0.0f, GREEN);
        DrawTextEx(data.font, TextFormat("%i", data.cpuScore), Vector2{ textPosX, textPosY }, fontSize, 0.0f, GREEN);
        data.ball.drawBall();
        data.player.draw();
        data.cpuPaddle.draw();
	}
    else
    {
        const char* winner = data.gameState == GameStates::PlayerWon ? "You Won!" : "CPU Won!";
		DrawTextEx(data.font, winner, Vector2{ windowWidth / 4.5f, windowHeight / 3.5f }, fontSize * 2, 0.0f, GREEN);
        
    }  
}










