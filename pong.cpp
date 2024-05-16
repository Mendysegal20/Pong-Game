#include "raylib.h"
#include <iostream>
using namespace std;

int player_score = 0;
int cpu_score = 0;

class Ball
{
public:
    float x, y;
    int speed_x, speed_y;
    int radius;

    Ball(float pos_x, float pos_y, int speedX, int speedY, int r)
    {
        x = pos_x;
        y = pos_y;
        speed_x = speedX;
        speed_y = speedY;
        radius = r;
    }

    void drawBall()
    {
        DrawCircle(x , y, radius, WHITE);
    }

    void update()
    {
        x += speed_x;
        y += speed_y;

        if (y - radius >= GetScreenHeight() || y + radius <= 0)
            speed_y *= -1;
        
        if (x + radius >= GetScreenWidth())// cpu wins
        {
            cpu_score++;
            resetBall();
        } 
            
        if (x - radius <= 0)// player wins
        {
            player_score++;
            resetBall(); 
        } 
                 
    }

    void resetBall()
    {
        x = GetScreenWidth() / 2;
        y = GetScreenHeight() / 2;

        int speed_choices[2] = {1, -1};
        speed_x *= speed_choices[GetRandomValue(0,1)];
        speed_y *= speed_choices[GetRandomValue(0,1)];
    }

};


class Paddle
{

protected:
    void linitMovement()
        {
            if (y <= 0)
                y = 0;
        
            if (y + height >= GetScreenHeight())
                y = GetScreenHeight() - height;
        }

public:
    float x, y;
    int width, height;
    int speed;

    Paddle(float pos_x, float pos_y, int w, int h, int Pspeed)
    {
        x = pos_x;
        y = pos_y;
        width = w;
        height = h;
        speed = Pspeed;
    }
    
    void draw()
    {
        DrawRectangle(x, y,width , height, BLUE);
    }

    void update()
    {   
        if (IsKeyDown(KEY_UP))
            y -= speed;
        
        if (IsKeyDown(KEY_DOWN))
            y += speed;
        
        linitMovement();

    }
};


class CpuPaddle: public Paddle
{
public:
    CpuPaddle(float pos_x, float pos_y, int w, int h, int Pspeed)
    : Paddle(pos_x, pos_y, w, h, Pspeed){}

    void update(int ball_y)
    {
        if (y + height/2 > ball_y)
            y -= speed;
        
        if (y + height/2 < ball_y)
            y += speed;
        
        //linitMovement();
    }
};


int main()
{

    const int width = 1280;
    const int height = 800;
    
    InitWindow(width, height, "Pong Game");
    SetTargetFPS(60);

    Ball ball = Ball(width / 2, height / 2, 7, 7, 20);
    Paddle player = Paddle(width - 35, height / 2 - 60, 25, 120, 6);
    CpuPaddle cpu = CpuPaddle(10, height / 2 - 60, 25, 120, 6);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        // draw
        ball.drawBall();
        player.draw();
        cpu.draw();
        DrawLine(width/2, 0, width/2, height, WHITE);
        
        // collisions
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, 
                ball.radius, Rectangle{player.x, player.y, player.width, player.height}))
                    ball.speed_x *= -1;

        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, 
                ball.radius, Rectangle{cpu.x, cpu.y, cpu.width, cpu.height}))
                    ball.speed_x *= -1;   
        
        //update
        ball.update();
        player.update();
        cpu.update(ball.y);
        DrawText(TextFormat("%i",cpu_score), width / 4 - 20, 20, 80, GREEN);
        DrawText(TextFormat("%i",player_score), 3 * width / 4 - 20, 20, 80, GREEN);
        
        EndDrawing();
        
    }
    CloseWindow();
    return 0;


}



