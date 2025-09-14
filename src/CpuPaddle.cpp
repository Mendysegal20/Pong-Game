#include "CpuPaddle.h"
#include <iostream>


CpuPaddle::CpuPaddle(float pos_x, float pos_y, int w, int h, int Pspeed)
	:Paddle(pos_x, pos_y, w, h, Pspeed) {}


void CpuPaddle::update(int ballDir, int ballX, int ballY)
{
    
    int paddleCenterY = position.y + height / 2;
	int distanceFromBall = std::abs(ballX - position.x);
	
	// if the ball is too far away, the dead zone is larger because 
	// we want the cpu paddle to move more frequently to avoid missing the ball
	// // if the ball is close, the dead zone is larger because 
	// we don't want the cpu paddle to move too frequently and to prevent 
	// the cpu paddle from "shaking" 
    int deadZone = distanceFromBall < 50 ? 35 : 15;
    
    // if the ball's direction is towards the cpu paddle
    if (ballDir <= -1 && ballX < windowWidth / 1.5)
    {
        
        if (std::abs(ballY - paddleCenterY) > deadZone)
        {
            // follow the ball's trajectory
            if (paddleCenterY > ballY)
                position.y -= speed;

            if (paddleCenterY < ballY)
                position.y += speed;
        } 
    }
    else
    {
		/* the desired target position to centralize the cpu paddle
		 in case the paddle center is close enough to the middle of the screen */
        int targetY = middleScreenY - height / 2;

		// if the paddle center is not close enough to the middle of the screen
        if(std::abs(paddleCenterY - middleScreenY) > speed)
        {
			// if the paddle center is too low, then move it up
            if (paddleCenterY > middleScreenY)
                position.y -= speed;
            
			// if the paddle center is too high, then move it down
            else if (paddleCenterY < middleScreenY)
                position.y += speed;
		}

		/* if the paddle center is close enough to the middle of the screen
		 we set the paddle position to the target position */
        else
			position.y = targetY;
    }

    
    // centralize the cpu paddle if the ball if on the oposite direction
    /*else if (paddleCenterY != middleScreenY)
        paddleCenterY > middleScreenY ? position.y -= speed : position.y += speed;*/

	limitMovement();
}




