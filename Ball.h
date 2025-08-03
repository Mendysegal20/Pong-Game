#pragma once
#include "raylib.h"
#include "Constants.h"

class Ball
{
private:
    float x, y;
    int radius;
    float WaitTime;

public:

    int speedX, speedY;
    
    Ball(float pos_x, float pos_y, int speedX, int speedY, int r);

    void drawBall();

    void update();

    void resetBall();

    float getX();

    float getY();
    
    int getRadius();
};




