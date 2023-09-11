#include "stdafx.h"
#include "Map.h"

Map* Map::Create(string name)
{
	Map* temp = new Map();
	temp->type = ObType::Actor;
	return temp;
}

Map::Map()
{
}

Map::~Map()
{
}

void Map::Update()
{
	Actor::Update();
}
