#ifndef _GAME_
#define _GAME_

#include "Graphics.h"

//used for rng for the combat counter. Used with rand to generate a number of steps between max and min the player can take, before a combat is started.
//no this is totally not like pokemon..
#define MaxSteps 30//max number of steps the player can take before combat
#define MinSteps 10//min number of steps the player can take before combat

#define FPS 60 //number of frames per second, used to make a variable sdl delay

class Game//game class with both the game loops and the menu loops
{
protected:

	Graphics *graphics;//graphics controller
	Keyboard *keyboard;//keyboard controller
	Mouse *mouse; //mouse controller
	Inventory *inventory;//Inventory manager
	Player *player;//player manager
	ChestPlacement *chestPlace;//chest manager
	Cave *cave;//room manager
	Map *map;//Map Manager

	int stepsToBattle;//counter.. counts down to combat start.. is decremented everytime the player takes a step
	Vec2 oldPos;//used for movement check to decrement the steps to battle timer
	bool Dead;//bool used to exit the explore game loop
	bool battleOn;//bool used to enter and exit combat loop
	bool discardOn;//bool used to enable item discard.. when true, discard text box and buttons appear
	bool itemSelectOn;//bool used during combat to print inventory instead of combat menu and enable player to select an item
	bool enemyTurn;//this bool is set to true after the player attacks.. enables enemy to attack in the next frame

	int fpsStartTime;//used to set a fixed fps, by making a variable sdl delay.. this variable is set to the time at the start of every frame

	//used for mouse checks
	Vec2 C1;//corner 1 of button
	Vec2 C2;//corner 2

public:

	//initialize all the pointers and get ready for game loop
	Game();

	//delete all the pointers
	~Game();

	//gameloop for exploring.. walking picking up items
	void Explore();

	//gameloop for combat.. turn based
	void Combat();

	//menu loop
	bool Menu();

	//randomly generates a starter sword of level 1
	Sword starterSword();

	//initializes the entire map with wall tiles, before rooms and chests are carved into it
	void initMap();

	//spawns an enemy whose level is set accoridng to player location and level and with a random element
	void spawnEnemy(Enemy &Enem);

	//mouse and keyboard input management for the explore game loop
	void manageExploreInput();

	//mouse input management for the combat loop
	void manageCombatInput(Enemy *Enem);

	//checks if the player has moved during this frame, if so decrement the counter and reset the old player position. 
	//Then checks if the steps to battle counter is equal to 0, if so start combat loop. 
	void stepCheck();
	
	//checks if the player's level has reached 3, if so spawn the legendary chest in the final room(opening it ends the game)
	void lvlCheck();

	//if the bool enemyTurn is true, the enemy attacks, lowering the player's hp
	void enemyAttack(Enemy *Enem);
	
	//used to add a variable sdl delay based on the current time it takes to process a frame. This makes the FPS fixed.
	void regulateFPS();

};




#endif