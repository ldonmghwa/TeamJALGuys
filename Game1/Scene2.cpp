#include "stdafx.h"
#include "Obstacle.h"
#include "Obstacle1.h"
#include "Obstacle2.h"
#include "Scene2.h"


Scene2::Scene2()
{
	grid = Grid::Create();
	GM->obstacleList.push_back(new Obstacle1());
	GM->obstacleList.push_back(new Obstacle2());
}

Scene2::~Scene2()
{

}

void Scene2::Init()
{
	player->Init(Vector3(0,8,100));

	player->body->SetWorldPosY(0);
}

void Scene2::Release()
{

	for (auto& it : GM->obstacleList)
	{
		it->Release();
	}
}

void Scene2::Update()
{
	
	ImGui::Begin("Hierarchy");

	player->body->RenderHierarchy();
	for (auto& it : GM->obstacleList)
	{
		it->root->RenderHierarchy();
	}
	ImGui::End();

	grid->Update();
	for (auto& it : GM->obstacleList)
	{
		it->Update();
	}
	player->Update();
}

void Scene2::LateUpdate()
{
	for (auto& it : GM->obstacleList)
	{
		it->LateUpdate();
	}


}

void Scene2::Render()
{
	grid->Render();

	for (auto& it : GM->obstacleList)
	{
		it->Render();
	}
	player->Render();
}

void Scene2::PreRender()
{
}

void Scene2::ResizeScreen()
{
}
