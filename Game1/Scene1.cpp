#include "stdafx.h"
#include "Scene1.h"
#include "Map.h"
#include "WallMap.h"
#include "Player.h"

Scene1::Scene1()
{
    
	Camera::main = static_cast<Camera*>(player->body->Find("PCam"));
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
    player->Init();
    
    //플레이어 위치잡는것 하나 추가하기
}

void Scene1::Release()
{
	
}

void Scene1::Update()
{
    //Camera::main->ControlMainCam();

    ImGui::Begin("Hierarchy");
    grid->RenderHierarchy();
    //cam1->RenderHierarchy();
    map->RenderHierarchy();
    player->body->RenderHierarchy();

    ImGui::End();

    cout << player->isLand;
    /*if (player->PCamActive) {
        POINT ptMouse;
        ptMouse.x = App.GetHalfWidth();
        ptMouse.y = App.GetHalfHeight();
        Vector3 Rot;
        Rot.x = (INPUT->position.y - ptMouse.y) * 0.001f;
        Rot.y = (INPUT->position.x - ptMouse.x) * 0.001f;
        player->body->rotation.y += Rot.y;
        Camera::main->rotation.x += Rot.x;
        ClientToScreen(App.GetHandle(), &ptMouse);
        SetCursorPos(ptMouse.x, ptMouse.y);
    }*/

  

    grid->Update();
    map->Update();
    Camera::main->Update();
    player->Update();
  
}

void Scene1::LateUpdate()
{
    //Ground 충돌
    if (player->body->Intersect(map->Find("Ground0"))) player->isLand = true;
    else player->isLand = false;
}

void Scene1::Render()
{
    Camera::main->Set();
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
