#include "stdafx.h"
#include "Obstacle.h"
#include "Obstacle1.h"

Obstacle1::Obstacle1():Obstacle()
{
	root->LoadFile("fallworld.xml");
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

	root->Find("obstacle1")->rotation.y += 0.3 * DELTA;
	root->Find("obchild1")->rotation.y -= 2 * DELTA;
}

void Obstacle1::LateUpdate()
{
	Obstacle::LateUpdate();

    if (root->Find("obstacle1")->Intersect(player->body))
    {

        player->isLand = true;

        Vector3 IntersectPos = player->GetWorldPos();
        float centerX = root->Find("obstacle1")->GetWorldPos().x;
        float centerY = root->Find("obstacle1")->GetWorldPos().y;
        float centerZ = root->Find("obstacle1")->GetWorldPos().z - 100;//��? �̰� �𸣰��� 0,0,0������ ������
        Vector3 CenterPos(centerX, centerY, centerZ);

        Vector3 Offset = IntersectPos - CenterPos;
        float distance = sqrt(Offset.x * Offset.x + Offset.z * Offset.z);

        // ���� ��迡�� �÷��̾��� ��ġ ���
        float angle = atan2(Offset.z, Offset.x); // �浹 ������ �߽� ������ ����
        float newX = centerX + 5 * cos(angle);
        float newZ = centerZ + 5 * sin(angle);//5 ������ ��ġ�� �� ����

        // �÷��̾ �� ��ġ�� �̵�
        player->body->MoveWorldPos(Vector3(newX, IntersectPos.y, newZ) * DELTA);
    }

    else player->isLand = false;


    if (root->Find("obson1")->Intersect(player->body))
    {

        Vector3 IntersectPos = player->GetWorldPos();
        float centerX = root->Find("obchild1")->GetWorldPos().x;
        float centerY = root->Find("obchild1")->GetWorldPos().y;
        float centerZ = root->Find("obchild1")->GetWorldPos().z;
        Vector3 CenterPos(centerX, centerY, centerZ);

        Vector3 Offset = IntersectPos - CenterPos;
        float distance = sqrt(Offset.x * Offset.x + Offset.z * Offset.z);


        float angle = atan2(Offset.z, Offset.x);
        float newX = centerX + 50 + 300 * cos(angle);
        float newZ = centerZ + 30 + 100 * sin(angle);

        player->body->MoveWorldPos(Vector3(newX, IntersectPos.y, newZ) * DELTA);
    }
}

void Obstacle1::Render()
{
	Obstacle::Render();
}
