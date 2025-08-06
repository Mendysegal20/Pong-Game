#include "Ball.h"



Ball::Ball(float pos_x, float pos_y, float speed_x, float speed_y, int r)
{
	position = { pos_x, pos_y };
	velocity = { speed_x, speed_y };
    radius = r;
	WaitTime = 0;
}


void Ball::drawBall()
{
    DrawCircle(position.x, position.y, radius, WHITE);
}


void Ball::update()
{
    if(GetTime() - WaitTime >= 2.0f) // wait for 2 seconds before the next round starts
    {
       
        position.x += velocity.x;
        position.y += velocity.y;

        // check for boundaries
        if (position.y + radius >= windowHeight || position.y - radius <= 0)
            velocity.y *= -1;
	}
}


void Ball::resetBall()
{
    
    position.x = windowWidth / 2;
    position.y = windowHeight / 2;

    int direction_choices[2] = { 1, -1 };
    velocity.x *= direction_choices[GetRandomValue(0, 1)]; // left or right
    velocity.y *= direction_choices[GetRandomValue(0, 1)]; // up or down

    WaitTime = GetTime();
}



int Ball::getRadius()
{
    return radius;
}

float Ball::getX()
{
    return position.x;
}

float Ball::getY()
{
    return position.y;
}
