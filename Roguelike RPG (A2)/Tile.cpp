#include "Tile.h"

Tile::Tile() {}; 

Tile::Tile(tileType _type)
{
	Type = _type;
};

Tile::~Tile() {};

void Tile::setType(tileType _type) { Type = _type; };

tileType Tile::getType() { return Type; };