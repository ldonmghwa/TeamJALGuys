#include "stdafx.h"
#include "Map.h"
#include "WallMap.h"
#include "Main.h"

Main::Main()
{
    grid = Grid::Create();

    cam1 = Camera::Create();
    cam1->LoadFile("Cam.xml");
    Camera::main = cam1;//

    cam1->viewport.x = 0.0f;
    cam1->viewport.y = 0.0f;
    cam1->viewport.width = App.GetWidth();
    cam1->viewport.height = App.GetHeight();
    cam1->width = App.GetWidth();
    cam1->height = App.GetHeight();

    map = WallMap::Create();
    map->LoadFile("Map1.xml");
    map->name = "Map";
    
    obstacle1 = Actor::Create();
    obstacle1->LoadFile("glitingBoard1.xml");
    obstacle1->name = "temp";
    obstacle2 = Actor::Create();
    obstacle2->LoadFile("glitingBoard2.xml");
    obstacle2->name = "temp2";
    obstacle1Root = Actor::Create();
    //obstacle1Root->LoadFile("UpDownBoard.xml");
    obstacle1Root->name = "boardRoot";
    //map->AddObstacle("UpDownBoard.xml");
    for (int i = 0; i < 12; i++) {
        GameObject* temp = GameObject::Create();
        temp->mesh = obstacle1->root->mesh;
        temp->shader = obstacle1->root->shader;
        temp->scale = obstacle1->root->scale;
        temp->name = "GlitingBoard_" + to_string(i);
        temp->collider = obstacle1->collider;
        if (i % 2 == 0) {
            temp->texture = obstacle1->root->texture;
            temp->SetLocalPosX(-20.0f + obstacle1->scale.x * 2.0f * i);
            temp->SetLocalPosZ(obstacle1->scale.z);
        }
        else {
            temp->texture = obstacle2->root->texture;
            temp->SetLocalPosX(-20.0f + obstacle1->scale.x * 2.0f * i);
        }
        //temp->SetLocalPosZ(-obstacle1->scale.z * 5.0f + obstacle1->scale.z * 5.0f * i);
        obstacle1Root->AddChild(temp);
    }
    
    //for (int i = 0; i < 12; i++) {
    //    GameObject* temp = GameObject::Create();
    //    temp->texture = obstacle1->root->texture;
    //    temp->mesh = obstacle1->root->mesh;
    //    temp->shader = obstacle1->root->shader;
    //    temp->scale = obstacle1->root->scale;
    //    temp->name = "UpDownBoard_" + to_string(i);
    //    temp->collider = obstacle1->collider;
    //    if (i % 2 == 0) {
    //        temp->SetLocalPosX(-obstacle1->scale.x * 6.3f + obstacle1->scale.x * 2.5f * i / 2);
    //        temp->SetLocalPosZ(obstacle1->scale.z * 4.5f);
    //    }
    //    else {
    //        temp->SetLocalPosX(-obstacle1->scale.x * 6.3f + obstacle1->scale.x * 2.5f * (i - 1) / 2);
    //    }
    //    //temp->SetLocalPosZ(-obstacle1->scale.z * 5.0f + obstacle1->scale.z * 5.0f * i);
    //    obstacle1Root->AddChild(temp);
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
    obstacle1->Release();
    obstacle2->Release();
    //obstacle1Root->Release();
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
    obstacle1->RenderHierarchy();
    obstacle2->RenderHierarchy();
    obstacle1Root->RenderHierarchy();
    ImGui::End();

    grid->Update();
    map->Update();
    obstacle1->Update();
    obstacle2->Update();
    obstacle1Root->Update();
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
    obstacle1->Render();
    obstacle2->Render();
    obstacle1Root->Render();
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