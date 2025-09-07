#include "Renderer.h"
#include <string.h>


// This function draws the entire frame based on the game state, including the frame logic
RendererActions Renderer::renderFrame(const GameRenderData& data) const
{ 
    DrawTexture(data.background, 0, 0, WHITE);

    bool exitBtnClicked = false;

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
		DrawTextEx(data.font, winner, Vector2{ windowWidth / 3.5f, windowHeight / 3.5f }, fontSize * 2, 0.0f, GREEN);
        renderButton(playBtnRec,"Replay", data.font, GREEN, DARKGREEN, LIME);
        exitBtnClicked = renderButton(ExitBtnRec, "Exit", data.font, RED, MAROON, BEIGE);
    }

	/*return exitBtnClicked;*/
	return exitBtnClicked ? RendererActions::ExitGame : RendererActions::Render;
}


bool Renderer::renderButton(const Rectangle& btnRec, const char* text, const Font& font, 
    const Color btnColor, const Color hoverColor, const Color clickedColor) const
{

	bool isClicked = false;

    if(CheckCollisionPointRec(GetMousePosition(), btnRec))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            DrawRectangleRounded(btnRec, 8, 2, clickedColor);
			isClicked = true;
			/*gameShuldClose = true;*/
        }
            
			
        else
            DrawRectangleRounded(btnRec, 8, 2, hoverColor);
	}
    else
        DrawRectangleRounded(btnRec, 8, 2, btnColor);

    
    /*
        we calculate the text position to center it in the button
		the calculation is as follows:
		1. Measure the size of the text using MeasureTextEx
        2. for pos x, we take the begining of the button (btnRec.x), and
		   we add half of the free space left in the button after placing the text.
           that will be the begining of the text position

		   we do the same for pos y, but we also substract 4 to center it better
		   because the text has the letter y that goes below the line a bit
    */ 
    Vector2 textSize = MeasureTextEx(font, text, fontSize / 1.5, 0.0f);
	
    /* btnRec.x = begining of the button
       btnRec.width = width of the button
	   textSize.x = width of the text
	   btnRec.width - textSize.x = free space left in the button after placing the text
    */
    Vector2 textPosition = { btnRec.x + (btnRec.width - textSize.x) / 2,
                            btnRec.y + (btnRec.height - textSize.y) / 2 - 4 };

    DrawTextEx(font, text, textPosition, fontSize / 1.5, 2.0f, WHITE);

	return isClicked;
}


//void Renderer::update(const Font& font)
//{
//	bool exitBtnClicked = renderButton(ExitBtnRec, "Exit", font, RED, MAROON, BEIGE);
//}


