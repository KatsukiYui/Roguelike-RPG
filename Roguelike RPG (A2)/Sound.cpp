#include "Sound.h"

Sound* Sound::soundController = nullptr;

//private constructor
Sound::Sound()
{
	//loading sound files
	BGM = Mix_LoadMUS("Conquest_loop.mp3");

	Mix_VolumeMusic(20); //lowering the BGM volume.. thank me later

	Button = Mix_LoadWAV("Menu Sound Effect.wav");

	Attack = Mix_LoadWAV("Attack Sound Effect.wav");
};

//returns the static instance. Used to call the functions
Sound *Sound::getSoundController()
{
	if (soundController == nullptr)//if the pointer was not initialized
	{
		soundController = new Sound();//initialize the pointer and create a new Sound object on the heap
	}

	return soundController;//return the only instance
}

//plays the BGM
void Sound::playBGM()
{
	Mix_PlayMusic(BGM, -1);//-1 for infinite looping

}

//plays the attack sound effect whenever the player or enemy attack
void Sound::playAttack()
{
	Mix_PlayChannel(-1, Attack, 0);
}

//plays the button sound effect whenever a button is pressed
void Sound::playButton()
{
	Mix_PlayChannel(-1, Button, 0);
}

