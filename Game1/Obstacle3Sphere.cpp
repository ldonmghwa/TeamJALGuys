#include "stdafx.h"
#include "Obstacle3Sphere.h"

Obstacle3Sphere::Obstacle3Sphere()
{
	fireTime = 0.0f;
	disappearTime = 0.0f;
	collisionTime = 0.0f;
}

Obstacle3Sphere::~Obstacle3Sphere()
{
}

Obstacle3Sphere* Obstacle3Sphere::Create()
{
	
	Obstacle3Sphere* temp = new Obstacle3Sphere();
	temp->LoadFile("ball.xml");
	temp->type = ObType::Actor;
	return temp;
}

void Obstacle3Sphere::Update()
{
	if (not isFire) return;
	
	Actor::Update();

	root->rotation.x += 2 * DELTA;
	root->rotation.z += 2 * DELTA;

	root->MoveWorldPos(dir * power * DELTA);

	if (isHit)
	{

		float elapsedTime = TIMER->GetWorldTime() - collisionTime;

		float ballCenterX = root->GetWorldPos().x - player->body->GetWorldPos().x;
		float ballCenterZ = root->GetWorldPos().z - player->body->GetWorldPos().z;
		Vector3 ballCenter(ballCenterX, 0, ballCenterZ);
		ballCenter.Normalize();

		if (elapsedTime <= 1.0f)
		{
			player->body->MoveWorldPos(-ballCenter * DELTA * 40);
		}
		else
		{
			isHit = false;
		}
	}


	if (GetWorldPos().z < 260)
	{
		isFire = false;
	}
	
}

void Obstacle3Sphere::LateUpdate()
{
	if (not isFire) return;

	if (root->Intersect(player->body))
	{
		collisionTime = TIMER->GetWorldTime();
		isHit = true;
		
	}
}

void Obstacle3Sphere::Render()
{
	if (not isFire) return;

	Actor::Render();
}

bool Obstacle3Sphere::Fire(Vector3 pos,Vector3 dir, float power)
{
	if (isFire)  return false;

	SetWorldPos(pos);
	this->dir = dir;
	this->power = power;
	isFire = true;

	return true;
}


