#include "stdafx.h"
#include "Obstacle.h"
#include "Obstacle3Sphere.h"
#include "Obstacle3.h"



Obstacle3::Obstacle3() :Obstacle()
{
    root->LoadFile("obstacle3.xml");
   
    fireTime = 0;
    for (int i = 0; i < 2; i++)
    {
        ball[i] = Obstacle3Sphere::Create();
    }

}

Obstacle3::~Obstacle3()
{
}

Obstacle3::Obstacle3(Vector3 pos)
{
    root->LoadFile("obstacle3.xml");

    fireTime = 0;
    for (int i = 0; i < 2; i++)
    {
        ball[i] = Obstacle3Sphere::Create();
    }

    root->SetWorldPos(pos);
}

void Obstacle3::Init()
{
}

void Obstacle3::Release()
{
}

void Obstacle3::Update()
{
 
    Obstacle::Update();

    if (GM->isActive)
    {
        for (int i = 0; i < 2; i++)
        {
            if (TIMER->GetTick(fireTime, RANDOM->Float(4,8)))
            {
                ball[i]->Fire(root->GetWorldPos(), -root->GetForward(), 50);
            }
        }
    }

    ImGui::Begin("Hierarchy");
    for (int i = 0; i < 2; i++)
    {
        ball[i]->RenderHierarchy();
    }
    ImGui::End();
    
    

    for (int i = 0; i < 2; i++)
    {
        ball[i]->Update();
    }
}

void Obstacle3::LateUpdate()
{
    Obstacle::LateUpdate();
    for (int i = 0; i < 2; i++)
    {
        ball[i]->LateUpdate();
    }
}

void Obstacle3::Render()
{
    Obstacle::Render();

    for (int i = 0; i < 2; i++)
    {
        ball[i]->Render();
    }
}


