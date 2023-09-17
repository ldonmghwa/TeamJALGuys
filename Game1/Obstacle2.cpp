#include "stdafx.h"
#include "Obstacle.h"
#include "Obstacle2.h"

Obstacle2::Obstacle2() :Obstacle()
{
	root->LoadFile("obstacleWindmill.xml");
	CollisionTime = 0.0f;
}

Obstacle2::~Obstacle2()
{
}

Obstacle2::Obstacle2(Vector3 pos)
{
    root->LoadFile("obstacleWindmill.xml");
    CollisionTime = 0.0f;
    root->SetWorldPos(pos);
}

void Obstacle2::Init()
{
}

void Obstacle2::Release()
{
}

void Obstacle2::Update()
{

    Obstacle::Update();
    root->Find("obstacle1Root")->rotation.z += 1.3 * DELTA;
    root->Find("obstacle1poll1")->SetWorldPos(root->Find("obstacle1Root")->GetWorldPos());

if (isGoFoward)
{
    float elapsedTime = TIMER->GetWorldTime() - CollisionTime;
    if (elapsedTime <= 0.5f) 
    {
        player->body->MoveWorldPos(-Vector3(-1, 0, 0) * 60 * DELTA);
    }
    else
    {
        isGoFoward = false;
    }
}

if (isGoBack)
{
    float elapsedTime = TIMER->GetWorldTime() - CollisionTime;
    if (elapsedTime <= 0.4f) 
    {
        player->body->MoveWorldPos(-Vector3(-1,0,0) * 50 * DELTA);
    }
    else
    {
        isGoBack = false;
    }
}
}

void Obstacle2::LateUpdate()
{
    Obstacle::LateUpdate();

    if (root->Find("obstacle1Rootchild1")->Intersect(player->body))
    {
        CollisionTime = TIMER->GetWorldTime();

        if (player->body->GetWorldPos().z > root->Find("obstacle1Rootchild1")->GetWorldPos().z)
        {
            isGoFoward = true;
        }
        else
        {
            isGoBack = true;
        }
    }

    if (root->Find("obstacle1Rootchild2")->Intersect(player->body))
    {
        CollisionTime = TIMER->GetWorldTime();

        if (player->body->GetWorldPos().z > root->Find("obstacle1Rootchild2")->GetWorldPos().z)
        {
            isGoFoward = true;
        }
        else
        {
            isGoBack = true;
        }
    }


}

void Obstacle2::Render()
{
	Obstacle::Render();
}
