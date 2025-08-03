#include "Paddle.h"


void Paddle::limitMovement()
{
    if (y <= 0)
        y = 0;

    if (y + height >= GetScreenHeight())
        y = GetScreenHeight() - height;
}


Paddle::Paddle(float pos_x, float pos_y, int w, int h, int Pspeed)
{
    x = pos_x;
    y = pos_y;
    width = w;
    height = h;
    speed = Pspeed;
}


void Paddle::draw()
{
    DrawRectangle(x, y, width, height, BLUE);
}


void Paddle::update()
{
    if (IsKeyDown(KEY_UP))
        y -= speed;

    if (IsKeyDown(KEY_DOWN))
        y += speed;

    limitMovement();
}


float Paddle::getX()
{
    return x;
}


float Paddle::getY()
{
    return y;
}


int Paddle::getWidth()
{
    return width;
}

int Paddle::getHeight()
{
    return height;
}

int Paddle::getSpeed()
{
    return speed;
}





