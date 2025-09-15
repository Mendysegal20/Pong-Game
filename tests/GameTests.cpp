#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "Ball.h"
#include "Paddle.h"


TEST_CASE("Ball & Paddle Tests") {

	
	float dt = 1.0f;
	
	Ball ball1(400, 300, 440, 440, 10); // Posx, Posy, speedX, speedY, radius
	Ball ball2(35, 210, 440, 440, 15); // Posx, Posy, speedX, speedY, radius
	Paddle paddle(50, 200, 20, 100, 440); // Posx, Posy, width, height, speed

	SECTION("Ball initial position") {
		REQUIRE(ball1.getX() == 400);
		REQUIRE(ball1.getY() == 300);
		REQUIRE(ball1.getRadius() == 10);
	}

	SECTION("Paddle initial position") {
		REQUIRE(paddle.getX() == 50);
		REQUIRE(paddle.getY() == 200);
		REQUIRE(paddle.getWidth() == 20);
		REQUIRE(paddle.getHeight() == 100);
	}

	SECTION("Ball movement update") {
		ball1.update(dt);
		REQUIRE(ball1.getX() >= 400); // 400 + dt * 440
		REQUIRE(ball1.getY() >= 300); // 300 + dt * 440
	}

	SECTION("Collisions") {
		REQUIRE(ball1.isBallCollide(paddle) == false); // ball1X=400 far from paddleX=50
		REQUIRE(ball2.isBallCollide(paddle) == true); // ball2X=35 + radius=15 collides with paddleX=50
	}

	SECTION("Paddle speed up and reset") {
		float initialSpeed = paddle.getSpeed();
		
		paddle.speedUp(dt);
		REQUIRE(paddle.getSpeed() > initialSpeed);
		
		paddle.resetSpeed(paddleSpeed);
		REQUIRE(paddle.getSpeed() == initialSpeed);
	}

	SECTION("Ball speed up and reset") {
		float initialSpeedX = ball1.velocity.x;
		float initialSpeedY = ball1.velocity.y;
		
		ball1.speedUp(dt);
		
		REQUIRE(ball1.velocity.x > initialSpeedX);
		REQUIRE(ball1.velocity.y > initialSpeedY);

		ball1.resetBall(ballSpeedX, ballSpeedY);
		REQUIRE(ball1.velocity.x == initialSpeedX);
		REQUIRE(ball1.velocity.y == initialSpeedY);
	}
}
