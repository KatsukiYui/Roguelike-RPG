#ifndef _SOUND_
#define _SOUND_

#include <SDL_mixer.h>

class Sound//Sound manager. I wanted to try and make a singleton for this class
{
private:

	Mix_Music *BGM;//background music
	Mix_Chunk *Attack; //attack sound effect
	Mix_Chunk *Button;//button click sound effect

	static Sound *soundController;//only instance

	//private constructor
	Sound();
	
public:

	//returns the static instance. Used to call the functions
	static Sound *getSoundController();

	//plays the BGM
	void playBGM();

	//plays the attack sound effect whenever the player or enemy attack
	void playAttack();

	//plays the button sound effect whenever a button is pressed
	void playButton();

};





#endif
