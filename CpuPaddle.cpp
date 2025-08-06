#include "CpuPaddle.h"


CpuPaddle::CpuPaddle(float pos_x, float pos_y, int w, int h, int Pspeed)
	:Paddle(pos_x, pos_y, w, h, Pspeed) {}


void CpuPaddle::update(int ballDir, int ballX, int ballY)
{
    
    int paddleCenterY = position.y + height / 2;
    
    // if the ball's direction is towards the cpu paddle
    if (ballDir <= -1 && ballX < windowWidth / 1.5)
    {
        // follow the ball's trajectory
        if (paddleCenterY > ballY)
            position.y -= speed;

        if (paddleCenterY < ballY)
            position.y += speed;
    }

    // centralize the cpu paddle if the ball if on the oposite direction
    else if (paddleCenterY != middleScreenY)
        paddleCenterY > middleScreenY ? position.y -= speed : position.y += speed;
}













