#pragma once
#include "raylib.h"
#include "Paddle.h"
#include "Constants.h"


class CpuPaddle : public Paddle
{
public:
    
    CpuPaddle(float pos_x, float pos_y, int w, int h, int Pspeed);
    
    void update(int ballDir, int ballX, int ballY);
};








