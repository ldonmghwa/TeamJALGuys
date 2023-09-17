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

    dron = Actor::Create();
    dron->LoadFile("dronCam.xml");
    dron->name = "dron";
    Camera::main = static_cast<Camera*>(dron->Find("dronCam"));
   // Camera::main = static_cast<Camera*>(player->body->Find("PCam"));

    SOUND->AddSound("Sc1.mp3", "Sc1",true);
}

Scene1::~Scene1()
{
}

void Scene1::Init()
{
    player->Init(Vector3(0, 25, -50));
    player->body->rotation.y = -361.0f * ToRadian;
    map->Init();
    SOUND->SetVolume("Sc1", 0.6f);
    SOUND->Play("Sc1");
    mapEndingTime = 3.0f;
    dron->SetWorldPos(Vector3(0, 100, -40));
  
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
    dron->RenderHierarchy();
   
    ImGui::End();

    if (dron->GetWorldPos().y >= 30) {
        Camera::main = static_cast<Camera*>(dron->Find("dronCam"));
        dron->rotation.x = 25.0f*ToRadian;
        dron->MoveWorldPos(Vector3(0, -1, 0) * 10.0f * DELTA);
    }
    else {
        Camera::main = static_cast<Camera*>(player->body->Find("PCam"));
        
    }
       


    if (!isTimeStop) {
        wallskin->Update();
        wall->Update();

        map->Update();
        dron->Update();
        player->Update();
    }
}

void Scene1::LateUpdate()
{
    //Ground Ãæµ¹
    map->LateUpdate();
    if (player->body->Intersect(map->goal) or player->body->GetWorldPos().z > 243.0f) {
        isTimeStop = true;
        mapEndingTime -= DELTA;
        if (mapEndingTime < 0)
        {
            mapEndingTime = 3.0f;
            SOUND->Stop("Sc1");
            SCENE->ChangeScene("SC2");
        }
    }
}

void Scene1::Render()
{
    //Camera::main->Set();
    map->Render();
    wallskin->Render();
    wall->Render();
    player->Render();
    dron->Render();
    
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
