#pragma once
#include "raylib.h"

class Paddle
{

protected:
	Vector2 position;
    int width, height;
    int speed;
    
    void limitMovement();

public:

    Paddle(float pos_x, float pos_y, int w, int h, int Pspeed);

    void draw();
    void update();

    float getX();
    float getY();
    int getWidth();
    int getHeight();
    int getSpeed();
};











