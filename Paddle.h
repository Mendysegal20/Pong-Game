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

    void draw() const;
    void update();

    float getX() const;
    float getY() const;
    int getWidth() const;
    int getHeight() const;
    int getSpeed() const;
};











