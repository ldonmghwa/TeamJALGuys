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

}

Scene1::~Scene1()
{
}

void Scene1::Init()
{
    player->Init(Vector3(0, 25, -50));
    map->Init();
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
    ImGui::End();
    if (!isTimeStop) {
        grid->Update();
        map->Update();
        player->Update();
    }
}

void Scene1::LateUpdate()
{
    map->LateUpdate();
    if (player->body->Intersect(map->goal) or player->body->GetWorldPos().z > 243.0f) {
        isTimeStop = true;
        mapEndingTime -= DELTA; 
        if(mapEndingTime<0)
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
