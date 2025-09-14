#pragma once

#include "raylib.h"
#include "CpuPaddle.h"
#include "Ball.h"
#include "Paddle.h"
#include "GameStatus.h"


/*
A struct to hold all the data needed for rendering a frame.
everithing is passed by reference to avoid copying large objects,
and to ensure the renderer always has the most up-to-date information
without risking of null references because rfrerences must be initialized at creation
and always point to a valid object.
*/ 

struct GameRenderData
{
    const Texture2D& background;
    const Font& font;
    const Ball& ball;
    const Paddle& player;
    const Paddle& cpuPaddle;
    const int& playerScore;
    const int& cpuScore;
    const GameStates& gameState;
};


