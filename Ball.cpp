#include "Ball.h"
#include "SoundManager.h"



Ball::Ball(float pos_x, float pos_y, float speed_x, float speed_y, int r)
{
	position = { pos_x, pos_y };
	velocity = { speed_x, speed_y };
    radius = r;
}


void Ball::drawBall() const
{
    DrawCircle(position.x, position.y, radius, WHITE);
}


void Ball::update()
{

    position.x += velocity.x;
    position.y += velocity.y;

    // check for boundaries
    if (position.y + radius >= windowHeight)
    {
	    position.y = windowHeight - radius; // fix the ball position if it goes out of bounds
        velocity.y *= -1;
    }

    if (position.y -radius <= 0)
    {
        position.y = radius;
        velocity.y *= -1;
    }


	// previous boundary check. Does not work for an edge case of the ball 
	// being at the top or bottom edge. It does not fix the ball position
    /*if (position.y + radius >= windowHeight || position.y - radius <= 0)
        velocity.y *= -1;*/
}


void Ball::resetBall()
{
    
    position.x = windowWidth / 2;
    position.y = windowHeight / 2;
	velocity.x = ballSpeedX;
	velocity.y = ballSpeedY;

    int direction_choices[2] = { 1, -1 };
    velocity.x *= direction_choices[GetRandomValue(0, 1)]; // left or right
    velocity.y *= direction_choices[GetRandomValue(0, 1)]; // up or down
}



bool Ball::isBallCollide(const Paddle& paddle)
{
    if (CheckCollisionCircleRec(Vector2{ position.x, position.y },
        radius, Rectangle{ paddle.getX(), paddle.getY(), (float)paddle.getWidth(), (float)paddle.getHeight() }))
        return true;

    return false;
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



void Ball::speedUp()
{
    velocity.x *= 1.03f;
    velocity.y *= 1.03f;
}

