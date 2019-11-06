#ifndef _LCHEST_
#define _LCHEST_



#include "Chest.h"

class LegendaryChest: public Chest// end game chest. The open sword function will end the game
{

protected:

public:

	//changed the end bool to true whent he chest is opened. This exists the gameloop.
	void openChest(bool *_end, Inventory *_I);
};

#endif // !_LCHEST_

