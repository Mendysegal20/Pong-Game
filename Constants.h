#pragma once

const int windowWidth = 1280;
const int windowHeight = 829;

const int middleScreenX = windowWidth / 2;
const int middleScreenY = windowHeight / 2;

const int paddlePosX = 1280 - 35;
const int paddlePosY = windowHeight / 2 - 60;

const int cpuPaddlePosX = 10;

const int paddleWidth = 25;
const int paddleHeight = 120;
const int paddleSpeed = 7;

const float ballSpeedX = 7;
const float ballSpeedY = 7;
const int radius = 15;


const int textPosX = windowWidth / 4 - 20;
const int textPosY = 20;
const int fontSize = 80;

const char bgPath[20] = "assets/bg.png";
const char fontPath[30] = "assets/JosefinSans.ttf";
const char losingSoundPath[30] = "assets/game-over-sound.mp3";
const char winningSoundPath[30] = "assets/winning-sound.mp3";
const char winningRoundSoundPath[30] = "assets/winning-round.wav";
const char losingRoundSoundPath[30] = "assets/losing-point-sound.mp3";
const char touchingBoundsSound[30] = "assets/ball-bounds-sound.wav";
const char hittingBallPaddleSound[30] = "assets/ball-paddle-sound.wav";




