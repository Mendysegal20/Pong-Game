#include "Renderer.h"
#include <fstream>
#include <sstream>


void Renderer::renderPlayScreen(const GameRenderData& data) const
{   
    DrawTextEx(data.font, TextFormat("%i", data.playerScore), Vector2{ 3 * textPosX, textPosY }, fontSize, 0.0f, GREEN);
    DrawTextEx(data.font, TextFormat("%i", data.cpuScore), Vector2{ textPosX, textPosY }, fontSize, 0.0f, GREEN);
	renderButton(playScreenPauseButton.btnRec, playScreenPauseButton.text, data.font, BLUE, DARKBLUE, DARKPURPLE);
    data.ball.drawBall();
    data.player.draw();
    data.cpuPaddle.draw();
}




void Renderer::renderHomeScreen(const GameRenderData& data) const
{
    renderButton(homeScreenPlayButton.btnRec,"Play", data.font, GREEN, DARKGREEN, LIME);
    renderButton(homeScreenExitButton.btnRec, "Exit", data.font, RED, MAROON, BEIGE);
	renderButton(homeScreenCreditsButton.btnRec, "Credits", data.font, BLUE, DARKBLUE, SKYBLUE);
}




void Renderer::renderEndScreen(const GameRenderData& data) const
{
    // implement better end screen later
    const char* winner = data.gameState == GameStates::PlayerWon ? "You Won!" : "CPU Won!";
    DrawTextEx(data.font, winner, Vector2{ windowWidth / 3.5f, windowHeight / 3.5f }, fontSize * 2, 0.0f, GREEN);
    renderButton(endScreenPlayButton.btnRec,"Replay", data.font, GREEN, DARKGREEN, LIME);
    renderButton(endScreenExitButton.btnRec, "Exit", data.font, RED, MAROON, BEIGE);
}



void Renderer::readFile(const std::string& fileName)
{
    std::ifstream file("assets/" + fileName);
    if(!file.is_open())
    {
        std::cerr << "Failed to open the credits file: " << fileName << "\n";
        return;
	}

    std::string line;

    while(std::getline(file, line))
        creditText.push_back(line);
    
    
    file.close();
}


void Renderer::renderCreditsScreen(const GameRenderData& data) const
{

    Vector2 pos = { 0.05f * windowWidth, 0.05f * windowHeight};
    
    for (int i = 0; i < creditText.size(); i++)
    {
        DrawTextEx(data.font, creditText[i].c_str(),{pos.x + 1, pos.y + i * (fontSize + 5) + 1},
			fontSize / 1.6f, 0.0f, DARKGRAY);

        DrawTextEx(data.font, creditText[i].c_str(), { pos.x, pos.y + i * (fontSize + 5)},
            fontSize / 1.6f, 0.0f, BLACK);
    }

	renderButton(CreditsScreenBackButton.btnRec, "Back", data.font,ORANGE , GOLD, YELLOW);
}




void Renderer::renderButton(const Rectangle& btnRec, const std::string& text, const Font& font, 
    const Color btnColor, const Color hoverColor, const Color clickedColor) const
{

    if(CheckCollisionPointRec(GetMousePosition(), btnRec))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            DrawRectangleRounded(btnRec, 8, 2, clickedColor);
            
			
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
    Vector2 textSize = MeasureTextEx(font, text.c_str(), fontSize / 1.5, 0.0f);
	
    /* btnRec.x = begining of the button
       btnRec.width = width of the button
	   textSize.x = width of the text
	   btnRec.width - textSize.x = free space left in the button after placing the text
    */
    Vector2 textPosition = { btnRec.x + (btnRec.width - textSize.x) / 2,
                            btnRec.y + (btnRec.height - textSize.y) / 2 - 4 };

    DrawTextEx(font, text.c_str(), textPosition, fontSize / 1.5, 2.0f, WHITE);
}




GameEvents Renderer::checkForEvents()
{
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {   
        if (isBtnClicked(homeScreenPlayButton))
            return GameEvents::homeScreenPlayBtnClicked;
        
        else if (isBtnClicked(homeScreenExitButton))
            return GameEvents::homeScreenExitBtnClicked;

        else if(isBtnClicked(homeScreenCreditsButton))
			return GameEvents::homeScreenCreditsBtnClicked;

		else if (isBtnClicked(CreditsScreenBackButton))
			return GameEvents::CreditsScreenBackBtnClicked;

        else if (isBtnClicked(playScreenPauseButton))
            return GameEvents::playScreenPauseBtnClicked;

        else if(isBtnClicked(endScreenPlayButton))
            return GameEvents::endScreenPlayBtnClicked;

        else if(isBtnClicked(endScreenExitButton))
			return GameEvents::endScreenExitBtnClicked;
	}

    /*else if(IsKeyPressed(KEY_SPACE))
		return GameEvents::PauseBtnClicked;*/

	return GameEvents::None;
}




bool Renderer::isBtnClicked(const Button& btn) const
{
    if (CheckCollisionPointRec(GetMousePosition(), btn.btnRec))
        return true;

    return false;
}


void Renderer::changePauseBtnText()
{
    playScreenPauseButton.text == "II" ?
        playScreenPauseButton.text = ">" :
        playScreenPauseButton.text = "II";
}


