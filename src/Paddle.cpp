#include "Paddle.h"
#include "Constants.h"


void Paddle::limitMovement()
{
    if (position.y <= 0)
        position.y = 0;

    if (position.y + height >= GetScreenHeight())
        position.y = GetScreenHeight() - height;
}


Paddle::Paddle(float pos_x, float pos_y, int w, int h, float Pspeed)
{
	position = { pos_x, pos_y };
    width = w;
    height = h;
    speed = Pspeed;
}


void Paddle::draw() const
{
    DrawRectangle(position.x, position.y, width, height, BLUE);
}


void Paddle::update(const float dt)
{
    if (IsKeyDown(KEY_UP))
        position.y -= speed * dt;

    if (IsKeyDown(KEY_DOWN))
        position.y += speed * dt;

    limitMovement();
}


float Paddle::getX() const
{
    return position.x;
}


float Paddle::getY() const
{
    return position.y;
}


int Paddle::getWidth() const
{
    return width;
}

int Paddle::getHeight() const
{
    return height;
}

float Paddle::getSpeed() const
{
    return speed;
}


void Paddle::speedUp(const float dt)
{
    speed *= 1.03f * dt * 60.0f;
}


void Paddle::resetSpeed(const float Pspeed)
{
    speed = Pspeed;
}





