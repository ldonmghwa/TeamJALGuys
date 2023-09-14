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
	for (auto it = pillarUnderList.begin(); it != pillarUnderList.end(); it++) {
		//float ranNum = RANDOM->Float(1.0f, 10.0f);
		if (isUp[count]) {
			(*it)->MoveWorldPos(Vector3(0, 1, 0) * wallSpeed[count] * DELTA);
			if ((*it)->GetLocalPos().y > 3.0f) {
				isUp[count] = false;
			}
		}
		else {
			(*it)->MoveWorldPos(Vector3(0, -1, 0) * wallSpeed[count] * DELTA);
			if ((*it)->GetLocalPos().y < -3.0f) {
				isUp[count] = true;
			}
		}
		count++;
		if (count == pillarUnderList.size()) count = 0;
	}

	boardActiveTime -= DELTA;

	if (isBoardChange) {
		for (int i = 0; i < glitingBoardList.size(); i++) {
			if (i < 4) glitingBoardList[i]->visible = true;
			else glitingBoardList[i]->visible = false;
		}
	}
	else {
		for (int i = 0; i < glitingBoardList.size(); i++) {
			if (i < 4) glitingBoardList[i]->visible = false;
			else glitingBoardList[i]->visible = true;
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
		pillarUnderList.push_back(this->root->Find("Pillar1_under" + to_string(pillarUnderCount)));
		pillarUnderCount++;
	}
	int pillarCount = 0;
	while (this->root->Find("Pillar1_" + to_string(pillarCount))) {
		pillarList.push_back(this->root->Find("Pillar1_" + to_string(pillarCount)));
		pillarCount++;
	}
	int boardCount = 0;
	while (this->root->Find("Board_" + to_string(boardCount))) {
		glitingBoardList.push_back(this->root->Find("Board_" + to_string(boardCount)));
		if (boardCount < 4) glitingBoardList1.push_back(this->root->Find("Board_" + to_string(boardCount)));
		else glitingBoardList2.push_back(this->root->Find("Board_" + to_string(boardCount)));
		boardCount++;
	}
	int upDownBoardCount = 0;
	/*while (this->root->Find("UpDownBoard_" + to_string(upDownBoardCount))){
		upDownBoardList.push_back(this->root->Find("UpDownBoard_" + to_string(upDownBoardCount)));
		if (upDownBoardCount % 2 == 0) {

		}

	}*/
	wallSpeed = new float[pillarCount]; 
	isUp = new bool[pillarCount];
	for (int i = 0; i < pillarCount; i++) {
		wallSpeed[i] = RANDOM->Float(3, 10);
		isUp[i] = false;
	}
}

