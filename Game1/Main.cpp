#include "stdafx.h"
#include "Map.h"
#include "Main.h"
#include "Player.h"

Main::Main()
{
    grid = Grid::Create();

    cam1 = Camera::Create();
    cam1->LoadFile("Cam.xml");
    Camera::main = cam1;

    cam1->viewport.x = 0.0f;
    cam1->viewport.y = 0.0f;
    cam1->viewport.width = App.GetWidth();
    cam1->viewport.height = App.GetHeight();
    cam1->width = App.GetWidth();
    cam1->height = App.GetHeight();

    map = Map::Create();
    map->LoadFile("Map1.xml");
    map->name = "Map";

    temp = Actor::Create();
    
    
}

Main::~Main()
{

}

void Main::Init()
{
    player->Init();
}

void Main::Release()
{

}

void Main::Update()
{
    Camera::main->ControlMainCam();
    ImGui::Begin("Hierarchy");
    grid->RenderHierarchy();
    cam1->RenderHierarchy();
    map->RenderHierarchy();
    temp->RenderHierarchy();
    player->body->RenderHierarchy();
    ImGui::End();

    grid->Update();
    map->Update();
    temp->Update();
    Camera::main->Update();
    player->Update();
}

void Main::LateUpdate()
{
    if (player->GetWorldPos().y<=6.0f)
    {
        player->isLand = true;
    }
}
void Main::PreRender()
{
}

void Main::Render()
{
    Camera::main->Set();
    grid->Render();
    map->Render();
    temp->Render();
    player->Render();
}

void Main::ResizeScreen()
{
    cam1->viewport.x = 0.0f;
    cam1->viewport.y = 0.0f;
    cam1->viewport.width = App.GetWidth();
    cam1->viewport.height = App.GetHeight();

    cam1->width = App.GetWidth();
    cam1->height = App.GetHeight();
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