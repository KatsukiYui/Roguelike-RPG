#include "Game.h"


//initialize all the pointers and get ready for game loop
Game::Game() 
{ 
	//prepare for game loop.. Initialize member Pointers

	graphics = new Graphics();

	map = new Map(); //consists of a 2D tile array and its size
	
	graphics->initializeRects(*map);//initialize rectangles used for drawing things

	mouse = new Mouse();//initialize mouse controller

	keyboard = new Keyboard();//initialize keyboard controller

	Sound::getSoundController()->playBGM();//play the background music

	bool Start = false;//boolean used to exit the while loop that restarts the game and calls the menu again

	//call main menu
	Start = Menu();//if user chooses quit, the following loop never starts

	while (Start) //while the user isnt choosing to quit or
	{

		battleOn = false;//boolean used to exit the combat loop
		Dead = false;//boolean used to exit the Explore game loop


		discardOn = false;//boolean used to print the discard item text box

		srand(time(0));//used for rng battle counter

		//rng battle counter..generte the number of steps the player can take before battle (between max and min steps)
		stepsToBattle = (int)(rand() % (MaxSteps - MinSteps + 1)) + MinSteps;

		Item* firstSword = new Item(starterSword());//generate random starter sword
		inventory = new Inventory(graphics->getInventoryRect());
		inventory->Add(firstSword);//add random starter sword to inventory

		initMap();//initialize the map with wall tiles

		cave = new Cave(*map); //update the grid with rooms and corridors to make the cave

		player = new Player(cave->getRoomAt(0).getCorner1().X, cave->getRoomAt(0).getCorner1().Y, 1);//x and y position, level
		
		player->Move(*map, true, graphics->getPlayerFrameRect(), keyboard); //its the start of the game so just place the player sprite

		//save player position for checks next frame.. to check if the player moved and decrement the steps timer
		oldPos.X = player->getX();
		oldPos.Y = player->getY();

		//place chests in rooms
		chestPlace = new ChestPlacement(*(firstSword->getSword()));//pass the starter sword, to ommit it from the chests
		chestPlace->placeChests(*cave, map);//update map with chest tiles based on the room numbers

		map->View(player->getX(), player->getY());//make the view map (smaller map surrounding the player 11*11)

		//call explore game loop.. real time loop where payer moves and collects items
		Explore();

		Start = Menu();//call menu again if the player dies, wins or hits the X button
	}

}

//delete all the pointers
Game::~Game()
{
	//delete ptrs
	delete mouse;
	delete player;
	delete chestPlace;
	delete keyboard;
	delete graphics;
	delete cave;
	delete map;
	delete inventory;
}

//gameloop for exploring.. walking picking up items
void Game::Explore()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	graphics->drawMap(*map);//loop and draw the map

	while (event.type != SDL_QUIT && !Dead)//gameloop for exploring the cave. 
	{                                      //loops till player HP is 0, player wins by opening legendary sword or X button is hit

		fpsStartTime = SDL_GetTicks();//set fps timer to the time at start of frame, to add delay later

		SDL_PollEvent(&event);//poll event for X button checks

		graphics->Clear();//clear window

		player->Move(*map, false, graphics->getPlayerFrameRect(), keyboard);//move and animate the player if keyboard buttons are pressed

		map->View(player->getX(), player->getY());//make the view map (smaller map surrounding the player)

		graphics->drawMap(*map);//loop and draw the map

		graphics->drawInventory(inventory);//loop and draw inventory menu

		graphics->drawBars(player->getHP(), player->getMaxHP(), player->getLevel(), HPBar);//draw the HP bar
		graphics->drawBars(player->getExp(), player->getMaxExp(), player->getLevel(), ExpBar);//draw the Exp bar

		manageExploreInput();//check for mouse input on buttons or shift key pressed to open chests

		stepCheck();//update the steps timer, check if it is time for battle

		lvlCheck();//check if player level is 3 to spawn legendary sword

		graphics->Present();//print frame

		regulateFPS();//add variable delay depending on the time it took to process this frame
	}

}

//gameloop for combat.. turn based
void Game::Combat()
{
	srand(time(0));//used for spawning random enemies

	SDL_Event event;
	SDL_PollEvent(&event);
	battleOn = true;//used to exit the loop if player won or died
	enemyTurn = false;//used to make the enemy attack in the next frame after the player attacks

	Enemy Enem(NoElement, 1);
	spawnEnemy(Enem);//spawn a random enemy

	bool itemSelectOn = false;//used to print inventory menu and wait for user to select an item

	//combat loop
	while (event.type != SDL_QUIT && battleOn)
	{
		fpsStartTime = SDL_GetTicks();//set fps timer to the time at start of frame, to add delay later

		graphics->Clear();//clear window

		SDL_PollEvent(&event);//poll event for X button checks

		graphics->drawEnemy(Enem.getElement(), &itemSelectOn);//draw enemy sprite

		if (enemyTurn) { enemyAttack(&Enem); };//if the player attacked (last frame) then its the enemy's turn to attack

		manageCombatInput(&Enem);//input checks for the combat buttons, takes enemy object to lower its HP if the player clicked attack

		graphics->drawBars(player->getHP(), player->getMaxHP(), player->getLevel(), HPBar);//draw the HP bar
		graphics->drawBars(Enem.getHP(), Enem.getMaxHP(), Enem.getLevel(), EnemyHPBar);//draw the enemy HP bar

		if (Enem.getHP() <= 0)//if the enemy died
		{
			battleOn = false;//end battle loop
			player->levelUp(Enem.getEXP());//add exp to the player and check if they leveled up
		}

		if (player->getHP() <= 0)
		{
			Dead = true;//end explore loop
			battleOn = false;//end battle loop
		}

		graphics->Present();//print frame

		regulateFPS();//add variable delay depending on the time it took to process this frame
	}

	//recalculate the number of steps till next battle
	stepsToBattle = (int)(rand() % (MaxSteps - MinSteps + 1)) + MinSteps;
}

//menu loop
bool Game::Menu()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	bool instructionsOn = false;//used to print the instructions screen instead of menu screen
	int Choice = 0;//used for button input

	while (event.type != SDL_QUIT && (Choice == 0 || Choice == 2))//while no choice or Instructions
	{
		mouse->updateInput();//update mouse position and if it was clicked

		SDL_PollEvent(&event);//poll event for X button checks

		fpsStartTime = SDL_GetTicks();//set fps timer to the time at start of frame, to add delay later

		graphics->Clear();//clear window

		graphics->drawMenu(instructionsOn);//draw the menu screen if instructions on is false, else draw instructions screen

		if (mouse->getMouseClicked())//if the mouse was left clicked
		{

			//checking for mouse left click on each of the menu buttons
			C1.X = 150 * ((float)graphics->getWindowSize().X / 600);//button started at 150 X when window width is 600
			C1.Y = 300 * ((float)graphics->getWindowSize().Y / 600);
			C2.X = C1.X + 300 *((float)graphics->getWindowSize().X / 600);
			C2.Y = C1.Y + 75 * ((float)graphics->getWindowSize().Y / 600);

			if (mouse->leftClick(C1, C2))//check if the mouse was within these coordinates/corners
			{
				Choice = 1;//start explore loop
				Sound::getSoundController()->playButton();//play button sound effect
			}

			C1.X = 150 * ((float)graphics->getWindowSize().X / 600);//button started at 150 X when window width is 600
			C1.Y = 400 * ((float)graphics->getWindowSize().Y / 600);
			C2.X = C1.X + 300 * ((float)graphics->getWindowSize().X / 600);
			C2.Y = C1.Y + 75 * ((float)graphics->getWindowSize().Y / 600);

			if (mouse->leftClick(C1, C2))//check if the mouse was within these coordinates/corners when it was left clicked
			{
				Choice = 2;//instructions
				Sound::getSoundController()->playButton();//play button sound effect
				instructionsOn = true;//print instructions screen and wait for used to press back
			}

			C1.X = 150 * ((float)graphics->getWindowSize().X / 600);//button started at 150 X when window width is 600
			C1.Y = 500 * ((float)graphics->getWindowSize().Y / 600);
			C2.X = C1.X + 300 * ((float)graphics->getWindowSize().X / 600);
			C2.Y = C1.Y + 75 * ((float)graphics->getWindowSize().Y / 600);

			if (mouse->leftClick(C1, C2))//check if the mouse was within these coordinates/corners
			{
				Choice = 3;//quit, quits menu and the entire game
				Sound::getSoundController()->playButton();//play button sound effect
			}

		}

		if (instructionsOn)//check for back button pressed
		{
			if (mouse->getMouseClicked())//if the mouse was left clicked
			{
				C1.X = 450 * ((float)graphics->getWindowSize().X / 600);//button started at 450 X when window width is 600
				C1.Y = 20 * ((float)graphics->getWindowSize().Y / 600);
				C2.X = C1.X + 330 * ((float)graphics->getWindowSize().X / 600);
				C2.Y = C1.Y + 50 * ((float)graphics->getWindowSize().Y / 600);

				if (mouse->leftClick(C1, C2))//check if the mouse was on this button when it was left clicked
				{
					Choice = 0;//back to menu
					Sound::getSoundController()->playButton();//play button sound effect
					instructionsOn = false;//exit instructions screen and print menu screen instead
				}
			}
		}

		graphics->Present();//print frame

		regulateFPS();//add variable delay depending on the time it took to process this frame

	}

	if (event.type == SDL_QUIT)//if the used hit the X button
	{
		Choice = 0;//no choice
	}

	switch (Choice)
	{
	case 1:
		return true;//start game
		break;
	case 3:
		return false;//quit
		break;
	case 0:
		return false;//user hit the X button on the window
		break;
	}
}

//randomly generates a starter sword of level 1
Sword Game::starterSword()
{
	srand(time(0));

	Sword S1(NoElement, 1);

	switch ((int)(rand() % 3))//start with a random Sword of level 1 and random element
	{
	case 0:
		S1.setElement(Fire);
		break;
	case 1:
		S1.setElement(Water);
		break;
	case 2:
		S1.setElement(Earth);
		break;
	}

	return S1;
}

//initializes the entire map with wall tiles, before rooms and chests are carved into it
void Game::initMap()
{
	//a grid of tiles.. the game map

	for (int r = 0; r < map->mapR; r++)
	{
		for (int c = 0; c < map->mapC; c++)
		{

			Tile Wall(Wall); //making a wall tile of size window/mapSize and type wall
			map->setTileAt(r, c, Wall); //setting all the Map Tiles to be walls
		}
	}
}

//spawns an enemy whose level is set accoridng to player location and level and with a random element
void Game::spawnEnemy(Enemy &Enem)
{
	srand(time(0));

	switch ((int)(rand() % 3))//Spawn an enemy or random element
	{
	case Fire:
		Enem.setElement(Fire);
		break;
	case Water:
		Enem.setElement(Water);
		break;
	case Earth:
		Enem.setElement(Earth);
		break;
	}

	int roomNo;

	//check if the player is in a room or not, update roomNo. if so
	if (cave->findRoom(&roomNo, player->getX(), player->getY()))//if the player is in a room.. spawn an enemy with a suitable lvl for the room no.
	{
		Enem.setLevel((roomNo / 4) + 1); //room no(0-8)/4-> (0-2)+1 -> (1-3)
	}
	else//if the player is in a corridor
	{
		Enem.setLevel(player->getLevel());//spawn an enemy with the same lvl as the player
	}
}

//mouse and keyboard input management for the explore game loop
void Game::manageExploreInput()
{
	mouse->updateInput();//update mouse position and if it was clicked

	if (keyboard->Update() == Shift)//if the player presses shift
	{
		for (int i = 0; i < chestPlace->getChestsSize(); i++)
		{
			//if the player hits shift and theyre on the right,left etc of the chest
			if ((player->getX() >= chestPlace->getChestAt(i)->getX() - 1 && player->getX() <= chestPlace->getChestAt(i)->getX() + 1) && (player->getY() == chestPlace->getChestAt(i)->getY())
				|| ((player->getY() >= chestPlace->getChestAt(i)->getY() - 1 && player->getY() <= chestPlace->getChestAt(i)->getY() + 1)) && (player->getX() == chestPlace->getChestAt(i)->getX()))
			{
				//only has an effect if the chest has not been opened before
				chestPlace->getChestAt(i)->openChest(&Dead, inventory);//add the item onto inventory or incase of legendary chest, end the game
			}

		}
	}

	if (mouse->getMouseClicked())//if the mouse was left clicked
	{
		//check if it was clicked on any of the inventory slots
		for (int i = 0; i < inventory->getInventorySize(); i++)
		{
			C1.X = inventory->getSlotPosAt(i).x - inventory->getSlotWidth() * 0.35;//small change since i decided to draw items in the middle of the inventory slot
			C1.Y = inventory->getSlotPosAt(i).y - inventory->getSlotHeight() * 0.25;
			C2.X = C1.X + inventory->getSlotWidth();
			C2.Y = C1.Y + inventory->getSlotHeight();

			if (mouse->leftClick(C1, C2))//check if the mouse was left clicked within these coordinates/corners
			{
				discardOn = true;//used to print discard text box and wait for input
				inventory->setSelectedItem(i);//set the selected item to the item that was clicked
				Sound::getSoundController()->playButton();//play button sound effect

			}

		}
	}

	if (discardOn)//if the player clicked an inventory item
	{
		graphics->drawTextBox(DiscardTexture);//draw discard text box

		if (mouse->getMouseClicked())
		{
			//260, 15...size 150*45.. 420, 15 yes and no button pos and size
			C1.X = graphics->getTextBoxRect().x + (260 * graphics->getTextBoxRect().w / 600); //for scaling 
			C1.Y = graphics->getTextBoxRect().y + 15;//the Ys are fixed in the inventory menu
			C2.X = C1.X + (150 * graphics->getTextBoxRect().w / 600);
			C2.Y = C1.Y + 45;
			//yes button clicked?.. is the mouse on the yes button
			if (mouse->leftClick(C1, C2))
			{
				inventory->Discard(inventory->getSelectedItem()); //discard the selected item
				discardOn = false;//stop drawing the discard text box
				Sound::getSoundController()->playButton();//play button sound effect

			}

			C1.X = graphics->getTextBoxRect().x + (420 * graphics->getTextBoxRect().w / 600);
			C1.Y = graphics->getTextBoxRect().y + 15;
			C2.X = C1.X + (150 * graphics->getTextBoxRect().w / 600);
			C2.Y = C1.Y + 45;
			//No button clicked?.. is the mouse on the no button
			if (mouse->leftClick(C1, C2))
			{
				discardOn = false;//stop drawing the discard text box
				Sound::getSoundController()->playButton();//play button sound effect
			}

		}
	}

}

//mouse input management for the combat loop
void Game::manageCombatInput(Enemy * Enem)
{
	mouse->updateInput();

	int OpponentHp;//used for the attack functions
	Elements OpponentEle;

	if (!itemSelectOn)//if the player didnt choose to select items
	{
		if (mouse->getMouseClicked())//if the mouse was left clicked
		{
			C1.X = graphics->getInventoryRect().x + (300 * graphics->getInventoryRect().w / 600);
			C1.Y = graphics->getInventoryRect().y + 100;
			C2.X = C1.X + (300 * graphics->getInventoryRect().w / 600);
			C2.Y = C1.Y + 100;
			//Run button clicked?.. is the mouse on the Run button?
			if (mouse->leftClick(C1, C2))
			{
				battleOn = false;//end battle
				Sound::getSoundController()->playButton();//play button sound effect
			}

			C1.X = graphics->getInventoryRect().x;
			C1.Y = graphics->getInventoryRect().y;
			C2.X = C1.X + graphics->getInventoryRect().w;
			C2.Y = C1.Y + 100;
			//Attack button clicked?.. is the mouse on the attack button?
			if (mouse->leftClick(C1, C2))
			{
				Sound::getSoundController()->playButton();//play button sound effect
				OpponentHp = Enem->getHP();//set the opponent to be the enemy
				OpponentEle = Enem->getElement();
				inventory->getSelectedSword()->Attack(&(OpponentHp), OpponentEle);//make the sword attack the enemy
				Sound::getSoundController()->playAttack();//play Attack sound effect
				Enem->setHP(OpponentHp);//update enemy hp

				enemyTurn = true;//make the enemy attack next frame
			}

			C1.X = graphics->getInventoryRect().x;
			C1.Y = graphics->getInventoryRect().y + 100;
			C2.X = C1.X + (300 * graphics->getInventoryRect().w / 600);
			C2.Y = C1.Y + 100;
			//Items button clicked?.. was the mouse on the items button?
			if (mouse->leftClick(C1, C2))
			{
				itemSelectOn = true;//print inventory/item selection menu and wait for an item to be selected
				Sound::getSoundController()->playButton();//play button sound effect
			}

		}
	}
	else //item selection menu
	{
		graphics->drawInventory(inventory);//loop and draw inventory menu

		if (mouse->getMouseClicked())//if the mouse was left clicked
		{
			//checking if the mouse is on any of the inventory slots
			for (int i = 0; i < inventory->getInventorySize(); i++)
			{
				C1.X = inventory->getSlotPosAt(i).x - inventory->getSlotWidth() * 0.35;//small change since i decided to draw items in the middle of the inventory slot
				C1.Y = inventory->getSlotPosAt(i).y - inventory->getSlotHeight() * 0.25;
				C2.X = C1.X + inventory->getSlotWidth();
				C2.Y = C1.Y + inventory->getSlotHeight();

				if (mouse->leftClick(C1, C2))//check if the mouse was left clicked within these coordinates/corners
				{
					inventory->setSelectedItem(i);//set the sleected item to the item clicked
					itemSelectOn = false;//end item selection, draw combat menu instead
					Sound::getSoundController()->playButton();//play button sound effect
				}

			}

		}
	}

	if (inventory->getSelectedItemType() == potionT)//if a potion was selected.. heal and discard it
	{
		inventory->getSelectedPotion()->healPlayer(player);//heal the player
		inventory->Discard(inventory->getSelectedItem());//discard the potion
	}
}

//checks if the player has moved during this frame, if so decrement the counter and reset the old player position. 
//Then checks if the steps to battle counter is equal to 0, if so start combat loop. 
void Game::stepCheck()
{
	//decrement the step to battle counter, if the player moved
	if (!(player->getX() == oldPos.X && player->getY() == oldPos.Y))
	{
		oldPos.X = player->getX();//save the player's current position for the same check next frame
		oldPos.Y = player->getY();
		stepsToBattle--;//decrement the steps timer
	}

	//start the Combat if the counter reaches 0
	if (stepsToBattle == 0)
	{
		Combat();//combat loop
	}
}

//checks if the player's level has reached 3, if so spawn the legendary chest in the final room(opening it ends the game)
void Game::lvlCheck()
{
	if (player->getLevel() == 3)//if the player reaches level 3
	{
		chestPlace->spawnLegendaryChest(*cave, map);//spawn legendary chest in room 9 and update the map
	}
}

//if the bool enemyTurn is true, the enemy attacks, lowering the player's hp
void Game::enemyAttack(Enemy * Enem)
{
	int OpponentHp;//used for the attack functions
	Elements OpponentEle;

	SDL_Delay(500);//small delay between player and enemy attacks just for a nice effect

	OpponentHp = player->getHP();//set the opponent to be the player
	OpponentEle = inventory->getSelectedSword()->getElement();
	Enem->Attack(&(OpponentHp), OpponentEle);//make enemy attack the player
	Sound::getSoundController()->playAttack();//play Attack sound effect
	player->setHP(OpponentHp);//update player HP

	enemyTurn = false;//end enemy turn
}

//used to add a varliable sdl delay based on the current time it takes to process a frame. This makes the FPS fixed.
void Game::regulateFPS()
{
	//if time passed from the start of the frame is less that the frame rate, add a delay = to the difference
	if ((SDL_GetTicks() - fpsStartTime) < (1000 / FPS))
	{
		SDL_Delay((1000 / FPS) - (SDL_GetTicks() - fpsStartTime));
	}
}

