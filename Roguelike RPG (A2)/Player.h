#ifndef _PLAYER_
#define _PLAYER_

#include "InGameObject.h"
#include "Map.h"
#include "Keyboard.h"
#include "Vec2.h"

#define LevelCap 3//max player level
#define stepsPerSec 10 //number of steps that can be taken per second. Used so that the player isnt moving 60 tiles per sec.

class Player:public InGameObject//controls the player's position, animations and status (HP & exp).
{
protected:
	int HP;//health
	int maxHP;//used to stop overhealing and to print the outer HP Bar (empty red rectangle)
	int Exp;//experience
	int maxExp;//used for leveling up and to print the outer Exp Bar (empty green rectangle)

	Vec2 Frames[4][3];// used for animation.. stores an X and Y position for each frame
	int startTime;//animation start time
	int prevstepTime;//The time the prev step was taken. Used to set a fixed number of steps the player can take per second.

public:

	Player(int _x, int _y, int _lvl);

	void setHP(int _hp);
	void setExp(int _exp);

	int getHP();
	int getExp();
	int getMaxHP();
	int getMaxExp();


	//places the player at the start of the game and moves the player sprite according to keyboard entry
	void Move(Map &_map, bool _start, SDL_Rect *_frame, Keyboard *_key);

	//goes through animation frames according to the direction of movement
	void Animate(Keys _dir, SDL_Rect *_frame);

	//adds exp to player, and checks if the player's current exp + exp passed > maxExp, if so level up! (level cap is 3)
	void levelUp(int _exp);

};


#endif