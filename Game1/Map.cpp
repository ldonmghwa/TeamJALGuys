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
	obstacleNum = 0;
}

Map::~Map()
{
}

void Map::LoadFile(string _file)
{
	this->root->LoadFile(_file);
	while (this->root->Find("ObstacleRoot" + to_string(obstacleNum))) {
		obstacleList.push_back(this->root->Find("ObstacleRoot" + to_string(obstacleNum)));
		obstacleNum++;
	}

}

void Map::Update()
{
	Actor::Update();
}

void Map::AddObstacle(string _file)
{
	Actor* temp = Actor::Create();
	temp->LoadFile(_file);
	temp->name = "ObstacleRoot" + to_string(obstacleNum);
	obstacleNum++;
	this->AddChild(temp);
	obstacleList.push_back(temp);
}
