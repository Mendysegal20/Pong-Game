#pragma once
#include "raylib.h"
#include "Constants.h"
#include "Paddle.h"

class Ball
{
private:
	Vector2 position;
    int radius;

public:
    
    Vector2 velocity;
    
    Ball(float pos_x, float pos_y, float speedX, float speedY, int r);

    void drawBall() const;

    void update();

    void resetBall();

    bool isBallCollide(const Paddle& paddle);

    float getX();

    float getY();
    
    int getRadius();

	void speedUp();
};




