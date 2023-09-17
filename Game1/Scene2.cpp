#include "stdafx.h"
#include "Obstacle.h"
#include "Obstacle1.h"
#include "Obstacle2.h"
#include "Obstacle3.h"
#include "Scene2.h"


Scene2::Scene2()
{
	
	isCheck1 = true;
	isCheck2 = false;
	grid = Grid::Create();
	

	ground = Actor::Create();
	ground->name = "ground";
	ground->LoadFile("wall.xml");
	
	temp = Actor::Create();
	temp->name="temp";
    GM->obstacleList.push_back(new Obstacle1());
	GM->obstacleList.push_back(new Obstacle2());
	GM->obstacleList.push_back(new Obstacle2(Vector3(0,0,350)));
	GM->obstacleList.push_back(new Obstacle3());
	GM->obstacleList.push_back(new Obstacle3(Vector3(-15,7,490)));
	GM->obstacleList.push_back(new Obstacle3(Vector3(15, 7, 580)));
	
	wall = Actor::Create();
	wall->LoadFile("Sc2Room.xml");
	wall->name = "SC2Room";

	ending = UI::Create();
	ending->LoadFile("EndingUI.xml");
	ending->visible = false;
	ending->name = "ending";
	gameEndTime = 2.0f;
	SOUND->AddSound("Sc2.mp3", "Sc2",true);
}

Scene2::~Scene2()
{

}

void Scene2::Init()
{
	player->Init(ground->Find("checkpoint1")->GetLocalPos());
	player->body->rotation.y = 2.5f;
	SOUND->SetVolume("Sc2", 0.4f);
	SOUND->Play("Sc2");
}

void Scene2::Release()
{

	for (auto& it : GM->obstacleList)
	{
		it->Release();
	}
	ground->Release();
	ending->Release();
}

void Scene2::Update()
{
	
	ImGui::Begin("Hierarchy");
	
	player->body->RenderHierarchy();
	
	for (auto& it : GM->obstacleList)
	{
		it->root->RenderHierarchy();
	}
	ground->RenderHierarchy();
	wall->RenderHierarchy();
	ending->RenderHierarchy();
	temp->RenderHierarchy();
	ImGui::End();

	if (isCheck1)
	{
		if (player->body->GetWorldPos().y < -30)//¶³¾îÁö´Â ÁÂÇ¥´Â y¸¸ -30
		{
			player->body->SetWorldPos(ground->Find("checkpoint1")->GetLocalPos());//Ã¼Å©Æ÷ÀÎÆ® 1 ÁÂÇ¥(0,5,-55)
		}
	}

	if (isCheck2)
	{
		if (player->body->GetWorldPos().y < -30)//¶³¾îÁö´Â ÁÂÇ¥´Â y¸¸ -30
		{
			player->body->SetWorldPos(ground->Find("checkpoint2")->GetLocalPos());//Ã¼Å©Æ÷ÀÎÆ®2 ÁÂÇ¥(0,5,245) getlocal·Î
		}

	}

	if (player->body->GetWorldPos().z > 590)
	{
		SCENE->ChangeScene("SC3", 1.5f);
	}

	if (wall->Find("Back")->GetWorldPos().z <= 620.0f) {
		wall->Find("Back")->SetWorldPosZ(player->body->GetWorldPos().z + 400.0f);
	}
	
	if (!isGameEnd) {
		grid->Update();
		ground->Update();
		for (auto& it : GM->obstacleList)
		{
			it->Update();
		}
		player->Update();
		temp->Update();
		wall->Update();
		ending->Update();
	}
}

void Scene2::LateUpdate()
{
	if (player->body->GetWorldPos().z > 240)
	{
		isCheck1 = false;
		isCheck2 = true;	
		GM->isActive = true;
	}


	if (ground->Find("ground")->Intersect(player->body) || ground->Find("ground2")->Intersect(player->body))
	{
		player->isLand = true;
	}
	else player->isLand = false;

	if (ground->Find("wall1")->Intersect(player->body))
	{
		player->body->MoveWorldPos(Vector3(1, 0, 0) * 0.1);
	}
	if (ground->Find("wall2")->Intersect(player->body))
	{
		player->body->MoveWorldPos(Vector3(-1, 0, 0) * 0.1);
	}
	
	for (auto& it : GM->obstacleList)
	{
		it->LateUpdate();
	}
	
	if (player->body->GetWorldPos().z > 550.0f) {
		isGameEnd = true;
		gameEndTime -= DELTA;
		if (gameEndTime < 0) {
			gameEndTime = 2.0f;
			ending->visible = true;
		}
	}
}

void Scene2::Render()
{
	wall->Render();

	ground->Render();

	for (auto& it : GM->obstacleList)
	{
		it->Render();
	}

	player->Render();
	temp->Render();
	ending->Render();
}

void Scene2::PreRender()
{
}

void Scene2::ResizeScreen()
{
}
