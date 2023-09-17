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
}

void Main::Update()
{
    if (INPUT->KeyDown(VK_F1))
    {
        SCENE->ChangeScene("SC1");
    }
    if (INPUT->KeyDown(VK_F2))
    {
        SCENE->ChangeScene("SC2");
    }

    SCENE->Update();
}

void Main::LateUpdate()
{
   SCENE->LateUpdate();
}
void Main::PreRender()
{
}

void Main::Render()
{
    Camera::main->Set();
    SCENE->Render();
}

void Main::ResizeScreen()
{
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