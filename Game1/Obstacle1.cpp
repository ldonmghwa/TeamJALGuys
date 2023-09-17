#include "stdafx.h"
#include "Obstacle.h"
#include "Obstacle1.h"

Obstacle1::Obstacle1() :Obstacle()
{
 
    root->LoadFile("obstacle1.xml");
    HitTime = 0;
}

Obstacle1::~Obstacle1()
{
}

void Obstacle1::Init()
{
}

void Obstacle1::Release()
{
}

void Obstacle1::Update()
{
	Obstacle::Update();

	root->Find("floor1")->rotation.y -= 0.3* DELTA;
	root->Find("swing1")->rotation.y += 2 * DELTA;

    root->Find("floor2")->rotation.y -= 0.3 * DELTA;
    root->Find("swing2")->rotation.y += 2 * DELTA;

    root->Find("floor3")->rotation.y -= 0.3 * DELTA;
    root->Find("swing3")->rotation.y += 2 * DELTA;
   
    if (isGoCircle)
    {
        float elapsedTime = TIMER->GetWorldTime() - HitTime;
       
        float dx = 1.0f; 
        float dz = 0.0f; 

        float direction = atan2(dz, dx);

        float angle = direction * ToRadian;
       
        if (elapsedTime <= 0.2f)
        {
            player->body->MoveWorldPos(Vector3(-cos(angle)*10, 0, -sin(angle)*10) * 5 * DELTA);
           
        }
        else
        {
            isGoCircle = false;
        }
    }
   
}

void Obstacle1::LateUpdate()
{
    Obstacle::LateUpdate();

    if (root->Find("floor1")->Intersect(player->body)|| root->Find("floor2")->Intersect(player->body)|| root->Find("floor3")->Intersect(player->body))
    {

        player->isLand = true;


        Vector3 IntersectPos = player->GetWorldPos();
        float centerX = 0;
        float centerY = 0;
        float centerZ = 0;
        Vector3 CenterPos(centerX, centerY, centerZ);

        Vector3 Offset = IntersectPos - CenterPos;
        float distance = sqrt(Offset.x * Offset.x + Offset.z * Offset.z);

        // 원의 경계에서 플레이어의 위치 계산
        float angle = atan2(Offset.z, Offset.x); // 충돌 지점과 중심 사이의 각도
        float newX = centerX + 10 * cos(angle);
        float newZ = centerZ + 10 * sin(angle);//5 저거의 수치로 힘 조절

        // 플레이어를 새 위치로 이동
        player->body->MoveWorldPos(Vector3(newZ, IntersectPos.y, newX) * 10 * DELTA);
    }




    if (root->Find("swingson1")->Intersect(player->body) || root->Find("swingson2")->Intersect(player->body)|| root->Find("swingson3")->Intersect(player->body))
    {
        HitTime = TIMER->GetWorldTime();

        isGoCircle = true;
     
    }
}

void Obstacle1::Render()
{
	Obstacle::Render();
}
