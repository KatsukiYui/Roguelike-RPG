#include "Player.h"

Player::Player(int _x, int _y, int _lvl)
	:InGameObject(_x, _y, _lvl)
{//HP and maxEXP are calculated from level
	HP = (Level - 1) * 25 + 50;//HP = 50 at lvl 1, 75 at lvl 2, 100 at lvl 3
	maxHP = HP;
	Exp = 0;
	maxExp = _lvl * 100;

	//initializing the frames array
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			Frames[i][j].X = 48 * j;//sprite sheet has 4 rows and 3 columns
			Frames[i][j].Y = 48 * i;
		}


	}

	startTime = SDL_GetTicks();//start the timer used for animation frames
};


void Player::setHP(int _hp) { HP = _hp; };
void Player::setExp(int _exp) { Exp = _exp; };

int Player::getHP() { return HP; };
int Player::getExp() { return Exp; }
int Player::getMaxHP()
{
	return maxHP;
}
int Player::getMaxExp()
{
	return maxExp;
}


//places the player at the start of the game and moves the player sprite according to keyboard entry
void Player::Move(Map &_map, bool _start, SDL_Rect *_frame, Keyboard * _key)
{

	Tile P(PlayerSp);//tile with type player sprite
	Tile E(Empty);//tile with type empty

	if (_start)//place the player if its the start of the game
	{
		_map.setTileAt(yPos, xPos, P);//set map tile at the player's position to a player tile
		prevstepTime = SDL_GetTicks();//save the time at which the player was placed/last moved
		Animate(Down, _frame);//set animation frame to the down direction (prints player sprite faced towards the screen)
	}
	else//if the function is called in the gameLoop so not at the start
	{

		int tempX = xPos;//current/soon to be old position
		int tempY = yPos;

		switch (_key->Update())//returns a key ID/name from the key enum
		{
		case Up:
			if (_map.getTileAt((yPos - 1), xPos).getType() == Empty && (SDL_GetTicks() - prevstepTime) >= (1000 / stepsPerSec))//Y = 0 is top left corner in SDL so invert the movement
			{//if the tile to the player's south is empty & if it has been 1000/stepsPerSec ms since last movement 
				yPos--;//update player's position
				_map.setTileAt(tempY, tempX, E);//update tile at player's old position to empty
				_map.setTileAt(yPos, xPos, P);//update tile at new position to the player's sprite tile
				prevstepTime = SDL_GetTicks();//reset the timer
				Animate(Up, _frame);//update the animation frame according to current movement direction
			}
			break;

		case Down:
			if (_map.getTileAt((yPos + 1), xPos).getType() == Empty && (SDL_GetTicks() - prevstepTime) >= (1000 / stepsPerSec))
			{//if the tile to the player's north is empty & if it has been 1000/stepsPerSec ms since last movement 
				yPos++;//update player's position
				_map.setTileAt(tempY, tempX, E);//update tile at player's old position to empty
				_map.setTileAt(yPos, xPos, P);//update tile at new position to the player's sprite tile
				prevstepTime = SDL_GetTicks();//reset the timer
				Animate(Down, _frame);//update the animation frame according to current movement direction
			}
			break;

		case Right:
			if (_map.getTileAt(yPos, (xPos + 1)).getType() == Empty && (SDL_GetTicks() - prevstepTime) >= (1000 / stepsPerSec))
			{//if the tile to the player's right is empty & if it has been 1000/stepsPerSec ms since last movement 
				xPos++;//update player's position
				_map.setTileAt(tempY, tempX, E);//update tile at player's old position to empty
				_map.setTileAt(yPos, xPos, P);//update tile at new position to the player's sprite tile
				prevstepTime = SDL_GetTicks();//reset the timer
				Animate(Right, _frame);//update the animation frame according to current movement direction
			}
			break;

		case Left:
			if (_map.getTileAt(yPos, (xPos - 1)).getType() == Empty && (SDL_GetTicks() - prevstepTime) >= (1000 / stepsPerSec))
			{//if the tile to the player's left is empty & if it has been 1000/stepsPerSec ms since last movement 
				xPos--;//update player's position
				_map.setTileAt(tempY, tempX, E);//update tile at player's old position to empty
				_map.setTileAt(yPos, xPos, P);//update tile at new position to the player's sprite tile
				prevstepTime = SDL_GetTicks();//reset the timer
				Animate(Left, _frame);//update the animation frame according to current movement direction
			}
			break;
		}
	}

};

//goes through animation frames according to the direction of movement
void Player::Animate(Keys _dir, SDL_Rect *_frame)
{
	//the up and down animations looked a bit too fast and unnatural so i slowed them down
	int frameVRate = 6;//animation vertical and horiontal frame rate
	int frameHRate = 9;

	/*(time rn - startTime) * framerate..how many frames passed in between start time and now(in ms)
	/ 1000.. to get seconds %3 (number of frames) .. to calculate the current frame */
	int currentVFrame = ((SDL_GetTicks() - startTime) * frameVRate / 1000) % 3;
	int currentHFrame = ((SDL_GetTicks() - startTime) * frameHRate / 1000) % 3;


	switch (_dir)
	{
	case Up: //the sprite sheet has 4 rows of the character going down, Left, Right then Up

		_frame->x = Frames[3][currentVFrame].X;
		_frame->y = Frames[3][currentVFrame].Y;

		break;

	case Down:

		_frame->x = Frames[0][currentVFrame].X;
		_frame->y = Frames[0][currentVFrame].Y;

		break;

	case Right:

		_frame->x = Frames[2][currentHFrame].X;
		_frame->y = Frames[2][currentHFrame].Y;

		break;

	case Left:

		_frame->x = Frames[1][currentHFrame].X;
		_frame->y = Frames[1][currentHFrame].Y;

		break;
	}
}

//adds exp to player, and checks if the player's current exp + exp passed > maxExp, if so level up! (level cap is 3)
void Player::levelUp(int _exp)
{
	if (Exp + _exp >= maxExp)//level up!
	{
		Exp = maxExp - (Exp + _exp); //update exp to the difference
		Level++;//increase level
		maxExp = Level * 100;//update maxExp
	}
	else//otherwise just add _exp gained to current Exp
	{
		Exp += _exp;
	}
}
