#include "Renderer.h"
#include <fstream>
#include <sstream>


void Renderer::renderPlayScreen(const GameRenderData& data) const
{   
    DrawTextEx(data.font, TextFormat("%i", data.playerScore), 
        Vector2{ 3 * textPosX, textPosY }, fontSize, 0.0f, Color{ 7, 230, 74 , 255});
    DrawTextEx(data.font, TextFormat("%i", data.cpuScore), 
        Vector2{ textPosX, textPosY }, fontSize, 0.0f, Color{ 7, 230, 74 , 255});
	
    renderButton(playScreenPauseButton, playScreenPauseButton.text, data.font, 
        BLUE, DARKBLUE, Color{ 115, 197, 255 , 255});
    
    data.ball.drawBall();
    data.player.draw();
    data.cpuPaddle.draw();
}




void Renderer::renderHomeScreen(const GameRenderData& data) const
{
    renderButton(homeScreenPlayButton,"Play", data.font, 
        Color{ 91, 207, 52, 255 }, // Idle - Green
        Color{ 78, 171, 46, 255 }, // Hover - Dark Green
        Color{ 151, 207, 132, 255 }); // Pressed - Light Green
    
    renderButton(homeScreenExitButton, "Exit", data.font, 
		Color{ 222, 87, 42 , 255 }, // Idle - Red
		Color{ 171, 66, 31 , 255 }, // Hover - Dark Red
		Color{ 207, 138, 116 , 255 }); // Pressed - Light Red
	
    renderButton(homeScreenCreditsButton, "Credits", data.font, 
		Color{ 43, 147, 217, 255 }, // Idle - Blue
		Color{ 35, 104, 150, 255 }, // Hover - Dark Blue
		Color{ 177, 207, 227, 255 }); // Pressed - Light Blue
}




void Renderer::renderEndScreen(const GameRenderData& data) const
{
    
    const char* winner = data.gameState == GameStates::PlayerWon ? "Look who's not terrible today!" : "Wow, you suck";

    
	// draw a gradient background based on who won
    if (data.gameState == GameStates::PlayerWon)
        DrawRectangleGradientEx(Rectangle{ 0,0,windowWidth,windowHeight },
			Color{ 40, 140, 180, 255 },   // Dark Blue
			Color{ 70, 150, 200, 255 },   // Light Blue
			Color{ 100, 160, 190, 255 },  // Midium Blue
			Color{ 25, 25, 112, 255 });   // Midnight Blue

    else
         DrawRectangleGradientEx(Rectangle{0,0,windowWidth,windowHeight},
            Color{128,0,0,255},   // Maroon
            Color{220,20,60,255}, // Crimson
            Color{139,0,0,255},   // Dark Red
            Color{25,25,25,255}); // Dark Gray


	// to center the text, we measure its size first, then we calculate the empty space left
    Vector2 textSize = MeasureTextEx(data.font, winner, fontSize * 1.2f, 0);
	
    // empty space = (windowWidth - textSize.x) / 2
    Vector2 pos = { (windowWidth - textSize.x) / 2, windowHeight / 3.5f }; 
    
	// darken the background
    DrawRectangle(0, 0, windowWidth, windowHeight, Fade(BLACK, 0.3f)); 

    Color textColor = data.gameState == GameStates::PlayerWon ? 
        Color{ 38, 114, 235, 255 } : Color{ 235, 64, 38, 255 };
	
	// draw shadow around the text
    DrawTextEx(data.font, winner, Vector2{ pos.x + 1, pos.y + 1 }, fontSize * 1.2f, 0.0f, BLACK);
    
	// draw the text
    DrawTextEx(data.font, winner, Vector2{ pos.x, pos.y }, fontSize * 1.2f, 0.0f, textColor);
    renderButton(endScreenPlayButton,"Replay", data.font, 
		Color{ 44, 150, 26, 255 },
		Color{ 42, 122, 28, 255 },
		Color{ 195, 250, 199, 255 });
    
    renderButton(endScreenExitButton, "Exit", data.font, 
		Color{ 212, 57, 57, 255 },
		Color{ 166, 23, 23, 255 },
		Color{ 235, 169, 169, 255 });
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
			fontSize / 1.6f, 0.0f, BLACK);

        DrawTextEx(data.font, creditText[i].c_str(), { pos.x, pos.y + i * (fontSize + 5)},
            fontSize / 1.6f, 0.0f, Color{ 35, 43, 61 , 255});
    }

	renderButton(CreditsScreenBackButton, "Back", data.font,
        ORANGE , 
        Color{ 217, 137, 0 , 255},
        Color{ 250, 217, 160 , 255});
}




void Renderer::renderButton(const Button& btn, const std::string& text, const Font& font, 
    const Color btnColor, const Color hoverColor, const Color clickedColor) const
{

    if(isBtnClicked(btn))
    {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
            DrawRectangleRounded(btn.btnRec, 8, 2, clickedColor);
            
			
        else
            DrawRectangleRounded(btn.btnRec, 8, 2, hoverColor);
	}
    else
        DrawRectangleRounded(btn.btnRec, 8, 2, btnColor);

    
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
    Vector2 textPosition = { btn.btnRec.x + (btn.btnRec.width - textSize.x) / 2,
                            btn.btnRec.y + (btn.btnRec.height - textSize.y) / 2 - 4 };

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


