#pragma once
#include "raylib.h"


class SoundManager
{
private:
	
	Sound winningRoundSound;
	Sound losingRoundSound;
	Sound losingSound;
	Sound winningSound;
	Sound ballHitBoundsSound;
	Sound ballHitPaddleSound;

	bool isGameOverSoundPlayed = false;
	void loadAssets();

public:

	SoundManager();
	~SoundManager();
	
	void playWinningRoundSound();
	void playLosingRoundSound();
	void playLosingSound();
	void playWinningSound();
	void playBallHitBoundsSound();
	void playBallHitPaddleSound();

};













