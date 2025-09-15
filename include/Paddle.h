#pragma once
#include "raylib.h"

class Paddle
{

protected:
	Vector2 position;
    int width, height;
    float speed;
    
    void limitMovement();

public:

    Paddle(float pos_x, float pos_y, int w, int h, float Pspeed);

    void draw() const;
    void update(const float dt);

    float getX() const;
    float getY() const;
    int getWidth() const;
    int getHeight() const;
    float getSpeed() const;
	void speedUp(const float dt);
	void resetSpeed(const float Pspeed);
};











