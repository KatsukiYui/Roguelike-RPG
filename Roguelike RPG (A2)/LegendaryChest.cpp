#include "LegendaryChest.h"


//changed the end bool to true whent he chest is opened. This exists the gameloop.
void LegendaryChest::openChest(bool *_end, Inventory *_I)
{
	if (Opened == false)//if the chest hasnt been opened
	{
		*_end = true;//set end to true, which ends the game loop
		Opened = true;
	}
}
