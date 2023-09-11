#include "stdafx.h"
#include "Map.h"
#include "WallMap.h"

WallMap* WallMap::Create(string name)
{
	WallMap* temp = new WallMap();
	temp->type = ObType::Actor;
	return temp;
}

WallMap::WallMap() : Map()
{
}

WallMap::~WallMap()
{
	delete[] wallSpeed;
	delete[] isUp;
}

void WallMap::Update()
{
	for (auto it = movePillarList.begin(); it != movePillarList.end(); it++) {
		//float ranNum = RANDOM->Float(1.0f, 10.0f);
		if (isUp[count]) {
			(*it)->MoveWorldPos(Vector3(0, 1, 0) * wallSpeed[count] * DELTA);
			if ((*it)->GetLocalPos().y > 3.0f) {
				isUp[count] = false;
			}
		}
		else  {
			(*it)->MoveWorldPos(Vector3(0, -1, 0) * wallSpeed[count] * DELTA);
			if ((*it)->GetLocalPos().y < -3.0f) {
				isUp[count] = true;
			}
		}
		count++;
		if (count == movePillarList.size()) count = 0;
	}
	Map::Update();
}

void WallMap::LoadFile(string _file)
{
	Map::LoadFile(_file);
	int pillarCount = 0;
	while (this->root->Find("Pillar1_under" + to_string(pillarCount))) {
		movePillarList.push_back(this->root->Find("Pillar1_under" + to_string(pillarCount)));
		//movePillarList.front()->collider->scale = movePillarList.front()->scale;
		//movePillarList.front()->collider->visible = true;
		pillarCount++;
	}
	wallSpeed = new float[pillarCount]; 
	isUp = new bool[pillarCount];
	for (int i = 0; i < pillarCount; i++) {
		wallSpeed[i] = RANDOM->Float(3, 10);
		isUp[i] = false;
	}
}

