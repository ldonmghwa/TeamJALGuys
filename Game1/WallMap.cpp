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
	delete[] pillarUnderSpeed;
	delete[] upDownBoardSpeed;
	delete[] leftRightBoardSpeed;
	delete[] glitingBoardActiveTime;
	delete[] backUpGlitingBoardActiveTime;
	delete[] isPillarUnderUp;
	delete[] isUpDownBoardUp;
	delete[] isLeftRightBoardGo;
}

void WallMap::Init()
{
	ground0 = this->root->Find("Ground0");
	ground1 = this->root->Find("Ground1");
	ground2 = this->root->Find("Ground2");
	ground3 = this->root->Find("Ground3");
	goal = this->root->Find("Goal");
}

void WallMap::Update()
{
	{
		for (int i = 0; i < pillarUnderList.size(); i++) {
			if (isPillarUnderUp[i]) {
				pillarUnderList[i]->MoveWorldPos(Vector3(0, 1, 0) * pillarUnderSpeed[i] * DELTA);
				if (pillarUnderList[i]->GetLocalPos().y > 9.0f) isPillarUnderUp[i] = false;
			}
			else {
				pillarUnderList[i]->MoveWorldPos(Vector3(0, -1, 0) * pillarUnderSpeed[i] * DELTA);
				if (pillarUnderList[i]->GetLocalPos().y < -7.0f) isPillarUnderUp[i] = true;
			}
		}
	}
	{
		for (int i = 0; i < upDownBoardList.size(); i++) {
			if (isUpDownBoardUp[i]) {
				upDownBoardList[i]->MoveWorldPos(Vector3(0, 1, 0) * upDownBoardSpeed[i] * DELTA);
				if (upDownBoardList[i]->GetLocalPos().y > 5.0f) isUpDownBoardUp[i] = false;
			}
			else {
				upDownBoardList[i]->MoveWorldPos(Vector3(0, -1, 0) * upDownBoardSpeed[i] * DELTA);
				if (upDownBoardList[i]->GetLocalPos().y < -5.0f) isUpDownBoardUp[i] = true;
			}
		}
		for (int i = 0; i < leftRightBoardList.size(); i++) {
			if (isLeftRightBoardGo[i]) {
				leftRightBoardList[i]->MoveWorldPos(Vector3(1, 0, 0) * leftRightBoardSpeed[i] * DELTA);
				if (leftRightBoardList[i]->GetLocalPos().x > 19.0f) isLeftRightBoardGo[i] = false;
			}
			else {
				leftRightBoardList[i]->MoveWorldPos(Vector3(-1, 0, 0) * leftRightBoardSpeed[i] * DELTA);
				if (leftRightBoardList[i]->GetLocalPos().x < -19.0f) isLeftRightBoardGo[i] = true;
			}
		}
	}
	{
		for (int i = 0; i < glitingBoardList.size(); i++) {
			glitingBoardActiveTime[i] -= DELTA;
			if (glitingBoardActiveTime[i] < 0) {
				glitingBoardList[i]->visible = not glitingBoardList[i]->visible;
				glitingBoardActiveTime[i] = backUpGlitingBoardActiveTime[i];
			}
		}
	}
	
	/*glitingBoardActiveTime -= DELTA;
	if (glitingBoardActiveTime < 0) {
		for (int i = 0; i < glitingBoardList.size(); i++) glitingBoardList[i]->visible = not glitingBoardList[i]->visible;
		glitingBoardActiveTime = backUpGlitingBoardActiveTime;
		isGlitingBoardChange = not isGlitingBoardChange;
	}*/

	Map::Update();
}

void WallMap::LoadFile(string _file)
{
	Map::LoadFile(_file);
	{
		int pillarUnderCount = 0;
		while (this->root->Find("Pillar1_under" + to_string(pillarUnderCount))) {
			pillarUnderList.push_back(this->root->Find("Pillar1_under" + to_string(pillarUnderCount)));
			pillarUnderCount++;
		}
		pillarUnderCount = 0;
		while (this->root->Find("Pillar2_under" + to_string(pillarUnderCount))) {
			pillarUnderList.push_back(this->root->Find("Pillar2_under" + to_string(pillarUnderCount)));
			pillarUnderCount++;
		}
		pillarUnderCount = 0;
		while (this->root->Find("Pillar3_under" + to_string(pillarUnderCount))) {
			pillarUnderList.push_back(this->root->Find("Pillar3_under" + to_string(pillarUnderCount)));
			pillarUnderCount++;
		}
		pillarUnderCount = 0;
		while (this->root->Find("Pillar4_under" + to_string(pillarUnderCount))) {
			pillarUnderList.push_back(this->root->Find("Pillar4_under" + to_string(pillarUnderCount)));
			pillarUnderCount++;
		}
		int pillarCount = 0;
		while (this->root->Find("Pillar1_" + to_string(pillarCount))) {
			pillarList.push_back(this->root->Find("Pillar1_" + to_string(pillarCount)));
			pillarCount++;
		}
		pillarCount = 0;
		while (this->root->Find("Pillar2_" + to_string(pillarCount))) {
			pillarList.push_back(this->root->Find("Pillar2_" + to_string(pillarCount)));
			pillarCount++;
		}
		pillarCount = 0;
		while (this->root->Find("Pillar3_" + to_string(pillarCount))) {
			pillarList.push_back(this->root->Find("Pillar3_" + to_string(pillarCount)));
			pillarCount++;
		}
		pillarCount = 0;
		while (this->root->Find("Pillar4_" + to_string(pillarCount))) {
			pillarList.push_back(this->root->Find("Pillar4_" + to_string(pillarCount)));
			pillarCount++;
		}
	}
	{
		int boardCount = 0;
		while (this->root->Find("GlitingBoard_" + to_string(boardCount))) {
			glitingBoardList.push_back(this->root->Find("GlitingBoard_" + to_string(boardCount)));
			if (boardCount < 5) {
				glitingBoardList1.push_back(this->root->Find("GlitingBoard_" + to_string(boardCount)));
				this->root->Find("GlitingBoard_" + to_string(boardCount))->visible = false;
			}
			else if (boardCount < 10) {
				glitingBoardList2.push_back(this->root->Find("GlitingBoard_" + to_string(boardCount)));
				this->root->Find("GlitingBoard_" + to_string(boardCount))->visible = true;
			}
			else if (boardCount < 15) {
				glitingBoardList1.push_back(this->root->Find("GlitingBoard_" + to_string(boardCount)));
				this->root->Find("GlitingBoard_" + to_string(boardCount))->visible = false;
			}
			else if (boardCount < 20) {
				glitingBoardList2.push_back(this->root->Find("GlitingBoard_" + to_string(boardCount)));
				this->root->Find("GlitingBoard_" + to_string(boardCount))->visible = true;
			}
			else if (boardCount < 25) {
				glitingBoardList1.push_back(this->root->Find("GlitingBoard_" + to_string(boardCount)));
				this->root->Find("GlitingBoard_" + to_string(boardCount))->visible = false;
			}
			else if (boardCount < 30) {
				glitingBoardList2.push_back(this->root->Find("GlitingBoard_" + to_string(boardCount)));
				this->root->Find("GlitingBoard_" + to_string(boardCount))->visible = true;
			}
			boardCount++;
		}
	}
	{
		int upDownBoardCount = 0;
		while (this->root->Find("UpDownBoard_" + to_string(upDownBoardCount))) {
			upDownBoardList.push_back(this->root->Find("UpDownBoard_" + to_string(upDownBoardCount)));
			upDownBoardCount++;
		}
		int leftRightBoardCount = 0;
		while (this->root->Find("LeftRightBoard_" + to_string(leftRightBoardCount))) {
			leftRightBoardList.push_back(this->root->Find("LeftRightBoard_" + to_string(leftRightBoardCount)));
			leftRightBoardCount++;
		}
	}
	{
		pillarUnderSpeed = new float[pillarUnderList.size()];
		upDownBoardSpeed = new float[upDownBoardList.size()];
		leftRightBoardSpeed = new float[leftRightBoardList.size()];
		glitingBoardActiveTime = new float[glitingBoardList.size()];
		backUpGlitingBoardActiveTime = new float[glitingBoardList.size()];
		isPillarUnderUp = new bool[pillarUnderList.size()];
		isUpDownBoardUp = new bool[upDownBoardList.size()];
		isLeftRightBoardGo = new bool[leftRightBoardList.size()];
		landingYPos = glitingBoardList.back()->scale.y;
		playerScaleY = player->body->scale.y * 2.0f;
	}
	{
		for (int i = 0; i < pillarUnderList.size(); i++) {
			pillarUnderSpeed[i] = RANDOM->Float(10, 30);
			isPillarUnderUp[i] = false;
		}
		for (int i = 0; i < upDownBoardList.size(); i++) {
			upDownBoardSpeed[i] = RANDOM->Float(20, 30);
			isUpDownBoardUp[i] = RANDOM->Int(0, 1);
		}
		for (int i = 0; i < leftRightBoardList.size(); i++) {
			leftRightBoardSpeed[i] = RANDOM->Float(50, 60);
			isLeftRightBoardGo[i] = RANDOM->Int(0, 1);
		}
		for (int i = 0; i < glitingBoardList.size(); i++) {
			glitingBoardActiveTime[i] = RANDOM->Float(2.0f, 6.5f);
			//glitingBoardActiveTime[i] = 100.0f;
			backUpGlitingBoardActiveTime[i] = glitingBoardActiveTime[i];
		}
	}
}

void WallMap::LateUpdate()
{
	ImGui::Text("pl pos: %f, %f, %f", player->body->GetWorldPos().x, player->body->GetWorldPos().y, player->body->GetWorldPos().z);
	if (player->body->Intersect(ground0)) player->isLand = true;
	else if (player->body->Intersect(ground1)) player->isLand = true;
	else if (player->body->Intersect(ground2)) player->isLand = true;
	else if (player->body->Intersect(ground3)) player->isLand = true;
	else if (player->body->Intersect(goal)) player->isLand = true;
	else player->isLand = false;

	for (int i = 0; i < pillarUnderList.size(); i++) {
		if (pillarUnderList[i]->Intersect(player->body)) {
			player->body->MoveWorldPos(Vector3(0.0f, 0.0f, -1.0f) * 0.1f);
		}
	}
	for (int i = 0; i < pillarList.size(); i++) {
		if (pillarList[i]->Intersect(player->body)) {
			player->body->MoveWorldPos(Vector3(0.0f, 0.0f, -1.0f) * 0.1f);
		}
	}
	for (int i = 0; i < glitingBoardList.size(); i++) {
		if (glitingBoardList[i]->Intersect(player->body)) {
			if (glitingBoardList[i]->visible) player->isLand = true;
			else player->isLand = false;
		}
	}

}

