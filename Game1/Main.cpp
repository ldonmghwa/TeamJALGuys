#include "stdafx.h"
#include "Map.h"
#include "WallMap.h"
#include "Main.h"

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
    
    //obstacle1 = Actor::Create();
    //obstacle1->LoadFile("board.xml");
    //obstacle1->name = "temp";
    //obstacle2 = Actor::Create();
    //obstacle2->LoadFile("board2.xml");
    //obstacle2->name = "temp2";
    /*obstacle1Root = Actor::Create();
    obstacle1Root->LoadFile("Pillar1Root.xml");
    obstacle1Root->name = "Pillar1Root";*/
    map->AddObstacle("BoardRoot.xml");

    //for (int i = 0; i < 20; i++) {
    //    GameObject* temp = GameObject::Create();
    //    if (i < 10) {
    //        temp->texture = obstacle1->root->texture;
    //        temp->mesh = obstacle1->root->mesh;
    //        temp->shader = obstacle1->root->shader;
    //        temp->scale = obstacle1->root->scale;
    //        temp->name = "Board_" + to_string(i);
    //        temp->collider = obstacle1->collider;
    //        temp->SetWorldPosX(-map->root->Find("Ground")->scale.x + i * temp->scale.x * 2.0f + temp->scale.x);
    //        if (i % 2 == 0) {
    //            temp->SetWorldPosZ(temp->scale.z * 2.0f);
    //        }
    //    }
    //    else {
    //        temp->texture = obstacle2->root->texture;
    //        temp->mesh = obstacle2->root->mesh;
    //        temp->shader = obstacle2->root->shader;
    //        temp->scale = obstacle2->root->scale;
    //        temp->name = "Board_" + to_string(i);
    //        temp->collider = obstacle2->collider;
    //        temp->SetWorldPosX(-map->root->Find("Ground")->scale.x + (i - 10) * temp->scale.x * 2.0f + temp->scale.x);
    //        if (i % 2 != 0) {
    //            temp->SetWorldPosZ(temp->scale.z * 2.0f);
    //        }
    //    }
    //    obstacle1Root->AddChild(temp);
    //   
    //    
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
    /*obstacle1->Release();
    obstacle2->Release();
    obstacle1Root->Release();*/
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
    /*obstacle1->RenderHierarchy();
    obstacle2->RenderHierarchy();
    obstacle1Root->RenderHierarchy();*/
    ImGui::End();

    grid->Update();
    map->Update();
    /*obstacle1->Update();
    obstacle2->Update();
    obstacle1Root->Update();*/
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
    /*obstacle1->Render();
    obstacle2->Render();
    obstacle1Root->Render();*/
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