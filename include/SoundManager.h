#pragma once
#include "raylib.h"


class SoundManager
{
private:
	
	Sound homeScreenSound;
	Sound winningRoundSound;
	Sound losingRoundSound;
	Sound losingSound;
	Sound winningSound;
	Sound ballHitBoundsSound;
	Sound ballHitPaddleSound;

	bool isGameOverSoundPlayed = false;
	bool isHomeScreenSoundPlaying = false;
	
	void loadAssets();

public:

	SoundManager();
	~SoundManager();
	
	void playHomeScreenSound();
	void playWinningRoundSound();
	void playLosingRoundSound();
	void playLosingSound();
	void playWinningSound();
	void playBallHitBoundsSound();
	void playBallHitPaddleSound();

	void stopEndGameSounds();
	void stopHomeScreenSound();
};













