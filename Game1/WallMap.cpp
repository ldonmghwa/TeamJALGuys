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
	boardActiveTime = 1.5f;
}

WallMap::~WallMap()
{
	delete[] wallSpeed;
	delete[] isUp;
}

void WallMap::Update()
{
	for (auto it = pillarUnderColliderList.begin(); it != pillarUnderColliderList.end(); it++) {
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
		if (count == pillarUnderColliderList.size()) count = 0;
	}

	boardActiveTime -= DELTA;
	if (isBoardChange) {
		for (auto it = boardList1.begin(); it != boardList1.end(); it++) {
			(*it)->visible = false;
		}
		for (auto it = boardList2.begin(); it != boardList2.end(); it++) {
			(*it)->visible = true;
		}
	}
	else {
		for (auto it = boardList1.begin(); it != boardList1.end(); it++) {
			(*it)->visible = true;
		}
		for (auto it = boardList2.begin(); it != boardList2.end(); it++) {
			(*it)->visible = false;
		}
	}
	if (boardActiveTime < 0) {
		boardActiveTime = 1.5f;
		isBoardChange = not isBoardChange;
	}
	
	Map::Update();
}

void WallMap::LoadFile(string _file)
{
	Map::LoadFile(_file);
	int pillarUnderCount = 0;
	while (this->root->Find("Pillar1_under" + to_string(pillarUnderCount))) {
		pillarUnderColliderList.push_back(this->root->Find("Pillar1_under" + to_string(pillarUnderCount)));
		pillarUnderCount++;
	}
	int pillarCount = 0;
	while (this->root->Find("Pillar1_" + to_string(pillarCount))) {
		pillarColliderList.push_back(this->root->Find("Pillar1_" + to_string(pillarCount)));
		pillarCount++;
	}
	int boardCount = 0;
	while (this->root->Find("Board_"+to_string(boardCount))){

		boardColliderList.push_back(this->root->Find("Board_" + to_string(boardCount)));
		if (boardCount < 4) boardList1.push_back(this->root->Find("Board_" + to_string(boardCount)));
		else boardList2.push_back(this->root->Find("Board_" + to_string(boardCount)));
		boardCount++;
	}
	wallSpeed = new float[pillarCount]; 
	isUp = new bool[pillarCount];
	for (int i = 0; i < pillarCount; i++) {
		wallSpeed[i] = RANDOM->Float(3, 10);
		isUp[i] = false;
	}
}

