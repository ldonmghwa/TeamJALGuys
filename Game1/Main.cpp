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
    obstacle1->LoadFile("board2.xml");
    obstacle1->name = "temp";
    obstacle2 = Actor::Create();
    obstacle2->LoadFile("glitingBoard2.xml");
    obstacle2->name = "temp2";
    obstacle1Root = Actor::Create();
    //obstacle1Root->LoadFile("BoardRoot.xml");
    obstacle1Root->name = "boardRoot";
    //map->AddObstacle("LeftRightBoard.xml");
    float startpos = -16.0f;
    /*for (int i = 0; i < 30; i++) {
        GameObject* temp = GameObject::Create();
        temp->mesh = obstacle1->root->mesh;
        temp->shader = obstacle1->root->shader;
        temp->scale = obstacle1->root->scale;
        temp->name = "GlitingBoard_" + to_string(i);
        temp->collider = obstacle1->collider;
        if (i < 5) {
            temp->texture = obstacle1->root->texture;
            temp->SetLocalPosX(startpos + obstacle1->scale.x * 2.0f * i);
            if (i % 2 == 1) temp->SetLocalPosZ(obstacle1->scale.z * 2.0f);
        }
        else if (i < 10) {
            temp->texture = obstacle2->root->texture;
            temp->SetLocalPosX(startpos + obstacle1->scale.x * 2.0f * (i - 5));
            if (i % 2 == 1) temp->SetLocalPosZ(obstacle1->scale.z * 2.0f);
        }
        else if (i < 15) {
            temp->texture = obstacle1->root->texture;
            temp->SetLocalPosX(startpos + obstacle1->scale.x * 2.0f * (i - 10));
            if (i % 2 == 1) temp->SetLocalPosZ(3 * obstacle1->scale.z * 2.0f);
            else temp->SetLocalPosZ(2 * obstacle1->scale.z * 2.0f);
        }
        else if (i < 20) {
            temp->texture = obstacle2->root->texture;
            temp->SetLocalPosX(startpos + obstacle1->scale.x * 2.0f * (i - 15));
            if (i % 2 == 1) temp->SetLocalPosZ(3 * obstacle1->scale.z * 2.0f);
            else temp->SetLocalPosZ(2 * obstacle1->scale.z * 2.0f);
        }
        else if (i < 25) {
            temp->texture = obstacle1->root->texture;
            temp->SetLocalPosX(startpos + obstacle1->scale.x * 2.0f * (i - 20));
            if (i % 2 == 1) temp->SetLocalPosZ(5 * obstacle1->scale.z * 2.0f);
            else temp->SetLocalPosZ(4 * obstacle1->scale.z * 2.0f);
        }
        else if (i < 30) {
            temp->texture = obstacle2->root->texture;
            temp->SetLocalPosX(startpos + obstacle1->scale.x * 2.0f * (i - 25));
            if (i % 2 == 1) temp->SetLocalPosZ(5 * obstacle1->scale.z * 2.0f);
            else temp->SetLocalPosZ(4 * obstacle1->scale.z * 2.0f);
        }
        obstacle1Root->AddChild(temp);
    }*/

    //for (int i = 0; i < 30; i++) {
    //    GameObject* temp = GameObject::Create();
    //    temp->texture = obstacle1->root->texture;
    //    temp->mesh = obstacle1->root->mesh;
    //    temp->shader = obstacle1->root->shader;
    //    temp->scale = obstacle1->root->scale;
    //    temp->name = "UpDownBoard_" + to_string(i);
    //    temp->collider = obstacle1->collider;
    //    if (i < 6) {
    //        temp->SetLocalPosX(-obstacle1->scale.x * 6.3f + obstacle1->scale.x * 2.5f * i);
    //    }
    //    else if(i < 12){
    //        temp->SetLocalPosX(-obstacle1->scale.x * 6.3f + obstacle1->scale.x * 2.5f * (i - 6));
    //        temp->SetLocalPosZ(obstacle1->scale.z * 5.5f);
    //    }
    //    else if (i < 18) {
    //        temp->SetLocalPosX(-obstacle1->scale.x * 6.3f + obstacle1->scale.x * 2.5f * (i - 12));
    //        temp->SetLocalPosZ(obstacle1->scale.z * 5.5f * 2);
    //    }
    //    else if (i < 24) {
    //        temp->SetLocalPosX(-obstacle1->scale.x * 6.3f + obstacle1->scale.x * 2.5f * (i - 18));
    //        temp->SetLocalPosZ(obstacle1->scale.z * 5.5f * 3);
    //    }
    //    else if (i < 30) {
    //        temp->SetLocalPosX(-obstacle1->scale.x * 6.3f + obstacle1->scale.x * 2.5f * (i - 24));
    //        temp->SetLocalPosZ(obstacle1->scale.z * 5.5f * 4);
    //    }
    //    //temp->SetLocalPosZ(-obstacle1->scale.z * 5.0f + obstacle1->scale.z * 5.0f * i);
    //    obstacle1Root->AddChild(temp);
    //}

    /*for (int i = 0; i < 8; i++) {
        GameObject* temp = GameObject::Create();
        temp->texture = obstacle1->root->texture;
        temp->mesh = obstacle1->root->mesh;
        temp->shader = obstacle1->root->shader;
        temp->scale = obstacle1->root->scale;
        temp->name = "LeftRightBoard_" + to_string(i);
        temp->collider = obstacle1->collider;
        temp->SetWorldPosZ(i * obstacle1->scale.z * 2.0f * 3.0f);
        obstacle1Root->AddChild(temp);
    }*/
}

Main::~Main()
{
    grid->Release();
    cam1->SaveFile("Cam.xml");
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