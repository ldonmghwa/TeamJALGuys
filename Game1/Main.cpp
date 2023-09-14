#include "stdafx.h"
#include "Map.h"
#include "WallMap.h"
#include "Player.h"
#include "Main.h"

Main::Main()
{
    grid = Grid::Create();

    Camera::main = static_cast<Camera*>(player->body->Find("PCam"));

    map = WallMap::Create();
    map->LoadFile("Map1.xml");
    map->name = "Map";
    
    ui = UI::Create();
    
    mouse = UI::Create();

    cursor = UI::Create();
    cursor->name = "cursor";
    cursor->LoadFile("Cursor.xml");
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
    ImGui::Begin("Hierarchy");

    grid->RenderHierarchy();
    map->RenderHierarchy();
    player->body->RenderHierarchy();
    ui->RenderHierarchy();
    cursor->RenderHierarchy();

    ImGui::End();
    
   


    grid->Update();
    map->Update();
    Camera::main->Update();
    player->Update();
    ui->Update();
    cursor->Update();
}

void Main::LateUpdate()
{
    //Ground Ãæµ¹
    if (player->PCamActive) {
        if (player->body->Intersect(map->Find("Ground"))) player->isLand = true;
        else player->isLand = false;
    }

   //Cursor
    Vector3 ndcMouse = Utility::MouseToNDC();
    cursor->SetWorldPos(ndcMouse);
}
void Main::PreRender()
{
}

void Main::Render()
{
    Camera::main->Set();
    grid->Render();
    map->Render();
    player->Render();
    cursor->Render();
}

void Main::ResizeScreen()
{
    Camera::main->viewport.x = 0.0f;
    Camera::main->viewport.y = 0.0f;
    Camera::main->viewport.width = App.GetWidth();
    Camera::main->viewport.height = App.GetHeight();
    Camera::main->width = App.GetWidth();
    Camera::main->height = App.GetHeight();
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