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



}

void Scene2::Release()
{
	grid->Update();

	for (auto& it : GM->obstacleList)
	{
		it->Release();
	}
}

void Scene2::Update()
{
	ImGui::Begin("Hierarchy");

	for (auto& it : GM->obstacleList)
	{
	    it->root->RenderHierarchy();
	}
	ImGui::End();

	for (auto& it : GM->obstacleList)
	{
		it->Update();
	}
}

void Scene2::LateUpdate()
{



}

void Scene2::Render()
{
	grid->Render();
	
	for (auto& it : GM->obstacleList)
	{
		it->Render();
	}
}

void Scene2::PreRender()
{
}

void Scene2::ResizeScreen()
{
}
