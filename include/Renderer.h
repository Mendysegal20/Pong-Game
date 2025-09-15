#pragma once
#include <string>
#include "GameRenderData.h"
#include "GameEvents.h"
#include <iostream>
#include <vector>



struct Button
{
	Rectangle btnRec{};
	std::string text = "II"; // pause symbol by default
};


class Renderer
{

public:
	
	Renderer()
	{	
		readFile("credits.txt");
		
		homeScreenPlayButton.btnRec = { windowWidth / 2.0f - 100, windowHeight / 2.5f - 60, 200, 50 };
		homeScreenExitButton.btnRec = { windowWidth / 2.0f - 100, windowHeight / 2.5f + 60, 200, 50 };
		homeScreenCreditsButton.btnRec = { windowWidth / 2.0f - 100, windowHeight / 2.5f + 180, 200, 50 };

		CreditsScreenBackButton.btnRec = { windowWidth - 170, 40, 130, 50 };
		playScreenPauseButton.btnRec = { windowWidth / 2.0f - 50, 20, 100, 50 };

		endScreenPlayButton.btnRec = { windowWidth / 2.0f - 250, windowHeight / 1.2f, 200, 50 };
		endScreenExitButton.btnRec = { windowWidth / 2.0f + 50, windowHeight / 1.2f, 200, 50 };
	}

	void renderPlayScreen(const GameRenderData& data) const;
	void renderHomeScreen(const GameRenderData& data) const;
	void renderEndScreen(const GameRenderData& data) const;
	void renderCreditsScreen(const GameRenderData& data) const;
	void changePauseBtnText();


	GameEvents checkForEvents();
	
	void renderButton(const Button& btn, const std::string& text, const Font& font,
		const Color btnColor, const Color hoverColor, 
		const Color clickedColor) const;


private:
	
	Button homeScreenPlayButton;
	Button homeScreenCreditsButton;
	Button CreditsScreenBackButton;
	Button homeScreenExitButton;
	Button playScreenPauseButton;
	Button endScreenPlayButton;
	Button endScreenExitButton;
	std::vector<std::string> creditText;

	bool isBtnClicked(const Button& btn) const;
	void readFile(const std::string& fileName);
};



