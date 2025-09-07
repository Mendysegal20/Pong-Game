#pragma once
#include "GameRenderData.h"
#include "RendererActions.h"




class Renderer
{

public:

	/*bool gameShuldClose = false;*/
	
	Renderer()
	{
		playBtnRec = { windowWidth / 2.0f - 250, windowHeight / 1.2f, 200, 50 };
		ExitBtnRec = { windowWidth / 2.0f + 50, windowHeight / 1.2f, 200, 50 };
	}

	RendererActions renderFrame(const GameRenderData& data) const;
	
	bool renderButton(const Rectangle& btnRec, const char* text, const Font& font,
		const Color btnColor, const Color hoverColor, 
		const Color clickedColor) const;


private:
	Rectangle playBtnRec;
	Rectangle ExitBtnRec;
};



