#include "stdafx.h"
#include "Scene1.h"
#include "Player.h"
#include "Map.h"
#include "WallMap.h"


Scene1::Scene1()
{
    grid = Grid::Create();

    map = WallMap::Create();
    map->LoadFile("Maptest.xml");
    map->name = "Map";

}

Scene1::~Scene1()
{
}

void Scene1::Init()
{
    player->Init();
    //플레이어 위치잡는것 하나 추가하기
}

void Scene1::Release()
{
	
}

void Scene1::Update()
{
    ImGui::Begin("Hierarchy");
    grid->RenderHierarchy();
    //cam1->RenderHierarchy();
    map->RenderHierarchy();
    player->body->RenderHierarchy();

    ImGui::End();


   

    grid->Update();
    map->Update();
    player->Update();
}

void Scene1::LateUpdate()
{
    //Ground 충돌
    if (player->body->Intersect(map->Find("Ground0"))) player->isLand = true;
    else if (player->body->Intersect(map->Find("groundtest"))) player->isLand = true;
    else player->isLand = false;
}

void Scene1::Render()
{
    //Camera::main->Set();
    grid->Render();
    map->Render();
    player->Render();
}

void Scene1::PreRender()
{
}

void Scene1::ResizeScreen()
{
    Camera::main->viewport.x = 0.0f;
    Camera::main->viewport.y = 0.0f;
    Camera::main->viewport.width = App.GetWidth();
    Camera::main->viewport.height = App.GetHeight();
    Camera::main->width = App.GetWidth();
    Camera::main->height = App.GetHeight();
}
