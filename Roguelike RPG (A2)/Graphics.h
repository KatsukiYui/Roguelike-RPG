#ifndef _GRAPHICS_
#define _GRAPHICS_

#include <iostream>

#include "Sword.h"
#include "Enemy.h"
#include "Player.h"
#include "Inventory.h"
#include "Mouse.h"
#include "ChestPlacement.h"
#include "Text.h"
#include "Sound.h"

enum textID//type of texture to draw. Used to extract textures from the texture vector
{WallTexture, PlayerTexture, InventoryTexture, DiscardTexture, SwordTextures, PotionTexture, ChestTexture,
FireEnemyTexture, WaterEnemyTexture, EarthEnemyTexture, CombatMenuTexture, MainMenuTexture, InstructionsTexture};


enum Bars{HPBar, ExpBar, EnemyHPBar};//type of status bar to draw

//graphics management class
class Graphics
{
protected:


	SDL_Window *Window;
	SDL_Renderer *Renderer;
	SDL_Surface *Surface;//surface used to make textures and load images
	std::vector<std::pair<textID, SDL_Texture*>> gameTextures;//game texture and its name/ID

	SDL_Rect invenRect;//rectangle used to print the inventory texture
	SDL_Rect textBox;//used to output text boxes
	SDL_Rect tileRect; //rectangle used to draw tiles
	SDL_Rect enemyRect;//rect used to draw enemy
	SDL_Rect *Frame;//rectangle used to crop the animation frames from the player sprite sheet
	SDL_Rect sTex;//used to get an individual sword from the texture

public:

	//create window and renderer,load all the image files and push them onto the vector
	Graphics();

	//empty texture vector and delete any pointers
	~Graphics();

	//initializes the class's sdl rects with suitable values
	void initializeRects(Map _map);

	//returns the sdl texture with the passed ID from the texture vector
	SDL_Texture* getTextureCalled(textID _name);

	//uses sdl render copy and the texture's ID to extract the correct texture then draw it
	void Draw(textID _text, SDL_Rect* Crop, SDL_Rect* Place);

	//loops through the map and draws it
	void drawMap(Map _map);

	//draws the inventory menu and all the items and their level
	void drawInventory(Inventory *_inven);

	//draws the enemy texture during combat
	void drawEnemy(Elements _ele, bool *_itemSelectOn);

	//currently only draws the discard item textbox. Used for printing textboxes that show up above the inventory menu
	void drawTextBox(textID _text);

	//according to the bar name/ID passed, it draws a status bar witht he suitable color.
	void drawBars(int _width, int _maxWidth, int _lvl, Bars _bar);

	//draws the menu screen. If Instructions on is true, draws the instructions screen instead.
	void drawMenu(bool _InstructionsOn);

	//calls render clear with the color black
	void Clear();

	//calls render present
	void Present();

	//returns a vector(x, y) of the current width and height of the sdl window, using SDL get windowsize.
	Vec2 getWindowSize();

	//getter functions for rectangles used outside the class.
	//rectangle used to crop the animation frames from the player sprite sheet
	SDL_Rect* getPlayerFrameRect();

	//used to get an individual sword from the texture
	SDL_Rect getSwordTextureRect();

	//rectangle used to print the inventory texture
	SDL_Rect getInventoryRect();

	//used to output text boxes
	SDL_Rect getTextBoxRect();


};


#endif