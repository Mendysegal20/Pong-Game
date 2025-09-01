#include "SoundManager.h"
#include "Constants.h"


SoundManager::SoundManager()
{
	InitAudioDevice();
	isGameOverSoundPlayed = false;
	loadAssets();
}


void SoundManager::loadAssets()
{
	winningRoundSound = LoadSound(winningRoundSoundPath);
	losingRoundSound = LoadSound(losingRoundSoundPath);
	winningSound = LoadSound(winningSoundPath);
	losingSound = LoadSound(losingSoundPath);
	ballHitBoundsSound = LoadSound(touchingBoundsSound);
	ballHitPaddleSound = LoadSound(hittingBallPaddleSound);
}



SoundManager::~SoundManager()
{
	UnloadSound(winningRoundSound);
	UnloadSound(losingRoundSound);
	UnloadSound(winningSound);
	UnloadSound(losingSound);
	UnloadSound(ballHitBoundsSound);
	UnloadSound(ballHitPaddleSound);
	CloseAudioDevice();
}



void SoundManager::playWinningRoundSound()
{
	PlaySound(winningRoundSound);
}

void SoundManager::playLosingRoundSound()
{
	PlaySound(losingRoundSound);
}


void SoundManager::playWinningSound()
{
	// we play the appropriate end-game sound (win or lose), only once
	if(!isGameOverSoundPlayed)
	{
		PlaySound(winningSound);
		isGameOverSoundPlayed = true;
	}
}


void SoundManager::playLosingSound()
{
	
	if(!isGameOverSoundPlayed)
	{
		PlaySound(losingSound);
		isGameOverSoundPlayed = true;
	}
}


void SoundManager::playBallHitBoundsSound()
{
	PlaySound(ballHitBoundsSound);
}

void SoundManager::playBallHitPaddleSound()
{
	PlaySound(ballHitPaddleSound);
}





