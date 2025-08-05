#pragma once
#include "raylib.h"
#include "Constants.h"

class Ball
{
private:
	Vector2 position;
    int radius;
    float WaitTime;

public:
    
    Vector2 velocity;
    
    Ball(float pos_x, float pos_y, float speedX, float speedY, int r);

    void drawBall();

    void update();

    void resetBall();

    float getX();

    float getY();
    
    int getRadius();
};




