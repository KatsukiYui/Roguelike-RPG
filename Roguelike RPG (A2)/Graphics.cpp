#include "Graphics.h"


//create window and renderer, load all the image files and push them onto the vector
Graphics::Graphics()
{
	//create window and renderer
	Vec2 windowSize{660, 662};//this window size works well for my tiles, so i made it fixed
	Window = SDL_CreateWindow("Roguelike", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowSize.X, windowSize.Y, 0);;
	Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);

	//load in all the pictures and add them to the vector
	//wall texture
	Surface = SDL_LoadBMP("wallx3.BMP");//load picture
	SDL_Texture *wallTexture = SDL_CreateTextureFromSurface(Renderer, Surface);//create a texture from it
	SDL_FreeSurface(Surface);//empty the surface
	gameTextures.emplace_back(WallTexture, wallTexture);//add the texture and its corresponding ID onto the vector

	//player sprite sheet
	Surface = SDL_LoadBMP("Aqua Sprite Sheet (Cropped for animation).BMP"); //144*192 sprite sheet
	SDL_Texture *playerTexture = SDL_CreateTextureFromSurface(Renderer, Surface);
	SDL_FreeSurface(Surface);
	gameTextures.emplace_back(PlayerTexture, playerTexture);


	//load the inventory space picture
	Surface = SDL_LoadBMP("Inventory.BMP"); //600*200 pixels
	SDL_Texture *invenTexture = SDL_CreateTextureFromSurface(Renderer, Surface);
	SDL_FreeSurface(Surface);
	gameTextures.emplace_back(InventoryTexture, invenTexture);


	//inventory discard image
	//260, 15...size 150*45.. 420, 15 yes and no button pos and size
	Surface = SDL_LoadBMP("DiscardTexture.BMP");
	SDL_Texture *disTexture = SDL_CreateTextureFromSurface(Renderer, Surface);
	SDL_FreeSurface(Surface);
	gameTextures.emplace_back(DiscardTexture, disTexture);


	//sword texture sheet
	Surface = SDL_LoadBMP("SwordTextures.BMP"); //600*200 pixels
	SDL_Texture *sTextures = SDL_CreateTextureFromSurface(Renderer, Surface);
	SDL_FreeSurface(Surface);
	gameTextures.emplace_back(SwordTextures, sTextures);


	//potion texture
	Surface = SDL_LoadBMP("PotionTexture.BMP");
	SDL_Texture *potTexture = SDL_CreateTextureFromSurface(Renderer, Surface);
	SDL_FreeSurface(Surface);
	gameTextures.emplace_back(PotionTexture, potTexture);

	//Chest texture
	Surface = SDL_LoadBMP("Pink Chest.BMP");
	SDL_Texture *chestTexture = SDL_CreateTextureFromSurface(Renderer, Surface);
	SDL_FreeSurface(Surface);
	gameTextures.emplace_back(ChestTexture, chestTexture);

	//enemy textures
	//fire
	Surface = SDL_LoadBMP("Mega Flareon.BMP");
	SDL_Texture *fEnemTexture = SDL_CreateTextureFromSurface(Renderer, Surface);
	SDL_FreeSurface(Surface);
	gameTextures.emplace_back(FireEnemyTexture, fEnemTexture);

	//water
	Surface = SDL_LoadBMP("Mega Vaporeon.BMP");
	SDL_Texture *wEnemTexture = SDL_CreateTextureFromSurface(Renderer, Surface);
	SDL_FreeSurface(Surface);
	gameTextures.emplace_back(WaterEnemyTexture, wEnemTexture);

	//earth
	Surface = SDL_LoadBMP("Mega Leafeon.BMP");
	SDL_Texture *eEnemTexture = SDL_CreateTextureFromSurface(Renderer, Surface);
	SDL_FreeSurface(Surface);
	gameTextures.emplace_back(EarthEnemyTexture, eEnemTexture);

	//combat menu texture
	Surface = SDL_LoadBMP("Combat Menu.BMP");
	SDL_Texture *cMenuTexture = SDL_CreateTextureFromSurface(Renderer, Surface);
	SDL_FreeSurface(Surface);
	gameTextures.emplace_back(CombatMenuTexture, cMenuTexture);

	//main menu texture
	Surface = SDL_LoadBMP("Main Menu.BMP");
	SDL_Texture *mMenuTexture = SDL_CreateTextureFromSurface(Renderer, Surface);
	SDL_FreeSurface(Surface);
	gameTextures.emplace_back(MainMenuTexture, mMenuTexture);

	//instructions texture
	Surface = SDL_LoadBMP("Instructions.BMP");
	SDL_Texture *InstTexture = SDL_CreateTextureFromSurface(Renderer, Surface);
	SDL_FreeSurface(Surface);
	gameTextures.emplace_back(InstructionsTexture, InstTexture);

}

//empty texture vector and delete any pointers
Graphics::~Graphics()
{
	//destroy SDL pointers
	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(Window);

	std::vector <std::pair < textID, SDL_Texture*>> ::iterator itr;
	for (itr = gameTextures.begin(); itr != gameTextures.end(); )
	{
		SDL_DestroyTexture(itr->second);//freeing up space 
		itr = gameTextures.erase(itr);//clearing the vector
	}

	//delete ptrs
	delete Frame;

	//Text::cleanUp(); //sdl cleans up its own fonts etc when SDL_Quit is called
}

//initializes the class's sdl rects with suitable values
void Graphics::initializeRects(Map _map)
{
	//Inventory and combat menu rectangle 
	const int invenH = 200;//size of the texture
	const int invenW = 600;
	invenRect.w = getWindowSize().X;
	invenRect.h = invenH;
	invenRect.x = 0;
	invenRect.y = getWindowSize().Y - invenRect.h;

	//used to output text boxes ontop of the inventory menu e.g. the discard item text box
	textBox = invenRect;
	textBox.h = 75;

	//rectangle used to draw tiles
	tileRect.w = (float)getWindowSize().X / (float)(_map.viewC);
	tileRect.h = ((float)(getWindowSize().Y) - (float)(invenH)) / (float)(_map.viewR); //making space for the inventory

	//rect used to draw enemy sprite
	enemyRect.x = 100;
	enemyRect.y = 0;
	enemyRect.w = 400;
	enemyRect.h = 400;

    //rectangle used to crop the animation frames from the player sprite sheet
	Frame = new SDL_Rect;
	Frame->h = 48; //the sprite sheet is 144*192 .. each frame is 48*48
	Frame->w = 48;

    //used to get an individual sword from the texture of 3 swords
	sTex.w = 70;
	sTex.h = 70;
};

//returns the sdl texture with the passed ID from the texture vector
SDL_Texture * Graphics::getTextureCalled(textID _name)
{

	for (int i = 0; i < gameTextures.size(); i++)//loop through the texture vector and find the texture with this ID
	{
		if (gameTextures[i].first == _name)//vector of a pair, first item being the ID
		{
			return gameTextures[i].second;//vector of a pair and the second item is the texture so return that
		}

	}
	//it exited the loop without returning a value
	std::cout << "Texture not found" << std::endl;

}

//uses sdl render copy and the texture's ID to extract the correct texture then draw it
void Graphics::Draw(textID _text, SDL_Rect * Crop, SDL_Rect * Place)
{//texture ID, croping rectangle, scaling and placing rectangle
	SDL_RenderCopy(Renderer, getTextureCalled(_text), Crop, Place);
}

//loops through the map and draws it
void Graphics::drawMap(Map _map)
{

	for (int r = 0; r < _map.viewR; r++)//loop through the view map (2D array of 11*11)
	{
		for (int c = 0; c < _map.viewC; c++)
		{
			tileRect.x = c * tileRect.w; //setting the x and Y positions of these rectangles depending on the 2D map's index
			tileRect.y = r * tileRect.h;
			if (_map.getViewTileAt(r, c).getType() == Wall)//if the tile in this index is of type wall
			{
				Draw(WallTexture, 0, &tileRect);//print the wall texture
			}
			else if (_map.getViewTileAt(r, c).getType() == PlayerSp)//if the tile in this index is of type player sprite
			{
				Draw(PlayerTexture, Frame, &tileRect);//print the player texture.. cropping the current animation frame			
			}
			else if (_map.getViewTileAt(r, c).getType() == ChestSp)//if the tile in this index is of type chest sprite
			{
				Draw(ChestTexture, 0, &tileRect);//print the chest texture
			}

		}
	}
	

	//code to print the entire map and not the view map (11*11 map that surrounds the player)..comment above loop out and uncomment below for debugging
	/*
	tileRect.w = (float)getWindowSize().X / (float)(_map.mapC);//used to print the entire map.. so smaller tiles.. for testing
    tileRect.h = ((float)(getWindowSize().Y) - (float)(200)) / (float)(_map.mapR);;

	for (int r = 0; r < _map.mapR; r++) //print the entire map.. for testing
	{
		for (int c = 0; c < _map.mapC; c++)
		{
			tileRect.x = c * tileRect.w; //setting the x and Y positions of these rectangles
			tileRect.y = r * tileRect.h;
			if (_map.getTileAt(r, c).getType() == Wall)
			{
				Draw(WallTexture, 0, &tileRect);//print the wall texture
			}
			else if (_map.getTileAt(r, c).getType() == PlayerSp)
			{
				Draw(PlayerTexture, Frame, &tileRect);//print the player texture.. cropping the current animation frame
			
			}
			else if (_map.getTileAt(r, c).getType() == ChestSp)
			{
				Draw(ChestTexture, 0, &tileRect);
			
			}
		}
	}
	*/
}

//draws the inventory menu and all the items and their level
void Graphics::drawInventory(Inventory *_inven)
{
	//print the inventory texture
	Draw(InventoryTexture, 0, &invenRect);

	//used to print out the item level
	std::string Level;
	SDL_Rect lvlRect{0, 0, 20, 40};

	//print inventory slots
	for (int i = 0; i < _inven->getInventorySize(); i++)//loop through inventory
	{
		itemType type = _inven->getItemAt(i)->getType();
		switch (type)//if the type of the item at this index is
		{

		case swordT:// a sword
			sTex.x = _inven->getSwordTextureAt(i).X;//extact the right sword texture, according to this sword's element
			sTex.y = _inven->getSwordTextureAt(i).Y;
			Draw(SwordTextures, &sTex, &_inven->getSlotPosAt(i));//draw the sword texture in its slot position
			Level = std::to_string(_inven->getItemAt(i)->getSword()->getLevel());//get the level of the sword
			break;

		case potionT://a potion
			Draw(PotionTexture, 0, &_inven->getSlotPosAt(i));//draw the potion texture in its slot position
			Level = std::to_string(_inven->getItemAt(i)->getPotion()->getLevel());// get the potion's level
			break;

		case emptyT://empty type
			break;//do nothing cuz life hurts
		}

		lvlRect.x = _inven->getSlotPosAt(i).x - _inven->getSlotWidth() * 0.35;
		lvlRect.y = _inven->getSlotPosAt(i).y - _inven->getSlotHeight() * 0.25;//placing the level rectangle at the edge of the slot


		Text::writeText(Level, Renderer, lvlRect);//print the level of the sword

	}
}

//draws the enemy texture during combat
void Graphics::drawEnemy(Elements _ele, bool *_itemSelectOn)
{
	if (!*_itemSelectOn)//if the inventory select menu isnt being drawn rn
	{
		Draw(CombatMenuTexture, 0, &invenRect);//draw combat menu
	}

	switch (_ele)//draw the enemy sprite depending on its element
	{
	case Fire:
		Draw(FireEnemyTexture, 0, &enemyRect);
		break;
	case Water:
		Draw(WaterEnemyTexture, 0, &enemyRect);
		break;
	case Earth:
		Draw(EarthEnemyTexture, 0, &enemyRect);
		break;
	}
}

//currently only draws the discard item textbox. Used for printing textboxes that show up above the inventory menu
void Graphics::drawTextBox(textID _text)
{//texture ID, croping rectangle, scaling and placing rectangle
	Draw(_text, 0, &textBox);
}

//according to the bar name/ID passed, it draws a status bar witht he suitable color.
void Graphics::drawBars(int _width, int _maxWidth, int _lvl, Bars _bar)
{
	SDL_Rect maxBar{ 0, 0,(getWindowSize().X), 10 };//used to print out the outer empty bars
	int temp = ((float)(_width) / (float)(_maxWidth) * (float)(getWindowSize().X));//e.g. player HP Bar: current HP/ max HP *windowSize.X
	SDL_Rect Bar{ 0, 0, temp, 10 };//used to print out the inner filled bars

	//used to print out the player or enemy level
	std::string Level;
	SDL_Rect lvlRect{ 0, 20, 15, 35 };

	switch (_bar)//what type of bar is being drawn?
	{
	case HPBar://print player HP Bar
		Bar.y = 0;//set bar y position
		maxBar.y = 0;
		SDL_SetRenderDrawColor(Renderer, 200, 0, 0, 255);//set render color to red
		SDL_RenderDrawRect(Renderer, &maxBar);//draw outer bar showing max value
		SDL_RenderDrawRect(Renderer, &Bar);
		SDL_RenderFillRect(Renderer, &Bar);//draw and fill inner bar shaowing current value
		Level = std::to_string(_lvl);//convert int to string
		Text::writeText(Level, Renderer, lvlRect);//draw level using the static Text draw function
		break;
	case ExpBar://print Player Exp Bar
		Bar.y = 10;//set bar y position
		maxBar.y = 10;
		SDL_SetRenderDrawColor(Renderer, 0, 150, 0, 255);//set render color to blue
		SDL_RenderDrawRect(Renderer, &maxBar);//draw outer bar showing max value
		SDL_RenderDrawRect(Renderer, &Bar);
		SDL_RenderFillRect(Renderer, &Bar);//draw and fill inner bar shaowing current value
		break;
	case EnemyHPBar://print Enemy HP bar
		Bar.y = invenRect.y - 10;//set bar y position
		maxBar.y = invenRect.y - 10;
		SDL_SetRenderDrawColor(Renderer, 150, 0, 150, 255);//set render color to purple
		SDL_RenderDrawRect(Renderer, &maxBar);//draw outer bar showing max value
		SDL_RenderDrawRect(Renderer, &Bar);
		SDL_RenderFillRect(Renderer, &Bar);//draw and fill inner bar shaowing current value
		Level = std::to_string(_lvl);//convert int to string
		lvlRect.y = Bar.y - lvlRect.h;//set level rect y position
		Text::writeText(Level, Renderer, lvlRect);//draw level using the static Text draw function
		break;
	}

}

//draws the menu screen. If Instructions on is true, draws the instructions screen instead.
void Graphics::drawMenu(bool _InstructionsOn)
{
	SDL_Rect menuRect{ 0 };//recatngle used to draw the menu screen texture
	menuRect.w = getWindowSize().X;//setting the width and height of it to the current window size
	menuRect.h = getWindowSize().Y;

	if (_InstructionsOn)//print instructions texture
	{
		Draw(InstructionsTexture, 0, &menuRect);
	}
	else//print menu texture
	{
		Draw(MainMenuTexture, 0, &menuRect);

	}

}

//calls render clear with the color black
void Graphics::Clear()
{
	SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
	SDL_RenderClear(Renderer);
}

//calls render present
void Graphics::Present()
{
	SDL_RenderPresent(Renderer);
}

//returns a vector(x, y) of the current width and height of the sdl window, using SDL get windowsize.
Vec2 Graphics::getWindowSize()
{
	Vec2 win;//vector of X and Y integers
	SDL_GetWindowSize(Window, &win.X, &win.Y);//update the vector
	return win;
}

//getter functions for rectangles used outside the class.
//rectangle used to crop the animation frames from the player sprite sheet
SDL_Rect* Graphics::getPlayerFrameRect()
{
	return Frame;
}

//used to get an individual sword from the texture
SDL_Rect Graphics::getSwordTextureRect()
{
	return sTex;
}

//rectangle used to print the inventory texture
SDL_Rect Graphics::getInventoryRect()
{
	return invenRect;
}

//used to output text boxes
SDL_Rect Graphics::getTextBoxRect()
{
	return textBox;
}





