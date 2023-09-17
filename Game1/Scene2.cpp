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
	
}

Scene2::~Scene2()
{

}

void Scene2::Init()
{
	player->Init(ground->Find("checkpoint1")->GetLocalPos());
}

void Scene2::Release()
{

	for (auto& it : GM->obstacleList)
	{
		it->Release();
	}
	ground->Release();
	
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
	
	

	grid->Update();
	ground->Update();
	for (auto& it : GM->obstacleList)
	{
		it->Update();
	}
	
	player->Update();
	temp->Update();
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
	
	
	for (auto& it : GM->obstacleList)
	{
		it->LateUpdate();
	}
	
	

}

void Scene2::Render()
{
	grid->Render();

	ground->Render();

	for (auto& it : GM->obstacleList)
	{
		it->Render();
	}

	player->Render();
	temp->Render();
	
}

void Scene2::PreRender()
{
}

void Scene2::ResizeScreen()
{
}
