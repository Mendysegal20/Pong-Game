#include "Paddle.h"


void Paddle::limitMovement()
{
    if (position.y <= 0)
        position.y = 0;

    if (position.y + height >= GetScreenHeight())
        position.y = GetScreenHeight() - height;
}


Paddle::Paddle(float pos_x, float pos_y, int w, int h, int Pspeed)
{
    /*x = pos_x;
    y = pos_y;*/
	position = { pos_x, pos_y };
    width = w;
    height = h;
    speed = Pspeed;
}


void Paddle::draw()
{
    DrawRectangle(position.x, position.y, width, height, BLUE);
}


void Paddle::update()
{
    if (IsKeyDown(KEY_UP))
        position.y -= speed;

    if (IsKeyDown(KEY_DOWN))
        position.y += speed;

    limitMovement();
}


float Paddle::getX()
{
    return position.x;
}


float Paddle::getY()
{
    return position.y;
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





