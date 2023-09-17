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
    map->name = "Map1";

    wallskin = Actor::Create();
    wallskin->LoadFile("Sc1Land.xml");
    wallskin->name = "SC1Land";
    wall = Actor::Create();
    wall->LoadFile("Sc1Room.xml");
    wall->name = "SC1Room";
   
    SOUND->AddSound("Sc1.mp3", "Sc1");
}

Scene1::~Scene1()
{
}

void Scene1::Init()
{
    player->Init(Vector3(0, 25, -50));
    map->Init();
    SOUND->Play("Sc1");
    SOUND->SetVolume("Sc1", 0.1f);
    mapEndingTime = 3.0f;
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
    player->Second1->RenderHierarchy();
    player->Second10->RenderHierarchy();
    ImGui::End();

    if (!isTimeStop) {
        wallskin->Update();
        wall->Update();
        grid->Update();
        map->Update();
        player->Update();
    }
}

void Scene1::LateUpdate()
{
    //Ground �浹
    map->LateUpdate();
    if (player->body->Intersect(map->goal) or player->body->GetWorldPos().z > 243.0f) {
        isTimeStop = true;
        mapEndingTime -= DELTA;
        if (mapEndingTime < 0)
        {
            mapEndingTime = 3.0f;
            SCENE->ChangeScene("SC2");
        }
    }
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
