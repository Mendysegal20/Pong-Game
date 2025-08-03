#include "Ball.h"



Ball::Ball(float pos_x, float pos_y, int speed_x, int speed_y, int r)
{
    x = pos_x;
    y = pos_y;
    speedX = speed_x;
    speedY = speed_y;
    radius = r;
	WaitTime = 0;
}


void Ball::drawBall()
{
    DrawCircle(x, y, radius, WHITE);
}


void Ball::update()
{
    if(GetTime() - WaitTime >= 2.0f) // wait for 2 seconds before the next round starts
    {
        /*isWaiting = false;*/
        
        x += speedX;
        y += speedY;

        if (y - radius >= windowHeight || y + radius <= 0)
            speedY *= -1;
	}
}


void Ball::resetBall()
{
    
    x = windowWidth / 2;
    y = windowHeight / 2;

    int direction_choices[2] = { 1, -1 };
    speedX *= direction_choices[GetRandomValue(0, 1)]; // left or right
    speedY *= direction_choices[GetRandomValue(0, 1)]; // up or down

	//isWaiting = true; // wait for a moment before the next round starts
    WaitTime = GetTime();
}



int Ball::getRadius()
{
    return radius;
}

float Ball::getX()
{
    return x;
}

float Ball::getY()
{
    return y;
}
