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
	homeScreenSound = LoadSound(homeScreenSoundPath);
	winningRoundSound = LoadSound(winningRoundSoundPath);
	losingRoundSound = LoadSound(losingRoundSoundPath);
	winningSound = LoadSound(winningSoundPath);
	losingSound = LoadSound(losingSoundPath);
	ballHitBoundsSound = LoadSound(touchingBoundsSound);
	ballHitPaddleSound = LoadSound(hittingBallPaddleSound);
}



SoundManager::~SoundManager()
{
	UnloadSound(homeScreenSound);
	UnloadSound(winningRoundSound);
	UnloadSound(losingRoundSound);
	UnloadSound(winningSound);
	UnloadSound(losingSound);
	UnloadSound(ballHitBoundsSound);
	UnloadSound(ballHitPaddleSound);
	CloseAudioDevice();
}



void SoundManager::playHomeScreenSound()
{
	if(!isHomeScreenSoundPlaying)
	{
		isHomeScreenSoundPlaying = true;
		PlaySound(homeScreenSound);
	}
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



void SoundManager::stopHomeScreenSound()
{
	isHomeScreenSoundPlaying = false;
	StopSound(homeScreenSound);
}


void SoundManager::stopEndGameSounds()
{
	isGameOverSoundPlayed = false;
	StopSound(winningSound);
	StopSound(losingSound);
}







