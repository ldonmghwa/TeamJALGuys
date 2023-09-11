#include "stdafx.h"
#include "Map.h"
#include "WallMap.h"
#include "Main.h"

#define PillarMax 11

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

    map = WallMap::Create();
    map->LoadFile("Map1.xml");
    map->name = "Map";
    
    //pillar1Ob = Actor::Create();
    //pillar1Ob->LoadFile("Pillar1.xml");
    //pillar1Ob->name = "temp";
    //pillar1Root = Actor::Create();
    ////pillar1Root->LoadFile("Pillar1Root.xml");
    //pillar1Root->name = "Pillar1Root";
    //map->AddObstacle("Pillar1Root.xml");

    //for (int i = 0; i < PillarMax; i++) {
    //    GameObject* temp = GameObject::Create();
    //    temp->texture = pillar1Ob->root->Find("Mesh")->texture;
    //    temp->mesh = pillar1Ob->root->Find("Mesh")->mesh;
    //    temp->shader = pillar1Ob->root->Find("Mesh")->shader;
    //    temp->scale = pillar1Ob->root->Find("Mesh")->scale;
    //    temp->name = "Pillar1_" + to_string(i);
    //    temp->SetWorldPosX(-map->root->Find("Ground")->scale.x + i * 10.0f);
    //    temp->SetWorldPosY(3.5f);
    //    pillar1Root->AddChild(temp);
    //    //vMapOb.push_back(temp);
    //}

    //for (int i = 0; i < PillarMax - 1; i++) {
    //    GameObject* temp = GameObject::Create();
    //    temp->texture = pillar1Ob->root->Find("Mesh")->texture;
    //    temp->mesh = pillar1Ob->root->Find("Mesh")->mesh;
    //    temp->shader = pillar1Ob->root->Find("Mesh")->shader;
    //    temp->scale = pillar1Ob->root->Find("Mesh")->scale;
    //   
    //    temp->name = "Pillar1_under" + to_string(i);
    //    cout << pillar1Root->root->Find("Pillar1_" + to_string(i + 1))->GetLocalPos().x << ", " << pillar1Root->root->Find("Pillar1_" + to_string(i))->GetLocalPos().x << endl;
    //    temp->SetLocalPosX(
    //        (pillar1Root->root->Find("Pillar1_" + to_string(i + 1))->GetLocalPos().x
    //        + pillar1Root->root->Find("Pillar1_" + to_string(i))->GetLocalPos().x) * 0.5f);
    //    temp->scale.y = 6.0f;
    //    temp->scale.x = (pillar1Root->root->Find("Pillar1_" + to_string(i + 1))->GetLocalPos().x
    //        - pillar1Root->root->Find("Pillar1_" + to_string(i))->GetLocalPos().x) * 0.5f - pillar1Root->root->Find("Pillar1_" + to_string(i))->scale.x;
    //    temp->collider->scale = temp->scale;
    //    temp->SetLocalPosY(3.0f);
    //    pillar1Root->AddChild(temp);
    //    //vMapOb.push_back(temp);
    //}
}

Main::~Main()
{
    grid->Release();
    cam1->Release();
    map->Release();
    //pillar1Ob->Release();
    //pillar1Root->Release();
}

void Main::Init()
{

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
    //pillar1Ob->RenderHierarchy();
    //pillar1Root->RenderHierarchy();
    ImGui::End();

    grid->Update();
    map->Update();
    //pillar1Ob->Update();
    //pillar1Root->Update();
    Camera::main->Update();
}

void Main::LateUpdate()
{
}
void Main::PreRender()
{
}

void Main::Render()
{
    Camera::main->Set();
    grid->Render();
    map->Render();
    //pillar1Ob->Render();
    //pillar1Root->Render();
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