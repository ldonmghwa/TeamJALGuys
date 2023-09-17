#include "stdafx.h"
#include "Scene1.h"
#include "Player.h"
#include "Map.h"
#include "WallMap.h"


Scene1::Scene1()
{
    grid = Grid::Create();

    map = WallMap::Create();
    map->LoadFile("Map1.xml");
    map->name = "Map";

    wallskin = Actor::Create();
    wallskin->LoadFile("Sc1Land.xml");
    wallskin->name = "SC1Land";
    wall = Actor::Create();
    wall->LoadFile("Sc1Room.xml");
    wall->name = "SC1Room";
}

Scene1::~Scene1()
{
}

void Scene1::Init()
{
    player->Init(Vector3(0, 25, 68));
    map->Init();
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
    wallskin->RenderHierarchy();
    wall->RenderHierarchy();
    player->Time->RenderHierarchy();
    ImGui::End();


   
    wallskin->Update();
    wall->Update();
    grid->Update();
    map->Update();
    player->Update();
}

void Scene1::LateUpdate()
{
    //Ground Ãæµ¹
    map->LateUpdate();
    /*if (player->body->Intersect(map->Find("Ground0"))) player->isLand = true;
    else if (player->body->Intersect(map->Find("groundtest"))) player->isLand = true;
    else player->isLand = false;*/
}

void Scene1::Render()
{
    //Camera::main->Set();
    grid->Render();
    map->Render();
    wallskin->Render();
    wall->Render();
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
