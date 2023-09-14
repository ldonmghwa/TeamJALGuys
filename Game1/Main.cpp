#include "stdafx.h"
#include "SceneIntro.h"
#include "Scene1.h"
#include "Scene2.h"
#include "Obstacle.h"
#include "Obstacle1.h"
#include "Obstacle2.h"
#include "Map.h"
#include "WallMap.h"
#include "Player.h"
#include "Main.h"

Main::Main()
{
    SCIntro = new SceneIntro();
    SC1 = new Scene1();
    SC2 = new Scene2();
   /* grid = Grid::Create();*/

    Camera::main = static_cast<Camera*>(player->body->Find("PCam"));
  
   /* cam1 = Camera::Create();
    cam1->LoadFile("Cam.xml");*/
   /* cam1->viewport.x = 0.0f;
    cam1->viewport.y = 0.0f;
    cam1->viewport.width = App.GetWidth();
    cam1->viewport.height = App.GetHeight();
    cam1->width = App.GetWidth();
    cam1->height = App.GetHeight();*/

    map = WallMap::Create();
    map->LoadFile("Map1.xml");
    map->name = "Map";*/
    
    
}

Main::~Main()
{

}

void Main::Init()
{
    
    SCENE->AddScene("SCIntro", SCIntro);
    SCENE->AddScene("SC1", SC1);
    SCENE->AddScene("SC2", SC2);

    
    SCENE->ChangeScene("SC1");
    
}

void Main::Release()
{
    /*for (auto& it : GM->obstacleList)
    {
        it->Release();
    }*/
}

void Main::Update()
{
    //Camera::main->ControlMainCam();
    ImGui::Begin("Hierarchy");
    grid->RenderHierarchy();
    //cam1->RenderHierarchy();
    map->RenderHierarchy();
    player->body->RenderHierarchy();
    ImGui::End();

    

    if (player->PCamActive) {
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
    }

    grid->Update();
    map->Update();
    Camera::main->Update();
    player->Update();
}

void Main::LateUpdate()
{
    //Ground Ãæµ¹
    if (player->body->Intersect(map->Find("Ground"))) player->isLand = true;
    else player->isLand = false;
}
void Main::PreRender()
{
}

void Main::Render()
{/*
    Camera::main->Set();
    grid->Render();
    map->Render();
    player->Render();
}

void Main::ResizeScreen()
{
   /* Camera::main->viewport.x = 0.0f;
    Camera::main->viewport.y = 0.0f;
    Camera::main->viewport.width = App.GetWidth();
    Camera::main->viewport.height = App.GetHeight();
    Camera::main->width = App.GetWidth();
    Camera::main->height = App.GetHeight();*/
    SCENE->ResizeScreen();
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
    App.SetAppName(L"Game1");
    App.SetInstance(instance);
    WIN->Create();
    D3D->Create();
    Main* main = new Main();
    main->Init();

    int wParam = (int)WIN->Run(main);


    main->Release();
    SafeDelete(main);
    D3D->DeleteSingleton();
    WIN->DeleteSingleton();

    return wParam;
}